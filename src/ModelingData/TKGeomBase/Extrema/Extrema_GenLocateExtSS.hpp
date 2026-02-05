#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Extrema_POnSurf.hpp>
class Adaptor3d_Surface;

//! With two close points it calculates the distance
//! between two surfaces.
//! This distance can be a minimum or a maximum.
class Extrema_GenLocateExtSS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_GenLocateExtSS();

  //! Calculates the distance with two close points.
  //! The close points are defined by the parameter values
  //! (U1,V1) for S1 and (U2,V2) for S2.
  //! The function F(u1,v1,u2,v2)=distance(S1(u1,v1),S2(u2,v2))
  //! has an extremun when gradient(F)=0. The algorithm searches
  //! a zero near the close points.
  Standard_EXPORT Extrema_GenLocateExtSS(const Adaptor3d_Surface& S1,
                                         const Adaptor3d_Surface& S2,
                                         const double             U1,
                                         const double             V1,
                                         const double             U2,
                                         const double             V2,
                                         const double             Tol1,
                                         const double             Tol2);

  Standard_EXPORT void Perform(const Adaptor3d_Surface& S1,
                               const Adaptor3d_Surface& S2,
                               const double             U1,
                               const double             V1,
                               const double             U2,
                               const double             V2,
                               const double             Tol1,
                               const double             Tol2);

  //! Returns True if the distance is found.
  Standard_EXPORT bool IsDone() const;

  //! Returns the value of the extremum square distance.
  Standard_EXPORT double SquareDistance() const;

  //! Returns the point of the extremum distance on S1.
  Standard_EXPORT const Extrema_POnSurf& PointOnS1() const;

  //! Returns the point of the extremum distance on S2.
  Standard_EXPORT const Extrema_POnSurf& PointOnS2() const;

private:
  bool            myDone;
  double          mySqDist;
  Extrema_POnSurf myPoint1;
  Extrema_POnSurf myPoint2;
};
