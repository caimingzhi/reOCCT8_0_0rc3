#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_FunctionWithDerivative.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
class Geom_Curve;

//! Searches singularities on fillet.
//! F(t) = (C1(t) - C2(t)).(C1'(t) - C2'(t));
class ChFi3d_SearchSing : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ChFi3d_SearchSing(const occ::handle<Geom_Curve>& C1,
                                    const occ::handle<Geom_Curve>& C2);

  //! computes the value of the function <F> for the
  //! variable <X>.
  //! returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT bool Value(const double X, double& F) override;

  //! computes the derivative <D> of the function
  //! for the variable <X>.
  //! Returns True if the calculation were successfully done,
  //! False otherwise.
  Standard_EXPORT bool Derivative(const double X, double& D) override;

  //! computes the value <F> and the derivative <D> of the
  //! function for the variable <X>.
  //! Returns True if the calculation were successfully done,
  //! False otherwise.
  Standard_EXPORT bool Values(const double X, double& F, double& D) override;

private:
  occ::handle<Geom_Curve> myC1;
  occ::handle<Geom_Curve> myC2;
};

