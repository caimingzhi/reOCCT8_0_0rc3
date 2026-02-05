#include <AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute.hpp>

#include <AppDef_MultiLine.hpp>
#include <AppDef_MyLineTool.hpp>
#include <AppDef_MyGradientbisOfBSplineCompute.hpp>
#include <AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute.hpp>
#include <AppDef_ResConstraintOfMyGradientbisOfBSplineCompute.hpp>
#include <AppDef_ParFunctionOfMyGradientbisOfBSplineCompute.hpp>
#include <math_MultipleVarFunctionWithGradient.hpp>

AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute::
  AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute(math_MultipleVarFunctionWithGradient& F,
                                                      const math_Vector& StartingPoint,
                                                      const double       Tolerance3d,
                                                      const double       Tolerance2d,
                                                      const double       Eps,
                                                      const int          NbIterations)
    : math_BFGS(F.NbVariables(), Eps, NbIterations, Eps),
      myTol3d(Tolerance3d),
      myTol2d(Tolerance2d)
{
  Perform(F, StartingPoint);
}

bool AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute::IsSolutionReached(
  math_MultipleVarFunctionWithGradient& F) const
{
  AppDef_ParFunctionOfMyGradientbisOfBSplineCompute* F1 =
    (AppDef_ParFunctionOfMyGradientbisOfBSplineCompute*)&F;
  bool Result, Result2;

  Result        = (2.0 * fabs(TheMinimum - PreviousMinimum)
            <= 1.e-10 * (fabs(TheMinimum) + fabs(PreviousMinimum)) + 1.e-12);
  double MErr3d = F1->MaxError3d();
  double MErr2d = F1->MaxError2d();

  Result2 = ((MErr3d <= myTol3d) && (MErr2d <= myTol2d));
  return (Result || Result2);
}
