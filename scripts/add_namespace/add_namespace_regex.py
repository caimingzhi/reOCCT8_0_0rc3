import os
import argparse
import sys
import re
import csv
import time
import clang.cindex
from clang.cindex import CursorKind, TranslationUnit

# ================= 配置区域 =================

ALLOWED_EXTENSIONS = {
    '.hpp', '.cxx', '.cpp', '.c', '.h'
}

IGNORE_DIRS = {
    '.git', '.vs', 'build', 'out', 'bin', 'lib',
    'doc', 'adm'
}

# ===========================================


def load_namespace_mapping(csv_path, start_row=1, end_row=None):
    """
    读取CSV文件，返回 {OldName: NewNamespace} 映射字典。
    """
    mapping = {}
    print(f"[*] 正在读取 CSV: {csv_path}")
    print(f"[*] 目标行范围: {start_row} 到 {end_row if end_row else '末尾'}")

    try:
        with open(csv_path, 'r', encoding='utf-8-sig') as f:
            reader = csv.DictReader(f)

            if 'OldName' not in reader.fieldnames or \
               'NewNamespace' not in reader.fieldnames:
                print("[错误] CSV 文件缺少必要的列头: 'OldName' 或 'NewNamespace'")
                sys.exit(1)

            count_loaded = 0
            for i, row in enumerate(reader, start=1):
                if i < start_row:
                    continue
                if end_row is not None and i > end_row:
                    break

                old_name = row['OldName'].strip()
                new_ns = row['NewNamespace'].strip()

                if old_name and new_ns:
                    mapping[old_name] = new_ns
                    count_loaded += 1

    except Exception as e:
        print(f"[错误] 读取 CSV 失败: {e}")
        sys.exit(1)

    print(f"[*] 成功加载规则: {count_loaded} 条")
    return mapping


def find_matching_brace(content, open_brace_pos):
    """
    从 open_brace_pos 位置的 '{' 开始，找到匹配的 '}'。
    跳过字符串字面量和注释。
    返回 '}' 的位置索引，找不到返回 -1。
    """
    depth = 0
    i = open_brace_pos
    length = len(content)

    while i < length:
        c = content[i]

        # 行注释 //
        if c == '/' and i + 1 < length and content[i + 1] == '/':
            nl = content.find('\n', i)
            if nl == -1:
                return -1
            i = nl + 1
            continue

        # 块注释 /* ... */
        if c == '/' and i + 1 < length and content[i + 1] == '*':
            end = content.find('*/', i + 2)
            if end == -1:
                return -1
            i = end + 2
            continue

        # 字符串字面量 "..."
        if c == '"':
            i += 1
            while i < length:
                if content[i] == '\\':
                    i += 2
                    continue
                if content[i] == '"':
                    break
                i += 1
            i += 1
            continue

        # 字符字面量 '...'
        if c == "'":
            i += 1
            while i < length:
                if content[i] == '\\':
                    i += 2
                    continue
                if content[i] == "'":
                    break
                i += 1
            i += 1
            continue

        # 大括号计数
        if c == '{':
            depth += 1
        elif c == '}':
            depth -= 1
            if depth == 0:
                return i

        i += 1

    return -1


def find_template_start(content, class_keyword_pos):
    """
    从 class/struct 关键字位置往回查找 template<...>，
    如果找到，返回 template 的起始位置；否则返回 class_keyword_pos。
    """
    i = class_keyword_pos - 1

    # 跳过空白
    while i >= 0 and content[i] in ' \t\r\n':
        i -= 1

    if i < 0 or content[i] != '>':
        return class_keyword_pos

    # 找匹配的 '<'
    depth = 1
    i -= 1
    while i >= 0 and depth > 0:
        if content[i] == '>':
            depth += 1
        elif content[i] == '<':
            depth -= 1
        i -= 1

    # 跳过空白
    while i >= 0 and content[i] in ' \t\r\n':
        i -= 1

    # 检查是否是 'template' 关键字
    keyword = 'template'
    end_pos = i + 1
    start_pos = end_pos - len(keyword)
    if start_pos >= 0 and content[start_pos:end_pos] == keyword:
        if start_pos == 0 or not (content[start_pos - 1].isalnum() or content[start_pos - 1] == '_'):
            return start_pos

    return class_keyword_pos


def generate_namespace_wrapper(namespace_str):
    """
    生成 namespace 包裹的前缀和后缀。
    例如 'visual::interactive' →
      前缀: 'namespace visual { namespace interactive {\n'
      后缀: '\n}} // namespace visual::interactive\n'
    """
    parts = namespace_str.split('::')
    prefix = ' '.join(f'namespace {p} {{' for p in parts) + '\n'
    suffix = '\n' + '}' * len(parts) + f' // namespace {namespace_str}\n'
    return prefix, suffix


