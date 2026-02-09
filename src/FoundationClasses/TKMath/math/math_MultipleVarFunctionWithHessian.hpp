#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_MultipleVarFunctionWithGradient.hpp>
#include <Standard_Integer.hpp>
#include <math_Vector.hpp>
class math_Matrix;

class math_MultipleVarFunctionWithHessian : public math_MultipleVarFunctionWithGradient
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT int NbVariables() const override = 0;

  Standard_EXPORT bool Value(const math_Vector& X, double& F) override = 0;

  Standard_EXPORT bool Gradient(const math_Vector& X, math_Vector& G) override = 0;

  Standard_EXPORT bool Values(const math_Vector& X, double& F, math_Vector& G) override = 0;

  Standard_EXPORT virtual bool Values(const math_Vector& X,
                                      double&            F,
                                      math_Vector&       G,
                                      math_Matrix&       H) = 0;
};
