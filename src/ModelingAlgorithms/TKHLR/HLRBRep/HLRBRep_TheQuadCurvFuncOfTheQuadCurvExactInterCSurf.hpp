#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntSurf_Quadric.hpp>
#include <gp_Lin.hpp>
#include <math_FunctionWithDerivative.hpp>
#include <Standard_Boolean.hpp>
class IntSurf_Quadric;
class gp_Lin;
class HLRBRep_LineTool;

class HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf(const IntSurf_Quadric& Q,
                                                                      const gp_Lin&          C);

  Standard_EXPORT bool Value(const double Param, double& F) override;

  Standard_EXPORT bool Derivative(const double Param, double& D) override;

  Standard_EXPORT bool Values(const double Param, double& F, double& D) override;

private:
  IntSurf_Quadric myQuadric;
  gp_Lin          myCurve;
};
