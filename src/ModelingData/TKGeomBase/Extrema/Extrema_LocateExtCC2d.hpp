#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Extrema_POnCurv2d.hpp>
class Adaptor2d_Curve2d;

//! It calculates the distance between two curves with
//! a close point; these distances can be maximum or
//! minimum.
class Extrema_LocateExtCC2d
{
public:
  DEFINE_STANDARD_ALLOC

  //! Calculates the distance with a close point. The
  //! close point is defined by a parameter value on each
  //! curve.
  //! The function F(u,v)=distance(C1(u),C2(v)) has an
  //! extremun when gradient(f)=0. The algorithm searches
  //! the zero near the close point.
  Standard_EXPORT Extrema_LocateExtCC2d(const Adaptor2d_Curve2d& C1,
                                        const Adaptor2d_Curve2d& C2,
                                        const double             U0,
                                        const double             V0);

  //! Returns True if the distance is found.
  Standard_EXPORT bool IsDone() const;

  //! Returns the value of the extremum square distance.
  Standard_EXPORT double SquareDistance() const;

  //! Returns the points of the extremum distance.
  //! P1 is on the first curve, P2 on the second one.
  Standard_EXPORT void Point(Extrema_POnCurv2d& P1, Extrema_POnCurv2d& P2) const;

private:
  bool              myDone;
  double            mySqDist;
  Extrema_POnCurv2d myPoint1;
  Extrema_POnCurv2d myPoint2;
};

