#include <BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox.hpp>

#include <BRepApprox_TheMultiLineOfApprox.hpp>
#include <BRepApprox_TheMultiLineToolOfApprox.hpp>
#include <BRepApprox_MyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <math_MultipleVarFunctionWithGradient.hpp>

BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox::
  BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox(
    math_MultipleVarFunctionWithGradient& F,
    const math_Vector&                    StartingPoint,
    const double                          Tolerance3d,
    const double                          Tolerance2d,
    const double                          Eps,
    const int                             NbIterations)
    : math_BFGS(F.NbVariables(), Eps, NbIterations, Eps),
      myTol3d(Tolerance3d),
      myTol2d(Tolerance2d)
{
  Perform(F, StartingPoint);
}

bool BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox::IsSolutionReached(
  math_MultipleVarFunctionWithGradient& F) const
{
  BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox* F1 =
    (BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox*)&F;
  bool Result, Result2;

  Result        = (2.0 * fabs(TheMinimum - PreviousMinimum)
            <= 1.e-10 * (fabs(TheMinimum) + fabs(PreviousMinimum)) + 1.e-12);
  double MErr3d = F1->MaxError3d();
  double MErr2d = F1->MaxError2d();

  Result2 = ((MErr3d <= myTol3d) && (MErr2d <= myTol2d));
  return (Result || Result2);
}
