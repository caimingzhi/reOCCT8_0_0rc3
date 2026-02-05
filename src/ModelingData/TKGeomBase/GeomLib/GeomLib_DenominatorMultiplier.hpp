#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <Standard_Real.hpp>
class Geom_BSplineSurface;

//! this defines an evaluator for a function of 2 variables
//! that will be used by CancelDenominatorDerivative in one
//! direction.
class GeomLib_DenominatorMultiplier
{
public:
  DEFINE_STANDARD_ALLOC

  //! if the surface is rational this will define the evaluator
  //! of a real function of 2 variables a(u,v) such that
  //! if we define a new surface by :
  //! a(u,v) * N(u,v)
  //! NewF(u,v) = ----------------
  //! a(u,v) * D(u,v)
  Standard_EXPORT GeomLib_DenominatorMultiplier(const occ::handle<Geom_BSplineSurface>& Surface,
                                                const NCollection_Array1<double>&       KnotVector);

  //! Returns the value of
  //! a(UParameter,VParameter)=
  //!
  //! H0(UParameter)/Denominator(Umin,Vparameter)
  //!
  //! D Denominator(Umin,Vparameter)
  //! - ------------------------------[H1(u)]/(Denominator(Umin,Vparameter)^2)
  //! D U
  //!
  //! + H3(UParameter)/Denominator(Umax,Vparameter)
  //!
  //! D Denominator(Umax,Vparameter)
  //! - ------------------------------[H2(u)]/(Denominator(Umax,Vparameter)^2)
  //! D U
  Standard_EXPORT double Value(const double UParameter, const double VParameter) const;

private:
  occ::handle<Geom_BSplineSurface> mySurface;
  NCollection_Array1<double>       myKnotFlatVector;
};
