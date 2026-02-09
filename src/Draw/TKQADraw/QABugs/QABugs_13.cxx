#include <QABugs.hpp>

#include <Draw.hpp>
#include <Draw_Interpretor.hpp>
#include <DBRep.hpp>
#include <AIS_InteractiveContext.hpp>
#include <AIS_Shape.hpp>
#include <TopoDS_Shape.hpp>

#include <gp_Ax2.hpp>
#include <gp_Circ.hpp>
#include <gp_Pln.hpp>
#include <BRep_Builder.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepCheck_Analyzer.hpp>
#include <BRepGProp.hpp>
#include <BRepOffsetAPI_MakePipeShell.hpp>
#include <GC_MakeArcOfCircle.hpp>
#include <Geom_Plane.hpp>
#include <Law_Linear.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <TopExp_Explorer.hpp>
#include <GProp_GProps.hpp>
#include <Standard_ErrorHandler.hpp>

#ifndef M_SQRT2
  #define M_SQRT2 1.41421356237309504880168872420969808
#endif

static int OCC332bug(Draw_Interpretor& di, int argc, const char** argv)
{

  char name[255];
  bool check = true;

  double wall_thickness = 10.0;
  double dia1           = 80.0;
  double dia2           = 100.0;
  double length         = 400.0;
  double major_radius   = 280.0;

  if (argc > 1)
    wall_thickness = Draw::Atof(argv[1]);
  if (argc > 2)
    dia1 = Draw::Atof(argv[2]);
  if (argc > 3)
    dia2 = Draw::Atof(argv[3]);
  if (argc > 4)
    major_radius = Draw::Atof(argv[4]);
  if (argc > 5)
    length = Draw::Atof(argv[5]);
  double bend_angle = length / major_radius;

  if ((bend_angle >= M_PI))
  {
    di << "The arguments are invalid.\n";
    return 1;
  }
  di << "creating the shape for a bent tube\n";

  double radius_l = dia1 / 2.0;
  double radius_r = dia2 / 2.0;

  gp_Ax2 origin(gp_Pnt(5000.0, -300.0, 1000.0), gp_Dir(0.0, -1.0, -1.0));

  TopoDS_Face  myFace;
  TopoDS_Shape myShape, gasSolid;
  TopoDS_Solid wallSolid;

  gp_Pln  circ1Plane(origin.Location(), origin.Direction());
  gp_Circ faceCircle(origin, radius_l);
  gp_Circ outFaceCircle(origin, radius_l + wall_thickness);

  gp_Pnt circ_center = origin.Location().Translated(major_radius * origin.XDirection());

  gp_Ax1 circ_axis(circ_center, origin.YDirection());
  gp_Pln circ2Plane = circ1Plane.Rotated(circ_axis, bend_angle);

  gp_Ax2  spineAxis(circ_center, origin.YDirection(), -origin.XDirection());
  gp_Circ circle(spineAxis, major_radius);

  TopoDS_Edge E1     = BRepBuilderAPI_MakeEdge(faceCircle);
  TopoDS_Wire Wire1_ = BRepBuilderAPI_MakeWire(E1).Wire();

  TopoDS_Edge Eout1       = BRepBuilderAPI_MakeEdge(outFaceCircle);
  TopoDS_Wire outerWire1_ = BRepBuilderAPI_MakeWire(Eout1).Wire();

  occ::handle<Geom_Curve> SpineCurve(GC_MakeArcOfCircle(circle, 0.0, bend_angle, true).Value());

  occ::handle<Law_Linear> myLaw1 = new Law_Linear();
  occ::handle<Law_Linear> myLaw2 = new Law_Linear();

  myLaw1->Set(SpineCurve->FirstParameter(), 1.0, SpineCurve->LastParameter(), radius_r / radius_l);
  myLaw2->Set(SpineCurve->FirstParameter(),
              1.0,
              SpineCurve->LastParameter(),
              (radius_r + wall_thickness) / (radius_l + wall_thickness));

  BRepBuilderAPI_MakeFace mkFace;

  BRepBuilderAPI_MakeEdge mkEdge;

  mkEdge.Init(SpineCurve);
  if (!mkEdge.IsDone())
    return 0;
  TopoDS_Wire SpineWire = BRepBuilderAPI_MakeWire(mkEdge.Edge()).Wire();

  Sprintf(name, "SpineWire");
  DBRep::Set(name, SpineWire);

  Sprintf(name, "Wire1_");
  DBRep::Set(name, Wire1_);

  Sprintf(name, "outerWire1_");
  DBRep::Set(name, outerWire1_);

  di.Eval("fit");

  BRepOffsetAPI_MakePipeShell mkPipe1(SpineWire);
  mkPipe1.SetTolerance(1.0e-8, 1.0e-8, 1.0e-6);

  mkPipe1.SetLaw(Wire1_, myLaw1, false, false);
  mkPipe1.Build();
  if (!mkPipe1.IsDone())
    return 0;

  BRepOffsetAPI_MakePipeShell mkPipe2(SpineWire);
  mkPipe2.SetTolerance(1.0e-8, 1.0e-8, 1.0e-6);

  mkPipe2.SetLaw(outerWire1_, myLaw2, false, false);
  mkPipe2.Build();
  if (!mkPipe2.IsDone())
    return 0;

  occ::handle<Geom_Plane> Plane1 = new Geom_Plane(circ1Plane);
  mkFace.Init(Plane1, false, Precision::Confusion());

  mkFace.Add(TopoDS::Wire(mkPipe2.FirstShape()));
  mkFace.Add(TopoDS::Wire(mkPipe1.FirstShape().Reversed()));
  if (!mkFace.IsDone())
    return 0;
  TopoDS_Face Face1 = mkFace.Face();

  occ::handle<Geom_Plane> Plane2 = new Geom_Plane(circ2Plane);
  mkFace.Init(Plane2, false, Precision::Confusion());

  mkFace.Add(TopoDS::Wire(mkPipe2.LastShape()));
  mkFace.Add(TopoDS::Wire(mkPipe1.LastShape().Reversed()));
  if (!mkFace.IsDone())
    return 0;
  TopoDS_Face Face2 = mkFace.Face();

  TopoDS_Shell TubeShell;
  BRep_Builder B;
  B.MakeShell(TubeShell);
  TopExp_Explorer getFaces;
  TopoDS_Face     test_face;
  getFaces.Init(mkPipe1.Shape(), TopAbs_FACE);

  if (getFaces.More())
    B.Add(TubeShell, getFaces.Current().Reversed());

  mkPipe1.MakeSolid();
  gasSolid = mkPipe1.Shape();

  Sprintf(name, "gasSolid_");
  DBRep::Set(name, gasSolid);

  getFaces.Init(mkPipe2.Shape(), TopAbs_FACE);

  if (getFaces.More())
    B.Add(TubeShell, getFaces.Current());

  B.Add(TubeShell, Face1.Reversed());
  B.Add(TubeShell, Face2);
  TubeShell.Closed(BRep_Tool::IsClosed(TubeShell));

  B.MakeSolid(wallSolid);
  B.Add(wallSolid, TubeShell);

  Sprintf(name, "wallSolid_");
  DBRep::Set(name, wallSolid);

  GProp_GProps gprops;
  BRepGProp::VolumeProperties(wallSolid, gprops);
  di << "The wallSolid's volume is: " << gprops.Mass() << "\n";

  if (check)
  {
    if (!(BRepCheck_Analyzer(wallSolid).IsValid()))
      di << "The TopoDS_Solid was checked, and it was invalid!\n";
    else
      di << "The TopoDS_Solid was checked, and it was valid.\n";
    if (!wallSolid.Closed())
      di << "The TopoDS_Solid is not closed!\n";
    else
      di << "The TopoDS_Solid is closed.\n";
    if (!wallSolid.Checked())
      di << "The TopoDS_Solid is not checked!\n";
    else
      di << "The TopoDS_Solid has been checked.\n";
    if (wallSolid.Infinite())
      di << "The TopoDS_Solid is infinite!\n";
    else
      di << "The TopoDS_Solid is finite.\n";
  }

  di << "The result is a ";

  switch (wallSolid.ShapeType())
  {
    case (TopAbs_COMPOUND):
      di << "TopAbs_COMPOUND\n";
      break;
    case (TopAbs_COMPSOLID):
      di << "TopAbs_COMPSOLID\n";
      break;
    case (TopAbs_SOLID):
      di << "TopAbs_SOLID\n";
      break;
    case (TopAbs_SHELL):
      di << "TopAbs_SHELL\n";
      break;
    case (TopAbs_FACE):
      di << "TopAbs_FACE\n";
      break;
    case (TopAbs_WIRE):
      di << "TopAbs_WIRE\n";
      break;
    case (TopAbs_EDGE):
      di << "TopAbs_EDGE\n";
      break;
    case (TopAbs_VERTEX):
      di << "TopAbs_VERTEX\n";
      break;
    case (TopAbs_SHAPE):
      di << "TopAbs_SHAPE\n";
  }
  di << "Can we turn it into a solid? ";
  try
  {
    OCC_CATCH_SIGNALS
    di << " yes\n";
  }
  catch (Standard_TypeMismatch const&)
  {
    di << " no\n";
  }

  getFaces.Clear();
  getFaces.Init(wallSolid, TopAbs_FACE);
  int i = 0;
  while (getFaces.More())
  {
    i++;
    Sprintf(name, "Face%d", i);
    di << "Face named " << name << "\n";
    DBRep::Set(name, getFaces.Current());
    getFaces.Next();
  }

  return 0;
}

