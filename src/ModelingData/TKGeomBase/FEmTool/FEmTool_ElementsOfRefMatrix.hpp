#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <math_FunctionSet.hpp>
#include <math_Vector.hpp>
#include <PLib_HermitJacobi.hpp>

//! this class describes the functions needed for calculating
//! matrix elements of RefMatrix for linear criteriums
//! (Tension, Flexion and Jerk) by Gauss integration.
//! Each function from set gives value Pi(u)'*Pj(u)' or
//! Pi(u)''*Pj(u)'' or Pi(u)'''*Pj(u)''' for each i and j,
//! where Pi(u) is i-th basis function of expansion and
//! (') means derivative.
class FEmTool_ElementsOfRefMatrix : public math_FunctionSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT FEmTool_ElementsOfRefMatrix(const PLib_HermitJacobi& TheBase, const int DerOrder);

  //! returns the number of variables of the function.
  //! It is supposed that NbVariables = 1.
  Standard_EXPORT int NbVariables() const override;

  //! returns the number of equations of the function.
  Standard_EXPORT int NbEquations() const override;

  //! computes the values <F> of the functions for the
  //! variable <X>.
  //! returns True if the computation was done successfully,
  //! False otherwise.
  //! F contains results only for i<=j in following order:
  //! P0*P0, P0*P1, P0*P2... P1*P1, P1*P2,... (upper triangle of
  //! matrix {PiPj})
  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

private:
  PLib_HermitJacobi myBase;
  int               myDerOrder;
  int               myNbEquations;
};
