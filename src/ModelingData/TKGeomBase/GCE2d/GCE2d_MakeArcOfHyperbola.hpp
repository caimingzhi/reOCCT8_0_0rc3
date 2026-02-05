#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GCE2d_Root.hpp>
#include <Geom2d_TrimmedCurve.hpp>

class gp_Hypr2d;
class gp_Pnt2d;

//! Implements construction algorithms for an arc of
//! hyperbola in the plane. The result is a Geom2d_TrimmedCurve curve.
//! A MakeArcOfHyperbola object provides a framework for:
//! -   defining the construction of the arc of hyperbola,
//! -   implementing the construction algorithm, and
//! -   consulting the results. In particular, the Value
//! function returns the constructed arc of hyperbola.
class GCE2d_MakeArcOfHyperbola : public GCE2d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Makes an arc of Hyperbola (TrimmedCurve from Geom2d) from
  //! a Hyperbola between two parameters Alpha1 and Alpha2.
  Standard_EXPORT GCE2d_MakeArcOfHyperbola(const gp_Hypr2d& Hypr,
                                           const double     Alpha1,
                                           const double     Alpha2,
                                           const bool       Sense = true);

  //! Makes an arc of Hyperbola (TrimmedCurve from Geom2d) from
  //! a Hyperbola between point <P> and the parameter
  //! Alpha.
  Standard_EXPORT GCE2d_MakeArcOfHyperbola(const gp_Hypr2d& Hypr,
                                           const gp_Pnt2d&  P,
                                           const double     Alpha,
                                           const bool       Sense = true);

  //! Makes an arc of Hyperbola (TrimmedCurve from Geom2d) from
  //! a Hyperbola between two points P1 and P2.
  //! Note: the orientation of the arc of hyperbola is:
  //! -   the trigonometric sense if Sense is not defined or
  //! is true (default value), or
  //! -   the opposite sense if Sense is false.
  //! - IsDone always returns true.
  Standard_EXPORT GCE2d_MakeArcOfHyperbola(const gp_Hypr2d& Hypr,
                                           const gp_Pnt2d&  P1,
                                           const gp_Pnt2d&  P2,
                                           const bool       Sense = true);

  //! Returns the constructed arc of hyperbola.
  Standard_EXPORT const occ::handle<Geom2d_TrimmedCurve>& Value() const;

  operator const occ::handle<Geom2d_TrimmedCurve>&() const { return Value(); }

private:
  occ::handle<Geom2d_TrimmedCurve> TheArc;
};
