#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Extrema_POnCurv.hpp>
#include <Extrema_POnSurf.hpp>
class Adaptor3d_Curve;
class Adaptor3d_Surface;

class Extrema_GenLocateExtCS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_GenLocateExtCS();

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

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT double SquareDistance() const;

  Standard_EXPORT const Extrema_POnCurv& PointOnCurve() const;

  Standard_EXPORT const Extrema_POnSurf& PointOnSurface() const;

private:
  bool            myDone;
  double          mySqDist;
  Extrema_POnCurv myPoint1;
  Extrema_POnSurf myPoint2;
};
