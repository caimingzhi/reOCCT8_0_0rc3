

#include <Geom_CartesianPoint.hpp>
#include <Geom_Point.hpp>
#include <GeomToIGES_GeomPoint.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESGeom_Point.hpp>

GeomToIGES_GeomPoint::GeomToIGES_GeomPoint(const GeomToIGES_GeomEntity& GE)
    : GeomToIGES_GeomEntity(GE)
{
}

GeomToIGES_GeomPoint::GeomToIGES_GeomPoint()

  = default;

occ::handle<IGESGeom_Point> GeomToIGES_GeomPoint::TransferPoint(const occ::handle<Geom_Point>& P)
{
  occ::handle<IGESGeom_Point> Piges = new IGESGeom_Point;
  if (P.IsNull())
  {
    return Piges;
  }

  double X, Y, Z;
  P->Coord(X, Y, Z);
  occ::handle<IGESBasic_SubfigureDef> voidsubdef;
  Piges->Init(gp_XYZ(X / GetUnit(), Y / GetUnit(), Z / GetUnit()), voidsubdef);
  return Piges;
}

occ::handle<IGESGeom_Point> GeomToIGES_GeomPoint::TransferPoint(
  const occ::handle<Geom_CartesianPoint>& P)
{

  occ::handle<IGESGeom_Point> Piges = new IGESGeom_Point;
  if (P.IsNull())
  {
    return Piges;
  }

  double X, Y, Z;
  P->Coord(X, Y, Z);
  occ::handle<IGESBasic_SubfigureDef> voidsubdef;
  Piges->Init(gp_XYZ(X / GetUnit(), Y / GetUnit(), Z / GetUnit()), voidsubdef);
  return Piges;
}