def get_class_extents_from_clang(filepath):
    """
    使用 clang 解析文件，返回所有顶层 class/struct 声明的范围信息。
    返回: { class_name: [(extent_start_offset, extent_end_offset, is_definition), ...] }
    """
    result = {}
    abs_path = os.path.normpath(os.path.abspath(filepath))

    try:
        index = clang.cindex.Index.create()
        tu = index.parse(abs_path,
                         args=['-std=c++17', '-fms-compatibility'],
                         options=TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)
    except Exception:
        return result

    def walk(cursor):
        if cursor.kind == CursorKind.TRANSLATION_UNIT:
            for child in cursor.get_children():
                walk(child)
            return

        loc = cursor.location
        if not loc.file:
            return
        if os.path.normpath(loc.file.name) != abs_path:
            return

        if cursor.kind in (CursorKind.CLASS_DECL, CursorKind.STRUCT_DECL, CursorKind.CLASS_TEMPLATE):
            name = cursor.spelling
            if name:
                start_off = cursor.extent.start.offset
                end_off = cursor.extent.end.offset
                is_def = cursor.is_definition()
                if name not in result:
                    result[name] = []
                result[name].append((start_off, end_off, is_def))

        for child in cursor.get_children():
            walk(child)

    walk(tu.cursor)
    return result


def build_reference_regex(mapping):
    """
    构建匹配所有类名的正则表达式（同 content_refactor 方式）。
    按长度降序排列，确保长词优先匹配。
    """
    if not mapping:
        return None

    sorted_keys = sorted(mapping.keys(), key=len, reverse=True)
    escaped_keys = [re.escape(k) for k in sorted_keys]
    union_pattern = '|'.join(escaped_keys)
    full_pattern = r'\b(' + union_pattern + r')\b(?!\.(?:hxx|cxx))'

    try:
        return re.compile(full_pattern)
    except re.error as e:
        print(f"[错误] 正则表达式编译失败: {e}")
        sys.exit(1)


