#include <BRepAdaptor_Curve.hpp>
#include <BRepLProp_CurveTool.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

void BRepLProp_CurveTool::Value(const BRepAdaptor_Curve& C, const double U, gp_Pnt& P)
{
  P = C.Value(U);
}

void BRepLProp_CurveTool::D1(const BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& V1)
{
  C.D1(U, P, V1);
}

void BRepLProp_CurveTool::D2(const BRepAdaptor_Curve& C,
                             const double             U,
                             gp_Pnt&                  P,
                             gp_Vec&                  V1,
                             gp_Vec&                  V2)
{
  C.D2(U, P, V1, V2);
}

void BRepLProp_CurveTool::D3(const BRepAdaptor_Curve& C,
                             const double             U,
                             gp_Pnt&                  P,
                             gp_Vec&                  V1,
                             gp_Vec&                  V2,
                             gp_Vec&                  V3)
{
  C.D3(U, P, V1, V2, V3);
}

int BRepLProp_CurveTool::Continuity(const BRepAdaptor_Curve& C)
{
  GeomAbs_Shape s = C.Continuity();
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

double BRepLProp_CurveTool::FirstParameter(const BRepAdaptor_Curve& C)
{
  return C.FirstParameter();
}

double BRepLProp_CurveTool::LastParameter(const BRepAdaptor_Curve& C)
{
  return C.LastParameter();
}
