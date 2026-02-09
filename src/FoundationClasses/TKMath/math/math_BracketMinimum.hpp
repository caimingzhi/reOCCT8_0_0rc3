#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
class math_Function;

class math_BracketMinimum
{
public:
  DEFINE_STANDARD_ALLOC

  math_BracketMinimum(const double A, const double B);

  Standard_EXPORT math_BracketMinimum(math_Function& F, const double A, const double B);

  Standard_EXPORT math_BracketMinimum(math_Function& F,
                                      const double   A,
                                      const double   B,
                                      const double   FA);

  Standard_EXPORT math_BracketMinimum(math_Function& F,
                                      const double   A,
                                      const double   B,
                                      const double   FA,
                                      const double   FB);

  void SetLimits(const double theLeft, const double theRight);

  void SetFA(const double theValue);

  void SetFB(const double theValue);

  Standard_EXPORT void Perform(math_Function& F);

  bool IsDone() const;

  Standard_EXPORT void Values(double& A, double& B, double& C) const;

  Standard_EXPORT void FunctionValues(double& FA, double& FB, double& FC) const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  double Limited(const double theValue) const;

  bool LimitAndMayBeSwap(math_Function& F,
                         const double   theA,
                         double&        theB,
                         double&        theFB,
                         double&        theC,
                         double&        theFC) const;

private:
  bool   Done;
  double Ax;
  double Bx;
  double Cx;
  double FAx;
  double FBx;
  double FCx;
  double myLeft;
  double myRight;
  bool   myIsLimited;
  bool   myFA;
  bool   myFB;
};

#include <Precision.hpp>

inline math_BracketMinimum::math_BracketMinimum(const double A, const double B)
    : Done(false),
      Ax(A),
      Bx(B),
      Cx(0.),
      FAx(0.),
      FBx(0.),
      FCx(0.),
      myLeft(-Precision::Infinite()),
      myRight(Precision::Infinite()),
      myIsLimited(false),
      myFA(false),
      myFB(false)
{
}

inline bool math_BracketMinimum::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_BracketMinimum& Br)
{
  Br.Dump(o);
  return o;
}

inline void math_BracketMinimum::SetLimits(const double theLeft, const double theRight)
{
  myLeft      = theLeft;
  myRight     = theRight;
  myIsLimited = true;
}

inline void math_BracketMinimum::SetFA(const double theValue)
{
  FAx  = theValue;
  myFA = true;
}

inline void math_BracketMinimum::SetFB(const double theValue)
{
  FBx  = theValue;
  myFB = true;
}

inline double math_BracketMinimum::Limited(const double theValue) const
{
  return theValue < myLeft ? myLeft : theValue > myRight ? myRight : theValue;
}
