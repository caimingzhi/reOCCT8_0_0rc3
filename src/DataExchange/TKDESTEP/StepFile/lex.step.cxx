

#if !defined(_MSC_VER) || (_MSC_VER >= 1600)
  #include <cstdint>
#endif

#define YY_INT_ALIGNED short int

#define FLEX_SCANNER
#define YY_FLEX_MAJOR_VERSION 2
#define YY_FLEX_MINOR_VERSION 6
#define YY_FLEX_SUBMINOR_VERSION 4
#if YY_FLEX_SUBMINOR_VERSION > 0
  #define FLEX_BETA
#endif

#define yyFlexLexer stepFlexLexer

#ifdef yyalloc
  #define stepalloc_ALREADY_DEFINED
#else
  #define yyalloc stepalloc
#endif

#ifdef yyrealloc
  #define steprealloc_ALREADY_DEFINED
#else
  #define yyrealloc steprealloc
#endif

#ifdef yyfree
  #define stepfree_ALREADY_DEFINED
#else
  #define yyfree stepfree
#endif

#ifndef FLEXINT_H
  #define FLEXINT_H

  #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

    #ifndef __STDC_LIMIT_MACROS
      #define __STDC_LIMIT_MACROS 1
    #endif

    #include <inttypes.h>
typedef int8_t   flex_int8_t;
typedef uint8_t  flex_uint8_t;
typedef int16_t  flex_int16_t;
typedef uint16_t flex_uint16_t;
typedef int32_t  flex_int32_t;
typedef uint32_t flex_uint32_t;
  #else
typedef signed char        flex_int8_t;
typedef short int          flex_int16_t;
typedef int                flex_int32_t;
typedef unsigned char      flex_uint8_t;
typedef unsigned short int flex_uint16_t;
typedef unsigned int       flex_uint32_t;

    #ifndef INT8_MIN
      #define INT8_MIN (-128)
    #endif
    #ifndef INT16_MIN
      #define INT16_MIN (-32767 - 1)
    #endif
    #ifndef INT32_MIN
      #define INT32_MIN (-2147483647 - 1)
    #endif
    #ifndef INT8_MAX
      #define INT8_MAX (127)
    #endif
    #ifndef INT16_MAX
      #define INT16_MAX (32767)
    #endif
    #ifndef INT32_MAX
      #define INT32_MAX (2147483647)
    #endif
    #ifndef UINT8_MAX
      #define UINT8_MAX (255U)
    #endif
    #ifndef UINT16_MAX
      #define UINT16_MAX (65535U)
    #endif
    #ifndef UINT32_MAX
      #define UINT32_MAX (4294967295U)
    #endif

    #ifndef SIZE_MAX
      #define SIZE_MAX (~(size_t)0)
    #endif

  #endif

#endif

#include <iostream>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#define yyconst const

#if defined(__GNUC__) && __GNUC__ >= 3
  #define yynoreturn __attribute__((__noreturn__))
#else
  #define yynoreturn
#endif

#define YY_NULL 0

#define YY_SC_TO_UI(c) ((YY_CHAR)(c))

#define BEGIN (yy_start) = 1 + 2 *

#define YY_START (((yy_start) - 1) / 2)
#define YYSTATE YY_START

#define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)

#define YY_NEW_FILE yyrestart(yyin)
#define YY_END_OF_BUFFER_CHAR 0

#ifndef YY_BUF_SIZE
  #ifdef __ia64__

    #define YY_BUF_SIZE 32768
  #else
    #define YY_BUF_SIZE 16384
  #endif
#endif

#define YY_STATE_BUF_SIZE ((YY_BUF_SIZE + 2) * sizeof(yy_state_type))

#ifndef YY_TYPEDEF_YY_BUFFER_STATE
  #define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state* YY_BUFFER_STATE;
#endif

#ifndef YY_TYPEDEF_YY_SIZE_T
  #define YY_TYPEDEF_YY_SIZE_T
typedef size_t yy_size_t;
#endif

extern int yyleng;

#define EOB_ACT_CONTINUE_SCAN 0
#define EOB_ACT_END_OF_FILE 1
#define EOB_ACT_LAST_MATCH 2

#define YY_LESS_LINENO(n)
#define YY_LINENO_REWIND_TO(ptr)

#define yyless(n)                                                                                  \
  do                                                                                               \
  {                                                                                                \
                                                                                                   \
    int yyless_macro_arg = (n);                                                                    \
    YY_LESS_LINENO(yyless_macro_arg);                                                              \
    *yy_cp                                = (yy_hold_char);                                        \
    YY_RESTORE_YY_MORE_OFFSET(yy_c_buf_p) = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ;        \
    YY_DO_BEFORE_ACTION;                                                                           \
  } while (0)
#define unput(c) yyunput(c, (yytext_ptr))

#ifndef YY_STRUCT_YY_BUFFER_STATE
  #define YY_STRUCT_YY_BUFFER_STATE

struct yy_buffer_state
{

  std::streambuf* yy_input_file;

  char* yy_ch_buf;
  char* yy_buf_pos;

  int yy_buf_size;

  int yy_n_chars;

  int yy_is_our_buffer;

  int yy_is_interactive;

  int yy_at_bol;

  int yy_bs_lineno;
  int yy_bs_column;

  int yy_fill_buffer;

  int yy_buffer_status;

  #define YY_BUFFER_NEW 0
  #define YY_BUFFER_NORMAL 1

  #define YY_BUFFER_EOF_PENDING 2
};
#endif

#define YY_CURRENT_BUFFER ((yy_buffer_stack) ? (yy_buffer_stack)[(yy_buffer_stack_top)] : NULL)

#define YY_CURRENT_BUFFER_LVALUE (yy_buffer_stack)[(yy_buffer_stack_top)]

void* yyalloc(yy_size_t);
void* yyrealloc(void*, yy_size_t);
void  yyfree(void*);

#define yy_new_buffer yy_create_buffer
#define yy_set_interactive(is_interactive)                                                         \
  {                                                                                                \
    if (!YY_CURRENT_BUFFER)                                                                        \
    {                                                                                              \
      yyensure_buffer_stack();                                                                     \
      YY_CURRENT_BUFFER_LVALUE = yy_create_buffer(yyin, YY_BUF_SIZE);                              \
    }                                                                                              \
    YY_CURRENT_BUFFER_LVALUE->yy_is_interactive = is_interactive;                                  \
  }
#define yy_set_bol(at_bol)                                                                         \
  {                                                                                                \
    if (!YY_CURRENT_BUFFER)                                                                        \
    {                                                                                              \
      yyensure_buffer_stack();                                                                     \
      YY_CURRENT_BUFFER_LVALUE = yy_create_buffer(yyin, YY_BUF_SIZE);                              \
    }                                                                                              \
    YY_CURRENT_BUFFER_LVALUE->yy_at_bol = at_bol;                                                  \
  }
