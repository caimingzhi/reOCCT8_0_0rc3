# Rename To hpp Script

## 1. 背景

为了方便重命名，我们打算先给代码加上命名空间——这样不同的命名空间里，就可以拥有相同名字的类了。
为了方便整理命名空间，我们打算先把文件整理一遍。

第一步，先把.hxx/.lxx/.pxx/.gxx重命名成.hpp，规范命名。

## 2. 脚本功能

如背景所述，把.hxx/.lxx/.pxx/.gxx重命名成.hpp。
会对应修改#include，以及CMake配置、FILES列表。

## 3. 脚本用法

python rename_to_hpp.py "source path"
特殊参数：
--csv f  输出保存到f中
例如：
python rename_to_hpp.py ./src --csv my_renames.csv
