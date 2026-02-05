#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Extrema_POnCurv.hpp>
#include <Extrema_POnSurf.hpp>
class Adaptor3d_Curve;
class Adaptor3d_Surface;

//! With two close points it calculates the distance
//! between two surfaces.
//! This distance can be a minimum or a maximum.
class Extrema_GenLocateExtCS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_GenLocateExtCS();

  //! Calculates the distance with two close points.
  //! The close points are defined by the parameter values
  //! T for C and (U,V) for S.
  //! The function F(t,u,v)=distance(C(t),S(u,v))
  //! has an extremun when gradient(F)=0. The algorithm searches
  //! a zero near the close points.
  Standard_EXPORT Extrema_GenLocateExtCS(const Adaptor3d_Curve&   C,
                                         const Adaptor3d_Surface& S,
                                         const double             T,
                                         const double             U,
                                         const double             V,
                                         const double             Tol1,
                                         const double             Tol2);

  Standard_EXPORT void Perform(const Adaptor3d_Curve&   C,
                               const Adaptor3d_Surface& S,
                               const double             T,
                               const double             U,
                               const double             V,
                               const double             Tol1,
                               const double             Tol2);

  //! Returns True if the distance is found.
  Standard_EXPORT bool IsDone() const;

  //! Returns the value of the extremum square distance.
  Standard_EXPORT double SquareDistance() const;

  //! Returns the point of the extremum distance on C.
  Standard_EXPORT const Extrema_POnCurv& PointOnCurve() const;

  //! Returns the point of the extremum distance on S.
  Standard_EXPORT const Extrema_POnSurf& PointOnSurface() const;

private:
  bool            myDone;
  double          mySqDist;
  Extrema_POnCurv myPoint1;
  Extrema_POnSurf myPoint2;
};
