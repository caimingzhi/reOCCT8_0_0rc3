#pragma once

#include <math_FunctionWithDerivative.hpp>

class Adaptor2d_Curve2d;

class Adaptor3d_InterFunc : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Adaptor3d_InterFunc(const occ::handle<Adaptor2d_Curve2d>& C,
                                      const double                          FixVal,
                                      const int                             Fix);

  Standard_EXPORT bool Value(const double X, double& F) override;

  Standard_EXPORT bool Derivative(const double X, double& D) override;

  Standard_EXPORT bool Values(const double X, double& F, double& D) override;

private:
  occ::handle<Adaptor2d_Curve2d> myCurve2d;
  double                         myFixVal;
  int                            myFix;
};
