#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRBRep_TypeDef.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <Standard_Boolean.hpp>
#include <math_Vector.hpp>
class HLRBRep_CurveTool;
class math_Matrix;

class HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter
    : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter(
    const HLRBRep_CurvePtr& curve1,
    const HLRBRep_CurvePtr& curve2);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

private:
  HLRBRep_CurvePtr thecurve1;
  HLRBRep_CurvePtr thecurve2;
};
