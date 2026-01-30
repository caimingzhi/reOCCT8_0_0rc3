import os
import argparse
import sys
import csv
import time
import concurrent.futures

# ================= 配置区域 =================

# 允许扫描的文件后缀 (根据你的项目调整)
ALLOWED_EXTENSIONS = {
    '.hxx', '.hpp', '.cxx', '.cpp', '.c', '.h', '.lxx', '.gxx',
    '.cmake', '.txt', '.mm', '.pxx'
}

# 忽略的目录
IGNORE_DIRS = {
    '.git', '.vs', 'build', 'out', 'bin', 'lib', 'doc', 'adm'
}

# ===========================================

def get_all_source_files(root_dir):
    """
    遍历目录获取所有需要扫描的文件路径列表
    """
    file_list = []
    print(f"[*] 正在索引文件: {root_dir}")
    for dirpath, dirnames, filenames in os.walk(root_dir):
        # 过滤目录
        dirnames[:] = [d for d in dirnames if d not in IGNORE_DIRS]
        
        for filename in filenames:
            _, ext = os.path.splitext(filename)
            if ext.lower() in ALLOWED_EXTENSIONS:
                file_list.append(os.path.join(dirpath, filename))
    print(f"[*] 索引完成，共 {len(file_list)} 个文件待扫描。")
    return file_list

def search_in_file(filepath, target_strings):
    """
    在单个文件中搜索目标字符串集合。
    返回在这个文件中找到的所有目标字符串。
    """
    found_items = set()
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
            # 简单的字符串包含搜索 (比正则快，适合大规模初筛)
            for s in target_strings:
                if s in content:
                    found_items.add(s)
    except Exception:
        pass
    return found_items

def main(root_dir, csv_path):
    start_time = time.time()
    
    # 1. 读取 CSV 获取所有 Suggested_New_Name
    rules = [] # 存储 (New, Old) 元组
    new_names_set = set()
    
    print(f"[*] 正在读取规则 CSV: {csv_path}")
    try:
        with open(csv_path, 'r', encoding='utf-8') as f:
            reader = csv.DictReader(f)
            if 'Suggested_New_Name' not in reader.fieldnames:
                print("[错误] CSV 缺少 'Suggested_New_Name' 列")
                sys.exit(1)
                
            for row in reader:
                new_name = row['Suggested_New_Name'].strip()
                old_name = row['Original_Class_Name'].strip()
                if new_name and old_name:
                    rules.append({'Suggested_New_Name': new_name, 'Original_Class_Name': old_name})
                    new_names_set.add(new_name)
    except Exception as e:
        print(f"[错误] 读取 CSV 失败: {e}")
        sys.exit(1)

    print(f"[*] 共加载 {len(rules)} 条规则，涉及 {len(new_names_set)} 个唯一的新名字。")

    # 2. 获取文件列表
    if not os.path.exists(root_dir):
        print(f"[错误] 目录不存在: {root_dir}")
        sys.exit(1)
    
    all_files = get_all_source_files(root_dir)

    # 3. 并行搜索
    print("[*] 开始全量搜索冲突 (可能需要几分钟)...")
    found_names = set()
    
    # 使用多进程/线程加速搜索
    # 将 new_names_set 转为 list 方便传递，但其实在 search_in_file 里我们只需要遍历它
    # 为了效率，我们按文件并行，每个文件搜一遍所有关键词
    
    with concurrent.futures.ProcessPoolExecutor() as executor:
        # 提交任务
        futures = {executor.submit(search_in_file, f, new_names_set): f for f in all_files}
        
        # 收集结果
        completed_count = 0
        total_count = len(all_files)
        
        for future in concurrent.futures.as_completed(futures):
            found_in_file = future.result()
            found_names.update(found_in_file)
            
            completed_count += 1
            if completed_count % 1000 == 0:
                print(f"    进度: {completed_count}/{total_count} 文件...", end='\r')

    print(f"\n[*] 搜索结束。共发现 {len(found_names)} 个新名字已在代码中存在。")

    # 4. 分类并写入结果
    safe_rows = []
    risky_rows = []

    for row in rules:
        if row['Suggested_New_Name'] in found_names:
            risky_rows.append(row)
        else:
            safe_rows.append(row)

    # 写入 Safe 文件
    safe_csv = "safe_to_rename.csv"
    with open(safe_csv, 'w', encoding='utf-8', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=['Suggested_New_Name', 'Original_Class_Name'])
        writer.writeheader()
        writer.writerows(safe_rows)

    # 写入 Risky 文件
    risky_csv = "risky_new_names.csv"
    with open(risky_csv, 'w', encoding='utf-8', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=['Suggested_New_Name', 'Original_Class_Name'])
        writer.writeheader()
        writer.writerows(risky_rows)

    end_time = time.time()
    print("-" * 60)
    print(f"处理完成，耗时 {end_time - start_time:.2f} 秒")
    print(f"[Safe]  无冲突规则: {len(safe_rows)} 条 -> 已保存至 {safe_csv}")
    print(f"[Risky] 有冲突规则: {len(risky_rows)} 条 -> 已保存至 {risky_csv}")
    print("\n建议：")
    print("1. 对 risky_new_names.csv 中的条目进行人工核查（看是重名了，还是本身就是代码里已有的定义）。")
    print("2. 优先对 safe_to_rename.csv 执行批量重命名。")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="检测新类名是否已存在于源码中")
    parser.add_argument("dir", help="源码根目录 (例如 D:\\OCCT\\src)")
    parser.add_argument("csv_file", help="重命名规则 CSV")
    
    args = parser.parse_args()
    
    # 启用 Windows 下的多进程支持保护
    import multiprocessing
    multiprocessing.freeze_support()
    
    main(args.dir, args.csv_file)
