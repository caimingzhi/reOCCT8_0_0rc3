# Add Namespace Script

## 1. 背景

为了方便重命名，我们打算先给代码加上命名空间——这样不同的命名空间里，就可以拥有相同名字的类了。

## 2. 脚本功能

如背景所述。
这个脚本没有借用clang语法分析器（ai生成的借用语法分析器的代码，错漏百出）。
假设原本有一个
class OldClass
{
    OldClass::OldClass();
    string GetHello() { return "hello"; }
};
OldClass a;
cout << a.GetHello();

如果我希望给OldClass添加一个MyNamespace，那么，

1. 在所有形如class OldClass的地方，会加MyNamespace包裹。
2. 在其它用到OldClass的地方，会加MyNamespace::前缀。

即，修改后变成
namespace MyNamespace
{
    class OldClass
    {
        OldClass::OldClass();
        string GetHello() { return "hello"; }
    };
}
MyNamespace::OldClass a;
cout << a.GetHello();

如果namespace是多级的，处理类似，区别只是在包裹class时做了多层包裹。

## 3. 脚本用法

python add_namespace.py "source path" "csv file path"
例如：
python ./scripts/add_namespace/add_namespace.py ./src renaming.csv
