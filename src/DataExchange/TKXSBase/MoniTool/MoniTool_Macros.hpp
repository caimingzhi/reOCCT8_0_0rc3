#pragma once


// Interface General purpose Macros
// Their use is not required, but it gets some program parts easier :
// DownCasting, with or without Declaration

//  DownCasting to a "Handle" already declared
#define GetCasted(atype, start) Handle(atype)::DownCast(start)

//  DownCasting with Declaration :
//  - Declares the variable result
//  - then performs DownCasting
//  - after it, result can be used as a new variable
#define DeclareAndCast(atype, result, start) Handle(atype) result = Handle(atype)::DownCast(start)

#define FastCast(atype, result, start)                                                             \
  Handle(atype) result;                                                                            \
  result = (*(Handle(atype)*)) & start

