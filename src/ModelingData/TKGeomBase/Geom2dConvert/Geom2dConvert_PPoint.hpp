#pragma once


#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

class Adaptor2d_Curve2d;

//! Class representing a point on curve, with 2D coordinate and the tangent
class Geom2dConvert_PPoint
{
public:
  //! Empty constructor.
  Standard_EXPORT inline Geom2dConvert_PPoint()
      : myParameter(::RealLast()),
        myPoint(0., 0.),
        myD1(0., 0.)
  {
  }

  //! Constructor.
  Standard_EXPORT inline Geom2dConvert_PPoint(const double theParameter,
                                              const gp_XY& thePoint,
                                              const gp_XY& theD1)
      : myParameter(theParameter),
        myPoint(thePoint),
        myD1(theD1)
  {
  }

  //! Constructor.
  Standard_EXPORT Geom2dConvert_PPoint(const double             theParameter,
                                       const Adaptor2d_Curve2d& theAdaptor);

  //! Compute the distance between two 2d points.
  inline double Dist(const Geom2dConvert_PPoint& theOth) const
  {
    return myPoint.Distance(theOth.myPoint);
  }

  //! Query the parameter value.
  inline double Parameter() const { return myParameter; }

  //! Query the point location.
  inline const gp_XY& Point() const { return myPoint.XY(); }

  //! Query the first derivatives.
  inline const gp_XY& D1() const { return myD1.XY(); }

  //! Change the value of the derivative at the point.
  inline void SetD1(const gp_XY& theD1) { myD1.SetXY(theD1); }

  //! Compare two values of this type.
  Standard_EXPORT bool operator==(const Geom2dConvert_PPoint&) const;

  //! Compare two values of this type.
  Standard_EXPORT bool operator!=(const Geom2dConvert_PPoint&) const;

private:
  double   myParameter; //! Parameter value
  gp_Pnt2d myPoint;     //! Point location
  gp_Vec2d myD1;        //! derivatives by parameter (components of the tangent).
};

