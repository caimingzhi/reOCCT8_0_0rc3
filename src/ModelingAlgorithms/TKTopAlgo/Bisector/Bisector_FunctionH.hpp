#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <math_FunctionWithDerivative.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
class Geom2d_Curve;

//! H(v) = (T1.P2(v) - P1) * ||T(v)|| -
//! 2         2
//! (T(v).P2(v) - P1) * ||T1||
class Bisector_FunctionH : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Bisector_FunctionH(const occ::handle<Geom2d_Curve>& C2,
                                     const gp_Pnt2d&                  P1,
                                     const gp_Vec2d&                  T1);

  //! Computes the values of the Functions for the variable <X>.
  Standard_EXPORT bool Value(const double X, double& F) override;

  Standard_EXPORT bool Derivative(const double X, double& D) override;

  //! Returns the values of the functions and the derivatives
  //! for the variable <X>.
  Standard_EXPORT bool Values(const double X, double& F, double& D) override;

private:
  occ::handle<Geom2d_Curve> curve2;
  gp_Pnt2d                  p1;
  gp_Vec2d                  t1;
};
