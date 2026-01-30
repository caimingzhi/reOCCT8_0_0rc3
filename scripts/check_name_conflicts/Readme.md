# Check Name Conflicts Script

## 1. 背景

已有renaming_map.csv文件，里面列出了需要重命名的类名。
但是这个文件中的Suggested_New_Name列，是ai工具给出的建议，不一定正确。

1. 重命名后，可能与C++标准库/第三方库命名冲突。
2. 重命名后，可能与OCCT的类名冲突。
3. 重命名后，可能与OCCT的函数名/变量名冲突。

因此需要冲突检查。

## 2. 脚本功能

目前的检查，只需要做一个简化版本。
仅检查背景中提到的2. 3.情形。且简化类名/函数名/变量名的判断规则。
扫描指定目录下的所有文件，识别出现过的所有单词，只要Suggested_New_Name和某个单词相同，就认为有可能出现冲突。标记为坏名字。

## 3. 脚本用法

python check_name_conflicts.py "path" "csv file path"
例如：
python check_name_conflicts.py "D:\reOCCT8_0_0rc3\src" "TKernelName01.csv"
输出：
safe_to_rename.csv  无冲突的Suggested_New_Name
risky_new_names.csv  有冲突的Suggested_New_Name
