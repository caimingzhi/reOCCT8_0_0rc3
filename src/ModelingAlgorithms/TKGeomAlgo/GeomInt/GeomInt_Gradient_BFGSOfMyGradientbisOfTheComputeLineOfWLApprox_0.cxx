#include <GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>

#include <GeomInt_TheMultiLineOfWLApprox.hpp>
#include <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#include <GeomInt_MyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <math_MultipleVarFunctionWithGradient.hpp>

GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox::
  GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox(
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

bool GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox::IsSolutionReached(
  math_MultipleVarFunctionWithGradient& F) const
{
  GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox* F1 =
    (GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox*)&F;
  bool Result, Result2;

  Result        = (2.0 * fabs(TheMinimum - PreviousMinimum)
            <= 1.e-10 * (fabs(TheMinimum) + fabs(PreviousMinimum)) + 1.e-12);
  double MErr3d = F1->MaxError3d();
  double MErr2d = F1->MaxError2d();

  Result2 = ((MErr3d <= myTol3d) && (MErr2d <= myTol2d));
  return (Result || Result2);
}
