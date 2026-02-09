#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepLib.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <BRepTools_Substitution.hpp>
#include <ElCLib.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dConvert_CompCurveToBSplineCurve.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BoundedCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomLib.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_NullObject.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopOpeBRepTool_FuseEdges.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

#ifdef OCCT_DEBUG
extern bool TopOpeBRepBuild_GettraceFE();
#endif

TopOpeBRepTool_FuseEdges::TopOpeBRepTool_FuseEdges(const TopoDS_Shape& theShape,

                                                   const bool)
    : myShape(theShape),
      myShapeDone(false),
      myEdgesDone(false),
      myResultEdgesDone(false),
      myNbConnexEdge(0)
{

  Standard_NullObject_Raise_if(theShape.IsNull(), "FuseEdges");
  myMapFaces.Clear();
}

void TopOpeBRepTool_FuseEdges::AvoidEdges(
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapEdg)
{
  myAvoidEdg = theMapEdg;
}

void TopOpeBRepTool_FuseEdges::Edges(
  NCollection_DataMap<int, NCollection_List<TopoDS_Shape>>& theMapLstEdg)
{

  if (!myEdgesDone)
  {
    BuildListEdges();
  }

  theMapLstEdg = myMapLstEdg;
}

void TopOpeBRepTool_FuseEdges::ResultEdges(NCollection_DataMap<int, TopoDS_Shape>& theMapEdg)
{

  if (!myEdgesDone)
  {
    BuildListEdges();
  }

  if (!myResultEdgesDone)
  {
    BuildListResultEdges();
  }

  theMapEdg = myMapEdg;
}

void TopOpeBRepTool_FuseEdges::Faces(
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theMapFac)
{

  if (!myEdgesDone)
  {
    BuildListEdges();
  }

  if (!myResultEdgesDone)
  {
    BuildListResultEdges();
  }

  if (!myShapeDone)
  {
    Perform();
  }

  theMapFac = myMapFaces;
}

int TopOpeBRepTool_FuseEdges::NbVertices()
{

  Standard_NullObject_Raise_if(myShape.IsNull(), "FuseEdges : No Shape");
  int nbedges, nbvertices = 0;

  if (!myEdgesDone)
  {
    BuildListEdges();
  }

  if ((nbedges = myMapLstEdg.Extent()) > 0)
  {

    NCollection_DataMap<int, NCollection_List<TopoDS_Shape>>::Iterator itEdg;
    for (itEdg.Initialize(myMapLstEdg); itEdg.More(); itEdg.Next())
    {
      const int&                            iLst    = itEdg.Key();
      const NCollection_List<TopoDS_Shape>& LmapEdg = myMapLstEdg.Find(iLst);
      nbvertices += LmapEdg.Extent() - 1;
    }
  }

  return nbvertices;
}

TopoDS_Shape& TopOpeBRepTool_FuseEdges::Shape()
{
  Standard_NullObject_Raise_if(myShape.IsNull(), "FuseEdges : No Shape");

  if (!myEdgesDone)
  {
    BuildListEdges();
  }

  if (!myResultEdgesDone)
  {
    BuildListResultEdges();
  }

  if (!myShapeDone)
  {
    Perform();
  }

  return myShape;
}

void TopOpeBRepTool_FuseEdges::BuildListEdges()
{

#ifdef OCCT_DEBUG
  bool tFE = TopOpeBRepBuild_GettraceFE();
#endif

#ifdef OCCT_DEBUG
  if (tFE)
    std::cout << std::endl << "FuseEdges : BuildListEdges  " << std::endl;
#endif

  myMapLstEdg.Clear();
  myMapVerLstEdg.Clear();
  myMapEdgLstFac.Clear();

  TopExp::MapShapesAndUniqueAncestors(myShape, TopAbs_VERTEX, TopAbs_EDGE, myMapVerLstEdg);
  TopExp::MapShapesAndAncestors(myShape, TopAbs_EDGE, TopAbs_FACE, myMapEdgLstFac);

  int                                                    iEdg;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapUniqEdg;

  for (iEdg = 1; iEdg <= myMapEdgLstFac.Extent(); iEdg++)
  {
    const TopoDS_Shape&            edgecur = myMapEdgLstFac.FindKey(iEdg);
    NCollection_List<TopoDS_Shape> LstEdg;

    if (!mapUniqEdg.Contains(edgecur)
        && (edgecur.Orientation() == TopAbs_FORWARD || edgecur.Orientation() == TopAbs_REVERSED))
    {
      if (myAvoidEdg.Contains(edgecur))
        continue;
      BuildListConnexEdge(edgecur, mapUniqEdg, LstEdg);
      if (LstEdg.Extent() > 1)
      {
        myNbConnexEdge++;
        myMapLstEdg.Bind(myNbConnexEdge, LstEdg);
      }
    }
  }

  myEdgesDone       = true;
  myResultEdgesDone = false;
}

