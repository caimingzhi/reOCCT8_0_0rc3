#include <QABugs.hpp>
#include <Draw.hpp>
#include <Draw_Interpretor.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS.hpp>
#include <DBRep.hpp>
#include <BRep_Tool.hpp>
#include <GeomInt_IntSS.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <ViewerTest.hpp>
#include <AIS_Shape.hpp>

#include <fstream>

static int BUC60623(Draw_Interpretor& di, int argc, const char** a)
{
  if (argc != 4)
  {
    di << "Usage : " << a[0] << " result Shape1 Shape2\n";
    return -1;
  }

  TopLoc_Location           L1;
  TopLoc_Location           L2;
  TopoDS_Face               F1   = TopoDS::Face(DBRep::Get(a[2], TopAbs_FACE));
  TopoDS_Face               F2   = TopoDS::Face(DBRep::Get(a[3], TopAbs_FACE));
  occ::handle<Geom_Surface> GSF1 = BRep_Tool::Surface(F1, L1);
  occ::handle<Geom_Surface> GSF2 = BRep_Tool::Surface(F2, L2);
  GeomInt_IntSS             Inter;
  Inter.Perform(GSF1, GSF2, BRep_Tool::Tolerance(F1));
  if (!Inter.IsDone())
  {
    di << "Intersection not done\n";
    return 1;
  }
  int nbsol = Inter.NbLines();
  if (!nbsol)
  {
    di << "The number of solutions is zero!" << "\n";
    return 0;
  }
  occ::handle<Geom_Curve> Sol = Inter.Line(1);
  if (!Sol.IsNull())
  {
    DBRep::Set(a[1], BRepBuilderAPI_MakeEdge(Sol));
    return 0;
  }
  else
    di << "The first solution is Null!" << "\n";

  di << "fini\n";
  return 0;
}

#include <BRepBuilderAPI_MakeVertex.hpp>
#include <TCollection_ExtendedString.hpp>
#include <AIS_InteractiveContext.hpp>
#include <PrsDim_LengthDimension.hpp>

static int BUC60632(Draw_Interpretor& di, int, const char** a)
{

  occ::handle<AIS_InteractiveContext> myAIScontext = ViewerTest::GetAISContext();
  if (myAIScontext.IsNull())
  {
    di << "use 'vinit' command before " << a[0] << "\n";
    return -1;
  }
  myAIScontext->EraseAll(false);

  TopoDS_Vertex V1 = BRepBuilderAPI_MakeVertex(gp_Pnt(0, 0, 0));
  TopoDS_Vertex V2 = BRepBuilderAPI_MakeVertex(gp_Pnt(10, 10, 0));

  occ::handle<AIS_Shape> Ve1 = new AIS_Shape(V1);
  occ::handle<AIS_Shape> Ve2 = new AIS_Shape(V2);

  myAIScontext->Display(Ve1, false);
  myAIScontext->Display(Ve2, false);

  occ::handle<Geom_Plane>    Plane1 = new Geom_Plane(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  TCollection_ExtendedString Ext1("Dim1");
  occ::handle<PrsDim_LengthDimension> Dim1 = new PrsDim_LengthDimension(V1, V2, Plane1->Pln());
  Dim1->SetCustomValue(Draw::Atof(a[2]));

  occ::handle<Prs3d_DimensionAspect> anAspect = new Prs3d_DimensionAspect();
  anAspect->MakeArrows3d(false);
  anAspect->MakeText3d(true);
  anAspect->MakeTextShaded(true);
  anAspect->TextAspect()->SetHeight(2.5);
  anAspect->ArrowAspect()->SetLength(1.0);
  Dim1->SetDimensionAspect(anAspect);

  myAIScontext->SetDisplayMode(Dim1, Draw::Atoi(a[1]), false);
  myAIScontext->Display(Dim1, true);
  return 0;
}

#include <BRepTools.hpp>

static int BUC60652(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc != 2)
  {
    di << "Usage : BUC60652 fase" << "\n";
    return 1;
  }
  TopoDS_Shape shape = DBRep::Get(argv[1]);
  TopoDS_Face  face  = TopoDS::Face(shape);
  TopoDS_Wire  ow    = BRepTools::OuterWire(face);
  DBRep::Set("w", ow);
  return 0;
}

#include <BRepPrimAPI_MakeBox.hpp>

#include <BRepAlgoAPI_Fuse.hpp>

#include <V3d_View.hpp>

#include <Bnd_BoundSortBox.hpp>
#include <BRepBndLib.hpp>
#include <TopExp_Explorer.hpp>

#include <gp_Circ.hpp>
#include <Geom_Circle.hpp>
#include <GeomAPI.hpp>
#include <Geom2d_CartesianPoint.hpp>
#include <Geom2dGcc_QualifiedCurve.hpp>
#include <Geom2dGcc_Circ2d2TanRad.hpp>
#include <Geom2d_Circle.hpp>
#include <ProjLib.hpp>

