#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GCE2d_Root.hpp>
#include <Geom2d_TrimmedCurve.hpp>

class gp_Elips2d;
class gp_Pnt2d;

//! Implements construction algorithms for an arc of
//! ellipse in the plane. The result is a Geom2d_TrimmedCurve curve.
//! A MakeArcOfEllipse object provides a framework for:
//! -   defining the construction of the arc of ellipse,
//! -   implementing the construction algorithm, and
//! -   consulting the results. In particular, the Value
//! function returns the constructed arc of ellipse.
class GCE2d_MakeArcOfEllipse : public GCE2d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Make an arc of Ellipse (TrimmedCurve from Geom2d) from
  //! a Ellipse between two parameters Alpha1 and Alpha2.
  Standard_EXPORT GCE2d_MakeArcOfEllipse(const gp_Elips2d& Elips,
                                         const double      Alpha1,
                                         const double      Alpha2,
                                         const bool        Sense = true);

  //! Make an arc of Ellipse (TrimmedCurve from Geom2d) from
  //! a Ellipse between point <P> and the parameter
  //! Alpha.
  Standard_EXPORT GCE2d_MakeArcOfEllipse(const gp_Elips2d& Elips,
                                         const gp_Pnt2d&   P,
                                         const double      Alpha,
                                         const bool        Sense = true);

  //! Make an arc of Ellipse (TrimmedCurve from Geom2d) from
  //! a Ellipse between two points P1 and P2.
  //! Please, note: The orientation of the arc is:
  //! -   the trigonometric sense if Sense is not defined or
  //! is true (default value), or
  //! -   the opposite sense if Sense is false.
  //! -   Alpha1, Alpha2 and Alpha are angle values, given in radians.
  //! -   IsDone always returns true.
  Standard_EXPORT GCE2d_MakeArcOfEllipse(const gp_Elips2d& Elips,
                                         const gp_Pnt2d&   P1,
                                         const gp_Pnt2d&   P2,
                                         const bool        Sense = true);

  //! Returns the constructed arc of ellipse.
  Standard_EXPORT const occ::handle<Geom2d_TrimmedCurve>& Value() const;

  operator const occ::handle<Geom2d_TrimmedCurve>&() const { return Value(); }

private:
  occ::handle<Geom2d_TrimmedCurve> TheArc;
};

