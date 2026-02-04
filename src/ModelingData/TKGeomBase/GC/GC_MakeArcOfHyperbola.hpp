#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_TrimmedCurve.hpp>

class gp_Hypr;
class gp_Pnt;

//! Implements construction algorithms for an arc
//! of hyperbola in 3D space. The result is a Geom_TrimmedCurve curve.
//! A MakeArcOfHyperbola object provides a framework for:
//! -   defining the construction of the arc of hyperbola,
//! -   implementing the construction algorithm, and
//! -   consulting the results. In particular, the
//! Value function returns the constructed arc of hyperbola.
class GC_MakeArcOfHyperbola : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an arc of Hyperbola (TrimmedCurve from Geom) from
  //! a Hyperbola between two parameters Alpha1 and Alpha2
  //! (given in radians).
  Standard_EXPORT GC_MakeArcOfHyperbola(const gp_Hypr& Hypr,
                                        const double   Alpha1,
                                        const double   Alpha2,
                                        const bool     Sense);

  //! Creates an arc of Hyperbola (TrimmedCurve from Geom) from
  //! a Hyperbola between point <P> and the parameter
  //! Alpha (given in radians).
  Standard_EXPORT GC_MakeArcOfHyperbola(const gp_Hypr& Hypr,
                                        const gp_Pnt&  P,
                                        const double   Alpha,
                                        const bool     Sense);

  //! Creates an arc of Hyperbola (TrimmedCurve from Geom) from
  //! a Hyperbola between two points P1 and P2.
  //! The orientation of the arc of hyperbola is:
  //! -   the sense of Hypr if Sense is true, or
  //! -   the opposite sense if Sense is false.
  Standard_EXPORT GC_MakeArcOfHyperbola(const gp_Hypr& Hypr,
                                        const gp_Pnt&  P1,
                                        const gp_Pnt&  P2,
                                        const bool     Sense);

  //! Returns the constructed arc of hyperbola.
  Standard_EXPORT const occ::handle<Geom_TrimmedCurve>& Value() const;

  operator const occ::handle<Geom_TrimmedCurve>&() const { return Value(); }

private:
  occ::handle<Geom_TrimmedCurve> TheArc;
};

