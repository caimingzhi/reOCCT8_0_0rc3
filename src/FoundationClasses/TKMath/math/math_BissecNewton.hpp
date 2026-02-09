#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Status.hpp>
#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
class math_FunctionWithDerivative;

class math_BissecNewton
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_BissecNewton(const double theXTolerance);

  Standard_EXPORT void Perform(math_FunctionWithDerivative& F,
                               const double                 Bound1,
                               const double                 Bound2,
                               const int                    NbIterations = 100);

  virtual bool IsSolutionReached(math_FunctionWithDerivative& theFunction);

  bool IsDone() const;

  double Root() const;

  double Derivative() const;

  double Value() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

  Standard_EXPORT virtual ~math_BissecNewton();

protected:
  math_Status TheStatus;
  double      XTol;
  double      x;
  double      dx;
  double      f;
  double      df;

private:
  bool Done;
};

#include <StdFail_NotDone.hpp>

inline bool math_BissecNewton::IsSolutionReached(math_FunctionWithDerivative&)
{
  return std::abs(dx) <= XTol;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_BissecNewton& Bi)
{
  Bi.Dump(o);
  return o;
}

inline bool math_BissecNewton::IsDone() const
{
  return Done;
}

inline double math_BissecNewton::Root() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return x;
}

inline double math_BissecNewton::Derivative() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return df;
}

inline double math_BissecNewton::Value() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return f;
}