void TopOpeBRepTool_FuseEdges::BuildListResultEdges()
{

#ifdef OCCT_DEBUG
  bool tFE = TopOpeBRepBuild_GettraceFE();
#endif

#ifdef OCCT_DEBUG
  if (tFE)
    std::cout << std::endl << "FuseEdges : BuildListResultEdges  " << std::endl;
#endif

  if (myMapLstEdg.Extent() > 0)
  {
    NCollection_DataMap<int, NCollection_List<TopoDS_Shape>>::Iterator itLstEdg;
    TopoDS_Vertex                                                      VF, VL;
    occ::handle<Geom_Curve>                                            C;
    TopLoc_Location                                                    loc;
    double                                                             f, l;
    TopoDS_Edge                                                        NewEdge;

    myMapEdg.Clear();

    for (itLstEdg.Initialize(myMapLstEdg); itLstEdg.More(); itLstEdg.Next())
    {
      const int&                            iLst    = itLstEdg.Key();
      const NCollection_List<TopoDS_Shape>& LmapEdg = myMapLstEdg.Find(iLst);
#ifdef OCCT_DEBUG
      NCollection_List<TopoDS_Shape>::Iterator itEdg;
#endif

      const TopoDS_Edge& OldEdge = TopoDS::Edge(LmapEdg.First());

      if (OldEdge.Orientation() == TopAbs_REVERSED)
      {
        VL = TopExp::FirstVertex(TopoDS::Edge(LmapEdg.First()), true);
        VF = TopExp::LastVertex(TopoDS::Edge(LmapEdg.Last()), true);
      }
      else
      {
        VF = TopExp::FirstVertex(TopoDS::Edge(LmapEdg.First()), true);
        VL = TopExp::LastVertex(TopoDS::Edge(LmapEdg.Last()), true);
      }
      C = BRep_Tool::Curve(OldEdge, loc, f, l);

      if (!loc.IsIdentity())
      {
        C = occ::down_cast<Geom_Curve>(C->Transformed(loc.Transformation()));
      }

      if (C->DynamicType() == STANDARD_TYPE(Geom_TrimmedCurve))
      {
        C = occ::down_cast<Geom_TrimmedCurve>(C)->BasisCurve();
      }

#ifdef OCCT_DEBUG
      if (tFE)
        std::cout << std::endl << "FuseEdges : Creating New Edge " << std::endl;
#endif

      BRepLib_MakeEdge ME(C, VF, VL);

      if (!ME.IsDone())
      {

#ifdef OCCT_DEBUG
        if (tFE)
          std::cout << std::endl
                    << "FuseEdges : MakeEdge failed. Trying to Extend Curve " << std::endl;
#endif
        occ::handle<Geom_BoundedCurve> ExtC = occ::down_cast<Geom_BoundedCurve>(C->Copy());
        if (!ExtC.IsNull())
        {
          gp_Pnt PF = BRep_Tool::Pnt(VF);
          gp_Pnt PL = BRep_Tool::Pnt(VL);
          GeomLib::ExtendCurveToPoint(ExtC, PF, 1, false);
          GeomLib::ExtendCurveToPoint(ExtC, PL, 1, true);

          ME.Init(ExtC, VF, VL);
          if (!ME.IsDone())
            throw Standard_ConstructionError("FuseEdges : Fusion failed");
        }
        else
          throw Standard_ConstructionError("FuseEdges : Fusion failed");
      }

      NewEdge = ME.Edge();

#ifdef OCCT_DEBUG
      if (tFE)
        std::cout << std::endl << "FuseEdges : Updating pcurve " << std::endl;
#endif
      if (UpdatePCurve(OldEdge, NewEdge, LmapEdg))
        myMapEdg.Bind(iLst, NewEdge);
    }

    myResultEdgesDone = true;
  }
}

