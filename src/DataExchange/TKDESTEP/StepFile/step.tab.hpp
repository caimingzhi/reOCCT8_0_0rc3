#pragma once

#include <StepFile_ReadData.hpp>

namespace step
{
  class scanner;
};

#ifdef _MSC_VER

  #pragma warning(disable : 4522)

  #pragma warning(disable : 4512)
#endif

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#if defined __cplusplus
  #define YY_CPLUSPLUS __cplusplus
#else
  #define YY_CPLUSPLUS 199711L
#endif

#if 201103L <= YY_CPLUSPLUS
  #define YY_MOVE std::move
  #define YY_MOVE_OR_COPY move
  #define YY_MOVE_REF(Type) Type&&
  #define YY_RVREF(Type) Type&&
  #define YY_COPY(Type) Type
#else
  #define YY_MOVE
  #define YY_MOVE_OR_COPY copy
  #define YY_MOVE_REF(Type) Type&
  #define YY_RVREF(Type) const Type&
  #define YY_COPY(Type) const Type&
#endif

#if 201103L <= YY_CPLUSPLUS
  #define YY_NOEXCEPT noexcept
  #define YY_NOTHROW
#else
  #define YY_NOEXCEPT
  #define YY_NOTHROW throw()
#endif

#if 201703 <= YY_CPLUSPLUS
  #define YY_CONSTEXPR constexpr
#else
  #define YY_CONSTEXPR
#endif

#ifndef YY_ATTRIBUTE_PURE
  #if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
    #define YY_ATTRIBUTE_PURE __attribute__((__pure__))
  #else
    #define YY_ATTRIBUTE_PURE
  #endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
  #if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
    #define YY_ATTRIBUTE_UNUSED __attribute__((__unused__))
  #else
    #define YY_ATTRIBUTE_UNUSED
  #endif
#endif

#if !defined lint || defined __GNUC__
  #define YYUSE(E) ((void)(E))
#else
  #define YYUSE(E)
#endif

#if defined __GNUC__ && !defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__

  #define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                                                      \
    _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuninitialized\"")           \
      _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
  #define YY_IGNORE_MAYBE_UNINITIALIZED_END _Pragma("GCC diagnostic pop")
#else
  #define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  #define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  #define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
  #define YY_INITIAL_VALUE(Value)
#endif

#if defined __cplusplus && defined __GNUC__ && !defined __ICC && 6 <= __GNUC__
  #define YY_IGNORE_USELESS_CAST_BEGIN                                                             \
    _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuseless-cast\"")
  #define YY_IGNORE_USELESS_CAST_END _Pragma("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
  #define YY_IGNORE_USELESS_CAST_BEGIN
  #define YY_IGNORE_USELESS_CAST_END
#endif

#ifndef YY_CAST
  #ifdef __cplusplus
    #define YY_CAST(Type, Val) static_cast<Type>(Val)
    #define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type>(Val)
  #else
    #define YY_CAST(Type, Val) ((Type)(Val))
    #define YY_REINTERPRET_CAST(Type, Val) ((Type)(Val))
  #endif
#endif
#ifndef YY_NULLPTR
  #if defined __cplusplus
    #if 201103L <= __cplusplus
      #define YY_NULLPTR nullptr
    #else
      #define YY_NULLPTR 0
    #endif
  #else
    #define YY_NULLPTR ((void*)0)
  #endif
#endif

#ifndef YYDEBUG
  #define YYDEBUG 0
#endif

namespace step
{

  class parser
  {
  public:
#ifndef YYSTYPE

    typedef int semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif

    struct syntax_error : std::runtime_error
    {
      syntax_error(const std::string& m)
          : std::runtime_error(m)
      {
      }

      syntax_error(const syntax_error& s)
          : std::runtime_error(s.what())
      {
      }

      ~syntax_error() YY_NOEXCEPT YY_NOTHROW;
    };

    struct token
    {
      enum token_kind_type
      {
        YYEMPTY  = -2,
        YYEOF    = 0,
        YYerror  = 256,
        YYUNDEF  = 257,
        STEP     = 258,
        HEADER   = 259,
        ENDSEC   = 260,
        DATA     = 261,
        ENDSTEP  = 262,
        SCOPE    = 263,
        ENDSCOPE = 264,
        ENTITY   = 265,
        TYPE     = 266,
        INTEGER  = 267,
        FLOAT    = 268,
        IDENT    = 269,
        TEXT     = 270,
        NONDEF   = 271,
        ENUM     = 272,
        HEXA     = 273,
        QUID     = 274
      };

