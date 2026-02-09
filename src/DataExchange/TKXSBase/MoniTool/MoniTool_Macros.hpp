#pragma once

#define GetCasted(atype, start) Handle(atype)::DownCast(start)

#define DeclareAndCast(atype, result, start) Handle(atype) result = Handle(atype)::DownCast(start)

#define FastCast(atype, result, start)                                                             \
  Handle(atype) result;                                                                            \
  result = (*(Handle(atype)*)) & start