void TopOpeBRepTool_FuseEdges::Perform()
{

#ifdef OCCT_DEBUG
  bool tFE = TopOpeBRepBuild_GettraceFE();
#endif

  if (!myResultEdgesDone)
  {
    BuildListResultEdges();
  }

#ifdef OCCT_DEBUG
  if (tFE)
    std::cout << std::endl << "FuseEdges : Perform  " << std::endl;
#endif

  if (myMapEdg.Extent() > 0)
  {
    NCollection_DataMap<int, NCollection_List<TopoDS_Shape>>::Iterator itLstEdg;
    NCollection_List<TopoDS_Shape>                                     EmptyList, EdgeToSubs;
    BRepTools_Substitution                                             Bsub;

    for (itLstEdg.Initialize(myMapLstEdg); itLstEdg.More(); itLstEdg.Next())
    {
      const int& iLst = itLstEdg.Key();
      if (!myMapEdg.IsBound(iLst))
        continue;
      const NCollection_List<TopoDS_Shape>&    LmapEdg = myMapLstEdg.Find(iLst);
      NCollection_List<TopoDS_Shape>::Iterator itEdg;

      EdgeToSubs.Clear();
      const TopoDS_Edge& OldEdge = TopoDS::Edge(LmapEdg.First());

      EdgeToSubs.Append(myMapEdg(iLst));
      Bsub.Substitute(OldEdge, EdgeToSubs);

      itEdg.Initialize(LmapEdg);

      while (itEdg.More())
      {
        if (!OldEdge.IsSame(TopoDS::Edge(itEdg.Value())))
        {
          Bsub.Substitute(itEdg.Value(), EmptyList);
        }
        itEdg.Next();
      }
    }

#ifdef OCCT_DEBUG
    if (tFE)
      std::cout << std::endl << "FuseEdges : Building New Shape  " << std::endl;
#endif

    Bsub.Build(myShape);

    TopExp_Explorer exp(myShape, TopAbs_FACE);

    for (; exp.More(); exp.Next())
    {
      const TopoDS_Shape& facecur = exp.Current();
      if (Bsub.IsCopied(facecur))
      {
        myMapFaces.Bind(facecur, (Bsub.Copy(facecur)).First());
      }
    }

    if (Bsub.IsCopied(myShape))
    {
      myShape = (Bsub.Copy(myShape)).First();
    }

#ifdef OCCT_DEBUG
    if (tFE)
      std::cout << std::endl << "FuseEdges : " << NbVertices() << " vertices removed" << std::endl;
#endif
  }

  myShapeDone = true;
}

void TopOpeBRepTool_FuseEdges::BuildListConnexEdge(
  const TopoDS_Shape&                                     theEdge,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapUniq,
  NCollection_List<TopoDS_Shape>&                         theLstEdg)
{

  TopoDS_Vertex VF, VL;

  VL = TopExp::LastVertex(TopoDS::Edge(theEdge), true);
  TopoDS_Shape edgeconnex;
  TopoDS_Shape edgecur = theEdge;
  theLstEdg.Clear();
  theLstEdg.Append(edgecur);
  theMapUniq.Add(edgecur);
  TopAbs_Orientation ori2;

  while (NextConnexEdge(VL, edgecur, edgeconnex))
  {
    if (theMapUniq.Contains(edgeconnex))
    {
      break;
    }
    theLstEdg.Append(edgeconnex);
    edgecur = edgeconnex;

    ori2 = edgecur.Orientation();
    if (ori2 == TopAbs_EXTERNAL || ori2 == TopAbs_INTERNAL)
    {
      break;
    }
    VL = TopExp::LastVertex(TopoDS::Edge(edgecur), true);
    theMapUniq.Add(edgecur);
  }

  edgecur = theEdge;
  VF      = TopExp::FirstVertex(TopoDS::Edge(theEdge), true);

  while (NextConnexEdge(VF, edgecur, edgeconnex))
  {
    if (theMapUniq.Contains(edgeconnex))
    {
      break;
    }
    theLstEdg.Prepend(edgeconnex);
    edgecur = edgeconnex;

    ori2 = edgecur.Orientation();
    if (ori2 == TopAbs_EXTERNAL || ori2 == TopAbs_INTERNAL)
    {
      break;
    }
    VF = TopExp::FirstVertex(TopoDS::Edge(edgecur), true);
    theMapUniq.Add(edgecur);
  }
}

