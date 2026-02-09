#include <BRepTools_Modification.hpp>
#include <BRepTools_Modifier.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_List.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedDataMap.hpp>

#include <Geom2d_Line.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <TopoDS.hpp>
#include <BRepTools.hpp>
#include <TopAbs.hpp>
#include <TopExp.hpp>
#include <gp_Pnt.hpp>

#include <gp.hpp>

#include <Standard_NullObject.hpp>
#include <BRepTools_TrsfModification.hpp>
#include <Message_ProgressScope.hpp>
#include <Geom_Surface.hpp>

static void SetShapeFlags(const TopoDS_Shape& theInSh, TopoDS_Shape& theOutSh);

BRepTools_Modifier::BRepTools_Modifier(bool theMutableInput)
    : myDone(false),
      myMutableInput(theMutableInput)
{
}

BRepTools_Modifier::BRepTools_Modifier(const TopoDS_Shape& S)
    : myShape(S),
      myDone(false),
      myMutableInput(false)
{
  Put(S);
}

BRepTools_Modifier::BRepTools_Modifier(const TopoDS_Shape&                        S,
                                       const occ::handle<BRepTools_Modification>& M)
    : myShape(S),
      myDone(false),
      myMutableInput(false)
{
  Put(S);
  Perform(M);
}

void BRepTools_Modifier::Init(const TopoDS_Shape& S)
{
  myShape = S;
  myDone  = false;
  Put(S);
}

#ifdef DEBUG_Modifier
static NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MapE, MapF;
#endif

void BRepTools_Modifier::Perform(const occ::handle<BRepTools_Modification>& M,
                                 const Message_ProgressRange&               theProgress)
{
  if (myShape.IsNull())
  {
    throw Standard_NullObject();
  }
#ifdef DEBUG_Modifier
  MapE.Clear();
  MapF.Clear();
  TopExp::MapShapes(myShape, TopAbs_EDGE, MapE);
  TopExp::MapShapes(myShape, TopAbs_FACE, MapF);
#endif
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator theIter(myMap);

  Message_ProgressScope aPS(theProgress, "Converting Shape", 2);

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aMVE, aMEF;
  TopExp::MapShapesAndAncestors(myShape, TopAbs_VERTEX, TopAbs_EDGE, aMVE);
  TopExp::MapShapesAndAncestors(myShape, TopAbs_EDGE, TopAbs_FACE, aMEF);

  CreateNewVertices(aMVE, M);

  FillNewCurveInfo(aMEF, M);

  FillNewSurfaceInfo(M);

  if (!myMutableInput)
    CreateOtherVertices(aMVE, aMEF, M);

  bool aNewGeom;
  Rebuild(myShape, M, aNewGeom, aPS.Next());

  if (!aPS.More())
  {

    return;
  }

  if (myShape.ShapeType() == TopAbs_FACE)
  {
    if (myShape.Orientation() == TopAbs_REVERSED)
    {
      myMap(myShape).Reverse();
    }
    else
    {
      myMap(myShape).Orientation(myShape.Orientation());
    }
  }
  else
  {
    myMap(myShape).Orientation(myShape.Orientation());
  }

  BRep_Builder aBB;

  for (int ii = 1; ii <= aMEF.Extent(); ii++)
  {
    const TopoDS_Edge& CurE = TopoDS::Edge(aMEF.FindKey(ii));
    const TopoDS_Edge& NewE = TopoDS::Edge(myMap(CurE));
    if (!CurE.IsSame(NewE))
    {
      NCollection_List<TopoDS_Shape>::Iterator it;
      it.Initialize(aMEF.FindFromKey(CurE));
      TopoDS_Face F1, F2;
      while (it.More() && F2.IsNull())
      {
        if (F1.IsNull())
        {
          F1 = TopoDS::Face(it.Value());
        }
        else
        {
          F2 = TopoDS::Face(it.Value());
        }
        it.Next();
      }
      if (!F2.IsNull())
      {
        const TopoDS_Face& newf1   = TopoDS::Face(myMap(F1));
        const TopoDS_Face& newf2   = TopoDS::Face(myMap(F2));
        GeomAbs_Shape      Newcont = M->Continuity(CurE, F1, F2, NewE, newf1, newf2);
        if (Newcont > GeomAbs_C0)
        {
          aBB.Continuity(NewE, newf1, newf2, Newcont);
        }
      }
    }
    theIter.Next();
  }

  myDone = true;
}

