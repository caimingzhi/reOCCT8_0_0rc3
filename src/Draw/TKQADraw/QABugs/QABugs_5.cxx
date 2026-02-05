#include <QABugs.hpp>

#include <Draw_Interpretor.hpp>
#include <Adaptor3d_Curve.hpp>
#include <DrawTrSurf.hpp>
#include <DBRep.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <TopoDS.hpp>
#include <BRepAdaptor_CompCurve.hpp>
#include <IntCurveSurface_HInter.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <TopoDS_Edge.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <Standard_ErrorHandler.hpp>

#include <cstdio>
#include <cstdlib>

static int OCC6001(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 4)
  {
    di << "missing parameters\n";
    return 1;
  }
  const char*                  name = argv[1];
  occ::handle<Adaptor3d_Curve> hcurve;
  occ::handle<Geom_Curve>      curve = DrawTrSurf::GetCurve(argv[2]);
  if (!curve.IsNull())
    hcurve = new GeomAdaptor_Curve(curve);
  else
  {
    TopoDS_Shape wire = DBRep::Get(argv[2]);
    if (wire.IsNull() || wire.ShapeType() != TopAbs_WIRE)
    {
      di << "incorrect 1st parameter, curve or wire expected\n";
      return 1;
    }
    BRepAdaptor_CompCurve comp_curve(TopoDS::Wire(wire));
    hcurve = new BRepAdaptor_CompCurve(comp_curve);
  }
  occ::handle<Geom_Surface>        surf  = DrawTrSurf::GetSurface(argv[3]);
  occ::handle<GeomAdaptor_Surface> hsurf = new GeomAdaptor_Surface(surf);
  IntCurveSurface_HInter           inter;
  inter.Perform(hcurve, hsurf);
  int nb = inter.NbPoints();
  if (!inter.IsDone() || nb == 0)
  {
    di << "no intersections";
    return 0;
  }
  for (int i = 1; i <= nb; i++)
  {
    const IntCurveSurface_IntersectionPoint& int_pnt = inter.Point(i);
    double                                   par     = int_pnt.W();
    gp_Pnt                                   p       = int_pnt.Pnt();
    di << "inter " << i << ": W = " << par << "\n"
       << "\tpnt = " << p.X() << " " << p.Y() << " " << p.Z() << "\n";
    char n[20], *pname = n;
    Sprintf(n, "%s_%d", name, i);
    DrawTrSurf::Set(pname, p);
  }

  return 0;
}

void QABugs::Commands_5(Draw_Interpretor& theCommands)
{
  const char* group = "QABugs";

  theCommands.Add("OCC6001",
                  "OCC6001 name curve/wire surface\n\t\tintersect curve by surface",
                  __FILE__,
                  OCC6001,
                  group);

  return;
}
