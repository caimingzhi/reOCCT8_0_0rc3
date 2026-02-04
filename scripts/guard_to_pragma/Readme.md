# Guard To Pragma Script

## 1. 背景

清理旧风格的include guards，改用pragma once。

## 2. 脚本功能

如背景所述。
仅匹配文件开头的include guards。
且对于本身旧没有include guards的hpp文件，不额外添加pragma once——这部分hpp就是被设计成要include多次的。

## 3. 脚本用法

python guard_to_pragma.py "source path" "log file path"
特殊参数：
--run 实际执行，不加则是预演模式
例如：
python ./scripts/guard_to_pragma/guard_to_pragma.py ./src ./scripts/guard_to_pragma/error_log.txt --run

## 4. 运行结果

保存了运行的结果error_log.txt。
_Standard_Integer_HeaderFile、
_Standard_Macro_HeaderFile、
_Standard_Real_HeaderFile、
_TCollection_HAsciiString_HeaderFile、
_TCollection_HExtendedString_HeaderFile，这些是可以删掉的，已手动处理。
