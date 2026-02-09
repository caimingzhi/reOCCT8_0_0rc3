import sys
import os
import csv
import logging
import clang.cindex
from clang.cindex import CursorKind, TokenKind, TranslationUnit

# ================= 配置区域 =================
# 如果你的系统环境找不到 libclang，请取消下行注释并手动指定路径
# clang.cindex.Config.set_library_path(r'C:\Program Files\LLVM\bin')

EXTENSIONS = {'.cxx', '.hpp', '.cpp', '.h', '.cc', '.c'}
# ===========================================

def load_mapping(csv_file):
    """从 CSV 加载类名到命名空间的映射"""
    mapping = {}
    try:
        with open(csv_file, 'r', encoding='utf-8') as f:
            reader = csv.reader(f)
            for row in reader:
                if len(row) >= 2:
                    cls_name = row[0].strip()
                    ns_name = row[1].strip()
                    if cls_name and ns_name:
                        mapping[cls_name] = ns_name
    except Exception as e:
        print(f"Error loading CSV: {e}")
        sys.exit(1)
    return mapping

def get_all_header_dirs(root_dir):
    """自动扫描 root_dir 下所有包含头文件的目录，用于 Clang -I 参数"""
    header_dirs = set()
    header_dirs.add(os.path.abspath(root_dir))
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            if file.lower().endswith(('.h', '.hpp', '.hxx')):
                header_dirs.add(os.path.abspath(root))
                break
    return [f"-I{d}" for d in header_dirs]

def setup_logging(log_file):
    """设置日志：同时输出到控制台和文件"""
    logger = logging.getLogger()
    logger.setLevel(logging.WARNING)
    formatter = logging.Formatter('%(asctime)s [%(levelname)s] %(message)s')
    
    fh = logging.FileHandler(log_file, mode='w', encoding='utf-8')
    fh.setFormatter(formatter)
    logger.addHandler(fh)

    ch = logging.StreamHandler()
    ch.setLevel(logging.WARNING)
    logger.addHandler(ch)
    return logger

def generate_namespace_wrappers_bytes(namespace_str):
    """生成用于包裹类的 bytes 内容"""
    parts = namespace_str.split('::')
    prefix = ("\n" + " ".join([f"namespace {p} {{" for p in parts]) + "\n").encode('utf-8')
    suffix = ("\n" + " ".join(["}" for _ in parts]) + f" // namespace {namespace_str}\n").encode('utf-8')
    return prefix, suffix

