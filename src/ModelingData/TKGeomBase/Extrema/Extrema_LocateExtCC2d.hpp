#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Extrema_POnCurv2d.hpp>
class Adaptor2d_Curve2d;

class Extrema_LocateExtCC2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_LocateExtCC2d(const Adaptor2d_Curve2d& C1,
                                        const Adaptor2d_Curve2d& C2,
                                        const double             U0,
                                        const double             V0);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT double SquareDistance() const;

  Standard_EXPORT void Point(Extrema_POnCurv2d& P1, Extrema_POnCurv2d& P2) const;

private:
  bool              myDone;
  double            mySqDist;
  Extrema_POnCurv2d myPoint1;
  Extrema_POnCurv2d myPoint2;
};
