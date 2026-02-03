# Rename To hpp Script

## 1. 背景

为了方便重命名，我们打算先给代码加上命名空间——这样不同的命名空间里，就可以拥有相同名字的类了。
为了方便整理命名空间，我们打算先把文件整理一遍。

第四步，读取psv中的hpp依赖关系，清理只被hpp单依赖的hpp，将它们合并。

## 2. 脚本功能

如背景所述，清理只被hpp单依赖的hpp。
会删除hpp文件，以及清理CMake配置、FILES列表。
由于可能出现链式依赖，比如A->B->C，而链式依赖在psv中出现的顺序不确定，因此需要有个map来记录依赖/被依赖对，每次合并时需要更新这个map。

## 3. 脚本用法

python inline_headers.py "psv file path" "source path"
特殊参数：
--run 实际执行，不加则是预演模式
例如：
python ./scripts/inline_headers/inline_headers.py ./scripts/scan_include_hpp/hpp_dependency.psv ./src --run