      typedef token_kind_type yytokentype;
    };

    typedef token::yytokentype token_kind_type;

    typedef token_kind_type token_type;

    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS  = 27,
        S_YYEMPTY  = -2,
        S_YYEOF    = 0,
        S_YYerror  = 1,
        S_YYUNDEF  = 2,
        S_STEP     = 3,
        S_HEADER   = 4,
        S_ENDSEC   = 5,
        S_DATA     = 6,
        S_ENDSTEP  = 7,
        S_SCOPE    = 8,
        S_ENDSCOPE = 9,
        S_ENTITY   = 10,
        S_TYPE     = 11,
        S_INTEGER  = 12,
        S_FLOAT    = 13,
        S_IDENT    = 14,
        S_TEXT     = 15,
        S_NONDEF   = 16,
        S_ENUM     = 17,
        S_HEXA     = 18,
        S_QUID     = 19,
        S_20_      = 20,
        S_21_      = 21,
        S_22_      = 22,
        S_23_      = 23,
        S_24_      = 24,
        S_25_      = 25,
        S_26_      = 26,
        S_YYACCEPT = 27,
        S_finvide  = 28,
        S_finstep  = 29,
        S_stepf1   = 30,
        S_stepf2   = 31,
        S_stepf3   = 32,
        S_stepf    = 33,
        S_headl    = 34,
        S_headent  = 35,
        S_endhead  = 36,
        S_unarg    = 37,
        S_listype  = 38,
        S_deblist  = 39,
        S_finlist  = 40,
        S_listarg  = 41,
        S_arglist  = 42,
        S_model    = 43,
        S_bloc     = 44,
        S_plex     = 45,
        S_unent    = 46,
        S_debscop  = 47,
        S_unid     = 48,
        S_export   = 49,
        S_debexp   = 50,
        S_finscop  = 51,
        S_entlab   = 52,
        S_enttype  = 53
      };
    };

    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    template <typename Base>
    struct basic_symbol : Base
    {

      typedef Base super_type;

      basic_symbol()
          : value()
      {
      }

#if 201103L <= YY_CPLUSPLUS

      basic_symbol(basic_symbol&& that)
          : Base(std::move(that)),
            value(std::move(that.value))
      {
      }
#endif

      basic_symbol(const basic_symbol& that);

      basic_symbol(typename Base::kind_type t);

      basic_symbol(typename Base::kind_type t, YY_RVREF(semantic_type) v);

      ~basic_symbol() { clear(); }

      void clear() { Base::clear(); }

      std::string name() const YY_NOEXCEPT { return parser::symbol_name(this->kind()); }

      symbol_kind_type type_get() const YY_NOEXCEPT;

      bool empty() const YY_NOEXCEPT;

      void move(basic_symbol& s);

      semantic_type value;

    private:
#if YY_CPLUSPLUS < 201103L

      basic_symbol& operator=(const basic_symbol& that);
#endif
    };

    struct by_kind
    {

      by_kind();

#if 201103L <= YY_CPLUSPLUS

      by_kind(by_kind&& that);
#endif

      by_kind(const by_kind& that);

      typedef token_kind_type kind_type;

      by_kind(kind_type t);

      void clear();

      void move(by_kind& that);

      symbol_kind_type kind() const YY_NOEXCEPT;

      symbol_kind_type type_get() const YY_NOEXCEPT;

      symbol_kind_type kind_;
    };

    typedef by_kind by_type;

    struct symbol_type : basic_symbol<by_kind>
    {
    };

    parser(step::scanner* scanner_yyarg);
    virtual ~parser();

#if 201103L <= YY_CPLUSPLUS

    parser(const parser&) = delete;

    parser& operator=(const parser&) = delete;
#endif

    int operator()();

    virtual int parse();

#if YYDEBUG

    std::ostream& debug_stream() const YY_ATTRIBUTE_PURE;

    void set_debug_stream(std::ostream&);

    typedef int debug_level_type;

    debug_level_type debug_level() const YY_ATTRIBUTE_PURE;

    void set_debug_level(debug_level_type l);
