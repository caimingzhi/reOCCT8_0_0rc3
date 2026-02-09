#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_FunctionWithDerivative.hpp>
class Geom2d_Curve;

class Geom2dLProp_FuncCurExt : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dLProp_FuncCurExt(const occ::handle<Geom2d_Curve>& C, const double Tol);

  Standard_EXPORT bool Value(const double X, double& F) override;

  Standard_EXPORT bool Derivative(const double X, double& D) override;

  Standard_EXPORT bool Values(const double X, double& F, double& D) override;

  Standard_EXPORT bool IsMinKC(const double Param) const;

private:
  occ::handle<Geom2d_Curve> theCurve;
  double                    epsX;
};
