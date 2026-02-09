

#define yylex steplex

#include "step.tab.hpp"

#undef yylex
#define yylex scanner->lex
#define StepData scanner->myDataModel

#ifdef _MSC_VER
  #pragma warning(disable : 4065 4244 4131 4127 4702)
#endif
void StepFile_Interrupt(const char* theErrorMessage, const bool theIsFail);

#ifndef YY_
  #if defined YYENABLE_NLS && YYENABLE_NLS
    #if ENABLE_NLS
      #include <libintl.h>
      #define YY_(msgid) dgettext("bison-runtime", msgid)
    #endif
  #endif
  #ifndef YY_
    #define YY_(msgid) msgid
  #endif
#endif

#ifndef YY_EXCEPTIONS
  #if defined __GNUC__ && !defined __EXCEPTIONS
    #define YY_EXCEPTIONS 0
  #else
    #define YY_EXCEPTIONS 1
  #endif
#endif

#if YYDEBUG

  #define YYCDEBUG                                                                                 \
    if (yydebug_)                                                                                  \
    (*yycdebug_)

  #define YY_SYMBOL_PRINT(Title, Symbol)                                                           \
    do                                                                                             \
    {                                                                                              \
      if (yydebug_)                                                                                \
      {                                                                                            \
        *yycdebug_ << Title << ' ';                                                                \
        yy_print_(*yycdebug_, Symbol);                                                             \
        *yycdebug_ << '\n';                                                                        \
      }                                                                                            \
    } while (false)

  #define YY_REDUCE_PRINT(Rule)                                                                    \
    do                                                                                             \
    {                                                                                              \
      if (yydebug_)                                                                                \
        yy_reduce_print_(Rule);                                                                    \
    } while (false)

  #define YY_STACK_PRINT()                                                                         \
    do                                                                                             \
    {                                                                                              \
      if (yydebug_)                                                                                \
        yy_stack_print_();                                                                         \
    } while (false)

#else

  #define YYCDEBUG                                                                                 \
    if (false)                                                                                     \
    std::cerr
  #define YY_SYMBOL_PRINT(Title, Symbol) YYUSE(Symbol)
  #define YY_REDUCE_PRINT(Rule) static_cast<void>(0)
  #define YY_STACK_PRINT() static_cast<void>(0)

#endif

#define yyerrok (yyerrstatus_ = 0)
#define yyclearin (yyla.clear())

#define YYACCEPT goto yyacceptlab
#define YYABORT goto yyabortlab
#define YYERROR goto yyerrorlab
#define YYRECOVERING() (!!yyerrstatus_)

namespace step
{

  parser::parser(step::scanner* scanner_yyarg)
#if YYDEBUG
      : yydebug_(false),
        yycdebug_(&std::cerr),
#else
      :
#endif
        scanner(scanner_yyarg)
  {
  }

  parser::~parser() = default;

  parser::syntax_error::~syntax_error() YY_NOEXCEPT YY_NOTHROW = default;

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol(const basic_symbol& that)
      : Base(that),
        value(that.value)
  {
  }

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol(typename Base::kind_type t)
      : Base(t),
        value()
  {
  }

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol(typename Base::kind_type t, YY_RVREF(semantic_type) v)
      : Base(t),
        value(YY_MOVE(v))
  {
  }

  template <typename Base>
  parser::symbol_kind_type parser::basic_symbol<Base>::type_get() const YY_NOEXCEPT
  {
    return this->kind();
  }

