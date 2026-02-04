#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_FunctionSet.hpp>
#include <Standard_Integer.hpp>
#include <math_Vector.hpp>
class math_Matrix;

//! This abstract class describes the virtual functions associated
//! with a set of N Functions each of M independent variables.
class math_FunctionSetWithDerivatives : public math_FunctionSet
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the number of variables of the function.
  Standard_EXPORT int NbVariables() const override = 0;

  //! Returns the number of equations of the function.
  Standard_EXPORT int NbEquations() const override = 0;

  //! Computes the values <F> of the Functions for the
  //! variable <X>.
  //! Returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override = 0;

  //! Returns the values <D> of the derivatives for the
  //! variable <X>.
  //! Returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT virtual bool Derivatives(const math_Vector& X, math_Matrix& D) = 0;

  //! returns the values <F> of the functions and the derivatives
  //! <D> for the variable <X>.
  //! Returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT virtual bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) = 0;
};

