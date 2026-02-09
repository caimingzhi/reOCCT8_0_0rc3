#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_FunctionSetWithDerivatives.hpp>
#include <Standard_Boolean.hpp>
#include <math_Vector.hpp>
class math_Matrix;
class gp_Pnt;

class Blend_CurvPointFuncInv : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override = 0;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override = 0;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override = 0;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override = 0;

  Standard_EXPORT virtual void Set(const gp_Pnt& P) = 0;

  Standard_EXPORT virtual void GetTolerance(math_Vector& Tolerance, const double Tol) const = 0;

  Standard_EXPORT virtual void GetBounds(math_Vector& InfBound, math_Vector& SupBound) const = 0;

  Standard_EXPORT virtual bool IsSolution(const math_Vector& Sol, const double Tol) = 0;
};
