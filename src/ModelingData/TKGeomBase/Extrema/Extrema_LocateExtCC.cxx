#include <Adaptor3d_Curve.hpp>
#include <Extrema_LocateExtCC.hpp>
#include <Extrema_LocECC.hpp>
#include <Extrema_POnCurv.hpp>
#include <Precision.hpp>
#include <StdFail_NotDone.hpp>

Extrema_LocateExtCC::Extrema_LocateExtCC(const Adaptor3d_Curve& C1,
                                         const Adaptor3d_Curve& C2,
                                         const double           U0,
                                         const double           V0)
    : mySqDist(RealLast())
{
  double          TolU = C1.Resolution(Precision::Confusion());
  double          TolV = C2.Resolution(Precision::Confusion());
  Extrema_POnCurv P1, P2;

  Extrema_LocECC Xtrem(C1, C2, U0, V0, TolU, TolV);

  myDone = Xtrem.IsDone();
  if (Xtrem.IsDone())
  {
    mySqDist = Xtrem.SquareDistance();
    Xtrem.Point(P1, P2);
    myPoint1 = P1;
    myPoint2 = P2;
  }
}

bool Extrema_LocateExtCC::IsDone() const
{

  return myDone;
}

double Extrema_LocateExtCC::SquareDistance() const
{

  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return mySqDist;
}

void Extrema_LocateExtCC::Point(Extrema_POnCurv& P1, Extrema_POnCurv& P2) const
{

  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  P1 = myPoint1;
  P2 = myPoint2;
}
