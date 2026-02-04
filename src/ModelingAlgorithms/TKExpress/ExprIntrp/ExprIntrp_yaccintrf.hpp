#pragma once


#ifdef __cplusplus
extern "C"
{
#endif

  int  ExprIntrpparse();
  void ExprIntrperror(char* msg);

  void ExprIntrp_start_string(const char* str);
  void ExprIntrp_stop_string();

  void ExprIntrp_SetResult();
  void ExprIntrp_SetDegree();

  int ExprIntrplex(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

  #include <TCollection_AsciiString.hpp>

const TCollection_AsciiString& ExprIntrp_GetResult();
int                            ExprIntrp_GetDegree();

#endif

