#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2dAdaptor_Curve.hpp>
#include <gp_Pnt2d.hpp>
#include <math_FunctionWithDerivative.hpp>

//! This abstract class describes a Function of 1 Variable
//! used to find a line tangent to a curve and passing
//! through a point.
class Geom2dGcc_FunctionTanCuPnt : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_FunctionTanCuPnt(const Geom2dAdaptor_Curve& C, const gp_Pnt2d& Point);

  //! Computes the value of the function F for the variable X.
  //! It returns True if the computation is successfully done,
  //! False otherwise.
  Standard_EXPORT bool Value(const double X, double& F) override;

  //! Computes the derivative of the function F for the variable X.
  //! It returns True if the computation is successfully done,
  //! False otherwise.
  Standard_EXPORT bool Derivative(const double X, double& Deriv) override;

  //! Computes the value and the derivative of the function F
  //! for the variable X.
  //! It returns True if the computation is successfully done,
  //! False otherwise.
  Standard_EXPORT bool Values(const double X, double& F, double& Deriv) override;

private:
  Geom2dAdaptor_Curve TheCurv;
  gp_Pnt2d            ThePoint;
};