#include <gce_MakePln.hpp>
#include <BRepOffsetAPI_Sewing.hpp>
#include <BRepAlgoAPI_Fuse.hpp>

static int OCC544(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc > 6)
  {
    di << "Usage : " << argv[0] << " [[[[[wT [[[[d1 [[[d2 [[R [length]]]]]\n";
    return 1;
  }

  char name[255];
  bool check = true;

  double radius_l = 20.0;
  double radius_r = 80.0;

  double bend_angle = M_PI / 2.0;

  double major_rad      = 280.0;
  double wall_thickness = 10.0;

  if (argc > 1)
    radius_l = Draw::Atof(argv[1]);
  if (argc > 2)
    radius_r = Draw::Atof(argv[2]);
  if (argc > 3)
    bend_angle = Draw::Atof(argv[3]);
  if (argc > 4)
    major_rad = Draw::Atof(argv[4]);
  if (argc > 5)
    wall_thickness = Draw::Atof(argv[5]);

  if ((bend_angle >= 2.0 * M_PI))
  {
    di << "The arguments are invalid.\n";
    return 1;
  }
  di << "creating the shape for a bent tube\n";

  gp_Ax2 origin(gp_Pnt(500.0, -300.0, 100.0), gp_Dir(0.0, -1.0 / M_SQRT2, -1.0 / M_SQRT2));

  TopoDS_Face  firstFace, lastFace;
  TopoDS_Solid wallSolid, myShape;

  gp_Pln  circ1Plane(origin.Location(), origin.Direction());
  gp_Circ faceCircle(origin, radius_l);
  gp_Circ outFaceCircle(origin, radius_l + wall_thickness);

  gp_Pnt circ_center = origin.Location().Translated(major_rad * origin.XDirection());

  gp_Pnt endPoint = origin.Location();
  endPoint.Translate(major_rad * (1.0 - cos(bend_angle)) * origin.XDirection());
  endPoint.Translate((-major_rad * sin(bend_angle)) * origin.Direction());

  gp_Pln circ2Plane =
    gce_MakePln(circ_center, endPoint, endPoint.Translated(major_rad * origin.YDirection()))
      .Value();

  gp_Ax2  spineAxis(circ_center, origin.YDirection(), origin.XDirection());
  gp_Circ circle(spineAxis, major_rad);

  gp_Ax2  circ2axis(endPoint, circ2Plane.Axis().Direction(), origin.YDirection());
  gp_Circ faceCircle2(circ2axis, radius_r);
  gp_Circ outFaceCircle2(circ2axis, radius_r + wall_thickness);

  TopoDS_Edge E1_1   = BRepBuilderAPI_MakeEdge(faceCircle, 0, M_PI);
  TopoDS_Edge E1_2   = BRepBuilderAPI_MakeEdge(faceCircle, M_PI, 2. * M_PI);
  TopoDS_Wire Wire1_ = BRepBuilderAPI_MakeWire(E1_1, E1_2);

  TopoDS_Edge Eout1_1     = BRepBuilderAPI_MakeEdge(outFaceCircle, 0, M_PI);
  TopoDS_Edge Eout1_2     = BRepBuilderAPI_MakeEdge(outFaceCircle, M_PI, 2. * M_PI);
  TopoDS_Wire outerWire1_ = BRepBuilderAPI_MakeWire(Eout1_1, Eout1_2);

  TopoDS_Edge E2_1   = BRepBuilderAPI_MakeEdge(faceCircle2, 0, M_PI);
  TopoDS_Edge E2_2   = BRepBuilderAPI_MakeEdge(faceCircle2, M_PI, 2. * M_PI);
  TopoDS_Wire Wire2_ = BRepBuilderAPI_MakeWire(E2_1, E2_2);

  TopoDS_Edge Eout2_1     = BRepBuilderAPI_MakeEdge(outFaceCircle2, 0, M_PI);
  TopoDS_Edge Eout2_2     = BRepBuilderAPI_MakeEdge(outFaceCircle2, M_PI, 2. * M_PI);
  TopoDS_Wire outerWire2_ = BRepBuilderAPI_MakeWire(Eout2_1, Eout2_2);

  BRepBuilderAPI_MakeFace mkFace;

  occ::handle<Geom_Curve> SpineCurve(
    GC_MakeArcOfCircle(circle, endPoint, origin.Location(), true).Value());
  occ::handle<Law_Linear> myLaw  = new Law_Linear();
  occ::handle<Law_Linear> myLaw2 = new Law_Linear();

  myLaw->Set(SpineCurve->FirstParameter(), radius_r / radius_l, SpineCurve->LastParameter(), 1.0);

  myLaw2->Set(SpineCurve->FirstParameter(),
              (radius_r + wall_thickness) / (radius_l + wall_thickness),
              SpineCurve->LastParameter(),
              1.0);

  di << "SpineCurve->FirstParameter() is " << SpineCurve->FirstParameter() << "\n";
  di << "SpineCurve->LastParameter() is " << SpineCurve->LastParameter() << "\n";
  di << "Law1 Value at FirstParameter() is " << myLaw->Value(SpineCurve->FirstParameter()) << "\n";
  di << "Law1 Value at LastParameter() is " << myLaw->Value(SpineCurve->LastParameter()) << "\n";
  di << "radius_r / radius_l is " << radius_r / radius_l << "\n";

  BRepBuilderAPI_MakeEdge mkEdge;

  mkEdge.Init(SpineCurve);
  if (!mkEdge.IsDone())
    return 1;
  TopoDS_Wire SpineWire = BRepBuilderAPI_MakeWire(mkEdge.Edge()).Wire();

  Sprintf(name, "SpineWire");
  DBRep::Set(name, SpineWire);

  Sprintf(name, "Wire1_");
  DBRep::Set(name, Wire1_);

  Sprintf(name, "outerWire1_");
  DBRep::Set(name, outerWire1_);

  Sprintf(name, "Wire2_");
  DBRep::Set(name, Wire2_);

  Sprintf(name, "outerWire2_");
  DBRep::Set(name, outerWire2_);

  di.Eval("fit");

  TopoDS_Vertex Location1, Location2;

  TopExp::Vertices(SpineWire, Location2, Location1);

  Sprintf(name, "Location1");
  DBRep::Set(name, Location1);

  Sprintf(name, "Location2");
  DBRep::Set(name, Location2);

  BRepOffsetAPI_MakePipeShell mkPipe1(SpineWire);
  mkPipe1.SetTolerance(1.0e-8, 1.0e-8, 1.0e-6);
  mkPipe1.SetTransitionMode(BRepBuilderAPI_Transformed);
  mkPipe1.SetMode(false);
  mkPipe1.SetLaw(Wire1_, myLaw, Location1, false, false);
  mkPipe1.Build();
  if (!mkPipe1.IsDone())
    return 1;

  BRepOffsetAPI_MakePipeShell mkPipe2(SpineWire);
  mkPipe2.SetTolerance(1.0e-8, 1.0e-8, 1.0e-6);
  mkPipe2.SetTransitionMode(BRepBuilderAPI_Transformed);
  mkPipe2.SetMode(false);
  mkPipe2.SetLaw(outerWire1_, myLaw2, Location1, false, false);
  mkPipe2.Build();
  if (!mkPipe2.IsDone())
    return 1;

  BRepOffsetAPI_Sewing SewIt(1.0e-4);

  TopExp_Explorer getFaces;
  TopoDS_Face     test_face;
  getFaces.Init(mkPipe1.Shape(), TopAbs_FACE);
  while (getFaces.More())
  {
    SewIt.Add(getFaces.Current().Reversed());
    getFaces.Next();
  }

  occ::handle<Geom_Plane> Plane1 = new Geom_Plane(circ1Plane);
  mkFace.Init(Plane1, false, Precision::Confusion());
  mkFace.Add(TopoDS::Wire(outerWire1_));
  mkFace.Add(TopoDS::Wire(Wire1_.Reversed()));
  if (!mkFace.IsDone())
    return 1;
  TopoDS_Face Face1 = mkFace.Face();

  occ::handle<Geom_Plane> Plane2 = new Geom_Plane(circ2Plane);
  mkFace.Init(Plane2, false, Precision::Confusion());
  mkFace.Add(TopoDS::Wire(outerWire2_));
  mkFace.Add(TopoDS::Wire(Wire2_.Reversed()));
  if (!mkFace.IsDone())
    return 1;
  TopoDS_Face Face2 = mkFace.Face();

  mkPipe1.MakeSolid();
  myShape = TopoDS::Solid(mkPipe1.Shape());

  getFaces.Clear();
  getFaces.Init(mkPipe2.Shape(), TopAbs_FACE);
  while (getFaces.More())
  {
    SewIt.Add(getFaces.Current());
    getFaces.Next();
  }

  SewIt.Add(Face1.Reversed());
  SewIt.Add(Face2);

  SewIt.Perform();

  di << "The result of the Sewing operation is a ";

  switch (SewIt.SewedShape().ShapeType())
  {
    case (TopAbs_COMPOUND):
      di << "TopAbs_COMPOUND\n";
      break;
    case (TopAbs_COMPSOLID):
      di << "TopAbs_COMPSOLID\n";
      break;
    case (TopAbs_SOLID):
      di << "TopAbs_SOLID\n";
      break;
    case (TopAbs_SHELL):
      di << "TopAbs_SHELL\n";
      break;
    case (TopAbs_FACE):
      di << "TopAbs_FACE\n";
      break;
    case (TopAbs_WIRE):
      di << "TopAbs_WIRE\n";
      break;
    case (TopAbs_EDGE):
      di << "TopAbs_EDGE\n";
      break;
    case (TopAbs_VERTEX):
      di << "TopAbs_VERTEX\n";
      break;
    case (TopAbs_SHAPE):
      di << "TopAbs_SHAPE\n";
  }

  BRep_Builder B;

  TopoDS_Shell TubeShell;
  di << "Can we turn it into a shell? ";
  try
  {
    OCC_CATCH_SIGNALS
    TubeShell = TopoDS::Shell(SewIt.SewedShape());
    B.MakeSolid(wallSolid);
    B.Add(wallSolid, TubeShell);
    di << " yes\n";
  }
  catch (Standard_TypeMismatch const&)
  {
    di << "Can't convert to shell...\n";
    TopExp_Explorer getSol;
    getSol.Init(SewIt.SewedShape(), TopAbs_SOLID);
    if (getSol.More())
    {
      di << "First solid found in compound\n";
      wallSolid = TopoDS::Solid(getSol.Current());
      TopoDS_Solid test_solid;
      while (getSol.More())
      {
        di << "Next solid found in compound\n";
        getSol.Next();
        test_solid = TopoDS::Solid(getSol.Current());

        di << "BRepAlgoAPI_Fuse fuser(test_solid, wallSolid)\n";
        BRepAlgoAPI_Fuse fuser(test_solid, wallSolid);
        TopExp_Explorer  aExpS(fuser.Shape(), TopAbs_SOLID);
        if (aExpS.More())
        {
          wallSolid = TopoDS::Solid(aExpS.Current());
        }
      }
    }
    else
    {

      TopExp_Explorer getShel;
      getShel.Init(SewIt.SewedShape(), TopAbs_SHELL);
      if (getShel.More())
      {
        di << "First shell found in compound\n";
        B.MakeSolid(wallSolid);
        di << "B.Add(wallSolid,TopoDS::Shell(getShel.Current()));\n";
        int i = 1;
        while (getShel.More())
        {
          di << "Next shell found in compound\n";
          di << "B.Add(wallSolid,TopoDS::Shell(getShel.Current()));\n";
          Sprintf(name, "shell%d", i++);
          DBRep::Set(name, getShel.Current());
          B.Add(wallSolid, TopoDS::Shell(getShel.Current()));
          getShel.Next();
        }
      }
    }
  }

  Sprintf(name, "result");
  DBRep::Set(name, wallSolid);

  GProp_GProps gprops;
  BRepGProp::VolumeProperties(wallSolid, gprops);
  di << "The wallSolid's volume is: " << gprops.Mass() << "\n";

  if (check)
  {
    if (!(BRepCheck_Analyzer(wallSolid).IsValid()))
      di << "The TopoDS_Solid was checked, and it was invalid!\n";
    else
      di << "The TopoDS_Solid was checked, and it was valid.\n";
    if (!wallSolid.Closed())
      di << "The TopoDS_Solid is not closed!\n";
    else
      di << "The TopoDS_Solid is closed.\n";
    if (!wallSolid.Checked())
      di << "The TopoDS_Solid is not checked!\n";
    else
      di << "The TopoDS_Solid has been checked.\n";
    if (wallSolid.Infinite())
      di << "The TopoDS_Solid is infinite!\n";
    else
      di << "The TopoDS_Solid is finite.\n";
  }

  di << "The result is a ";

  switch (wallSolid.ShapeType())
  {
    case (TopAbs_COMPOUND):
      di << "TopAbs_COMPOUND\n";
      break;
    case (TopAbs_COMPSOLID):
      di << "TopAbs_COMPSOLID\n";
      break;
    case (TopAbs_SOLID):
      di << "TopAbs_SOLID\n";
      break;
    case (TopAbs_SHELL):
      di << "TopAbs_SHELL\n";
      break;
    case (TopAbs_FACE):
      di << "TopAbs_FACE\n";
      break;
    case (TopAbs_WIRE):
      di << "TopAbs_WIRE\n";
      break;
    case (TopAbs_EDGE):
      di << "TopAbs_EDGE\n";
      break;
    case (TopAbs_VERTEX):
      di << "TopAbs_VERTEX\n";
      break;
    case (TopAbs_SHAPE):
      di << "TopAbs_SHAPE\n";
  }

  return 0;
}

