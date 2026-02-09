import sys
import os
import csv
import logging
import traceback
import clang.cindex
from clang.cindex import CursorKind, TokenKind, TranslationUnit

# ================= 配置区域 =================
# 如果系统找不到 libclang，请取消下面注释并手动指定 bin 目录
# clang.cindex.Config.set_library_path(r'C:\Program Files\LLVM\bin')

EXTENSIONS = {'.cxx', '.hpp', '.cpp', '.h', '.cc', '.c'}
# ===========================================

def setup_logging(log_file):
    """配置日志系统，同时输出到控制台和文件"""
    logger = logging.getLogger()
    logger.setLevel(logging.DEBUG)
    
    # 格式：时间 - 级别 - 消息
    formatter = logging.Formatter('%(asctime)s [%(levelname)s] %(message)s')

    # 文件输出 (记录详细错误)
    fh = logging.FileHandler(log_file, mode='w', encoding='utf-8')
    fh.setLevel(logging.DEBUG)
    fh.setFormatter(formatter)
    logger.addHandler(fh)

    # 控制台输出 (记录主要进度)
    ch = logging.StreamHandler()
    ch.setLevel(logging.INFO)
    ch.setFormatter(logging.Formatter('%(message)s'))
    logger.addHandler(ch)

    return logger

def load_mapping(csv_file):
    mapping = {}
    try:
        with open(csv_file, 'r', encoding='utf-8') as f:
            reader = csv.reader(f)
            for row in reader:
                if len(row) >= 2:
                    cls_name = row[0].strip()
                    ns_name = row[1].strip()
                    if cls_name and ns_name:
                        mapping[cls_name] = ns_name
    except Exception as e:
        logging.error(f"Failed to load CSV mapping: {e}")
        sys.exit(1)
    return mapping

def generate_namespace_wrappers_bytes(namespace_str):
    parts = namespace_str.split('::')
    prefix = " ".join([f"namespace {p} {{" for p in parts])
    suffix = " ".join(["}" for _ in parts])
    comment = f" // namespace {namespace_str}"
    return (f"\n{prefix}\n".encode('utf-8'), f"\n{suffix}{comment}\n".encode('utf-8'))

