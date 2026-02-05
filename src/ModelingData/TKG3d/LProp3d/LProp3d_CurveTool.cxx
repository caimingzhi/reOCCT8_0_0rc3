#include <Adaptor3d_Curve.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <LProp3d_CurveTool.hpp>

//=================================================================================================

void LProp3d_CurveTool::Value(const occ::handle<Adaptor3d_Curve>& C, const double U, gp_Pnt& P)
{
  P = C->Value(U);
}

//=================================================================================================

void LProp3d_CurveTool::D1(const occ::handle<Adaptor3d_Curve>& C,
                           const double                        U,
                           gp_Pnt&                             P,
                           gp_Vec&                             V1)
{
  C->D1(U, P, V1);
}

//=================================================================================================

void LProp3d_CurveTool::D2(const occ::handle<Adaptor3d_Curve>& C,
                           const double                        U,
                           gp_Pnt&                             P,
                           gp_Vec&                             V1,
                           gp_Vec&                             V2)
{
  C->D2(U, P, V1, V2);
}

//=================================================================================================

void LProp3d_CurveTool::D3(const occ::handle<Adaptor3d_Curve>& C,
                           const double                        U,
                           gp_Pnt&                             P,
                           gp_Vec&                             V1,
                           gp_Vec&                             V2,
                           gp_Vec&                             V3)
{
  C->D3(U, P, V1, V2, V3);
}

//=================================================================================================

int LProp3d_CurveTool::Continuity(const occ::handle<Adaptor3d_Curve>& C)
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

//=================================================================================================

double LProp3d_CurveTool::FirstParameter(const occ::handle<Adaptor3d_Curve>& C)
{
  return C->FirstParameter();
}

//=================================================================================================

double LProp3d_CurveTool::LastParameter(const occ::handle<Adaptor3d_Curve>& C)
{
  return C->LastParameter();
}
