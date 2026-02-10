import sys
import os
import csv
import logging
import multiprocessing
from concurrent.futures import ProcessPoolExecutor
import clang.cindex
from clang.cindex import CursorKind, TokenKind, TranslationUnit

# ================= 配置区域 =================
# 如果需要，取消下面一行的注释并指向你的 LLVM bin 目录
# clang.cindex.Config.set_library_path(r'C:\Program Files\LLVM\bin')
EXTENSIONS = {'.cxx', '.hpp', '.cpp', '.h', '.cc', '.c'}
# ===========================================

def load_mapping(csv_file):
    mapping = {}
    with open(csv_file, 'r', encoding='utf-8') as f:
        reader = csv.reader(f)
        for row in reader:
            if len(row) >= 2:
                cls, ns = row[0].strip(), row[1].strip()
                if cls and ns: mapping[cls] = ns
    return mapping

def get_all_header_dirs(root_dir):
    header_dirs = set()
    for root, _, files in os.walk(root_dir):
        for file in files:
            if file.lower().endswith(('.h', '.hpp', '.hxx')):
                header_dirs.add(os.path.abspath(root))
                break
    return [f"-I{d}" for d in header_dirs]

def generate_namespace_wrappers_bytes(namespace_str):
    parts = namespace_str.split('::')
    prefix = ("\n" + " ".join([f"namespace {p} {{" for p in parts]) + "\n").encode('utf-8')
    suffix = ("\n" + " ".join(["}" for _ in parts]) + f" // namespace {namespace_str}\n").encode('utf-8')
    return prefix, suffix

