import os
import csv
import re
import sys
import argparse
import time

# ================= 配置区 =================
EXTENSIONS = {'.hpp', '.hxx', '.h', '.cpp', '.cxx', '.c'}
# ==========================================

def load_mapping(csv_path):
    mapping = {}
    if not os.path.exists(csv_path):
        print(f"Error: {csv_path} not found.")
        return {}
    with open(csv_path, 'r', encoding='utf-8-sig') as f:
        reader = csv.DictReader(f)
        for row in reader:
            if 'OldName' in row and 'NewNamespace' in row:
                old = row['OldName'].strip()
                new = row['NewNamespace'].strip()
                if old and new:
                    mapping[old] = new
    return mapping

class TokenizerProcessor:
    def __init__(self, mapping):
        self.mapping = mapping
        self.token_pattern = re.compile(r'''
            (?P<INCLUDE>^\s*\#\s*include.*)|            
            (?P<COMMENT>//.*?$|/\*[\s\S]*?\*/)|         
            (?P<STRING>"[^"\\]*(?:\\.[^"\\]*)*")|       
            (?P<CHAR>\'[^\'\\]*(?:\\.[^\'\\]*)*\')|     
            (?P<CLASS_DEF>\b(?P<cls_type>class|struct)\s+(?P<cls_name>\w+))| 
            (?P<SCOPE>::)|                              
            (?P<TILDE>~)|                               
            (?P<IDENTIFIER>\b\w+\b)|                    
            (?P<SYMBOL>[{};])|                          
            (?P<NEWLINE>\n)                             
        ''', re.MULTILINE | re.VERBOSE)

    def process_file(self, file_path):
        """
        I/O 包装器：读取文件并调用核心处理逻辑
        """
        try:
            with open(file_path, 'r', encoding='utf-8', errors='replace') as f:
                content = f.read()
            return self.process_content(content)
        except Exception as e:
            print(f"Error reading {file_path}: {e}")
            return None

    def process_content(self, content):
        """
        核心逻辑：纯内存操作，输入字符串，输出处理后的字符串
        """
        output = []
        last_pos = 0
        brace_level = 0
        
        # 闭合栈: 存储待闭合的命名空间信息
        # 结构: {'level': int (创建时的层级), 'ns_parts': list (命名空间片段), 'raw_ns': str}
        closing_stack = []

        # 活跃命名空间列表 (用于判断当前是否已在某个命名空间内)
        # 结构: ['System::OS', 'Math::Geo']
        active_namespaces = []

        prev_token_type = None

        for match in self.token_pattern.finditer(content):
            # 1. 补全上次匹配位置到当前位置之间的内容（通常是空格、未捕获的符号等）
            output.append(content[last_pos:match.start()])
            last_pos = match.end()

            kind = match.lastgroup
            text = match.group()

            # --- 处理包含 ---
            if kind == 'INCLUDE':
                output.append(text)

            # --- 处理注释/字符串/字符/换行 (保持原样) ---
            elif kind in ['COMMENT', 'STRING', 'CHAR', 'NEWLINE']:
                output.append(text)

            # --- 处理类/结构体定义 ---
            elif kind == 'CLASS_DEF':
                cls_name = match.group('cls_name')
                cls_type = match.group('cls_type') # class 或 struct
                
                if cls_name in self.mapping:
                    target_ns = self.mapping[cls_name]
                    parts = target_ns.split('::')
                    
                    # 生成: namespace System { namespace OS {
                    ns_open = " ".join([f"namespace {p} {{" for p in parts])
                    
                    # 写入: namespace ... { class MyClass
                    output.append(f"{ns_open} {cls_type} {cls_name}")
                    
                    # 入栈记录，等待遇到同层级的 ';' 时闭合
                    closing_stack.append({
                        'level': brace_level, 
                        'ns_parts': parts,
                        'raw_ns': target_ns
                    })
                    active_namespaces.append(target_ns)
                else:
                    output.append(text)

            # --- 处理符号 ---
            elif kind == 'SYMBOL':
                output.append(text)
                
                if text == '{':
                    brace_level += 1
                elif text == '}':
                    brace_level -= 1
                elif text == ';':
                    # 检查是否需要闭合命名空间
                    # 只有当当前的 brace_level 回到了创建命名空间时的 level 时，才说明这个类定义结束了
                    if closing_stack:
                        top = closing_stack[-1]
                        if brace_level == top['level']:
                            # 生成闭合括号: } }
                            ns_close = " ".join(["}" for _ in range(len(top['ns_parts']))])
                            # 添加注释方便阅读: } // namespace System::OS
                            output.append(f" {ns_close} // namespace {top['raw_ns']}")
                            
                            closing_stack.pop()
                            active_namespaces.pop()

            # --- 处理标识符 (替换引用) ---
            elif kind == 'IDENTIFIER':
                if text in self.mapping:
                    target_ns = self.mapping[text]
                    
                    # 判断 1: 是否是 MyClass::StaticFunc 或 ~MyClass
                    is_scoped_or_destructor = (prev_token_type in ['SCOPE', 'TILDE'])
                    
                    # 判断 2: 当前代码是否已经处于该命名空间内部
                    # 例如在 namespace System { ... } 内部使用 System 里的类不需要加前缀
                    is_inside_ns = (target_ns in active_namespaces)

                    if is_scoped_or_destructor or is_inside_ns:
                        # 保持原样
                        output.append(text)
                    else:
                        # 替换为全限定名: System::OS::MyClass
                        output.append(f"{target_ns}::{text}")
                else:
                    output.append(text)
            
            # --- 其他 Token (SCOPE, TILDE) ---
            else:
                output.append(text)

            # 更新 prev_token_type，用于下一次循环判断上下文
            # 注意：跳过 NEWLINE/COMMENT/WHITESPACE，因为它们不影响语法逻辑
            if kind not in ['NEWLINE', 'COMMENT', 'STRING', 'CHAR']:
                prev_token_type = kind

        # 补全最后剩余的内容
        output.append(content[last_pos:])
        
        return "".join(output)

