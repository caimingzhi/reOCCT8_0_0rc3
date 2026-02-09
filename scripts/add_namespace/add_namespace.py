import sys
import os
import csv
import logging
import multiprocessing
from concurrent.futures import ProcessPoolExecutor
import clang.cindex
from clang.cindex import CursorKind, TokenKind, TranslationUnit

# ================= 配置区域 =================
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
            if file.lower().endswith(('.h', '.hpp', '.hxx', '.gxx')):
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
        abs_path = os.path.abspath(file_path).lower()
        
        # 1. 快速预筛选 (Fast Triage)
        try:
            with open(file_path, 'rb') as f:
                content = f.read()
            if not any(key in content for key in self.mapping_keys_bytes):
                return False, file_path
        except: return False, file_path

        index = clang.cindex.Index.create()
        
        # 标记预处理行 (用于行盾牌)
        protected_lines = set()
        lines = content.split(b'\n')
        is_ml_pp = False
        for i, line in enumerate(lines):
            s = line.strip()
            if s.startswith(b'#') or is_ml_pp:
                protected_lines.add(i + 1)
                is_ml_pp = s.endswith(b'\\')
            else: is_ml_pp = False

        try:
            # 增加宏兼容性参数
            base_args = [
                '-std=c++17', 
                '-D_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH', 
                '-fms-compatibility',
                '-fms-extensions',
                '-Wno-pragma-once-outside-header'
            ]
            tu = index.parse(file_path, 
                             args=base_args + self.header_args,
                             options=TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD | 
                                     TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)
        except: return False, file_path

        replacements = []
        protected_offsets = []

        # --- AST 扫描 ---
        def walk(cursor):
            # 获取物理位置
            loc = cursor.location
            if loc.file:
                # 使用 spelling_location.file 获取物理写入的文件
                spell_file = loc.get_spelling_location().file
                if spell_file and os.path.abspath(spell_file.name).lower() != abs_path:
                    return

            if cursor.kind == CursorKind.STRING_LITERAL:
                protected_offsets.append((cursor.extent.start.offset, cursor.extent.end.offset))
            
            if cursor.kind in [CursorKind.CLASS_DECL, CursorKind.STRUCT_DECL] and cursor.spelling in self.mapping:
                if cursor.is_definition() or (cursor.lexical_parent and cursor.lexical_parent.kind in [CursorKind.TRANSLATION_UNIT, CursorKind.NAMESPACE]):
                    protected_offsets.append((cursor.extent.start.offset, cursor.extent.end.offset))
                    target_ns = self.mapping[cursor.spelling]
                    pre, suf = generate_namespace_wrappers_bytes(target_ns)
                    
                    start_off = cursor.extent.start.offset
                    end_off = cursor.extent.end.offset
                    
                    # 查找分号逻辑
                    scan_pos = end_off
                    limit = min(end_off + 200, len(content))
                    while scan_pos < limit:
                        if content[scan_pos] == 59: # ';'
                            scan_pos += 1
                            break
                        elif content[scan_pos] not in (9, 10, 13, 32): break
                        scan_pos += 1
                    replacements.append((start_off, 0, pre))
                    replacements.append((scan_pos, 0, suf))
            
            for child in cursor.get_children(): walk(child)

        walk(tu.cursor)

        # --- Token 扫描 (处理宏参数引用) ---
        prev = None
        for t in tu.cursor.get_tokens():
            # 【关键修改】使用 get_spelling_location() 穿透宏展开
            spell_loc = t.location.get_spelling_location()
            if not spell_loc.file: continue
            
            if os.path.abspath(spell_loc.file.name).lower() != abs_path:
                continue

            if spell_loc.line in protected_lines: 
                prev = t
                continue
            
            # 检查偏移量是否在保护区
            if any(s <= t.location.offset < e for s, e in protected_offsets):
                prev = t
                continue

            if t.kind == TokenKind.IDENTIFIER and t.spelling in self.mapping:
                # 排除已经有作用域的情况或析构函数
                if not (prev and prev.spelling in ['::', '~']):
                    new_bytes = f"{self.mapping[t.spelling]}::{t.spelling}".encode('utf-8')
                    replacements.append((t.location.offset, len(t.spelling.encode('utf-8')), new_bytes))
            prev = t

        if not replacements: return False, file_path
        
        # 应用修改
        replacements.sort(key=lambda x: x[0], reverse=True)
        new_data = bytearray(content)
        seen_offsets = set()
        for off, leng, txt in replacements:
            if off in seen_offsets: continue
            new_data[off:off+leng] = txt
            seen_offsets.add(off)
        
        try:
            with open(file_path, 'wb') as f:
                f.write(new_data)
            return True, file_path
        except: return False, file_path

def global_worker(task):
    file_path, mapping, header_args = task
    try:
        worker = RefactorWorker(mapping, header_args)
        return worker.process_file(file_path)
    except: return False, file_path

def main():
    if len(sys.argv) < 4:
        print("Usage: python script.py <src_dir> <mapping_csv> <log_file>")
        return
    src_dir, csv_file, log_file = sys.argv[1], sys.argv[2], sys.argv[3]
    
    logging.basicConfig(filename=log_file, level=logging.WARNING, format='%(asctime)s %(message)s')
    mapping = load_mapping(csv_file)
    header_args = get_all_header_dirs(src_dir)

    tasks = []
    for root, _, files in os.walk(src_dir):
        dirs = [d for d in _ if not d.startswith('.')] # 排除隐藏目录
        for file in files:
            if os.path.splitext(file)[1].lower() in EXTENSIONS:
                tasks.append((os.path.join(root, file), mapping, header_args))

    print(f"Detected {multiprocessing.cpu_count()} cores. Processing {len(tasks)} files...")
    
    mod_count = 0
    with ProcessPoolExecutor() as executor:
        results = executor.map(global_worker, tasks)
        for i, (modified, path) in enumerate(results):
            if modified:
                mod_count += 1
                logging.info(f"[MODIFIED] {path}")
            if i % 20 == 0:
                print(f"Progress: {i}/{len(tasks)} | Modified: {mod_count}", end='\r')

    print(f"\nCompleted. Total modified: {mod_count}")

if __name__ == "__main__":
    # Windows 多进程必须在 if __name__ == "__main__": 下
    main()
