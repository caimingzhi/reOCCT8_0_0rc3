#include <FairCurve_Newton.hpp>
#include <math_MultipleVarFunctionWithHessian.hpp>

//=================================================================================================

FairCurve_Newton::FairCurve_Newton(const math_MultipleVarFunctionWithHessian& theFunction,
                                   const double                               theSpatialTolerance,
                                   const double                               theCriteriumTolerance,
                                   const int                                  theNbIterations,
                                   const double                               theConvexity,
                                   const bool                                 theWithSingularity)
    : math_NewtonMinimum(theFunction,
                         theCriteriumTolerance,
                         theNbIterations,
                         theConvexity,
                         theWithSingularity),
      mySpTol(theSpatialTolerance)
{
}

//=======================================================================
// function : IsConverged
// purpose  : Convert if the steps are too small or if the criterion
//           progresses little with a reasonable step, this last
//           requirement allows detecting infinite slidings
//           (case when the criterion varies troo slowly).
//=======================================================================
bool FairCurve_Newton::IsConverged() const
{
  const double N = TheStep.Norm();
  return (N <= 0.01 * mySpTol)
         || (N <= mySpTol
             && std::abs(TheMinimum - PreviousMinimum) <= XTol * std::abs(PreviousMinimum));
}