class FileRefactor:
    def __init__(self, file_path, mapping):
        self.file_path = file_path
        self.abs_file_path = os.path.abspath(file_path)
        self.mapping = mapping
        self.replacements = [] 
        self.content_bytes = b""
        self.protected_offsets = [] 
        self.protected_lines = set()

    def _identify_pp_lines(self):
        lines = self.content_bytes.split(b'\n')
        is_multiline_pp = False
        for i, line in enumerate(lines):
            stripped = line.strip()
            if stripped.startswith(b'#') or is_multiline_pp:
                self.protected_lines.add(i + 1)
                is_multiline_pp = stripped.endswith(b'\\')
            else:
                is_multiline_pp = False

    def process(self):
        try:
            with open(self.file_path, 'rb') as f:
                self.content_bytes = f.read()
        except Exception as e:
            logging.error(f"Cannot read file {self.file_path}: {e}")
            return False

        self._identify_pp_lines()

        index = clang.cindex.Index.create()
        try:
            # 解析设置
            tu = index.parse(self.file_path, args=['-std=c++17', '-I.'], 
                             options=TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
            
            if not tu:
                logging.error(f"Clang failed to create translation unit for {self.file_path}")
                return False

            # 打印 Clang 的诊断信息（即使解析成功也可能有警告）
            for diag in tu.diagnostics:
                if diag.severity >= clang.cindex.Diagnostic.Error:
                    logging.debug(f"Clang Diagnostic in {self.file_path} [{diag.location}]: {diag.spelling}")

        except Exception as e:
            logging.error(f"Exception during Clang parsing for {self.file_path}: {e}")
            logging.debug(traceback.format_exc())
            return False

        # 1. 扫描 AST
        try:
            self.scan_ast_recursive(tu.cursor)
            # 2. 扫描 Token
            self.scan_tokens(tu)
            # 3. 应用修改
            return self.apply_changes()
        except Exception as e:
            logging.error(f"Logic error while processing {self.file_path}: {e}")
            logging.debug(traceback.format_exc())
            return False

    def scan_ast_recursive(self, cursor):
        if cursor.kind != CursorKind.TRANSLATION_UNIT:
            if cursor.location.file is None or os.path.abspath(cursor.location.file.name) != self.abs_file_path:
                return
        if cursor.kind == CursorKind.STRING_LITERAL:
            self.protected_offsets.append((cursor.extent.start.offset, cursor.extent.end.offset))
            return
        if cursor.kind in [CursorKind.CLASS_DECL, CursorKind.STRUCT_DECL]:
            if cursor.spelling in self.mapping:
                self.handle_class_decl(cursor)
        for child in cursor.get_children():
            self.scan_ast_recursive(child)

    def handle_class_decl(self, cursor):
        is_wrap = False
        if cursor.is_definition():
            is_wrap = True
        else:
            parent = cursor.lexical_parent
            if parent and parent.kind in [CursorKind.TRANSLATION_UNIT, CursorKind.NAMESPACE, 
                                          CursorKind.CLASS_DECL, CursorKind.STRUCT_DECL]:
                is_wrap = True
        if is_wrap:
            self.protected_offsets.append((cursor.extent.start.offset, cursor.extent.end.offset))
            self.add_wrapper(cursor)

    def scan_tokens(self, tu):
        tokens = tu.cursor.get_tokens()
        prev_token = None
        for token in tokens:
            if token.location.file is None or os.path.abspath(token.location.file.name) != self.abs_file_path:
                continue
            if token.location.line in self.protected_lines:
                prev_token = token
                continue
            if any(s <= token.location.offset < e for s, e in self.protected_offsets):
                prev_token = token
                continue
            if token.kind == TokenKind.IDENTIFIER and token.spelling in self.mapping:
                if prev_token and prev_token.spelling in ['::', '~']:
                    prev_token = token
                    continue
                self.add_prefix(token)
            prev_token = token

    def add_wrapper(self, cursor):
        target_ns = self.mapping[cursor.spelling]
        prefix_bytes, suffix_bytes = generate_namespace_wrappers_bytes(target_ns)
        start, end = cursor.extent.start.offset, cursor.extent.end.offset
        limit = min(end + 200, len(self.content_bytes))
        scan_pos = end
        while scan_pos < limit:
            if self.content_bytes[scan_pos] == 59:
                scan_pos += 1
                break
            elif self.content_bytes[scan_pos] not in (9, 10, 13, 32): break
            scan_pos += 1
        self.replacements.append((start, 0, prefix_bytes))
        self.replacements.append((scan_pos, 0, suffix_bytes))

    def add_prefix(self, token):
        target_ns = self.mapping[token.spelling]
        start = token.location.offset
        length = len(token.spelling.encode('utf-8'))
        new_bytes = f"{target_ns}::{token.spelling}".encode('utf-8')
        self.replacements.append((start, length, new_bytes))

    def apply_changes(self):
        if not self.replacements: return False
        self.replacements.sort(key=lambda x: x[0], reverse=True)
        unique = []
        seen = set()
        for r in self.replacements:
            if r[0] not in seen:
                unique.append(r)
                seen.add(r[0])
        new_content = bytearray(self.content_bytes)
        for offset, length, text_bytes in unique:
            new_content[offset : offset + length] = text_bytes
        if new_content != self.content_bytes:
            with open(self.file_path, 'wb') as f:
                f.write(new_content)
            return True
        return False

def main():
    if len(sys.argv) < 4:
        print("Usage: python script.py <src_dir> <mapping.csv> <log_file>")
        return
    
    src_dir, csv_file, log_file = sys.argv[1], sys.argv[2], sys.argv[3]
    
    logger = setup_logging(log_file)
    logger.info(f"Refactor Start. Mapping: {csv_file}")
    
    mapping = load_mapping(csv_file)
    logger.info(f"Loaded {len(mapping)} renaming rules.")

    modified_count = 0
    error_count = 0
    total_scanned = 0

    for root, dirs, files in os.walk(src_dir):
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        for file in files:
            if os.path.splitext(file)[1].lower() in EXTENSIONS:
                total_scanned += 1
                path = os.path.join(root, file)
                
                # 实时进度反馈到控制台
                print(f"Scanned: {total_scanned} | Modified: {modified_count} | Errors: {error_count}", end='\r')
                
                refactor = FileRefactor(path, mapping)
                try:
                    success = refactor.process()
                    if success:
                        modified_count += 1
                        logger.info(f"[SUCCESS] Modified: {path}")
                except Exception:
                    error_count += 1
                    logger.error(f"[CRITICAL] Unexpected crash on {path}")
                    logger.debug(traceback.format_exc())

    logger.info("\n" + "="*40)
    logger.info(f"Refactor Finished.")
    logger.info(f"Total Scanned: {total_scanned}")
    logger.info(f"Total Modified: {modified_count}")
    logger.info(f"Total Errors: {error_count}")
    logger.info(f"Full log saved to: {log_file}")
    logger.info("="*40)

if __name__ == "__main__":
    main()
