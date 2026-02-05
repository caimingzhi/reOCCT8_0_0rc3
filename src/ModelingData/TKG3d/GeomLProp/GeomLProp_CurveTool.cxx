#include <Geom_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomLProp_CurveTool.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

void GeomLProp_CurveTool::Value(const occ::handle<Geom_Curve>& C, const double U, gp_Pnt& P)
{
  P = C->Value(U);
}

void GeomLProp_CurveTool::D1(const occ::handle<Geom_Curve>& C,
                             const double                   U,
                             gp_Pnt&                        P,
                             gp_Vec&                        V1)
{
  C->D1(U, P, V1);
}

void GeomLProp_CurveTool::D2(const occ::handle<Geom_Curve>& C,
                             const double                   U,
                             gp_Pnt&                        P,
                             gp_Vec&                        V1,
                             gp_Vec&                        V2)
{
  C->D2(U, P, V1, V2);
}

void GeomLProp_CurveTool::D3(const occ::handle<Geom_Curve>& C,
                             const double                   U,
                             gp_Pnt&                        P,
                             gp_Vec&                        V1,
                             gp_Vec&                        V2,
                             gp_Vec&                        V3)
{
  C->D3(U, P, V1, V2, V3);
}

int GeomLProp_CurveTool::Continuity(const occ::handle<Geom_Curve>& C)
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

double GeomLProp_CurveTool::FirstParameter(const occ::handle<Geom_Curve>& C)
{
  return C->FirstParameter();
}

double GeomLProp_CurveTool::LastParameter(const occ::handle<Geom_Curve>& C)
{
  return C->LastParameter();
}
