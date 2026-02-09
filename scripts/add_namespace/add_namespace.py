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
        abs_path = os.path.abspath(file_path)
        
        # 优化 1: 快速预筛选 (Fast Triage)
        # 如果文件二进制内容里连类名字符串都没有，直接跳过，不调用 Clang
        try:
            with open(abs_path, 'rb') as f:
                content = f.read()
            if not any(key in content for key in self.mapping_keys_bytes):
                return False, file_path
        except: return False, file_path

        # 优化 2: 这里的 Index 在每个进程内初始化一次
        index = clang.cindex.Index.create()
        
        # 标记预处理行
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
            # 优化 3: 使用 PARSE_SKIP_FUNCTION_BODIES
            # 既然是改类定义和类型前缀，函数体内部的局部变量通常不需要 AST 深度解析
            # 如果你的引用出现在函数内部，这个标志可能会漏掉，
            # 但配合我们的 Token 扫描（Token 扫描是不受此标志影响的），可以兼顾速度与准度。
            tu = index.parse(abs_path, 
                             args=['-std=c++17', '-D_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH', '-fms-compatibility'] + self.header_args,
                             options=TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD | 
                                     TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)
        except: return False, file_path

        replacements = []
        protected_offsets = []

        # AST 扫描 (处理包裹)
        def walk(cursor):
            if cursor.location.file and os.path.abspath(cursor.location.file.name) != abs_path: return
            if cursor.kind == CursorKind.STRING_LITERAL:
                protected_offsets.append((cursor.extent.start.offset, cursor.extent.end.offset))
            if cursor.kind in [CursorKind.CLASS_DECL, CursorKind.STRUCT_DECL] and cursor.spelling in self.mapping:
                if cursor.is_definition() or (cursor.lexical_parent and cursor.lexical_parent.kind in [CursorKind.TRANSLATION_UNIT, CursorKind.NAMESPACE]):
                    protected_offsets.append((cursor.extent.start.offset, cursor.extent.end.offset))
                    # 查找分号并记录替换
                    target_ns = self.mapping[cursor.spelling]
                    pre, suf = generate_namespace_wrappers_bytes(target_ns)
                    end_off = cursor.extent.end.offset
                    scan_pos = end_off
                    limit = min(end_off + 200, len(content))
                    while scan_pos < limit:
                        if content[scan_pos] == 59: { scan_pos := scan_pos + 1 }; break
                        elif content[scan_pos] not in (9, 10, 13, 32): break
                        scan_pos += 1
                    replacements.append((cursor.extent.start.offset, 0, pre))
                    replacements.append((scan_pos, 0, suf))
            for child in cursor.get_children(): walk(child)

        walk(tu.cursor)

        # Token 扫描 (处理引用)
        prev = None
        for t in tu.cursor.get_tokens():
            if t.location.file and os.path.abspath(t.location.file.name) == abs_path:
                if t.location.line in protected_lines: continue
                if any(s <= t.location.offset < e for s, e in protected_offsets): continue
                if t.kind == TokenKind.IDENTIFIER and t.spelling in self.mapping:
                    if not (prev and prev.spelling in ['::', '~']):
                        new_bytes = f"{self.mapping[t.spelling]}::{t.spelling}".encode('utf-8')
                        replacements.append((t.location.offset, len(t.spelling.encode('utf-8')), new_bytes))
                prev = t

        if not replacements: return False, file_path
        
        # 应用修改
        replacements.sort(key=lambda x: x[0], reverse=True)
        new_data = bytearray(content)
        seen = set()
        for off, leng, txt in replacements:
            if off in seen: continue
            new_data[off:off+leng] = txt
            seen.add(off)
        
        with open(abs_path, 'wb') as f: f.write(new_data)
        return True, file_path

# 多进程包装函数
def global_worker(task):
    file_path, mapping, header_args = task
    worker = RefactorWorker(mapping, header_args)
    return worker.process_file(file_path)

def main():
    if len(sys.argv) < 4: return
    src_dir, csv_file, log_file = sys.argv[1], sys.argv[2], sys.argv[3]
    
    logging.basicConfig(filename=log_file, level=logging.DEBUG, format='%(asctime)s %(message)s')
    mapping = load_mapping(csv_file)
    header_args = get_all_header_dirs(src_dir)

    tasks = []
    for root, _, files in os.walk(src_dir):
        for file in files:
            if os.path.splitext(file)[1].lower() in EXTENSIONS:
                tasks.append((os.path.join(root, file), mapping, header_args))

    print(f"Total tasks: {len(tasks)}. Processing with {multiprocessing.cpu_count()} cores...")
    
    mod_count = 0
    # 优化 4: 使用进程池
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
