#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_MultipleVarFunctionWithGradient.hpp>
#include <Adaptor3d_Surface.hpp>

#include <Standard_Boolean.hpp>

template <typename T>
class math_VectorBase;
using math_Vector = math_VectorBase<double>;

//! Functional for search of extremum of the square Euclidean distance between point P and
//! surface S, starting from approximate solution (u0, v0).
//!
//! The class inherits math_MultipleVarFunctionWithGradient and thus is intended
//! for use in math_BFGS algorithm.
//!
//! The criteria is:
//! F = SquareDist(P, S(u, v)) - > min
//!
//! The first derivative are:
//! F1(u,v) = (S(u,v) - P) * Su
//! F2(u,v) = (S(u,v) - P) * Sv
//!
//! Su and Sv are first derivatives of the surface, * symbol means dot product.
class Extrema_FuncPSDist : public math_MultipleVarFunctionWithGradient
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor.
  Standard_EXPORT Extrema_FuncPSDist(const Adaptor3d_Surface& theS, const gp_Pnt& theP);

  //! Number of variables.
  Standard_EXPORT int NbVariables() const override;

  //! Value.
  Standard_EXPORT bool Value(const math_Vector& X, double& F) override;

  //! Gradient.
  Standard_EXPORT bool Gradient(const math_Vector& X, math_Vector& G) override;

  //! Value and gradient.
  Standard_EXPORT bool Values(const math_Vector& X, double& F, math_Vector& G) override;

private:
  //! Check point is inside of the surface parameter space.
  //! Returns true if inside and false otherwise.
  bool IsInside(const math_Vector& X);

  const Extrema_FuncPSDist& operator=(const Extrema_FuncPSDist&) = delete;
  Extrema_FuncPSDist(const Extrema_FuncPSDist&)                  = delete;

  const Adaptor3d_Surface& mySurf;
  const gp_Pnt&            myP;
};
