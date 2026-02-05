#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2dAdaptor_Curve.hpp>
#include <gp_Dir2d.hpp>
#include <math_FunctionWithDerivative.hpp>

//! This class describe a function of a single variable.
class Geom2dGcc_FunctionTanObl : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_FunctionTanObl(const Geom2dAdaptor_Curve& Curve, const gp_Dir2d& Dir);

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
  gp_Dir2d            TheDirection;
};
