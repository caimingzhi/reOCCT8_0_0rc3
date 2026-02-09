#include <BRepOffset_SimpleOffset.hpp>

#include <Adaptor3d_CurveOnSurface.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepLib.hpp>
#include <BRepLib_ValidateEdge.hpp>
#include <BRep_Tool.hpp>
#include <BRepOffset.hpp>
#include <Geom_OffsetSurface.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <NCollection_Vector.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>

BRepOffset_SimpleOffset::BRepOffset_SimpleOffset(const TopoDS_Shape& theInputShape,
                                                 const double        theOffsetValue,
                                                 const double        theTolerance)
    : myOffsetValue(theOffsetValue),
      myTolerance(theTolerance)
{
  FillOffsetData(theInputShape);
}

bool BRepOffset_SimpleOffset::NewSurface(const TopoDS_Face&         F,
                                         occ::handle<Geom_Surface>& S,
                                         TopLoc_Location&           L,
                                         double&                    Tol,
                                         bool&                      RevWires,
                                         bool&                      RevFace)
{
  if (!myFaceInfo.IsBound(F))
    return false;

  const NewFaceData& aNFD = myFaceInfo.Find(F);

  S        = aNFD.myOffsetS;
  L        = aNFD.myL;
  Tol      = aNFD.myTol;
  RevWires = aNFD.myRevWires;
  RevFace  = aNFD.myRevFace;

  return true;
}

bool BRepOffset_SimpleOffset::NewCurve(const TopoDS_Edge&       E,
                                       occ::handle<Geom_Curve>& C,
                                       TopLoc_Location&         L,
                                       double&                  Tol)
{
  if (!myEdgeInfo.IsBound(E))
    return false;

  const NewEdgeData& aNED = myEdgeInfo.Find(E);

  C   = aNED.myOffsetC;
  L   = aNED.myL;
  Tol = aNED.myTol;

  return true;
}

bool BRepOffset_SimpleOffset::NewPoint(const TopoDS_Vertex& V, gp_Pnt& P, double& Tol)
{
  if (!myVertexInfo.IsBound(V))
    return false;

  const NewVertexData& aNVD = myVertexInfo.Find(V);

  P   = aNVD.myP;
  Tol = aNVD.myTol;

  return true;
}

bool BRepOffset_SimpleOffset::NewCurve2d(const TopoDS_Edge& E,
                                         const TopoDS_Face& F,
                                         const TopoDS_Edge&,
                                         const TopoDS_Face&,
                                         occ::handle<Geom2d_Curve>& C,
                                         double&                    Tol)
{

  double aF, aL;
  C   = BRep_Tool::CurveOnSurface(E, F, aF, aL);
  Tol = BRep_Tool::Tolerance(E);

  if (myEdgeInfo.IsBound(E))
    Tol = myEdgeInfo.Find(E).myTol;

  return true;
}

bool BRepOffset_SimpleOffset::NewParameter(const TopoDS_Vertex& V,
                                           const TopoDS_Edge&   E,
                                           double&              P,
                                           double&              Tol)
{

  P   = BRep_Tool::Parameter(V, E);
  Tol = BRep_Tool::Tolerance(V);

  if (myVertexInfo.IsBound(V))
    Tol = myVertexInfo.Find(V).myTol;

  return true;
}

GeomAbs_Shape BRepOffset_SimpleOffset::Continuity(const TopoDS_Edge& E,
                                                  const TopoDS_Face& F1,
                                                  const TopoDS_Face& F2,
                                                  const TopoDS_Edge&,
                                                  const TopoDS_Face&,
                                                  const TopoDS_Face&)
{

  return BRep_Tool::Continuity(E, F1, F2);
}

