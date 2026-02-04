#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_MultipleVarFunction.hpp>
#include <Standard_Integer.hpp>
#include <math_Vector.hpp>

//! The abstract class MultipleVarFunctionWithGradient
//! describes the virtual functions associated with a multiple variable function.
class math_MultipleVarFunctionWithGradient : public math_MultipleVarFunction
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the number of variables of the function.
  Standard_EXPORT int NbVariables() const override = 0;

  //! Computes the values of the Functions <F> for the variable <X>.
  //! Returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT bool Value(const math_Vector& X, double& F) override = 0;

  //! Computes the gradient <G> of the functions for the variable <X>.
  //! Returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT virtual bool Gradient(const math_Vector& X, math_Vector& G) = 0;

  //! computes the value <F> and the gradient <G> of the
  //! functions for the variable <X>.
  //! Returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT virtual bool Values(const math_Vector& X, double& F, math_Vector& G) = 0;
};

