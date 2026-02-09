#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Extrema_POnCurv.hpp>
class Adaptor3d_Curve;

class Extrema_LocateExtCC
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_LocateExtCC(const Adaptor3d_Curve& C1,
                                      const Adaptor3d_Curve& C2,
                                      const double           U0,
                                      const double           V0);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT double SquareDistance() const;

  Standard_EXPORT void Point(Extrema_POnCurv& P1, Extrema_POnCurv& P2) const;

private:
  bool            myDone;
  double          mySqDist;
  Extrema_POnCurv myPoint1;
  Extrema_POnCurv myPoint2;
};