#define YY_AT_BOL() (YY_CURRENT_BUFFER_LVALUE->yy_at_bol)

#define YY_SKIP_YYWRAP
typedef flex_uint8_t YY_CHAR;

#define yytext_ptr yytext
#define YY_INTERACTIVE

#include <FlexLexer.h>

inline int yyFlexLexer::yywrap()
{
  return 1;
}

int yyFlexLexer::yylex()
{
  LexerError("yyFlexLexer::yylex invoked but %option yyclass used");
  return 0;
}

#define YY_DECL int step::scanner::yylex()

#define YY_DO_BEFORE_ACTION                                                                        \
  (yytext_ptr) = yy_bp;                                                                            \
  (yytext_ptr) -= (yy_more_len);                                                                   \
  yyleng         = (int)(yy_cp - (yytext_ptr));                                                    \
  (yy_hold_char) = *yy_cp;                                                                         \
  *yy_cp         = '\0';                                                                           \
  (yy_c_buf_p)   = yy_cp;
#define YY_NUM_RULES 44
#define YY_END_OF_BUFFER 45

struct yy_trans_info
{
  flex_int32_t yy_verify;
  flex_int32_t yy_nxt;
};

static const flex_int16_t yy_acclist[167] = {
  0,  2,    2,  45, 42, 44, 10, 42, 44,    12, 42, 44, 13, 42, 44, 11, 42, 44, 42, 44, 42, 44,
  42, 44,   26, 42, 44, 42, 44, 5,  42,    44, 23, 42, 44, 24, 44, 18, 42, 44, 25, 42, 44, 42,
  44, 37,   42, 44, 18, 40, 42, 44, 28,    42, 44, 27, 42, 44, 40, 42, 44, 40, 42, 44, 40, 42,
  44, 40,   42, 44, 40, 42, 44, 40, 42,    44, 14, 42, 44, 2,  44, 12, 44, 3,  44, 43, 44, 8,
  44, 6,    12, 44, 7,  44, 41, 17, 16400, 19, 18, 19, 19,

  19, 1,    19, 22, 18, 19, 40, 40, 22,    40, 40, 40, 40, 40, 14, 2,  3,  3,  4,  8,  9,  21,
  15, 8208, 40, 40, 40, 40, 40, 40, 8208,  20, 20, 20, 40, 40, 40, 40, 40, 36, 40, 20, 20, 20,
  40, 32,   40, 40, 40, 40, 29, 38, 40,    40, 40, 40, 40, 31, 40, 30, 35, 39, 40, 33, 34, 34};

static const flex_int16_t yy_accept[125] = {
  0,   1,   1,   1,   2,   3,   3,   3,   3,   3,   4,   6,   9,   12,  15,  18,  20,
  22,  24,  27,  29,  32,  35,  37,  40,  43,  45,  48,  52,  55,  58,  61,  64,  67,
  70,  73,  76,  79,  81,  83,  85,  87,  89,  92,  94,  95,  95,  97,  97,  98,  100,
  101, 102, 102, 103, 105, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
  120, 121, 121, 122, 123, 123, 125, 125, 125, 125, 126, 127, 128, 129, 130, 131, 132,
  132, 133, 134, 136, 137, 137, 138, 139, 139, 140, 141, 142, 142, 143, 144, 146,

  147, 147, 148, 149, 150, 151, 152, 153, 153, 154, 155, 156, 157, 157, 158, 159, 160,
  161, 161, 162, 164, 166, 167, 167};

static const YY_CHAR yy_ec[256] = {
  0,  1,  1,  1,  1,  1,  1,  1,  1,  2,  3,  1,  1,  4,  1,  1,  1,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  5,  6,  7,  8,  9,  1,  10, 11, 12, 13,
  14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 1,  21, 1,  22, 1,
  1,  1,  23, 24, 25, 26, 27, 24, 28, 29, 30, 28, 28, 28, 28, 31, 32, 33, 28, 34, 35,
  36, 28, 28, 28, 28, 28, 28, 1,  1,  1,  1,  28, 1,  37, 24, 38, 39,

  40, 24, 28, 41, 42, 28, 28, 28, 28, 43, 44, 45, 28, 46, 47, 48, 28, 28, 28, 28, 28,
  28, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,

  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1};

static const YY_CHAR yy_meta[50] = {0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 4, 1, 1,
                                    1, 5, 1, 6, 1, 1, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7,
                                    7, 7, 7, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 1};

static const flex_int16_t yy_base[135] = {
  0,   0,   0,   47,  48,  255, 252, 49,  52,  253, 323, 323, 323, 323, 323, 0,   0,
  221, 323, 18,  323, 323, 323, 36,  323, 39,  223, 46,  323, 323, 211, 49,  40,  50,
  52,  55,  148, 0,   323, 55,  323, 0,   323, 89,  0,   183, 93,  50,  89,  90,  94,
  100, 139, 323, 104, 105, 138, 323, 101, 58,  110, 118, 108, 90,  0,   66,  87,  323,
  0,   148, 323, 323, 136, 323, 110, 148, 152, 156, 157, 142, 160, 61,  148, 323, 146,
  91,  164, 165, 125, 158, 177, 169, 186, 201, 323, 180, 165, 84,  190, 194, 323,

  176, 198, 202, 206, 210, 323, 323, 194, 214, 213, 217, 218, 228, 225, 323, 233, 323,
  240, 323, 82,  0,   0,   323, 265, 272, 279, 281, 83,  284, 287, 294, 301, 308, 315};

static const flex_int16_t yy_def[135] = {
  0,   123, 1,   124, 124, 125, 125, 126, 126, 123, 123, 123, 123, 123, 123, 127, 128,
  123, 123, 123, 123, 123, 123, 123, 123, 129, 123, 130, 123, 123, 130, 130, 130, 130,
  130, 130, 123, 131, 123, 132, 123, 133, 123, 123, 127, 128, 123, 123, 123, 123, 129,
  129, 129, 123, 123, 130, 130, 123, 130, 130, 130, 130, 130, 123, 131, 132, 132, 123,
  133, 123, 123, 123, 123, 123, 123, 123, 129, 130, 130, 130, 130, 130, 130, 123, 123,
  123, 129, 130, 130, 123, 130, 130, 123, 130, 123, 130, 123, 123, 129, 130, 123,

  123, 130, 130, 130, 130, 123, 123, 123, 130, 130, 130, 130, 123, 130, 123, 130, 123,
  123, 123, 130, 134, 134, 0,   123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123};