  template <typename Base>
  bool parser::basic_symbol<Base>::empty() const YY_NOEXCEPT
  {
    return this->kind() == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void parser::basic_symbol<Base>::move(basic_symbol& s)
  {
    super_type::move(s);
    value = YY_MOVE(s.value);
  }

  parser::by_kind::by_kind()
      : kind_(symbol_kind::S_YYEMPTY)
  {
  }

#if 201103L <= YY_CPLUSPLUS
  parser::by_kind::by_kind(by_kind&& that)
      : kind_(that.kind_)
  {
    that.clear();
  }
#endif

  parser::by_kind::by_kind(const by_kind& that)

    = default;

  parser::by_kind::by_kind(token_kind_type t)
      : kind_(yytranslate_(t))
  {
  }

  void parser::by_kind::clear()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void parser::by_kind::move(by_kind& that)
  {
    kind_ = that.kind_;
    that.clear();
  }

  parser::symbol_kind_type parser::by_kind::kind() const YY_NOEXCEPT
  {
    return kind_;
  }

  parser::symbol_kind_type parser::by_kind::type_get() const YY_NOEXCEPT
  {
    return this->kind();
  }

  parser::by_state::by_state() YY_NOEXCEPT : state(empty_state) {}

  parser::by_state::by_state(const by_state& that) YY_NOEXCEPT = default;

  void parser::by_state::clear() YY_NOEXCEPT
  {
    state = empty_state;
  }

  void parser::by_state::move(by_state& that)
  {
    state = that.state;
    that.clear();
  }

  parser::by_state::by_state(state_type s) YY_NOEXCEPT : state(s) {}

  parser::symbol_kind_type parser::by_state::kind() const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST(symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type() = default;

  parser::stack_symbol_type::stack_symbol_type(YY_RVREF(stack_symbol_type) that)
      : super_type(YY_MOVE(that.state), YY_MOVE(that.value))
  {
#if 201103L <= YY_CPLUSPLUS

    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type(state_type s, YY_MOVE_REF(symbol_type) that)
      : super_type(s, YY_MOVE(that.value))
  {

    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type& parser::stack_symbol_type::operator=(const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  parser::stack_symbol_type& parser::stack_symbol_type::operator=(stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;

    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void parser::yy_destroy_(const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT(yymsg, yysym);

    YYUSE(yysym.kind());
  }

#if YYDEBUG
  template <typename Base>
  void parser::yy_print_(std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE(yyoutput);
    if (yysym.empty())
      yyo << "empty symbol";
    else
    {
      symbol_kind_type yykind = yysym.kind();
      yyo << (yykind < YYNTOKENS ? "token" : "nterm") << ' ' << yysym.name() << " (";
      YYUSE(yykind);
      yyo << ')';
    }
  }
#endif

  void parser::yypush_(const char* m, YY_MOVE_REF(stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT(m, sym);
    yystack_.push(YY_MOVE(sym));
  }

  void parser::yypush_(const char* m, state_type s, YY_MOVE_REF(symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_(m, stack_symbol_type(s, std::move(sym)));
#else
    stack_symbol_type ss(s, sym);
    yypush_(m, ss);
#endif
  }

  void parser::yypop_(int n)
  {
    yystack_.pop(n);
  }

#if YYDEBUG
  std::ostream& parser::debug_stream() const
  {
    return *yycdebug_;
  }

  void parser::set_debug_stream(std::ostream& o)
  {
    yycdebug_ = &o;
  }

  parser::debug_level_type parser::debug_level() const
  {
    return yydebug_;
  }

  void parser::set_debug_level(debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  parser::state_type parser::yy_lr_goto_state_(state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool parser::yy_pact_value_is_default_(int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool parser::yy_table_value_is_error_(int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int parser::operator()()
  {
    return parse();
  }

  int parser::parse()
  {
    int yyn;

    int yylen = 0;

    int yyerrstatus_ = 0;

    symbol_type yyla;

    int yyresult;

#if YY_EXCEPTIONS
    try
#endif
    {
      YYCDEBUG << "Starting parse\n";

      yystack_.clear();
      yypush_(YY_NULLPTR, 0, YY_MOVE(yyla));

    yynewstate:
      YYCDEBUG << "Entering state " << int(yystack_[0].state) << '\n';
      YY_STACK_PRINT();

      if (yystack_[0].state == yyfinal_)
        YYACCEPT;

      goto yybackup;

    yybackup:

      yyn = yypact_[+yystack_[0].state];
      if (yy_pact_value_is_default_(yyn))
        goto yydefault;

      if (yyla.empty())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif
        {
          yyla.kind_ = yytranslate_(yylex(&yyla.value));
        }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error(yyexc);
          goto yyerrlab1;
        }
#endif
      }
      YY_SYMBOL_PRINT("Next token is", yyla);

      if (yyla.kind() == symbol_kind::S_YYerror)
      {

        yyla.kind_ = symbol_kind::S_YYUNDEF;
        goto yyerrlab1;
      }

      yyn += yyla.kind();
      if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind())
      {
        goto yydefault;
      }

      yyn = yytable_[yyn];
      if (yyn <= 0)
      {
        if (yy_table_value_is_error_(yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

      if (yyerrstatus_)
        --yyerrstatus_;

      yypush_("Shifting", state_type(yyn), YY_MOVE(yyla));
      goto yynewstate;

    yydefault:
      yyn = yydefact_[+yystack_[0].state];
      if (yyn == 0)
        goto yyerrlab;
      goto yyreduce;

    yyreduce:
      yylen = yyr2_[yyn];
      {
        stack_symbol_type yylhs;
        yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);

        if (yylen)
          yylhs.value = yystack_[yylen - 1].value;
        else
          yylhs.value = yystack_[0].value;

        YY_REDUCE_PRINT(yyn);
#if YY_EXCEPTIONS
        try
#endif
        {
          switch (yyn)
          {
            case 11:
            {
              return (0);
            }
            break;

            case 16:
            {
              StepData->FinalOfHead();
            }
            break;

            case 17:
            {
              StepData->SetTypeArg(Interface_ParamIdent);
              StepData->CreateNewArg();
            }
            break;

            case 18:
            {
              StepData->CreateNewArg();
            }
            break;

            case 19:
            {
              StepData->CreateNewArg();
            }
            break;

            case 20:
            {
              StepData->CreateNewArg();
            }
            break;

            case 21:
            {
              StepData->CreateErrorArg();
            }
            break;

            case 22:
            {
              StepData->RecordTypeText();
            }
            break;

            case 23:
            {
              StepData->RecordListStart();
            }
            break;

            case 24:
            {
              if (StepData->GetModePrint() > 0)
              {
                printf("Record no : %d -- ", StepData->GetNbRecord() + 1);
                StepData->PrintCurrentRecord();
              }
              StepData->RecordNewEntity();
              yyerrstatus_ = 0;
            }
            break;

            case 39:
            {
              StepData->AddNewScope();
            }
            break;

            case 40:
            {
              StepData->SetTypeArg(Interface_ParamIdent);
              StepData->CreateNewArg();
            }
            break;

            case 43:
            {
              StepData->RecordListStart();
            }
            break;

            case 44:
            {
              StepData->FinalOfScope();
            }
            break;

            case 45:
            {
              printf("***  Warning : Export List not yet processed\n");
              StepData->RecordNewEntity();
              StepData->FinalOfScope();
            }
            break;

            case 46:
            {
              StepData->RecordIdent();
            }
            break;

            case 47:
            {
              StepData->RecordType();
            }
            break;

            default:
              break;
          }
        }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error(yyexc);
          YYERROR;
        }
#endif
        YY_SYMBOL_PRINT("-> $$ =", yylhs);
        yypop_(yylen);
        yylen = 0;

        yypush_(YY_NULLPTR, YY_MOVE(yylhs));
      }
      goto yynewstate;

    yyerrlab:

      if (!yyerrstatus_)
      {
        context     yyctx(*this, yyla);
        std::string msg = yysyntax_error_(yyctx);
        error(YY_MOVE(msg));
      }

      if (yyerrstatus_ == 3)
      {

        if (yyla.kind() == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty())
        {
          yy_destroy_("Error: discarding", yyla);
          yyla.clear();
        }
      }

      goto yyerrlab1;

    yyerrorlab:

      if (false)
        YYERROR;

      yypop_(yylen);
      yylen = 0;
      YY_STACK_PRINT();
      goto yyerrlab1;

    yyerrlab1:
      yyerrstatus_ = 3;

      for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_(yyn))
        {
          yyn += symbol_kind::S_YYerror;
          if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == symbol_kind::S_YYerror)
          {
            yyn = yytable_[yyn];
            if (0 < yyn)
              break;
          }
        }

        if (yystack_.size() == 1)
          YYABORT;

        yy_destroy_("Error: popping", yystack_[0]);
        yypop_();
        YY_STACK_PRINT();
      }
      {
        stack_symbol_type error_token;

        error_token.state = state_type(yyn);
        yypush_("Shifting", YY_MOVE(error_token));
      }
      goto yynewstate;

    yyacceptlab:
      yyresult = 0;
      goto yyreturn;

    yyabortlab:
      yyresult = 1;
      goto yyreturn;

    yyreturn:
      if (!yyla.empty())
        yy_destroy_("Cleanup: discarding lookahead", yyla);

      yypop_(yylen);
      YY_STACK_PRINT();
      while (1 < yystack_.size())
      {
        yy_destroy_("Cleanup: popping", yystack_[0]);
        yypop_();
      }

      return yyresult;
    }
#if YY_EXCEPTIONS
    catch (...)
    {
      YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";

      if (!yyla.empty())
        yy_destroy_(YY_NULLPTR, yyla);

      while (1 < yystack_.size())
      {
        yy_destroy_(YY_NULLPTR, yystack_[0]);
        yypop_();
      }
      throw;
    }
#endif
  }

  void parser::error(const syntax_error& yyexc)
  {
    error(yyexc.what());
  }

  std::string parser::yytnamerr_(const char* yystr)
  {
    if (*yystr == '"')
    {
      std::string yyr;
      char const* yyp = yystr;

      for (;;)
        switch (*++yyp)
        {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            yyr += *yyp;
            break;

          case '"':
            return yyr;
        }
    do_not_strip_quotes:;
    }

    return yystr;
  }

  std::string parser::symbol_name(symbol_kind_type yysymbol)
  {
    return yytnamerr_(yytname_[yysymbol]);
  }

  parser::context::context(const parser& yyparser, const symbol_type& yyla)
      : yyparser_(yyparser),
        yyla_(yyla)
  {
  }

  int parser::context::expected_tokens(symbol_kind_type yyarg[], int yyargn) const
  {

    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_(yyn))
    {

      int yyxbegin = yyn < 0 ? -yyn : 0;

      int yychecklim = yylast_ - yyn + 1;
      int yyxend     = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
            && !yy_table_value_is_error_(yytable_[yyx + yyn]))
        {
          if (!yyarg)
            ++yycount;
          else if (yycount == yyargn)
            return 0;
          else
            yyarg[yycount++] = YY_CAST(symbol_kind_type, yyx);
        }
    }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }

  int parser::yy_syntax_error_arguments_(const context&   yyctx,
                                         symbol_kind_type yyarg[],
                                         int              yyargn) const
  {

    if (!yyctx.lookahead().empty())
    {
      if (yyarg)
        yyarg[0] = yyctx.token();
      int yyn = yyctx.expected_tokens(yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      return yyn + 1;
    }
    return 0;
  }

  std::string parser::yysyntax_error_(const context& yyctx) const
  {

    enum
    {
      YYARGS_MAX = 5
    };

    symbol_kind_type yyarg[YYARGS_MAX];
    int              yycount = yy_syntax_error_arguments_(yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
    {
#define YYCASE_(N, S)                                                                              \
  case N:                                                                                          \
    yyformat = S;                                                                                  \
    break
      default:
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

    std::string yyres;

    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
      {
        yyres += symbol_name(yyarg[yyi++]);
        ++yyp;
      }
      else
        yyres += *yyp;
    return yyres;
  }

  const signed char parser::yypact_ninf_ = -24;

  const signed char parser::yytable_ninf_ = -9;

  const signed char parser::yypact_[] = {
    26,  5,   -24, -24, -24, 35,  29,  -24, -24, 41,  -24, 43,  -24, 36,  -24, 45,  41,
    -24, -24, 3,   38,  -24, -24, 40,  -24, 32,  45,  -24, -24, -24, -24, -24, -24, 36,
    -24, -24, 9,   -24, 60,  56,  -24, -3,  51,  -24, 17,  -24, -24, -24, 53,  44,  6,
    36,  59,  -24, 0,   36,  -24, 42,  6,   2,   -24, 47,  -24, -24, 36,  -24, -24, 55,
    2,   49,  -24, 52,  -24, -24, -24, -14, 50,  -24, -24, 55,  -24, -24, -24};

  const signed char parser::yydefact_[] = {
    0,  0,  9,  10, 11, 0,  0,  1,  15, 0,  47, 0,  12, 0,  16, 0,  0,  13, 23, 0,  0,
    34, 46, 0,  29, 0,  0,  21, 22, 17, 18, 24, 27, 0,  25, 19, 0,  14, 34, 0,  30, 0,
    0,  20, 0,  26, 7,  39, 0,  0,  0,  0,  0,  28, 0,  0,  31, 44, 0,  0,  37, 4,  6,
    38, 0,  35, 43, 0,  0,  0,  2,  5,  36, 40, 41, 0,  0,  33, 3,  0,  45, 32, 42};

  const signed char parser::yypgoto_[] = {-24, -24, -24, -24, -24, -24, -24, -24, 62,
                                          58,  31,  -24, -24, 46,  -13, -24, -23, -21,
                                          -24, -6,  -24, -2,  -24, -24, 18,  -24, -5};

  const signed char parser::yydefgoto_[] = {-1, 71, 62, 2,  3,  4,  5,  11, 12, 15, 32, 33, 19, 34,
                                            35, 36, 23, 24, 54, 49, 50, 74, 75, 67, 59, 25, 51};

  const signed char parser::yytable_[] = {
    20, 13, 40, 42, 27, 47, 13, 21, 10, 6,  79, 10, 80, 10, 28, 57, 22, 29, 27, 48, 43,
    40, 30, 63, 48, 18, 31, 58, 28, 1,  8,  29, 31, 44, 9,  7,  30, 40, 60, 18, 10, 38,
    65, 55, 8,  39, 21, 14, 16, 64, 22, 72, 21, 69, 10, 22, 52, 41, 18, 37, -8, 22, 76,
    46, 10, 56, 61, 70, 66, 73, 77, 81, 78, 17, 26, 53, 68, 82, 0,  0,  0,  0,  45};

  const signed char parser::yycheck_[] = {
    13, 6,  23, 26, 1,  8,  11, 1,  11, 4,  24, 11, 26, 11, 11, 9,  10, 14, 1,  22, 33,
    42, 19, 23, 22, 22, 23, 50, 11, 3,  1,  14, 23, 24, 5,  0,  19, 58, 51, 22, 11, 1,
    55, 48, 1,  5,  1,  6,  5,  54, 10, 64, 1,  59, 11, 10, 5,  25, 22, 21, 0,  10, 68,
    7,  11, 21, 7,  20, 26, 14, 21, 21, 20, 11, 16, 44, 58, 79, -1, -1, -1, -1, 36};

  const signed char parser::yystos_[] = {
    0,  3,  30, 31, 32, 33, 4,  0,  1,  5,  11, 34, 35, 53, 6,  36, 5,  35, 22, 39, 41,
    1,  10, 43, 44, 52, 36, 1,  11, 14, 19, 23, 37, 38, 40, 41, 42, 21, 1,  5,  44, 25,
    43, 41, 24, 40, 7,  8,  22, 46, 47, 53, 5,  37, 45, 53, 21, 9,  43, 51, 41, 7,  29,
    23, 53, 41, 26, 50, 51, 46, 20, 28, 41, 14, 48, 49, 46, 21, 20, 24, 26, 21, 48};

  const signed char parser::yyr1_[] = {
    0,  27, 28, 28, 29, 29, 30, 31, 32, 33, 33, 33, 34, 34, 35, 35, 36, 37, 37, 37, 37, 37, 38, 39,
    40, 41, 41, 42, 42, 43, 43, 44, 44, 44, 44, 45, 45, 46, 46, 47, 48, 49, 49, 50, 51, 51, 52, 53};

  const signed char parser::yyr2_[] = {0, 2, 1, 2, 1, 2, 8, 7, 6, 1, 1, 1, 1, 2, 3, 1,
                                       1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 3, 1, 3, 1, 2, 4,
                                       7, 6, 1, 2, 3, 2, 3, 1, 1, 1, 3, 1, 1, 4, 1, 1};

  const char* const parser::yytname_[] = {"\"end of file\"",
                                          "error",
                                          "\"invalid token\"",
                                          "STEP",
                                          "HEADER",
                                          "ENDSEC",
                                          "DATA",
                                          "ENDSTEP",
                                          "SCOPE",
                                          "ENDSCOPE",
                                          "ENTITY",
                                          "TYPE",
                                          "INTEGER",
                                          "FLOAT",
                                          "IDENT",
                                          "TEXT",
                                          "NONDEF",
                                          "ENUM",
                                          "HEXA",
                                          "QUID",
                                          "' '",
                                          "';'",
                                          "'('",
                                          "')'",
                                          "','",
                                          "'='",
                                          "'/'",
                                          "$accept",
                                          "finvide",
                                          "finstep",
                                          "stepf1",
                                          "stepf2",
                                          "stepf3",
                                          "stepf",
                                          "headl",
                                          "headent",
                                          "endhead",
                                          "unarg",
                                          "listype",
                                          "deblist",
                                          "finlist",
                                          "listarg",
                                          "arglist",
                                          "model",
                                          "bloc",
                                          "plex",
                                          "unent",
                                          "debscop",
                                          "unid",
                                          "export",
                                          "debexp",
                                          "finscop",
                                          "entlab",
                                          "enttype",
                                          YY_NULLPTR};

#if YYDEBUG
  const unsigned char parser::yyrline_[] = {
    0,   96,  96,  97,  98,  99,  100, 101, 102, 103, 103, 103, 106, 107, 109, 110,
    112, 115, 116, 117, 118, 119, 122, 125, 128, 133, 134, 136, 137, 139, 140, 142,
    143, 144, 145, 147, 148, 150, 151, 153, 156, 159, 160, 162, 165, 167, 172, 175};

  void parser::yy_stack_print_() const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator i = yystack_.begin(), i_end = yystack_.end(); i != i_end; ++i)
      *yycdebug_ << ' ' << int(i->state);
    *yycdebug_ << '\n';
  }

  void parser::yy_reduce_print_(int yyrule) const
  {
    int yylno  = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];

    *yycdebug_ << "Reducing stack by rule " << yyrule - 1 << " (line " << yylno << "):\n";

    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT("   $" << yyi + 1 << " =", yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif

  parser::symbol_kind_type parser::yytranslate_(int t)
  {

    static const signed char translate_table[] = {
      0, 2, 2, 2, 2, 2, 2, 2,  2, 2,  2, 2,  2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
      2, 2, 2, 2, 2, 2, 2, 20, 2, 2,  2, 2,  2, 2, 2, 22, 23, 2,  2,  24, 2,  2,  26, 2,  2,
      2, 2, 2, 2, 2, 2, 2, 2,  2, 21, 2, 25, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
      2, 2, 2, 2, 2, 2, 2, 2,  2, 2,  2, 2,  2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
      2, 2, 2, 2, 2, 2, 2, 2,  2, 2,  2, 2,  2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
      2, 2, 2, 2, 2, 2, 2, 2,  2, 2,  2, 2,  2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
      2, 2, 2, 2, 2, 2, 2, 2,  2, 2,  2, 2,  2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
      2, 2, 2, 2, 2, 2, 2, 2,  2, 2,  2, 2,  2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
      2, 2, 2, 2, 2, 2, 2, 2,  2, 2,  2, 2,  2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
      2, 2, 2, 2, 2, 2, 2, 2,  2, 2,  2, 2,  2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
      2, 2, 2, 2, 2, 2, 1, 2,  3, 4,  5, 6,  7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    const int code_max = 274;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST(symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // namespace step

void step::parser::error(const std::string& m)
{
  char newmess[120];
  bool isSyntax = strncmp(m.c_str(), "syntax error", 12) == 0;
  if (isSyntax && m.length() > 13)
    Sprintf(newmess,
            "Undefined Parsing: Line %d: %s: %s",
            scanner->lineno() + 1,
            "Incorrect syntax",
            m.c_str() + 14);
  else if (isSyntax)
    Sprintf(newmess, "Undefined Parsing: Line %d: Incorrect syntax", scanner->lineno() + 1);
  else
    Sprintf(newmess, "Undefined Parsing: Line %d: %s", scanner->lineno() + 1, m.c_str());

  StepFile_Interrupt(newmess, false);

  StepData->AddError(newmess);
}