static int BUC60792(Draw_Interpretor& di, int, const char** argv)
{
  occ::handle<AIS_InteractiveContext> aContext = ViewerTest::GetAISContext();
  if (aContext.IsNull())
  {
    di << "use 'vinit' command before " << argv[0] << "\n";
    return -1;
  }

  gp_Pnt                    pt3d(0, 20, 150);
  gp_Ax2                    anAx2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::X), gp_Dir(gp_Dir::D::Z));
  gp_Circ                   circ(anAx2, 50.0);
  occ::handle<Geom_Circle>  gcir  = new Geom_Circle(circ);
  occ::handle<Geom_Plane>   pln   = new Geom_Plane(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::X)));
  occ::handle<Geom2d_Curve> gcir1 = GeomAPI::To2d(gcir, pln->Pln());
  TopoDS_Shape              sh1   = BRepBuilderAPI_MakeEdge(gcir1, pln).Shape();
  occ::handle<AIS_Shape>    ais1  = new AIS_Shape(sh1);
  aContext->SetColor(ais1, Quantity_NOC_INDIANRED, false);
  aContext->Display(ais1, false);
  DBRep::Set("sh0", sh1);
  gp_Pnt2d thepoint;

  thepoint                                    = ProjLib::Project(pln->Pln(), pt3d);
  occ::handle<Geom2d_CartesianPoint> ThePoint = new Geom2d_CartesianPoint(thepoint);
  Geom2dAdaptor_Curve                acur1(gcir1);
  Geom2dGcc_QualifiedCurve           qcur1(acur1, GccEnt_outside);
  Geom2dGcc_Circ2d2TanRad            cirtanrad(qcur1, ThePoint, 200.0, 0.0001);
  printf("\n No. of solutions = %d\n", cirtanrad.NbSolutions());
  occ::handle<Geom2d_Circle> gccc;
  if (cirtanrad.NbSolutions())
  {
    for (int i = 1; i <= cirtanrad.NbSolutions(); i++)
    {
      gp_Circ2d ccc   = cirtanrad.ThisSolution(i);
      gccc            = new Geom2d_Circle(ccc);
      TopoDS_Shape sh = BRepBuilderAPI_MakeEdge(gccc, pln).Shape();
      char         aStr[5];
      Sprintf(aStr, "sh%d", i);
      DBRep::Set(aStr, sh);
      occ::handle<AIS_Shape> ais = new AIS_Shape(sh);
      if (i == 1)
        aContext->SetColor(ais, Quantity_NOC_GREEN, false);
      if (i == 2)
        aContext->SetColor(ais, Quantity_NOC_HOTPINK, false);
      aContext->Display(ais, false);
      double   ParSol1, ParSol2, ParArg1, ParArg2;
      gp_Pnt2d PntSol1, PntSol2;
      cirtanrad.Tangency1(i, ParSol1, ParArg1, PntSol1);
      printf("%f\t%f\t\t%f\t%f\n", ParSol1, ParArg1, PntSol1.X(), PntSol1.Y());
      cirtanrad.Tangency2(i, ParSol2, ParArg2, PntSol2);
      printf("%f\t%f\t\t%f\t%f\n", ParSol2, ParArg2, PntSol2.X(), PntSol2.Y());
    }
  }
  aContext->UpdateCurrentViewer();
  return 0;
}

#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <Geom_BezierSurface.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <Geom_OffsetSurface.hpp>
#include <BRepFilletAPI_MakeFillet2d.hpp>
#include <GeomProjLib.hpp>
#include <Geom_TrimmedCurve.hpp>