static const flex_int16_t yy_nxt[373] = {
  0,   10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  10,  23,  24,  23,
  25,  26,  27,  28,  29,  30,  30,  30,  31,  32,  30,  33,  34,  30,  30,  30,  30,  35,
  30,  30,  30,  31,  32,  33,  34,  30,  30,  30,  30,  35,  30,  36,  38,  38,  42,  47,
  48,  42,  49,  50,  57,  51,  43,  39,  39,  43,  54,  47,  55,  57,  57,  66,  57,  59,
  58,  57,  67,  74,  57,  60,  92,  57,  123, 93,  94,  59,  79,  123, 58,  61,  74,  45,
  60,  62,  69,  69,  69,  72,  69,  79,  72,  61,  57,

  66,  70,  62,  97,  70,  67,  48,  48,  48,  49,  97,  50,  46,  51,  73,  75,  75,  54,
  57,  51,  76,  48,  54,  48,  55,  57,  76,  57,  75,  75,  75,  77,  80,  76,  82,  57,
  78,  72,  63,  76,  72,  84,  57,  75,  77,  100, 80,  82,  78,  81,  69,  69,  69,  84,
  69,  57,  57,  83,  89,  57,  70,  81,  85,  70,  85,  57,  85,  85,  85,  57,  85,  86,
  85,  57,  57,  87,  90,  57,  96,  88,  95,  57,  57,  98,  99,  91,  57,  101, 90,  71,
  96,  107, 95,  88,  57,  105, 63,  57,  91,  101,

  106, 102, 92,  103, 107, 92,  94,  57,  105, 98,  108, 57,  104, 99,  102, 57,  103, 92,
  57,  57,  93,  94,  108, 57,  104, 113, 110, 57,  57,  109, 57,  57,  111, 115, 57,  57,
  53,  113, 117, 110, 46,  109, 57,  112, 118, 111, 114, 118, 119, 116, 57,  120, 123, 121,
  38,  112, 118, 38,  114, 118, 119, 116, 123, 123, 120, 37,  37,  37,  37,  37,  37,  37,
  40,  40,  40,  40,  40,  40,  40,  41,  41,  41,  41,  41,  41,  41,  44,  44,  52,  52,
  52,  56,  56,  56,  64,  123, 64,  123, 64,  64,

  64,  65,  123, 65,  65,  65,  65,  65,  68,  123, 123, 68,  68,  68,  68,  122, 123, 122,
  122, 122, 122, 122, 9,   123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123,
  123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123,
  123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123};

static const flex_int16_t yy_chk[373] = {
  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   3,   4,   7,   19,
  23,  8,   23,  25,  32,  25,  7,   3,   4,   8,   27,  19,  27,  31,  33,  39,  34,  32,
  31,  35,  39,  47,  59,  33,  81,  81,  65,  81,  81,  32,  59,  65,  31,  34,  47,  128,
  33,  35,  43,  43,  43,  46,  43,  59,  46,  34,  120,

  66,  43,  35,  97,  43,  66,  48,  49,  48,  49,  85,  50,  46,  50,  46,  48,  49,  51,
  58,  51,  50,  54,  55,  54,  55,  62,  51,  60,  48,  49,  54,  55,  60,  50,  62,  61,
  58,  72,  63,  51,  72,  74,  88,  54,  55,  88,  60,  62,  58,  61,  69,  69,  69,  74,
  69,  56,  52,  72,  79,  79,  69,  61,  75,  69,  75,  82,  76,  75,  76,  76,  77,  76,
  77,  77,  78,  77,  79,  80,  84,  78,  82,  86,  87,  86,  87,  80,  91,  89,  79,  45,
  84,  96,  82,  78,  90,  91,  36,  95,  80,  89,

  95,  90,  92,  90,  96,  92,  92,  98,  91,  98,  101, 99,  90,  99,  90,  102, 90,  93,
  93,  103, 93,  93,  101, 104, 90,  108, 103, 105, 30,  102, 110, 109, 104, 110, 111, 112,
  26,  108, 112, 103, 17,  102, 114, 105, 113, 104, 109, 113, 113, 111, 116, 114, 9,   116,
  6,   105, 118, 5,   109, 118, 118, 111, 0,   0,   114, 124, 124, 124, 124, 124, 124, 124,
  125, 125, 125, 125, 125, 125, 125, 126, 126, 126, 126, 126, 126, 126, 127, 127, 129, 129,
  129, 130, 130, 130, 131, 0,   131, 0,   131, 131,

  131, 132, 0,   132, 132, 132, 132, 132, 133, 0,   0,   133, 133, 133, 133, 134, 0,   134,
  134, 134, 134, 134, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123,
  123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123,
  123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123};

#define YY_TRAILING_MASK 0x2000
#define YY_TRAILING_HEAD_MASK 0x4000
#define REJECT                                                                                     \
  {                                                                                                \
    *yy_cp           = (yy_hold_char);                                                             \
    yy_cp            = (yy_full_match);                                                            \
    (yy_lp)          = (yy_full_lp);                                                               \
    (yy_state_ptr)   = (yy_full_state);                                                            \
    yy_current_state = *(yy_state_ptr);                                                            \
    ++(yy_lp);                                                                                     \
    goto find_rule;                                                                                \
  }

#define yymore() ((yy_more_flag) = 1)
#define YY_MORE_ADJ (yy_more_len)
#define YY_RESTORE_YY_MORE_OFFSET

#define YY_NO_INPUT 1

#include <step.tab.hpp>

#ifdef YY_DECL
  #undef YY_DECL
#endif
#define YY_DECL int step::scanner::lex(step::parser::semantic_type*)

#ifdef YY_INTERACTIVE
  #undef YY_INTERACTIVE
#endif

typedef step::parser::token token;

#include <Standard_Failure.hpp>
#define YY_FATAL_ERROR(msg) throw Standard_Failure(msg);

#ifdef _MSC_VER

  #include <stdlib.h>
  #include <io.h>

  #ifndef YY_NO_UNISTD_H
    #define YY_NO_UNISTD_H
  #endif

  #if defined(__INTEL_COMPILER)
    #pragma warning(disable : 177 1786 1736)
  #elif defined(__clang__)
    #pragma GCC diagnostic ignored "-Wunused-function"
    #pragma GCC diagnostic ignored "-Winconsistent-dllimport"
    #pragma GCC diagnostic ignored "-Wunneeded-internal-declaration"
  #else
    #pragma warning(disable : 4131 4244 4273 4127 4267)
  #endif

#endif

#define CreateNewText myDataModel->CreateNewText
#define SetTypeArg myDataModel->SetTypeArg

