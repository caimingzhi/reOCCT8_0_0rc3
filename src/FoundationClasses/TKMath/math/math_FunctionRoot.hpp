#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
class math_FunctionWithDerivative;

class math_FunctionRoot
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_FunctionRoot(math_FunctionWithDerivative& F,
                                    const double                 Guess,
                                    const double                 Tolerance,
                                    const int                    NbIterations = 100);

  Standard_EXPORT math_FunctionRoot(math_FunctionWithDerivative& F,
                                    const double                 Guess,
                                    const double                 Tolerance,
                                    const double                 A,
                                    const double                 B,
                                    const int                    NbIterations = 100);

  bool IsDone() const;

  double Root() const;

  double Derivative() const;

  double Value() const;

  int NbIterations() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool   Done;
  double TheRoot;
  double TheError{};
  double TheDerivative;
  int    NbIter;
};

#include <StdFail_NotDone.hpp>

inline bool math_FunctionRoot::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_FunctionRoot& F)
{
  F.Dump(o);
  return o;
}

inline double math_FunctionRoot::Root() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheRoot;
}

inline double math_FunctionRoot::Derivative() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheDerivative;
}

inline double math_FunctionRoot::Value() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheError;
}

inline int math_FunctionRoot::NbIterations() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return NbIter;
}
