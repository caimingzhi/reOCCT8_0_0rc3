#include <cstring>
#include <ExprIntrp_yaccintrf.hpp>

static TCollection_AsciiString ExprIntrp_curres;
static int                     ExprIntrp_degree;

#ifndef _WIN32
extern char* ExprIntrptext;
#else
extern "C" char* ExprIntrptext;
#endif // _WIN32

extern "C" void ExprIntrp_SetResult()
{
  ExprIntrp_curres = ExprIntrptext;
}

extern "C" void ExprIntrp_SetDegree()
{
  ExprIntrp_degree = (int)strlen(ExprIntrptext);
}

int ExprIntrp_GetDegree()
{
  return ExprIntrp_degree;
}

const TCollection_AsciiString& ExprIntrp_GetResult()
{
  return ExprIntrp_curres;
}
