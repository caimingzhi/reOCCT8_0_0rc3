import os
import sys
import subprocess
import shutil
import time

# 定义需要格式化的文件后缀
TARGET_EXTENSIONS = ('.cxx', '.hpp', '.cpp', '.c', '.cc', '.h', '.hxx', '.cu')

def check_clang_format_installed():
    """检查系统是否安装了 clang-format"""
    return shutil.which("clang-format") is not None

def format_file(file_path):
    """
    格式化单个文件
    """
    try:
        # -i: 直接修改文件
        # -style=file: 使用目录层级中最近的 .clang-format 文件配置
        cmd = ['clang-format', '-i', '-style=file', file_path]
        
        # 运行命令，check=True 会在返回非 0 状态码时抛出异常
        subprocess.run(cmd, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return True, None
    except subprocess.CalledProcessError as e:
        return False, e.stderr.decode('utf-8', errors='ignore').strip()
    except Exception as e:
        return False, str(e)

def main(root_dir):
    if not check_clang_format_installed():
        print("错误: 未找到 'clang-format'。请检查环境变量。")
        return

    # 1. 先收集所有文件路径，以便计算总进度
    print(f"正在扫描目录: {root_dir} ...")
    files_to_format = []
    
    for root, dirs, files in os.walk(root_dir):
        # 忽略 .git 等隐藏目录
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        
        for file in files:
            if file.lower().endswith(TARGET_EXTENSIONS):
                files_to_format.append(os.path.join(root, file))

    total_files = len(files_to_format)
    if total_files == 0:
        print("未找到需要格式化的源码文件。")
        return

    print(f"找到 {total_files} 个文件，开始顺序格式化...")
    print("-" * 50)

    success_count = 0
    fail_count = 0
    errors = []

    # 2. 顺序处理循环
    try:
        for index, file_path in enumerate(files_to_format):
            # 计算百分比
            percent = (index + 1) / total_files * 100
            
            # 打印进度条 (覆盖当前行，避免刷屏)
            # end='\r' 让光标回到行首
            print(f"[{index + 1}/{total_files}] {percent:.1f}% 处理中: {os.path.basename(file_path)}", end='\r')
            
            is_success, msg = format_file(file_path)
            
            if is_success:
                success_count += 1
            else:
                fail_count += 1
                # 记录错误文件，稍后统一打印
                errors.append(f"{file_path} -> {msg}")
                
    except KeyboardInterrupt:
        print("\n\n用户手动停止脚本。")
    
    # 3. 结果汇总
    print("\n" + "-" * 50)
    print("处理结束！")
    print(f"成功: {success_count}")
    print(f"失败: {fail_count}")

    if fail_count > 0:
        print("\n以下文件格式化失败:")
        for err in errors[:20]: # 只显示前20个错误，避免刷屏
            print(err)
        if len(errors) > 20:
            print(f"... 以及其他 {len(errors) - 20} 个错误。")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("用法: python format_code_single.py <目标目录>")
    else:
        target_dir = sys.argv[1]
        if os.path.exists(target_dir):
            main(target_dir)
        else:
            print("错误: 目录不存在。")
