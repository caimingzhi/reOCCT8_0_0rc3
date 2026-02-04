#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_FunctionWithDerivative.hpp>
class Geom2d_Curve;

//! Function used to find the inflections in 2d.
class Geom2dLProp_FuncCurNul : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dLProp_FuncCurNul(const occ::handle<Geom2d_Curve>& C);

  //! Returns the value for the variable <X>.
  Standard_EXPORT bool Value(const double X, double& F) override;

  //! Returns the derivative for the variable <X>
  Standard_EXPORT bool Derivative(const double X, double& D) override;

  //! Returns the value of the function and the derivative
  //! for the variable <X>.
  Standard_EXPORT bool Values(const double X, double& F, double& D) override;

private:
  occ::handle<Geom2d_Curve> theCurve;
};

