import os
import re
import argparse
import sys
from collections import Counter

def log_message(log_path, level, message):
    formatted_msg = f"[{level}] {message}"
    if level == "ERROR" or level == "SKIP":
        print(f"  {formatted_msg}")
    try:
        with open(log_path, 'a', encoding='utf-8') as f:
            f.write(formatted_msg + "\n")
    except:
        pass

def remove_comments_in_memory(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'): return " " 
        else: return " "
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|"(?:\\.|[^\\"])*"|\'(?:\\.|[^\\\'])*\'',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

def scan_main_guards(root_dir):
    """
    Step 2.1: 扫描位于文件 '第一行有效代码' 的 Include Guard
    """
    print("Step 2.1: 扫描 Main Include Guards...")
    candidates = {} # macro -> file_path
    
    re_ifndef = re.compile(r'^\s*#\s*ifndef\s+(\w+)')
    re_define = re.compile(r'^\s*#\s*define\s+(\w+)')

    for root, dirs, files in os.walk(root_dir):
        for file in files:
            if not file.lower().endswith('.hpp'):
                continue
            
            file_path = os.path.join(root, file)
            try:
                with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                    lines = f.readlines()
                
                # 寻找第一行非空行
                found_first_line = False
                for i in range(len(lines) - 1):
                    line = lines[i].strip()
                    if not line: continue 
                    
                    # 第一行有效代码必须是 ifndef
                    m_ifndef = re_ifndef.match(lines[i])
                    if m_ifndef:
                        macro_name = m_ifndef.group(1)
                        # 下一行必须是 define
                        m_define = re_define.match(lines[i+1])
                        if m_define and m_define.group(1) == macro_name:
                            # 找到了 Main Guard
                            if macro_name in candidates:
                                candidates[macro_name] = None # 重复定义，标记无效
                            else:
                                candidates[macro_name] = file_path
                    
                    # 无论是否匹配，只要遇到了非空行，就停止判断 "Main Guard"
                    found_first_line = True
                    break
                    
            except Exception: pass

    # 过滤掉 None
    return {k: v for k, v in candidates.items() if v is not None}

def count_occurrences(root_dir, candidates):
    """
    Step 2.2: 统计宏引用次数
    """
    print("Step 2.2: 验证 Guard 安全性 (统计引用次数)...")
    macro_counts = Counter()
    candidate_set = set(candidates.keys())
    re_word = re.compile(r'\b\w+\b')

    processed = 0
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            valid_exts = ('.hpp', '.hxx', '.h', '.cpp', '.cxx', '.c', '.cc', '.mm')
            if not file.lower().endswith(valid_exts): continue

            file_path = os.path.join(root, file)
            try:
                with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                    clean_content = remove_comments_in_memory(content)
                    words = re_word.findall(clean_content)
                    relevant_words = [w for w in words if w in candidate_set]
                    macro_counts.update(relevant_words)
                processed += 1
                if processed % 100 == 0:
                    sys.stdout.write(f"\r  已扫描 {processed} 个文件...")
            except: pass
    print("\n  统计完成。")
    return macro_counts

def replace_guard_with_pragma(file_path, macro_name):
    """
    Step 2.3: 执行替换
    移除 #ifndef X, #define X 和匹配的 #endif，并在头部插入 #pragma once
    """
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
    except: return False

    re_ifndef = re.compile(r'^\s*#\s*ifndef\s+' + re.escape(macro_name))
    re_endif  = re.compile(r'^\s*#\s*endif\b')
    re_if_any = re.compile(r'^\s*#\s*(if|ifdef|ifndef)\b')

    start_idx = -1
    # 定位 Main Guard (肯定是第一行有效代码，前面已有扫描逻辑保证，这里再确认一次)
    for i in range(len(lines)):
        if lines[i].strip():
            if re_ifndef.match(lines[i]):
                start_idx = i
            break
    
    if start_idx == -1: return False

    # 寻找匹配的 endif
    indices_to_remove = {start_idx, start_idx + 1} # ifndef 和 define
    balance = 1
    found_end = False
    
    for j in range(start_idx + 2, len(lines)):
        line_clean = lines[j].split('//')[0]
        if re_if_any.match(line_clean):
            balance += 1
        elif re_endif.match(line_clean):
            balance -= 1
            if balance == 0:
                indices_to_remove.add(j)
                found_end = True
                break
    
    if not found_end: 
        print(f"  [警告] 文件 {os.path.basename(file_path)} endif 不匹配，跳过。")
        return False

    try:
        new_lines = ["#pragma once\n", "\n"]
        for idx, line in enumerate(lines):
            if idx not in indices_to_remove:
                new_lines.append(line)
        
        with open(file_path, 'w', encoding='utf-8') as f:
            f.writelines(new_lines)
        return True
    except Exception as e:
        print(f"  [写入失败] {file_path}: {e}")
        return False

def main():
    parser = argparse.ArgumentParser(description="Step 2: 将标准 Include Guard 替换为 #pragma once")
    parser.add_argument("target_dir", help="扫描根目录")
    parser.add_argument("error_log", help="日志输出路径") # 新增
    parser.add_argument("--run", action="store_true", help="执行实际修改")
    args = parser.parse_args()

    # 初始化日志
    with open(args.error_log, 'w', encoding='utf-8') as f:
        f.write("Step 2 Log: Replace Main Guards with #pragma once\n=============================\n")

    # 1. 找候选 (必须位于文件第一行的Guard)
    candidates = scan_main_guards(args.target_dir)
    if not candidates:
        print("未找到 Main Guard 候选。")
        return

    # 2. 验证引用计数
    # 只有 count == 2 (只在定义处和if判断处出现) 才认为是普通的Guard
    # 如果 count > 2，说明有其他文件在 check 这个宏 (例如 #ifdef OCCT_HEADER_H)，则不能替换为 pragma once
    macro_counts = count_occurrences(args.target_dir, candidates)
    
    valid_replacements = []
    
    for macro, path in candidates.items():
        count = macro_counts[macro]
        if count == 2:
            valid_replacements.append((macro, path))
        else:
            # 记录被跳过的宏
            log_message(args.error_log, "SKIP", f"主宏 '{macro}' (位于 {os.path.basename(path)}) 出现了 {count} 次 (非2次)。不符合标准Guard特征，已跳过。")

    print(f"\n分析结果:")
    print(f"  - 可安全替换: {len(valid_replacements)} 个")

    if not args.run:
        print("\n预览将执行的替换:")
        for m, p in valid_replacements[:5]:
            print(f"  - {os.path.basename(p)} (Guard: {m}) -> #pragma once")
        print("请添加 --run 执行替换。")
        return

    # 3. 执行替换
    success_count = 0
    for macro, path in valid_replacements:
        if replace_guard_with_pragma(path, macro):
            success_count += 1
            
    print(f"\n完成。成功处理 {success_count} 个文件。")

if __name__ == "__main__":
    main()
