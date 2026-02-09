#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
class math_Function;

class math_BracketedRoot
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_BracketedRoot(math_Function& F,
                                     const double   Bound1,
                                     const double   Bound2,
                                     const double   Tolerance,
                                     const int      NbIterations = 100,
                                     const double   ZEPS         = 1.0e-12);

  bool IsDone() const;

  double Root() const;

  double Value() const;

  int NbIterations() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool   Done;
  double TheRoot;
  double TheError;
  int    NbIter;
};

#include <StdFail_NotDone.hpp>

inline bool math_BracketedRoot::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_BracketedRoot& Br)
{
  Br.Dump(o);
  return o;
}

inline double math_BracketedRoot::Root() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheRoot;
}

inline double math_BracketedRoot::Value() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheError;
}

inline int math_BracketedRoot::NbIterations() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return NbIter;
}
