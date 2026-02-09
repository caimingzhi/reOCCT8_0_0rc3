#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepLib.hpp>
#include <BRepMAT2d_Explorer.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <GCE2d_MakeSegment.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BoundedCurve.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Ellipse.hpp>
#include <Geom2d_Hyperbola.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_OffsetCurve.hpp>
#include <Geom2d_Parabola.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dConvert.hpp>
#include <GeomAbs_CurveType.hpp>
#include <NCollection_Sequence.hpp>
#include <Precision.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Wire.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

static TopoDS_Edge MakeEdge(const occ::handle<Geom2d_Curve>& theCurve,
                            const TopoDS_Face&               theFace,
                            const TopoDS_Vertex&             theVFirst,
                            const TopoDS_Vertex&             theVLast);

static GeomAbs_CurveType                GetCurveType(const occ::handle<Geom2d_Curve>& theC2d);
static occ::handle<Geom2d_TrimmedCurve> AdjustCurveEnd(
  const occ::handle<Geom2d_BoundedCurve>& theC2d,
  const gp_Pnt2d                          theP,
  const bool                              isFirst);

BRepMAT2d_Explorer::BRepMAT2d_Explorer()
{
  Clear();
}

BRepMAT2d_Explorer::BRepMAT2d_Explorer(const TopoDS_Face& aFace)
{
  Perform(aFace);
}

void BRepMAT2d_Explorer::Perform(const TopoDS_Face& aFace)
{
  Clear();
  myShape       = aFace;
  TopoDS_Face F = TopoDS::Face(aFace);
  F.Orientation(TopAbs_FORWARD);
  TopExp_Explorer Exp(F, TopAbs_WIRE);

  occ::handle<Geom_Surface> aSurf = BRep_Tool::Surface(F);
  TopoDS_Face               aNewF = BRepBuilderAPI_MakeFace(aSurf, Precision::Confusion());

  while (Exp.More())
  {
    Add(TopoDS::Wire(Exp.Current()), F, aNewF);
    Exp.Next();
  }

  BRepLib::BuildCurves3d(aNewF);

  myModifShapes.Add(aFace, aNewF);
}

