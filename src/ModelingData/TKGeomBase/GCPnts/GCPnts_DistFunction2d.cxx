

#include <GCPnts_DistFunction2d.hpp>
#include <gp_Pnt2d.hpp>

GCPnts_DistFunction2d::GCPnts_DistFunction2d(const Adaptor2d_Curve2d& theCurve,
                                             const double             U1,
                                             const double             U2)
    : myCurve(theCurve),
      myU1(U1),
      myU2(U2)
{
  gp_Pnt2d P2d1 = theCurve.Value(U1), P2d2 = theCurve.Value(U2);
  if (P2d1.SquareDistance(P2d2) > gp::Resolution())
  {
    myLin = gp_Lin2d(P2d1, P2d2.XY() - P2d1.XY());
  }
  else
  {

    theCurve.D0(U1 + .01 * (U2 - U1), P2d2);
    myLin = gp_Lin2d(P2d1, P2d2.XY() - P2d1.XY());
  }
}

bool GCPnts_DistFunction2d::Value(const double X, double& F)
{
  if (X < myU1 || X > myU2)
    return false;

  gp_Pnt2d aP2d = myCurve.Value(X);
  F             = -myLin.SquareDistance(aP2d);
  return true;
}

GCPnts_DistFunction2dMV::GCPnts_DistFunction2dMV(GCPnts_DistFunction2d& theCurvLinDist)
    : myMaxCurvLinDist(theCurvLinDist)
{
}

bool GCPnts_DistFunction2dMV::Value(const math_Vector& X, double& F)
{
  bool Ok = myMaxCurvLinDist.Value(X(1), F);
  return Ok;
}

int GCPnts_DistFunction2dMV::NbVariables() const
{
  return 1;
}