static int BUC60811(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc == 4)
  {
    TopLoc_Location           L1;
    TopoDS_Edge               aEdge = TopoDS::Edge(DBRep::Get(argv[2], TopAbs_EDGE));
    TopoDS_Face               aFace = TopoDS::Face(DBRep::Get(argv[3], TopAbs_FACE));
    double                    f = 0.0, l = 0.0;
    occ::handle<Geom_Curve>   GC       = BRep_Tool::Curve(aEdge, f, l);
    occ::handle<Geom_Surface> GS       = BRep_Tool::Surface(aFace, L1);
    GC                                 = new Geom_TrimmedCurve(GC, f, l);
    occ::handle<Geom_Curve>  projCurve = GeomProjLib::Project(GC, GS);
    BRepBuilderAPI_MakeWire* myWire;
    myWire = new BRepBuilderAPI_MakeWire();
    myWire->Add((BRepBuilderAPI_MakeEdge(projCurve)).Edge());
    DBRep::Set(argv[1], myWire->Wire());
    return 0;
  }

  occ::handle<AIS_InteractiveContext> aContext = ViewerTest::GetAISContext();
  if (aContext.IsNull())
  {
    di << "use 'vinit' command before " << argv[0] << "\n";
    return -1;
  }

  TopoDS_Face                     FP;
  TopoDS_Shape                    FP1;
  TopoDS_Solid                    solid;
  occ::handle<AIS_Shape>          ais1;
  occ::handle<AIS_Shape>          ais2;
  occ::handle<Geom_BezierSurface> BZ1;
  NCollection_Array2<gp_Pnt>      array1(1, 3, 1, 3);
  array1.SetValue(1, 1, gp_Pnt(0, 100, 0));
  array1.SetValue(1, 2, gp_Pnt(200, 100, 0));
  array1.SetValue(1, 3, gp_Pnt(400, 100, 0));
  array1.SetValue(2, 1, gp_Pnt(0, 200, 100));
  array1.SetValue(2, 2, gp_Pnt(200, 200, 100));
  array1.SetValue(2, 3, gp_Pnt(400, 200, 100));
  array1.SetValue(3, 1, gp_Pnt(0, 300, 0));
  array1.SetValue(3, 2, gp_Pnt(200, 300, 0));
  array1.SetValue(3, 3, gp_Pnt(400, 300, 0));
  BZ1 = new Geom_BezierSurface(array1);
  BRepBuilderAPI_MakeFace bzf1(BZ1, Precision::Confusion());
  TopoDS_Face             F1 = bzf1.Face();
  ais1                       = new AIS_Shape(F1);
  DBRep::Set("F1", F1);
  aContext->SetMaterial(ais1, Graphic3d_NameOfMaterial_Aluminum, false);
  aContext->Display(ais1, false);
  BRep_Builder B;
  TopoDS_Shell shell;
  B.MakeShell(shell);
  B.Add(shell, bzf1);
  shell.Closed(BRep_Tool::IsClosed(shell));
  B.MakeSolid(solid);
  B.Add(solid, shell);
  BRepBuilderAPI_MakeWire  mkw;
  gp_Pnt                   p1 = gp_Pnt(150., 150.0, 260.);
  gp_Pnt                   p2 = gp_Pnt(350., 150., 260.);
  BRepBuilderAPI_MakeEdge* E1 = new BRepBuilderAPI_MakeEdge(p1, p2);
  mkw.Add(*E1);
  p1                          = gp_Pnt(350., 150., 260.);
  p2                          = gp_Pnt(350., 250., 260.);
  BRepBuilderAPI_MakeEdge* E2 = new BRepBuilderAPI_MakeEdge(p1, p2);
  mkw.Add(*E2);
  p1                          = gp_Pnt(350., 250., 260.);
  p2                          = gp_Pnt(300., 250.0, 260.);
  BRepBuilderAPI_MakeEdge* E3 = new BRepBuilderAPI_MakeEdge(p1, p2);
  mkw.Add(*E3);
  p1                          = gp_Pnt(300., 250.0, 260.);
  p2                          = gp_Pnt(200., 200.0, 260.);
  BRepBuilderAPI_MakeEdge* E4 = new BRepBuilderAPI_MakeEdge(p1, p2);
  mkw.Add(*E4);
  p1                          = gp_Pnt(200., 200.0, 260.);
  p2                          = gp_Pnt(150., 200.0, 260.);
  BRepBuilderAPI_MakeEdge* E5 = new BRepBuilderAPI_MakeEdge(p1, p2);
  mkw.Add(*E5);
  p1                          = gp_Pnt(150., 200.0, 260.);
  p2                          = gp_Pnt(150., 150.0, 260.);
  BRepBuilderAPI_MakeEdge* E6 = new BRepBuilderAPI_MakeEdge(p1, p2);
  mkw.Add(*E6);
  FP   = BRepBuilderAPI_MakeFace(mkw.Wire());
  ais2 = new AIS_Shape(FP);
  aContext->SetMaterial(ais2, Graphic3d_NameOfMaterial_Aluminum, false);
  aContext->Display(ais2, false);

  DBRep::Set("FP", FP);

  occ::handle<Geom_OffsetSurface> offsurf;
  offsurf = new Geom_OffsetSurface(BZ1, -100);
  BRepBuilderAPI_MakeFace bzf2(offsurf, Precision::Confusion());
  const TopoDS_Face&      F2    = bzf2.Face();
  occ::handle<AIS_Shape>  ais22 = new AIS_Shape(F2);
  aContext->Display(ais22, false);
  DBRep::Set("F2", F2);

  BRepFilletAPI_MakeFillet2d fillet(FP);
  TopExp_Explorer            Ex;
  Ex.Init(FP, TopAbs_VERTEX);
  TopoDS_Vertex v1 = TopoDS::Vertex(Ex.Current());
  fillet.AddFillet(v1, 20);
  di << "\nError is " << fillet.Status() << "\n";

  Ex.Next();
  TopoDS_Vertex V2 = TopoDS::Vertex(Ex.Current());
  fillet.AddFillet(V2, 20);
  di << "\nError is " << fillet.Status() << "\n";

  fillet.Build();
  FP1  = fillet.Shape();
  ais2 = new AIS_Shape(FP1);
  aContext->SetMaterial(ais2, Graphic3d_NameOfMaterial_Aluminum, false);
  aContext->Display(ais2, false);

  DBRep::Set("FP1", FP1);

  BRepBuilderAPI_MakeWire* myWire;
  myWire = new BRepBuilderAPI_MakeWire();
  for (Ex.Init(FP1, TopAbs_EDGE); Ex.More(); Ex.Next())
  {
    TopoDS_Edge             e1 = TopoDS::Edge(Ex.Current());
    double                  f = 0.0, l = 0.0;
    occ::handle<Geom_Curve> newBSplin = BRep_Tool::Curve(e1, f, l);
    newBSplin                         = new Geom_TrimmedCurve(newBSplin, f, l);
    occ::handle<Geom_Curve> projCurve = GeomProjLib::Project(newBSplin, offsurf);
    myWire->Add((BRepBuilderAPI_MakeEdge(projCurve)).Edge());
  }
  occ::handle<AIS_Shape> ais33 = new AIS_Shape(myWire->Wire());
  aContext->Display(ais33, true);

  DBRep::Set("Wire", myWire->Wire());

  return 0;
}

#include <GeomAPI_ExtremaCurveCurve.hpp>

static int BUC60825(Draw_Interpretor& di, int argc, const char** argv)

