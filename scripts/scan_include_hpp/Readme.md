# Scan Include hpp Script

## 1. 背景

（大背景同rename_to_hpp）
为了方便重命名，我们打算先给代码加上命名空间——这样不同的命名空间里，就可以拥有相同名字的类了。
为了方便整理命名空间，我们打算先把文件整理一遍。

第二步，扫描所有.hpp的被依赖情况，输出到psv（因为多个依赖用,分隔，因此输出格式用psv）中保存。

## 2. 脚本功能

如背景所述，扫描所有.hpp的被依赖情况，输出到psv中保存。
只扫描#include。会忽略CMake配置、FILES列表中列出来的名字（因为不含有#include关键字）。

## 3. 脚本用法

python scan_include_hpp.py "source path"
特殊参数：
--output f  输出保存到f中
例如：
python ./scripts/scan_include_hpp/scan_include_hpp.py ./src --output hpp_dependency.psv

## 4. 运行结果

保存了运行的结果，其中
hpp_dependency.psv是做清理前的扫描结果
cleaned_dependency.psv是做了一次clean_unused_hpp和inline_headers后的扫描结果
cleaned_dependency.psv中仍有可以clean或inline的hpp，是第一次清理后新被判定为0依赖的（比如本身仅有A include了B，而没有其它任何文件include了A，此时A、B实际上都是孤儿文件，但第一轮扫描是识别不出来的）