#ifdef __GNUC__
  #pragma GCC diagnostic ignored "-Wunused-function"
#endif

#define INITIAL 0
#define Com 1
#define End 2
#define Text 3

#ifndef YY_NO_UNISTD_H

  #include <unistd.h>
#endif

#ifndef YY_EXTRA_TYPE
  #define YY_EXTRA_TYPE void*
#endif

#ifndef yytext_ptr
static void yy_flex_strncpy(char*, const char*, int);
#endif

#ifdef YY_NEED_STRLEN
static int yy_flex_strlen(const char*);
#endif

#ifndef YY_NO_INPUT

#endif

#ifndef YY_READ_BUF_SIZE
  #ifdef __ia64__

    #define YY_READ_BUF_SIZE 16384
  #else
    #define YY_READ_BUF_SIZE 8192
  #endif
#endif

#ifndef ECHO
  #define ECHO LexerOutput(yytext, yyleng)
#endif

#ifndef YY_INPUT
  #define YY_INPUT(buf, result, max_size)                                                          \
                                                                                                   \
    if ((int)(result = LexerInput((char*)buf, max_size)) < 0)                                      \
      YY_FATAL_ERROR("input in flex scanner failed");

#endif

#ifndef yyterminate
  #define yyterminate() return YY_NULL
#endif

#ifndef YY_START_STACK_INCR
  #define YY_START_STACK_INCR 25
#endif

#ifndef YY_FATAL_ERROR
  #define YY_FATAL_ERROR(msg) LexerError(msg)
#endif

#ifndef YY_DECL
  #define YY_DECL_IS_OURS 1
  #define YY_DECL int yyFlexLexer::yylex()
#endif

#ifndef YY_USER_ACTION
  #define YY_USER_ACTION
#endif

#ifndef YY_BREAK
  #define YY_BREAK break;
#endif

#define YY_RULE_SETUP YY_USER_ACTION

