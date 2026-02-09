#include <BRepOffset_MakeSimpleOffset.hpp>

#include <Adaptor3d_CurveOnSurface.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepLib.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <BRepLib_MakeFace.hpp>
#include <BRepTools_Quilt.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepOffset_SimpleOffset.hpp>
#include <BRepTools_Modifier.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <Geom2d_Line.hpp>
#include <GeomFill_Generator.hpp>
#include <Extrema_LocateExtPC.hpp>
#include <NCollection_List.hpp>
#include <ShapeAnalysis_FreeBounds.hpp>
#include <ShapeFix_Edge.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

BRepOffset_MakeSimpleOffset::BRepOffset_MakeSimpleOffset()
    : myOffsetValue(0.),
      myTolerance(Precision::Confusion()),
      myIsBuildSolid(false),
      myMaxAngle(0.0),
      myError(BRepOffsetSimple_OK),
      myIsDone(false)
{
  myReShape = new ShapeBuild_ReShape();
}

BRepOffset_MakeSimpleOffset::BRepOffset_MakeSimpleOffset(const TopoDS_Shape& theInputShape,
                                                         const double        theOffsetValue)
    : myInputShape(theInputShape),
      myOffsetValue(theOffsetValue),
      myTolerance(Precision::Confusion()),
      myIsBuildSolid(false),
      myMaxAngle(0.0),
      myError(BRepOffsetSimple_OK),
      myIsDone(false)
{
  myReShape = new ShapeBuild_ReShape();
}

void BRepOffset_MakeSimpleOffset::Initialize(const TopoDS_Shape& theInputShape,
                                             const double        theOffsetValue)
{
  myInputShape  = theInputShape;
  myOffsetValue = theOffsetValue;
  Clear();
}

TCollection_AsciiString BRepOffset_MakeSimpleOffset::GetErrorMessage() const
{
  TCollection_AsciiString anError = "";

  if (myError == BRepOffsetSimple_NullInputShape)
  {
    anError = "Null input shape";
    return anError;
  }
  else if (myError == BRepOffsetSimple_ErrorOffsetComputation)
  {
    anError = "Error during offset construction";
    return anError;
  }
  else if (myError == BRepOffsetSimple_ErrorWallFaceComputation)
  {
    anError = "Error during building wall face";
    return anError;
  }
  else if (myError == BRepOffsetSimple_ErrorInvalidNbShells)
  {
    anError = "Result contains two or more shells";
    return anError;
  }
  else if (myError == BRepOffsetSimple_ErrorNonClosedShell)
  {
    anError = "Result shell is not closed";
    return anError;
  }

  return anError;
}

void BRepOffset_MakeSimpleOffset::Clear()
{
  myIsDone   = false;
  myError    = BRepOffsetSimple_OK;
  myMaxAngle = 0.0;
  myMapVE.Clear();
  myReShape->Clear();
}

double BRepOffset_MakeSimpleOffset::GetSafeOffset(const double theExpectedToler)
{
  if (myInputShape.IsNull())
    return 0.0;

  if (myMaxAngle == 0.0)
    ComputeMaxAngle();

  double aMaxTol = 0.0;
  aMaxTol        = BRep_Tool::MaxTolerance(myInputShape, TopAbs_VERTEX);

  const double anExpOffset = std::max((theExpectedToler - aMaxTol) / (2.0 * myMaxAngle), 0.0);
  return anExpOffset;
}