class FileRefactor:
    def __init__(self, file_path, mapping, clang_args):
        self.file_path = file_path
        self.abs_file_path = os.path.abspath(file_path)
        self.mapping = mapping
        self.clang_args = clang_args
        self.replacements = [] 
        self.content_bytes = b""
        self.protected_offsets = [] 
        self.protected_lines = set()

    def _identify_pp_lines(self):
        """标记所有 # 开头的预处理行"""
        lines = self.content_bytes.split(b'\n')
        is_multiline_pp = False
        for i, line in enumerate(lines):
            stripped = line.strip()
            if stripped.startswith(b'#') or is_multiline_pp:
                self.protected_lines.add(i + 1)
                is_multiline_pp = stripped.endswith(b'\\')
            else:
                is_multiline_pp = False

    def process(self):
        try:
            with open(self.file_path, 'rb') as f:
                self.content_bytes = f.read()
        except Exception as e:
            logging.error(f"Cannot read {self.file_path}: {e}")
            return False

        self._identify_pp_lines()
        index = clang.cindex.Index.create()
        try:
            # ================= 核心修改处 =================
            # 添加 -D_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH 忽略版本检查
            # 添加 -fms-compatibility 增强对 Windows 头文件的兼容性
            base_args = [
                '-std=c++17', 
                '-D_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH', 
                '-fms-compatibility',
                '-fms-extensions'
            ]
            
            tu = index.parse(self.abs_file_path, 
                             args=base_args + self.clang_args,
                             options=TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
            # =============================================
            
            for diag in tu.diagnostics:
                if diag.severity >= clang.cindex.Diagnostic.Error:
                    logging.debug(f"[{self.file_path}] Clang Diag: {diag.spelling} (Line {diag.location.line})")
        except Exception as e:
            logging.error(f"Clang parse exception for {self.file_path}: {e}")
            return False

        self.scan_ast_recursive(tu.cursor)
        self.scan_tokens(tu)
        return self.apply_changes()

    def scan_ast_recursive(self, cursor):
        """遍历 AST 寻找类定义和需要保护的字符串"""
        if cursor.kind != CursorKind.TRANSLATION_UNIT:
            if cursor.location.file is None or os.path.abspath(cursor.location.file.name) != self.abs_file_path:
                return
        
        # 保护字符串字面量
        if cursor.kind == CursorKind.STRING_LITERAL:
            self.protected_offsets.append((cursor.extent.start.offset, cursor.extent.end.offset))
            return

        # 发现类或结构体
        if cursor.kind in [CursorKind.CLASS_DECL, CursorKind.STRUCT_DECL]:
            if cursor.spelling in self.mapping:
                self.handle_class_decl(cursor)

        for child in cursor.get_children():
            self.scan_ast_recursive(child)

    def handle_class_decl(self, cursor):
        """判断是定义还是前向声明，并进行包裹"""
        should_wrap = False
        if cursor.is_definition():
            should_wrap = True
        else:
            parent = cursor.lexical_parent
            if parent and parent.kind in [CursorKind.TRANSLATION_UNIT, CursorKind.NAMESPACE, 
                                          CursorKind.CLASS_DECL, CursorKind.STRUCT_DECL]:
                should_wrap = True
        
        if should_wrap:
            # 保护类名所在区域，防止 Token 扫描阶段重复修改
            self.protected_offsets.append((cursor.extent.start.offset, cursor.extent.end.offset))
            self.add_wrapper_logic(cursor)

    def scan_tokens(self, tu):
        """遍历 Token 查找所有引用处"""
        prev_token = None
        for token in tu.cursor.get_tokens():
            if token.location.file is None or os.path.abspath(token.location.file.name) != self.abs_file_path:
                continue
            # 行盾牌保护
            if token.location.line in self.protected_lines:
                prev_token = token
                continue
            # 偏移量保护（字符串/定义）
            if any(s <= token.location.offset < e for s, e in self.protected_offsets):
                prev_token = token
                continue
            
            # 匹配标识符并加前缀
            if token.kind == TokenKind.IDENTIFIER and token.spelling in self.mapping:
                if prev_token and prev_token.spelling in ['::', '~']:
                    prev_token = token
                    continue
                self.add_prefix_logic(token)
            prev_token = token

    def add_wrapper_logic(self, cursor):
        target_ns = self.mapping[cursor.spelling]
        pre, suf = generate_namespace_wrappers_bytes(target_ns)
        start, end = cursor.extent.start.offset, cursor.extent.end.offset
        
        # 寻找分号
        limit = min(end + 200, len(self.content_bytes))
        scan_pos = end
        while scan_pos < limit:
            if self.content_bytes[scan_pos] == 59: # ';'
                scan_pos += 1
                break
            elif self.content_bytes[scan_pos] not in (9, 10, 13, 32): break
            scan_pos += 1
            
        self.replacements.append((start, 0, pre))
        self.replacements.append((scan_pos, 0, suf))

    def add_prefix_logic(self, token):
        target_ns = self.mapping[token.spelling]
        start = token.location.offset
        length = len(token.spelling.encode('utf-8'))
        new_bytes = f"{target_ns}::{token.spelling}".encode('utf-8')
        self.replacements.append((start, length, new_bytes))

    def apply_changes(self):
        if not self.replacements: return False
        self.replacements.sort(key=lambda x: x[0], reverse=True)
        
        new_data = bytearray(self.content_bytes)
        seen_offsets = set()
        for offset, length, text in self.replacements:
            if offset in seen_offsets: continue
            new_data[offset : offset + length] = text
            seen_offsets.add(offset)
            
        if new_data != self.content_bytes:
            with open(self.file_path, 'wb') as f:
                f.write(new_data)
            return True
        return False

def main():
    if len(sys.argv) < 4:
        print("Usage: python script.py <src_dir> <mapping_csv> <log_file>")
        return
    
    src_dir, mapping_csv, log_file = sys.argv[1], sys.argv[2], sys.argv[3]
    logger = setup_logging(log_file)
    
    # 1. 自动发现所有头文件路径 (解决 Standard.hpp not found)
    logger.info("Auto-detecting header directories...")
    header_args = get_all_header_dirs(src_dir)
    logger.info(f"Found {len(header_args)} include paths.")

    # 2. 加载映射表
    mapping = load_mapping(mapping_csv)
    logger.info(f"Mapping loaded: {len(mapping)} rules.")

    total, modified = 0, 0
    for root, dirs, files in os.walk(src_dir):
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        for file in files:
            if os.path.splitext(file)[1].lower() in EXTENSIONS:
                total += 1
                path = os.path.join(root, file)
                print(f"Scanned: {total} | Modified: {modified}", end='\r')
                
                try:
                    worker = FileRefactor(path, mapping, header_args)
                    if worker.process():
                        modified += 1
                        logger.info(f"[SUCCESS] {path}")
                except Exception as e:
                    logger.error(f"[ERROR] {path}: {e}")

    logger.info(f"\nFinal Result: Scanned {total}, Modified {modified}. Log: {log_file}")

if __name__ == "__main__":
    main()
