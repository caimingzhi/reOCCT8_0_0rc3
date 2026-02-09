#include <BRepAdaptor_Surface.hpp>
#include <BRepLProp_SurfaceTool.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

void BRepLProp_SurfaceTool::Value(const BRepAdaptor_Surface& S,
                                  const double               U,
                                  const double               V,
                                  gp_Pnt&                    P)
{
  P = S.Value(U, V);
}

void BRepLProp_SurfaceTool::D1(const BRepAdaptor_Surface& S,
                               const double               U,
                               const double               V,
                               gp_Pnt&                    P,
                               gp_Vec&                    D1U,
                               gp_Vec&                    D1V)
{
  S.D1(U, V, P, D1U, D1V);
}

void BRepLProp_SurfaceTool::D2(const BRepAdaptor_Surface& S,
                               const double               U,
                               const double               V,
                               gp_Pnt&                    P,
                               gp_Vec&                    D1U,
                               gp_Vec&                    D1V,
                               gp_Vec&                    D2U,
                               gp_Vec&                    D2V,
                               gp_Vec&                    DUV)
{
  S.D2(U, V, P, D1U, D1V, D2U, D2V, DUV);
}

gp_Vec BRepLProp_SurfaceTool::DN(const BRepAdaptor_Surface& S,
                                 const double               U,
                                 const double               V,
                                 const int                  IU,
                                 const int                  IV)
{
  return S.DN(U, V, IU, IV);
}

int BRepLProp_SurfaceTool::Continuity(const BRepAdaptor_Surface& S)
{
  GeomAbs_Shape s = std::min(S.UContinuity(), S.VContinuity());
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

void BRepLProp_SurfaceTool::Bounds(const BRepAdaptor_Surface& S,
                                   double&                    U1,
                                   double&                    V1,
                                   double&                    U2,
                                   double&                    V2)
{
  U1 = S.FirstUParameter();
  V1 = S.FirstVParameter();
  U2 = S.LastUParameter();
  V2 = S.LastVParameter();
}
