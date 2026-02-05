#include <Bisector.hpp>
#include <Geom2d_Curve.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

//=================================================================================================

bool Bisector::IsConvex(const occ::handle<Geom2d_Curve>& Cu, const double Sign)
{

  double   U1 = (Cu->LastParameter() + Cu->FirstParameter()) / 2.;
  gp_Pnt2d P1;
  gp_Vec2d V1, V2;
  Cu->D2(U1, P1, V1, V2);
  double Tol = 1.e-5;
  return Sign * (V1 ^ V2) < Tol;
}
