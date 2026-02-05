#include <AppDef_Gradient_BFGSOfTheGradient.hpp>

#include <AppDef_MultiLine.hpp>
#include <AppDef_MyLineTool.hpp>
#include <AppDef_TheGradient.hpp>
#include <AppDef_ParLeastSquareOfTheGradient.hpp>
#include <AppDef_ResConstraintOfTheGradient.hpp>
#include <AppDef_ParFunctionOfTheGradient.hpp>
#include <math_MultipleVarFunctionWithGradient.hpp>

AppDef_Gradient_BFGSOfTheGradient::AppDef_Gradient_BFGSOfTheGradient(
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

bool AppDef_Gradient_BFGSOfTheGradient::IsSolutionReached(
  math_MultipleVarFunctionWithGradient& F) const
{
  AppDef_ParFunctionOfTheGradient* F1 = (AppDef_ParFunctionOfTheGradient*)&F;
  bool                             Result, Result2;

  Result        = (2.0 * fabs(TheMinimum - PreviousMinimum)
            <= 1.e-10 * (fabs(TheMinimum) + fabs(PreviousMinimum)) + 1.e-12);
  double MErr3d = F1->MaxError3d();
  double MErr2d = F1->MaxError2d();

  Result2 = ((MErr3d <= myTol3d) && (MErr2d <= myTol2d));
  return (Result || Result2);
}
