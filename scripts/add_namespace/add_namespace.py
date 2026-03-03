import os
import argparse
import sys
import re
import csv
import time
import clang.cindex
from clang.cindex import CursorKind, TranslationUnit

# ================= 配置区域 =================

# 允许处理的文件后缀
ALLOWED_EXTENSIONS = {
    '.hpp', '.hxx', '.h', '.gxx', '.lxx', 
    '.cxx', '.cpp', '.c', '.cc'
}

IGNORE_DIRS = {
    '.git', '.vs', 'build', 'out', 'bin', 'lib',
    'doc', 'adm'
}

# ===========================================

def load_namespace_mapping(csv_path, start_row=1, end_row=None):
    """读取 CSV 映射表"""
    mapping = {}
    print(f"[*] 正在读取 CSV: {csv_path}")
    try:
        with open(csv_path, 'r', encoding='utf-8-sig') as f:
            reader = csv.DictReader(f)
            if 'OldName' not in reader.fieldnames or 'NewNamespace' not in reader.fieldnames:
                print("[错误] CSV 缺少 'OldName' 或 'NewNamespace' 列")
                sys.exit(1)
            count = 0
            for i, row in enumerate(reader, start=1):
                if i < start_row: continue
                if end_row is not None and i > end_row: break
                old_name = row['OldName'].strip()
                new_ns = row['NewNamespace'].strip()
                if old_name and new_ns:
                    mapping[old_name] = new_ns
                    count += 1
            print(f"[*] 成功加载规则: {count} 条")
    except Exception as e:
        print(f"[错误] CSV 读取失败: {e}")
        sys.exit(1)
    return mapping

def find_matching_brace(content, open_brace_pos):
    """查找匹配的闭合大括号，跳过注释和字符串"""
    depth = 0
    i = open_brace_pos
    length = len(content)
    while i < length:
        c = content[i]
        # 跳过行注释
        if c == '/' and i + 1 < length and content[i + 1] == '/':
            nl = content.find('\n', i)
            i = nl if nl != -1 else length; continue
        # 跳过块注释
        if c == '/' and i + 1 < length and content[i + 1] == '*':
            end = content.find('*/', i + 2)
            i = end + 2 if end != -1 else length; continue
        # 跳过字符串
        if c == '"':
            i += 1
            while i < length:
                if content[i] == '\\': i += 2; continue
                if content[i] == '"': break
                i += 1
            i += 1; continue
        # 跳过字符
        if c == "'":
            i += 1
            while i < length:
                if content[i] == '\\': i += 2; continue
                if content[i] == "'": break
                i += 1
            i += 1; continue
        
        if c == '{': depth += 1
        elif c == '}':
            depth -= 1
            if depth == 0: return i
        i += 1
    return -1

def find_template_start(content, start_pos):
    """向前查找 template <...> 声明的起始位置"""
    i = start_pos - 1
    while i >= 0 and content[i] in ' \t\r\n': i -= 1
    if i < 0 or content[i] != '>': return start_pos 
    depth = 1; i -= 1
    while i >= 0 and depth > 0:
        if content[i] == '>': depth += 1
        elif content[i] == '<': depth -= 1
        i -= 1
    while i >= 0 and content[i] in ' \t\r\n': i -= 1
    keyword = 'template'; kw_end = i + 1; kw_start = kw_end - len(keyword)
    if kw_start >= 0 and content[kw_start:kw_end] == keyword:
        if kw_start == 0 or not (content[kw_start-1].isalnum() or content[kw_start-1] == '_'):
            return kw_start
    return start_pos

def generate_namespace_wrapper(namespace_str):
    """生成 namespace 前缀和后缀"""
    ns_for_wrap = namespace_str.lstrip(':')
    parts = ns_for_wrap.split('::')
    prefix = ' '.join(f'namespace {p} {{' for p in parts) + '\n'
    suffix = '\n' + '}' * len(parts) + f' // namespace {ns_for_wrap}\n'
    return prefix, suffix

def get_clang_tu(filepath):
    abs_path = os.path.normpath(os.path.abspath(filepath))
    try:
        index = clang.cindex.Index.create()
        tu = index.parse(abs_path, args=['-std=c++17', '-fms-compatibility'])
        return tu, abs_path
    except Exception:
        return None, None

def get_class_extents_from_tu(tu, abs_path):
    result = {}
    def walk(cursor):
        if cursor.kind == CursorKind.TRANSLATION_UNIT:
            for child in cursor.get_children(): walk(child)
            return
        loc = cursor.location
        if not loc.file or os.path.normpath(loc.file.name) != abs_path: return
        if cursor.kind in (CursorKind.CLASS_DECL, CursorKind.STRUCT_DECL, CursorKind.CLASS_TEMPLATE):
            name = cursor.spelling
            if name:
                if name not in result: result[name] = []
                result[name].append((cursor.extent.start.offset, cursor.extent.end.offset, cursor.is_definition()))
        # 优化：不进入函数体
        if cursor.kind not in (CursorKind.CXX_METHOD, CursorKind.FUNCTION_DECL, CursorKind.CONSTRUCTOR, CursorKind.DESTRUCTOR):
            for child in cursor.get_children(): walk(child)
    walk(tu.cursor)
    return result

