#include <Adaptor3d_Curve.hpp>
#include <GeomFill_PlanFunc.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

GeomFill_PlanFunc::GeomFill_PlanFunc(const gp_Pnt&                       theP,
                                     const gp_Vec&                       theV,
                                     const occ::handle<Adaptor3d_Curve>& theC)
    : myCurve(theC)
{
  myPnt = theP.XYZ();
  myVec = theV.XYZ();
}

bool GeomFill_PlanFunc::Value(const double X, double& F)
{
  myCurve->D0(X, G);
  V.SetLinearForm(-1, myPnt, G.XYZ());
  F = myVec.Dot(V);
  return true;
}

bool GeomFill_PlanFunc::Derivative(const double X, double& D)
{
  gp_Vec dg;
  myCurve->D1(X, G, dg);
  D = myVec.Dot(dg.XYZ());

  return true;
}

bool GeomFill_PlanFunc::Values(const double X, double& F, double& D)
{
  gp_Vec dg;
  myCurve->D1(X, G, dg);
  V.SetLinearForm(-1, myPnt, G.XYZ());
  F = myVec.Dot(V);
  D = myVec.Dot(dg.XYZ());

  return true;
}

// void  GeomFill_PlanFunc::D2(const double  X,
//			    double& F,
//			    double& D1,
//			    double& D2)
void GeomFill_PlanFunc::D2(const double, double&, double&, double&) {}

void GeomFill_PlanFunc::DEDT(const double X, const gp_Vec& DPnt, const gp_Vec& DVec, double& DFDT)
{
  myCurve->D0(X, G);
  V.SetLinearForm(-1, myPnt, G.XYZ());
  DFDT = DVec.Dot(V) - myVec.Dot(DPnt.XYZ());
}

void GeomFill_PlanFunc::D2E(const double  X,
                            const gp_Vec& DP,
                            //			     const gp_Vec& D2P,
                            const gp_Vec&,
                            const gp_Vec& DV,
                            //			     const gp_Vec& D2V,
                            const gp_Vec&,
                            double& DFDT,
                            //			     double& ,
                            double& /*D2FDT2*/,
                            //			     double& D2FDTDX)
                            double&)
{
  gp_Vec dg;
  myCurve->D1(X, G, dg);
  gp_XYZ DVDT;
  V.SetLinearForm(-1, myPnt, G.XYZ());
  DVDT.SetLinearForm(-1, DP.XYZ(), G.XYZ());
  DFDT = DV.Dot(V) + myVec.Dot(DVDT);
}
