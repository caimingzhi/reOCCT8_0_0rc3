import sys
import os
import csv
import clang.cindex
from clang.cindex import CursorKind, TokenKind, TranslationUnit

# ================= 配置区域 =================
# 如果系统找不到 libclang，请取消下面注释并手动指定 bin 目录
# clang.cindex.Config.set_library_path(r'C:\Program Files\LLVM\bin')

EXTENSIONS = {'.cxx', '.hpp', '.cpp', '.h', '.cc', '.c'}
# ===========================================

def load_mapping(csv_file):
    mapping = {}
    with open(csv_file, 'r', encoding='utf-8') as f:
        reader = csv.reader(f)
        for row in reader:
            if len(row) >= 2:
                cls_name = row[0].strip()
                ns_name = row[1].strip()
                if cls_name and ns_name:
                    mapping[cls_name] = ns_name
    return mapping

def generate_namespace_wrappers_bytes(namespace_str):
    parts = namespace_str.split('::')
    prefix = " ".join([f"namespace {p} {{" for p in parts])
    suffix = " ".join(["}" for _ in parts])
    comment = f" // namespace {namespace_str}"
    # 前后加换行符确保格式清晰
    return (f"\n{prefix}\n".encode('utf-8'), f"\n{suffix}{comment}\n".encode('utf-8'))