YY_DECL
{
  yy_state_type yy_current_state;
  char *        yy_cp, *yy_bp;
  int           yy_act;

  if (!(yy_init))
  {
    (yy_init) = 1;

#ifdef YY_USER_INIT
    YY_USER_INIT;
#endif

    if (!(yy_state_buf))
      (yy_state_buf) = (yy_state_type*)yyalloc(YY_STATE_BUF_SIZE);
    if (!(yy_state_buf))
      YY_FATAL_ERROR("out of dynamic memory in yylex()");

    if (!(yy_start))
      (yy_start) = 1;

    if (!yyin)
      yyin.rdbuf(std::cin.rdbuf());

    if (!yyout)
      yyout.rdbuf(std::cout.rdbuf());

    if (!YY_CURRENT_BUFFER)
    {
      yyensure_buffer_stack();
      YY_CURRENT_BUFFER_LVALUE = yy_create_buffer(yyin, YY_BUF_SIZE);
    }

    yy_load_buffer_state();
  }

  {

    while (true)
    {
      (yy_more_len) = 0;
      if ((yy_more_flag))
      {
        (yy_more_len)  = (int)((yy_c_buf_p) - (yytext_ptr));
        (yy_more_flag) = 0;
      }
      yy_cp = (yy_c_buf_p);

      *yy_cp = (yy_hold_char);

      yy_bp = yy_cp;

      yy_current_state = (yy_start);

      (yy_state_ptr)    = (yy_state_buf);
      *(yy_state_ptr)++ = yy_current_state;

    yy_match:
      do
      {
        YY_CHAR yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)];
        while (yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state)
        {
          yy_current_state = (int)yy_def[yy_current_state];
          if (yy_current_state >= 124)
            yy_c = yy_meta[yy_c];
        }
        yy_current_state  = yy_nxt[yy_base[yy_current_state] + yy_c];
        *(yy_state_ptr)++ = yy_current_state;
        ++yy_cp;
      } while (yy_base[yy_current_state] != 323);

    yy_find_action:
      yy_current_state = *--(yy_state_ptr);
      (yy_lp)          = yy_accept[yy_current_state];
    find_rule:
      for (;;)
      {
        if ((yy_lp) && (yy_lp) < yy_accept[yy_current_state + 1])
        {
          yy_act = yy_acclist[(yy_lp)];
          if (yy_act & YY_TRAILING_HEAD_MASK || (yy_looking_for_trail_begin))
          {
            if (yy_act == (yy_looking_for_trail_begin))
            {
              (yy_looking_for_trail_begin) = 0;
              yy_act &= ~YY_TRAILING_HEAD_MASK;
              break;
            }
          }
          else if (yy_act & YY_TRAILING_MASK)
          {
            (yy_looking_for_trail_begin) = yy_act & ~YY_TRAILING_MASK;
            (yy_looking_for_trail_begin) |= YY_TRAILING_HEAD_MASK;
          }
          else
          {
            (yy_full_match) = yy_cp;
            (yy_full_state) = (yy_state_ptr);
            (yy_full_lp)    = (yy_lp);
            break;
          }
          ++(yy_lp);
          goto find_rule;
        }
        --yy_cp;
        yy_current_state = *--(yy_state_ptr);
        (yy_lp)          = yy_accept[yy_current_state];
      }

      YY_DO_BEFORE_ACTION;

    do_action:

      switch (yy_act)
      {
        case 1:
          YY_RULE_SETUP
          {
            BEGIN(Com);
          }
          YY_BREAK
        case 2:
          YY_RULE_SETUP
          {
            ;
          }
          YY_BREAK
        case 3:
          YY_RULE_SETUP
          {
            ;
          }
          YY_BREAK
        case 4:
          YY_RULE_SETUP
          {
            BEGIN(INITIAL);
          }
          YY_BREAK
        case 5:
          YY_RULE_SETUP
          {
            BEGIN(Text);
            yymore();
          }
          YY_BREAK
        case 6:

          YY_RULE_SETUP
          {
            yymore();
            yylineno++;
          }
          YY_BREAK
        case 7:
          YY_RULE_SETUP
          {
            yymore();
          }
          YY_BREAK
        case 8:
          YY_RULE_SETUP
          {
            yymore();
          }
          YY_BREAK
        case 9:

          *yy_cp = (yy_hold_char);
          YY_LINENO_REWIND_TO(yy_bp + 1);
          (yy_c_buf_p) = yy_cp = yy_bp + 1;
          YY_DO_BEFORE_ACTION;
          YY_RULE_SETUP
          {
            BEGIN(INITIAL);
            CreateNewText(YYText(), YYLeng());
            SetTypeArg(Interface_ParamText);
            return (token::QUID);
          }
          YY_BREAK
        case 10:
          YY_RULE_SETUP
          {
            ;
          }
          YY_BREAK
        case 11:
          YY_RULE_SETUP
          {
            ;
          }
          YY_BREAK
        case 12:

          YY_RULE_SETUP
          {
            yylineno++;
          }
          YY_BREAK
        case 13:
          YY_RULE_SETUP
          {
            ;
          }
          YY_BREAK
        case 14:
          YY_RULE_SETUP
          {
            ;
          }
          YY_BREAK
        case 15:
          *yy_cp       = (yy_hold_char);
          (yy_c_buf_p) = yy_cp -= 1;
          YY_DO_BEFORE_ACTION;
          YY_RULE_SETUP
          {
            CreateNewText(YYText(), YYLeng());
            return (token::ENTITY);
          }
          YY_BREAK
        case 16:
          YY_RULE_SETUP
          {
            CreateNewText(YYText(), YYLeng());
            return (token::ENTITY);
          }
          YY_BREAK
        case 17:
          YY_RULE_SETUP
          {
            CreateNewText(YYText(), YYLeng());
            return (token::IDENT);
          }
          YY_BREAK
        case 18:
          YY_RULE_SETUP
          {
            CreateNewText(YYText(), YYLeng());
            SetTypeArg(Interface_ParamInteger);
            return (token::QUID);
          }
          YY_BREAK
        case 19:
          YY_RULE_SETUP
          {
            CreateNewText(YYText(), YYLeng());
            SetTypeArg(Interface_ParamReal);
            return (token::QUID);
          }
          YY_BREAK
        case 20:
          YY_RULE_SETUP
          {
            CreateNewText(YYText(), YYLeng());
            SetTypeArg(Interface_ParamReal);
            return (token::QUID);
          }
          YY_BREAK
        case 21:
          YY_RULE_SETUP
          {
            CreateNewText(YYText(), YYLeng());
            SetTypeArg(Interface_ParamHexa);
            return (token::QUID);
          }
          YY_BREAK
        case 22:
          YY_RULE_SETUP
          {
            CreateNewText(YYText(), YYLeng());
            SetTypeArg(Interface_ParamEnum);
            return (token::QUID);
          }
          YY_BREAK
        case 23:
          YY_RULE_SETUP
          {
            return ('(');
          }
          YY_BREAK
        case 24:
          YY_RULE_SETUP
          {
            return (')');
          }
          YY_BREAK
        case 25:
          YY_RULE_SETUP
          {
            myDataModel->PrepareNewArg();
            return (',');
          }
          YY_BREAK
        case 26:
          YY_RULE_SETUP
          {
            CreateNewText(YYText(), YYLeng());
            SetTypeArg(Interface_ParamVoid);
            return (token::QUID);
          }
          YY_BREAK
        case 27:
          YY_RULE_SETUP
          {
            return ('=');
          }
          YY_BREAK
        case 28:
          YY_RULE_SETUP
          {
            return (';');
          }
          YY_BREAK
        case 29:
          YY_RULE_SETUP
          {
            return (token::STEP);
          }
          YY_BREAK
        case 30:
          YY_RULE_SETUP
          {
            return (token::HEADER);
          }
          YY_BREAK
        case 31:
          YY_RULE_SETUP
          {
            return (token::ENDSEC);
          }
          YY_BREAK
        case 32:
          YY_RULE_SETUP
          {
            return (token::DATA);
          }
          YY_BREAK
        case 33:
          YY_RULE_SETUP
          {
            return (token::ENDSTEP);
          }
          YY_BREAK
        case 34:
          YY_RULE_SETUP
          {
            return (token::ENDSTEP);
          }
          YY_BREAK
        case 35:
          YY_RULE_SETUP
          {
            BEGIN(End);
            return (token::ENDSTEP);
          }
          YY_BREAK
        case 36:
          YY_RULE_SETUP
          {
            return (token::STEP);
          }
          YY_BREAK
        case 37:
          YY_RULE_SETUP
          {
            return ('/');
          }
          YY_BREAK
        case 38:
          YY_RULE_SETUP
          {
            return (token::SCOPE);
          }
          YY_BREAK
        case 39:
          YY_RULE_SETUP
          {
            return (token::ENDSCOPE);
          }
          YY_BREAK
        case 40:
          YY_RULE_SETUP
          {
            CreateNewText(YYText(), YYLeng());
            return (token::TYPE);
          }
          YY_BREAK
        case 41:
          YY_RULE_SETUP
          {
            CreateNewText(YYText(), YYLeng());
            return (token::TYPE);
          }
          YY_BREAK
        case 42:

          YY_RULE_SETUP
          {
            CreateNewText(YYText(), YYLeng());
            SetTypeArg(Interface_ParamMisc);
            return (token::QUID);
          }
          YY_BREAK
        case 43:
          YY_RULE_SETUP
          {
            ;
          }
          YY_BREAK
        case 44:
          YY_RULE_SETUP
          YY_FATAL_ERROR("flex scanner jammed");
          YY_BREAK
        case YY_STATE_EOF(INITIAL):
        case YY_STATE_EOF(Com):
        case YY_STATE_EOF(End):
        case YY_STATE_EOF(Text):
          yyterminate();

        case YY_END_OF_BUFFER:
        {

          int yy_amount_of_matched_text = (int)(yy_cp - (yytext_ptr)) - 1;

          *yy_cp = (yy_hold_char);
          YY_RESTORE_YY_MORE_OFFSET

          if (YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_NEW)
          {

            (yy_n_chars)                               = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
            YY_CURRENT_BUFFER_LVALUE->yy_input_file    = yyin.rdbuf();
            YY_CURRENT_BUFFER_LVALUE->yy_buffer_status = YY_BUFFER_NORMAL;
          }

          if ((yy_c_buf_p) <= &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)])
          {
            yy_state_type yy_next_state;

            (yy_c_buf_p) = (yytext_ptr) + yy_amount_of_matched_text;

            yy_current_state = yy_get_previous_state();

            yy_next_state = yy_try_NUL_trans(yy_current_state);

            yy_bp = (yytext_ptr) + YY_MORE_ADJ;

            if (yy_next_state)
            {

              yy_cp            = ++(yy_c_buf_p);
              yy_current_state = yy_next_state;
              goto yy_match;
            }

            else
            {
              yy_cp = (yy_c_buf_p);
              goto yy_find_action;
            }
          }

          else
            switch (yy_get_next_buffer())
            {
              case EOB_ACT_END_OF_FILE:
              {
                (yy_did_buffer_switch_on_eof) = 0;

                if (yywrap())
                {

                  (yy_c_buf_p) = (yytext_ptr) + YY_MORE_ADJ;

                  yy_act = YY_STATE_EOF(YY_START);
                  goto do_action;
                }

                else
                {
                  if (!(yy_did_buffer_switch_on_eof))
                    YY_NEW_FILE;
                }
                break;
              }

              case EOB_ACT_CONTINUE_SCAN:
                (yy_c_buf_p) = (yytext_ptr) + yy_amount_of_matched_text;

                yy_current_state = yy_get_previous_state();

                yy_cp = (yy_c_buf_p);
                yy_bp = (yytext_ptr) + YY_MORE_ADJ;
                goto yy_match;

              case EOB_ACT_LAST_MATCH:
                (yy_c_buf_p) = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)];

                yy_current_state = yy_get_previous_state();

                yy_cp = (yy_c_buf_p);
                yy_bp = (yytext_ptr) + YY_MORE_ADJ;
                goto yy_find_action;
            }
          break;
        }

        default:
          YY_FATAL_ERROR("fatal flex scanner internal error--no action found");
      }
    }
  }
}