void BRepTools_Modifier::Put(const TopoDS_Shape& S)
{
  if (!myMap.IsBound(S))
  {
    myMap.Bind(S, TopoDS_Shape());
    for (TopoDS_Iterator theIterator(S, false); theIterator.More(); theIterator.Next())
    {

      Put(theIterator.Value());
    }
  }
}

bool BRepTools_Modifier::Rebuild(const TopoDS_Shape&                        S,
                                 const occ::handle<BRepTools_Modification>& M,
                                 bool&                                      theNewGeom,
                                 const Message_ProgressRange&               theProgress)
{
#ifdef DEBUG_Modifier
  int iF = MapF.Contains(S) ? MapF.FindIndex(S) : 0;
  int iE = MapE.Contains(S) ? MapE.FindIndex(S) : 0;
#endif
  TopAbs_ShapeEnum ts     = S.ShapeType();
  TopoDS_Shape&    result = myMap(S);
  if (!result.IsNull())
  {
    theNewGeom = myHasNewGeom.Contains(S);
    return !S.IsSame(result);
  }
  bool               rebuild = false, RevWires = false;
  TopAbs_Orientation ResOr = TopAbs_FORWARD;
  BRep_Builder       B;
  double             tol;
  bool               No3DCurve = false;

  switch (ts)
  {
    case TopAbs_FACE:
    {
      rebuild = myNSInfo.IsBound(TopoDS::Face(S));
      if (rebuild)
      {
        const NewSurfaceInfo& aNSinfo = myNSInfo(TopoDS::Face(S));
        RevWires                      = aNSinfo.myRevWires;
        B.MakeFace(TopoDS::Face(result),
                   aNSinfo.mySurface,
                   aNSinfo.myLoc.Predivided(S.Location()),
                   aNSinfo.myToler);
        result.Location(S.Location(), false);
        if (aNSinfo.myRevFace)
          ResOr = TopAbs_REVERSED;

        B.NaturalRestriction(TopoDS::Face(result), BRep_Tool::NaturalRestriction(TopoDS::Face(S)));
      }

      occ::handle<Poly_Triangulation> aTriangulation;
      if (M->NewTriangulation(TopoDS::Face(S), aTriangulation))
      {
        if (rebuild)
          B.UpdateFace(TopoDS::Face(result), aTriangulation);
        else
        {
          B.MakeFace(TopoDS::Face(result), aTriangulation);
          result.Location(S.Location(), false);
        }
        rebuild = true;
      }
    }
    break;

    case TopAbs_EDGE:
    {
      rebuild = myNCInfo.IsBound(TopoDS::Edge(S));
      if (rebuild)
      {
        const NewCurveInfo& aNCinfo = myNCInfo(TopoDS::Edge(S));
        if (aNCinfo.myCurve.IsNull())
        {
          B.MakeEdge(TopoDS::Edge(result));
          B.Degenerated(TopoDS::Edge(result), BRep_Tool::Degenerated(TopoDS::Edge(S)));
          B.UpdateEdge(TopoDS::Edge(result), aNCinfo.myToler);
          No3DCurve = true;
        }
        else
        {
          B.MakeEdge(TopoDS::Edge(result),
                     aNCinfo.myCurve,
                     aNCinfo.myLoc.Predivided(S.Location()),
                     aNCinfo.myToler);
          No3DCurve = false;
        }
        result.Location(S.Location(), false);

        B.SameParameter(TopoDS::Edge(result), BRep_Tool::SameParameter(TopoDS::Edge(S)));
        B.SameRange(TopoDS::Edge(result), BRep_Tool::SameRange(TopoDS::Edge(S)));
      }

      occ::handle<Poly_Polygon3D> aPolygon;
      if (M->NewPolygon(TopoDS::Edge(S), aPolygon))
      {
        if (rebuild)
          B.UpdateEdge(TopoDS::Edge(result), aPolygon, S.Location());
        else
        {
          B.MakeEdge(TopoDS::Edge(result), aPolygon);
          result.Location(S.Location(), false);
        }
        rebuild = true;
      }
    }
    break;
    default:;
  }

  bool newgeom = rebuild;
  theNewGeom   = rebuild;

  TopoDS_Iterator it;

  {
    int aShapeCount = 0;
    {
      for (it.Initialize(S, false); it.More(); it.Next())
        ++aShapeCount;
    }

    Message_ProgressScope aPS(theProgress, "Converting SubShapes", aShapeCount);

    for (it.Initialize(S, false); it.More() && aPS.More(); it.Next())
    {

      bool isSubNewGeom = false;
      bool subrebuilt   = Rebuild(it.Value(), M, isSubNewGeom, aPS.Next());
      rebuild           = subrebuilt || rebuild;
      theNewGeom        = theNewGeom || isSubNewGeom;
    }
    if (!aPS.More())
    {

      return false;
    }
  }
  if (theNewGeom)
    myHasNewGeom.Add(S);

  if (rebuild && !newgeom)
  {
    result = S.EmptyCopied();
    result.Orientation(TopAbs_FORWARD);
  }

  if (rebuild)
  {
    TopAbs_Orientation orient;
    for (it.Initialize(S, false); it.More(); it.Next())
    {
      orient = it.Value().Orientation();
      if (RevWires || myMap(it.Value()).Orientation() == TopAbs_REVERSED)
      {
        orient = TopAbs::Reverse(orient);
      }
      B.Add(result, myMap(it.Value()).Oriented(orient));
    }

    if (ts == TopAbs_FACE)
    {

      occ::handle<Geom2d_Curve> curve2d;
      TopoDS_Face               face = TopoDS::Face(S);
      TopAbs_Orientation        fcor = face.Orientation();
      if (fcor != TopAbs_REVERSED)
        fcor = TopAbs_FORWARD;

      TopExp_Explorer ex(face.Oriented(fcor), TopAbs_EDGE);
      for (; ex.More(); ex.Next())
      {
        const TopoDS_Edge& edge = TopoDS::Edge(ex.Current());

#ifdef DEBUG_Modifier
        iE = MapE.Contains(edge) ? MapE.FindIndex(edge) : 0;
#endif
        if (theNewGeom
            && M->NewCurve2d(edge,
                             face,
                             TopoDS::Edge(myMap(ex.Current())),
                             TopoDS::Face(result),
                             curve2d,
                             tol))
        {

          bool isClosed = false;
          if (BRep_Tool::IsClosed(edge, face))
          {
            isClosed = (!newgeom || BRepTools::IsReallyClosed(edge, face));
            if (!isClosed)
            {
              TopLoc_Location aLoc;
              TopoDS_Shape    resface = (myMap.IsBound(face) ? myMap(face) : face);
              if (resface.IsNull())
                resface = face;
              occ::handle<Geom_Surface> aSurf = BRep_Tool::Surface(TopoDS::Face(resface), aLoc);

              TopExp_Explorer aExpF(myShape, TopAbs_FACE);
              for (; aExpF.More() && !isClosed; aExpF.Next())
              {
                TopoDS_Face anOther = TopoDS::Face(aExpF.Current());
                if (anOther.IsSame(face))
                  continue;
                TopoDS_Shape resface2 = (myMap.IsBound(anOther) ? myMap(anOther) : anOther);
                if (resface2.IsNull())
                  resface2 = anOther;
                TopLoc_Location           anOtherLoc;
                occ::handle<Geom_Surface> anOtherSurf =
                  BRep_Tool::Surface(TopoDS::Face(resface2), anOtherLoc);
                if (aSurf == anOtherSurf && aLoc.IsEqual(anOtherLoc))
                {
                  TopExp_Explorer aExpE(anOther, TopAbs_EDGE);
                  for (; aExpE.More() && !isClosed; aExpE.Next())
                    isClosed = edge.IsSame(aExpE.Current());
                }
              }
            }
          }
          if (isClosed)
          {
            TopoDS_Edge  CurE         = TopoDS::Edge(myMap(edge));
            TopoDS_Shape aLocalResult = result;
            aLocalResult.Orientation(TopAbs_FORWARD);
            TopoDS_Face               CurF = TopoDS::Face(aLocalResult);
            occ::handle<Geom2d_Curve> curve2d1, currcurv;
            double                    f, l;
            if ((!RevWires && fcor != edge.Orientation())
                || (RevWires && fcor == edge.Orientation()))
            {
              CurE.Orientation(TopAbs_FORWARD);
              curve2d1 = BRep_Tool::CurveOnSurface(CurE, CurF, f, l);
              if (curve2d1.IsNull())
                curve2d1 = new Geom2d_Line(gp::OX2d());
              B.UpdateEdge(CurE, curve2d1, curve2d, CurF, 0.);
            }
            else
            {
              CurE.Orientation(TopAbs_REVERSED);
              curve2d1 = BRep_Tool::CurveOnSurface(CurE, CurF, f, l);
              if (curve2d1.IsNull())
                curve2d1 = new Geom2d_Line(gp::OX2d());
              B.UpdateEdge(CurE, curve2d, curve2d1, CurF, 0.);
            }
            currcurv = BRep_Tool::CurveOnSurface(CurE, CurF, f, l);
            B.Range(CurE, f, l);
          }
          else
          {
            B.UpdateEdge(TopoDS::Edge(myMap(ex.Current())), curve2d, TopoDS::Face(result), 0.);
          }

          TopLoc_Location         theLoc;
          double                  theF, theL;
          occ::handle<Geom_Curve> C3D =
            BRep_Tool::Curve(TopoDS::Edge(myMap(ex.Current())), theLoc, theF, theL);
          if (C3D.IsNull())
          {
            double          param;
            TopExp_Explorer ex2(edge, TopAbs_VERTEX);
            while (ex2.More())
            {
              const TopoDS_Vertex& vertex = TopoDS::Vertex(ex2.Current());
              if (!M->NewParameter(vertex, edge, param, tol))
              {
                tol   = BRep_Tool::Tolerance(vertex);
                param = BRep_Tool::Parameter(vertex, edge);
              }

              TopAbs_Orientation vtxrelat = vertex.Orientation();
              if (edge.Orientation() == TopAbs_REVERSED)
              {

                vtxrelat = TopAbs::Reverse(vtxrelat);
              }

              TopoDS_Vertex aLocalVertex = TopoDS::Vertex(myMap(vertex));
              aLocalVertex.Orientation(vtxrelat);

              B.UpdateVertex(aLocalVertex, param, TopoDS::Edge(myMap(edge)), tol);
              ex2.Next();
            }
          }
        }

        occ::handle<Poly_PolygonOnTriangulation> aPolyOnTria_1, aPolyOnTria_2;
        bool aNewPonT = M->NewPolygonOnTriangulation(edge, face, aPolyOnTria_1);
        if (BRepTools::IsReallyClosed(edge, face))
        {

          TopoDS_Edge anEdgeRev = edge;
          anEdgeRev.Reverse();
          aNewPonT = M->NewPolygonOnTriangulation(anEdgeRev, face, aPolyOnTria_2) || aNewPonT;

          if (aPolyOnTria_1.IsNull() && !aPolyOnTria_2.IsNull())
          {
            aPolyOnTria_1 = aPolyOnTria_2;
            aPolyOnTria_2 = occ::handle<Poly_PolygonOnTriangulation>();
          }
        }
        if (aNewPonT)
        {
          TopLoc_Location                 aLocation;
          occ::handle<Poly_Triangulation> aNewFaceTria =
            BRep_Tool::Triangulation(TopoDS::Face(myMap(face)), aLocation);
          TopoDS_Edge aNewEdge = TopoDS::Edge(myMap(edge));
          if (aPolyOnTria_2.IsNull())
            B.UpdateEdge(aNewEdge, aPolyOnTria_1, aNewFaceTria, aLocation);
          else
          {
            if (edge.Orientation() == TopAbs_FORWARD)
              B.UpdateEdge(aNewEdge, aPolyOnTria_1, aPolyOnTria_2, aNewFaceTria, aLocation);
            else
              B.UpdateEdge(aNewEdge, aPolyOnTria_2, aPolyOnTria_1, aNewFaceTria, aLocation);
          }
        }
      }
    }

    else if (ts == TopAbs_EDGE && !No3DCurve)
    {

      double             param;
      const TopoDS_Edge& edge = TopoDS::Edge(S);
      TopAbs_Orientation edor = edge.Orientation();
      if (edor != TopAbs_REVERSED)
        edor = TopAbs_FORWARD;
      TopExp_Explorer ex(edge.Oriented(edor), TopAbs_VERTEX);
      while (ex.More())
      {
        const TopoDS_Vertex& vertex = TopoDS::Vertex(ex.Current());

        if (!M->NewParameter(vertex, edge, param, tol))
        {
          tol   = BRep_Tool::Tolerance(vertex);
          param = BRep_Tool::Parameter(vertex, edge);
        }

        TopAbs_Orientation vtxrelat = vertex.Orientation();
        if (edor == TopAbs_REVERSED)
        {

          vtxrelat = TopAbs::Reverse(vtxrelat);
        }

        TopoDS_Vertex aLocalVertex = TopoDS::Vertex(myMap(vertex));
        aLocalVertex.Orientation(vtxrelat);

        if (myMutableInput || !aLocalVertex.IsSame(vertex))
          B.UpdateVertex(aLocalVertex, param, TopoDS::Edge(result), tol);
        ex.Next();
      }
    }

    result.Orientable(S.Orientable());
    result.Closed(S.Closed());
    result.Infinite(S.Infinite());
  }
  else
    result = S;

  result.Orientation(ResOr);

  SetShapeFlags(S, result);

  return rebuild;
}

