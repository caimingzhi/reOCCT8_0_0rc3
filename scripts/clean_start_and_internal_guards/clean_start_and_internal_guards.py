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
    """
    [辅助] 移除字符串中的 C++ 注释和字符串字面量，用于统计宏引用计数
    """
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'): return " " 
        else: return " "

    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|"(?:\\.|[^\\"])*"|\'(?:\\.|[^\\\'])*\'',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

def strip_header_comments(file_path):
    """
    步骤1.1: 移除文件头部的注释块
    """
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
            
        # 匹配开头的注释块 (支持 // 和 /* ... */)
        header_pattern = re.compile(r'^(\s*(?://[^\n]*\n|/\*.*?\*/\s*))*', re.DOTALL)
        match = header_pattern.match(content)
        
        if match and match.end() > 0:
            header_len = match.end()
            new_content = content[header_len:].lstrip()
            # 如果内容没变（比如本来就没注释），就不写文件
            if new_content.strip() == content.strip():
                return False
            
            with open(file_path, 'w', encoding='utf-8') as f:
                f.write(new_content)
            return True
    except Exception as e:
        print(f"  [Header清理失败] {file_path}: {e}")
    return False

def scan_internal_candidates(root_dir):
    print("Step 1.2: 扫描内部冗余 Guard 候选...")
    candidates = {} 
    
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
                
                first_guard_found = False
                
                for i in range(len(lines) - 1):
                    line = lines[i].strip()
                    if not line: continue 

                    m_ifndef = re_ifndef.match(lines[i])
                    if m_ifndef:
                        macro_name = m_ifndef.group(1)

                        # --- FIX START: 智能区分系统宏和OCCT Guard ---
                        
                        # 1. 显式保护已知的重要配置宏
                        if macro_name in ['_USE_MATH_DEFINES', '_MSC_VER', '_WIN32', '_WINDOWS', '__cplusplus']:
                            continue

                        # 2. 针对以 '_' 开头的宏进行启发式判断
                        if macro_name.startswith('_'):
                            upper_name = macro_name.upper()
                            # 只有长得像 Guard 的宏才处理
                            is_likely_guard = (
                                upper_name.endswith('_HEADERFILE') or 
                                upper_name.endswith('_HXX') or 
                                upper_name.endswith('_HPP') or
                                upper_name.endswith('_H')
                            )
                            
                            if not is_likely_guard:
                                # 以 _ 开头但没有 Guard 后缀，视为系统配置宏，跳过
                                continue
                        # --- FIX END ---

                        m_define = re_define.match(lines[i+1])
                        
                        if m_define and m_define.group(1) == macro_name:
                            if not first_guard_found:
                                first_guard_found = True
                            else:
                                candidates[macro_name] = file_path

                        # 只要遇到了 ifndef，就标记代码开始了
                        if not first_guard_found: 
                            pass

            except Exception:
                pass

    return candidates

def count_occurrences(root_dir, candidates):
    """
    统计宏引用次数
    """
    print("Step 1.3: 统计宏引用次数...")
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
                    # 只统计我们在意的那些宏
                    relevant_words = [w for w in words if w in candidate_set]
                    macro_counts.update(relevant_words)
                processed += 1
                if processed % 100 == 0:
                    sys.stdout.write(f"\r  已扫描 {processed} 个文件...")
            except: pass
    print("\n  统计完成。")
    return macro_counts

def remove_guard_block(file_path, macro_name):
    """
    移除指定的 ifndef/define/endif 块
    """
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
    except: return False

    re_ifndef = re.compile(r'^\s*#\s*ifndef\s+' + re.escape(macro_name))
    re_define = re.compile(r'^\s*#\s*define\s+' + re.escape(macro_name))
    re_endif  = re.compile(r'^\s*#\s*endif\b')
    re_if_any = re.compile(r'^\s*#\s*(if|ifdef|ifndef)\b')

    start_idx = -1
    # 找开始点
    for i in range(len(lines) - 1):
        if re_ifndef.match(lines[i]) and re_define.match(lines[i+1]):
            start_idx = i
            break # 只删第一个匹配到的内部宏（防止同名宏多次出现逻辑复杂化）
    
    if start_idx == -1: return False

    # 找结束点 (处理嵌套)
    indices_to_remove = {start_idx, start_idx + 1}
    balance = 1
    found_end = False
    
    for j in range(start_idx + 2, len(lines)):
        line_clean = lines[j].split('//')[0] # 简单去注释
        if re_if_any.match(line_clean):
            balance += 1
        elif re_endif.match(line_clean):
            balance -= 1
            if balance == 0:
                indices_to_remove.add(j)
                found_end = True
                break
    
    if not found_end: return False

    try:
        with open(file_path, 'w', encoding='utf-8') as f:
            for idx, line in enumerate(lines):
                if idx not in indices_to_remove:
                    f.write(line)
        return True
    except: return False

def main():
    parser = argparse.ArgumentParser(description="Step 1: 清理头部注释 & 移除内部多余Guard")
    parser.add_argument("target_dir", help="扫描根目录")
    parser.add_argument("error_log", help="日志输出路径") # 新增
    parser.add_argument("--run", action="store_true", help="执行实际修改")
    args = parser.parse_args()

    # 初始化日志
    with open(args.error_log, 'w', encoding='utf-8') as f:
        f.write("Step 1 Log: Clean Headers & Remove Internal Guards\n=============================\n")
    cleaned_count = 0
    for root, dirs, files in os.walk(args.target_dir):
        for file in files:
            if file.lower().endswith('.hpp'):
                if args.run:
                    if strip_header_comments(os.path.join(root, file)):
                        cleaned_count += 1
                else:
                    # 预览模式简单统计
                    cleaned_count += 1
    
    action_str = "已清理" if args.run else "发现可清理"
    print(f"  {action_str} {cleaned_count} 个文件的头部注释。")

    # 2. 扫描内部 Guard
    candidates = scan_internal_candidates(args.target_dir)
    if not candidates:
        print("未发现内部冗余 Guard 候选。")
        return

    # 3. 统计引用
    macro_counts = count_occurrences(args.target_dir, candidates)
    
    to_remove = []
    for macro, path in candidates.items():
        if macro_counts[macro] == 2:
            to_remove.append((macro, path))
    
    print(f"扫描结果: 发现 {len(to_remove)} 个内部冗余 Guard (只出现2次，判定为非对外接口宏)。")

    if not args.run:
        print("预览将被移除的内部宏:")
        for m, p in to_remove[:5]:
            print(f"  - {m} in {os.path.basename(p)}")
        print("请添加 --run 执行删除。")
        return

    # 4. 执行删除
    removed_count = 0
    for macro, path in to_remove:
        if remove_guard_block(path, macro):
            removed_count += 1
            print(f"  [已移除] {macro} in {os.path.basename(path)}")
    
    # 在统计完次数后，添加跳过逻辑的日志：
    print(f"分析结果: 发现 {len(to_remove)} 个内部冗余 Guard (只出现2次)。")
    
    # 查找被跳过的（出现 >= 3 次的）
    for macro, count in macro_counts.items():
        if count >= 3:
            log_message(args.error_log, "SKIP", f"内部宏 '{macro}' 出现了 {count} 次 (>=3)，疑似被多处引用或有特殊用途，已跳过。")

if __name__ == "__main__":
    main()