yyFlexLexer::yyFlexLexer(std::istream* arg_yyin, std::ostream* arg_yyout)
    : yyin(arg_yyin ? arg_yyin->rdbuf() : std::cin.rdbuf()),
      yyout(arg_yyout ? arg_yyout->rdbuf() : std::cout.rdbuf())
{
  ctor_common();
}

yyFlexLexer::yyFlexLexer(std::istream& arg_yyin, std::ostream& arg_yyout)
    : yyin(arg_yyin.rdbuf()),
      yyout(arg_yyout.rdbuf())
{
  ctor_common();
}

void yyFlexLexer::ctor_common()
{
  yy_c_buf_p    = nullptr;
  yy_init       = 0;
  yy_start      = 0;
  yy_flex_debug = 0;
  yylineno      = 1;

  yy_did_buffer_switch_on_eof = 0;

  yy_looking_for_trail_begin = 0;
  yy_more_flag               = 0;
  yy_more_len                = 0;
  yy_more_offset = yy_prev_more_offset = 0;

  yy_start_stack_ptr = yy_start_stack_depth = 0;
  yy_start_stack                            = nullptr;

  yy_buffer_stack     = nullptr;
  yy_buffer_stack_top = 0;
  yy_buffer_stack_max = 0;

  yy_state_buf = new yy_state_type[YY_STATE_BUF_SIZE];
}

yyFlexLexer::~yyFlexLexer()
{
  delete[] yy_state_buf;
  yyfree(yy_start_stack);
  yy_delete_buffer(YY_CURRENT_BUFFER);
  yyfree(yy_buffer_stack);
}

void yyFlexLexer::switch_streams(std::istream& new_in, std::ostream& new_out)
{

  yy_delete_buffer(YY_CURRENT_BUFFER);
  yy_switch_to_buffer(yy_create_buffer(new_in, YY_BUF_SIZE));

  yyout.rdbuf(new_out.rdbuf());
}

void yyFlexLexer::switch_streams(std::istream* new_in, std::ostream* new_out)
{
  if (!new_in)
  {
    new_in = &yyin;
  }

  if (!new_out)
  {
    new_out = &yyout;
  }

  switch_streams(*new_in, *new_out);
}

#ifdef YY_INTERACTIVE
int yyFlexLexer::LexerInput(char* buf, int)
#else
int yyFlexLexer::LexerInput(char* buf, int max_size)
#endif
{
  if (yyin.eof() || yyin.fail())
    return 0;

#ifdef YY_INTERACTIVE
  yyin.get(buf[0]);

  if (yyin.eof())
    return 0;

  if (yyin.bad())
    return -1;

  return 1;

#else
  (void)yyin.read(buf, max_size);

  if (yyin.bad())
    return -1;
  else
    return static_cast<int>(yyin.gcount());
#endif
}

void yyFlexLexer::LexerOutput(const char* buf, int size)
{
  (void)yyout.write(buf, size);
}

int yyFlexLexer::yy_get_next_buffer()
{
  char* dest   = YY_CURRENT_BUFFER_LVALUE->yy_ch_buf;
  char* source = (yytext_ptr);
  int   number_to_move, i;
  int   ret_val;

  if ((yy_c_buf_p) > &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars) + 1])
    YY_FATAL_ERROR("fatal flex scanner internal error--end of buffer missed");

  if (YY_CURRENT_BUFFER_LVALUE->yy_fill_buffer == 0)
  {
    if ((yy_c_buf_p) - (yytext_ptr)-YY_MORE_ADJ == 1)
    {

      return EOB_ACT_END_OF_FILE;
    }

    else
    {

      return EOB_ACT_LAST_MATCH;
    }
  }

  number_to_move = (int)((yy_c_buf_p) - (yytext_ptr)-1);

  for (i = 0; i < number_to_move; ++i)
    *(dest++) = *(source++);

  if (YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_EOF_PENDING)

    YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars) = 0;

  else
  {
    int num_to_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;

    while (num_to_read <= 0)
    {

      YY_FATAL_ERROR("input buffer overflow, can't enlarge buffer because scanner uses REJECT");
    }

    if (num_to_read > YY_READ_BUF_SIZE)
      num_to_read = YY_READ_BUF_SIZE;

    YY_INPUT((&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move]), (yy_n_chars), num_to_read);

    YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
  }

  if ((yy_n_chars) == 0)
  {
    if (number_to_move == YY_MORE_ADJ)
    {
      ret_val = EOB_ACT_END_OF_FILE;
      yyrestart(yyin);
    }

    else
    {
      ret_val                                    = EOB_ACT_LAST_MATCH;
      YY_CURRENT_BUFFER_LVALUE->yy_buffer_status = YY_BUFFER_EOF_PENDING;
    }
  }

  else
    ret_val = EOB_ACT_CONTINUE_SCAN;

  if (((yy_n_chars) + number_to_move) > YY_CURRENT_BUFFER_LVALUE->yy_buf_size)
  {

    int new_size = (yy_n_chars) + number_to_move + ((yy_n_chars) >> 1);
    YY_CURRENT_BUFFER_LVALUE->yy_ch_buf =
      (char*)yyrealloc((void*)YY_CURRENT_BUFFER_LVALUE->yy_ch_buf, (yy_size_t)new_size);
    if (!YY_CURRENT_BUFFER_LVALUE->yy_ch_buf)
      YY_FATAL_ERROR("out of dynamic memory in yy_get_next_buffer()");

    YY_CURRENT_BUFFER_LVALUE->yy_buf_size = (int)(new_size - 2);
  }

  (yy_n_chars) += number_to_move;
  YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)]     = YY_END_OF_BUFFER_CHAR;
  YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars) + 1] = YY_END_OF_BUFFER_CHAR;

  (yytext_ptr) = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[0];

  return ret_val;
}