{
  if (argc < 3)
  {
    printf("Usage: %s edge1 edge2", argv[0]);
    return (-1);
  }

  TopoDS_Edge E1 = TopoDS::Edge(DBRep::Get(argv[1])), E2 = TopoDS::Edge(DBRep::Get(argv[2]));

  double fp, lp;

  occ::handle<Geom_Curve> C1 = BRep_Tool::Curve(E1, fp, lp), C2 = BRep_Tool::Curve(E2, fp, lp);

  GeomAPI_ExtremaCurveCurve aExt(C1, C2);

  di << "NB RESULTS : " << aExt.NbExtrema() << "\n";

  return 0;
}

#include <BRepBuilderAPI_MakePolygon.hpp>
#include <BRepOffsetAPI_ThruSections.hpp>

#include <GC_MakeTrimmedCone.hpp>

static int BUC60856(Draw_Interpretor& di, int, const char** argv)
{
  occ::handle<AIS_InteractiveContext> aContext = ViewerTest::GetAISContext();
  if (aContext.IsNull())
  {
    di << "use 'vinit' command before " << argv[0] << "\n";
    return -1;
  }

  double                                      R1 = 8, R2 = 16;
  gp_Pnt                                      P1(0, 0, 20), P2(0, 0, 45);
  occ::handle<Geom_RectangularTrimmedSurface> S = GC_MakeTrimmedCone(P1, P2, R1, R2).Value();
  TopoDS_Shape           myshape = BRepBuilderAPI_MakeFace(S, Precision::Confusion()).Shape();
  occ::handle<AIS_Shape> ais1    = new AIS_Shape(myshape);
  aContext->Display(ais1, false);
  aContext->SetColor(ais1, Quantity_NOC_BLUE1, false);

  occ::handle<Geom_RectangularTrimmedSurface> S2 = GC_MakeTrimmedCone(P1, P2, R1, 0).Value();
  TopoDS_Shape           myshape2 = BRepBuilderAPI_MakeFace(S2, Precision::Confusion()).Shape();
  occ::handle<AIS_Shape> ais2     = new AIS_Shape(myshape2);
  aContext->Display(ais2, false);
  aContext->SetColor(ais2, Quantity_NOC_RED, false);
  return 0;
}

static int coordload(Draw_Interpretor& theDi, int theArgsNb, const char** theArgVec)
{
  if (theArgsNb < 3)
  {
    return 1;
  }

  std::ifstream aFile(theArgVec[2], std::ios::in);
  if (!aFile)
  {
    theDi << "unable to open " << theArgVec[2] << " for input\n";
    return 2;
  }

  char aLine[80];
  memset(aLine, 0, 40);
  aFile.getline(aLine, 80);

  gp_Pnt aPnt(0.0, 0.0, 0.0);
  aLine[40] = '\0';
  aPnt.SetY(Draw::Atof(&aLine[20]));
  aLine[20] = '\0';
  aPnt.SetX(Draw::Atof(aLine));
  TopoDS_Vertex           aVert1 = BRepBuilderAPI_MakeVertex(aPnt);
  BRepBuilderAPI_MakeWire aMakeWire;
  for (;;)
  {
    memset(aLine, 0, 40);
    aFile.getline(aLine, 80);
    if (!aFile)
    {
      break;
    }

    aLine[40] = '\0';
    aPnt.SetY(Draw::Atof(&aLine[20]));
    aLine[20] = '\0';
    aPnt.SetX(Draw::Atof(aLine));
    TopoDS_Vertex aVert2 = BRepBuilderAPI_MakeVertex(aPnt);
    aMakeWire.Add(BRepBuilderAPI_MakeEdge(aVert1, aVert2));
    aVert1 = aVert2;
  }
  aFile.close();

  if (!aMakeWire.IsDone())
  {
    DBRep::Set(theArgVec[1], TopoDS_Face());
    return 0;
  }

  BRepBuilderAPI_MakeFace aMakeFace(aMakeWire.Wire());
  DBRep::Set(theArgVec[1], aMakeFace.IsDone() ? aMakeFace.Face() : TopoDS_Face());
  return 0;
}

static int BUC60876_(Draw_Interpretor& di, int argc, const char** argv)
{
  occ::handle<AIS_InteractiveContext> aContext = ViewerTest::GetAISContext();
  if (aContext.IsNull())
  {
    di << "use 'vinit' command before " << argv[0] << "\n";
    return -1;
  }
  if ((argc != 2) && (argc != 3))
  {
    di << "usage : " << argv[0] << " shape [mode==1]\n";
    return -1;
  }
  TopoDS_Shape                       aShape = DBRep::Get(argv[1]);
  occ::handle<AIS_InteractiveObject> anIO   = new AIS_Shape(aShape);
  anIO->SetHilightMode((argc == 3) ? Draw::Atoi(argv[2]) : 1);
  aContext->Display(anIO, true);
  return 0;
}

#include <BRepPrimAPI_MakeCylinder.hpp>
#include <BRepPrimAPI_MakeCone.hpp>

static int TestCMD(Draw_Interpretor& di, int argc, const char** argv)