bool TopOpeBRepTool_FuseEdges::NextConnexEdge(const TopoDS_Vertex& theVertex,
                                              const TopoDS_Shape&  theEdge,
                                              TopoDS_Shape&        theEdgeConnex) const
{

  const NCollection_List<TopoDS_Shape>&    LmapEdg   = myMapVerLstEdg.FindFromKey(theVertex);
  bool                                     HasConnex = true;
  NCollection_List<TopoDS_Shape>::Iterator itEdg, itFac1, itFac2;

  if (LmapEdg.Extent() == 2)
  {
    itEdg.Initialize(LmapEdg);
    theEdgeConnex = itEdg.Value();
    if (theEdge.IsSame(theEdgeConnex))
    {
      itEdg.Next();
      theEdgeConnex = itEdg.Value();
    }

    if (myAvoidEdg.Contains(theEdgeConnex))
      HasConnex = false;

    if (HasConnex)
    {
      const NCollection_List<TopoDS_Shape>& LmapFac1 = myMapEdgLstFac.FindFromKey(theEdge);
      const NCollection_List<TopoDS_Shape>& LmapFac2 = myMapEdgLstFac.FindFromKey(theEdgeConnex);

      if (LmapFac1.Extent() == LmapFac2.Extent() && LmapFac1.Extent() < 3)
      {
        itFac1.Initialize(LmapFac1);

        while (itFac1.More() && HasConnex)
        {
          const TopoDS_Shape& face1 = itFac1.Value();
          for (itFac2.Initialize(LmapFac2); itFac2.More(); itFac2.Next())
          {
            const TopoDS_Shape& face2 = itFac2.Value();
            HasConnex                 = false;
            if (face1.IsSame(face2))
            {
              HasConnex = true;
              break;
            }
          }
          itFac1.Next();
        }

        if (HasConnex)
        {
          HasConnex = SameSupport(TopoDS::Edge(theEdge), TopoDS::Edge(theEdgeConnex));
        }
      }
      else
        HasConnex = false;
    }
  }
  else
    HasConnex = false;

  return HasConnex;
}