yy_state_type yyFlexLexer::yy_get_previous_state()
{
  yy_state_type yy_current_state;
  char*         yy_cp;

  yy_current_state = (yy_start);

  (yy_state_ptr)    = (yy_state_buf);
  *(yy_state_ptr)++ = yy_current_state;

  for (yy_cp = (yytext_ptr) + YY_MORE_ADJ; yy_cp < (yy_c_buf_p); ++yy_cp)
  {
    YY_CHAR yy_c = (*yy_cp ? yy_ec[YY_SC_TO_UI(*yy_cp)] : 49);
    while (yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state)
    {
      yy_current_state = (int)yy_def[yy_current_state];
      if (yy_current_state >= 124)
        yy_c = yy_meta[yy_c];
    }
    yy_current_state  = yy_nxt[yy_base[yy_current_state] + yy_c];
    *(yy_state_ptr)++ = yy_current_state;
  }

  return yy_current_state;
}

yy_state_type yyFlexLexer::yy_try_NUL_trans(yy_state_type yy_current_state)
{
  int yy_is_jam;

  YY_CHAR yy_c = 49;
  while (yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state)
  {
    yy_current_state = (int)yy_def[yy_current_state];
    if (yy_current_state >= 124)
      yy_c = yy_meta[yy_c];
  }
  yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
  yy_is_jam        = (yy_current_state == 123);
  if (!yy_is_jam)
    *(yy_state_ptr)++ = yy_current_state;

  return yy_is_jam ? 0 : yy_current_state;
}

#ifndef YY_NO_UNPUT
void yyFlexLexer::yyunput(int c, char* yy_bp)
{
  char* yy_cp;

  yy_cp = (yy_c_buf_p);

  *yy_cp = (yy_hold_char);

  if (yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2)
  {

    int   number_to_move = (yy_n_chars) + 2;
    char* dest   = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[YY_CURRENT_BUFFER_LVALUE->yy_buf_size + 2];
    char* source = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move];

    while (source > YY_CURRENT_BUFFER_LVALUE->yy_ch_buf)
      *--dest = *--source;

    yy_cp += (int)(dest - source);
    yy_bp += (int)(dest - source);
    YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars) =
      (int)YY_CURRENT_BUFFER_LVALUE->yy_buf_size;

    if (yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2)
      YY_FATAL_ERROR("flex scanner push-back overflow");
  }

  *--yy_cp = (char)c;

  (yytext_ptr)   = yy_bp;
  (yy_hold_char) = *yy_cp;
  (yy_c_buf_p)   = yy_cp;
}
#endif

int yyFlexLexer::yyinput()
{
  int c;

  *(yy_c_buf_p) = (yy_hold_char);

  if (*(yy_c_buf_p) == YY_END_OF_BUFFER_CHAR)
  {

    if ((yy_c_buf_p) < &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)])

      *(yy_c_buf_p) = '\0';

    else
    {
      int offset = (int)((yy_c_buf_p) - (yytext_ptr));
      ++(yy_c_buf_p);

      switch (yy_get_next_buffer())
      {
        case EOB_ACT_LAST_MATCH:

          yyrestart(yyin);

        case EOB_ACT_END_OF_FILE:
        {
          if (yywrap())
            return 0;

          if (!(yy_did_buffer_switch_on_eof))
            YY_NEW_FILE;
#ifdef __cplusplus
          return yyinput();
#else
          return input();
#endif
        }

        case EOB_ACT_CONTINUE_SCAN:
          (yy_c_buf_p) = (yytext_ptr) + offset;
          break;
      }
    }
  }

  c              = *(unsigned char*)(yy_c_buf_p);
  *(yy_c_buf_p)  = '\0';
  (yy_hold_char) = *++(yy_c_buf_p);

  return c;
}

void yyFlexLexer::yyrestart(std::istream& input_file)
{

  if (!YY_CURRENT_BUFFER)
  {
    yyensure_buffer_stack();
    YY_CURRENT_BUFFER_LVALUE = yy_create_buffer(yyin, YY_BUF_SIZE);
  }

  yy_init_buffer(YY_CURRENT_BUFFER, input_file);
  yy_load_buffer_state();
}

void yyFlexLexer::yyrestart(std::istream* input_file)
{
  if (!input_file)
  {
    input_file = &yyin;
  }
  yyrestart(*input_file);
}

void yyFlexLexer::yy_switch_to_buffer(YY_BUFFER_STATE new_buffer)
{

  yyensure_buffer_stack();
  if (YY_CURRENT_BUFFER == new_buffer)
    return;

  if (YY_CURRENT_BUFFER)
  {

    *(yy_c_buf_p)                        = (yy_hold_char);
    YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = (yy_c_buf_p);
    YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
  }

  YY_CURRENT_BUFFER_LVALUE = new_buffer;
  yy_load_buffer_state();

  (yy_did_buffer_switch_on_eof) = 1;
}

void yyFlexLexer::yy_load_buffer_state()
{
  (yy_n_chars) = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
  (yytext_ptr) = (yy_c_buf_p) = YY_CURRENT_BUFFER_LVALUE->yy_buf_pos;
  yyin.rdbuf(YY_CURRENT_BUFFER_LVALUE->yy_input_file);
  (yy_hold_char) = *(yy_c_buf_p);
}

YY_BUFFER_STATE yyFlexLexer::yy_create_buffer(std::istream& file, int size)
{
  YY_BUFFER_STATE b;

  b = (YY_BUFFER_STATE)yyalloc(sizeof(struct yy_buffer_state));
  if (!b)
    YY_FATAL_ERROR("out of dynamic memory in yy_create_buffer()");

  b->yy_buf_size = size;

  b->yy_ch_buf = (char*)yyalloc((yy_size_t)(b->yy_buf_size + 2));
  if (!b->yy_ch_buf)
    YY_FATAL_ERROR("out of dynamic memory in yy_create_buffer()");

  b->yy_is_our_buffer = 1;

  yy_init_buffer(b, file);

  return b;
}

YY_BUFFER_STATE yyFlexLexer::yy_create_buffer(std::istream* file, int size)
{
  return yy_create_buffer(*file, size);
}

void yyFlexLexer::yy_delete_buffer(YY_BUFFER_STATE b)
{

  if (!b)
    return;

  if (b == YY_CURRENT_BUFFER)
    YY_CURRENT_BUFFER_LVALUE = (YY_BUFFER_STATE) nullptr;

  if (b->yy_is_our_buffer)
    yyfree((void*)b->yy_ch_buf);

  yyfree((void*)b);
}