void BRepTools_Modifier::CreateNewVertices(
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>& theMVE,
  const occ::handle<BRepTools_Modification>&                 M)
{
  double       aToler;
  BRep_Builder aBB;
  gp_Pnt       aPnt;
  for (int i = 1; i <= theMVE.Extent(); i++)
  {

    const TopoDS_Vertex& aV     = TopoDS::Vertex(theMVE.FindKey(i));
    bool                 IsNewP = M->NewPoint(aV, aPnt, aToler);
    if (IsNewP)
    {
      TopoDS_Vertex aNewV;
      aBB.MakeVertex(aNewV, aPnt, aToler);
      SetShapeFlags(aV, aNewV);
      myMap(aV) = aNewV;
      myHasNewGeom.Add(aV);
    }
    else if (myMutableInput)
      myMap(aV) = aV.Oriented(TopAbs_FORWARD);
  }
}

void BRepTools_Modifier::FillNewCurveInfo(
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>& theMEF,
  const occ::handle<BRepTools_Modification>&                 M)
{
  occ::handle<Geom_Curve>          aCurve;
  TopLoc_Location                  aLocation;
  BRepTools_Modifier::NewCurveInfo aNCinfo;
  double                           aToler;
  for (int i = 1; i <= theMEF.Extent(); i++)
  {
    const TopoDS_Edge& anE      = TopoDS::Edge(theMEF.FindKey(i));
    bool               IsNewCur = M->NewCurve(anE, aCurve, aLocation, aToler);
    if (IsNewCur)
    {
      aNCinfo.myCurve = aCurve;
      aNCinfo.myLoc   = aLocation;
      aNCinfo.myToler = aToler;
      myNCInfo.Bind(anE, aNCinfo);
      myHasNewGeom.Add(anE);
    }
  }
}

