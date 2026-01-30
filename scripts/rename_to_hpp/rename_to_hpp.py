import os
import argparse
import csv
import sys

# ================= 配置区域 =================
# 要处理的旧扩展名
TARGET_EXTS = {".lxx", ".pxx", ".gxx"}

# 需要扫描内容并更新引用的文件类型
# 包括源码、CMake配置、FILES列表等
TEXT_FILES_EXT = {
    ".hxx", ".cxx", ".hpp", ".cpp", ".h", ".c", 
    ".lxx", ".pxx", ".gxx", 
    ".cmake", ".template", ".cbp", ".vcxproj", ".filters", ".txt"
}

# 忽略的目录（如git仓库）
IGNORE_DIRS = {".git", ".vs", "build", "out"}
# ===========================================

def get_target_files(root_dir):
    """
    扫描目标目录下所有需要重命名的文件，并排序确保确定性。
    """
    targets = []
    print(f"Scanning directory: {root_dir} ...")
    
    for root, dirs, files in os.walk(root_dir):
        # 过滤目录
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        
        for f in files:
            ext = os.path.splitext(f)[1].lower()
            if ext in TARGET_EXTS:
                full_path = os.path.join(root, f)
                targets.append(full_path)
    
    # 排序是必须的，保证多次运行生成的 _1, _2 顺序一致
    targets.sort()
    return targets

def plan_renames(target_files):
    """
    生成重命名计划，解决命名冲突。
    返回:
    1. plan_list: [(OldPath, NewPath, OldName, NewName), ...]
    2. filename_map: { "OldName": "NewName" } 用于文本替换
    """
    plan_list = []
    filename_map = {}
    
    # 记录本轮运行中已经预定的新路径，防止 A.lxx 和 A.pxx 抢同一个 A.hpp
    reserved_paths = set()

    print("Planning renames and resolving collisions...")

    for old_path in target_files:
        dirname, filename = os.path.split(old_path)
        base_name = os.path.splitext(filename)[0]
        
        # 默认尝试 Base.hpp
        candidate_name = base_name + ".hpp"
        candidate_path = os.path.join(dirname, candidate_name)
        
        counter = 1
        # 冲突检测循环：
        # 1. 如果文件系统里已经存在该文件 (os.path.exists)
        # 2. 或者该名字已经被本轮的前一个文件预定了 (in reserved_paths)
        # 则尝试 _1.hpp, _2.hpp
        while os.path.exists(candidate_path) or candidate_path in reserved_paths:
            candidate_name = f"{base_name}_{counter}.hpp"
            candidate_path = os.path.join(dirname, candidate_name)
            counter += 1
        
        # 锁定该路径
        reserved_paths.add(candidate_path)
        
        # 记录
        plan_list.append((old_path, candidate_path, filename, candidate_name))
        filename_map[filename] = candidate_name
        
        if counter > 1:
            print(f"  [Collision Resolved] {filename} -> {candidate_name}")

    return plan_list, filename_map

def save_csv(plan_list, output_file="rename_mapping.csv"):
    """
    将映射表保存到 CSV 文件
    """
    print(f"Saving mapping table to {output_file} ...")
    try:
        with open(output_file, 'w', newline='', encoding='utf-8') as csvfile:
            writer = csv.writer(csvfile)
            # 写入表头
            writer.writerow(["Old Name", "New Name", "Old Path", "New Path"])
            # 写入数据
            for old_path, new_path, old_name, new_name in plan_list:
                writer.writerow([old_name, new_name, old_path, new_path])
        print("  CSV saved successfully.")
    except Exception as e:
        print(f"  Error saving CSV: {e}")

def update_file_contents(root_dir, filename_map):
    """
    遍历目录下的所有文本文件，替换对旧文件名的引用
    """
    print("Updating #include references in source files...")
    
    # 按文件名长度倒序排列，防止子串误替换 (虽然带后缀通常没事)
    sorted_old_names = sorted(filename_map.keys(), key=len, reverse=True)
    
    count = 0
    for root, dirs, files in os.walk(root_dir):
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        
        for f in files:
            # 检查是否是需要更新的文件类型，或者是 FILES 列表文件
            ext = os.path.splitext(f)[1].lower()
            if f == "FILES" or ext in TEXT_FILES_EXT:
                file_path = os.path.join(root, f)
                
                try:
                    # OCCT 源码通常是 Latin-1 编码
                    with open(file_path, 'r', encoding='latin-1') as f_in:
                        content = f_in.read()
                    
                    new_content = content
                    modified = False
                    
                    # 快速检查：如果文件里根本没有相关扩展名，跳过循环
                    if any(ext in content for ext in TARGET_EXTS):
                        for old_name in sorted_old_names:
                            if old_name in new_content:
                                new_name = filename_map[old_name]
                                new_content = new_content.replace(old_name, new_name)
                                modified = True
                    
                    if modified:
                        with open(file_path, 'w', encoding='latin-1') as f_out:
                            f_out.write(new_content)
                        count += 1
                except Exception as e:
                    print(f"  Warning: Could not process {file_path}: {e}")
                    
    print(f"Updated references in {count} files.")

def perform_physical_rename(plan_list):
    """
    执行磁盘上的重命名操作
    """
    print("Executing physical file renames...")
    count = 0
    for old_path, new_path, _, _ in plan_list:
        try:
            os.rename(old_path, new_path)
            count += 1
        except Exception as e:
            print(f"  Error renaming {old_path}: {e}")
    print(f"Renamed {count} files on disk.")

def main():
    # 1. 解析命令行参数
    parser = argparse.ArgumentParser(description="Batch rename OCCT source extensions (.lxx/.pxx/.gxx -> .hpp) and update references.")
    parser.add_argument("target_dir", help="The root directory to scan (e.g., ./src)")
    parser.add_argument("--csv", default="rename_mapping.csv", help="Output CSV filename (default: rename_mapping.csv)")
    
    args = parser.parse_args()
    
    target_dir = os.path.abspath(args.target_dir)
    if not os.path.exists(target_dir):
        print(f"Error: Directory '{target_dir}' does not exist.")
        sys.exit(1)

    # 2. 扫描文件
    targets = get_target_files(target_dir)
    if not targets:
        print("No target files (.lxx, .pxx, .gxx) found.")
        sys.exit(0)

    # 3. 生成重命名计划
    plan_list, filename_map = plan_renames(targets)
    
    # 4. 保存 CSV
    save_csv(plan_list, args.csv)
    
    # 5. 更新文件内容引用
    update_file_contents(target_dir, filename_map)
    
    # 6. 执行重命名
    perform_physical_rename(plan_list)

    print("\n------------------------------------------------")
    print("Process Completed.")
    print(f"Mapping file saved to: {os.path.abspath(args.csv)}")
    print("Remember to clean your CMake cache and rebuild!")

if __name__ == "__main__":
    main()
