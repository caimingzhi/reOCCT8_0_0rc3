#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_FunctionSetWithDerivatives.hpp>
#include <Standard_Boolean.hpp>
#include <math_Vector.hpp>
class Adaptor2d_Curve2d;
class Geom2dInt_Geom2dCurveTool;
class math_Matrix;

class Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter
    : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter(
    const Adaptor2d_Curve2d& curve1,
    const Adaptor2d_Curve2d& curve2);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

private:
  void* thecurve1;
  void* thecurve2;
};