#include <BRepPrimAPI_MakeBox.hpp>
#include <BRepBndLib.hpp>
#include <NCollection_Array1.hpp>
#include <BRepBuilderAPI_Copy.hpp>
#include <BRepAlgoAPI_Cut.hpp>
#include <BRepAlgoAPI_Common.hpp>
#include <Precision.hpp>

static int OCC817(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc != 3)
  {
    di << "Usage : " << argv[0] << " result mesh_delta\n";
    return 1;
  }

  constexpr double delt      = 5.0 * Precision::Confusion();
  double           mesh_delt = Draw::Atof(argv[2]);
  if (mesh_delt <= 0.0)
  {
    di << "Error: mesh_delta must be positive value\n";
    return -1;
  }

  gp_Pnt       P(0, 0, 0);
  TopoDS_Solid fullSolid = BRepPrimAPI_MakeBox(P, 30.0, 30.0, 30.0).Solid();

  P.SetX(10);
  P.SetY(10);
  P.SetZ(10);
  TopoDS_Solid internalSolid = BRepPrimAPI_MakeBox(P, 10.0, 10.0, 10.0).Solid();

  di << "BRepAlgoAPI_Cut cut( fullSolid, internalSolid )\n";
  BRepAlgoAPI_Cut cut(fullSolid, internalSolid);
  if (!cut.IsDone())
  {
    di << "Error: Could not cut volumes\n";
    return -1;
  }
  const TopoDS_Shape& cut_shape = cut.Shape();

  int             found_solid = 0;
  TopoDS_Solid    cutSolid;
  TopExp_Explorer Ex;
  for (Ex.Init(cut_shape, TopAbs_SOLID); Ex.More(); Ex.Next())
  {
    TopoDS_Solid sol = TopoDS::Solid(Ex.Current());
    if (!sol.IsNull())
    {
      cutSolid = sol;
      found_solid++;
    }
  }
  if (found_solid != 1)
  {
    di << "Error: Cut operation produced " << found_solid << " solids\n";
    return -1;
  }
  DBRep::Set(argv[1], cutSolid);

  GProp_GProps volumeVProps;
  BRepGProp::VolumeProperties(cutSolid, volumeVProps);
  di << "Info: Original volume  = " << volumeVProps.Mass() << "\n";

  Bnd_Box bndBox;
  BRepBndLib::Add(cutSolid, bndBox);
  double Xmin, Ymin, Zmin, Xmax, Ymax, Zmax;
  bndBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);
  Xmin -= delt;
  Ymin -= delt;
  Zmin -= delt;
  Xmax += delt;
  Ymax += delt;
  Zmax += delt;
  di << "Info: Bounds\n  (" << Xmin << "," << Ymin << "," << Zmin << ")\n  (" << Xmax << "," << Ymax
     << "," << Zmax << ")\n";

  int NumXsubvolumes = (int)((Xmax - Xmin) / mesh_delt);
  if (NumXsubvolumes <= 0)
    NumXsubvolumes = 1;
  int NumYsubvolumes = (int)((Ymax - Ymin) / mesh_delt);
  if (NumYsubvolumes <= 0)
    NumYsubvolumes = 1;
  int NumZsubvolumes = (int)((Zmax - Zmin) / mesh_delt);
  if (NumZsubvolumes <= 0)
    NumZsubvolumes = 1;
  const double StepX         = (Xmax - Xmin) / NumXsubvolumes;
  const double StepY         = (Ymax - Ymin) / NumYsubvolumes;
  const double StepZ         = (Zmax - Zmin) / NumZsubvolumes;
  const int    NumSubvolumes = NumXsubvolumes * NumYsubvolumes * NumZsubvolumes;
  di << "Info: NumSubvolumesX = " << NumXsubvolumes << "\n";
  di << "Info: NumSubvolumesY = " << NumYsubvolumes << "\n";
  di << "Info: NumSubvolumesZ = " << NumZsubvolumes << "\n";
  di << "Info: NumSubvolumes = " << NumSubvolumes << "\n";

  NCollection_Array1<TopoDS_Shape> SubvolumeSolid(0, NumSubvolumes - 1);
  NCollection_Array1<double>       SubvolumeVol(0, NumSubvolumes - 1);
  double                           accumulatedVolume = 0.0;
  int                              i, j, k, l = 0;
  double                           x = Xmin;
  for (i = 0; i < NumXsubvolumes; i++)
  {
    double y = Ymin;
    for (j = 0; j < NumYsubvolumes; j++)
    {
      double z = Zmin;
      for (k = 0; k < NumZsubvolumes; k++)
      {
        P.SetX(x);
        P.SetY(y);
        P.SetZ(z);
        TopoDS_Shape aSubvolume = BRepPrimAPI_MakeBox(P, StepX, StepY, StepZ).Solid();
        di << "Info: box b_" << l << " " << P.X() << " " << P.Y() << " " << P.Z() << " " << StepX
           << " " << StepY << " " << StepZ << "\n";
        if (aSubvolume.IsNull())
        {
          di << "Error: could not construct subvolume " << l << "\n";
          return 1;
        }
        SubvolumeSolid.SetValue(l, aSubvolume);
        GProp_GProps subvolumeVProps;
        BRepGProp::VolumeProperties(SubvolumeSolid(l), subvolumeVProps);
        const double vol = subvolumeVProps.Mass();
        di << "Info: original subvolume " << l << " volume = " << vol << "\n";
        SubvolumeVol.SetValue(l, vol);
        accumulatedVolume += vol;
        l++;
        z += StepZ;
      }
      y += StepY;
    }
    x += StepX;
  }
  di << "Info: Accumulated mesh volume = " << accumulatedVolume << "\n";

  accumulatedVolume = 0.0;
  for (l = 0; l < NumSubvolumes; l++)
  {
    TopoDS_Shape copySolid = BRepBuilderAPI_Copy(cutSolid).Shape();

    di << "BRepAlgoAPI_Common common(copySolid/*cutSolid*/, SubvolumeSolid(l))\n";
    BRepAlgoAPI_Common common(copySolid, SubvolumeSolid(l));
    if (!common.IsDone())
    {
      di << "Error: could not construct a common solid " << l << "\n";
      return 1;
    }
    const TopoDS_Shape& aCommonShape = common.Shape();

    found_solid = 0;
    TopoDS_Shape commonShape;

    for (Ex.Init(aCommonShape, TopAbs_SOLID); Ex.More(); Ex.Next())
    {
      TopoDS_Solid sol = TopoDS::Solid(Ex.Current());
      if (!sol.IsNull())
      {
        commonShape = sol;
        found_solid++;
      }
    }
    if (found_solid != 1)
    {
      di << "Info: Common operation " << l << " produced " << found_solid << " solids\n";
    }
    else
    {
      SubvolumeSolid.SetValue(l, commonShape);
      GProp_GProps subvolumeVProps;
      BRepGProp::VolumeProperties(SubvolumeSolid(l), subvolumeVProps);
      const double vol = subvolumeVProps.Mass();
      const bool   err = (vol > SubvolumeVol(l)) || (vol <= 0.0);

      if (err)
        di << "ERROR: final subvolume " << l << " volume = " << vol << "\n";
      else
        di << "Info: final subvolume " << l << " volume = " << vol << "\n";
      accumulatedVolume += vol;
      if (err)
      {
        char astr[80];
        Sprintf(astr, "e_%d", l);
        DBRep::Set(astr, commonShape);
      }
    }
  }
  di << "Info: Accumulated meshed volume = " << accumulatedVolume << "\n";

  return 0;
}

void QABugs::Commands_13(Draw_Interpretor& theCommands)
{
  const char* group = "QABugs";

  theCommands.Add("OCC332",
                  "OCC332 [wall_thickness [dia1 [dia2 [length [major_radius]]]]]",
                  __FILE__,
                  OCC332bug,
                  group);

  theCommands.Add("OCC544",
                  "OCC544 [[[[[wT [[[[d1 [[[d2 [[R [length ]]]]]",
                  __FILE__,
                  OCC544,
                  group);

  theCommands.Add("OCC817", "OCC817 result mesh_delta ", __FILE__, OCC817, group);

  return;
}