def process_file(filepath, ref_regex, mapping, mapping_names_set, dry_run):
    """
    处理单个文件：
    - 阶段1: 扫描 class/struct 声明/定义，添加 namespace 包裹
    - 阶段2: 替换其他引用，添加 namespace 前缀
    """
    if ref_regex is None:
        return False

    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore', newline='') as f:
            content = f.read()
    except Exception as e:
        print(f"  [错误] 无法读取 {filepath}: {e}")
        return False

    # 快速检查：文件中是否包含任何待处理的类名
    if not any(name in content for name in mapping_names_set):
        return False

    # 标记 #include 行号（用于跳过）
    include_line_set = set()
    for line_idx, line in enumerate(content.split('\n')):
        if re.match(r'^\s*#\s*include', line):
            include_line_set.add(line_idx)

    modifications = []          # (offset, remove_length, insert_text)
    protected_name_pos = []     # (start, end) — class 声明处的类名位置
    protected_body_ranges = []  # (start, end, class_name) — class body 范围

    # ================ 阶段1: class/struct 声明扫描 ================

    # 使用 clang 获取 class 声明的精确范围（含 template）
    clang_extents = get_class_extents_from_clang(filepath)

    class_keyword_regex = re.compile(r'\b(class|struct)\s+')

    for kw_match in class_keyword_regex.finditer(content):
        # 检查是否在 #include 行
        line_no = content[:kw_match.start()].count('\n')
        if line_no in include_line_set:
            continue

        # 检查是否是 friend class（用前缀形式，不包裹）
        friend_check_pos = kw_match.start() - 1
        while friend_check_pos >= 0 and content[friend_check_pos] in ' \t':
            friend_check_pos -= 1
        is_friend = False
        if friend_check_pos >= 5:
            candidate = content[friend_check_pos - 5:friend_check_pos + 1]
            if candidate == 'friend':
                # 确认 friend 前面是单词边界
                before_friend = friend_check_pos - 5 - 1
                if before_friend < 0 or not (content[before_friend].isalnum() or content[before_friend] == '_'):
                    is_friend = True

        # 提取 class/struct 后面的标识符序列
        pos = kw_match.end()
        words = []
        word_positions = []

        while pos < len(content):
            # 跳过空白（不含换行，避免跨行误读）
            while pos < len(content) and content[pos] in ' \t':
                pos += 1
            if pos >= len(content):
                break

            c = content[pos]
            # 遇到以下字符停止收集标识符
            if c in '{;:(<\r\n':
                break

            if c.isalpha() or c == '_':
                word_start = pos
                while pos < len(content) and (content[pos].isalnum() or content[pos] == '_'):
                    pos += 1
                word = content[word_start:pos]
                words.append(word)
                word_positions.append((word_start, pos))
            else:
                break

        # 查找哪个词是我们映射中的类名
        class_name = None
        class_name_start = -1
        class_name_end = -1

        for word, (ws, we) in zip(words, word_positions):
            if word in mapping:
                class_name = word
                class_name_start = ws
                class_name_end = we
                break

        if class_name is None:
            continue

        # friend class ClassName → 交给阶段2做前缀替换，不包裹
        if is_friend:
            continue

        # 确定声明类型：向前扫描，跳过空白
        scan_pos = class_name_end
        while scan_pos < len(content) and content[scan_pos] in ' \t\r\n':
            scan_pos += 1

        if scan_pos >= len(content):
            continue

        # 还可能有 'final' 等关键字在类名之后
        # 检测: 可能是 final / : / { / ;
        rest_word = ''
        if content[scan_pos].isalpha():
            wp = scan_pos
            while wp < len(content) and (content[wp].isalnum() or content[wp] == '_'):
                wp += 1
            rest_word = content[scan_pos:wp]
            scan_pos = wp
            while scan_pos < len(content) and content[scan_pos] in ' \t\r\n':
                scan_pos += 1

        next_char = content[scan_pos] if scan_pos < len(content) else ''

        namespace_str = mapping[class_name]

        # 尝试从 clang 获取精确的 class 范围（含 template）
        clang_extent = None
        if class_name in clang_extents:
            for (c_start, c_end, c_is_def) in clang_extents[class_name]:
                # 匹配条件：clang extent 覆盖了正则找到的类名位置
                if c_start <= class_name_start and c_end >= class_name_end:
                    clang_extent = (c_start, c_end, c_is_def)
                    break

        if next_char == ';' and rest_word == '':
            # 前向声明: class A;
            if clang_extent:
                wrap_start = clang_extent[0]
            else:
                wrap_start = kw_match.start()
            wrap_end = scan_pos + 1  # 包含 ;
            prefix, suffix = generate_namespace_wrapper(namespace_str)
            modifications.append((wrap_start, 0, prefix))
            modifications.append((wrap_end, 0, suffix))
            protected_name_pos.append((class_name_start, class_name_end))

        elif next_char == '{' or next_char == ':' or rest_word == 'final':
            # 类定义（可能有继承或 final）
            if clang_extent:
                # 使用 clang 提供的精确范围（含 template）
                wrap_start = clang_extent[0]
                clang_end_off = clang_extent[1]
                # clang extent end 通常指向 } 之后，寻找尾部 ;
                semi_pos = clang_end_off
                while semi_pos < len(content) and content[semi_pos] in ' \t\r\n':
                    semi_pos += 1
                if semi_pos < len(content) and content[semi_pos] == ';':
                    wrap_end = semi_pos + 1
                else:
                    wrap_end = clang_end_off

                # 用 find_matching_brace 获取 body 范围以保护同名引用
                brace_pos = content.find('{', class_name_end)
                if brace_pos != -1 and brace_pos < clang_end_off:
                    close_brace = find_matching_brace(content, brace_pos)
                    if close_brace != -1:
                        protected_body_ranges.append((brace_pos, close_brace, class_name))
            else:
                # clang 未能提供范围，回退到大括号匹配
                wrap_start = find_template_start(content, kw_match.start())
                brace_pos = content.find('{', class_name_end)
                if brace_pos == -1:
                    continue
                close_brace = find_matching_brace(content, brace_pos)
                if close_brace == -1:
                    continue
                semi_pos = close_brace + 1
                while semi_pos < len(content) and content[semi_pos] in ' \t\r\n':
                    semi_pos += 1
                if semi_pos < len(content) and content[semi_pos] == ';':
                    wrap_end = semi_pos + 1
                else:
                    wrap_end = close_brace + 1
                protected_body_ranges.append((brace_pos, close_brace, class_name))

            prefix, suffix = generate_namespace_wrapper(namespace_str)
            modifications.append((wrap_start, 0, prefix))
            modifications.append((wrap_end, 0, suffix))
            protected_name_pos.append((class_name_start, class_name_end))

        # 其他情况（如 elaborated type specifier）不包裹，交给阶段2处理

    # ================ 阶段1.5: DEFINE_STANDARD_EXCEPTION 宏包裹 ================

    macro_regex = re.compile(r'\bDEFINE_STANDARD_EXCEPTION\s*\(')

    for macro_match in macro_regex.finditer(content):
        # 检查是否在 #include 行
        line_no = content[:macro_match.start()].count('\n')
        if line_no in include_line_set:
            continue

        # 提取宏参数中的第一个标识符（类名）
        arg_start = macro_match.end()
        # 跳过空白
        pos = arg_start
        while pos < len(content) and content[pos] in ' \t\r\n':
            pos += 1

        # 读取第一个标识符
        if pos >= len(content) or not (content[pos].isalpha() or content[pos] == '_'):
            continue
        word_start = pos
        while pos < len(content) and (content[pos].isalnum() or content[pos] == '_'):
            pos += 1
        first_arg = content[word_start:pos]

        if first_arg not in mapping:
            continue

        # 找到匹配的右括号 )
        paren_depth = 1
        scan = macro_match.end()
        while scan < len(content) and paren_depth > 0:
            if content[scan] == '(':
                paren_depth += 1
            elif content[scan] == ')':
                paren_depth -= 1
            scan += 1
        # scan 现在指向 ) 之后的位置
        if paren_depth != 0:
            continue

        wrap_start = macro_match.start()
        wrap_end = scan
        namespace_str = mapping[first_arg]
        prefix, suffix = generate_namespace_wrapper(namespace_str)
        modifications.append((wrap_start, 0, prefix))
        modifications.append((wrap_end, 0, suffix))
        protected_name_pos.append((word_start, word_start + len(first_arg)))


    for ref_match in ref_regex.finditer(content):
        name = ref_match.group(1)
        name_start = ref_match.start(1)
        name_end = ref_match.end(1)

        # 检查是否在 #include 行
        line_no = content[:name_start].count('\n')
        if line_no in include_line_set:
            continue

        # 检查是否是 class 声明中的类名位置（已被阶段1处理）
        if any(s == name_start and e == name_end for s, e in protected_name_pos):
            continue

        # 检查是否在被 namespace 包裹的 class body 内，且是该 class 自身的名字
        if any(s <= name_start <= e and name == cn
               for s, e, cn in protected_body_ranges):
            continue

        # 检查前方是否有 :: （跳过构造函数等 A::A 中第二个A）
        if name_start >= 2 and content[name_start - 2:name_start] == '::':
            continue
        if name_start >= 1 and content[name_start - 1] == ':' and \
           name_start >= 2 and content[name_start - 2] == ':':
            continue

        # 检查前方是否有 ~ （析构函数）
        pre = name_start - 1
        while pre >= 0 and content[pre] in ' \t':
            pre -= 1
        if pre >= 0 and content[pre] == '~':
            continue

        # 执行替换
        ns = mapping[name]
        new_text = f'{ns}::{name}'
        modifications.append((name_start, name_end - name_start, new_text))

    if not modifications:
        return False

    # ================ 应用修改（倒序） ================

    modifications.sort(key=lambda x: x[0], reverse=True)

    new_content = content
    seen_offsets = set()
    total_mod_count = 0

    for offset, length, text in modifications:
        if offset in seen_offsets:
            continue
        new_content = new_content[:offset] + text + new_content[offset + length:]
        seen_offsets.add(offset)
        total_mod_count += 1

    if new_content == content:
        return False

    if not dry_run:
        try:
            with open(filepath, 'w', encoding='utf-8', newline='') as f:
                f.write(new_content)
            print(f"  [修改] {os.path.basename(filepath)} (共 {total_mod_count} 处修改)")
        except Exception as e:
            print(f"  [写入错误] {filepath}: {e}")
    else:
        print(f"  [预演] {os.path.basename(filepath)} (发现 {total_mod_count} 处修改)")

    return True


