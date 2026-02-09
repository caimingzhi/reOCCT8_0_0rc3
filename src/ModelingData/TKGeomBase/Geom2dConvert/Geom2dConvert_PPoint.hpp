#pragma once

#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

class Adaptor2d_Curve2d;

class Geom2dConvert_PPoint
{
public:
  Standard_EXPORT inline Geom2dConvert_PPoint()
      : myParameter(::RealLast()),
        myPoint(0., 0.),
        myD1(0., 0.)
  {
  }

  Standard_EXPORT inline Geom2dConvert_PPoint(const double theParameter,
                                              const gp_XY& thePoint,
                                              const gp_XY& theD1)
      : myParameter(theParameter),
        myPoint(thePoint),
        myD1(theD1)
  {
  }

  Standard_EXPORT Geom2dConvert_PPoint(const double             theParameter,
                                       const Adaptor2d_Curve2d& theAdaptor);

  inline double Dist(const Geom2dConvert_PPoint& theOth) const
  {
    return myPoint.Distance(theOth.myPoint);
  }

  inline double Parameter() const { return myParameter; }

  inline const gp_XY& Point() const { return myPoint.XY(); }

  inline const gp_XY& D1() const { return myD1.XY(); }

  inline void SetD1(const gp_XY& theD1) { myD1.SetXY(theD1); }

  Standard_EXPORT bool operator==(const Geom2dConvert_PPoint&) const;

  Standard_EXPORT bool operator!=(const Geom2dConvert_PPoint&) const;

private:
  double   myParameter;
  gp_Pnt2d myPoint;
  gp_Vec2d myD1;
};
