# Clean Unused hpp Script

## 1. 背景

为了方便重命名，我们打算先给代码加上命名空间——这样不同的命名空间里，就可以拥有相同名字的类了。
为了方便整理命名空间，我们打算先把文件整理一遍。

第三步，读取psv中的hpp依赖关系，删除所有不被任何文件依赖的hpp。

## 2. 脚本功能

如背景所述，删除所有不被任何文件依赖的hpp。
会删除hpp文件，以及清理CMake配置、FILES列表。

## 3. 脚本用法

python clean_unused_hpp.py "psv file path" "source path"
特殊参数：
--run 实际执行，不加则是预演模式
例如：
python ./scripts/clean_unused_hpp/clean_unused_hpp.py ./scripts/scan_include_hpp/hpp_dependency.psv ./src --run
