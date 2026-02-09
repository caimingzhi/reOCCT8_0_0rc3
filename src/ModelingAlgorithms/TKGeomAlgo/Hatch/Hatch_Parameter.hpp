#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>

class Hatch_Parameter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Hatch_Parameter();

  Standard_EXPORT Hatch_Parameter(const double Par1,
                                  const bool   Start,
                                  const int    Index = 0,
                                  const double Par2  = 0);

  friend class Hatch_Line;
  friend class Hatch_Hatcher;

private:
  double myPar1;
  bool   myStart;
  int    myIndex;
  double myPar2;
};