class RefactorWorker:
    def __init__(self, mapping, header_args):
        self.mapping = mapping
        self.header_args = header_args
        self.mapping_keys_bytes = [k.encode('utf-8') for k in mapping.keys()]

    def process_file(self, file_path):
        abs_path = os.path.normpath(os.path.abspath(file_path))
        
        try:
            with open(abs_path, 'rb') as f:
                content = f.read()
            if not any(key in content for key in self.mapping_keys_bytes):
                return False, file_path
        except: return False, file_path

        index = clang.cindex.Index.create()
        
        # 只屏蔽 #include 行，不屏蔽宏定义/调用行
        skip_lines = set()
        lines = content.split(b'\n')
        for i, line in enumerate(lines):
            if line.strip().startswith(b'#include'):
                skip_lines.add(i + 1)

        try:
            # 必须包含 DETAILED_PROCESSING_RECORD 才能在 Token 中处理宏
            tu = index.parse(abs_path, 
                             args=['-std=c++17', '-fms-compatibility'] + self.header_args,
                             options=TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
        except: return False, file_path

        replacements = []
        protected_offsets = []

        def walk(cursor):
            # 特殊处理 TranslationUnit：它通常没有文件信息，或者是整个单元的根，需要遍历其子节点
            if cursor.kind == CursorKind.TRANSLATION_UNIT:
                for child in cursor.get_children():
                    walk(child)
                return

            # 对于其他节点，检查是否在当前文件内
            # 如果不在当前文件，直接剪枝（不再遍历子节点）
            if not cursor.location.file or os.path.normpath(cursor.location.file.name) != abs_path:
                return
            
            # --- 以下逻辑仅对当前文件内的节点执行 ---

            # 记录字符串位置，防止修改字符串内容
            if cursor.kind == CursorKind.STRING_LITERAL:
                protected_offsets.append((cursor.extent.start.offset, cursor.extent.end.offset))

            # 处理类/结构体/类模板的声明
            if cursor.kind in [CursorKind.CLASS_DECL, CursorKind.STRUCT_DECL, CursorKind.CLASS_TEMPLATE] and cursor.spelling in self.mapping:
                # 必须同时满足：在顶层（TU或Namespace）
                # 注意：无论是定义（class A {...};）还是前向声明（class A;），只要在顶层都需要包裹
                is_definition = cursor.is_definition()
                parent = cursor.lexical_parent
                is_toplevel = parent and parent.kind in [CursorKind.TRANSLATION_UNIT, CursorKind.NAMESPACE]
                
                if is_toplevel:
                    # 记录范围，防止 Token 扫描阶段在类定义处重复加前缀
                    protected_offsets.append((cursor.extent.start.offset, cursor.extent.end.offset))
                    
                    target_ns = self.mapping[cursor.spelling]
                    pre, suf = generate_namespace_wrappers_bytes(target_ns)
                    
                    # 寻找末尾的分号
                    end_off = cursor.extent.end.offset
                    scan_pos = end_off
                    limit = min(end_off + 200, len(content))
                    found_semicolon = False
                    while scan_pos < limit:
                        if content[scan_pos] == 59: # ';'
                            scan_pos += 1
                            found_semicolon = True
                            break
                        elif content[scan_pos] not in (9, 10, 13, 32): # 非空白字符
                            break
                        scan_pos += 1
                    
                    replacements.append((cursor.extent.start.offset, 0, pre))
                    replacements.append((scan_pos if found_semicolon else end_off, 0, suf))
            
            # 继续遍历子节点（仅限当前文件内的节点）
            for child in cursor.get_children():
                walk(child)

        walk(tu.cursor)

        # 2. Token 扫描：处理宏参数和引用
        prev_t = None
        for t in tu.get_tokens(extent=tu.cursor.extent):
            loc = t.location
            # 这里的 loc 已经是物理文件位置
            if not loc.file or os.path.normpath(loc.file.name) != abs_path:
                continue
            
            # 跳过 #include 行
            if loc.line in skip_lines: continue
            
            # 跳过字符串内部和已处理的类定义头部
            if any(s <= loc.offset < e for s, e in protected_offsets): continue
            
            if t.kind == TokenKind.IDENTIFIER and t.spelling in self.mapping:
                # 检查是否已经是 NS::Class 或析构函数 ~Class 或成员调用 .Class
                is_qualified = False
                if prev_t:
                    if prev_t.spelling in ['::', '~', '.', '->']:
                        is_qualified = True
                
                if not is_qualified:
                    ns_prefix = self.mapping[t.spelling]
                    new_text = f"{ns_prefix}::{t.spelling}".encode('utf-8')
                    replacements.append((loc.offset, len(t.spelling.encode('utf-8')), new_text))
            
            prev_t = t

        if not replacements: return False, file_path
        
        # 3. 应用修改
        replacements.sort(key=lambda x: x[0], reverse=True)
        new_data = bytearray(content)
        seen_offsets = set()
        for off, leng, txt in replacements:
            if off in seen_offsets: continue
            new_data[off:off+leng] = txt
            seen_offsets.add(off)
        
        with open(abs_path, 'wb') as f:
            f.write(new_data)
        return True, file_path

def global_worker(task):
    file_path, mapping, header_args = task
    worker = RefactorWorker(mapping, header_args)
    return worker.process_file(file_path)

def main():
    if len(sys.argv) < 4:
        print("Usage: python add_namespace.py <src_dir> <csv_file> <log_file>")
        return
    src_dir, csv_file, log_file = sys.argv[1], sys.argv[2], sys.argv[3]
    
    logging.basicConfig(filename=log_file, level=logging.WARNING, format='%(asctime)s %(message)s')
    mapping = load_mapping(csv_file)
    header_args = get_all_header_dirs(src_dir)

    tasks = []
    for root, _, files in os.walk(src_dir):
        for file in files:
            if os.path.splitext(file)[1].lower() in EXTENSIONS:
                tasks.append((os.path.join(root, file), mapping, header_args))

    print(f"Total tasks: {len(tasks)}. Processing...")
    
    mod_count = 0
    with ProcessPoolExecutor() as executor:
        results = executor.map(global_worker, tasks)
        for i, (modified, path) in enumerate(results):
            if modified:
                mod_count += 1
                logging.info(f"[MODIFIED] {path}")
            if i % 10 == 0:
                print(f"Progress: {i}/{len(tasks)} | Modified: {mod_count}", end='\r')

    print(f"\nCompleted. Modified {mod_count} files.")

if __name__ == "__main__":
    main()