def get_out_of_line_methods(tu, abs_path, mapping):
    methods = []
    def walk(cursor):
        if cursor.kind == CursorKind.TRANSLATION_UNIT:
            for child in cursor.get_children(): walk(child)
            return
        loc = cursor.location
        if not loc.file or os.path.normpath(loc.file.name) != abs_path: return
        kinds = (CursorKind.CXX_METHOD, CursorKind.CONSTRUCTOR, CursorKind.DESTRUCTOR, CursorKind.FUNCTION_TEMPLATE)
        if cursor.kind in kinds and cursor.is_definition():
            parent = cursor.semantic_parent
            if parent and parent.spelling in mapping:
                if cursor.lexical_parent.kind == CursorKind.TRANSLATION_UNIT:
                    methods.append({
                        'start': cursor.extent.start.offset,
                        'end': cursor.extent.end.offset,
                        'class_name': parent.spelling,
                        'ns': mapping[parent.spelling]
                    })
    walk(tu.cursor)
    methods.sort(key=lambda x: x['start'])
    return methods

def build_reference_regex(mapping):
    """
    构建匹配所有类名的正则表达式。
    包含 Negative Lookahead (?!\.hxx) 以跳过文件名。
    """
    if not mapping: return None
    sorted_keys = sorted(mapping.keys(), key=len, reverse=True)
    escaped_keys = [re.escape(k) for k in sorted_keys]
    
    # 忽略列表: hxx, hpp, cxx, cpp, h, lxx, gxx, inc, c, cc
    ignore_exts = r"hxx|hpp|cxx|cpp|h|lxx|gxx|inc|c|cc"
    
    union_pattern = '|'.join(escaped_keys)
    full_pattern = fr'\b({union_pattern})\b(?!\.({ignore_exts}))'
    
    try:
        return re.compile(full_pattern)
    except re.error as e:
        print(f"[错误] 正则表达式编译失败: {e}")
        sys.exit(1)

