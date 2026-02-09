#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_FunctionSet.hpp>
#include <Standard_Integer.hpp>
#include <math_Vector.hpp>
class math_Matrix;

class math_FunctionSetWithDerivatives : public math_FunctionSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT int NbVariables() const override = 0;

  Standard_EXPORT int NbEquations() const override = 0;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override = 0;

  Standard_EXPORT virtual bool Derivatives(const math_Vector& X, math_Matrix& D) = 0;

  Standard_EXPORT virtual bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) = 0;
};
