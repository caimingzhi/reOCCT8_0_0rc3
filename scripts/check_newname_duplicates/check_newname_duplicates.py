import csv
import os
import sys
from collections import defaultdict

def check_duplicates(input_csv, output_single_csv, output_conflict_txt):
    print(f"[*] 正在读取: {input_csv}")
    
    if not os.path.exists(input_csv):
        print(f"[错误] 文件不存在: {input_csv}")
        return

    # 1. 读取数据并按 Suggested_New_Name 分组
    # 结构: { "NewName": ["OldName1", "OldName2", ...] }
    name_grouping = defaultdict(list)
    fieldnames = []

    try:
        with open(input_csv, 'r', encoding='utf-8', errors='ignore') as f:
            reader = csv.DictReader(f)
            fieldnames = reader.fieldnames
            
            if 'Suggested_New_Name' not in fieldnames or 'Original_Class_Name' not in fieldnames:
                print("[错误] CSV 缺少必要的列 (Suggested_New_Name 或 Original_Class_Name)")
                return

            for row in reader:
                new_name = row['Suggested_New_Name'].strip()
                old_name = row['Original_Class_Name'].strip()
                
                if new_name and old_name:
                    name_grouping[new_name].append(old_name)
                    
    except Exception as e:
        print(f"[异常] 读取失败: {e}")
        return

    # 2. 分离数据
    single_rows = []
    conflict_lines = []

    for new_name, old_names_list in name_grouping.items():
        # 去重：有时候 CSV 里可能有完全重复的行，这不算冲突
        unique_old_names = sorted(list(set(old_names_list)))

        if len(unique_old_names) == 1:
            # === 情况 A: 没有冲突 (一对一) ===
            single_rows.append({
                'Suggested_New_Name': new_name,
                'Original_Class_Name': unique_old_names[0]
            })
        else:
            # === 情况 B: 出现冲突 (多对一) ===
            # 格式: NewName -> Old1, Old2, Old3
            line = f"{new_name} -> {', '.join(unique_old_names)}"
            conflict_lines.append(line)

    # 3. 写入 single_rename.csv (无冲突的)
    try:
        with open(output_single_csv, 'w', encoding='utf-8', newline='') as f:
            # 我们只保留这两列，保持纯净
            writer = csv.DictWriter(f, fieldnames=['Suggested_New_Name', 'Original_Class_Name'])
            writer.writeheader()
            writer.writerows(single_rows)
        print(f"[Safe] 已生成无冲突列表: {output_single_csv} (共 {len(single_rows)} 条)")
    except Exception as e:
        print(f"[异常] 写入 CSV 失败: {e}")

    # 4. 写入 duplicate_conflicts.txt (有冲突的)
    try:
        with open(output_conflict_txt, 'w', encoding='utf-8') as f:
            f.write(f"# 以下新名字 (Suggested_New_Name) 对应多个旧类名，请人工核查合并逻辑\n")
            f.write(f"# 格式: New_Name -> Old_Name_1, Old_Name_2 ...\n\n")
            for line in conflict_lines:
                f.write(line + "\n")
        print(f"[Warn] 已生成冲突报告:   {output_conflict_txt} (共 {len(conflict_lines)} 组冲突)")
    except Exception as e:
        print(f"[异常] 写入 TXT 失败: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="检测新类名是否重复")
    parser.add_argument("input_file", help="源 CSV")
    
    args = parser.parse_args()

    output_csv = "single_rename.csv"       # 输出：干净的一对一映射
    output_txt = "duplicate_conflicts.txt" # 输出：多对一的冲突报告

    check_duplicates(args.input_file, output_csv, output_txt)
