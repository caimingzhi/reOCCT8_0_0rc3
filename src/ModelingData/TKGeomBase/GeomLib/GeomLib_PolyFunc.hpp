#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Vector.hpp>
#include <math_FunctionWithDerivative.hpp>

class GeomLib_PolyFunc : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLib_PolyFunc(const math_Vector& Coeffs);

  Standard_EXPORT bool Value(const double X, double& F) override;

  Standard_EXPORT bool Derivative(const double X, double& D) override;

  Standard_EXPORT bool Values(const double X, double& F, double& D) override;

private:
  math_Vector myCoeffs;
};
