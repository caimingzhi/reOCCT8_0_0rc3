#include <Geom2d_Curve.hpp>
#include <Geom2dLProp_Curve2dTool.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

void Geom2dLProp_Curve2dTool::Value(const occ::handle<Geom2d_Curve>& C, const double U, gp_Pnt2d& P)
{
  P = C->Value(U);
}

void Geom2dLProp_Curve2dTool::D1(const occ::handle<Geom2d_Curve>& C,
                                 const double                     U,
                                 gp_Pnt2d&                        P,
                                 gp_Vec2d&                        V1)
{
  C->D1(U, P, V1);
}

void Geom2dLProp_Curve2dTool::D2(const occ::handle<Geom2d_Curve>& C,
                                 const double                     U,
                                 gp_Pnt2d&                        P,
                                 gp_Vec2d&                        V1,
                                 gp_Vec2d&                        V2)
{
  C->D2(U, P, V1, V2);
}

void Geom2dLProp_Curve2dTool::D3(const occ::handle<Geom2d_Curve>& C,
                                 const double                     U,
                                 gp_Pnt2d&                        P,
                                 gp_Vec2d&                        V1,
                                 gp_Vec2d&                        V2,
                                 gp_Vec2d&                        V3)
{
  C->D3(U, P, V1, V2, V3);
}

int Geom2dLProp_Curve2dTool::Continuity(const occ::handle<Geom2d_Curve>& C)
{
  GeomAbs_Shape s = C->Continuity();
  switch (s)
  {
    case GeomAbs_C0:
      return 0;
    case GeomAbs_C1:
      return 1;
    case GeomAbs_C2:
      return 2;
    case GeomAbs_C3:
      return 3;
    case GeomAbs_G1:
      return 0;
    case GeomAbs_G2:
      return 0;
    case GeomAbs_CN:
      return 3;
  };
  return 0;
}

double Geom2dLProp_Curve2dTool::FirstParameter(const occ::handle<Geom2d_Curve>& C)
{
  return C->FirstParameter();
}

double Geom2dLProp_Curve2dTool::LastParameter(const occ::handle<Geom2d_Curve>& C)
{
  return C->LastParameter();
}
