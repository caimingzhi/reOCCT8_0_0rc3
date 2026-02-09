import sys
import os
import clang.cindex

# 配置：如果你的系统找不到 libclang，请在这里手动指定路径
# Windows 示例: clang.cindex.Config.set_library_path('C:/Program Files/LLVM/bin')
# Linux/Mac 通常不需要设置，或者设为 /usr/lib/llvm-x/lib

def remove_comments_from_file(file_path):
    """
    使用 libclang 解析文件并移除注释
    """
    try:
        # 创建索引
        index = clang.cindex.Index.create()
        
        # 解析文件
        # args=['-std=c++17'] 可以根据你的项目标准调整
        tu = index.parse(file_path, args=['-std=c++17'])
        
        # 读取原始文件内容（二进制方式，以免编码问题导致索引对不上）
        with open(file_path, 'rb') as f:
            content = f.read()
        
        # 获取所有 Token
        # extent=tu.cursor.extent 限制在当前文件范围内
        tokens = list(tu.get_tokens(extent=tu.cursor.extent))
        
        # 筛选出注释类型的 Token
        comment_tokens = [t for t in tokens if t.kind == clang.cindex.TokenKind.COMMENT]
        
        if not comment_tokens:
            return False # 没有注释，无需修改

        # 我们必须倒序处理（从文件末尾开始删），
        # 这样删除内容后，前面的索引位置才不会发生偏移。
        comment_tokens.sort(key=lambda x: x.extent.start.offset, reverse=True)
        
        new_content = content
        
        for token in comment_tokens:
            start_byte = token.extent.start.offset
            end_byte = token.extent.end.offset
            
            # 执行删除操作：拼接 start 之前和 end 之后的内容
            # 我们可以选择替换为空，或者替换为一个空格（防止 int a;/*c*/int b; 变成 int a;int b;）
            # 对于行注释 //，通常直接删除即可
            # 对于块注释 /**/，建议替换为一个空格，或者检查是否独立成行
            
            # 这里采用简单策略：直接切除
            new_content = new_content[:start_byte] + new_content[end_byte:]

        # 如果内容有变化，写回文件
        if new_content != content:
            with open(file_path, 'wb') as f:
                f.write(new_content)
            return True
            
    except Exception as e:
        print(f"Error processing {file_path}: {e}")
        return False

    return False

def process_directory(root_dir):
    """
    递归遍历目录
    """
    extensions = ('.cxx', '.hpp')
    count = 0
    
    print(f"Scanning directory: {root_dir} ...")
    
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            if file.lower().endswith(extensions):
                full_path = os.path.join(root, file)
                print(f"Processing: {full_path}", end=" ... ")
                
                if remove_comments_from_file(full_path):
                    print("Cleaned.")
                    count += 1
                else:
                    print("Skipped (No comments/Error).")
                    
    print(f"\nDone! Processed {count} files.")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python clean_comments.py <directory_path>")
    else:
        target_dir = sys.argv[1]
        if os.path.exists(target_dir):
            process_directory(target_dir)
        else:
            print("Error: Directory not found.")
