#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Circ2d.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <math_FunctionWithDerivative.hpp>

class Geom2dGcc_FunctionTanCirCu : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_FunctionTanCirCu(const gp_Circ2d&           Circ,
                                             const Geom2dAdaptor_Curve& Curv);

  Standard_EXPORT bool Value(const double X, double& F) override;

  Standard_EXPORT bool Derivative(const double X, double& Deriv) override;

  Standard_EXPORT bool Values(const double X, double& F, double& Deriv) override;

private:
  gp_Circ2d           TheCirc;
  Geom2dAdaptor_Curve Curve;
  double              myWeight;
};