{
  if (argc != 1)
  {
    di << "Usage : " << argv[0] << "\n";
    return 1;
  }

  double x11    = 36.085182;
  double y11    = 20.0;
  double z11    = 8.431413;
  double x12    = 88.04671;
  double y12    = 20.0;
  double z12    = 38.931416;
  double radius = 10.0;

  gp_Pnt base1(x11, y11, z11);
  gp_Dir vect1(x12 - x11, y12 - y11, z12 - z11);
  gp_Ax2 axis1(base1, vect1);
  double height1 =
    sqrt(((x12 - x11) * (x12 - x11)) + ((y12 - y11) * (y12 - y11)) + ((z12 - z11) * (z12 - z11)));
  BRepPrimAPI_MakeCylinder cylinder(axis1, radius, height1);

  TopoDS_Shape SCyl = cylinder.Shape();
  DBRep::Set("cyl", SCyl);

  double x21     = 70.7262;
  double y21     = 20.0;
  double z21     = 28.431412;
  double x22     = 105.36722;
  double y22     = 20.0;
  double z22     = 48.431416;
  double radius1 = 6.0;
  double radius2 = 3.0;

  gp_Pnt base2(x21, y21, z21);
  gp_Dir vect2(x22 - x21, y22 - y21, z22 - z21);
  gp_Ax2 axis2(base2, vect2);
  double height2 =
    sqrt(((x22 - x21) * (x22 - x21)) + ((y22 - y21) * (y22 - y21)) + ((z22 - z21) * (z22 - z21)));
  BRepPrimAPI_MakeCone cone(axis2, radius1, radius2, height2);

  TopoDS_Shape SCon = cone.Shape();
  DBRep::Set("con", SCon);

  di << "BRepAlgoAPI_Fuse SFuse(SCyl, SCon)\n";
  BRepAlgoAPI_Fuse SFuse(SCyl, SCon);
  if (!SFuse.IsDone())
  {
    di << "Error: Boolean fuse operation failed !\n";
  }
  else
  {
    const TopoDS_Shape& fuse = SFuse.Shape();
    DBRep::Set("fus", fuse);
  }
  return 0;
}

#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopExp.hpp>
#include <TopoDS_Iterator.hpp>

static int statface(Draw_Interpretor& di, int, const char** argv)

{
  TopoDS_Shape aShape = DBRep::Get(argv[1]);
  if (aShape.IsNull())
  {
    di << "Invalid input shape\n";
    return 1;
  }
  NCollection_DataMap<TCollection_AsciiString, int>           aMap;
  occ::handle<NCollection_HSequence<TCollection_AsciiString>> aSequence =
    new NCollection_HSequence<TCollection_AsciiString>;
  const char*     aString;
  int             l = 0;
  TopExp_Explorer expl;
  double          f3d, l3d;
  for (expl.Init(aShape, TopAbs_FACE); expl.More(); expl.Next())
  {

    TopoDS_Face               aFace    = TopoDS::Face(expl.Current());
    occ::handle<Geom_Surface> aSurface = BRep_Tool::Surface(aFace);
    aString                            = aSurface->DynamicType()->Name();

    if (aMap.IsBound(aString))
      aMap.ChangeFind(aString)++;
    else
    {
      aMap.Bind(aString, 1);
      aSequence->Append(aString);
    }
  }

  for (expl.Init(aShape, TopAbs_FACE); expl.More(); expl.Next())
  {
    TopoDS_Face     aFace = TopoDS::Face(expl.Current());
    TopoDS_Iterator anIt(aFace);
    TopoDS_Wire     aWire = TopoDS::Wire(anIt.Value());
    TopoDS_Iterator it(aWire);
    for (; it.More(); it.Next())
    {
      TopoDS_Edge               Edge     = TopoDS::Edge(it.Value());
      occ::handle<Geom2d_Curve> aCurve2d = BRep_Tool::CurveOnSurface(Edge, aFace, f3d, l3d);
      aString                            = aCurve2d->DynamicType()->Name();
      if (aMap.IsBound(aString))
        aMap.ChangeFind(aString)++;
      else
      {
        aMap.Bind(aString, 1);
        aSequence->Append(aString);
      }
    }
  }

  TopExp_Explorer exp;
  for (exp.Init(aShape, TopAbs_EDGE); exp.More(); exp.Next())
  {
    TopoDS_Edge             Edge     = TopoDS::Edge(exp.Current());
    occ::handle<Geom_Curve> aCurve3d = BRep_Tool::Curve(Edge, f3d, l3d);
    if (aCurve3d.IsNull())
    {
      l++;
    }
    else
    {
      aString = aCurve3d->DynamicType()->Name();
      if (aMap.IsBound(aString))
      {
        aMap.ChangeFind(aString)++;
      }
      else
      {
        aMap.Bind(aString, 1);
        aSequence->Append(aString);
      }
    }
  }

  di << "\n";

  for (int i = 1; i <= aSequence->Length(); i++)
  {
    di << aMap.Find(aSequence->Value(i)) << "   --   " << aSequence->Value(i).ToCString() << "\n";
  }

  di << "\n";
  di << "Degenerated edges :\n";
  di << l << "   --    Degenerated edges \n";

  return 0;
}

#include <BRepBuilderAPI_Transform.hpp>