void BRepTools_Modifier::FillNewSurfaceInfo(const occ::handle<BRepTools_Modification>& M)
{
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMF;
  TopExp::MapShapes(myShape, TopAbs_FACE, aMF);
  BRepTools_Modifier::NewSurfaceInfo aNSinfo;
  for (int i = 1; i <= aMF.Extent(); i++)
  {
    const TopoDS_Face&        aF = TopoDS::Face(aMF(i));
    bool                      RevFace;
    bool                      RevWires;
    occ::handle<Geom_Surface> aSurface;
    TopLoc_Location           aLocation;
    double                    aToler1;
    bool IsNewSur = M->NewSurface(aF, aSurface, aLocation, aToler1, RevWires, RevFace);
    if (IsNewSur)
    {
      aNSinfo.mySurface  = aSurface;
      aNSinfo.myLoc      = aLocation;
      aNSinfo.myToler    = aToler1;
      aNSinfo.myRevWires = RevWires;
      aNSinfo.myRevFace  = RevFace;
      myNSInfo.Bind(aF, aNSinfo);
      myHasNewGeom.Add(aF);
    }
    else
    {

      bool            notRebuilded = true;
      TopExp_Explorer exE(aF, TopAbs_EDGE);
      while (exE.More() && notRebuilded)
      {
        const TopoDS_Edge& anEE = TopoDS::Edge(exE.Current());
        if (myNCInfo.IsBound(anEE))
        {
          notRebuilded = false;
          break;
        }
        TopExp_Explorer exV(anEE, TopAbs_VERTEX);
        while (exV.More() && notRebuilded)
        {
          const TopoDS_Vertex& aVV = TopoDS::Vertex(exV.Current());
          if (!myMap(aVV).IsNull())
          {
            notRebuilded = false;
            break;
          }
          exV.Next();
        }
        exE.Next();
      }
      if (notRebuilded)
      {

        myNonUpdFace.Add(aF);
      }
    }
  }
}

