#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_BFGS.hpp>
#include <math_Vector.hpp>
class BRepApprox_TheMultiLineOfApprox;
class BRepApprox_TheMultiLineToolOfApprox;
class BRepApprox_MyGradientOfTheComputeLineBezierOfApprox;
class BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox;
class BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox;
class BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox;
class math_MultipleVarFunctionWithGradient;

class BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox : public math_BFGS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox(
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