static int BUC60841(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc != 1)
  {
    di << "Usage : " << argv[0] << "\n";
    return 1;
  }

  gp_Ax2                   Ax2 = gp_Ax2(gp_Pnt(0, 621, 78), gp_Dir(gp_Dir::D::Y));
  BRepPrimAPI_MakeCylinder cyl(Ax2, 260, 150);

  TopoDS_Shape sh1 = cyl.Shape();
  DBRep::Set("sh1", sh1);
  gp_Trsf trsf1, trsf2;
  trsf1.SetTranslation(gp_Pnt(0.000000, 700.000000, -170.000000),
                       gp_Pnt(0.000000, 700.000000, -95.000000));
  trsf2.SetRotation(
    gp_Ax1(gp_Pnt(0.000000, 700.000000, -170.000000), gp_Dir(0.000000, 0.000000, 1.000000)),
    0.436111);
  BRepBuilderAPI_Transform trans1(sh1, trsf1);
  TopoDS_Shape             sh2 = trans1.Shape();
  DBRep::Set("sh2", sh2);

  di << "BRepAlgoAPI_Fuse fuse1(sh1, sh2)\n";
  BRepAlgoAPI_Fuse fuse1(sh1, sh2);
  TopoDS_Shape     fsh1 = fuse1.Shape();
  DBRep::Set("fsh1", fsh1);

  BRepBuilderAPI_Transform trans2(fsh1, trsf2);
  TopoDS_Shape             sh3 = trans2.Shape();
  DBRep::Set("sh3", sh3);

  di << "BRepAlgoAPI_Fuse fuse2(fsh1,sh3)\n";
  BRepAlgoAPI_Fuse    fuse2(fsh1, sh3);
  const TopoDS_Shape& fsh2 = fuse2.Shape();
  DBRep::Set("fsh2", fsh2);

  occ::handle<AIS_Shape> aisp1 = new AIS_Shape(fsh2);
  return 0;
}

#include <ShapeBuild_Edge.hpp>

static int BUC60874(Draw_Interpretor&, int, const char** argv)
{
  TopoDS_Edge e = TopoDS::Edge(DBRep::Get(argv[1], TopAbs_EDGE));
  ShapeBuild_Edge().BuildCurve3d(e);
  DBRep::Set("ED", e);
  return 0;
}

#include <TDF_Label.hpp>
#include <TDataStd_TreeNode.hpp>

#include <DDocStd.hpp>

#include <DDF.hpp>

#include <TDocStd_Modified.hpp>
#include <TDocStd_Application.hpp>
#include <TDF_Delta.hpp>
#include <TDataXtd_Constraint.hpp>
#include <TPrsStd_AISPresentation.hpp>
#include <TPrsStd_AISViewer.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_Naming.hpp>
#include <TNaming_NamedShape.hpp>

static int BUC60831_1(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc != 2)
  {
    di << "Usage : " << argv[0] << " D\n";
    di << -1;
    return 0;
  }

  occ::handle<TDF_Data> DF;
  if (!DDF::GetDF(argv[1], DF))
  {
    di << -2;
    return 0;
  }

  TDF_Label L;
  DDF::FindLabel(DF, "0:1", L, false);
  occ::handle<TDocStd_Modified> MDF;
  if (!L.Root().FindAttribute(TDocStd_Modified::GetID(), MDF))
  {
    MDF = new TDocStd_Modified();
    L.Root().AddAttribute(MDF);
  }

  di << !MDF->IsEmpty();
  return 0;
}

static int BUC60831_2(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc != 3)
  {
    di << "Usage : " << argv[0] << " D Label\n";
    di << 1;
    return 0;
  }

  occ::handle<TDF_Data> DF;
  if (!DDF::GetDF(argv[1], DF))
  {
    di << 2;
    return 0;
  }

  TDF_Label L;
  DDF::FindLabel(DF, argv[2], L, false);

  TDocStd_Modified::Add(L);

  di << 0;
  return 0;
}

static int BUC60836(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc != 2)
  {
    di << "Usage : " << argv[0] << " D\n";
    di << 1;
    return 0;
  }

  occ::handle<TDF_Data> aDF;
  if (!DDF::GetDF(argv[1], aDF))
  {
    di << 2;
    return 0;
  }

  occ::handle<TDocStd_Document> aDocument;
  if (!DDocStd::GetDocument(argv[1], aDocument))
  {
    di << 3;
    return 0;
  }

  TDF_Label                      L;
  occ::handle<TDataStd_TreeNode> TN;

  aDocument->NewCommand();
  DDF::AddLabel(aDF, "0:2", L);
  TN = TDataStd_TreeNode::Set(L);

  aDocument->NewCommand();
  DDF::AddLabel(aDF, "0:3", L);
  TN = TDataStd_TreeNode::Set(L);

  aDocument->NewCommand();
  DDF::AddLabel(aDF, "0:4", L);
  TN = TDataStd_TreeNode::Set(L);
  aDocument->NewCommand();

  NCollection_List<occ::handle<TDF_Delta>> Us, Rs;
  Us = aDocument->GetUndos();
  Rs = aDocument->GetUndos();

  int  i;
  char Names[10][5] = {"n1", "n2", "n3", "n4", "n5", "n6", "n7", "n8", "n9", "n10"};

  NCollection_List<occ::handle<TDF_Delta>>::Iterator IDL;
  for (IDL.Initialize(Us), i = 1; IDL.More(); IDL.Next(), i++)
  {
    occ::handle<TDF_Delta>     D = IDL.Value();
    TCollection_ExtendedString S(Names[i - 1]);
    D->SetName(S);
  }

  aDocument->Undo();
  aDocument->Undo();

  Us = aDocument->GetUndos();
  Rs = aDocument->GetRedos();

  for (IDL.Initialize(Us), i = 1; IDL.More(); IDL.Next(), i++)
  {
    occ::handle<TDF_Delta> D = IDL.Value();
  }

  TCollection_ExtendedString n2name("n2");
  for (IDL.Initialize(Rs), i = 1; IDL.More(); IDL.Next(), i++)
  {
    occ::handle<TDF_Delta> D = IDL.Value();
    if (i == 1 && !D->Name().IsEqual(n2name))
    {
      di << 4;
      return 0;
    }
  }

  di << 0;
  return 0;
}

