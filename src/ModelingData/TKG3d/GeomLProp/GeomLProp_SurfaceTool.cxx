#include <Geom_Surface.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomLProp_SurfaceTool.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

void GeomLProp_SurfaceTool::Value(const occ::handle<Geom_Surface>& S,
                                  const double                     U,
                                  const double                     V,
                                  gp_Pnt&                          P)
{
  P = S->Value(U, V);
}

void GeomLProp_SurfaceTool::D1(const occ::handle<Geom_Surface>& S,
                               const double                     U,
                               const double                     V,
                               gp_Pnt&                          P,
                               gp_Vec&                          D1U,
                               gp_Vec&                          D1V)
{
  S->D1(U, V, P, D1U, D1V);
}

void GeomLProp_SurfaceTool::D2(const occ::handle<Geom_Surface>& S,
                               const double                     U,
                               const double                     V,
                               gp_Pnt&                          P,
                               gp_Vec&                          D1U,
                               gp_Vec&                          D1V,
                               gp_Vec&                          D2U,
                               gp_Vec&                          D2V,
                               gp_Vec&                          DUV)
{
  S->D2(U, V, P, D1U, D1V, D2U, D2V, DUV);
}

gp_Vec GeomLProp_SurfaceTool::DN(const occ::handle<Geom_Surface>& S,
                                 const double                     U,
                                 const double                     V,
                                 const int                        IU,
                                 const int                        IV)
{
  return S->DN(U, V, IU, IV);
}

int GeomLProp_SurfaceTool::Continuity(const occ::handle<Geom_Surface>& S)
{
  GeomAbs_Shape s = S->Continuity();
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

void GeomLProp_SurfaceTool::Bounds(const occ::handle<Geom_Surface>& S,
                                   double&                          U1,
                                   double&                          V1,
                                   double&                          U2,
                                   double&                          V2)
{
  S->Bounds(U1, U2, V1, V2);
}