void BRepMAT2d_Explorer::Add(const TopoDS_Wire& Spine,
                             const TopoDS_Face& aFace,
                             TopoDS_Face&       aNewFace)
{

  BRepTools_WireExplorer anExp(Spine, aFace);

  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> anOldNewE;
  if (!anExp.More())
    return;

  NewContour();
  myIsClosed(currentContour) = Spine.Closed();

  TopoDS_Edge                      aFirstEdge = anExp.Current();
  TopoDS_Edge                      aPrevEdge  = aFirstEdge;
  double                           UFirst, ULast, aD;
  occ::handle<Geom2d_Curve>        C2d;
  occ::handle<Geom2d_TrimmedCurve> CT2d;
  occ::handle<Geom2d_TrimmedCurve> aFirstCurve;
  gp_Pnt2d                         aPFirst;
  gp_Pnt2d                         aPLast;
  gp_Pnt2d                         aPCurFirst;

  double aTolConf = 1.e-8;

  bool isModif = false;

  anOldNewE.Add(aFirstEdge, aFirstEdge);
  C2d  = BRep_Tool::CurveOnSurface(aFirstEdge, aFace, UFirst, ULast);
  CT2d = new Geom2d_TrimmedCurve(C2d, UFirst, ULast);

  if (aFirstEdge.Orientation() == TopAbs_REVERSED)
    CT2d->Reverse();

  aPFirst = CT2d->Value(CT2d->FirstParameter());
  aPLast  = CT2d->Value(CT2d->LastParameter());

  Add(CT2d);
  aFirstCurve = CT2d;
  anExp.Next();

  for (; anExp.More(); anExp.Next())
  {
    const TopoDS_Edge& anEdge = anExp.Current();

    anOldNewE.Add(anEdge, anEdge);
    C2d  = BRep_Tool::CurveOnSurface(anEdge, aFace, UFirst, ULast);
    CT2d = new Geom2d_TrimmedCurve(C2d, UFirst, ULast);

    if (anEdge.Orientation() == TopAbs_REVERSED)
      CT2d->Reverse();

    aPCurFirst = CT2d->Value(CT2d->FirstParameter());

    aD = aPLast.Distance(aPCurFirst);
    if (aD > aTolConf)
    {

      isModif = true;

      int                              aNbC  = theCurves.Value(currentContour).Length();
      occ::handle<Geom2d_BoundedCurve> CPrev = occ::down_cast<Geom2d_BoundedCurve>(
        theCurves.ChangeValue(currentContour).ChangeValue(aNbC));

      GeomAbs_CurveType TCPrev = GetCurveType(CPrev);
      GeomAbs_CurveType TCCurr = GetCurveType(CT2d);

      if (TCCurr <= TCPrev)
      {
        CT2d = AdjustCurveEnd(CT2d, aPLast, true);

        TopoDS_Edge   aNewEdge;
        TopoDS_Vertex aVf = TopExp::FirstVertex(anEdge);
        TopoDS_Vertex aVl = TopExp::LastVertex(anEdge);

        if (anEdge.Orientation() == TopAbs_FORWARD)
          aNewEdge = MakeEdge(CT2d, aNewFace, aVf, aVl);
        else
          aNewEdge = MakeEdge(CT2d->Reversed(), aNewFace, aVf, aVl);

        aNewEdge.Orientation(anEdge.Orientation());

        anOldNewE.ChangeFromKey(anEdge) = aNewEdge;
      }
      else
      {
        gp_Pnt2d aP = CT2d->Value(CT2d->FirstParameter());
        CPrev       = AdjustCurveEnd(CPrev, aP, false);
        theCurves.ChangeValue(currentContour).ChangeValue(aNbC) = CPrev;

        TopoDS_Edge   aNewEdge;
        TopoDS_Vertex aVf = TopExp::FirstVertex(aPrevEdge);
        TopoDS_Vertex aVl = TopExp::LastVertex(aPrevEdge);

        if (aPrevEdge.Orientation() == TopAbs_FORWARD)
          aNewEdge = MakeEdge(CPrev, aNewFace, aVf, aVl);
        else
          aNewEdge = MakeEdge(CPrev->Reversed(), aNewFace, aVf, aVl);

        aNewEdge.Orientation(aPrevEdge.Orientation());

        anOldNewE.ChangeFromKey(aPrevEdge) = aNewEdge;
      }
    }

    aPLast = CT2d->Value(CT2d->LastParameter());
    Add(CT2d);
    aPrevEdge = anEdge;
  }

  if (myIsClosed(currentContour) && aPLast.Distance(aPFirst) > aTolConf)
  {
    isModif = true;

    int                              aNbC = theCurves.Value(currentContour).Length();
    occ::handle<Geom2d_BoundedCurve> CPrev =
      occ::down_cast<Geom2d_BoundedCurve>(theCurves.ChangeValue(currentContour).ChangeValue(aNbC));

    GeomAbs_CurveType TCPrev = GetCurveType(CPrev);
    GeomAbs_CurveType TCCurr = GetCurveType(aFirstCurve);

    if (TCCurr <= TCPrev)
    {
      aFirstCurve = AdjustCurveEnd(aFirstCurve, aPLast, true);
      theCurves.ChangeValue(currentContour).ChangeValue(1) = aFirstCurve;

      TopoDS_Edge   aNewEdge;
      TopoDS_Vertex aVf = TopExp::FirstVertex(aFirstEdge);
      TopoDS_Vertex aVl = TopExp::LastVertex(aFirstEdge);

      if (aFirstEdge.Orientation() == TopAbs_FORWARD)
        aNewEdge = MakeEdge(aFirstCurve, aNewFace, aVf, aVl);
      else
        aNewEdge = MakeEdge(aFirstCurve->Reversed(), aNewFace, aVf, aVl);

      aNewEdge.Orientation(aFirstEdge.Orientation());

      anOldNewE.ChangeFromKey(aFirstEdge) = aNewEdge;
    }
    else
    {
      gp_Pnt2d aP = aFirstCurve->Value(aFirstCurve->FirstParameter());
      CPrev       = AdjustCurveEnd(CPrev, aP, false);
      theCurves.ChangeValue(currentContour).ChangeValue(aNbC) = CPrev;

      TopoDS_Edge   aNewEdge;
      TopoDS_Vertex aVf = TopExp::FirstVertex(aPrevEdge);
      TopoDS_Vertex aVl = TopExp::LastVertex(aPrevEdge);

      if (aPrevEdge.Orientation() == TopAbs_FORWARD)
        aNewEdge = MakeEdge(CPrev, aNewFace, aVf, aVl);
      else
        aNewEdge = MakeEdge(CPrev->Reversed(), aNewFace, aVf, aVl);

      aNewEdge.Orientation(aPrevEdge.Orientation());

      anOldNewE.ChangeFromKey(aPrevEdge) = aNewEdge;
    }
  }

  TopoDS_Wire  aNewWire;
  BRep_Builder aBuilder;

  if (isModif)
  {
    int i;
    int aNbEdges = anOldNewE.Extent();

    aBuilder.MakeWire(aNewWire);

    for (i = 1; i <= aNbEdges; i++)
    {
      const TopoDS_Shape& aKey     = anOldNewE.FindKey(i);
      const TopoDS_Shape& aNewEdge = anOldNewE.FindFromIndex(i);

      aBuilder.Add(aNewWire, aNewEdge);
      myModifShapes.Add(aKey, aNewEdge);
    }

    if (myIsClosed(currentContour))
      aNewWire.Closed(true);

    myModifShapes.Add(Spine, aNewWire);
  }
  else
    aNewWire = Spine;

  aBuilder.Add(aNewFace, aNewWire);
}

