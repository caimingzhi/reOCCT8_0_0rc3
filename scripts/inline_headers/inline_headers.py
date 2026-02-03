import os
import sys
import argparse
import re

def get_cmake_files(dir_path):
    """
    获取指定目录下所有可能的构建文件列表。
    """
    candidates = []
    if not os.path.exists(dir_path):
        return candidates
    
    try:
        for f in os.listdir(dir_path):
            full_path = os.path.join(dir_path, f)
            if os.path.isfile(full_path):
                if f.lower().endswith(".cmake") or f == "FILES":
                    candidates.append(full_path)
    except Exception as e:
        print(f"    [Warn] 无法扫描目录 {dir_path}: {e}")
        
    return candidates

def update_cmake_file_content(file_path, filename_to_remove, is_dry_run):
    """
    尝试从指定的 CMake 文件中移除文件名。
    """
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
        
        new_lines = []
        removed = False
        target = filename_to_remove.strip()
        
        for line in lines:
            clean_line = line.strip().replace('"', '').replace("'", "")
            if clean_line == target:
                removed = True
                continue
            new_lines.append(line)
            
        if removed:
            if not is_dry_run:
                with open(file_path, 'w', encoding='utf-8') as f:
                    f.writelines(new_lines)
            print(f"    [Build] 已从 {os.path.basename(file_path)} 中移除: {target}")
            return True
        else:
            return False
            
    except Exception as e:
        print(f"    [Error] 修改构建文件失败 {os.path.basename(file_path)}: {e}")
        return False

def process_inline_recursive(psv_file, root_dir, is_dry_run):
    root_dir = os.path.abspath(root_dir)
    print(f"工作目录: {root_dir}")
    
    if is_dry_run:
        print("--- 模式: DRY RUN (仅模拟，不修改文件) ---")
    else:
        print("--- 模式: EXECUTE (注意：将直接修改和删除文件！) ---")

    # --- 1. 构建任务字典 ---
    pending_tasks = {}
    
    try:
        with open(psv_file, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            if lines and "HPP_File" in lines[0]:
                lines = lines[1:]
            
            for line in lines:
                parts = line.split('|')
                if len(parts) < 2: continue
                
                child_rel = parts[0].strip()
                refs_str = parts[1].strip()
                if not refs_str: continue
                
                refs = refs_str.split(',')
                if len(refs) == 1:
                    parent_rel = refs[0].strip()
                    if parent_rel.endswith('.hpp'):
                        pending_tasks[child_rel] = parent_rel
    except FileNotFoundError:
        print(f"错误: 找不到 PSV 文件 {psv_file}")
        return

    print(f"初始任务队列: {len(pending_tasks)} 个待合并文件")
    success_count = 0

    # --- 2. 动态循环处理 ---
    while pending_tasks:
        current_child, current_parent = pending_tasks.popitem()
        
        child_abs = os.path.join(root_dir, current_child)
        parent_abs = os.path.join(root_dir, current_parent)
        child_filename = os.path.basename(current_child)
        child_dir = os.path.dirname(child_abs)

        print(f"\n[任务] {child_filename} -> {os.path.basename(current_parent)}")

        if not os.path.exists(child_abs):
            print(f"    [Error] 子文件缺失: {current_child}")
            continue
        if not os.path.exists(parent_abs):
            print(f"    [Error] 父文件缺失: {current_parent}")
            continue

        merged = False
        try:
            # === 关键修改点 1: 读取子文件使用 utf-8-sig 自动去除 BOM ===
            # errors='ignore' 保持不变以兼容非 UTF-8 字符
            with open(child_abs, 'r', encoding='utf-8-sig', errors='ignore') as f:
                child_content = f.read()

            # === 关键修改点 2: 再次显式清理 BOM (双重保险) ===
            # 防止有些文件中间混入了 BOM 或者编码识别偏移
            child_content = child_content.replace('\ufeff', '')

            # 读取父文件 (父文件通常已经存在，BOM 应该只在开头，这里用 utf-8-sig 也没坏处)
            with open(parent_abs, 'r', encoding='utf-8-sig', errors='ignore') as f:
                parent_content = f.read()

            if not child_content.endswith('\n'):
                child_content += '\n'

            pattern = r'^\s*#\s*include\s+["<]' + re.escape(child_filename) + r'[">].*$'
            match = re.search(pattern, parent_content, re.MULTILINE)
            
            if match:
                if not is_dry_run:
                    new_parent_content = re.sub(pattern, lambda x: child_content, parent_content, count=1, flags=re.MULTILINE)
                    # 写回时使用 standard utf-8 (不带BOM)，这是 Linux/现代编译器最喜欢的格式
                    with open(parent_abs, 'w', encoding='utf-8') as f:
                        f.write(new_parent_content)
                    print(f"    [Merge] 已写入父文件")
                else:
                    print(f"    [Merge] (模拟) 将内容合并入父文件")
                
                merged = True
            else:
                print(f"    [Error] 父文件中未找到 include 语句")

        except Exception as e:
            print(f"    [Error] 合并异常: {e}")
            continue

        if merged:
            cmake_candidates = get_cmake_files(child_dir)
            found_in_cmake = False
            for cmake_file in cmake_candidates:
                if update_cmake_file_content(cmake_file, child_filename, is_dry_run):
                    found_in_cmake = True
            
            if not found_in_cmake:
                 print(f"    [Warn] 在构建文件中未找到文件名记录")

            if not is_dry_run:
                try:
                    os.remove(child_abs)
                    print(f"    [Delete] 已删除源文件")
                except Exception as e:
                    print(f"    [Delete Failed] {e}")
            else:
                print(f"    [Delete] (模拟) 删除源文件")

            success_count += 1

            redirect_count = 0
            for child_key, parent_val in list(pending_tasks.items()):
                if parent_val == current_child:
                    pending_tasks[child_key] = current_parent
                    redirect_count += 1
            
            if redirect_count > 0:
                print(f"    [Update] 重定向 {redirect_count} 个依赖关系")

    print(f"\n全部完成。共成功处理 {success_count} 个文件。")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="递归合并HPP文件(自动去除BOM)")
    parser.add_argument("psv_file", help="输入PSV文件")
    parser.add_argument("root_dir", help="OCCT源码根目录 (src)")
    parser.add_argument("--run", action="store_true", help="执行修改")
    
    args = parser.parse_args()
    
    if not os.path.isdir(args.root_dir):
        print(f"错误: 目录不存在 {args.root_dir}")
    else:
        is_dry_run = not args.run
        process_inline_recursive(args.psv_file, args.root_dir, is_dry_run)
