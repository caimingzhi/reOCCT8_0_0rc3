import os
import sys
import argparse
import re

def clean_project(psv_file, root_dir, is_dry_run):
    print(f"工作目录: {os.path.abspath(root_dir)}")
    print(f"读取清单: {psv_file}")
    if is_dry_run:
        print("--- 模式: Dry Run (仅模拟，不删除任何文件) ---")
    else:
        print("--- 模式: EXECUTE (将执行删除和修改) ---")

    # 1. 读取 PSV，找出需要删除的文件
    files_to_delete = []
    
    try:
        with open(psv_file, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            # 跳过表头
            if lines and "HPP_File" in lines[0]:
                lines = lines[1:]
            
            for line in lines:
                line = line.strip()
                if not line: continue
                
                parts = line.split('|')
                if len(parts) < 2: continue
                
                hpp_path = parts[0].strip()
                refs = parts[1].strip()
                
                # 如果引用列表为空，标记为删除
                if not refs:
                    files_to_delete.append(hpp_path)
    except Exception as e:
        print(f"读取 PSV 文件失败: {e}")
        return

    if not files_to_delete:
        print("没有发现未被引用的文件，无需操作。")
        return

    print(f"发现 {len(files_to_delete)} 个未使用的 HPP 文件。")

    # 2. 删除文件
    deleted_filenames = set() # 记录文件名，用于修改 Makefile
    
    for rel_path in files_to_delete:
        full_path = os.path.join(root_dir, rel_path)
        filename = os.path.basename(rel_path)
        
        if is_dry_run:
            print(f"[模拟删除] {full_path}")
            deleted_filenames.add(filename)
        else:
            try:
                if os.path.exists(full_path):
                    os.remove(full_path)
                    print(f"[已删除] {full_path}")
                    deleted_filenames.add(filename)
                else:
                    print(f"[文件不存在] {full_path}")
            except Exception as e:
                print(f"[删除失败] {full_path} : {e}")

    # 3. 修改 Makefile
    # 查找目录下所有的 Makefile (包括 Makefile, makefile, Makefile.in, Makefile.am 等)
    print("\n正在扫描并修改 Makefile ...")
    
    makefile_names = []
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            # 匹配规则：文件名包含 Makefile (忽略大小写)
            if "file" in file.lower():
                makefile_names.append(os.path.join(root, file))

    count_modified_makefiles = 0

    for mk_path in makefile_names:
        try:
            with open(mk_path, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            original_content = content
            is_changed = False
            
            # 遍历所有被删的文件名，从 Makefile 内容中移除
            for del_file in deleted_filenames:
                # 正则解释：
                # \b : 单词边界，确保不会把 SomeFile.hpp 里的 File.hpp 删掉
                # re.escape : 确保 .hpp 中的点被当做普通字符
                # 替换为空字符串
                pattern = r'\b' + re.escape(del_file) + r'\b'
                
                # 检查是否存在，减少不必要的正则操作
                if del_file in content:
                    # 执行替换
                    content = re.sub(pattern, '', content)
                    is_changed = True
            
            if is_changed:
                print(f"[{'模拟修改' if is_dry_run else '修改'}] {mk_path}")
                if not is_dry_run:
                    with open(mk_path, 'w', encoding='utf-8') as f:
                        f.write(content)
                count_modified_makefiles += 1
                
        except Exception as e:
            print(f"处理 Makefile 失败: {mk_path} - {e}")

    print("\n--- 完成 ---")
    print(f"需删除文件数: {len(files_to_delete)}")
    print(f"涉及 Makefile 数: {count_modified_makefiles}")
    if is_dry_run:
        print("提示: 当前为模拟模式。请添加 --run 参数来执行实际操作。")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="删除未引用的HPP文件并清理Makefile")
    parser.add_argument("psv_file", help="输入文件 (上一步生成的PSV)")
    parser.add_argument("root_dir", help="项目根目录 (必须与生成PSV时的目录一致)")
    parser.add_argument("--run", action="store_true", help="执行实际删除操作 (默认只模拟)")
    
    args = parser.parse_args()
    
    # 如果没加 --run，默认 is_dry_run = True
    is_dry_run = not args.run
    
    if not os.path.exists(args.root_dir):
        print("错误: 项目目录不存在")
    elif not os.path.exists(args.psv_file):
        print("错误: PSV文件不存在")
    else:
        clean_project(args.psv_file, args.root_dir, is_dry_run)
