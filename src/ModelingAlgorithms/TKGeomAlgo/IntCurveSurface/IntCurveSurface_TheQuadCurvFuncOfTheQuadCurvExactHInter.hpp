#pragma once

#include <Adaptor3d_Curve.hpp>
#include <IntSurf_Quadric.hpp>
#include <math_FunctionWithDerivative.hpp>

class IntSurf_Quadric;
class IntCurveSurface_TheHCurveTool;

class IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter(
    const IntSurf_Quadric&              Q,
    const occ::handle<Adaptor3d_Curve>& C);

  Standard_EXPORT bool Value(const double Param, double& F) override;

  Standard_EXPORT bool Derivative(const double Param, double& D) override;

  Standard_EXPORT bool Values(const double Param, double& F, double& D) override;

private:
  IntSurf_Quadric              myQuadric;
  occ::handle<Adaptor3d_Curve> myCurve;
};
