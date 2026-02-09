#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Function.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>

class math_FunctionWithDerivative : public math_Function
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT bool Value(const double X, double& F) override = 0;

  Standard_EXPORT virtual bool Derivative(const double X, double& D) = 0;

  Standard_EXPORT virtual bool Values(const double X, double& F, double& D) = 0;
  Standard_EXPORT ~math_FunctionWithDerivative() override;
};
