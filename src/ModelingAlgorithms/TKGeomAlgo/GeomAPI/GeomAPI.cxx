#include <GeomAPI.hpp>

#include <Adaptor3d_CurveOnSurface.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Plane.hpp>
#include <GeomAdaptor.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <gp_Pln.hpp>
#include <ProjLib_ProjectedCurve.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

occ::handle<Geom2d_Curve> GeomAPI::To2d(const occ::handle<Geom_Curve>& C, const gp_Pln& P)
{
  occ::handle<Geom2d_Curve>        result;
  occ::handle<GeomAdaptor_Curve>   HC    = new GeomAdaptor_Curve(C);
  occ::handle<Geom_Plane>          Plane = new Geom_Plane(P);
  occ::handle<GeomAdaptor_Surface> HS    = new GeomAdaptor_Surface(Plane);

  ProjLib_ProjectedCurve Proj(HS, HC);

  if (Proj.GetType() != GeomAbs_OffsetCurve && Proj.GetType() != GeomAbs_OtherCurve)
  {
    result = Geom2dAdaptor::MakeCurve(Proj);
  }

  return result;
}

occ::handle<Geom_Curve> GeomAPI::To3d(const occ::handle<Geom2d_Curve>& C, const gp_Pln& P)
{
  occ::handle<Geom2dAdaptor_Curve> AHC = new Geom2dAdaptor_Curve(C);

  occ::handle<Geom_Plane>          ThePlane = new Geom_Plane(P);
  occ::handle<GeomAdaptor_Surface> AHS      = new GeomAdaptor_Surface(ThePlane);

  Adaptor3d_CurveOnSurface COS(AHC, AHS);
  return GeomAdaptor::MakeCurve(COS);
}
