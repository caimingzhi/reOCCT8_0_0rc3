# Content Refactor Script

## 1. 背景

已有renaming_map.csv文件，里面列出了需要重命名的类名。
需要将Original_Class_Name匹配的类名，替换成Suggested_New_Name。

## 2. 脚本功能

1. 只扫描后缀在ALLOWED_EXTENSIONS中出现的文件，或是/src、/data、/tests下的无后缀文件。
2. 不扫描IGNORE_DIRS路径。
3. 按正则匹配完整单词。例外：会把"Handle_{Original_Class_Name}"也匹配上，替换成"Handle_{Suggested_New_Name}"。不会匹配#include行或紧跟着.hxx/.cxx的单词，防止替换到正文中的文件名（因为文件名没变）。
4. 会一次性加载所有替换规则，对每个单词进行扫描，匹配这些规则，即：外层循环是文件、内层循环是修改规则。这样可以减少打开文件的次数。（此前做过一个内外层循环反过来的版本，外层循环是修改规则、内层循环是文件，会慢很多，因为开关文件消耗时间）

## 3. 脚本用法

python content_refactor.py "source path" "csv file path"
特殊参数：
--start_row n  从第n条规则开始替换，忽略csv文件的前n-1条规则（注意n是去掉了csv表头行的，是实际的第n条规则，也就是通常在第n+1行）
--end_row n  到第n条规则结束
--run  实际执行，如果不加该参数则是预演模式
例如：
python ./test_results/content_refactor.py . ./test_results/single_rename.csv --start_row 1 --end_row 1 --run