bool TopOpeBRepTool_FuseEdges::SameSupport(const TopoDS_Edge& E1, const TopoDS_Edge& E2) const
{

  if (E1.IsNull() || E2.IsNull())
  {
    return false;
  }

  occ::handle<Geom_Curve>    C1, C2;
  TopLoc_Location            loc;
  double                     f1, l1, f2, l2;
  occ::handle<Standard_Type> typC1, typC2;

  C1 = BRep_Tool::Curve(E1, loc, f1, l1);

  if (C1.IsNull())
    return false;

  if (!loc.IsIdentity())
  {
    occ::handle<Geom_Geometry> GG1 = C1->Transformed(loc.Transformation());
    C1                             = occ::down_cast<Geom_Curve>(GG1);
  }
  C2 = BRep_Tool::Curve(E2, loc, f2, l2);

  if (C2.IsNull())
    return false;

  if (!loc.IsIdentity())
  {
    occ::handle<Geom_Geometry> GG2 = C2->Transformed(loc.Transformation());
    C2                             = occ::down_cast<Geom_Curve>(GG2);
  }

  typC1 = C1->DynamicType();
  typC2 = C2->DynamicType();

  if (typC1 == STANDARD_TYPE(Geom_TrimmedCurve))
  {
    C1    = occ::down_cast<Geom_TrimmedCurve>(C1)->BasisCurve();
    typC1 = C1->DynamicType();
  }

  if (typC2 == STANDARD_TYPE(Geom_TrimmedCurve))
  {
    C2    = occ::down_cast<Geom_TrimmedCurve>(C2)->BasisCurve();
    typC2 = C2->DynamicType();
  }

  if (typC1 != typC2)
  {
    return false;
  }

  if (typC1 != STANDARD_TYPE(Geom_Line) && typC1 != STANDARD_TYPE(Geom_Circle)
      && typC1 != STANDARD_TYPE(Geom_Ellipse) && typC1 != STANDARD_TYPE(Geom_BSplineCurve)
      && typC1 != STANDARD_TYPE(Geom_BezierCurve))
  {
#ifdef OCCT_DEBUG
    std::cout << " TopOpeBRepTool_FuseEdge : Type de Support non traite" << std::endl;
#endif
    return false;
  }

  const double tollin = Precision::Confusion();
  const double tolang = Precision::Angular();
  if (typC1 == STANDARD_TYPE(Geom_Line))
  {
    gp_Lin li1(occ::down_cast<Geom_Line>(C1)->Lin());
    gp_Lin li2(occ::down_cast<Geom_Line>(C2)->Lin());
    gp_Dir dir1(li1.Direction());
    gp_Dir dir2(li2.Direction());

    if (dir1.IsParallel(dir2, tolang))
    {

      gp_Pnt pf1 = BRep_Tool::Pnt(TopExp::FirstVertex(E1, true));
      gp_Pnt pl1 = BRep_Tool::Pnt(TopExp::LastVertex(E1, true));
      gp_Pnt pf2 = BRep_Tool::Pnt(TopExp::FirstVertex(E2, true));
      gp_Pnt pl2 = BRep_Tool::Pnt(TopExp::LastVertex(E2, true));
      return pl1.Distance(pf2) >= tollin || pl2.Distance(pf1) >= tollin;
    }
    return false;
  }
  else if (typC1 == STANDARD_TYPE(Geom_Circle))
  {
    gp_Circ ci1 = occ::down_cast<Geom_Circle>(C1)->Circ();
    gp_Circ ci2 = occ::down_cast<Geom_Circle>(C2)->Circ();
    return std::abs(ci1.Radius() - ci2.Radius()) <= tollin
           && ci1.Location().SquareDistance(ci2.Location()) <= tollin * tollin
           && ci1.Axis().IsParallel(ci2.Axis(), tolang);
  }
  else if (typC1 == STANDARD_TYPE(Geom_Ellipse))
  {
    gp_Elips ci1 = occ::down_cast<Geom_Ellipse>(C1)->Elips();
    gp_Elips ci2 = occ::down_cast<Geom_Ellipse>(C2)->Elips();

    return std::abs(ci1.MajorRadius() - ci2.MajorRadius()) <= tollin
           && std::abs(ci1.MinorRadius() - ci2.MinorRadius()) <= tollin
           && ci1.Location().SquareDistance(ci2.Location()) <= tollin * tollin
           && ci1.Axis().IsParallel(ci2.Axis(), tolang);
  }
  else if (typC1 == STANDARD_TYPE(Geom_BSplineCurve))
  {

    if (std::abs(f2 - l1) > tollin && std::abs(f1 - l2) > tollin)
    {
      return false;
    }

    occ::handle<Geom_BSplineCurve> B1 = occ::down_cast<Geom_BSplineCurve>(C1);
    occ::handle<Geom_BSplineCurve> B2 = occ::down_cast<Geom_BSplineCurve>(C2);

    int nbpoles = B1->NbPoles();
    if (nbpoles != B2->NbPoles())
    {
      return false;
    }

    int nbknots = B1->NbKnots();
    if (nbknots != B2->NbKnots())
    {
      return false;
    }

    NCollection_Array1<gp_Pnt> P1(1, nbpoles), P2(1, nbpoles);
    B1->Poles(P1);
    B2->Poles(P2);

    double tol3d = BRep_Tool::Tolerance(E1);
    for (int p = 1; p <= nbpoles; p++)
    {
      if ((P1(p)).Distance(P2(p)) > tol3d)
      {
        return false;
      }
    }

    NCollection_Array1<double> K1(1, nbknots), K2(1, nbknots);
    B1->Knots(K1);
    B2->Knots(K2);

    NCollection_Array1<int> M1(1, nbknots), M2(1, nbknots);
    B1->Multiplicities(M1);
    B2->Multiplicities(M2);

    for (int k = 1; k <= nbknots; k++)
    {
      if ((K1(k) - K2(k)) > tollin)
      {
        return false;
      }
      if (std::abs(M1(k) - M2(k)) > tollin)
      {
        return false;
      }
    }

    if (!B1->IsRational())
    {
      if (B2->IsRational())
      {
        return false;
      }
    }
    else
    {
      if (!B2->IsRational())
      {
        return false;
      }
    }

    if (B1->IsRational())
    {
      NCollection_Array1<double> W1(1, nbpoles), W2(1, nbpoles);
      B1->Weights(W1);
      B2->Weights(W2);

      for (int w = 1; w <= nbpoles; w++)
      {
        if (std::abs(W1(w) - W2(w)) > tollin)
        {
          return false;
        }
      }
    }
    return true;
  }
  else if (typC1 == STANDARD_TYPE(Geom_BezierCurve))
  {

    if (std::abs(f2 - l1) > tollin && std::abs(f1 - l2) > tollin)
    {
      return false;
    }

    occ::handle<Geom_BezierCurve> B1 = occ::down_cast<Geom_BezierCurve>(C1);
    occ::handle<Geom_BezierCurve> B2 = occ::down_cast<Geom_BezierCurve>(C2);

    int nbpoles = B1->NbPoles();
    if (nbpoles != B2->NbPoles())
    {
      return false;
    }

    NCollection_Array1<gp_Pnt> P1(1, nbpoles), P2(1, nbpoles);
    B1->Poles(P1);
    B2->Poles(P2);

    for (int p = 1; p <= nbpoles; p++)
    {
      if ((P1(p)).Distance(P2(p)) > tollin)
      {
        return false;
      }
    }

    if (!B1->IsRational())
    {
      if (B2->IsRational())
      {
        return false;
      }
    }
    else
    {
      if (!B2->IsRational())
      {
        return false;
      }
    }

    if (B1->IsRational())
    {
      NCollection_Array1<double> W1(1, nbpoles), W2(1, nbpoles);
      B1->Weights(W1);
      B2->Weights(W2);

      for (int w = 1; w <= nbpoles; w++)
      {
        if (std::abs(W1(w) - W2(w)) > tollin)
        {
          return false;
        }
      }
    }
    return true;
  }
  return false;
}

