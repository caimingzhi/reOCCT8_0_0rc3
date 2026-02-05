#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_TrimmedCurve.hpp>

class gp_Pnt;
class gp_Lin;

//! Implements construction algorithms for a line
//! segment in 3D space.
//! Makes a segment of Line from the 2 points <P1> and <P2>.
//! The result is a Geom_TrimmedCurve curve.
//! A MakeSegment object provides a framework for:
//! -   defining the construction of the line segment,
//! -   implementing the construction algorithm, and
//! -   consulting the results. In particular, the Value
//! function returns the constructed line segment.
class GC_MakeSegment : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Make a segment of Line from the 2 points <P1> and <P2>.
  //! It returns NullObject if <P1> and <P2> are confused.
  Standard_EXPORT GC_MakeSegment(const gp_Pnt& P1, const gp_Pnt& P2);

  //! Make a segment of Line from the line <Line1>
  //! between the two parameters U1 and U2.
  //! It returns NullObject if <U1> is equal <U2>.
  Standard_EXPORT GC_MakeSegment(const gp_Lin& Line, const double U1, const double U2);

  //! Make a segment of Line from the line <Line1>
  //! between the point <Point> and the parameter Ulast.
  //! It returns NullObject if <U1> is equal <U2>.
  Standard_EXPORT GC_MakeSegment(const gp_Lin& Line, const gp_Pnt& Point, const double Ulast);

  //! Make a segment of Line from the line <Line1>
  //! between the two points <P1> and <P2>.
  //! It returns NullObject if <U1> is equal <U2>.
  Standard_EXPORT GC_MakeSegment(const gp_Lin& Line, const gp_Pnt& P1, const gp_Pnt& P2);

  //! Returns the constructed line segment.
  Standard_EXPORT const occ::handle<Geom_TrimmedCurve>& Value() const;

  operator const occ::handle<Geom_TrimmedCurve>&() const { return Value(); }

private:
  occ::handle<Geom_TrimmedCurve> TheSegment;
};