def process_file(filepath, ref_regex, mapping, mapping_names_set, dry_run):
    if ref_regex is None: return False
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore', newline='') as f:
            content = f.read()
    except Exception as e:
        print(f"  [错误] 无法读取 {filepath}: {e}")
        return False
    if not any(name in content for name in mapping_names_set): return False

    include_line_set = set()
    for line_idx, line in enumerate(content.split('\n')):
        if re.match(r'^\s*#\s*include', line): include_line_set.add(line_idx)

    modifications = []          
    protected_name_pos = []     
    protected_body_ranges = []  
    protected_macro_blocks = [] 

    tu, abs_path = get_clang_tu(filepath)
    clang_extents = get_class_extents_from_tu(tu, abs_path) if tu else {}

    # ==== Phase 1: 类定义包裹 ====
    class_keyword_regex = re.compile(r'\b(class|struct)\s+')
    for kw_match in class_keyword_regex.finditer(content):
        line_no = content[:kw_match.start()].count('\n')
        if line_no in include_line_set: continue
        
        prefix_check = content[max(0, kw_match.start()-10):kw_match.start()]
        if 'friend' in prefix_check: continue

        pos = kw_match.end()
        match_name = re.match(r'\s*([A-Za-z0-9_]+)', content[pos:])
        if not match_name: continue
        class_name = match_name.group(1)
        name_start = pos + match_name.start(1); name_end = pos + match_name.end(1)

        if class_name not in mapping: continue
        ns_str = mapping[class_name]
        
        found_extent = None
        if class_name in clang_extents:
            for (cs, ce, cis_def) in clang_extents[class_name]:
                if ce >= name_end and cs <= name_start: 
                    found_extent = (cs, ce, cis_def); break
        
        if found_extent and found_extent[2]: 
            wrap_start = find_template_start(content, found_extent[0])
            end_scan = found_extent[1]
            while end_scan < len(content) and content[end_scan] in ' \t\r\n': end_scan += 1
            wrap_end = end_scan + 1 if (end_scan < len(content) and content[end_scan] == ';') else found_extent[1]

            prefix, suffix = generate_namespace_wrapper(ns_str)
            modifications.append((wrap_start, 0, prefix))
            modifications.append((wrap_end, 0, suffix))
            protected_name_pos.append((name_start, name_end))
            
            brace_pos = content.find('{', name_end)
            if brace_pos != -1 and brace_pos < wrap_end:
                close_pos = find_matching_brace(content, brace_pos)
                if close_pos != -1: protected_body_ranges.append((brace_pos, close_pos, class_name))

    # ==== Phase 1.5: 函数实现包裹 ====
    if tu:
        method_defs = get_out_of_line_methods(tu, abs_path, mapping)
        if method_defs:
            groups = []
            current_group = [method_defs[0]]
            for i in range(1, len(method_defs)):
                curr = method_defs[i]; prev = current_group[-1]
                gap_text = content[prev['end']:curr['start']]
                if curr['ns'] == prev['ns'] and '#include' not in gap_text and 'namespace' not in gap_text:
                    current_group.append(curr)
                else:
                    groups.append(current_group); current_group = [curr]
            groups.append(current_group)
            
            for grp in groups:
                ns_str = grp[0]['ns']
                first_start = grp[0]['start']
                block_start = find_template_start(content, first_start)
                block_end = grp[-1]['end']
                while block_end < len(content) and content[block_end] in ' \t\r\n': block_end += 1
                
                prefix, suffix = generate_namespace_wrapper(ns_str)
                modifications.append((block_start, 0, prefix))
                modifications.append((block_end, 0, suffix))
                
                # 保护函数签名中的 ClassName::
                for method in grp:
                    cn = method['class_name']
                    m_len = method['end'] - method['start']
                    scan_len = min(m_len, 500) 
                    header_text = content[method['start']:method['start']+scan_len]
                    brace_idx = header_text.find('{')
                    if brace_idx != -1: header_text = header_text[:brace_idx]
                    
                    cn_regex = re.compile(re.escape(cn) + r'\s*::')
                    for match in cn_regex.finditer(header_text):
                        abs_s = method['start'] + match.start()
                        protected_name_pos.append((abs_s, abs_s + len(cn)))
                        
                    body_start = method['start'] + (brace_idx if brace_idx!=-1 else 0)
                    body_end = method['end']
                    protected_body_ranges.append((body_start, body_end, cn))

    # ==== Phase 1.8: OCCT 宏处理 (恢复原始逻辑：支持 3 行模式包裹) ====
    # Group 1: Alias, Group 2: Target, Group 3: Include Line (optional)
    occt_macro_regex = re.compile(
        r'^[ \t]*#[ \t]*define[ \t]+([A-Za-z0-9_]+)[ \t]+([A-Za-z0-9_]+)[ \t]*(?://.*?)?\r?\n'
        r'(?:[ \t]*(?://.*?)?\r?\n)*'
        r'[ \t]*#[ \t]*define[ \t]+\1_hxx[ \t]+[<"][ \t]*\2\.[a-zA-Z0-9_]+[ \t]*[>"][ \t]*(?://.*?)?'
        r'((?:\r?\n(?:[ \t]*(?://.*?)?\r?\n)*[ \t]*#[ \t]*include[ \t]+[<"][ \t]*\1\.[a-zA-Z0-9_]+[ \t]*[>"][ \t]*(?://.*?)?))?',
        re.MULTILINE
    )

    for match in occt_macro_regex.finditer(content):
        class_name = match.group(2) # Target Class
        has_include = bool(match.group(3)) # Capture Group 3

        if class_name in mapping:
            namespace_str = mapping[class_name]

            if has_include:
                # === 策略 A: 3行模式 (LProp_SLProps) ===
                # 动作: 添加 namespace 包裹，保护整个块
                wrap_start = match.start()
                wrap_end = match.end()
                # 调整结束位置包含换行
                while wrap_end < len(content) and content[wrap_end] not in '\r\n': wrap_end += 1
                if wrap_end < len(content) and content[wrap_end] == '\r': wrap_end += 1
                if wrap_end < len(content) and content[wrap_end] == '\n': wrap_end += 1

                prefix, suffix = generate_namespace_wrapper(namespace_str)
                modifications.append((wrap_start, 0, prefix))
                modifications.append((wrap_end, 0, suffix))
                protected_macro_blocks.append((wrap_start, wrap_end))
            
            else:
                # === 策略 B: 2行模式 (Surface, Tool) ===
                # 动作: 给第1行加前缀，保护第2行文件名
                line1_cls_start = match.start(2)
                line1_cls_end = match.end(2)
                modifications.append((line1_cls_start, 0, f"::{namespace_str}::"))
                protected_name_pos.append((line1_cls_start, line1_cls_end))

                # 保护第2行 (文件名部分)
                search_start = match.end(2) 
                search_end = match.end()
                line2_cls_rel = content[search_start:search_end].find(class_name)
                if line2_cls_rel != -1:
                    line2_cls_start = search_start + line2_cls_rel
                    line2_cls_end = line2_cls_start + len(class_name)
                    protected_macro_blocks.append((line2_cls_start, line2_cls_end))

    # ==== Phase 2: 引用替换 ====
    for ref_match in ref_regex.finditer(content):
        name = ref_match.group(1)
        name_start = ref_match.start(1); name_end = ref_match.end(1)
        
        line_no = content[:name_start].count('\n')
        if line_no in include_line_set: continue
        if any(s <= name_start and name_end <= e for s, e in protected_name_pos): continue
        if any(s <= name_start and name_end <= e for s, e in protected_macro_blocks): continue
        if name_start >= 2 and content[name_start-2:name_start] == '::': continue
        
        target_ns = mapping[name]
        is_same_ns = False
        for (bs, be, enclosing_cls) in protected_body_ranges:
            if bs <= name_start <= be:
                enc_ns = mapping.get(enclosing_cls)
                if enc_ns == target_ns: is_same_ns = True; break
        if is_same_ns: continue
        
        new_text = f'::{target_ns}::{name}'
        modifications.append((name_start, name_end - name_start, new_text))

    if not modifications: return False

    modifications.sort(key=lambda x: (x[0], x[2]), reverse=True)
    new_content = content
    seen_offsets = set()
    total_mod = 0
    for offset, length, text in modifications:
        if length > 0:
            conflict = False
            for i in range(offset, offset+length):
                if i in seen_offsets: conflict = True; break
            if conflict: continue
            for i in range(offset, offset+length): seen_offsets.add(i)
        new_content = new_content[:offset] + text + new_content[offset+length:]
        total_mod += 1

    if new_content == content: return False
    if not dry_run:
        with open(filepath, 'w', encoding='utf-8', newline='') as f: f.write(new_content)
        print(f"  [修改] {os.path.basename(filepath)} ({total_mod} 处)")
    else:
        print(f"  [预演] {os.path.basename(filepath)} ({total_mod} 处)")
    return True

