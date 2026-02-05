#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_TrimmedCurve.hpp>

class gp_Parab;
class gp_Pnt;

//! Implements construction algorithms for an arc
//! of parabola in 3D space. The result is a Geom_TrimmedCurve curve.
//! A MakeArcOfParabola object provides a framework for:
//! -   defining the construction of the arc of parabola,
//! -   implementing the construction algorithm, and
//! -   consulting the results. In particular, the
//! Value function returns the constructed arc of parabola.
class GC_MakeArcOfParabola : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an arc of Parabola (TrimmedCurve from Geom) from
  //! a Parabola between two parameters Alpha1 and Alpha2
  //! (given in radians).
  Standard_EXPORT GC_MakeArcOfParabola(const gp_Parab& Parab,
                                       const double    Alpha1,
                                       const double    Alpha2,
                                       const bool      Sense);

  //! Creates an arc of Parabola (TrimmedCurve from Geom) from
  //! a Parabola between point <P> and the parameter
  //! Alpha (given in radians).
  Standard_EXPORT GC_MakeArcOfParabola(const gp_Parab& Parab,
                                       const gp_Pnt&   P,
                                       const double    Alpha,
                                       const bool      Sense);

  //! Creates an arc of Parabola (TrimmedCurve from Geom) from
  //! a Parabola between two points P1 and P2.
  Standard_EXPORT GC_MakeArcOfParabola(const gp_Parab& Parab,
                                       const gp_Pnt&   P1,
                                       const gp_Pnt&   P2,
                                       const bool      Sense);

  //! Returns the constructed arc of parabola.
  Standard_EXPORT const occ::handle<Geom_TrimmedCurve>& Value() const;

  operator const occ::handle<Geom_TrimmedCurve>&() const { return Value(); }

private:
  occ::handle<Geom_TrimmedCurve> TheArc;
};
