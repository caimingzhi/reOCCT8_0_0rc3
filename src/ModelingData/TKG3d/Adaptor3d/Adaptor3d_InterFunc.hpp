#pragma once

#include <math_FunctionWithDerivative.hpp>

class Adaptor2d_Curve2d;

//! Used to find the points U(t) = U0 or V(t) = V0 in
//! order to determine the Cn discontinuities of an
//! Adpator_CurveOnSurface relatively to the
//! discontinuities of the surface. Used to
//! find the roots of the functions
class Adaptor3d_InterFunc : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  //! build the function U(t)=FixVal if Fix =1 or
  //! V(t)=FixVal if Fix=2
  Standard_EXPORT Adaptor3d_InterFunc(const occ::handle<Adaptor2d_Curve2d>& C,
                                      const double                          FixVal,
                                      const int                             Fix);

  //! computes the value <F>of the function for the variable <X>.
  //! Returns True if the calculation were successfully done,
  //! False otherwise.
  Standard_EXPORT bool Value(const double X, double& F) override;

  //! computes the derivative <D> of the function
  //! for the variable <X>.
  //! Returns True if the calculation were successfully done,
  //! False otherwise.
  Standard_EXPORT bool Derivative(const double X, double& D) override;

  //! computes the value <F> and the derivative <D> of the
  //! function for the variable <X>.
  //! Returns True if the calculation were successfully done,
  //! False otherwise.
  Standard_EXPORT bool Values(const double X, double& F, double& D) override;

private:
  occ::handle<Adaptor2d_Curve2d> myCurve2d;
  double                         myFixVal;
  int                            myFix;
};