void BRepOffset_MakeSimpleOffset::Perform()
{

  Clear();

  if (myInputShape.IsNull())
  {
    myError = BRepOffsetSimple_NullInputShape;
    return;
  }

  if (myMaxAngle == 0.0)
    ComputeMaxAngle();

  myBuilder.Init(myInputShape);
  occ::handle<BRepOffset_SimpleOffset> aMapper =
    new BRepOffset_SimpleOffset(myInputShape, myOffsetValue, myTolerance);
  myBuilder.Perform(aMapper);

  if (!myBuilder.IsDone())
  {
    myError = BRepOffsetSimple_ErrorOffsetComputation;
    return;
  }

  myResShape = myBuilder.ModifiedShape(myInputShape);

  BRep_Builder    aBB;
  TopExp_Explorer anExpSE(myInputShape, TopAbs_EDGE);
  for (; anExpSE.More(); anExpSE.Next())
  {
    const TopoDS_Edge& aCurrEdge = TopoDS::Edge(anExpSE.Current());

    if (!BRep_Tool::Degenerated(aCurrEdge))
      continue;

    const TopoDS_Edge& anEdge = TopoDS::Edge(myBuilder.ModifiedShape(aCurrEdge));
    aBB.Degenerated(anEdge, true);
  }

  if (myIsBuildSolid && !BuildMissingWalls())
    return;

  myIsDone = true;
}

static void tgtfaces(const TopoDS_Edge& Ed,
                     const TopoDS_Face& F1,
                     const TopoDS_Face& F2,
                     const bool         couture,
                     double&            theResAngle)
{

  double                    aFirst, aLast;
  occ::handle<Geom2d_Curve> aCurve;
  aCurve = BRep_Tool::CurveOnSurface(Ed, F1, aFirst, aLast);
  if (aCurve.IsNull())
    return;
  aCurve = BRep_Tool::CurveOnSurface(Ed, F2, aFirst, aLast);
  if (aCurve.IsNull())
    return;

  double              u;
  TopoDS_Edge         E = Ed;
  BRepAdaptor_Surface aBAS1(F1, false);
  BRepAdaptor_Surface aBAS2(F2, false);

  occ::handle<BRepAdaptor_Surface> HS1 = new BRepAdaptor_Surface(aBAS1);
  occ::handle<BRepAdaptor_Surface> HS2;
  if (couture)
    HS2 = HS1;
  else
    HS2 = new BRepAdaptor_Surface(aBAS2);

  E.Orientation(TopAbs_FORWARD);
  BRepAdaptor_Curve2d C2d1(E, F1);
  if (couture)
    E.Orientation(TopAbs_REVERSED);
  BRepAdaptor_Curve2d C2d2(E, F2);

  bool   rev1 = (F1.Orientation() == TopAbs_REVERSED);
  bool   rev2 = (F2.Orientation() == TopAbs_REVERSED);
  double f, l, eps;
  BRep_Tool::Range(E, f, l);
  Extrema_LocateExtPC ext;

  eps = (l - f) / 100.0;
  f += eps;
  l -= eps;
  gp_Pnt2d p;
  gp_Pnt   pp1, pp2;
  gp_Vec   du1, dv1;
  gp_Vec   du2, dv2;
  gp_Vec   d1, d2;
  double   norm;

  const int NBPNT = 23;
  for (int i = 0; i <= NBPNT; i++)
  {

    u = f + (l - f) * i / NBPNT;

    C2d1.D0(u, p);
    HS1->D1(p.X(), p.Y(), pp1, du1, dv1);
    d1   = (du1.Crossed(dv1));
    norm = d1.Magnitude();
    if (norm > 1.e-12)
      d1 /= norm;
    else
      continue;
    if (rev1)
      d1.Reverse();

    C2d2.D0(u, p);
    HS2->D1(p.X(), p.Y(), pp2, du2, dv2);
    d2   = (du2.Crossed(dv2));
    norm = d2.Magnitude();
    if (norm > 1.e-12)
      d2 /= norm;
    else
      continue;
    if (rev2)
      d2.Reverse();

    double aCurrentAng = d1.Angle(d2);

    theResAngle = std::max(theResAngle, aCurrentAng);
  }
}

