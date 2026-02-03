import os
import re
import argparse
import sys
from collections import defaultdict

def scan_files(root_dir, output_file):
    # 将 root_dir 转换为绝对路径，方便计算相对路径
    root_dir = os.path.abspath(root_dir)
    print(f"正在扫描目录: {root_dir} ...")
    
    # 数据结构定义：
    # 1. hpp_map: { "B.hpp": ["src/Package1/B.hpp", "src/Package2/B.hpp"] }
    #    作用：通过 include 的文件名，反查出它在磁盘上的具体路径（可能存在重名文件，所以用 list）
    hpp_map = defaultdict(list)
    
    # 2. hpp_refs: { "src/Package1/B.hpp": {"src/Main.cpp", ...} }
    #    作用：记录每个具体路径的hpp文件，被哪些文件引用了
    hpp_refs = defaultdict(set)
    
    # 3. files_to_scan: 存储需要读取内容的源文件路径
    files_to_scan = []
    
    # --- 第一步：建立索引 ---
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            abs_path = os.path.join(root, file)
            # 计算相对路径，输出时更清爽
            rel_path = os.path.relpath(abs_path, root_dir)
            
            # 统一转小写判断后缀，但存储保留原文件名
            ext = os.path.splitext(file)[1].lower()
            
            # 如果是 HPP 文件，记录它的位置
            if ext == '.hpp':
                hpp_map[file].append(rel_path)
                # 初始化引用集合，确保即使没被引用的hpp也能出现在输出中
                hpp_refs[rel_path] = set()
            
            # 定义需要扫描内容的文件类型
            valid_exts = ('.cpp', '.cxx', '.c', '.cc', '.hpp', '.hxx', '.h', '.lxx', '.gxx', '.mm')
            if ext in valid_exts:
                files_to_scan.append(rel_path)

    print(f"索引建立完成：")
    print(f"  - 发现 {len(hpp_refs)} 个唯一的 .hpp 路径")
    print(f"  - 涉及 {len(hpp_map)} 个 .hpp 文件名")
    print(f"  - 准备扫描 {len(files_to_scan)} 个源文件...")

    # --- 第二步：正则匹配 ---
    # 匹配 #include <...> 或 "..."，提取文件名
    include_pattern = re.compile(r'^\s*#\s*include\s+["<]([^">]+)[">]', re.MULTILINE)

    # --- 第三步：扫描内容 ---
    processed_count = 0
    total_files = len(files_to_scan)

    for source_rel_path in files_to_scan:
        processed_count += 1
        if processed_count % 100 == 0:
            sys.stdout.write(f"\r进度: {processed_count}/{total_files}")
            sys.stdout.flush()

        source_abs_path = os.path.join(root_dir, source_rel_path)

        try:
            with open(source_abs_path, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
                includes = include_pattern.findall(content)
                
                for inc_path_str in includes:
                    # 从 include 字符串中提取文件名 (如 "Package/Class.hpp" -> "Class.hpp")
                    inc_filename = os.path.basename(inc_path_str)
                    
                    # 查找这个文件名是否在我们的 hpp_map 中
                    if inc_filename in hpp_map:
                        # 获取该文件名对应的所有真实路径
                        # 注意：如果项目中存在同名 hpp (如 src/A/Def.hpp 和 src/B/Def.hpp)
                        # 且代码里只写了 #include "Def.hpp"，脚本会将两者都标记为被引用。
                        # 这是静态扫描在没有编译器上下文时的最佳策略（宁滥勿缺）。
                        possible_paths = hpp_map[inc_filename]
                        
                        for target_hpp_path in possible_paths:
                            # 避免自己引用自己 (A.hpp include A.hpp)
                            if target_hpp_path != source_rel_path:
                                hpp_refs[target_hpp_path].add(source_rel_path)

        except Exception as e:
            print(f"\n[Error] 读取文件失败: {source_rel_path} - {e}")

    print(f"\n扫描完成。正在写入结果到 {output_file} ...")

    # --- 第四步：输出 PSV ---
    try:
        with open(output_file, 'w', encoding='utf-8') as out:
            # 第一列：HPP 文件的相对路径
            # 第二列：引用了该文件的其他文件列表
            out.write("HPP_File_Path|Included_By_Files\n")
            
            # 按路径字典序排序
            for hpp_path in sorted(hpp_refs.keys()):
                refs = hpp_refs[hpp_path]
                # 列表用逗号分隔，并排序
                ref_str = ",".join(sorted(list(refs)))
                out.write(f"{hpp_path}|{ref_str}\n")
                
        print(f"成功！结果已保存。")
        
    except IOError as e:
        print(f"写入输出文件失败: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="扫描OCCT项目中的HPP引用关系 (输出完整路径)")
    parser.add_argument("target_dir", help="要扫描的根目录路径")
    parser.add_argument("--output", "-o", default="hpp_path_refs.psv", help="输出文件名")
    
    args = parser.parse_args()
    
    if not os.path.isdir(args.target_dir):
        print(f"错误: 目录 '{args.target_dir}' 不存在。")
    else:
        scan_files(args.target_dir, args.output)
