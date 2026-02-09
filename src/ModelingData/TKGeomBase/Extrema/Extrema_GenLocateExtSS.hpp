#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Extrema_POnSurf.hpp>
class Adaptor3d_Surface;

class Extrema_GenLocateExtSS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_GenLocateExtSS();

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

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT double SquareDistance() const;

  Standard_EXPORT const Extrema_POnSurf& PointOnS1() const;

  Standard_EXPORT const Extrema_POnSurf& PointOnS2() const;

private:
  bool            myDone;
  double          mySqDist;
  Extrema_POnSurf myPoint1;
  Extrema_POnSurf myPoint2;
};