static void ComputeMaxAngleOnShape(const TopoDS_Shape& S, double& theResAngle)
{
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    M;
  TopExp::MapShapesAndAncestors(S, TopAbs_EDGE, TopAbs_FACE, M);
  NCollection_List<TopoDS_Shape>::Iterator It;
  TopExp_Explorer                          Ex;
  TopoDS_Face                              F1, F2;
  bool                                     found, couture;
  for (int i = 1; i <= M.Extent(); i++)
  {
    TopoDS_Edge E = TopoDS::Edge(M.FindKey(i));
    found         = false;
    couture       = false;
    F1.Nullify();
    for (It.Initialize(M.FindFromIndex(i)); It.More() && !found; It.Next())
    {
      if (F1.IsNull())
      {
        F1 = TopoDS::Face(It.Value());
      }
      else
      {
        if (!F1.IsSame(TopoDS::Face(It.Value())))
        {
          found = true;
          F2    = TopoDS::Face(It.Value());
        }
      }
    }
    if (!found && !F1.IsNull())
    {
      TopAbs_Orientation orE = E.Orientation();
      TopoDS_Edge        curE;
      for (Ex.Init(F1, TopAbs_EDGE); Ex.More() && !found; Ex.Next())
      {
        curE = TopoDS::Edge(Ex.Current());
        if (E.IsSame(curE) && orE != curE.Orientation())
        {
          found   = true;
          couture = true;
          F2      = F1;
        }
      }
    }
    if (found)
    {
      if (BRep_Tool::Continuity(E, F1, F2) <= GeomAbs_C0)
      {
        try
        {
          tgtfaces(E, F1, F2, couture, theResAngle);
        }
        catch (Standard_Failure const&)
        {
        }
      }
    }
  }
}

void BRepOffset_MakeSimpleOffset::ComputeMaxAngle()
{
  ComputeMaxAngleOnShape(myInputShape, myMaxAngle);
}

bool BRepOffset_MakeSimpleOffset::BuildMissingWalls()
{

  TopoDS_Compound aNewFaces;
  BRep_Builder    aBB;
  aBB.MakeCompound(aNewFaces);

  ShapeAnalysis_FreeBounds aFB(myInputShape);
  const TopoDS_Compound&   aFreeWires = aFB.GetClosedWires();

  TopExp_Explorer anExpCW(aFreeWires, TopAbs_WIRE);
  for (; anExpCW.More(); anExpCW.Next())
  {
    const TopoDS_Wire& aCurWire = TopoDS::Wire(anExpCW.Current());

    TopExp_Explorer anExpWE(aCurWire, TopAbs_EDGE);
    for (; anExpWE.More(); anExpWE.Next())
    {
      const TopoDS_Edge& aCurEdge = TopoDS::Edge(anExpWE.Current());

      TopoDS_Face aNewFace = BuildWallFace(aCurEdge);

      if (aNewFace.IsNull())
      {
        myError = BRepOffsetSimple_ErrorWallFaceComputation;
        return false;
      }

      aBB.Add(aNewFaces, aNewFace);
    }
  }

  ShapeFix_Edge aSFE;
  aSFE.SetContext(myReShape);
  TopExp_Explorer anExpCE(aNewFaces, TopAbs_EDGE);
  for (; anExpCE.More(); anExpCE.Next())
  {

    const TopoDS_Edge& aCurrEdge = TopoDS::Edge(anExpCE.Current());
    aSFE.FixSameParameter(aCurrEdge);
  }

  TopoDS_Compound aResCompound;
  aBB.MakeCompound(aResCompound);

  TopExp_Explorer anExpSF(myInputShape, TopAbs_FACE);
  for (; anExpSF.More(); anExpSF.Next())
    aBB.Add(aResCompound, anExpSF.Current());

  anExpSF.Init(myResShape, TopAbs_FACE);
  for (; anExpSF.More(); anExpSF.Next())
    aBB.Add(aResCompound, anExpSF.Current());

  TopExp_Explorer anExpCF(aNewFaces, TopAbs_FACE);
  for (; anExpCF.More(); anExpCF.Next())
  {
    const TopoDS_Face& aF = TopoDS::Face(anExpCF.Current());
    aBB.Add(aResCompound, aF);
  }

  aResCompound = TopoDS::Compound(myReShape->Apply(aResCompound));

  BRepTools_Quilt aQuilt;
  aQuilt.Add(aResCompound);
  TopoDS_Shape aShells = aQuilt.Shells();

  TopExp_Explorer anExpSSh(aShells, TopAbs_SHELL);
  TopoDS_Shell    aResShell;
  for (; anExpSSh.More(); anExpSSh.Next())
  {
    if (!aResShell.IsNull())
    {

      myError = BRepOffsetSimple_ErrorInvalidNbShells;
      return false;
    }
    aResShell = TopoDS::Shell(anExpSSh.Current());
  }

  if (!BRep_Tool::IsClosed(aResShell))
  {
    myError = BRepOffsetSimple_ErrorNonClosedShell;
    return false;
  }

  TopoDS_Solid aResSolid;
  aBB.MakeSolid(aResSolid);
  aBB.Add(aResSolid, aResShell);
  myResShape = aResSolid;

  return true;
}

