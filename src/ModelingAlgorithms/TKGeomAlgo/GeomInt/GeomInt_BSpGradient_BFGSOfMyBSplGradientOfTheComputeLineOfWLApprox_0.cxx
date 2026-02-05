#include <GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>

#include <GeomInt_TheMultiLineOfWLApprox.hpp>
#include <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#include <GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#include <math_MultipleVarFunctionWithGradient.hpp>

GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox::
  GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox(
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

bool GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox::IsSolutionReached(
  math_MultipleVarFunctionWithGradient& F) const
{
  bool                                                              Result, Result2;
  GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox* F1 =
    (GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox*)&F;

  Result        = (2.0 * fabs(TheMinimum - PreviousMinimum)
            <= 1.e-10 * (fabs(TheMinimum) + fabs(PreviousMinimum)) + 1.e-12);
  double MErr3d = F1->MaxError3d();
  double MErr2d = F1->MaxError2d();
  Result2       = ((MErr3d <= myTol3d) && (MErr2d <= myTol2d));

  return (Result || Result2);
}
