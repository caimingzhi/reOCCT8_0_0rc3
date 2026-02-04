#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <NCollection_Array1.hpp>
#include <math_FunctionWithDerivative.hpp>

//! Polynomial definition for surface normal computation at singular points.
//!
//! This class defines a polynomial function F(X) and its derivative for use
//! with numerical root-finding algorithms. The function represents a trigonometric
//! polynomial in terms of cos(X) and sin(X) with binomial coefficients.
//!
//! The polynomial has the form:
//!   F(X) = Sum_{i=0}^{k0} C(k0,i) * cos^i(X) * sin^(k0-i)(X) * li(i)
//!
//! where C(k0,i) is the binomial coefficient and li(i) are user-provided coefficients.
//!
//! This is used internally by CSLib::Normal() to find the normal direction
//! at singular surface points by solving for zeros of this polynomial.
class CSLib_NormalPolyDef : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a polynomial definition for normal computation.
  //!
  //! @param[in] theK0 Polynomial degree (must be >= 0)
  //! @param[in] theLi Array of coefficients with indices 0 to theK0
  Standard_EXPORT CSLib_NormalPolyDef(int theK0, const NCollection_Array1<double>& theLi);

  //! Computes the value of the function for the given variable.
  //!
  //! Evaluates F(X) = Sum_{i=0}^{k0} C(k0,i) * cos^i(X) * sin^(k0-i)(X) * li(i)
  //!
  //! @param[in]  theX Input variable (angle in radians)
  //! @param[out] theF Computed function value
  //! @return true if calculation was successful, false otherwise
  Standard_EXPORT bool Value(const double theX, double& theF) override;

  //! Computes the derivative of the function for the given variable.
  //!
  //! Evaluates dF/dX using the chain rule on the trigonometric polynomial.
  //!
  //! @param[in]  theX Input variable (angle in radians)
  //! @param[out] theD Computed derivative value
  //! @return true if calculation was successful, false otherwise
  Standard_EXPORT bool Derivative(const double theX, double& theD) override;

  //! Computes both the value and derivative of the function.
  //!
  //! More efficient than calling Value() and Derivative() separately
  //! as common subexpressions are computed only once.
  //!
  //! @param[in]  theX Input variable (angle in radians)
  //! @param[out] theF Computed function value
  //! @param[out] theD Computed derivative value
  //! @return true if calculation was successful, false otherwise
  Standard_EXPORT bool Values(const double theX, double& theF, double& theD) override;

private:
  int                        myK0;    //!< Polynomial degree
  NCollection_Array1<double> myTABli; //!< Array of coefficients li(i) for i = 0..myK0
};

