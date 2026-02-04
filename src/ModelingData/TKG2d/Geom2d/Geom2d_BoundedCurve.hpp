#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Curve.hpp>
class gp_Pnt2d;

//! The abstract class BoundedCurve describes the
//! common behavior of bounded curves in 2D space. A
//! bounded curve is limited by two finite values of the
//! parameter, termed respectively "first parameter" and
//! "last parameter". The "first parameter" gives the "start
//! point" of the bounded curve, and the "last parameter"
//! gives the "end point" of the bounded curve.
//! The length of a bounded curve is finite.
//! The Geom2d package provides three concrete
//! classes of bounded curves:
//! - two frequently used mathematical formulations of complex curves:
//! - Geom2d_BezierCurve,
//! - Geom2d_BSplineCurve, and
//! - Geom2d_TrimmedCurve to trim a curve, i.e. to
//! only take part of the curve limited by two values of
//! the parameter of the basis curve.
class Geom2d_BoundedCurve : public Geom2d_Curve
{

public:
  //! Returns the end point of the curve.
  //! The end point is the value of the curve for the
  //! "LastParameter" of the curve.
  Standard_EXPORT virtual gp_Pnt2d EndPoint() const = 0;

  //! Returns the start point of the curve.
  //! The start point is the value of the curve for the
  //! "FirstParameter" of the curve.
  Standard_EXPORT virtual gp_Pnt2d StartPoint() const = 0;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_BoundedCurve, Geom2d_Curve)
};