def main():
    parser = argparse.ArgumentParser(description="Batch replace namespaces or tokens.")
    parser.add_argument("directory", help="Target directory path")
    parser.add_argument("csv_file", help="CSV mapping file path")
    args = parser.parse_args()

    target_dir = args.directory
    csv_file = args.csv_file

    if not os.path.exists(target_dir):
        print(f"Error: Directory '{target_dir}' not found.")
        return
    if not os.path.exists(csv_file):
        print(f"Error: CSV file '{csv_file}' not found.")
        return

    # 加载映射规则
    try:
        # 假设 load_mapping 是现有的函数
        mapping = load_mapping(csv_file) 
        print(f"Loaded {len(mapping)} renaming rules.")
    except Exception as e:
        print(f"Error loading mapping: {e}")
        return

    # 初始化处理器
    try:
        processor = TokenizerProcessor(mapping)
    except NameError:
        print("Error: TokenizerProcessor class is not defined (please ensure imports are correct).")
        return

    count_modified = 0
    count_scanned = 0
    start_time = time.time()

    print(f"Scanning '{target_dir}' ...")

    try:
        for root, dirs, files in os.walk(target_dir):
            # 过滤掉隐藏目录（如 .git）
            dirs[:] = [d for d in dirs if not d.startswith('.')]

            for file in files:
                # 检查后缀 (O(1) 复杂度)
                if os.path.splitext(file)[1].lower() not in EXTENSIONS:
                    continue

                path = os.path.join(root, file)
                count_scanned += 1

                try:
                    with open(path, 'r', encoding='utf-8', errors='replace') as f:
                        original_content = f.read()

                    if hasattr(processor, 'process_content'):
                        new_content = processor.process_content(original_content)
                    else:
                        # 兼容旧接口：如果必须传 path，也没办法，但外部已经省了一次读取
                        new_content = processor.process_file(path)

                    # 5. 对比与写入
                    if new_content != original_content:
                        # 只有内容真正变了才写入
                        with open(path, 'w', encoding='utf-8', newline='') as f:
                            f.write(new_content)
                        
                        print(f"Modified: {file}")
                        count_modified += 1
                    else:
                        # 仅用于调试，平时可注释掉
                        # print(f"Skipped: {file} (No changes)")
                        pass

                except UnicodeDecodeError:
                    print(f"Warning: Skipping binary or non-utf8 file: {path}")
                except Exception as e:
                    print(f"Error processing {path}: {e}")

    except KeyboardInterrupt:
        print("\n\nAborted by user.")
    
    elapsed = time.time() - start_time
    print("-" * 40)
    print(f"Done in {elapsed:.2f}s.")
    print(f"Scanned: {count_scanned} files.")
    print(f"Modified: {count_modified} files.")

if __name__ == "__main__":
    main()
