#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_MultipleVarFunction.hpp>
#include <Standard_Integer.hpp>
#include <math_Vector.hpp>

class math_MultipleVarFunctionWithGradient : public math_MultipleVarFunction
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT int NbVariables() const override = 0;

  Standard_EXPORT bool Value(const math_Vector& X, double& F) override = 0;

  Standard_EXPORT virtual bool Gradient(const math_Vector& X, math_Vector& G) = 0;

  Standard_EXPORT virtual bool Values(const math_Vector& X, double& F, math_Vector& G) = 0;
};
