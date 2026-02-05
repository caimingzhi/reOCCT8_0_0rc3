#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <Extrema_POnSurf.hpp>
#include <Standard_Boolean.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>

class Adaptor3d_Surface;
class math_Matrix;
class Extrema_POnSurf;

//! Functional for search of extremum of the distance between point P and
//! surface S, starting from approximate solution (u0, v0).
//!
//! The class inherits math_FunctionSetWithDerivatives and thus is intended
//! for use in math_FunctionSetRoot algorithm .
//!
//! Denoting derivatives of the surface S(u,v) by u and v, respectively, as
//! Su and Sv, the two functions to be nullified are:
//!
//! F1(u,v) = (S - P) * Su
//! F2(u,v) = (S - P) * Sv
//!
//! The derivatives of the functional are:
//!
//! Duf1(u,v) = Su^2    + (S-P) * Suu;
//! Dvf1(u,v) = Su * Sv + (S-P) * Suv
//! Duf2(u,v) = Sv * Su + (S-P) * Suv = Dvf1
//! Dvf2(u,v) = Sv^2    + (S-P) * Svv
//!
//! Here * denotes scalar product, and ^2 is square power.
class Extrema_FuncPSNorm : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_FuncPSNorm();

  Standard_EXPORT Extrema_FuncPSNorm(const gp_Pnt& P, const Adaptor3d_Surface& S);

  //! sets the field mysurf of the function.
  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S);

  //! sets the field mysurf of the function.
  Standard_EXPORT void SetPoint(const gp_Pnt& P);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  //! Calculate Fi(U,V).
  Standard_EXPORT bool Value(const math_Vector& UV, math_Vector& F) override;

  //! Calculate Fi'(U,V).
  Standard_EXPORT bool Derivatives(const math_Vector& UV, math_Matrix& DF) override;

  //! Calculate Fi(U,V) and Fi'(U,V).
  Standard_EXPORT bool Values(const math_Vector& UV, math_Vector& F, math_Matrix& DF) override;

  //! Save the found extremum.
  Standard_EXPORT int GetStateNumber() override;

  //! Return the number of found extrema.
  Standard_EXPORT int NbExt() const;

  //! Return the value of the Nth distance.
  Standard_EXPORT double SquareDistance(const int N) const;

  //! Returns the Nth extremum.
  Standard_EXPORT const Extrema_POnSurf& Point(const int N) const;

private:
  gp_Pnt                                myP;
  const Adaptor3d_Surface*              myS;
  double                                myU;
  double                                myV;
  gp_Pnt                                myPs;
  NCollection_Sequence<double>          mySqDist;
  NCollection_Sequence<Extrema_POnSurf> myPoint;
  bool                                  myPinit;
  bool                                  mySinit;
};
