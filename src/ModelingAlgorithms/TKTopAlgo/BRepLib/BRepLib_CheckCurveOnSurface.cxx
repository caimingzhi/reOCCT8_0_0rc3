#include <Adaptor3d_CurveOnSurface.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepLib_CheckCurveOnSurface.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom_Surface.hpp>
#include <Standard_ErrorHandler.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>

BRepLib_CheckCurveOnSurface::BRepLib_CheckCurveOnSurface(const TopoDS_Edge& theEdge,
                                                         const TopoDS_Face& theFace)
    : myIsParallel(false)
{
  Init(theEdge, theFace);
}

void BRepLib_CheckCurveOnSurface::Init(const TopoDS_Edge& theEdge, const TopoDS_Face& theFace)
{
  myCOnSurfGeom.Init();

  if (theEdge.IsNull() || theFace.IsNull())
  {
    return;
  }

  if (BRep_Tool::Degenerated(theEdge) || !BRep_Tool::IsGeometric(theEdge))
  {
    return;
  }

  const occ::handle<Adaptor3d_Curve> anAdaptor3dCurve = new BRepAdaptor_Curve(theEdge);

  TopLoc_Location aLocation;
  double          aFirstParam, aLastParam;

  occ::handle<Geom2d_Curve> aGeom2dCurve =
    BRep_Tool::CurveOnSurface(theEdge, theFace, aFirstParam, aLastParam);
  occ::handle<Geom_Surface> aGeomSurface = BRep_Tool::Surface(theFace);

  occ::handle<Adaptor2d_Curve2d> anAdaptorCurve =
    new Geom2dAdaptor_Curve(aGeom2dCurve, aFirstParam, aLastParam);
  occ::handle<GeomAdaptor_Surface> aGeomAdaptorSurface = new GeomAdaptor_Surface(aGeomSurface);

  myAdaptorCurveOnSurface = new Adaptor3d_CurveOnSurface(anAdaptorCurve, aGeomAdaptorSurface);

  if (BRep_Tool::IsClosed(theEdge, theFace))
  {
    occ::handle<Geom2d_Curve> aGeom2dReversedCurve =
      BRep_Tool::CurveOnSurface(TopoDS::Edge(theEdge.Reversed()), theFace, aFirstParam, aLastParam);
    occ::handle<Adaptor2d_Curve2d> anAdaptorReversedCurve =
      new Geom2dAdaptor_Curve(aGeom2dReversedCurve, aFirstParam, aLastParam);
    myAdaptorCurveOnSurface2 =
      new Adaptor3d_CurveOnSurface(anAdaptorReversedCurve, aGeomAdaptorSurface);
  }

  myCOnSurfGeom.Init(anAdaptor3dCurve);
}

void BRepLib_CheckCurveOnSurface::Perform()
{

  Compute(myAdaptorCurveOnSurface);
  if (ErrorStatus())
  {
    return;
  }

  if (!myAdaptorCurveOnSurface2.IsNull())
  {

    Compute(myAdaptorCurveOnSurface2);
  }
}

void BRepLib_CheckCurveOnSurface::Compute(
  const occ::handle<Adaptor3d_CurveOnSurface>& theCurveOnSurface)
{
  myCOnSurfGeom.SetParallel(myIsParallel);
  myCOnSurfGeom.Perform(theCurveOnSurface);
}
