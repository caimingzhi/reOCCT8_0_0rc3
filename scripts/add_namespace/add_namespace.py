import os
import csv
import re
import sys

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
        # 修正正则：给 class/struct 关键字加上了组名 ?P<cls_type>
        self.token_pattern = re.compile(
            r'(?P<INCLUDE>^\s*#\s*include.*)|'          
            r'(?P<COMMENT>//.*|/\*[\s\S]*?\*/)|'        
            r'(?P<STRING>"[^"\\]*(?:\\.[^"\\]*)*")|'    
            r'(?P<CHAR>\'[^\'\\]*(?:\\.[^\'\\]*)*\')|'  
            r'(?P<CLASS_DEF>\b(?P<cls_type>class|struct)\s+(?P<cls_name>\w+))|' # 修复点在此
            r'(?P<SCOPE>::)|'                           
            r'(?P<TILDE>~)|'                            
            r'(?P<IDENTIFIER>\b\w+\b)|'                 
            r'(?P<SYMBOL>[{};])|'                       
            r'(?P<NEWLINE>\n)',                         
            re.MULTILINE
        )

    def process_file(self, file_path):
        # 使用二进制读取再解码，防止某些特殊字符导致偏移量计算错误，虽然在这里主要靠正则
        with open(file_path, 'r', encoding='utf-8', errors='replace') as f:
            content = f.read()

        output = []
        last_pos = 0
        brace_level = 0
        
        # 闭合栈：{'level': int, 'ns': str, 'parts_count': int}
        closing_stack = []

        # 活跃命名空间栈：['System', 'OS']
        active_namespaces = []

        prev_token_type = None

        for match in self.token_pattern.finditer(content):
            output.append(content[last_pos:match.start()])
            last_pos = match.end()

            kind = match.lastgroup
            text = match.group()

            if kind == 'INCLUDE':
                output.append(text) 

            elif kind in ['COMMENT', 'STRING', 'CHAR', 'NEWLINE']:
                output.append(text) 

            elif kind == 'CLASS_DEF':
                cls_name = match.group('cls_name')
                # 修复：直接使用组名获取 class 或 struct，不再使用数字索引
                keyword = match.group('cls_type') 
                
                if cls_name in self.mapping:
                    target_ns = self.mapping[cls_name]
                    
                    parts = target_ns.split('::')
                    ns_open = " ".join([f"namespace {p} {{" for p in parts])
                    
                    # 写入：namespace System { namespace OS { class OSD
                    output.append(f"{ns_open} {keyword} {cls_name}")
                    
                    closing_stack.append({
                        'level': brace_level, 
                        'ns': target_ns,
                        'parts_count': len(parts)
                    })
                    active_namespaces.append(target_ns)
                else:
                    output.append(text)

            elif kind == 'SYMBOL':
                output.append(text)
                if text == '{':
                    brace_level += 1
                elif text == '}':
                    brace_level -= 1
                elif text == ';':
                    # 闭合逻辑
                    if closing_stack:
                        top = closing_stack[-1]
                        if brace_level == top['level']:
                            ns_close = " ".join(["}" for _ in range(top['parts_count'])])
                            # 写入：} // namespace System::OS
                            output.append(f" {ns_close} // namespace {top['ns']}")
                            
                            closing_stack.pop()
                            active_namespaces.pop()

            elif kind == 'IDENTIFIER':
                if text in self.mapping:
                    target_ns = self.mapping[text]
                    
                    # 1. 前面有 :: 或 ~ 则不处理
                    is_scoped = (prev_token_type in ['SCOPE', 'TILDE'])
                    
                    # 2. 如果当前已经在该命名空间内部（构造函数/成员引用），也不处理
                    # active_namespaces 里存的是 'System::OS' 这种全名
                    is_inside_ns = (target_ns in active_namespaces)

                    if is_scoped or is_inside_ns:
                        output.append(text)
                    else:
                        # 外部引用，加前缀
                        output.append(f"{target_ns}::{text}")
                else:
                    output.append(text)
            
            elif kind in ['SCOPE', 'TILDE']:
                output.append(text)
            
            else:
                output.append(text)

            if kind not in ['NEWLINE', 'COMMENT', 'STRING', 'CHAR']:
                prev_token_type = kind

        output.append(content[last_pos:])
        return "".join(output)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python add_namespace.py <directory_path> <csv_file>")
    else:
        target_dir = sys.argv[1]
        csv_file = sys.argv[2]

    if not os.path.exists(csv_file):
        print(f"Error: {csv_file} not found.")
        return

    mapping = load_mapping(csv_file)
    print(f"Loaded {len(mapping)} renaming rules.")
    
    processor = TokenizerProcessor(mapping)
    
    count = 0
    for root, dirs, files in os.walk(target_dir):
        for file in files:
            if os.path.splitext(file)[1] not in EXTENSIONS:
                continue
            
            path = os.path.join(root, file)
            # 简单过滤
            try:
                with open(path, 'r', encoding='utf-8') as f:
                    if not any(k in f.read() for k in mapping):
                        continue
            except: continue

            print(f"Processing {file} ...")
            try:
                new_content = processor.process_file(path)
                
                with open(path, 'r', encoding='utf-8') as f:
                    old = f.read()
                
                if new_content != old:
                    with open(path, 'w', encoding='utf-8', newline='') as f:
                        f.write(new_content)
                    print("  -> Modified.")
                    count += 1
            except Exception as e:
                print(f"  [!] Error: {e}")

    print(f"Done. Modified {count} files.")