void BRepTools_Modifier::CreateOtherVertices(
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>& theMVE,
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>& theMEF,
  const occ::handle<BRepTools_Modification>&                 M)
{
  double aToler;

  for (int i = 1; i <= theMVE.Extent(); i++)
  {
    const TopoDS_Vertex& aV    = TopoDS::Vertex(theMVE.FindKey(i));
    TopoDS_Vertex        aNewV = TopoDS::Vertex(myMap(aV));
    if (aNewV.IsNull())
    {
      const NCollection_List<TopoDS_Shape>&    aLEdges   = theMVE(i);
      bool                                     toReplace = false;
      NCollection_List<TopoDS_Shape>::Iterator it(aLEdges);
      for (; it.More() && !toReplace; it.Next())
      {
        const TopoDS_Edge& anE = TopoDS::Edge(it.Value());
        if (myNCInfo.IsBound(anE) && !myNCInfo(anE).myCurve.IsNull())
          toReplace = true;

        if (!toReplace)
        {
          const NCollection_List<TopoDS_Shape>&    aLFaces = theMEF.FindFromKey(anE);
          NCollection_List<TopoDS_Shape>::Iterator it2(aLFaces);
          for (; it2.More(); it2.Next())
          {
            const TopoDS_Face& aF = TopoDS::Face(it2.Value());
            if (!myNonUpdFace.Contains(aF))
            {
              occ::handle<Geom2d_Curve> aCurve2d;

              TopoDS_Edge aDummyE = TopoDS::Edge(anE.EmptyCopied());
              if (M->NewCurve2d(anE, aF, aDummyE, TopoDS_Face(), aCurve2d, aToler))
              {
                toReplace = true;
                break;
              }
            }
          }
        }
      }
      if (toReplace)
        aNewV = TopoDS::Vertex(aV.EmptyCopied());
      else
        aNewV = aV;
      aNewV.Orientation(TopAbs_FORWARD);
      myMap(aV) = aNewV;
    }
  }
}

static void SetShapeFlags(const TopoDS_Shape& theInSh, TopoDS_Shape& theOutSh)
{
  theOutSh.Modified(theInSh.Modified());
  theOutSh.Checked(theInSh.Checked());
  theOutSh.Orientable(theInSh.Orientable());
  theOutSh.Closed(theInSh.Closed());
  theOutSh.Infinite(theInSh.Infinite());
  theOutSh.Convex(theInSh.Convex());
}

bool BRepTools_Modifier::IsMutableInput() const
{
  return myMutableInput;
}

void BRepTools_Modifier::SetMutableInput(bool theMutableInput)
{
  myMutableInput = theMutableInput;
}
