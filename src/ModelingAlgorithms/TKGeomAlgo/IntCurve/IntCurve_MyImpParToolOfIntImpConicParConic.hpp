#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntCurve_IConicTool.hpp>
#include <math_FunctionWithDerivative.hpp>
#include <Standard_Boolean.hpp>
class IntCurve_IConicTool;
class IntCurve_PConic;
class IntCurve_PConicTool;

class IntCurve_MyImpParToolOfIntImpConicParConic : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurve_MyImpParToolOfIntImpConicParConic(const IntCurve_IConicTool& IT,
                                                             const IntCurve_PConic&     PC);

  Standard_EXPORT bool Value(const double Param, double& F) override;

  Standard_EXPORT bool Derivative(const double Param, double& D) override;

  Standard_EXPORT bool Values(const double Param, double& F, double& D) override;

private:
  void*               TheParCurve;
  IntCurve_IConicTool TheImpTool;
};
