# Clean Start And Internal Guards Script

## 1. 背景

清理hpp文件开头的注释段。
清理hpp文件非开头的include guards。

## 2. 脚本功能

如背景所述。

## 3. 脚本用法

python clean_start_and_internal_guards.py "source path" "log file path"
特殊参数：
--run 实际执行，不加则是预演模式
例如：
python ./scripts/clean_start_and_internal_guards/clean_start_and_internal_guards.py ./src ./scripts/clean_start_and_internal_guards/error_log.txt --run

## 4. 运行结果

保存了运行的结果error_log.txt。
