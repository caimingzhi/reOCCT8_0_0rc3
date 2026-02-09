#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRBRep_TypeDef.hpp>
#include <IntCurve_IConicTool.hpp>
#include <math_FunctionWithDerivative.hpp>
#include <Standard_Boolean.hpp>
class IntCurve_IConicTool;
class HLRBRep_CurveTool;

class HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter
    : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter(
    const IntCurve_IConicTool& IT,
    const HLRBRep_CurvePtr&    PC);

  Standard_EXPORT bool Value(const double Param, double& F) override;

  Standard_EXPORT bool Derivative(const double Param, double& D) override;

  Standard_EXPORT bool Values(const double Param, double& F, double& D) override;

private:
  HLRBRep_CurvePtr    TheParCurve;
  IntCurve_IConicTool TheImpTool;
};