def main(root_dir, csv_path, start_row, end_row, dry_run=True):
    start_time = time.time()

    # 1. 加载映射
    mapping = load_namespace_mapping(csv_path, start_row, end_row)

    if not mapping:
        print("停止执行：没有规则可供处理。")
        return

    # 2. 构建引用替换正则
    ref_regex = build_reference_regex(mapping)
    mapping_names_set = set(mapping.keys())

    print(f"[*] 扫描目录: {root_dir}")
    print(f"[*] 限制条件: 全字匹配 | 忽略 #include | 跳过 ::Name 和 ~Name")

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
            is_test_data_no_ext = is_in_tests_or_data and (ext == '')
            is_src_resource_file = is_in_src and (ext == '')

            if not (is_allowed_ext or is_test_data_no_ext or is_src_resource_file):
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
    parser = argparse.ArgumentParser(description="基于正则的 Namespace 包裹工具 (读取CSV)")
    parser.add_argument("dir", help="源码目录")
    parser.add_argument("csv_file", help="映射表CSV文件路径")

    parser.add_argument("--start_row", type=int, default=1, help="CSV起始行号(包含), 默认为1")
    parser.add_argument("--end_row", type=int, default=None, help="CSV结束行号(包含), 默认为末尾")

    parser.add_argument("--run", action="store_true", help="执行实际修改 (默认仅预演)")

    args = parser.parse_args()

    if not os.path.exists(args.dir):
        print(f"目录不存在: {args.dir}")
        sys.exit(1)

    if not os.path.exists(args.csv_file):
        print(f"CSV文件不存在: {args.csv_file}")
        sys.exit(1)

    main(args.dir, args.csv_file, args.start_row, args.end_row, dry_run=not args.run)
