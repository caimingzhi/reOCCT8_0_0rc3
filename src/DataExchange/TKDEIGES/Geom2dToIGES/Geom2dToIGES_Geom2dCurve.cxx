#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2dToIGES_Geom2dCurve.hpp>
#include <Geom2dToIGES_Geom2dEntity.hpp>
#include <GeomAPI.hpp>
#include <GeomToIGES_GeomCurve.hpp>
#include <gp_Circ.hpp>
#include <gp_Pln.hpp>
#include <IGESGeom_BSplineCurve.hpp>

Geom2dToIGES_Geom2dCurve::Geom2dToIGES_Geom2dCurve()

  = default;

Geom2dToIGES_Geom2dCurve::Geom2dToIGES_Geom2dCurve(const Geom2dToIGES_Geom2dEntity& G2dE)
    : Geom2dToIGES_Geom2dEntity(G2dE)
{
}

occ::handle<IGESData_IGESEntity> Geom2dToIGES_Geom2dCurve::Transfer2dCurve(
  const occ::handle<Geom2d_Curve>& start,
  const double                     Udeb,
  const double                     Ufin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  GeomToIGES_GeomCurve GC;
  GC.SetModel(GetModel());
  GC.SetUnit(1.);
  return GC.TransferCurve(GeomAPI::To3d(start, gp_Pln(0, 0, 1, 0)), Udeb, Ufin);
}