bool TopOpeBRepTool_FuseEdges::UpdatePCurve(const TopoDS_Edge&                    theOldEdge,
                                            TopoDS_Edge&                          theNewEdge,
                                            const NCollection_List<TopoDS_Shape>& theLstEdg) const
{

  BRep_Builder              B;
  occ::handle<Geom2d_Curve> Curv2d;
  occ::handle<Geom_Surface> Surf;
  TopLoc_Location           loc, locbid;
  double                    ef, el, cf, cl;
  int                       iedg = 1;

  const NCollection_List<TopoDS_Shape>& LmapFac = myMapEdgLstFac.FindFromKey(theOldEdge);

  BRep_Tool::CurveOnSurface(theOldEdge, Curv2d, Surf, loc, cf, cl, iedg);

  bool pcurveRebuilt = false;

  while (!Curv2d.IsNull())
  {

    bool                                     SameSurf = false;
    NCollection_List<TopoDS_Shape>::Iterator itFac;

    for (itFac.Initialize(LmapFac); itFac.More(); itFac.Next())
    {
      const TopoDS_Shape&       face = itFac.Value();
      occ::handle<Geom_Surface> S    = BRep_Tool::Surface(TopoDS::Face(face), locbid);
      if (S == Surf)
      {
        SameSurf = true;
        break;
      }
    }

    if (SameSurf)
    {

      BRep_Tool::Range(theNewEdge, ef, el);

      TopoDS_Edge aFEdge = theOldEdge;
      aFEdge.Orientation(TopAbs_FORWARD);

      BRep_Tool::CurveOnSurface(aFEdge, Curv2d, Surf, loc, cf, cl, iedg);
      if (BRep_Tool::IsClosed(theOldEdge, Surf, loc))
      {
        aFEdge.Reverse();
        TopoDS_Face aFFace = TopoDS::Face(itFac.Value());
        aFFace.Orientation(TopAbs_FORWARD);
        occ::handle<Geom2d_Curve> Curv2dR = BRep_Tool::CurveOnSurface(aFEdge, aFFace, cf, cl);
        if (Curv2d->DynamicType() == STANDARD_TYPE(Geom2d_TrimmedCurve))
          Curv2d = occ::down_cast<Geom2d_TrimmedCurve>(Curv2d)->BasisCurve();
        if (Curv2dR->DynamicType() == STANDARD_TYPE(Geom2d_TrimmedCurve))
          Curv2dR = occ::down_cast<Geom2d_TrimmedCurve>(Curv2dR)->BasisCurve();

        B.UpdateEdge(theNewEdge, Curv2d, Curv2dR, Surf, loc, BRep_Tool::Tolerance(theNewEdge));
      }
      else
      {

        if (Curv2d->DynamicType() == STANDARD_TYPE(Geom2d_TrimmedCurve))
          Curv2d = occ::down_cast<Geom2d_TrimmedCurve>(Curv2d)->BasisCurve();
        double f, l;
        f = Curv2d->FirstParameter();
        l = Curv2d->LastParameter();
        if (l - f + 2. * Epsilon(l - f) < el - ef)
        {
          occ::handle<Geom2d_BoundedCurve> bcurve = occ::down_cast<Geom2d_BoundedCurve>(Curv2d);
          if (bcurve.IsNull())
            bcurve = new Geom2d_TrimmedCurve(Curv2d, cf, cl);
          Geom2dConvert_CompCurveToBSplineCurve    Concat(bcurve);
          NCollection_List<TopoDS_Shape>::Iterator iter(theLstEdg);
          iter.Next();
          for (; iter.More(); iter.Next())
          {
            const TopoDS_Edge&        E = TopoDS::Edge(iter.Value());
            double                    first, last;
            occ::handle<Geom2d_Curve> C = BRep_Tool::CurveOnSurface(E, Surf, loc, first, last);
            occ::handle<Geom2d_BoundedCurve> BC = occ::down_cast<Geom2d_BoundedCurve>(C);
            if (BC.IsNull())
              BC = new Geom2d_TrimmedCurve(C, first, last);
            if (!Concat.Add(BC, Precision::PConfusion()))

              return false;
          }
          Curv2d = Concat.BSplineCurve();

          double first = Curv2d->FirstParameter();
          double last  = Curv2d->LastParameter();
          if (std::abs(first - ef) > Precision::PConfusion()
              || std::abs(last - el) > Precision::PConfusion())
          {
            occ::handle<Geom2d_BSplineCurve> bc = occ::down_cast<Geom2d_BSplineCurve>(Curv2d);
            NCollection_Array1<double>       Knots(1, bc->NbKnots());
            bc->Knots(Knots);
            BSplCLib::Reparametrize(ef, el, Knots);
            bc->SetKnots(Knots);
          }
          pcurveRebuilt = true;
        }

        B.UpdateEdge(theNewEdge, Curv2d, Surf, loc, BRep_Tool::Tolerance(theNewEdge));
      }

      if (theOldEdge.Orientation() == TopAbs_REVERSED)
      {
        B.Range(theNewEdge, cl - el + ef, cl);
      }
      else
      {
        B.Range(theNewEdge, cf, cf + el - ef);
      }
    }

    iedg++;
    BRep_Tool::CurveOnSurface(theOldEdge, Curv2d, Surf, loc, cf, cl, iedg);
  }

  if (pcurveRebuilt)
  {

    B.SameParameter(theNewEdge, false);
    BRepLib::SameParameter(theNewEdge, BRep_Tool::Tolerance(theNewEdge));
  }

  return true;
}