void yyFlexLexer::yy_init_buffer(YY_BUFFER_STATE b, std::istream& file)

{
  int oerrno = errno;

  yy_flush_buffer(b);

  b->yy_input_file  = file.rdbuf();
  b->yy_fill_buffer = 1;

  if (b != YY_CURRENT_BUFFER)
  {
    b->yy_bs_lineno = 1;
    b->yy_bs_column = 0;
  }

  b->yy_is_interactive = 0;
  errno                = oerrno;
}

void yyFlexLexer::yy_flush_buffer(YY_BUFFER_STATE b)
{
  if (!b)
    return;

  b->yy_n_chars = 0;

  b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
  b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;

  b->yy_buf_pos = &b->yy_ch_buf[0];

  b->yy_at_bol        = 1;
  b->yy_buffer_status = YY_BUFFER_NEW;

  if (b == YY_CURRENT_BUFFER)
    yy_load_buffer_state();
}

void yyFlexLexer::yypush_buffer_state(YY_BUFFER_STATE new_buffer)
{
  if (new_buffer == nullptr)
    return;

  yyensure_buffer_stack();

  if (YY_CURRENT_BUFFER)
  {

    *(yy_c_buf_p)                        = (yy_hold_char);
    YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = (yy_c_buf_p);
    YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
  }

  if (YY_CURRENT_BUFFER)
    (yy_buffer_stack_top)++;
  YY_CURRENT_BUFFER_LVALUE = new_buffer;

  yy_load_buffer_state();
  (yy_did_buffer_switch_on_eof) = 1;
}

void yyFlexLexer::yypop_buffer_state()
{
  if (!YY_CURRENT_BUFFER)
    return;

  yy_delete_buffer(YY_CURRENT_BUFFER);
  YY_CURRENT_BUFFER_LVALUE = nullptr;
  if ((yy_buffer_stack_top) > 0)
    --(yy_buffer_stack_top);

  if (YY_CURRENT_BUFFER)
  {
    yy_load_buffer_state();
    (yy_did_buffer_switch_on_eof) = 1;
  }
}

void yyFlexLexer::yyensure_buffer_stack()
{
  yy_size_t num_to_alloc;

  if (!(yy_buffer_stack))
  {

    num_to_alloc = 1;
    (yy_buffer_stack) =
      (struct yy_buffer_state**)yyalloc(num_to_alloc * sizeof(struct yy_buffer_state*));
    if (!(yy_buffer_stack))
      YY_FATAL_ERROR("out of dynamic memory in yyensure_buffer_stack()");

    memset((yy_buffer_stack), 0, num_to_alloc * sizeof(struct yy_buffer_state*));

    (yy_buffer_stack_max) = num_to_alloc;
    (yy_buffer_stack_top) = 0;
    return;
  }

  if ((yy_buffer_stack_top) >= ((yy_buffer_stack_max))-1)
  {

    yy_size_t grow_size = 8;

    num_to_alloc = (yy_buffer_stack_max) + grow_size;
    (yy_buffer_stack) =
      (struct yy_buffer_state**)yyrealloc((yy_buffer_stack),
                                          num_to_alloc * sizeof(struct yy_buffer_state*));
    if (!(yy_buffer_stack))
      YY_FATAL_ERROR("out of dynamic memory in yyensure_buffer_stack()");

    memset((yy_buffer_stack) + (yy_buffer_stack_max),
           0,
           grow_size * sizeof(struct yy_buffer_state*));
    (yy_buffer_stack_max) = num_to_alloc;
  }
}

void yyFlexLexer::yy_push_state(int _new_state)
{
  if ((yy_start_stack_ptr) >= (yy_start_stack_depth))
  {
    yy_size_t new_size;

    (yy_start_stack_depth) += YY_START_STACK_INCR;
    new_size = (yy_size_t)(yy_start_stack_depth) * sizeof(int);

    if (!(yy_start_stack))
      (yy_start_stack) = (int*)yyalloc(new_size);

    else
      (yy_start_stack) = (int*)yyrealloc((void*)(yy_start_stack), new_size);

    if (!(yy_start_stack))
      YY_FATAL_ERROR("out of memory expanding start-condition stack");
  }

  (yy_start_stack)[(yy_start_stack_ptr)++] = YY_START;

  BEGIN(_new_state);
}

void yyFlexLexer::yy_pop_state()
{
  if (--(yy_start_stack_ptr) < 0)
    YY_FATAL_ERROR("start-condition stack underflow");

  BEGIN((yy_start_stack)[(yy_start_stack_ptr)]);
}

int yyFlexLexer::yy_top_state()
{
  return (yy_start_stack)[(yy_start_stack_ptr)-1];
}

#ifndef YY_EXIT_FAILURE
  #define YY_EXIT_FAILURE 2
#endif

void yyFlexLexer::LexerError(const char* msg)
{
  std::cerr << msg << std::endl;
  exit(YY_EXIT_FAILURE);
}

#undef yyless
#define yyless(n)                                                                                  \
  do                                                                                               \
  {                                                                                                \
                                                                                                   \
    int yyless_macro_arg = (n);                                                                    \
    YY_LESS_LINENO(yyless_macro_arg);                                                              \
    yytext[yyleng] = (yy_hold_char);                                                               \
    (yy_c_buf_p)   = yytext + yyless_macro_arg;                                                    \
    (yy_hold_char) = *(yy_c_buf_p);                                                                \
    *(yy_c_buf_p)  = '\0';                                                                         \
    yyleng         = yyless_macro_arg;                                                             \
  } while (0)

#ifndef yytext_ptr
static void yy_flex_strncpy(char* s1, const char* s2, int n)
{

  int i;
  for (i = 0; i < n; ++i)
    s1[i] = s2[i];
}
#endif

#ifdef YY_NEED_STRLEN
static int yy_flex_strlen(const char* s)
{
  int n;
  for (n = 0; s[n]; ++n)
    ;

  return n;
}
#endif

#define YYTABLES_NAME "yytables"

#include <Standard.hpp>

void* yyalloc(size_t theNbBytes)
{
  return Standard::AllocateOptimal(theNbBytes);
}

void* yyrealloc(void* thePnt, size_t theNbBytes)
{
  return Standard::Reallocate(thePnt, theNbBytes);
}

void yyfree(void* thePnt)
{
  Standard::Free(thePnt);
}

step::scanner::scanner(StepFile_ReadData* theDataModel, std::istream* in, std::ostream* out)
    : stepFlexLexer(in, out),
      myDataModel(theDataModel)
{
}
