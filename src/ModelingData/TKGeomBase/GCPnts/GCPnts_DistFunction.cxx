

#include <GCPnts_DistFunction.hpp>
#include <gp_Pnt.hpp>

GCPnts_DistFunction::GCPnts_DistFunction(const Adaptor3d_Curve& theCurve,
                                         const double           U1,
                                         const double           U2)
    : myCurve(theCurve),
      myU1(U1),
      myU2(U2)
{
  gp_Pnt P1 = theCurve.Value(U1), P2 = theCurve.Value(U2);
  if (P1.SquareDistance(P2) > gp::Resolution())
  {
    myLin = gp_Lin(P1, P2.XYZ() - P1.XYZ());
  }
  else
  {

    theCurve.D0(U1 + .01 * (U2 - U1), P2);
    myLin = gp_Lin(P1, P2.XYZ() - P1.XYZ());
  }
}

bool GCPnts_DistFunction::Value(const double X, double& F)
{
  if (X < myU1 || X > myU2)
    return false;

  F = -myLin.SquareDistance(myCurve.Value(X));
  return true;
}

GCPnts_DistFunctionMV::GCPnts_DistFunctionMV(GCPnts_DistFunction& theCurvLinDist)
    : myMaxCurvLinDist(theCurvLinDist)
{
}

bool GCPnts_DistFunctionMV::Value(const math_Vector& X, double& F)
{
  bool Ok = myMaxCurvLinDist.Value(X(1), F);
  return Ok;
}

int GCPnts_DistFunctionMV::NbVariables() const
{
  return 1;
}