void BRepMAT2d_Explorer::Clear()
{
  theCurves.Clear();
  currentContour = 0;

  myIsClosed.Clear();
  myModifShapes.Clear();
}

void BRepMAT2d_Explorer::NewContour()
{
  NCollection_Sequence<occ::handle<Geom2d_Curve>> Contour;
  theCurves.Append(Contour);

  myIsClosed.Append(false);

  currentContour++;
}

void BRepMAT2d_Explorer::Add(const occ::handle<Geom2d_Curve>& aCurve)
{
  theCurves.ChangeValue(currentContour).Append(aCurve);
}

int BRepMAT2d_Explorer::NumberOfContours() const
{
  return theCurves.Length();
}

int BRepMAT2d_Explorer::NumberOfCurves(const int IndexContour) const
{
  return theCurves.Value(IndexContour).Length();
}

void BRepMAT2d_Explorer::Init(const int IndexContour)
{
  currentContour = IndexContour;
  current        = 1;
}

bool BRepMAT2d_Explorer::More() const
{
  return (current <= NumberOfCurves(currentContour));
}

void BRepMAT2d_Explorer::Next()
{
  current++;
}

occ::handle<Geom2d_Curve> BRepMAT2d_Explorer::Value() const
{
  return theCurves.Value(currentContour).Value(current);
}

TopoDS_Shape BRepMAT2d_Explorer::Shape() const
{
  return myShape;
}

const NCollection_Sequence<occ::handle<Geom2d_Curve>>& BRepMAT2d_Explorer::Contour(
  const int IC) const
{
  return theCurves.Value(IC);
}

bool BRepMAT2d_Explorer::IsModified(const TopoDS_Shape& aShape) const
{
  if (myModifShapes.Contains(aShape))
  {
    const TopoDS_Shape& aNewShape = myModifShapes.FindFromKey(aShape);
    const bool          isSame    = aNewShape.IsSame(aShape);

    return !isSame;
  }

  return false;
}

TopoDS_Shape BRepMAT2d_Explorer::ModifiedShape(const TopoDS_Shape& aShape) const
{
  if (myModifShapes.Contains(aShape))
  {
    const TopoDS_Shape& aNewShape = myModifShapes.FindFromKey(aShape);

    return aNewShape;
  }

  return aShape;
}

const NCollection_Sequence<bool>& BRepMAT2d_Explorer::GetIsClosed() const
{
  return myIsClosed;
}