static int BUC60847(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc != 3)
  {
    di << "Usage : " << argv[0] << " D Shape\n";
    di << 1;
    return 0;
  }

  occ::handle<TDF_Data> aDF;
  if (!DDF::GetDF(argv[1], aDF))
  {
    di << 2;
    return 0;
  }

  TopoDS_Shape s = DBRep::Get(argv[2]);
  if (s.IsNull())
  {
    di << "shape not found\n";
    di << 3;
    return 0;
  }
  TDF_Label L;
  DDF::AddLabel(aDF, "0:2", L);
  TNaming_Builder SI(L);
  SI.Generated(s);

  occ::handle<TNaming_NamedShape> NS = new TNaming_NamedShape;

  TNaming_Naming aNN;
  NS = TNaming_Naming::Name(L, s, s);

  if (NS->IsEmpty())
  {
    di << 4;
    return 0;
  }
  di << 0;
  return 0;
}

static int BUC60862(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc != 3)
  {
    di << "Usage : " << argv[0] << " D Shape\n";
    di << 1;
    return 0;
  }

  occ::handle<TDF_Data> aDF;
  if (!DDF::GetDF(argv[1], aDF))
  {
    di << 2;
    return 0;
  }

  TopoDS_Shape s = DBRep::Get(argv[2]);
  if (s.IsNull())
  {
    di << "shape not found\n";
    di << 3;
    return 0;
  }
  TDF_Label L;
  DDF::AddLabel(aDF, "0:2", L);
  TNaming_Builder SI(L);
  SI.Generated(s);

  occ::handle<TNaming_NamedShape> NS = new TNaming_NamedShape;

  TNaming_Naming aNN;
  NS = TNaming_Naming::Name(L, s, s);
  if (NS->IsEmpty())
  {
    di << 4;
    return 0;
  }
  di << 0;
  return 0;
}

static int BUC60867(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc == 2)
  {
    TCollection_ExtendedString       path(argv[1]);
    occ::handle<TDocStd_Application> A = DDocStd::GetApplication();
    occ::handle<TDocStd_Document>    D;
    int                              insession = A->IsInSession(path);
    if (insession > 0)
    {
      di << "document " << insession << "  is already in session\n";
      di << 2;
      return 0;
    }
    PCDM_ReaderStatus Result = A->Open(path, D);
    if (Result == PCDM_RS_OK)
    {
      di << 0;
      return 0;
    }
  }
  di << 3;
  return 0;
}

static int BUC60910(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc != 2)
  {
    di << "Usage : " << argv[0] << " D\n";
    di << 1;
    return 0;
  }

  occ::handle<TDF_Data> aDF;
  if (!DDF::GetDF(argv[1], aDF))
  {
    di << 2;
    return 0;
  }

  TDF_Label L;
  DDF::AddLabel(aDF, "0:2", L);

  occ::handle<TPrsStd_AISPresentation> AISP =
    TPrsStd_AISPresentation::Set(L, TDataXtd_Constraint::GetID());

  if (AISP->HasOwnMode())
  {
    di << 3;
    return 0;
  }
  AISP->SetMode(3);
  int Mode = AISP->Mode();
  if (Mode != 3)
  {
    di << 4;
    return 0;
  }
  if (!AISP->HasOwnMode())
  {
    di << 5;
    return 0;
  }
  AISP->UnsetMode();
  if (AISP->HasOwnMode())
  {
    di << 6;
    return 0;
  }
  di << 0;
  return 0;
}

static int BUC60932(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc != 2)
  {
    di << "Usage : " << argv[0] << " D\n";
    di << 1;
    return 0;
  }

  occ::handle<TDocStd_Document> aDocument;
  if (!DDocStd::GetDocument(argv[1], aDocument))
  {
    di << 2;
    return 0;
  }

  if (!aDocument->InitDeltaCompaction())
  {
    di << 3;
    return 0;
  }
  if (!aDocument->PerformDeltaCompaction())
  {
    di << 4;
    return 0;
  }

  di << 0;
  return 0;
}

static int AISWidth(Draw_Interpretor& di, int argc, const char** argv)
{

  if (argc >= 3)
  {
    occ::handle<TDocStd_Document> D;
    if (!DDocStd::GetDocument(argv[1], D))
    {
      di << (-1);
      return 0;
    }
    TDF_Label L;
    if (!DDF::FindLabel(D->GetData(), argv[2], L))
    {
      di << (-2);
      return 0;
    }

    occ::handle<TPrsStd_AISViewer> viewer;
    if (!TPrsStd_AISViewer::Find(L, viewer))
    {
      di << (-3);
      return 0;
    }

    occ::handle<TPrsStd_AISPresentation> prs;
    if (L.FindAttribute(TPrsStd_AISPresentation::GetID(), prs))
    {
      if (argc == 4)
      {
        prs->SetWidth(Draw::Atof(argv[3]));
        TPrsStd_AISViewer::Update(L);
      }
      else
      {
        if (prs->HasOwnWidth())
        {

          di << prs->Width();
        }
        else
        {
          di << "AISWidth: Warning : Width wasn't set\n";
          di << (-4);
        }
      }
      return 0;
    }
  }
  di << "AISWidth : Error" << "\n";
  di << (-5);
  return 0;
}

