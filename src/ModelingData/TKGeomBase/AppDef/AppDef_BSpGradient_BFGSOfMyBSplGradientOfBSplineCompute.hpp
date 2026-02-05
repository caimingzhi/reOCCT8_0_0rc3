#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_BFGS.hpp>
#include <math_Vector.hpp>
class AppDef_MultiLine;
class AppDef_MyLineTool;
class AppDef_MyBSplGradientOfBSplineCompute;
class AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute;
class AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute;
class math_MultipleVarFunctionWithGradient;

class AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute : public math_BFGS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute(
    math_MultipleVarFunctionWithGradient& F,
    const math_Vector&                    StartingPoint,
    const double                          Tolerance3d,
    const double                          Tolerance2d,
    const double                          Eps,
    const int                             NbIterations = 200);

  Standard_EXPORT bool IsSolutionReached(math_MultipleVarFunctionWithGradient& F) const override;

private:
  double myTol3d;
  double myTol2d;
};
