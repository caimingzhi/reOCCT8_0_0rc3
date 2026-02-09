#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_OStream.hpp>
class math_FunctionWithDerivative;

class math_NewtonFunctionRoot
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_NewtonFunctionRoot(math_FunctionWithDerivative& F,
                                          const double                 Guess,
                                          const double                 EpsX,
                                          const double                 EpsF,
                                          const int                    NbIterations = 100);

  Standard_EXPORT math_NewtonFunctionRoot(math_FunctionWithDerivative& F,
                                          const double                 Guess,
                                          const double                 EpsX,
                                          const double                 EpsF,
                                          const double                 A,
                                          const double                 B,
                                          const int                    NbIterations = 100);

  Standard_EXPORT math_NewtonFunctionRoot(const double A,
                                          const double B,
                                          const double EpsX,
                                          const double EpsF,
                                          const int    NbIterations = 100);

  Standard_EXPORT void Perform(math_FunctionWithDerivative& F, const double Guess);

  bool IsDone() const;

  double Root() const;

  double Derivative() const;

  double Value() const;

  int NbIterations() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool   Done;
  double X;
  double Fx;
  double DFx;
  int    It;
  double EpsilonX;
  double EpsilonF;
  int    Itermax;
  double Binf;
  double Bsup;
};

#include <StdFail_NotDone.hpp>

inline bool math_NewtonFunctionRoot::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_NewtonFunctionRoot& N)
{
  N.Dump(o);
  return o;
}

inline double math_NewtonFunctionRoot::Root() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return X;
}

inline double math_NewtonFunctionRoot::Derivative() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return DFx;
}

inline double math_NewtonFunctionRoot::Value() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Fx;
}

inline int math_NewtonFunctionRoot::NbIterations() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return It;
}
