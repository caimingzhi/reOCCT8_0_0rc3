import os
import sys
import argparse
import re

def get_files_cmake_path(hpp_abs_path):
    """
    根据HPP文件的绝对路径，推断该包的FILES文件路径。
    """
    dir_path = os.path.dirname(hpp_abs_path)
    files_path = os.path.join(dir_path, "FILES")
    return files_path

def update_files_cmake(files_cmake_path, filename_to_remove, is_dry_run):
    """
    从FILES列表中移除指定文件名
    """
    if not os.path.exists(files_cmake_path):
        return False

    try:
        with open(files_cmake_path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
        
        new_lines = []
        removed = False
        target = filename_to_remove.strip()
        
        for line in lines:
            if line.strip() == target:
                removed = True
                continue
            new_lines.append(line)
            
        if removed:
            if not is_dry_run:
                with open(files_cmake_path, 'w', encoding='utf-8') as f:
                    f.writelines(new_lines)
            print(f"    [Build] 从 FILES 移除: {target}")
            return True
    except Exception as e:
        print(f"    [Error] 修改 FILES 失败: {e}")
        return False

def process_inline_recursive(psv_file, root_dir, is_dry_run):
    root_dir = os.path.abspath(root_dir)
    print(f"工作目录: {root_dir}")
    
    # --- 1. 构建任务字典 ---
    # 结构: { "src/Package/Child.hpp": "src/Package/Parent.hpp" }
    pending_tasks = {}
    
    with open(psv_file, 'r', encoding='utf-8') as f:
        lines = f.readlines()
        if lines and "HPP_File" in lines[0]:
            lines = lines[1:]
        
        for line in lines:
            parts = line.split('|')
            if len(parts) < 2: continue
            
            child_rel = parts[0].strip()
            refs_str = parts[1].strip()
            if not refs_str: continue
            
            refs = refs_str.split(',')
            
            # 筛选条件：被唯一引用，且引用者也是hpp
            if len(refs) == 1:
                parent_rel = refs[0].strip()
                if parent_rel.endswith('.hpp'):
                    # 存入字典，Key是子文件，Value是父文件
                    pending_tasks[child_rel] = parent_rel

    print(f"初始任务队列: {len(pending_tasks)} 个待合并文件")
    
    if is_dry_run:
        print("--- DRY RUN (模拟模式) ---")
    else:
        print("--- EXECUTE (执行模式) ---")

    success_count = 0

    # --- 2. 动态循环处理 ---
    # 我们不能简单遍历，因为字典在处理过程中会发生逻辑变化
    while pending_tasks:
        # 弹出一个任务 (Child -> Parent)
        # popitem() 在 Python 3.7+ 遵循插入顺序，但这里顺序其实不重要，因为我们有重定向机制
        current_child, current_parent = pending_tasks.popitem()
        
        child_abs = os.path.join(root_dir, current_child)
        parent_abs = os.path.join(root_dir, current_parent)
        child_filename = os.path.basename(current_child)

        print(f"\n[处理任务] {child_filename} \n      --> 归并入: {current_parent}")

        # 检查文件是否存在
        if not os.path.exists(child_abs):
            print(f"    [Error] 子文件缺失: {current_child} (可能已被错误删除?)")
            continue
        if not os.path.exists(parent_abs):
            print(f"    [Error] 父文件缺失: {current_parent}")
            continue

        # --- A. 执行合并逻辑 ---
        merged = False
        try:
            # 读取内容
            with open(child_abs, 'r', encoding='utf-8', errors='ignore') as f:
                child_content = f.read()
            with open(parent_abs, 'r', encoding='utf-8', errors='ignore') as f:
                parent_content = f.read()

            # 确保子内容末尾有换行
            if not child_content.endswith('\n'):
                child_content += '\n'

            # 匹配 include 语句
            pattern = r'^\s*#\s*include\s+["<]' + re.escape(child_filename) + r'[">].*$'
            match = re.search(pattern, parent_content, re.MULTILINE)
            
            if match:
                # 替换
                new_parent_content = re.sub(pattern, lambda x: child_content, parent_content, count=1, flags=re.MULTILINE)
                
                if not is_dry_run:
                    with open(parent_abs, 'w', encoding='utf-8') as f:
                        f.write(new_parent_content)
                print(f"    [Merge] 代码合并成功")
                merged = True
            else:
                print(f"    [Error] 在父文件中没找到 #include \"{child_filename}\"")
                # 即使没找到，为了防止死循环，我们也不把任务放回去了
                # 但这意味着我们不能安全删除子文件

        except Exception as e:
            print(f"    [Error] 文件操作异常: {e}")
            continue

        # --- B. 只有合并成功才继续后续清理 ---
        if merged:
            # 1. 清理 FILES
            files_cmake = get_files_cmake_path(child_abs)
            update_files_cmake(files_cmake, child_filename, is_dry_run)

            # 2. 删除子文件
            if not is_dry_run:
                try:
                    os.remove(child_abs)
                    print(f"    [Delete] 删除源文件")
                except Exception as e:
                    print(f"    [Delete Failed] {e}")

            success_count += 1

            # --- C. 核心逻辑：动态更新剩余任务 (重定向) ---
            # 场景：我们刚刚把 B 合并进了 A，并删除了 B。
            # 如果待处理列表中还有 "C -> B" (C 依赖 B)，现在 B 没了，C 应该依赖 A。
            # 因为 B 的内容（包括 include "C"）现在已经在 A 里了。
            
            # 这里的 current_child 就是 B，current_parent 就是 A
            # 我们要找所有 value == current_child 的项，把 value 改成 current_parent
            
            redirect_count = 0
            # 注意：不能在迭代字典时修改字典，所以用 list 包一层
            for child_key, parent_val in list(pending_tasks.items()):
                if parent_val == current_child:
                    # 更新父节点指向
                    pending_tasks[child_key] = current_parent
                    redirect_count += 1
            
            if redirect_count > 0:
                print(f"    [Update] 发现 {redirect_count} 个文件原本依赖 {child_filename}，现已重定向依赖到 {os.path.basename(current_parent)}")

    print(f"\n全部完成。共成功合并 {success_count} 个文件。")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="递归合并单引用HPP文件")
    parser.add_argument("psv_file", help="输入PSV文件")
    parser.add_argument("root_dir", help="OCCT源码根目录 (src)")
    parser.add_argument("--run", action="store_true", help="执行修改")
    
    args = parser.parse_args()
    
    if not os.path.isdir(args.root_dir):
        print("错误: 目录不存在")
    else:
        process_inline_recursive(args.psv_file, args.root_dir, args.run)