void BRepOffset_SimpleOffset::FillOffsetData(const TopoDS_Shape& theShape)
{

  myFaceInfo.Clear();
  myEdgeInfo.Clear();
  myVertexInfo.Clear();

  TopExp_Explorer anExpSF(theShape, TopAbs_FACE);
  for (; anExpSF.More(); anExpSF.Next())
  {
    const TopoDS_Face& aCurrFace = TopoDS::Face(anExpSF.Current());
    FillFaceData(aCurrFace);
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aEdgeFaceMap;
  TopExp::MapShapesAndAncestors(theShape, TopAbs_EDGE, TopAbs_FACE, aEdgeFaceMap);
  for (int anIdx = 1; anIdx <= aEdgeFaceMap.Size(); ++anIdx)
  {
    const TopoDS_Edge& aCurrEdge = TopoDS::Edge(aEdgeFaceMap.FindKey(anIdx));
    FillEdgeData(aCurrEdge, aEdgeFaceMap, anIdx);
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aVertexEdgeMap;
  TopExp::MapShapesAndAncestors(theShape, TopAbs_VERTEX, TopAbs_EDGE, aVertexEdgeMap);
  for (int anIdx = 1; anIdx <= aVertexEdgeMap.Size(); ++anIdx)
  {
    const TopoDS_Vertex& aCurrVertex = TopoDS::Vertex(aVertexEdgeMap.FindKey(anIdx));
    FillVertexData(aCurrVertex, aVertexEdgeMap, anIdx);
  }
}

void BRepOffset_SimpleOffset::FillFaceData(const TopoDS_Face& theFace)
{
  NewFaceData aNFD;
  aNFD.myRevWires = false;
  aNFD.myRevFace  = false;
  aNFD.myTol      = BRep_Tool::Tolerance(theFace);

  occ::handle<Geom_Surface> aS = BRep_Tool::Surface(theFace);
  aS                           = BRepOffset::CollapseSingularities(aS, theFace, myTolerance);

  double aMult = 1.0;
  if (theFace.Orientation() == TopAbs_REVERSED)
    aMult = -1.0;

  BRepOffset_Status aStatus;
  aNFD.myOffsetS = BRepOffset::Surface(aS, aMult * myOffsetValue, aStatus, true);
  aNFD.myL       = TopLoc_Location();

  myFaceInfo.Bind(theFace, aNFD);
}

void BRepOffset_SimpleOffset::FillEdgeData(
  const TopoDS_Edge&                                         theEdge,
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>& theEdgeFaceMap,
  const int                                                  theIdx)
{
  const NCollection_List<TopoDS_Shape>& aFacesList = theEdgeFaceMap(theIdx);

  if (aFacesList.Size() == 0)
    return;

  const TopoDS_Face& aCurrFace = TopoDS::Face(aFacesList.First());

  if (!myFaceInfo.IsBound(aCurrFace))
    return;

  const NewFaceData&        aNFD         = myFaceInfo.Find(aCurrFace);
  occ::handle<Geom_Surface> anOffsetSurf = aNFD.myOffsetS;

  double                    aF, aL;
  occ::handle<Geom2d_Curve> aC2d = BRep_Tool::CurveOnSurface(theEdge, aCurrFace, aF, aL);

  BRepBuilderAPI_MakeEdge anEdgeMaker(aC2d, anOffsetSurf, aF, aL);
  TopoDS_Edge             aNewEdge = anEdgeMaker.Edge();

  double aTol = BRep_Tool::MaxTolerance(theEdge, TopAbs_VERTEX);
  BRepLib::BuildCurves3d(aNewEdge, aTol);

  NewEdgeData aNED;
  aNED.myOffsetC = BRep_Tool::Curve(aNewEdge, aNED.myL, aF, aL);

  double                                   anEdgeTol = 0.0;
  NCollection_List<TopoDS_Shape>::Iterator anIter(aFacesList);
  for (; !aNED.myOffsetC.IsNull() && anIter.More(); anIter.Next())
  {
    const TopoDS_Face& aCurFace = TopoDS::Face(anIter.Value());

    if (!myFaceInfo.IsBound(aCurFace))
      continue;

    const occ::handle<Geom2d_Curve> aC2dNew = BRep_Tool::CurveOnSurface(theEdge, aCurFace, aF, aL);
    const occ::handle<Adaptor2d_Curve2d> aHCurve2d = new Geom2dAdaptor_Curve(aC2dNew, aF, aL);
    const occ::handle<Adaptor3d_Surface> aHSurface =
      new GeomAdaptor_Surface(myFaceInfo.Find(aCurFace).myOffsetS);
    const occ::handle<Adaptor3d_CurveOnSurface> aCurveOnSurf =
      new Adaptor3d_CurveOnSurface(aHCurve2d, aHSurface);

    const occ::handle<Adaptor3d_Curve> aCurve3d = new GeomAdaptor_Curve(aNED.myOffsetC, aF, aL);

    BRepLib_ValidateEdge aValidateEdge(aCurve3d, aCurveOnSurf, true);
    aValidateEdge.Process();
    if (aValidateEdge.IsDone())
    {
      double aMaxTol1 = aValidateEdge.GetMaxDistance();
      anEdgeTol       = std::max(anEdgeTol, aMaxTol1);
    }
  }
  aNED.myTol = std::max(BRep_Tool::Tolerance(aNewEdge), anEdgeTol);

  myEdgeInfo.Bind(theEdge, aNED);
}

void BRepOffset_SimpleOffset::FillVertexData(
  const TopoDS_Vertex&                                       theVertex,
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>& theVertexEdgeMap,
  const int                                                  theIdx)
{

  gp_Pnt aCurrPnt = BRep_Tool::Pnt(theVertex);

  const NCollection_List<TopoDS_Shape>& aEdgesList = theVertexEdgeMap(theIdx);

  if (aEdgesList.Size() == 0)
    return;

  NCollection_Vector<gp_Pnt> anOffsetPointVec;

  double aMaxEdgeTol = 0.0;

  NCollection_List<TopoDS_Shape>::Iterator anIterEdges(aEdgesList);
  for (; anIterEdges.More(); anIterEdges.Next())
  {
    const TopoDS_Edge& aCurrEdge = TopoDS::Edge(anIterEdges.Value());

    if (!myEdgeInfo.IsBound(aCurrEdge))
      continue;

    double                  aF, aL;
    occ::handle<Geom_Curve> aC3d = BRep_Tool::Curve(aCurrEdge, aF, aL);

    if (aC3d.IsNull())
      continue;

    const gp_Pnt aPntF = aC3d->Value(aF);
    const gp_Pnt aPntL = aC3d->Value(aL);

    const double aSqDistF = aPntF.SquareDistance(aCurrPnt);
    const double aSqDistL = aPntL.SquareDistance(aCurrPnt);

    double aMinParam = aF, aMaxParam = aL;
    if (aSqDistL < aSqDistF)
    {

      aMinParam = aL;
      aMaxParam = aF;
    }

    const NewEdgeData&             aNED          = myEdgeInfo.Find(aCurrEdge);
    const occ::handle<Geom_Curve>& anOffsetCurve = aNED.myOffsetC;
    const gp_Pnt                   anOffsetPoint = anOffsetCurve->Value(aMinParam);
    anOffsetPointVec.Append(anOffsetPoint);

    TopoDS_Vertex aV1, aV2;
    TopExp::Vertices(aCurrEdge, aV1, aV2);
    if (aV1.IsSame(aV2))
    {
      const gp_Pnt anOffsetPointLast = anOffsetCurve->Value(aMaxParam);
      anOffsetPointVec.Append(anOffsetPointLast);
    }

    aMaxEdgeTol = std::max(aMaxEdgeTol, aNED.myTol);
  }

  gp_Pnt aCenter(0.0, 0.0, 0.0);
  for (int i = anOffsetPointVec.Lower(); i <= anOffsetPointVec.Upper(); ++i)
  {
    aCenter.SetXYZ(aCenter.XYZ() + anOffsetPointVec.Value(i).XYZ());
  }
  aCenter.SetXYZ(aCenter.XYZ() / anOffsetPointVec.Size());

  double aSqMaxDist = 0.0;
  for (int i = anOffsetPointVec.Lower(); i <= anOffsetPointVec.Upper(); ++i)
  {
    const double aSqDist = aCenter.SquareDistance(anOffsetPointVec.Value(i));
    if (aSqDist > aSqMaxDist)
      aSqMaxDist = aSqDist;
  }

  const double aResTol = std::max(aMaxEdgeTol, std::sqrt(aSqMaxDist));

  const double  aMultCoeff = 1.001;
  NewVertexData aNVD;
  aNVD.myP   = aCenter;
  aNVD.myTol = aResTol * aMultCoeff;

  myVertexInfo.Bind(theVertex, aNVD);
}
