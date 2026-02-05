#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_NewtonMinimum.hpp>
class math_MultipleVarFunctionWithHessian;

//! Algorithm of Optimization used to make "FairCurve"
class FairCurve_Newton : public math_NewtonMinimum
{
public:
  DEFINE_STANDARD_ALLOC

  //! The tolerance required on the solution is given by Tolerance.
  //! Iteration are stopped if (!WithSingularity) and H(F(Xi)) is not definite
  //! positive (if the smaller eigenvalue of H < Convexity)
  //! or IsConverged() returns True for 2 successives Iterations.
  //! Warning: This constructor do not computation
  Standard_EXPORT FairCurve_Newton(const math_MultipleVarFunctionWithHessian& theFunction,
                                   const double theSpatialTolerance   = 1.0e-7,
                                   const double theCriteriumTolerance = 1.0e-7,
                                   const int    theNbIterations       = 40,
                                   const double theConvexity          = 1.0e-6,
                                   const bool   theWithSingularity    = true);

  //! This method is called at the end of each
  //! iteration to check the convergence:
  //! || Xi+1 - Xi || < SpatialTolerance/100 Or
  //! || Xi+1 - Xi || < SpatialTolerance and
  //! |F(Xi+1) - F(Xi)| < CriteriumTolerance * |F(xi)|
  //! It can be redefined in a sub-class to implement a specific test.
  Standard_EXPORT bool IsConverged() const override;

private:
  double mySpTol;
};