TopoDS_Edge MakeEdge(const occ::handle<Geom2d_Curve>& theCurve,
                     const TopoDS_Face&               theFace,
                     const TopoDS_Vertex&             theVFirst,
                     const TopoDS_Vertex&             theVLast)
{
  TopoDS_Edge      aNewEdge;
  BRep_Builder     aBuilder;
  constexpr double aTol  = Precision::Confusion();
  double           aFPar = theCurve->FirstParameter();
  double           aLPar = theCurve->LastParameter();

  aBuilder.MakeEdge(aNewEdge);
  aBuilder.UpdateEdge(aNewEdge, theCurve, theFace, aTol);
  aBuilder.Add(aNewEdge, theVFirst.Oriented(TopAbs_FORWARD));
  aBuilder.Add(aNewEdge, theVLast.Oriented(TopAbs_REVERSED));
  aBuilder.Range(aNewEdge, aFPar, aLPar);

  return aNewEdge;
}

GeomAbs_CurveType GetCurveType(const occ::handle<Geom2d_Curve>& theC2d)
{
  GeomAbs_CurveType          aTypeCurve = GeomAbs_OtherCurve;
  occ::handle<Standard_Type> TheType    = theC2d->DynamicType();
  if (TheType == STANDARD_TYPE(Geom2d_TrimmedCurve))
  {
    TheType = occ::down_cast<Geom2d_TrimmedCurve>(theC2d)->BasisCurve()->DynamicType();
  }

  if (TheType == STANDARD_TYPE(Geom2d_Circle))
  {
    aTypeCurve = GeomAbs_Circle;
  }
  else if (TheType == STANDARD_TYPE(Geom2d_Line))
  {
    aTypeCurve = GeomAbs_Line;
  }
  else if (TheType == STANDARD_TYPE(Geom2d_Ellipse))
  {
    aTypeCurve = GeomAbs_Ellipse;
  }
  else if (TheType == STANDARD_TYPE(Geom2d_Parabola))
  {
    aTypeCurve = GeomAbs_Parabola;
  }
  else if (TheType == STANDARD_TYPE(Geom2d_Hyperbola))
  {
    aTypeCurve = GeomAbs_Hyperbola;
  }
  else if (TheType == STANDARD_TYPE(Geom2d_BezierCurve))
  {
    aTypeCurve = GeomAbs_BezierCurve;
  }
  else if (TheType == STANDARD_TYPE(Geom2d_BSplineCurve))
  {
    aTypeCurve = GeomAbs_BSplineCurve;
  }
  else if (TheType == STANDARD_TYPE(Geom2d_OffsetCurve))
  {
    aTypeCurve = GeomAbs_OffsetCurve;
  }
  else
  {
    aTypeCurve = GeomAbs_OtherCurve;
  }
  return aTypeCurve;
}

occ::handle<Geom2d_TrimmedCurve> AdjustCurveEnd(const occ::handle<Geom2d_BoundedCurve>& theC2d,
                                                const gp_Pnt2d                          theP,
                                                const bool                              isFirst)
{
  GeomAbs_CurveType aType = GetCurveType(theC2d);
  if (aType == GeomAbs_Line)
  {

    if (isFirst)
    {
      gp_Pnt2d aP = theC2d->Value(theC2d->LastParameter());
      return GCE2d_MakeSegment(theP, aP);
    }
    else
    {
      gp_Pnt2d aP = theC2d->Value(theC2d->FirstParameter());
      return GCE2d_MakeSegment(aP, theP);
    }
  }
  else
  {

    occ::handle<Geom2d_BSplineCurve> BCurve =
      Geom2dConvert::CurveToBSplineCurve(theC2d, Convert_QuasiAngular);
    if (isFirst)
    {
      BCurve->SetPole(1, theP);
      return new Geom2d_TrimmedCurve(BCurve, BCurve->FirstParameter(), BCurve->LastParameter());
    }
    else
    {
      BCurve->SetPole(BCurve->NbPoles(), theP);
      return new Geom2d_TrimmedCurve(BCurve, BCurve->FirstParameter(), BCurve->LastParameter());
    }
  }
}