#endif

    virtual void error(const std::string& msg);

    void error(const syntax_error& err);

    static std::string symbol_name(symbol_kind_type yysymbol);

    class context
    {
    public:
      context(const parser& yyparser, const symbol_type& yyla);

      const symbol_type& lookahead() const { return yyla_; }

      symbol_kind_type token() const { return yyla_.kind(); }

      int expected_tokens(symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser&      yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L

    parser(const parser&);

    parser& operator=(const parser&);
#endif

    typedef signed char state_type;

    int yy_syntax_error_arguments_(const context&   yyctx,
                                   symbol_kind_type yyarg[],
                                   int              yyargn) const;

    virtual std::string yysyntax_error_(const context& yyctx) const;

    static state_type yy_lr_goto_state_(state_type yystate, int yysym);

    static bool yy_pact_value_is_default_(int yyvalue);

    static bool yy_table_value_is_error_(int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    static symbol_kind_type yytranslate_(int t);

    static std::string yytnamerr_(const char* yystr);

    static const char* const yytname_[];

    static const signed char yypact_[];

    static const signed char yydefact_[];

    static const signed char yypgoto_[];

    static const signed char yydefgoto_[];

    static const signed char yytable_[];

    static const signed char yycheck_[];

    static const signed char yystos_[];

    static const signed char yyr1_[];

    static const signed char yyr2_[];

#if YYDEBUG

    static const unsigned char yyrline_[];

    virtual void yy_reduce_print_(int r) const;

    virtual void yy_stack_print_() const;

    int yydebug_;

    std::ostream* yycdebug_;

    template <typename Base>
    void yy_print_(std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    template <typename Base>
    void yy_destroy_(const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    struct by_state
    {

      by_state() YY_NOEXCEPT;

      typedef state_type kind_type;

      by_state(kind_type s) YY_NOEXCEPT;

      by_state(const by_state& that) YY_NOEXCEPT;

      void clear() YY_NOEXCEPT;

      void move(by_state& that);

      symbol_kind_type kind() const YY_NOEXCEPT;

      enum
      {
        empty_state = 0
      };

      state_type state;
    };

    struct stack_symbol_type : basic_symbol<by_state>
    {

      typedef basic_symbol<by_state> super_type;

      stack_symbol_type();

      stack_symbol_type(YY_RVREF(stack_symbol_type) that);

      stack_symbol_type(state_type s, YY_MOVE_REF(symbol_type) sym);
#if YY_CPLUSPLUS < 201103L

      stack_symbol_type& operator=(stack_symbol_type& that);

      stack_symbol_type& operator=(const stack_symbol_type& that);
#endif
    };

    template <typename T, typename S = std::vector<T>>
    class stack
    {
    public:
      typedef typename S::iterator       iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type      size_type;
      typedef typename std::ptrdiff_t    index_type;

      stack(size_type n = 200)
          : seq_(n)
      {
      }

#if 201103L <= YY_CPLUSPLUS

      stack(const stack&) = delete;

      stack& operator=(const stack&) = delete;
#endif

      const T& operator[](index_type i) const { return seq_[size_type(size() - 1 - i)]; }

      T& operator[](index_type i) { return seq_[size_type(size() - 1 - i)]; }

      void push(YY_MOVE_REF(T) t)
      {
        seq_.push_back(T());
        operator[](0).move(t);
      }

      void pop(std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back();
      }

      void clear() YY_NOEXCEPT { seq_.clear(); }

      index_type size() const YY_NOEXCEPT { return index_type(seq_.size()); }

      const_iterator begin() const YY_NOEXCEPT { return seq_.begin(); }

      const_iterator end() const YY_NOEXCEPT { return seq_.end(); }

      class slice
      {
      public:
        slice(const stack& stack, index_type range)
            : stack_(stack),
              range_(range)
        {
        }

        const T& operator[](index_type i) const { return stack_[range_ - i]; }

      private:
        const stack& stack_;
        index_type   range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L

      stack(const stack&);

      stack& operator=(const stack&);
#endif

      S seq_;
    };

    typedef stack<stack_symbol_type> stack_type;

    stack_type yystack_;

    void yypush_(const char* m, YY_MOVE_REF(stack_symbol_type) sym);

    void yypush_(const char* m, state_type s, YY_MOVE_REF(symbol_type) sym);

    void yypop_(int n = 1);

    enum
    {
      yylast_  = 82,
      yynnts_  = 27,
      yyfinal_ = 7
    };

    step::scanner* scanner;
  };

} // namespace step

#if !defined(yyFlexLexer) && !defined(FlexLexerOnce)
  #define yyFlexLexer stepFlexLexer
  #include <FlexLexer.h>
#endif

namespace step
{

  class scanner : public stepFlexLexer
  {
  public:
    explicit scanner(StepFile_ReadData* theDataModel,
                     std::istream*      in  = nullptr,
                     std::ostream*      out = nullptr);

    int lex(step::parser::semantic_type* yylval);

    StepFile_ReadData* myDataModel;
  };

}; // namespace step
