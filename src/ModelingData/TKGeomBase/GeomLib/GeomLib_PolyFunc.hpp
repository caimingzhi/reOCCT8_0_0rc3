#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Vector.hpp>
#include <math_FunctionWithDerivative.hpp>

//! Polynomial Function
class GeomLib_PolyFunc : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLib_PolyFunc(const math_Vector& Coeffs);

  //! computes the value <F>of the function for the variable <X>.
  //! Returns True if the calculation were successfully done,
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
  math_Vector myCoeffs;
};

