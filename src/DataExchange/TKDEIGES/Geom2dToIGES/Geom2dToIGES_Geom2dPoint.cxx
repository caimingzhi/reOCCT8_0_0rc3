#include <Geom2d_CartesianPoint.hpp>
#include <Geom2d_Point.hpp>
#include <Geom2dToIGES_Geom2dPoint.hpp>
#include <gp_XYZ.hpp>
#include <IGESGeom_Point.hpp>

//=============================================================================
// Geom2dToIGES_Geom2dPoint
//=============================================================================
Geom2dToIGES_Geom2dPoint::Geom2dToIGES_Geom2dPoint()

  = default;

//=============================================================================
// Geom2dToIGES_Geom2dPoint
//=============================================================================

Geom2dToIGES_Geom2dPoint::Geom2dToIGES_Geom2dPoint(const Geom2dToIGES_Geom2dEntity& G2dE)
    : Geom2dToIGES_Geom2dEntity(G2dE)
{
}

//=============================================================================
// Transfer of Point2d from Geom2d to IGES
// Tranfer2dPoint
//=============================================================================

occ::handle<IGESGeom_Point> Geom2dToIGES_Geom2dPoint::Transfer2dPoint(
  const occ::handle<Geom2d_Point>& P)
{

  occ::handle<IGESGeom_Point> Piges = new IGESGeom_Point;
  if (P.IsNull())
  {
    return Piges;
  }

  double X, Y;
  P->Coord(X, Y);
  occ::handle<IGESBasic_SubfigureDef> voidsubdef;
  Piges->Init(gp_XYZ(X, Y, 0.), voidsubdef);
  return Piges;
}

//=============================================================================
// Transfer of CartesianPoint from Geom2d to IGES
// Tranfer2dPoint
//=============================================================================

occ::handle<IGESGeom_Point> Geom2dToIGES_Geom2dPoint::Transfer2dPoint(
  const occ::handle<Geom2d_CartesianPoint>& P)
{

  occ::handle<IGESGeom_Point> Piges = new IGESGeom_Point;
  if (P.IsNull())
  {
    return Piges;
  }

  double X, Y;
  P->Coord(X, Y);
  occ::handle<IGESBasic_SubfigureDef> voidsubdef;
  Piges->Init(gp_XYZ(X, Y, 0.), voidsubdef);
  return Piges;
}
