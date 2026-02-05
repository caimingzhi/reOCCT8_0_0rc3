#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_MultipleVarFunctionWithGradient.hpp>
#include <Standard_Integer.hpp>
#include <math_Vector.hpp>
class math_Matrix;

class math_MultipleVarFunctionWithHessian : public math_MultipleVarFunctionWithGradient
{
public:
  DEFINE_STANDARD_ALLOC

  //! returns the number of variables of the function.
  Standard_EXPORT int NbVariables() const override = 0;

  //! computes the values of the Functions <F> for the
  //! variable <X>.
  //! Returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT bool Value(const math_Vector& X, double& F) override = 0;

  //! computes the gradient <G> of the functions for the
  //! variable <X>.
  //! Returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT bool Gradient(const math_Vector& X, math_Vector& G) override = 0;

  //! computes the value <F> and the gradient <G> of the
  //! functions for the variable <X>.
  //! Returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT bool Values(const math_Vector& X, double& F, math_Vector& G) override = 0;

  //! computes the value <F>, the gradient <G> and the
  //! hessian <H> of the functions for the variable <X>.
  //! Returns True if the computation was done
  //! successfully, False otherwise.
  Standard_EXPORT virtual bool Values(const math_Vector& X,
                                      double&            F,
                                      math_Vector&       G,
                                      math_Matrix&       H) = 0;
};
