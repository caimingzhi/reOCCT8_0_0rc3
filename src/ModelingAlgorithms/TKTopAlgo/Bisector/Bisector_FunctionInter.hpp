#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_FunctionWithDerivative.hpp>
class Geom2d_Curve;
class Bisector_Curve;

//! 2                      2
//! F(u) = (PC(u) - PBis1(u)) + (PC(u) - PBis2(u))
class Bisector_FunctionInter : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Bisector_FunctionInter();

  Standard_EXPORT Bisector_FunctionInter(const occ::handle<Geom2d_Curve>&   C,
                                         const occ::handle<Bisector_Curve>& Bis1,
                                         const occ::handle<Bisector_Curve>& Bis2);

  Standard_EXPORT void Perform(const occ::handle<Geom2d_Curve>&   C,
                               const occ::handle<Bisector_Curve>& Bis1,
                               const occ::handle<Bisector_Curve>& Bis2);

  //! Computes the values of the Functions for the variable <X>.
  Standard_EXPORT bool Value(const double X, double& F) override;

  Standard_EXPORT bool Derivative(const double X, double& D) override;

  //! Returns the values of the functions and the derivatives
  //! for the variable <X>.
  Standard_EXPORT bool Values(const double X, double& F, double& D) override;

private:
  occ::handle<Geom2d_Curve>   curve;
  occ::handle<Bisector_Curve> bisector1;
  occ::handle<Bisector_Curve> bisector2;
};