# =========================================================
#  Main Logic (Restored)
# =========================================================
def main(root_dir, csv_path, start_row, end_row, dry_run=True):
    start_time = time.time()
    mapping = load_namespace_mapping(csv_path, start_row, end_row)
    if not mapping:
        print("停止执行：没有规则可供处理。")
        return

    ref_regex = build_reference_regex(mapping)
    mapping_names_set = set(mapping.keys())

    print(f"[*] 扫描目录: {root_dir}")
    if dry_run:
        print("[!] 模式: 预演 (Dry Run) - 不会修改文件")
    else:
        print("[!] 模式: 执行 (Run) - 将修改文件")
    print("-" * 60)

    modified_files_count = 0
    scanned_files_count = 0

    for dirpath, dirnames, filenames in os.walk(root_dir):
        dirnames[:] = [d for d in dirnames if d not in IGNORE_DIRS]

        path_parts = dirpath.split(os.sep)
        is_in_tests_or_data = ('tests' in path_parts) or ('data' in path_parts)
        is_in_src = 'src' in path_parts

        for filename in filenames:
            file_path = os.path.join(dirpath, filename)
            _, ext = os.path.splitext(filename)
            ext = ext.lower()

            is_allowed_ext = ext in ALLOWED_EXTENSIONS
            # 特殊规则：tests/data/src 目录下无扩展名的文件也可能需要处理
            is_special_file = (is_in_tests_or_data or is_in_src) and (ext == '')

            if not (is_allowed_ext or is_special_file):
                continue

            scanned_files_count += 1
            if process_file(file_path, ref_regex, mapping, mapping_names_set, dry_run):
                modified_files_count += 1

    end_time = time.time()
    duration = end_time - start_time

    print("-" * 60)
    print(f"处理完成。")
    print(f"耗时: {duration:.2f} 秒")
    print(f"扫描文件: {scanned_files_count}")
    print(f"涉及修改: {modified_files_count}")

    if dry_run:
        print("\n提示: 这里的输出仅为预演。请添加 --run 参数来执行实际修改。")
    else:
        print("\n提示: 修改已完成。")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="OCCT Namespace Adder Final")
    parser.add_argument("dir", help="源码目录")
    parser.add_argument("csv_file", help="映射表CSV文件路径")
    parser.add_argument("--start_row", type=int, default=1, help="CSV起始行号(包含)")
    parser.add_argument("--end_row", type=int, default=None, help="CSV结束行号(包含)")
    parser.add_argument("--run", action="store_true", help="执行实际修改 (默认仅预演)")

    args = parser.parse_args()

    if not os.path.exists(args.dir):
        print(f"目录不存在: {args.dir}")
        sys.exit(1)
    if not os.path.exists(args.csv_file):
        print(f"CSV文件不存在: {args.csv_file}")
        sys.exit(1)

    main(args.dir, args.csv_file, args.start_row, args.end_row, dry_run=not args.run)