TopoDS_Face BRepOffset_MakeSimpleOffset::BuildWallFace(const TopoDS_Edge& theOrigEdge)
{
  TopoDS_Face aResFace;

  TopoDS_Edge aNewEdge = TopoDS::Edge(myBuilder.ModifiedShape(theOrigEdge));
  aNewEdge.Orientation(TopAbs_REVERSED);

  TopoDS_Vertex aNewV1, aNewV2;
  TopExp::Vertices(aNewEdge, aNewV1, aNewV2);

  TopoDS_Edge anOrigCopy = theOrigEdge;
  anOrigCopy.Orientation(TopAbs_FORWARD);
  TopoDS_Vertex aV1, aV2;
  TopExp::Vertices(anOrigCopy, aV1, aV2);

  TopoDS_Vertex aForwardV1 = TopoDS::Vertex(aV1.Oriented(TopAbs_FORWARD));
  TopoDS_Vertex aForwardV2 = TopoDS::Vertex(aV2.Oriented(TopAbs_FORWARD));

  TopoDS_Edge aWall1;
  if (myMapVE.IsBound(aForwardV2))
  {

    aWall1 = myMapVE(aForwardV2);
  }
  else
  {

    BRepLib_MakeEdge aME1(TopoDS::Vertex(aV2.Oriented(TopAbs_FORWARD)),
                          TopoDS::Vertex(aNewV2.Oriented(TopAbs_REVERSED)));
    if (!aME1.IsDone())
      return aResFace;
    aWall1 = aME1.Edge();

    myMapVE.Bind(aForwardV2, aWall1);
  }

  TopoDS_Edge aWall2;
  if (myMapVE.IsBound(aForwardV1))
  {

    aWall2 = TopoDS::Edge(myMapVE(aForwardV1).Oriented(TopAbs_REVERSED));
  }
  else
  {

    BRepLib_MakeEdge aME2(TopoDS::Vertex(aV1.Oriented(TopAbs_FORWARD)),
                          TopoDS::Vertex(aNewV1.Oriented(TopAbs_REVERSED)));
    if (!aME2.IsDone())
      return aResFace;
    aWall2 = aME2.Edge();

    myMapVE.Bind(aForwardV1, aWall2);

    aWall2.Orientation(TopAbs_REVERSED);
  }

  BRep_Builder aBB;

  TopoDS_Wire aWire;
  aBB.MakeWire(aWire);
  aBB.Add(aWire, anOrigCopy);
  aBB.Add(aWire, aWall1);
  aBB.Add(aWire, aNewEdge);
  aBB.Add(aWire, aWall2);

  BRepLib::BuildCurves3d(aWire);

  TopoDS_Face aF;
  try
  {

    BRepLib_MakeFace aFM(aWire, true);
    if (aFM.IsDone())
      aF = aFM.Face();
  }
  catch (Standard_Failure const&)
  {
  }

  if (aF.IsNull())
  {

    bool                           ToReverse = false;
    double                         fpar, lpar, fparOE, lparOE;
    occ::handle<Geom_Curve>        EdgeCurve   = BRep_Tool::Curve(theOrigEdge, fpar, lpar);
    occ::handle<Geom_TrimmedCurve> TrEdgeCurve = new Geom_TrimmedCurve(EdgeCurve, fpar, lpar);
    occ::handle<Geom_Curve>        OffsetCurve = BRep_Tool::Curve(aNewEdge, fparOE, lparOE);
    occ::handle<Geom_TrimmedCurve> TrOffsetCurve =
      new Geom_TrimmedCurve(OffsetCurve, fparOE, lparOE);

    GeomFill_Generator ThrusecGenerator;
    ThrusecGenerator.AddCurve(TrEdgeCurve);
    ThrusecGenerator.AddCurve(TrOffsetCurve);
    ThrusecGenerator.Perform(Precision::PConfusion());
    occ::handle<Geom_Surface> theSurf = ThrusecGenerator.Surface();

    double Uf, Ul, Vf, Vl;
    theSurf->Bounds(Uf, Ul, Vf, Vl);
    TopLoc_Location          Loc;
    occ::handle<Geom2d_Line> EdgeLine2d, OELine2d, aLine2d, aLine2d2;
    EdgeLine2d = new Geom2d_Line(gp_Pnt2d(0., Vf), gp_Dir2d(gp_Dir2d::D::X));
    aBB.UpdateEdge(theOrigEdge, EdgeLine2d, theSurf, Loc, Precision::Confusion());
    OELine2d = new Geom2d_Line(gp_Pnt2d(0., Vl), gp_Dir2d(gp_Dir2d::D::X));
    aBB.UpdateEdge(aNewEdge, OELine2d, theSurf, Loc, Precision::Confusion());
    double UonV1 = (ToReverse) ? Ul : Uf;
    double UonV2 = (ToReverse) ? Uf : Ul;
    aLine2d      = new Geom2d_Line(gp_Pnt2d(UonV2, 0.), gp_Dir2d(gp_Dir2d::D::Y));
    aLine2d2     = new Geom2d_Line(gp_Pnt2d(UonV1, 0.), gp_Dir2d(gp_Dir2d::D::Y));
    if (aWall1.IsSame(aWall2))
    {
      aBB.UpdateEdge(aWall1, aLine2d, aLine2d2, theSurf, Loc, Precision::Confusion());
      occ::handle<Geom_Curve> BSplC34 = theSurf->UIso(Uf);
      aBB.UpdateEdge(aWall1, BSplC34, Precision::Confusion());
      aBB.Range(aWall1, Vf, Vl);
    }
    else
    {
      aBB.SameParameter(aWall1, false);
      aBB.SameRange(aWall1, false);
      aBB.SameParameter(aWall2, false);
      aBB.SameRange(aWall2, false);
      aBB.UpdateEdge(aWall1, aLine2d, theSurf, Loc, Precision::Confusion());
      aBB.Range(aWall1, theSurf, Loc, Vf, Vl);
      aBB.UpdateEdge(aWall2, aLine2d2, theSurf, Loc, Precision::Confusion());
      aBB.Range(aWall2, theSurf, Loc, Vf, Vl);
      occ::handle<Geom_Curve> BSplC3 = theSurf->UIso(UonV2);
      aBB.UpdateEdge(aWall1, BSplC3, Precision::Confusion());
      aBB.Range(aWall1, Vf, Vl, true);
      occ::handle<Geom_Curve> BSplC4 = theSurf->UIso(UonV1);
      aBB.UpdateEdge(aWall2, BSplC4, Precision::Confusion());
      aBB.Range(aWall2, Vf, Vl, true);
    }

    aF = BRepLib_MakeFace(theSurf, aWire);
  }

  return aF;
}

const TopoDS_Shape BRepOffset_MakeSimpleOffset::Generated(const TopoDS_Shape& theShape) const
{

  TopoDS_Shape aRes;
  aRes = myBuilder.ModifiedShape(theShape);

  if (aRes.IsNull())
    return aRes;

  aRes = myReShape->Apply(aRes);

  return aRes;
}

const TopoDS_Shape BRepOffset_MakeSimpleOffset::Modified(const TopoDS_Shape& theShape) const
{
  TopoDS_Shape aRes, anEmptyShape;

  int aModStatus = myReShape->Status(theShape, aRes);

  if (aModStatus == 0)
    return anEmptyShape;

  return aRes;
}
