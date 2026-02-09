#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
class math_Function;

class math_BrentMinimum
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_BrentMinimum(const double TolX,
                                    const int    NbIterations = 100,
                                    const double ZEPS         = 1.0e-12);

  Standard_EXPORT math_BrentMinimum(const double TolX,
                                    const double Fbx,
                                    const int    NbIterations = 100,
                                    const double ZEPS         = 1.0e-12);

  Standard_EXPORT virtual ~math_BrentMinimum();

  Standard_EXPORT void Perform(math_Function& F, const double Ax, const double Bx, const double Cx);

  virtual bool IsSolutionReached(math_Function& theFunction);

  bool IsDone() const;

  double Location() const;

  double Minimum() const;

  int NbIterations() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  double a;
  double b;
  double x;
  double fx;
  double fv;
  double fw;
  double XTol;
  double EPSZ;

private:
  bool Done;
  int  iter;
  int  Itermax;
  bool myF;
};

#include <StdFail_NotDone.hpp>

inline bool math_BrentMinimum::IsSolutionReached(math_Function&)
{
  const double TwoTol = 2.0 * (XTol * fabs(x) + EPSZ);
  return (x <= (TwoTol + a)) && (x >= (b - TwoTol));
}

inline bool math_BrentMinimum::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_BrentMinimum& Br)
{
  Br.Dump(o);
  return o;
}

inline double math_BrentMinimum::Location() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return x;
}

inline double math_BrentMinimum::Minimum() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return fx;
}

inline int math_BrentMinimum::NbIterations() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return iter;
}
