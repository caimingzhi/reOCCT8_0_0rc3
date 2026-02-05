#include <Extrema_LocateExtCC2d.hpp>

#include <StdFail_NotDone.hpp>
#include <Extrema_POnCurv2d.hpp>

#include <Extrema_Curve2dTool.hpp>
#include <Extrema_LocECC2d.hpp>

//=================================================================================================

Extrema_LocateExtCC2d::Extrema_LocateExtCC2d(const Adaptor2d_Curve2d& C1,
                                             const Adaptor2d_Curve2d& C2,
                                             const double             U0,
                                             const double             V0)
    : mySqDist(RealLast())
{
  double            TolU = Extrema_Curve2dTool::Resolution(C1, Precision::Confusion());
  double            TolV = Extrema_Curve2dTool::Resolution(C2, Precision::Confusion());
  Extrema_POnCurv2d P1, P2;

  // Non implemente pour l instant: l appel a Geom2dExtrema_ExtCC.

  Extrema_LocECC2d Xtrem(C1, C2, U0, V0, TolU, TolV);
  // Exploitation

  myDone = Xtrem.IsDone();
  if (Xtrem.IsDone())
  {
    mySqDist = Xtrem.SquareDistance();
    Xtrem.Point(P1, P2);
    myPoint1 = P1;
    myPoint2 = P2;
  }
}

//=================================================================================================

bool Extrema_LocateExtCC2d::IsDone() const
{

  return myDone;
}

//=================================================================================================

double Extrema_LocateExtCC2d::SquareDistance() const
{

  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return mySqDist;
}

//=================================================================================================

void Extrema_LocateExtCC2d::Point(Extrema_POnCurv2d& P1, Extrema_POnCurv2d& P2) const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  P1 = myPoint1;
  P2 = myPoint2;
}
