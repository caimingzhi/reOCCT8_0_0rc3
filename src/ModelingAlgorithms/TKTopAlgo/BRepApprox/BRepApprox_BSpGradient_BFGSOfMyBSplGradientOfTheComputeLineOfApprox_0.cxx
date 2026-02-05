#include <BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox.hpp>

#include <BRepApprox_TheMultiLineOfApprox.hpp>
#include <BRepApprox_TheMultiLineToolOfApprox.hpp>
#include <BRepApprox_MyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <math_MultipleVarFunctionWithGradient.hpp>

BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox::
  BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox(
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

bool BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox::IsSolutionReached(
  math_MultipleVarFunctionWithGradient& F) const
{
  bool                                                               Result, Result2;
  BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox* F1 =
    (BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox*)&F;

  Result        = (2.0 * fabs(TheMinimum - PreviousMinimum)
            <= 1.e-10 * (fabs(TheMinimum) + fabs(PreviousMinimum)) + 1.e-12);
  double MErr3d = F1->MaxError3d();
  double MErr2d = F1->MaxError2d();
  Result2       = ((MErr3d <= myTol3d) && (MErr2d <= myTol2d));

  return (Result || Result2);
}
