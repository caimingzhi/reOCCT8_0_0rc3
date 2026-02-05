#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Function.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>

//! This abstract class describes the virtual functions associated with
//! a function of a single variable for which the first derivative is
//! available.
class math_FunctionWithDerivative : public math_Function
{
public:
  DEFINE_STANDARD_ALLOC

  //! Computes the value <F>of the function for the variable <X>.
  //! Returns True if the calculation were successfully done,
  //! False otherwise.
  Standard_EXPORT bool Value(const double X, double& F) override = 0;

  //! Computes the derivative <D> of the function
  //! for the variable <X>.
  //! Returns True if the calculation were successfully done,
  //! False otherwise.
  Standard_EXPORT virtual bool Derivative(const double X, double& D) = 0;

  //! Computes the value <F> and the derivative <D> of the
  //! function for the variable <X>.
  //! Returns True if the calculation were successfully done,
  //! False otherwise.
  Standard_EXPORT virtual bool Values(const double X, double& F, double& D) = 0;
  Standard_EXPORT ~math_FunctionWithDerivative() override;
};
