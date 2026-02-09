#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_NewtonMinimum.hpp>
class math_MultipleVarFunctionWithHessian;

class FairCurve_Newton : public math_NewtonMinimum
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT FairCurve_Newton(const math_MultipleVarFunctionWithHessian& theFunction,
                                   const double theSpatialTolerance   = 1.0e-7,
                                   const double theCriteriumTolerance = 1.0e-7,
                                   const int    theNbIterations       = 40,
                                   const double theConvexity          = 1.0e-6,
                                   const bool   theWithSingularity    = true);

  Standard_EXPORT bool IsConverged() const override;

private:
  double mySpTol;
};
