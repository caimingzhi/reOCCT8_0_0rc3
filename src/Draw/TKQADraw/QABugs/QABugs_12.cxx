#include <QABugs.hpp>

#include <Draw.hpp>
#include <Draw_Interpretor.hpp>
#include <DBRep.hpp>
#include <AIS_InteractiveContext.hpp>
#include <TopoDS_Shape.hpp>

#include <gp_Pnt.hpp>
#include <gp_Ax2.hpp>
#include <gp.hpp>
#include <gp_Ax1.hpp>
#include <gce_MakeCirc.hpp>
#include <gp_Circ.hpp>
#include <GC_MakeArcOfCircle.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <TopoDS_Wire.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <BRepOffsetAPI_ThruSections.hpp>

static int OCC895(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 2 || argc > 5)
  {
    di << "Usage : " << argv[0] << " result [angle [reverse [order]]]\n";
    return 1;
  }

  const double rad     = 1.0;
  const double angle   = (argc > 2) ? Draw::Atof(argv[2]) : 0.0;
  const int    reverse = (argc > 3) ? Draw::Atoi(argv[3]) : 0;
  const int    order   = (argc > 4) ? Draw::Atoi(argv[4]) : 0;

  gp_Pnt center1(0, 10, 0);
  gp_Ax2 axis1 =
    reverse ? gp_Ax2(center1, gp::DY(), gp::DZ()) : gp_Ax2(center1, -gp::DY(), gp::DX());
  if (std::abs(angle) > gp::Resolution())
    axis1.Rotate(gp_Ax1(center1, gp::DZ()), angle * M_PI / 180.0);

  gce_MakeCirc makeCirc1(axis1, rad);
  if (!makeCirc1.IsDone())
    return 1;
  gp_Circ            circ1 = makeCirc1.Value();
  GC_MakeArcOfCircle makeArc1(circ1, 0, M_PI / 2, true);
  if (!makeArc1.IsDone())
    return 1;
  occ::handle<Geom_TrimmedCurve> arc1 = makeArc1.Value();

  BRepBuilderAPI_MakeEdge makeEdge1(arc1, arc1->StartPoint(), arc1->EndPoint());
  if (!makeEdge1.IsDone())
    return 1;
  TopoDS_Edge             edge1 = makeEdge1.Edge();
  BRepBuilderAPI_MakeWire makeWire1;
  makeWire1.Add(edge1);
  if (!makeWire1.IsDone())
    return 1;
  TopoDS_Wire wire1 = makeWire1.Wire();

  gp_Pnt center2(10, 0, 0);
  gp_Ax2 axis2(center2, -gp::DX(), gp::DZ());

  gce_MakeCirc makeCirc2(axis2, rad);
  if (!makeCirc2.IsDone())
    return 1;
  gp_Circ            circ2 = makeCirc2.Value();
  GC_MakeArcOfCircle makeArc2(circ2, 0, M_PI / 2, true);
  if (!makeArc2.IsDone())
    return 1;
  occ::handle<Geom_TrimmedCurve> arc2 = makeArc2.Value();

  BRepBuilderAPI_MakeEdge makeEdge2(arc2, arc2->StartPoint(), arc2->EndPoint());
  if (!makeEdge2.IsDone())
    return 1;
  TopoDS_Edge             edge2 = makeEdge2.Edge();
  BRepBuilderAPI_MakeWire makeWire2;
  makeWire2.Add(edge2);
  if (!makeWire2.IsDone())
    return 1;
  TopoDS_Wire wire2 = makeWire2.Wire();

  BRepOffsetAPI_ThruSections thruSect(false, true);
  if (order)
  {
    thruSect.AddWire(wire1);
    thruSect.AddWire(wire2);
  }
  else
  {
    thruSect.AddWire(wire2);
    thruSect.AddWire(wire1);
  }
  thruSect.Build();
  if (!thruSect.IsDone())
    return 1;
  TopoDS_Shape myShape = thruSect.Shape();

  DBRep::Set(argv[1], myShape);

  return 0;
}

void QABugs::Commands_12(Draw_Interpretor& theCommands)
{
  const char* group = "QABugs";

  theCommands.Add("OCC895", "OCC895 result [angle [reverse [order]]]", __FILE__, OCC895, group);

  return;
}