class FileRefactor:
    def __init__(self, file_path, mapping):
        self.file_path = file_path
        self.abs_file_path = os.path.abspath(file_path)
        self.mapping = mapping
        self.replacements = [] 
        self.content_bytes = b""
        
        self.protected_offsets = [] # 用于保护字符串和类定义区域
        self.protected_lines = set() # 物理行盾牌：绝对不改 # 开头的行

    def _identify_pp_lines(self):
        """
        物理扫描：标记所有预处理行（以 # 开头或多行宏延续）
        """
        lines = self.content_bytes.split(b'\n')
        is_multiline_pp = False
        for i, line in enumerate(lines):
            stripped = line.strip()
            # 标记以 # 开头的行，或上一行带有 \ 延续符号的行
            if stripped.startswith(b'#') or is_multiline_pp:
                self.protected_lines.add(i + 1) # Clang 行号从 1 开始
                # 检查本行末尾是否有续行符 \
                is_multiline_pp = stripped.endswith(b'\\')
            else:
                is_multiline_pp = False

    def process(self):
        index = clang.cindex.Index.create()
        
        if not os.path.exists(self.file_path):
            return False

        with open(self.file_path, 'rb') as f:
            self.content_bytes = f.read()

        self._identify_pp_lines()

        try:
            # PARSE_DETAILED_PROCESSING_RECORD 协助识别预处理节点
            tu = index.parse(self.file_path, args=['-std=c++17', '-I.'], 
                             options=TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
        except Exception as e:
            print(f"  [Error] Parse failed: {e}")
            return False

        # 1. 扫描 AST 建立保护区
        self.scan_ast_recursive(tu.cursor)

        # 2. 扫描 Token 应用修改
        self.scan_tokens(tu)

        return self.apply_changes()

    def scan_ast_recursive(self, cursor):
        # 路径过滤：不进入 #include 的文件
        if cursor.kind != CursorKind.TRANSLATION_UNIT:
            if cursor.location.file is None or os.path.abspath(cursor.location.file.name) != self.abs_file_path:
                return

        # 保护字符串
        if cursor.kind == CursorKind.STRING_LITERAL:
            self.protected_offsets.append((cursor.extent.start.offset, cursor.extent.end.offset))
            return

        # 处理并保护类定义/前向声明
        if cursor.kind in [CursorKind.CLASS_DECL, CursorKind.STRUCT_DECL]:
            if cursor.spelling in self.mapping:
                self.handle_class_decl(cursor)

        for child in cursor.get_children():
            self.scan_ast_recursive(child)

    def handle_class_decl(self, cursor):
        is_wrap_target = False
        if cursor.is_definition():
            is_wrap_target = True
        else:
            # 前向声明判断：父节点为全局、命名空间或类
            parent = cursor.lexical_parent
            if parent and parent.kind in [CursorKind.TRANSLATION_UNIT, CursorKind.NAMESPACE, 
                                          CursorKind.CLASS_DECL, CursorKind.STRUCT_DECL]:
                is_wrap_target = True

        if is_wrap_target:
            # 加入偏移量保护区，防止 Token 扫描阶段在类名上加前缀
            self.protected_offsets.append((cursor.extent.start.offset, cursor.extent.end.offset))
            self.add_wrapper(cursor)

    def scan_tokens(self, tu):
        # 正确获取根游标范围
        extent = tu.cursor.extent
        tokens = tu.get_tokens(extent=extent)

        prev_token = None
        for token in tokens:
            # 1. 路径检查
            if token.location.file is None or os.path.abspath(token.location.file.name) != self.abs_file_path:
                continue

            # 2. 【核心防御】检查是否在 # 开头的预处理行
            if token.location.line in self.protected_lines:
                prev_token = token
                continue

            # 3. 检查是否在字符串或已处理的类定义内部
            if any(s <= token.location.offset < e for s, e in self.protected_offsets):
                prev_token = token
                continue

            # 4. 标识符替换
            if token.kind == TokenKind.IDENTIFIER and token.spelling in self.mapping:
                # 过滤掉 ~MyClass 和 MyNamespace::MyClass
                if prev_token and prev_token.spelling in ['::', '~']:
                    prev_token = token
                    continue
                
                self.add_prefix(token)

            prev_token = token

    def add_wrapper(self, cursor):
        target_ns = self.mapping[cursor.spelling]
        prefix_bytes, suffix_bytes = generate_namespace_wrappers_bytes(target_ns)
        start, end = cursor.extent.start.offset, cursor.extent.end.offset
        
        # 寻找类定义结束后的分号
        limit = min(end + 200, len(self.content_bytes))
        scan_pos = end
        while scan_pos < limit:
            if self.content_bytes[scan_pos] == 59: # ';'
                scan_pos += 1
                break
            elif self.content_bytes[scan_pos] not in (9, 10, 13, 32): 
                break
            scan_pos += 1
        
        self.replacements.append((start, 0, prefix_bytes))
        self.replacements.append((scan_pos, 0, suffix_bytes))

    def add_prefix(self, token):
        target_ns = self.mapping[token.spelling]
        start = token.location.offset
        length = len(token.spelling.encode('utf-8'))
        new_bytes = f"{target_ns}::{token.spelling}".encode('utf-8')
        self.replacements.append((start, length, new_bytes))

    def apply_changes(self):
        if not self.replacements: return False
        
        # 倒序应用修改
        self.replacements.sort(key=lambda x: x[0], reverse=True)
        unique = []
        seen = set()
        for r in self.replacements:
            if r[0] not in seen:
                unique.append(r)
                seen.add(r[0])
        
        new_content = bytearray(self.content_bytes)
        for offset, length, text_bytes in unique:
            new_content[offset : offset + length] = text_bytes
            
        if new_content != self.content_bytes:
            with open(self.file_path, 'wb') as f:
                f.write(new_content)
            return True
        return False

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py <src_dir> <mapping.csv>")
        return
    src_dir, csv_file = sys.argv[1], sys.argv[2]
    mapping = load_mapping(csv_file)
    print(f"Loaded {len(mapping)} rules. Scanning...")
    
    for root, dirs, files in os.walk(src_dir):
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        for file in files:
            if os.path.splitext(file)[1].lower() in EXTENSIONS:
                path = os.path.join(root, file)
                try:
                    refactor = FileRefactor(path, mapping)
                    if refactor.process():
                        print(f"[Fixed] {path}")
                except Exception as e:
                    print(f"\n[Error] {path}: {e}")

if __name__ == "__main__":
    main()