static int BUC60921(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb >= 4)
  {
    occ::handle<TDocStd_Document> D;
    if (!DDocStd::GetDocument(arg[1], D))
    {
      di << 1;
      return 0;
    }
    TDF_Label L;
    DDF::AddLabel(D->GetData(), arg[2], L);

    BRep_Builder B;
    TopoDS_Shape S;
    BRepTools::Read(S, arg[3], B);

    TNaming_Builder tnBuild(L);
    tnBuild.Generated(S);

    di << 0;
    return 0;
  }
  di << "BUC60921 Doc label brep_file: directly read brep file and put shape to the label" << "\n";
  di << 2;
  return 0;
}

#include <IGESControl_Reader.hpp>
#include <BRepPrimAPI_MakeHalfSpace.hpp>

static int BUC60951_(Draw_Interpretor& di, int argc, const char** a)
{
  if (argc != 2)
  {
    di << "Usage : " << a[0] << " file.igs\n";
    return 1;
  }

  occ::handle<AIS_InteractiveContext> myContext = ViewerTest::GetAISContext();

  if (myContext.IsNull())
  {
    di << "use 'vinit' command before " << a[0] << "\n";
    return -1;
  }

  IGESControl_Reader reader;
  reader.ReadFile(a[1]);
  reader.TransferRoots();
  TopoDS_Shape shape = reader.OneShape();
  printf("\n iges1 shape type = %d", shape.ShapeType());
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> list;
  TopExp::MapShapes(shape, TopAbs_FACE, list);
  printf("\n No. of faces = %d", list.Extent());

  TopoDS_Shell shell;
  BRep_Builder builder;
  builder.MakeShell(shell);
  for (int i = 1; i <= list.Extent(); i++)
  {
    TopoDS_Face face = TopoDS::Face(list.FindKey(i));
    builder.Add(shell, face);
  }
  shell.Closed(BRep_Tool::IsClosed(shell));

  BRepPrimAPI_MakeHalfSpace half(shell, gp_Pnt(0, 0, 20));
  const TopoDS_Solid&       sol = half.Solid();
  gp_Ax2                    anAx2(gp_Pnt(-800.0, 0.0, 0), gp_Dir(gp_Dir::D::NZ));
  BRepPrimAPI_MakeCylinder  cyl(anAx2, 50, 300);
  TopoDS_Shape              sh = cyl.Shape();

  di << "BRepAlgoAPI_Fuse fuse(sol, sh)\n";
  BRepAlgoAPI_Fuse fuse(sol, sh);
  sh = fuse.Shape();

  occ::handle<AIS_Shape> res = new AIS_Shape(sh);
  myContext->Display(res, true);
  return 0;
}

void QABugs::Commands_3(Draw_Interpretor& theCommands)
{
  const char* group = "QABugs";

  theCommands.Add("BUC60623", "BUC60623 result Shape1 Shape2", __FILE__, BUC60623, group);
  theCommands.Add("BUC60632", "BUC60632 mode length", __FILE__, BUC60632, group);
  theCommands.Add("BUC60652", "BUC60652 face", __FILE__, BUC60652, group);

  theCommands.Add("BUC60792", "BUC60792", __FILE__, BUC60792, group);
  theCommands.Add("BUC60811", "BUC60811", __FILE__, BUC60811, group);

  theCommands.Add("BUC60825", "BUC60825", __FILE__, BUC60825, group);

  theCommands.Add("BUC60856", "BUC60856", __FILE__, BUC60856, group);

  theCommands.Add("coordload", "load coord from file", __FILE__, coordload, group);

  theCommands.Add("BUC60876", "BUC60876 shape", __FILE__, BUC60876_, group);

  theCommands.Add("TestCMD", "TestCMD", __FILE__, TestCMD, group);

  theCommands.Add("statface", "statface face", __FILE__, statface, group);

  theCommands.Add("BUC60841", "BUC60841", __FILE__, BUC60841, group);

  theCommands.Add("BUC60874", "BUC60874", __FILE__, BUC60874, group);
  theCommands.Add("BUC60831_1", "BUC60831_1 D", __FILE__, BUC60831_1, group);
  theCommands.Add("BUC60831_2", "BUC60831_2 D Label", __FILE__, BUC60831_2, group);
  theCommands.Add("BUC60836", "BUC60836 D", __FILE__, BUC60836, group);
  theCommands.Add("BUC60847", "BUC60847 D Shape", __FILE__, BUC60847, group);
  theCommands.Add("BUC60862", "BUC60862 D Shape", __FILE__, BUC60862, group);
  theCommands.Add("BUC60867", "BUC60867", __FILE__, BUC60867, group);
  theCommands.Add("BUC60910", "BUC60910 D", __FILE__, BUC60910, group);
  theCommands.Add("BUC60932", "BUC60932 D", __FILE__, BUC60932, group);
  theCommands.Add("AISWidth", "AISWidth (DOC,entry,[width])", __FILE__, AISWidth, group);
  theCommands.Add("BUC60921", "BUC60921 Doc label brep_file", __FILE__, BUC60921, group);

  theCommands.Add("BUC60951", "BUC60951 file.igs", __FILE__, BUC60951_, group);
}
