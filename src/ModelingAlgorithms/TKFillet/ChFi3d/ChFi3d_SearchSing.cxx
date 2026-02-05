#include <ChFi3d_SearchSing.hpp>
#include <Geom_Curve.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

ChFi3d_SearchSing::ChFi3d_SearchSing(const occ::handle<Geom_Curve>& C1,
                                     const occ::handle<Geom_Curve>& C2)
{
  myC1 = C1;
  myC2 = C2;
}

bool ChFi3d_SearchSing::Value(const double X, double& F)
{
  gp_Pnt P1, P2;
  gp_Vec V1, V2;
  myC1->D1(X, P1, V1);
  myC2->D1(X, P2, V2);
  gp_Vec V(P1, P2);
  F = V * (V2 - V1);
  return true;
}

bool ChFi3d_SearchSing::Derivative(const double X, double& D)
{
  gp_Pnt P1, P2;
  gp_Vec V1, V2, W1, W2;
  myC1->D2(X, P1, V1, W1);
  myC2->D2(X, P2, V2, W2);
  gp_Vec V(P1, P2), VPrim;
  VPrim = V2 - V1;
  D     = VPrim.SquareMagnitude() + (V * (W2 - W1));
  return true;
}

bool ChFi3d_SearchSing::Values(const double X, double& F, double& D)
{
  gp_Pnt P1, P2;
  gp_Vec V1, V2, W1, W2;
  myC1->D2(X, P1, V1, W1);
  myC2->D2(X, P2, V2, W2);
  gp_Vec V(P1, P2), VPrim;
  VPrim = V2 - V1;
  F     = V * VPrim;
  D     = VPrim.SquareMagnitude() + (V * (W2 - W1));
  return true;
}
