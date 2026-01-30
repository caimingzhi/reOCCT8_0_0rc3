# Check New Name Duplicates Script

## 1. 背景

已有renaming_map.csv文件，里面列出了需要重命名的类名。
但是这个文件中的Suggested_New_Name列，是ai工具给出的建议，可能出现重复。
需要重命名的类太多，ai难以记住这么长的token，因此需要脚本辅助检查。

## 2. 脚本功能

扫描所有Suggested_New_Name，如果同个Suggested_New_Name在多行出现，标记为重复。

## 3. 脚本用法

python check_newname_duplicates.py "csv file path"
例如：
python ./test_results/check_newname_duplicates.py ./test_results/safe_to_rename.csv
输出：
single_rename.csv  无重复的Suggested_New_Name
duplicate_conflicts.txt  有重复的Suggested_New_Name
