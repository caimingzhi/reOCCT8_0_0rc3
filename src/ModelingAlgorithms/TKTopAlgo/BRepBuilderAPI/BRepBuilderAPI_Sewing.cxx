#define TEST 1

#include <Bnd_Box2d.hpp>
#include <BndLib_Add2dCurve.hpp>
#include <BndLib_Add3dCurve.hpp>
#include <BRep_Builder.hpp>
#include <BRep_PointRepresentation.hpp>
#include <NCollection_List.hpp>
#include <BRep_PointOnCurve.hpp>
#include <BRep_Tool.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_TVertex.hpp>
#include <BRepBuilderAPI_BndBoxTreeSelector.hpp>
#include <BRepBuilderAPI_VertexInspector.hpp>
#include <BRepBuilderAPI_Sewing.hpp>
#include <BRepLib.hpp>
#include <BRepTools.hpp>
#include <BRepTools_Quilt.hpp>
#include <BRepTools_ReShape.hpp>
#include <Extrema_ExtPC.hpp>
#include <GCPnts_AbscissaPoint.hpp>
#include <GCPnts_UniformAbscissa.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_OffsetSurface.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomLib.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Message_ProgressScope.hpp>
#include <NCollection_UBTreeFiller.hpp>
#include <Precision.hpp>
#include <Standard_Failure.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array2.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>
#include <TopAbs.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <utility>

IMPLEMENT_STANDARD_RTTIEXT(BRepBuilderAPI_Sewing, Standard_Transient)

occ::handle<Geom2d_Curve> BRepBuilderAPI_Sewing::SameRange(
  const occ::handle<Geom2d_Curve>& CurvePtr,
  const double                     FirstOnCurve,
  const double                     LastOnCurve,
  const double                     RequestedFirst,
  const double                     RequestedLast) const
{
  occ::handle<Geom2d_Curve> NewCurvePtr;
  try
  {

    GeomLib::SameRange(Precision::PConfusion(),
                       CurvePtr,
                       FirstOnCurve,
                       LastOnCurve,
                       RequestedFirst,
                       RequestedLast,
                       NewCurvePtr);
  }
  catch (Standard_Failure const& anException)
  {
#ifdef OCCT_DEBUG
    std::cout << "Exception in BRepBuilderAPI_Sewing::SameRange: ";
    anException.Print(std::cout);
    std::cout << std::endl;
#endif
    (void)anException;
  }
  return NewCurvePtr;
}

TopoDS_Face BRepBuilderAPI_Sewing::WhichFace(const TopoDS_Edge& theEdg, const int index) const
{
  TopoDS_Shape bound = theEdg;
  if (mySectionBound.IsBound(bound))
    bound = mySectionBound(bound);
  if (myBoundFaces.Contains(bound))
  {
    int                                      i = 1;
    NCollection_List<TopoDS_Shape>::Iterator itf(myBoundFaces.FindFromKey(bound));
    for (; itf.More(); itf.Next(), i++)
      if (i == index)
        return TopoDS::Face(itf.Value());
  }
  return TopoDS_Face();
}

static bool IsClosedShape(const TopoDS_Shape& theshape,
                          const TopoDS_Shape& v1,
                          const TopoDS_Shape& v2)
{
  double          TotLength = 0.0;
  TopExp_Explorer aexp;
  for (aexp.Init(theshape, TopAbs_EDGE); aexp.More(); aexp.Next())
  {
    TopoDS_Edge aedge = TopoDS::Edge(aexp.Current());
    if (aedge.IsNull())
      continue;
    TopoDS_Vertex ve1, ve2;
    TopExp::Vertices(aedge, ve1, ve2);
    if (!ve1.IsSame(v1) && !ve1.IsSame(v2))
      continue;
    if (BRep_Tool::Degenerated(aedge))
      continue;
    double                  first, last;
    occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(TopoDS::Edge(aedge), first, last);
    if (!c3d.IsNull())
    {
      GeomAdaptor_Curve cAdapt(c3d);
      double            length = GCPnts_AbscissaPoint::Length(cAdapt, first, last);
      TotLength += length;
      if (ve2.IsSame(v1) || ve2.IsSame(v2))
        break;
    }
  }
  if (TotLength > 0.0)
  {
    gp_Pnt p1 = BRep_Tool::Pnt(TopoDS::Vertex(v1));
    gp_Pnt p2 = BRep_Tool::Pnt(TopoDS::Vertex(v2));
    return (p1.Distance(p2) < TotLength / (1.2 * M_PI));
  }
  return false;
}

static bool IsClosedByIsos(const occ::handle<Geom_Surface>& thesurf,
                           const occ::handle<Geom2d_Curve>& acrv2d,
                           const double                     f2d,
                           const double                     l2d,
                           const bool                       isUIsos)
{
  bool isClosed = false;

  gp_Pnt2d                psurf1 = (acrv2d->IsPeriodic() ? acrv2d->Value(f2d)
                                                         : acrv2d->Value(std::max(f2d, acrv2d->FirstParameter())));
  gp_Pnt2d                psurf2 = (acrv2d->IsPeriodic() ? acrv2d->Value(l2d)
                                                         : acrv2d->Value(std::min(l2d, acrv2d->LastParameter())));
  occ::handle<Geom_Curve> aCrv1;
  occ::handle<Geom_Curve> aCrv2;
  if (isUIsos)
  {
    aCrv1 = thesurf->UIso(psurf1.X());
    aCrv2 = thesurf->UIso(psurf2.X());
  }
  else
  {
    aCrv1 = thesurf->VIso(psurf1.Y());
    aCrv2 = thesurf->VIso(psurf2.Y());
  }
  gp_Pnt p11, p1m, p12, p21, p2m, p22;
  double af1 = aCrv1->FirstParameter();
  double al1 = aCrv1->LastParameter();
  double af2 = aCrv2->FirstParameter();
  double al2 = aCrv2->LastParameter();
  aCrv1->D0(af1, p11);
  aCrv1->D0((af1 + al1) * 0.5, p1m);
  aCrv1->D0(al1, p12);
  aCrv2->D0(af2, p21);
  aCrv2->D0((af2 + al2) * 0.5, p2m);
  aCrv2->D0(al2, p22);
  isClosed = (((p11.XYZ() - p12.XYZ()).Modulus()
               < (p11.XYZ() - p1m.XYZ()).Modulus() - Precision::Confusion())
              && ((p21.XYZ() - p22.XYZ()).Modulus()
                  < (p21.XYZ() - p2m.XYZ()).Modulus() - Precision::Confusion()));
  return isClosed;
}

bool BRepBuilderAPI_Sewing::IsUClosedSurface(const occ::handle<Geom_Surface>& surf,
                                             const TopoDS_Shape&              theEdge,
                                             const TopLoc_Location&           theloc) const
{
  occ::handle<Geom_Surface> tmpsurf = surf;
  if (tmpsurf->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
    tmpsurf = occ::down_cast<Geom_RectangularTrimmedSurface>(surf)->BasisSurface();
  else if (tmpsurf->IsKind(STANDARD_TYPE(Geom_OffsetSurface)))
    tmpsurf = occ::down_cast<Geom_OffsetSurface>(surf)->BasisSurface();
  else
  {
    bool isClosed = tmpsurf->IsUClosed();
    if (!isClosed)
    {
      double                    f2d, l2d;
      occ::handle<Geom2d_Curve> acrv2d =
        BRep_Tool::CurveOnSurface(TopoDS::Edge(theEdge), surf, theloc, f2d, l2d);
      if (!acrv2d.IsNull())
        isClosed = IsClosedByIsos(tmpsurf, acrv2d, f2d, l2d, false);
    }
    return isClosed;
  }
  return IsUClosedSurface(tmpsurf, theEdge, theloc);
}

bool BRepBuilderAPI_Sewing::IsVClosedSurface(const occ::handle<Geom_Surface>& surf,
                                             const TopoDS_Shape&              theEdge,
                                             const TopLoc_Location&           theloc) const
{
  occ::handle<Geom_Surface> tmpsurf = surf;
  if (tmpsurf->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
    tmpsurf = occ::down_cast<Geom_RectangularTrimmedSurface>(surf)->BasisSurface();
  else if (tmpsurf->IsKind(STANDARD_TYPE(Geom_OffsetSurface)))
    tmpsurf = occ::down_cast<Geom_OffsetSurface>(surf)->BasisSurface();
  else
  {
    bool isClosed = tmpsurf->IsVClosed();
    if (!isClosed)
    {
      double                    f2d, l2d;
      occ::handle<Geom2d_Curve> acrv2d =
        BRep_Tool::CurveOnSurface(TopoDS::Edge(theEdge), surf, theloc, f2d, l2d);
      if (!acrv2d.IsNull())
        isClosed = IsClosedByIsos(tmpsurf, acrv2d, f2d, l2d, true);
    }
    return isClosed;
  }
  return IsVClosedSurface(tmpsurf, theEdge, theloc);
}

void BRepBuilderAPI_Sewing::SameParameter(const TopoDS_Edge& edge) const
{
  try
  {

    BRepLib::SameParameter(edge);
  }
  catch (Standard_Failure const& anException)
  {
#ifdef OCCT_DEBUG
    std::cout << "Exception in BRepBuilderAPI_Sewing::SameParameter: ";
    anException.Print(std::cout);
    std::cout << std::endl;
#endif
    (void)anException;
  }
}

TopoDS_Edge BRepBuilderAPI_Sewing::SameParameterEdge(
  const TopoDS_Shape&                                     edge,
  const NCollection_Sequence<TopoDS_Shape>&               seqEdges,
  const NCollection_Sequence<bool>&                       seqForward,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& mapMerged,
  const occ::handle<BRepTools_ReShape>&                   locReShape)
{

  TopoDS_Shape aTmpShape = myReShape->Apply(edge);
  TopoDS_Edge  Edge1     = TopoDS::Edge(aTmpShape);
  aTmpShape              = locReShape->Apply(Edge1);
  if (locReShape != myReShape)
    Edge1 = TopoDS::Edge(aTmpShape);
  bool isDone = false;

  NCollection_List<TopoDS_Shape>                         listFaces1;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> MergedFaces;

  if (mySewing)
  {

    TopoDS_Shape bnd1 = edge;
    if (mySectionBound.IsBound(bnd1))
      bnd1 = mySectionBound(bnd1);
    if (myBoundFaces.Contains(bnd1))
    {
      NCollection_List<TopoDS_Shape>::Iterator itf(myBoundFaces.FindFromKey(bnd1));
      for (; itf.More(); itf.Next())
        if (MergedFaces.Add(itf.Value()))
          listFaces1.Append(itf.Value());
    }
  }
  else
  {

    TopoDS_Vertex V1, V2;
    TopExp::Vertices(Edge1, V1, V2);
    if (myVertexNode.Contains(V1))
      V1 = TopoDS::Vertex(myVertexNode.FindFromKey(V1));
    if (myVertexNode.Contains(V2))
      V2 = TopoDS::Vertex(myVertexNode.FindFromKey(V2));

    TopoDS_Edge NewEdge = Edge1;
    NewEdge.EmptyCopy();

    BRep_Builder aBuilder;
    TopoDS_Shape anEdge = NewEdge.Oriented(TopAbs_FORWARD);
    aBuilder.Add(anEdge, V1.Oriented(TopAbs_FORWARD));
    aBuilder.Add(anEdge, V2.Oriented(TopAbs_REVERSED));

    Edge1 = NewEdge;
  }

  bool isForward = true;

  for (int i = 1; i <= seqEdges.Length(); i++)
  {

    const TopoDS_Shape& oedge2 = seqEdges(i);

    if (mySewing)
    {

      aTmpShape         = myReShape->Apply(oedge2);
      TopoDS_Edge Edge2 = TopoDS::Edge(aTmpShape);
      aTmpShape         = locReShape->Apply(Edge2);
      if (locReShape != myReShape)
        Edge2 = TopoDS::Edge(aTmpShape);

      bool Orientation = seqForward(i);
      if (!isForward)
        Orientation = !Orientation;

      TopoDS_Shape bnd2 = oedge2;
      if (mySectionBound.IsBound(bnd2))
        bnd2 = mySectionBound(bnd2);
      if (!myBoundFaces.Contains(bnd2))
        continue;
      const NCollection_List<TopoDS_Shape>& listFaces2 = myBoundFaces.FindFromKey(bnd2);

      int         whichSec = 1;
      TopoDS_Edge NewEdge =
        SameParameterEdge(Edge1, Edge2, listFaces1, listFaces2, Orientation, whichSec);
      if (NewEdge.IsNull())
        continue;

      NCollection_List<TopoDS_Shape>::Iterator itf(listFaces2);
      for (; itf.More(); itf.Next())
        if (MergedFaces.Add(itf.Value()))
          listFaces1.Append(itf.Value());

      if (!Orientation && whichSec != 1)
        isForward = !isForward;
      Edge1 = NewEdge;
    }

    mapMerged.Add(oedge2);
    isDone = true;

    if (!myNonmanifold)
      break;
  }

  if (isDone)
  {

    Edge1.Orientation(isForward ? TopAbs_FORWARD : TopAbs_REVERSED);
  }
  else
    Edge1.Nullify();

  return Edge1;
}

static bool findNMVertices(const TopoDS_Edge&                  theEdge,
                           NCollection_Sequence<TopoDS_Shape>& theSeqNMVert,
                           NCollection_Sequence<double>&       theSeqPars)
{
  TopoDS_Iterator aItV(theEdge, false);
  for (; aItV.More(); aItV.Next())
  {
    if (aItV.Value().Orientation() == TopAbs_INTERNAL
        || aItV.Value().Orientation() == TopAbs_EXTERNAL)
      theSeqNMVert.Append(aItV.Value());
  }
  int nbV = theSeqNMVert.Length();
  if (!nbV)
    return false;
  double                  first, last;
  occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(theEdge, first, last);
  GeomAdaptor_Curve       GAC(c3d);
  Extrema_ExtPC           locProj;
  locProj.Initialize(GAC, first, last);
  gp_Pnt pfirst = GAC.Value(first), plast = GAC.Value(last);

  for (int i = 1; i <= nbV; i++)
  {
    TopoDS_Vertex aV = TopoDS::Vertex(theSeqNMVert.Value(i));
    gp_Pnt        pt = BRep_Tool::Pnt(aV);

    double distF2 = pfirst.SquareDistance(pt);
    double distL2 = plast.SquareDistance(pt);
    double apar   = (distF2 > distL2 ? last : first);

    locProj.Perform(pt);
    if (locProj.IsDone() && locProj.NbExt() > 0)
    {
      double dist2Min = std::min(distF2, distL2);
      int    ind, indMin = 0;
      for (ind = 1; ind <= locProj.NbExt(); ind++)
      {
        double dProj2 = locProj.SquareDistance(ind);
        if (dProj2 < dist2Min)
        {
          indMin   = ind;
          dist2Min = dProj2;
        }
      }
      if (indMin)
        apar = locProj.Point(indMin).Parameter();

      theSeqPars.Append(apar);
    }
  }
  return true;
}

static void ComputeToleranceVertex(TopoDS_Vertex theV1, TopoDS_Vertex theV2, TopoDS_Vertex& theNewV)
{
  int           m, n;
  double        aR[2], dR, aD, aEps;
  TopoDS_Vertex aV[2];
  gp_Pnt        aP[2];
  BRep_Builder  aBB;

  aEps  = RealEpsilon();
  aV[0] = std::move(theV1);
  aV[1] = std::move(theV2);
  for (m = 0; m < 2; ++m)
  {
    aP[m] = BRep_Tool::Pnt(aV[m]);
    aR[m] = BRep_Tool::Tolerance(aV[m]);
  }

  m = 0;
  n = 1;
  if (aR[0] < aR[1])
  {
    m = 1;
    n = 0;
  }

  dR = aR[m] - aR[n];
  gp_Vec aVD(aP[m], aP[n]);
  aD = aVD.Magnitude();

  if (aD <= dR || aD < aEps)
  {
    aBB.MakeVertex(theNewV, aP[m], aR[m]);
  }
  else
  {
    double aRr;
    gp_XYZ aXYZr;
    gp_Pnt aPr;

    aRr   = 0.5 * (aR[m] + aR[n] + aD);
    aXYZr = 0.5 * (aP[m].XYZ() + aP[n].XYZ() - aVD.XYZ() * (dR / aD));
    aPr.SetXYZ(aXYZr);

    aBB.MakeVertex(theNewV, aPr, aRr);
  }
  return;
}

static void ComputeToleranceVertex(TopoDS_Vertex  theV1,
                                   TopoDS_Vertex  theV2,
                                   TopoDS_Vertex  theV3,
                                   TopoDS_Vertex& theNewV)
{
  double        aDi, aDmax;
  gp_Pnt        aCenter;
  gp_Pnt        aP[3];
  double        aR[3];
  TopoDS_Vertex aV[3];
  gp_XYZ        aXYZ(0., 0., 0.);
  aV[0] = std::move(theV1);
  aV[1] = std::move(theV2);
  aV[2] = std::move(theV3);
  for (int i = 0; i < 3; ++i)
  {
    aP[i] = BRep_Tool::Pnt(aV[i]);
    aR[i] = BRep_Tool::Tolerance(aV[i]);
    aXYZ  = aXYZ + aP[i].XYZ();
  }

  aXYZ.Divide(3.0);
  aCenter.SetXYZ(aXYZ);

  aDmax = -1.;
  for (int i = 0; i < 3; ++i)
  {
    aDi = aCenter.Distance(aP[i]);
    aDi += aR[i];
    if (aDi > aDmax)
      aDmax = aDi;
  }

  BRep_Builder aBB;
  aBB.MakeVertex(theNewV, aCenter, aDmax);
  return;
}

TopoDS_Edge BRepBuilderAPI_Sewing::SameParameterEdge(
  const TopoDS_Edge&                    edgeFirst,
  const TopoDS_Edge&                    edgeLast,
  const NCollection_List<TopoDS_Shape>& listFacesFirst,
  const NCollection_List<TopoDS_Shape>& listFacesLast,
  const bool                            secForward,
  int&                                  whichSec,
  const bool                            firstCall)
{

  if (!listFacesFirst.Extent() || !listFacesLast.Extent())
    return TopoDS_Edge();

  TopoDS_Edge edge1, edge2;
  if (firstCall)
  {

    double                  f, l;
    occ::handle<Geom_Curve> c3d1 = BRep_Tool::Curve(TopoDS::Edge(edgeFirst), f, l);
    GeomAdaptor_Curve       cAdapt1(c3d1);
    double                  len1 = GCPnts_AbscissaPoint::Length(cAdapt1, f, l);
    occ::handle<Geom_Curve> c3d2 = BRep_Tool::Curve(TopoDS::Edge(edgeLast), f, l);
    GeomAdaptor_Curve       cAdapt2(c3d2);
    double                  len2 = GCPnts_AbscissaPoint::Length(cAdapt2, f, l);
    if (len1 < len2)
    {
      edge1    = edgeLast;
      edge2    = edgeFirst;
      whichSec = 2;
    }
    else
    {
      edge1    = edgeFirst;
      edge2    = edgeLast;
      whichSec = 1;
    }
  }
  else
  {
    if (whichSec == 1)
    {
      edge1    = edgeLast;
      edge2    = edgeFirst;
      whichSec = 2;
    }
    else
    {
      edge1    = edgeFirst;
      edge2    = edgeLast;
      whichSec = 1;
    }
  }

  double first, last;
  BRep_Tool::Range(edge1, first, last);
  BRep_Builder aBuilder;

  NCollection_Sequence<TopoDS_Shape> aSeqNMVert;
  NCollection_Sequence<double>       aSeqNMPars;
  findNMVertices(edge1, aSeqNMVert, aSeqNMPars);
  findNMVertices(edge2, aSeqNMVert, aSeqNMPars);

  TopoDS_Edge edge;
  aBuilder.MakeEdge(edge);
  edge.Orientation(edge1.Orientation());

  TopLoc_Location         loc3d;
  double                  first3d, last3d;
  occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(edge1, loc3d, first3d, last3d);
  if (!loc3d.IsIdentity())
  {
    c3d = occ::down_cast<Geom_Curve>(c3d->Copy());
    c3d->Transform(loc3d.Transformation());
  }
  aBuilder.UpdateEdge(edge, c3d, BRep_Tool::Tolerance(edge1));
  aBuilder.Range(edge, first, last);
  aBuilder.SameRange(edge, false);
  aBuilder.SameParameter(edge, false);

  {
    TopoDS_Vertex V1New, V2New;

    TopoDS_Vertex V11, V12, V21, V22;
    TopExp::Vertices(edge1, V11, V12);
    TopExp::Vertices(edge2, V21, V22);

    bool isClosed1 = V11.IsSame(V12);
    bool isClosed2 = V21.IsSame(V22);
    if (!isClosed1 && !isClosed2)
    {
      if (secForward)
      {
        if (V11.IsSame(V22) || V12.IsSame(V21))
          return TopoDS_Edge();
      }
      else
      {
        if (V11.IsSame(V21) || V12.IsSame(V22))
          return TopoDS_Edge();
      }
    }

    if (isClosed1 || isClosed2)
    {

      if (isClosed1 && isClosed2)
      {

        ComputeToleranceVertex(V11, V21, V1New);
      }
      else if (isClosed1)
      {

        ComputeToleranceVertex(V22, V21, V11, V1New);
      }
      else
      {

        ComputeToleranceVertex(V11, V12, V21, V1New);
      }
      V2New = V1New;
    }
    else
    {

      bool isOldFirst = (secForward ? V11.IsSame(V21) : V11.IsSame(V22));
      bool isOldLast  = (secForward ? V12.IsSame(V22) : V12.IsSame(V21));
      if (secForward)
      {

        if (!isOldFirst)
        {
          ComputeToleranceVertex(V11, V21, V1New);
        }
        if (!isOldLast)
        {
          ComputeToleranceVertex(V12, V22, V2New);
        }
      }
      else
      {
        if (!isOldFirst)
        {
          ComputeToleranceVertex(V11, V22, V1New);
        }
        if (!isOldLast)
        {
          ComputeToleranceVertex(V12, V21, V2New);
        }
      }
      if (isOldFirst)
        V1New = V11;

      if (isOldLast)
        V2New = V12;
    }

    TopoDS_Shape anEdge = edge.Oriented(TopAbs_FORWARD);

    TopoDS_Shape aLocalEdge = V1New.Oriented(TopAbs_FORWARD);

    aBuilder.Add(anEdge, aLocalEdge);
    aLocalEdge = V2New.Oriented(TopAbs_REVERSED);
    aBuilder.Add(anEdge, aLocalEdge);

    int k = 1;
    for (; k <= aSeqNMVert.Length(); k++)
      aBuilder.Add(anEdge, aSeqNMVert.Value(k));
  }

  TopLoc_Location           loc2;
  occ::handle<Geom_Surface> surf2;

  NCollection_List<TopoDS_Shape>::Iterator itf2;
  if (whichSec == 1)
    itf2.Initialize(listFacesLast);
  else
    itf2.Initialize(listFacesFirst);
  bool        isResEdge = false;
  TopoDS_Face fac2;
  for (; itf2.More(); itf2.Next())
  {
    occ::handle<Geom2d_Curve> c2d2, c2d21;
    double                    firstOld, lastOld;
    fac2 = TopoDS::Face(itf2.Value());

    surf2        = BRep_Tool::Surface(fac2, loc2);
    bool isSeam2 = ((IsUClosedSurface(surf2, edge2, loc2) || IsVClosedSurface(surf2, edge2, loc2))
                    && BRep_Tool::IsClosed(TopoDS::Edge(edge2), fac2));
    if (isSeam2)
    {
      if (!myNonmanifold)
        return TopoDS_Edge();
      TopoDS_Shape aTmpShape = edge2.Reversed();
      c2d21 = BRep_Tool::CurveOnSurface(TopoDS::Edge(aTmpShape), fac2, firstOld, lastOld);
    }
    c2d2 = BRep_Tool::CurveOnSurface(edge2, fac2, firstOld, lastOld);
    if (c2d2.IsNull() && c2d21.IsNull())
      continue;

    if (!c2d21.IsNull())
    {
      c2d21 = occ::down_cast<Geom2d_Curve>(c2d21->Copy());
      if (!secForward)
      {
        if (c2d21->IsKind(STANDARD_TYPE(Geom2d_Line)))
          c2d21 = new Geom2d_TrimmedCurve(c2d21, firstOld, lastOld);
        double first2d = firstOld;
        double last2d  = lastOld;
        firstOld       = c2d21->ReversedParameter(last2d);
        lastOld        = c2d21->ReversedParameter(first2d);
        c2d21->Reverse();
      }
      c2d21 = SameRange(c2d21, firstOld, lastOld, first, last);
    }

    c2d2 = occ::down_cast<Geom2d_Curve>(c2d2->Copy());

    if (!secForward)
    {
      if (c2d2->IsKind(STANDARD_TYPE(Geom2d_Line)))
        c2d2 = new Geom2d_TrimmedCurve(c2d2, firstOld, lastOld);
      double first2d = firstOld;
      double last2d  = lastOld;
      firstOld       = c2d2->ReversedParameter(last2d);
      lastOld        = c2d2->ReversedParameter(first2d);
      c2d2->Reverse();
    }

    c2d2 = SameRange(c2d2, firstOld, lastOld, first, last);
    if (c2d2.IsNull())
      continue;

    bool               isSeam = false;
    TopAbs_Orientation Ori    = TopAbs_FORWARD;

    NCollection_List<TopoDS_Shape>::Iterator itf1;
    if (whichSec == 1)
      itf1.Initialize(listFacesFirst);
    else
      itf1.Initialize(listFacesLast);
    for (; itf1.More() && !isSeam; itf1.Next())
    {
      occ::handle<Geom2d_Curve> c2d1, c2d11;
      const TopoDS_Face&        fac1 = TopoDS::Face(itf1.Value());

      TopLoc_Location           loc1;
      occ::handle<Geom_Surface> surf1 = BRep_Tool::Surface(fac1, loc1);

      double first2d, last2d;
      bool isSeam1 = ((IsUClosedSurface(surf1, edge1, loc1) || IsVClosedSurface(surf1, edge1, loc1))
                      && BRep_Tool::IsClosed(TopoDS::Edge(edge1), fac1));
      c2d1         = BRep_Tool::CurveOnSurface(edge1, fac1, first2d, last2d);
      Ori          = edge1.Orientation();
      if (fac1.Orientation() == TopAbs_REVERSED)
        Ori = TopAbs::Reverse(Ori);

      if (isSeam1)
      {
        if (!myNonmanifold)
          return TopoDS_Edge();
        TopoDS_Shape aTmpShape = edge1.Reversed();
        c2d11 = BRep_Tool::CurveOnSurface(TopoDS::Edge(aTmpShape), fac1, first2d, last2d);

        if (Ori == TopAbs_FORWARD)
          aBuilder.UpdateEdge(edge, c2d1, c2d11, fac1, 0);
        else
          aBuilder.UpdateEdge(edge, c2d11, c2d1, fac1, 0);
      }
      else
        aBuilder.UpdateEdge(edge, c2d1, fac1, 0);

      if (c2d1.IsNull() && c2d11.IsNull())
        continue;

      if (surf2 == surf1)
      {

        if (!loc2.IsDifferent(loc1))
        {
          bool uclosed = IsUClosedSurface(surf2, edge2, loc2);
          bool vclosed = IsVClosedSurface(surf2, edge2, loc2);
          if (uclosed || vclosed)
          {
            double pf = c2d1->FirstParameter();

            gp_Pnt2d p1n   = c2d1->Value(std::max(first, pf));
            gp_Pnt2d p21n  = c2d2->Value(std::max(first, c2d2->FirstParameter()));
            gp_Pnt2d p22n  = c2d2->Value(std::min(last, c2d2->LastParameter()));
            double   aDist = std::min(p1n.Distance(p21n), p1n.Distance(p22n));
            double   U1, U2, V1, V2;
            surf2->Bounds(U1, U2, V1, V2);
            isSeam = ((uclosed && aDist > 0.75 * (fabs(U2 - U1)))
                      || (vclosed && aDist > 0.75 * (fabs(V2 - V1))));
            if (!isSeam && BRep_Tool::IsClosed(TopoDS::Edge(edge), fac1))
              continue;
          }
        }
      }

      isResEdge = true;
      if (isSeam)
      {
        if (Ori == TopAbs_FORWARD)
          aBuilder.UpdateEdge(edge, c2d1, c2d2, surf2, loc2, Precision::Confusion());
        else
          aBuilder.UpdateEdge(edge, c2d2, c2d1, surf2, loc2, Precision::Confusion());
      }
      else if (isSeam2)
      {
        TopAbs_Orientation InitOri = edge2.Orientation();
        TopAbs_Orientation SecOri  = edge.Orientation();
        if (fac2.Orientation() == TopAbs_REVERSED)
        {

          InitOri = TopAbs::Reverse(InitOri);
          SecOri  = TopAbs::Reverse(SecOri);
        }
        if (!secForward)
          InitOri = TopAbs::Reverse(InitOri);

        if (InitOri == TopAbs_FORWARD)
          aBuilder.UpdateEdge(edge, c2d2, c2d21, surf2, loc2, Precision::Confusion());
        else
          aBuilder.UpdateEdge(edge, c2d21, c2d2, surf2, loc2, Precision::Confusion());
      }
      else
      {
        aBuilder.UpdateEdge(edge, c2d2, surf2, loc2, Precision::Confusion());
      }
    }
  }
  double tolReached = Precision::Infinite();
  bool   isSamePar  = false;
  try
  {
    if (isResEdge)
      SameParameter(edge);

    if (BRep_Tool::SameParameter(edge))
    {
      isSamePar  = true;
      tolReached = BRep_Tool::Tolerance(edge);
    }
  }

  catch (Standard_Failure const&)
  {
    isSamePar = false;
  }

  if (firstCall && (!isResEdge || !isSamePar || tolReached > myTolerance))
  {
    int whichSecn = whichSec;

    bool        second_ok = false;
    TopoDS_Edge s_edge    = SameParameterEdge(edgeFirst,
                                           edgeLast,
                                           listFacesFirst,
                                           listFacesLast,
                                           secForward,
                                           whichSecn,
                                           false);
    if (!s_edge.IsNull())
    {
      double tolReached_2 = BRep_Tool::Tolerance(s_edge);
      second_ok           = (BRep_Tool::SameParameter(s_edge) && tolReached_2 < tolReached);
      if (second_ok)
      {
        edge       = s_edge;
        whichSec   = whichSecn;
        tolReached = tolReached_2;
      }
    }

    if (!second_ok && !edge.IsNull())
    {

      GeomAdaptor_Curve c3dAdapt(c3d);

      int                        i, j, nbp = 23;
      double                     deltaT = (last3d - first3d) / (nbp - 1);
      NCollection_Array1<gp_Pnt> c3dpnt(1, nbp);
      for (i = 1; i <= nbp; i++)
        c3dpnt(i) = c3dAdapt.Value(first3d + (i - 1) * deltaT);

      double dist = 0., maxTol = -1.0;
      bool   more = true;

      for (j = 1; more; j++)
      {
        occ::handle<Geom2d_Curve> c2d2;
        BRep_Tool::CurveOnSurface(edge, c2d2, surf2, loc2, first, last, j);

        more = !c2d2.IsNull();
        if (more)
        {
          occ::handle<Geom_Surface> aS = surf2;
          if (!loc2.IsIdentity())
            aS = occ::down_cast<Geom_Surface>(surf2->Transformed(loc2));

          double dist2 = 0.;
          deltaT       = (last - first) / (nbp - 1);
          for (i = 1; i <= nbp; i++)
          {
            gp_Pnt2d aP2d = c2d2->Value(first + (i - 1) * deltaT);
            gp_Pnt   aP2(0., 0., 0.);
            aS->D0(aP2d.X(), aP2d.Y(), aP2);
            gp_Pnt aP1 = c3dpnt(i);
            dist       = aP2.SquareDistance(aP1);
            if (dist > dist2)
              dist2 = dist;
          }
          maxTol = std::max(sqrt(dist2) * (1. + 1e-7), Precision::Confusion());
        }
      }
      if (maxTol >= 0. && maxTol < tolReached)
      {
        if (tolReached > MaxTolerance())
        {

          static_cast<BRep_TEdge*>(edge.TShape().get())->Tolerance(maxTol);
        }
        else
        {

          aBuilder.UpdateEdge(edge, maxTol);
        }
      }
      aBuilder.SameParameter(edge, true);
    }
  }

  double tolEdge1 = BRep_Tool::Tolerance(edge);
  if (tolEdge1 > MaxTolerance())
    edge.Nullify();
  return edge;
}

void BRepBuilderAPI_Sewing::EvaluateAngulars(NCollection_Sequence<TopoDS_Shape>& sequenceSec,
                                             NCollection_Array1<bool>&           secForward,
                                             NCollection_Array1<double>&         tabAng,
                                             const int                           indRef) const
{
  tabAng.Init(-1.0);

  int i, j, npt = 4, lengSec = sequenceSec.Length();

  TopoDS_Edge                edge;
  TopoDS_Face                face;
  TopLoc_Location            loc;
  double                     first, last;
  occ::handle<Geom_Curve>    c3d;
  occ::handle<Geom2d_Curve>  c2d;
  occ::handle<Geom_Surface>  surf;
  NCollection_Array1<gp_Vec> normRef(1, npt);

  for (i = indRef; i <= lengSec; i++)
  {

    edge = TopoDS::Edge(sequenceSec(i));

    TopoDS_Shape bnd = edge;
    if (mySectionBound.IsBound(bnd))
      bnd = mySectionBound(bnd);
    if (myBoundFaces.Contains(bnd))
    {
      face = TopoDS::Face(myBoundFaces.FindFromKey(bnd).First());
      surf = BRep_Tool::Surface(face, loc);
      if (!loc.IsIdentity())
      {
        surf = occ::down_cast<Geom_Surface>(surf->Copy());
        surf->Transform(loc.Transformation());
      }
      c2d = BRep_Tool::CurveOnSurface(edge, face, first, last);
    }
    else if (i == indRef)
      return;
    else
      continue;

    c3d = BRep_Tool::Curve(edge, loc, first, last);
    if (!loc.IsIdentity())
    {
      c3d = occ::down_cast<Geom_Curve>(c3d->Copy());
      c3d->Transform(loc.Transformation());
    }

    GeomAdaptor_Curve      adapt(c3d);
    GCPnts_UniformAbscissa uniAbs(adapt, npt, first, last);

    double cumulateAngular = 0.0;
    int    nbComputedAngle = 0;

    for (j = 1; j <= npt; j++)
    {
      gp_Pnt2d P;
      c2d->D0(uniAbs.Parameter((secForward(i) || i == indRef) ? j : npt - j + 1), P);
      gp_Vec w1, w2;
      gp_Pnt unused;
      surf->D1(P.X(), P.Y(), unused, w1, w2);
      gp_Vec n = w1 ^ w2;
      if (i == indRef)
        normRef(j) = n;
      else if ((n.Magnitude() > gp::Resolution()) && (normRef(j).Magnitude() > gp::Resolution()))
      {
        nbComputedAngle++;
        double angular = n.Angle(normRef(j));
        if (angular > M_PI / 2.)
          angular = M_PI - angular;
        cumulateAngular += angular;
      }
    }

    if (nbComputedAngle)
      tabAng(i) = cumulateAngular / ((double)nbComputedAngle);
  }
}

void BRepBuilderAPI_Sewing::EvaluateDistances(NCollection_Sequence<TopoDS_Shape>& sequenceSec,
                                              NCollection_Array1<bool>&           secForward,
                                              NCollection_Array1<double>&         tabDst,
                                              NCollection_Array1<double>&         arrLen,
                                              NCollection_Array1<double>&         tabMinDist,
                                              const int                           indRef) const
{
  secForward.Init(true);
  tabDst.Init(-1.0);
  arrLen.Init(0.);
  tabMinDist.Init(Precision::Infinite());
  const int                  npt = 8;
  NCollection_Array1<gp_Pnt> ptsRef(1, npt), ptsSec(1, npt);

  int                          i, j, lengSec = sequenceSec.Length();
  NCollection_Sequence<gp_Pnt> seqSec;

  occ::handle<Geom_Curve> c3dRef;
  double                  firstRef = 0., lastRef = 0.;

  for (i = indRef; i <= lengSec; i++)
  {

    const TopoDS_Edge& sec = TopoDS::Edge(sequenceSec(i));

    TopLoc_Location         loc;
    double                  first, last;
    occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(sec, loc, first, last);
    if (c3d.IsNull())
      continue;
    if (!loc.IsIdentity())
    {
      c3d = occ::down_cast<Geom_Curve>(c3d->Copy());
      c3d->Transform(loc.Transformation());
    }

    if (i == indRef)
    {
      c3dRef   = c3d;
      firstRef = first;
      lastRef  = last;
    }

    double dist = Precision::Infinite(), distFor = -1.0, distRev = -1.0;
    double aMinDist = Precision::Infinite();

    double T, deltaT = (last - first) / (npt - 1);
    double aLenSec2 = 0.;

    int nbFound = 0;
    for (j = 1; j <= npt; j++)
    {

      if (j == 1)
        T = first;
      else if (j == npt)
        T = last;
      else
        T = first + (j - 1) * deltaT;

      gp_Pnt pt = c3d->Value(T);

      if (i == indRef)
      {
        ptsRef(j) = pt;
        if (j > 1)
          aLenSec2 += pt.SquareDistance(ptsRef(j - 1));
      }
      else
      {
        ptsSec(j) = pt;

        if (j > 1)
          aLenSec2 += pt.SquareDistance(ptsSec(j - 1));

        dist = pt.Distance(ptsRef(j));
        if (aMinDist > dist)
          aMinDist = dist;
        if (distFor < dist)
          distFor = dist;
        dist = pt.Distance(ptsRef(npt - j + 1));

        if (aMinDist > dist)
          aMinDist = dist;
        if (distRev < dist)
          distRev = dist;

        const gp_Pnt& p11 = ptsRef(1);
        const gp_Pnt& p12 = ptsRef(npt);
        const gp_Vec  aVec1(pt, p11);
        const gp_Vec  aVec2(pt, p12);
        const gp_Vec  aVecRef(p11, p12);
        if ((aVecRef * aVec1) * (aVecRef * aVec2) < 0.)
          nbFound++;
      }
    }

    double aLenSec = sqrt(aLenSec2);

    arrLen.SetValue(i, aLenSec);

    bool isForward = (distFor < distRev);
    secForward(i)  = isForward;

    dist = (isForward ? distFor : distRev);
    if (i == indRef || (dist < myTolerance && nbFound >= npt * 0.5))
    {
      tabDst(i)     = dist;
      tabMinDist(i) = aMinDist;
    }
    else
    {
      nbFound = 0, aMinDist = Precision::Infinite(), dist = -1;
      NCollection_Array1<gp_Pnt> arrProj(1, npt);
      NCollection_Array1<double> arrDist(1, npt), arrPara(1, npt);
      if (arrLen(indRef) >= arrLen(i))
        ProjectPointsOnCurve(ptsSec, c3dRef, firstRef, lastRef, arrDist, arrPara, arrProj, false);
      else
        ProjectPointsOnCurve(ptsRef, c3d, first, last, arrDist, arrPara, arrProj, false);
      for (j = 1; j <= npt; j++)
      {
        if (arrDist(j) < 0.)
          continue;
        if (dist < arrDist(j))
          dist = arrDist(j);
        if (aMinDist > arrDist(j))
          aMinDist = arrDist(j);
        nbFound++;
      }
      if (nbFound > 1)
      {
        tabDst(i)     = dist;
        tabMinDist(i) = aMinDist;
      }
    }
  }
}

bool BRepBuilderAPI_Sewing::IsMergedClosed(const TopoDS_Edge& Edge1,
                                           const TopoDS_Edge& Edge2,
                                           const TopoDS_Face& face) const
{

  TopLoc_Location           loc;
  occ::handle<Geom_Surface> surf      = BRep_Tool::Surface(face, loc);
  bool                      isUClosed = IsUClosedSurface(surf, Edge1, loc);
  bool                      isVClosed = IsVClosedSurface(surf, Edge1, loc);
  if (!isUClosed && !isVClosed)
    return false;

  double                    first2d1, last2d1, first2d2, last2d2;
  occ::handle<Geom2d_Curve> C2d1 = BRep_Tool::CurveOnSurface(Edge1, face, first2d1, last2d1);
  occ::handle<Geom2d_Curve> C2d2 = BRep_Tool::CurveOnSurface(Edge2, face, first2d2, last2d2);
  if (C2d1.IsNull() || C2d2.IsNull())
    return false;

  int    isULongC1, isULongC2, isVLongC1, isVLongC2;
  double SUmin, SUmax, SVmin, SVmax;
  double C1Umin, C1Vmin, C1Umax, C1Vmax;
  double C2Umin, C2Vmin, C2Umax, C2Vmax;
  {
    Bnd_Box2d           B1, B2;
    Geom2dAdaptor_Curve aC2d1(C2d1), aC2d2(C2d2);
    BndLib_Add2dCurve::Add(aC2d1, first2d1, last2d1, Precision::PConfusion(), B1);
    BndLib_Add2dCurve::Add(aC2d2, first2d2, last2d2, Precision::PConfusion(), B2);
    B1.Get(C1Umin, C1Vmin, C1Umax, C1Vmax);
    B2.Get(C2Umin, C2Vmin, C2Umax, C2Vmax);
    double du, dv;
    du        = (C1Umax - C1Umin);
    dv        = (C1Vmax - C1Vmin);
    isULongC1 = (dv <= du);
    isVLongC1 = (du <= dv);
    du        = (C2Umax - C2Umin);
    dv        = (C2Vmax - C2Vmin);
    isULongC2 = (dv <= du);
    isVLongC2 = (du <= dv);
    surf->Bounds(SUmin, SUmax, SVmin, SVmax);
  }
  if (isUClosed && isVLongC1 && isVLongC2)
  {

    double dist = std::max((C2Vmin - C1Vmax), (C1Vmin - C2Vmax));
    if (dist < 0.0)
    {
      double distInner = std::max((C2Umin - C1Umax), (C1Umin - C2Umax));
      double distOuter = (SUmax - SUmin) - std::max((C2Umax - C1Umin), (C1Umax - C2Umin));
      if (distOuter <= distInner)
        return true;
    }
  }
  if (isVClosed && isULongC1 && isULongC2)
  {

    double dist = std::max((C2Umin - C1Umax), (C1Umin - C2Umax));
    if (dist < 0.0)
    {
      double distInner = std::max((C2Vmin - C1Vmax), (C1Vmin - C2Vmax));
      double distOuter = (SVmax - SVmin) - std::max((C2Vmax - C1Vmin), (C1Vmax - C2Vmin));
      if (distOuter <= distInner)
        return true;
    }
  }
  return false;
}

void BRepBuilderAPI_Sewing::AnalysisNearestEdges(
  const NCollection_Sequence<TopoDS_Shape>& sequenceSec,
  NCollection_Sequence<int>&                seqIndCandidate,
  NCollection_Sequence<bool>&               seqOrientations,
  const bool                                evalDist)
{

  int                            workIndex = seqIndCandidate.First();
  TopoDS_Shape                   workedge  = sequenceSec.Value(workIndex);
  TopoDS_Shape                   bnd       = workedge;
  NCollection_List<TopoDS_Shape> workfaces;
  if (mySectionBound.IsBound(bnd))
    bnd = mySectionBound(bnd);
  if (myBoundFaces.Contains(bnd))
    workfaces = myBoundFaces.FindFromKey(bnd);
  if (workfaces.IsEmpty())
    return;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapFaces;
  NCollection_List<TopoDS_Shape>::Iterator               lIt;
  for (lIt.Initialize(workfaces); lIt.More(); lIt.Next())
    mapFaces.Add(lIt.Value());
  NCollection_Sequence<int> seqNotCandidate;
  NCollection_Sequence<int> seqNewForward;

  seqNotCandidate.Append(workIndex);
  for (int i = 1; i <= seqIndCandidate.Length();)
  {
    int  index    = seqIndCandidate.Value(i);
    bool isRemove = false;
    if (index == workIndex)
    {
      seqIndCandidate.Remove(i);
      seqOrientations.Remove(i);
      isRemove = true;
    }
    if (!isRemove)
    {
      TopoDS_Shape bnd2 = sequenceSec.Value(index);
      if (mySectionBound.IsBound(bnd2))
        bnd2 = mySectionBound(bnd2);

      if (myBoundFaces.Contains(bnd2))
      {
        const NCollection_List<TopoDS_Shape>& listfaces = myBoundFaces.FindFromKey(bnd2);
        bool                                  isMerged  = true;
        for (lIt.Initialize(listfaces); lIt.More() && isMerged; lIt.Next())
        {
          if (mapFaces.Contains(lIt.Value()))
          {
            TopLoc_Location           loc;
            occ::handle<Geom_Surface> surf = BRep_Tool::Surface(TopoDS::Face(lIt.Value()), loc);
            isMerged = ((IsUClosedSurface(surf, bnd2, loc) || IsVClosedSurface(surf, bnd2, loc))
                        && IsMergedClosed(TopoDS::Edge(sequenceSec.Value(index)),
                                          TopoDS::Edge(workedge),
                                          TopoDS::Face(lIt.Value())));
          }
        }
        if (!isMerged)
        {
          seqNotCandidate.Append(index);
          seqIndCandidate.Remove(i);
          seqOrientations.Remove(i);
          isRemove = true;
        }
      }
      else
      {
        seqIndCandidate.Remove(i);
        seqOrientations.Remove(i);
        isRemove = true;
      }
    }
    if (!isRemove)
      i++;
  }
  if (seqIndCandidate.Length() == 0 || seqNotCandidate.Length() == 1)
    return;
  if (!evalDist)
    return;
  NCollection_Array2<double> TotTabDist(1, seqNotCandidate.Length(), 1, seqIndCandidate.Length());
  NCollection_Map<int>       MapIndex;
  NCollection_Sequence<int>  seqForward;

  for (int k = 1; k <= seqNotCandidate.Length(); k++)
  {
    int                                index1 = seqNotCandidate.Value(k);
    const TopoDS_Shape&                edge   = sequenceSec.Value(index1);
    NCollection_Sequence<TopoDS_Shape> tmpSeq;
    tmpSeq.Append(edge);
    for (int kk = 1; kk <= seqIndCandidate.Length(); kk++)
      tmpSeq.Append(sequenceSec.Value(seqIndCandidate.Value(kk)));

    int                        lengSec = tmpSeq.Length();
    NCollection_Array1<bool>   tabForward(1, lengSec);
    NCollection_Array1<double> tabDist(1, lengSec);
    NCollection_Array1<double> arrLen(1, lengSec);
    NCollection_Array1<double> tabMinDist(1, lengSec);
    for (int i1 = 1; i1 <= lengSec; i1++)
      tabDist(i1) = -1;

    EvaluateDistances(tmpSeq, tabForward, tabDist, arrLen, tabMinDist, 1);
    if (k == 1)
    {
      for (int n = 1; n < lengSec; n++)
      {
        if (tabDist(n + 1) == -1 || tabDist(n + 1) > myTolerance)
        {
          MapIndex.Add(n);
          continue;
        }
        TotTabDist(k, n) = tabDist(n + 1);
        seqForward.Append(tabForward(n + 1) ? 1 : 0);
      }
    }
    else
    {
      for (int n = 1; n < lengSec; n++)
      {
        if (tabDist(n) == -1 || tabDist(n) > myTolerance)
          continue;
        if (tabDist(n + 1) < TotTabDist(1, n))
        {
          MapIndex.Add(n);
        }
      }
    }
  }

  int i2 = seqIndCandidate.Length();
  for (; i2 >= 1; i2--)
  {
    if (MapIndex.Contains(i2))
    {
      seqIndCandidate.Remove(i2);
      seqOrientations.Remove(i2);
    }
  }
}

bool BRepBuilderAPI_Sewing::FindCandidates(NCollection_Sequence<TopoDS_Shape>& seqSections,
                                           NCollection_IndexedMap<int>&        mapReference,
                                           NCollection_Sequence<int>&          seqCandidates,
                                           NCollection_Sequence<bool>&         seqOrientations)
{
  int i, nbSections = seqSections.Length();
  if (nbSections <= 1)
    return false;

  int indReference = mapReference(mapReference.Extent());
  int nbCandidates = 0;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> Faces1;

  TopoDS_Edge Edge1 = TopoDS::Edge(seqSections(indReference));

  {
    TopoDS_Shape bnd = Edge1;
    if (mySectionBound.IsBound(bnd))
      bnd = mySectionBound(bnd);
    if (myBoundFaces.Contains(bnd))
    {
      NCollection_List<TopoDS_Shape>::Iterator itf1(myBoundFaces.FindFromKey(bnd));
      for (; itf1.More(); itf1.Next())
        Faces1.Add(itf1.Value());
    }
  }

  NCollection_Sequence<TopoDS_Shape> seqSectionsNew;
  NCollection_Sequence<int>          seqCandidatesNew;
  for (i = 1; i <= nbSections; i++)
  {
    if (i == indReference)
    {
      seqSectionsNew.Prepend(Edge1);
      seqCandidatesNew.Prepend(i);
    }
    else
    {
      const TopoDS_Edge& Edge2 = TopoDS::Edge(seqSections(i));
      seqSectionsNew.Append(Edge2);
      seqCandidatesNew.Append(i);
    }
  }

  int nbSectionsNew = seqSectionsNew.Length();
  if (nbSectionsNew > 1)
  {

    NCollection_Array1<bool>   arrForward(1, nbSectionsNew);
    NCollection_Array1<double> arrDistance(1, nbSectionsNew);
    NCollection_Array1<double> arrLen(1, nbSectionsNew);
    NCollection_Array1<double> arrMinDist(1, nbSectionsNew);
    EvaluateDistances(seqSectionsNew, arrForward, arrDistance, arrLen, arrMinDist, 1);

    for (i = 2; i <= nbSectionsNew; i++)
    {
      double aMaxDist = arrDistance(i);
      if (aMaxDist >= 0.0 && aMaxDist <= myTolerance && arrLen(i) > myMinTolerance)
      {

        bool isInserted = false;
        bool ori        = arrForward(i);
        for (int j = 1; (j <= seqCandidates.Length()) && !isInserted; j++)
        {
          double aDelta = arrDistance(i) - arrDistance(seqCandidates.Value(j));

          if (aDelta < Precision::Confusion())
          {

            if (fabs(aDelta) > RealSmall() || arrMinDist(i) < arrMinDist(seqCandidates.Value(j)))
            {
              seqCandidates.InsertBefore(j, i);
              seqOrientations.InsertBefore(j, ori);
              isInserted = true;
            }
          }
        }
        if (!isInserted)
        {
          seqCandidates.Append(i);
          seqOrientations.Append(ori);
        }
      }
    }

    nbCandidates = seqCandidates.Length();
    if (!nbCandidates)
      return false;

    for (i = 1; i <= nbCandidates; i++)
      seqCandidates(i) = seqCandidatesNew(seqCandidates(i));
  }

  if (!nbCandidates)
    return false;

  if (myNonmanifold && nbCandidates > 1)
  {
    NCollection_Sequence<int>  seqNewCandidates;
    NCollection_Sequence<bool> seqOrientationsNew;
    seqCandidates.Prepend(1);
    seqOrientations.Prepend(true);
    for (int k = 1; k <= seqSections.Length() && seqCandidates.Length() > 1; k++)
    {
      AnalysisNearestEdges(seqSections, seqCandidates, seqOrientations, (k == 1));
      if (k == 1 && !seqCandidates.Length())
        return false;
      if (seqCandidates.Length())
      {
        seqNewCandidates.Append(seqCandidates.First());
        seqOrientationsNew.Append(seqOrientations.First());
      }
    }
    seqCandidates.Prepend(seqNewCandidates);
    seqOrientations.Prepend(seqOrientationsNew);
    return true;
  }
  else
  {

    while (nbCandidates)
    {

      int indCandidate = seqCandidates.First();

      if (mapReference.Contains(indCandidate))
        break;

      mapReference.Add(indCandidate);
      NCollection_Sequence<int>  seqCandidates1;
      NCollection_Sequence<bool> seqOrientations1;
      bool isFound = FindCandidates(seqSections, mapReference, seqCandidates1, seqOrientations1);
      mapReference.RemoveLast();
      if (isFound)
        isFound = (seqCandidates1.Length() > 0);
      if (isFound)
      {
        int indCandidate1 = seqCandidates1.First();

        if (indCandidate1 == indReference)
          break;

        if (mapReference.Contains(indCandidate1))
        {
          seqCandidates.Prepend(indCandidate1);
          nbCandidates++;
          break;
        }
        isFound = false;
      }
      if (!isFound)
      {

        seqCandidates.Remove(1);
        seqOrientations.Remove(1);
        nbCandidates--;
      }
    }
  }

  if (nbCandidates > 0)
  {
    int          anInd = seqCandidates.Value(1);
    TopoDS_Edge  Edge2 = TopoDS::Edge(seqSections(anInd));
    TopoDS_Shape bnd   = Edge2;
    if (mySectionBound.IsBound(bnd))
      bnd = mySectionBound(bnd);

    if (myBoundFaces.Contains(bnd))
    {
      bool                                     isOK = true;
      NCollection_List<TopoDS_Shape>::Iterator itf2(myBoundFaces.FindFromKey(bnd));
      for (; itf2.More() && isOK; itf2.Next())
      {
        const TopoDS_Face& Face2 = TopoDS::Face(itf2.Value());

        isOK = !Faces1.Contains(Face2);
        if (!isOK)
          isOK = IsMergedClosed(Edge1, Edge2, Face2);
      }
      if (!isOK)
        return false;
    }
  }
  return (nbCandidates > 0);
}

BRepBuilderAPI_Sewing::BRepBuilderAPI_Sewing(const double tolerance,
                                             const bool   optionSewing,
                                             const bool   optionAnalysis,
                                             const bool   optionCutting,
                                             const bool   optionNonmanifold)
{
  myReShape = new BRepTools_ReShape;
  Init(tolerance, optionSewing, optionAnalysis, optionCutting, optionNonmanifold);
}

void BRepBuilderAPI_Sewing::Init(const double tolerance,
                                 const bool   optionSewing,
                                 const bool   optionAnalysis,
                                 const bool   optionCutting,
                                 const bool   optionNonmanifold)
{

  myTolerance   = std::max(tolerance, Precision::Confusion());
  mySewing      = optionSewing;
  myAnalysis    = optionAnalysis;
  myCutting     = optionCutting;
  myNonmanifold = optionNonmanifold;

  myMinTolerance = myTolerance * 1e-4;
  if (myMinTolerance < Precision::Confusion())
    myMinTolerance = Precision::Confusion();
  myMaxTolerance = Precision::Infinite();

  myFaceMode          = true;
  myFloatingEdgesMode = false;

  mySameParameterMode  = true;
  myLocalToleranceMode = false;
  mySewedShape.Nullify();

  Load(TopoDS_Shape());
}

void BRepBuilderAPI_Sewing::Load(const TopoDS_Shape& theShape)
{
  myReShape->Clear();
  if (theShape.IsNull())
    myShape.Nullify();
  else
    myShape = myReShape->Apply(theShape);
  mySewedShape.Nullify();

  myNbShapes = myNbEdges = myNbVertices = 0;

  myOldShapes.Clear();

  myDegenerated.Clear();
  myFreeEdges.Clear();
  myMultipleEdges.Clear();
  myContigousEdges.Clear();
  myContigSecBound.Clear();
  myBoundFaces.Clear();
  myBoundSections.Clear();
  myVertexNode.Clear();
  myVertexNodeFree.Clear();
  myNodeSections.Clear();
  myCuttingNode.Clear();
  mySectionBound.Clear();
  myLittleFace.Clear();
}

void BRepBuilderAPI_Sewing::Add(const TopoDS_Shape& aShape)
{
  if (aShape.IsNull())
    return;
  TopoDS_Shape oShape = myReShape->Apply(aShape);
  myOldShapes.Add(aShape, oShape);
  myNbShapes = myOldShapes.Extent();
}

#ifdef OCCT_DEBUG
  #include <OSD_Timer.hpp>
#endif

void BRepBuilderAPI_Sewing::Perform(const Message_ProgressRange& theProgress)
{
  const int             aNumberOfStages = myAnalysis + myCutting + mySewing + 2;
  Message_ProgressScope aPS(theProgress, "Sewing", aNumberOfStages);
#ifdef OCCT_DEBUG
  double          t_total = 0., t_analysis = 0., t_assembling = 0., t_cutting = 0., t_merging = 0.;
  OSD_Chronometer chr_total, chr_local;
  chr_total.Reset();
  chr_total.Start();
#endif

  if (myAnalysis)
  {
#ifdef OCCT_DEBUG
    std::cout << "Begin face analysis..." << std::endl;
    chr_local.Reset();
    chr_local.Start();
#endif
    FaceAnalysis(aPS.Next());
    if (!aPS.More())
      return;
#ifdef OCCT_DEBUG
    chr_local.Stop();
    chr_local.Show(t_analysis);
    std::cout << "Face analysis finished after " << t_analysis << " s" << std::endl;
#endif
  }

  if (myNbShapes || !myShape.IsNull())
  {

    FindFreeBoundaries();

    if (myBoundFaces.Extent())
    {

#ifdef OCCT_DEBUG
      std::cout << "Begin vertices assembling..." << std::endl;
      chr_local.Reset();
      chr_local.Start();
#endif
      VerticesAssembling(aPS.Next());
      if (!aPS.More())
        return;
#ifdef OCCT_DEBUG
      chr_local.Stop();
      chr_local.Show(t_assembling);
      std::cout << "Vertices assembling finished after " << t_assembling << " s" << std::endl;
#endif
      if (myCutting)
      {
#ifdef OCCT_DEBUG
        std::cout << "Begin cutting..." << std::endl;
        chr_local.Reset();
        chr_local.Start();
#endif
        Cutting(aPS.Next());
        if (!aPS.More())
          return;
#ifdef OCCT_DEBUG
        chr_local.Stop();
        chr_local.Show(t_cutting);
        std::cout << "Cutting finished after " << t_cutting << " s" << std::endl;
#endif
      }
#ifdef OCCT_DEBUG
      std::cout << "Begin merging..." << std::endl;
      chr_local.Reset();
      chr_local.Start();
#endif
      Merging(true, aPS.Next());
      if (!aPS.More())
        return;
#ifdef OCCT_DEBUG
      chr_local.Stop();
      chr_local.Show(t_merging);
      std::cout << "Merging finished after " << t_merging << " s" << std::endl;
#endif
    }
    else
    {
      aPS.Next();
      if (myCutting)
        aPS.Next();
      aPS.Next();
      if (!aPS.More())
        return;
    }

    if (mySewing)
    {

#ifdef OCCT_DEBUG
      std::cout << "Creating sewed shape..." << std::endl;
#endif

      EdgeProcessing(aPS.Next());
      if (!aPS.More())
        return;
      CreateSewedShape();
      if (!aPS.More())
      {
        mySewedShape.Nullify();
        return;
      }

      EdgeRegularity(aPS.Next());

      if (mySameParameterMode && myFaceMode)
        SameParameterShape();
      if (!aPS.More())
      {
        mySewedShape.Nullify();
        return;
      }
#ifdef OCCT_DEBUG
      std::cout << "Sewed shape created" << std::endl;
#endif
    }

    CreateOutputInformations();
    if (!aPS.More())
    {
      mySewedShape.Nullify();
      return;
    }
  }
#ifdef OCCT_DEBUG
  chr_total.Stop();
  chr_total.Show(t_total);
  std::cout << "Sewing finished!" << std::endl;
  std::cout << " analysis time   : " << t_analysis << " s" << std::endl;
  std::cout << " assembling time : " << t_assembling << " s" << std::endl;
  std::cout << " cutting time    : " << t_cutting << " s" << std::endl;
  std::cout << " merging time    : " << t_merging << " s" << std::endl;
  std::cout << "Total time       : " << t_total << " s" << std::endl;
#endif
}

const TopoDS_Shape& BRepBuilderAPI_Sewing::SewedShape() const
{
  return mySewedShape;
}

int BRepBuilderAPI_Sewing::NbFreeEdges() const
{
  return myFreeEdges.Extent();
}

const TopoDS_Edge& BRepBuilderAPI_Sewing::FreeEdge(const int index) const
{
  Standard_OutOfRange_Raise_if(index < 0 || index > NbFreeEdges(),
                               "BRepBuilderAPI_Sewing::FreeEdge");
  return TopoDS::Edge(myFreeEdges(index));
}

int BRepBuilderAPI_Sewing::NbMultipleEdges() const
{
  return myMultipleEdges.Extent();
}

const TopoDS_Edge& BRepBuilderAPI_Sewing::MultipleEdge(const int index) const
{
  Standard_OutOfRange_Raise_if(index < 0 || index > NbMultipleEdges(),
                               "BRepBuilderAPI_Sewing::MultipleEdge");
  return TopoDS::Edge(myMultipleEdges(index));
}

int BRepBuilderAPI_Sewing::NbContigousEdges() const
{
  return myContigousEdges.Extent();
}

const TopoDS_Edge& BRepBuilderAPI_Sewing::ContigousEdge(const int index) const
{
  Standard_OutOfRange_Raise_if(index < 0 || index > NbContigousEdges(),
                               "BRepBuilderAPI_Sewing::ContigousEdge");
  return TopoDS::Edge(myContigousEdges.FindKey(index));
}

const NCollection_List<TopoDS_Shape>& BRepBuilderAPI_Sewing::ContigousEdgeCouple(
  const int index) const
{
  Standard_OutOfRange_Raise_if(index < 0 || index > NbContigousEdges(),
                               "BRepBuilderAPI_Sewing::ContigousEdgeCouple");
  return myContigousEdges(index);
}

bool BRepBuilderAPI_Sewing::IsSectionBound(const TopoDS_Edge& section) const
{
  return myContigSecBound.IsBound(section);
}

const TopoDS_Edge& BRepBuilderAPI_Sewing::SectionToBoundary(const TopoDS_Edge& section) const
{
  Standard_NoSuchObject_Raise_if(!IsSectionBound(section),
                                 "BRepBuilderAPI_Sewing::SectionToBoundary");
  return TopoDS::Edge(myContigSecBound(section));
}

int BRepBuilderAPI_Sewing::NbDeletedFaces() const
{
  return myLittleFace.Extent();
}

const TopoDS_Face& BRepBuilderAPI_Sewing::DeletedFace(const int index) const
{
  Standard_OutOfRange_Raise_if(index < 0 || index > NbDeletedFaces(),
                               "BRepBuilderAPI_Sewing::DeletedFace");
  return TopoDS::Face(myLittleFace(index));
}

int BRepBuilderAPI_Sewing::NbDegeneratedShapes() const
{
  return myDegenerated.Extent();
}

const TopoDS_Shape& BRepBuilderAPI_Sewing::DegeneratedShape(const int index) const
{
  Standard_OutOfRange_Raise_if(index < 0 || index > NbDegeneratedShapes(),
                               "BRepBuilderAPI_Sewing::DegereratedShape");
  return myDegenerated(index);
}

bool BRepBuilderAPI_Sewing::IsDegenerated(const TopoDS_Shape& aShape) const
{
  TopoDS_Shape NewShape = myReShape->Apply(aShape);

  if (aShape.ShapeType() == TopAbs_FACE)
    return NewShape.IsNull();
  if (NewShape.IsNull())
    return false;

  if (NewShape.ShapeType() == TopAbs_EDGE)
    return BRep_Tool::Degenerated(TopoDS::Edge(NewShape));

  if (NewShape.ShapeType() == TopAbs_WIRE)
  {
    bool isDegenerated = true;
    for (TopoDS_Iterator aIt(NewShape); aIt.More() && isDegenerated; aIt.Next())
      isDegenerated = BRep_Tool::Degenerated(TopoDS::Edge(aIt.Value()));
    return isDegenerated;
  }
  return false;
}

bool BRepBuilderAPI_Sewing::IsModified(const TopoDS_Shape& aShape) const
{
  TopoDS_Shape NewShape = aShape;
  if (myOldShapes.Contains(aShape))
    NewShape = myOldShapes.FindFromKey(aShape);
  if (!NewShape.IsSame(aShape))
    return true;
  return false;
}

const TopoDS_Shape& BRepBuilderAPI_Sewing::Modified(const TopoDS_Shape& aShape) const
{
  if (myOldShapes.Contains(aShape))
    return myOldShapes.FindFromKey(aShape);

  return aShape;
}

bool BRepBuilderAPI_Sewing::IsModifiedSubShape(const TopoDS_Shape& aShape) const
{
  TopoDS_Shape NewShape = myReShape->Apply(aShape);
  return !NewShape.IsSame(aShape);
}

TopoDS_Shape BRepBuilderAPI_Sewing::ModifiedSubShape(const TopoDS_Shape& aShape) const
{
  return myReShape->Apply(aShape);
}

void BRepBuilderAPI_Sewing::Dump() const
{
  int i, NbBounds = myBoundFaces.Extent(), NbSections = 0;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapVertices, mapEdges;
  for (i = 1; i <= NbBounds; i++)
  {
    TopoDS_Shape bound = myBoundFaces.FindKey(i);
    if (myBoundSections.IsBound(bound))
      NbSections += myBoundSections(bound).Extent();
    else
      NbSections++;
    TopExp_Explorer aExp(myReShape->Apply(bound), TopAbs_EDGE);
    for (; aExp.More(); aExp.Next())
    {
      TopoDS_Edge E = TopoDS::Edge(aExp.Current());
      mapEdges.Add(E);
      TopoDS_Vertex V1, V2;
      TopExp::Vertices(E, V1, V2);
      mapVertices.Add(V1);
      mapVertices.Add(V2);
    }
  }
  std::cout << " " << std::endl;
  std::cout << "                        Information                         " << std::endl;
  std::cout << " ===========================================================" << std::endl;
  std::cout << " " << std::endl;
  std::cout << " Number of input shapes      : " << myOldShapes.Extent() << std::endl;
  std::cout << " Number of actual shapes     : " << myNbShapes << std::endl;
  std::cout << " Number of Bounds            : " << NbBounds << std::endl;
  std::cout << " Number of Sections          : " << NbSections << std::endl;
  std::cout << " Number of Edges             : " << mapEdges.Extent() << std::endl;
  std::cout << " Number of Vertices          : " << myNbVertices << std::endl;
  std::cout << " Number of Nodes             : " << mapVertices.Extent() << std::endl;
  std::cout << " Number of Free Edges        : " << myFreeEdges.Extent() << std::endl;
  std::cout << " Number of Contiguous Edges  : " << myContigousEdges.Extent() << std::endl;
  std::cout << " Number of Multiple Edges    : " << myMultipleEdges.Extent() << std::endl;
  std::cout << " Number of Degenerated Edges : " << myDegenerated.Extent() << std::endl;
  std::cout << " ===========================================================" << std::endl;
  std::cout << " " << std::endl;
}

void BRepBuilderAPI_Sewing::FaceAnalysis(const Message_ProgressRange& theProgress)
{
  if (!myShape.IsNull() && myOldShapes.IsEmpty())
  {
    Add(myShape);
    myShape.Nullify();
  }

  BRep_Builder                                           B;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> SmallEdges;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                        GluedVertices;
  int                   i = 1;
  Message_ProgressScope aPS(theProgress, "Shape analysis", myOldShapes.Extent());
  for (i = 1; i <= myOldShapes.Extent() && aPS.More(); i++, aPS.Next())
  {
    for (TopExp_Explorer fexp(myOldShapes(i), TopAbs_FACE); fexp.More(); fexp.Next())
    {

      TopoDS_Shape aTmpShape = fexp.Current();
      TopoDS_Face  face      = TopoDS::Face(aTmpShape);
      int          nbEdges = 0, nbSmall = 0;

      aTmpShape                 = face.EmptyCopied().Oriented(TopAbs_FORWARD);
      TopoDS_Face nface         = TopoDS::Face(aTmpShape);
      bool        isFaceChanged = false;

      TopoDS_Iterator witer(face.Oriented(TopAbs_FORWARD));
      for (; witer.More(); witer.Next())
      {

        aTmpShape = witer.Value();
        if (aTmpShape.ShapeType() != TopAbs_WIRE)
          continue;
        TopoDS_Wire wire = TopoDS::Wire(aTmpShape);

        aTmpShape                 = wire.EmptyCopied().Oriented(TopAbs_FORWARD);
        TopoDS_Wire nwire         = TopoDS::Wire(aTmpShape);
        bool        isWireChanged = false;

        TopoDS_Iterator eiter(wire.Oriented(TopAbs_FORWARD));
        for (; eiter.More(); eiter.Next())
        {

          aTmpShape        = eiter.Value();
          TopoDS_Edge edge = TopoDS::Edge(aTmpShape);
          nbEdges++;

          if (BRep_Tool::Degenerated(edge))
          {
            B.Add(nwire, edge);
            myDegenerated.Add(edge);
            nbSmall++;
            continue;
          }

          bool isSmall = SmallEdges.Contains(edge);
          if (!isSmall)
          {

            double                  first, last;
            occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(edge, first, last);
            if (c3d.IsNull())
            {
#ifdef OCCT_DEBUG
              std::cout << "Warning: Possibly small edge can be sewed: No 3D curve" << std::endl;
#endif
            }
            else
            {

              const int npt = 5;
              gp_Pnt    cp((c3d->Value(first).XYZ() + c3d->Value(last).XYZ()) * 0.5);
              double    dist, maxdist = 0.0;
              double    delta = (last - first) / (npt - 1);
              for (int idx = 0; idx < npt; idx++)
              {
                dist = cp.Distance(c3d->Value(first + idx * delta));
                if (maxdist < dist)
                  maxdist = dist;
              }
              isSmall = (2. * maxdist <= MinTolerance());
            }

            if (isSmall)
            {

              SmallEdges.Add(edge);

              TopoDS_Vertex v1, v2;
              TopExp::Vertices(edge, v1, v2);
              TopoDS_Shape nv1 = myReShape->Apply(v1), nv2 = myReShape->Apply(v2);

              if (!nv1.IsSame(v1))
              {
                NCollection_List<TopoDS_Shape>& vlist1 = GluedVertices.ChangeFromKey(nv1);

                if (!nv2.IsSame(v2))
                {

                  if (!nv1.IsSame(nv2))
                  {
                    NCollection_List<TopoDS_Shape>::Iterator liter(GluedVertices.FindFromKey(nv2));
                    for (; liter.More(); liter.Next())
                    {
                      TopoDS_Shape v = liter.Value();
                      myReShape->Replace(v, nv1.Oriented(v.Orientation()));
                      vlist1.Append(v);
                    }
                    GluedVertices.RemoveKey(nv2);
                  }
                }
                else
                {

                  vlist1.Append(v2);
                  myReShape->Replace(v2, nv1.Oriented(v2.Orientation()));
                }
              }
              else if (!nv2.IsSame(v2))
              {

                GluedVertices.ChangeFromKey(nv2).Append(v1);
                myReShape->Replace(v1, nv2.Oriented(v1.Orientation()));
              }
              else if (!v1.IsSame(v2))
              {

                TopoDS_Vertex nv;
                B.MakeVertex(nv);
                NCollection_List<TopoDS_Shape> vlist;
                vlist.Append(v1);
                vlist.Append(v2);
                GluedVertices.Add(nv, vlist);
                myReShape->Replace(v1, nv.Oriented(v1.Orientation()));
                myReShape->Replace(v2, nv.Oriented(v2.Orientation()));
              }
            }
          }

          if (isSmall)
          {
#ifdef OCCT_DEBUG
            std::cout << "Warning: Small edge made degenerated by FaceAnalysis" << std::endl;
#endif
            nbSmall++;

            aTmpShape                       = edge.Oriented(TopAbs_FORWARD);
            TopoDS_Edge               fedge = TopoDS::Edge(aTmpShape);
            double                    pfirst, plast;
            occ::handle<Geom2d_Curve> c2d = BRep_Tool::CurveOnSurface(fedge, face, pfirst, plast);
            if (!c2d.IsNull())
            {
              TopoDS_Edge nedge;
              B.MakeEdge(nedge);
              B.UpdateEdge(nedge, c2d, face, Precision::Confusion());
              B.Range(nedge, pfirst, plast);
              B.Degenerated(nedge, true);
              TopoDS_Vertex v1, v2;
              TopExp::Vertices(fedge, v1, v2);
              B.Add(nedge, myReShape->Apply(v1).Oriented(v1.Orientation()));
              B.Add(nedge, myReShape->Apply(v2).Oriented(v2.Orientation()));
              B.Add(nwire, nedge.Oriented(edge.Orientation()));
              myDegenerated.Add(nedge);
            }
            isWireChanged = true;
          }
          else
            B.Add(nwire, edge);
        }

        if (isWireChanged)
        {
          B.Add(nface, nwire.Oriented(wire.Orientation()));
          isFaceChanged = true;
        }
        else
          B.Add(nface, wire);
      }

      if (nbSmall == nbEdges)
      {
#ifdef OCCT_DEBUG
        std::cout << "Warning: Small face removed by FaceAnalysis" << std::endl;
#endif
        myLittleFace.Add(face);
        myReShape->Remove(face);
      }
      else if (isFaceChanged)
      {

        myReShape->Replace(face, nface.Oriented(face.Orientation()));
      }
    }
  }

  NCollection_IndexedDataMap<TopoDS_Shape,
                             NCollection_List<TopoDS_Shape>,
                             TopTools_ShapeMapHasher>::Iterator aMIter(GluedVertices);
  for (; aMIter.More(); aMIter.Next())
  {
    const TopoDS_Vertex&                     vnew = TopoDS::Vertex(aMIter.Key());
    gp_XYZ                                   coord(0., 0., 0.);
    int                                      nbPoints = 0;
    const NCollection_List<TopoDS_Shape>&    vlist    = aMIter.Value();
    NCollection_List<TopoDS_Shape>::Iterator liter1(vlist);
    for (; liter1.More(); liter1.Next())
    {
      coord += BRep_Tool::Pnt(TopoDS::Vertex(liter1.Value())).XYZ();
      nbPoints++;
    }
    if (nbPoints)
    {
      gp_Pnt                                   vp(coord / nbPoints);
      double                                   tol = 0.0, mtol = 0.0;
      NCollection_List<TopoDS_Shape>::Iterator liter2(vlist);
      for (; liter2.More(); liter2.Next())
      {
        double vtol = BRep_Tool::Tolerance(TopoDS::Vertex(liter2.Value()));
        if (mtol < vtol)
          mtol = vtol;
        vtol = vp.Distance(BRep_Tool::Pnt(TopoDS::Vertex(liter2.Value())));
        if (tol < vtol)
          tol = vtol;
      }
      B.UpdateVertex(vnew, vp, tol + mtol);
    }
  }

  for (i = 1; i <= myOldShapes.Extent(); i++)
    myOldShapes(i) = myReShape->Apply(myOldShapes(i));
}

void BRepBuilderAPI_Sewing::FindFreeBoundaries()
{

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> NewShapes;
  if (!myShape.IsNull())
  {
    if (myOldShapes.IsEmpty())
    {
      Add(myShape);
      myShape.Nullify();
    }
    else
    {
      TopoDS_Shape newShape = myReShape->Apply(myShape);
      if (!newShape.IsNull())
        NewShapes.Add(newShape);
    }
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
      EdgeFaces;
  int i, nbShapes = myOldShapes.Extent();
  for (i = 1; i <= nbShapes; i++)
  {

    const TopoDS_Shape& shape = myOldShapes(i);
    if (shape.IsNull())
      continue;
    NewShapes.Add(shape);

    for (TopExp_Explorer eExp(shape, TopAbs_EDGE); eExp.More(); eExp.Next())
    {
      const TopoDS_Shape& edge = eExp.Current();
      if (!EdgeFaces.Contains(edge))
      {
        NCollection_List<TopoDS_Shape> listFaces;
        EdgeFaces.Add(edge, listFaces);
      }
    }
  }

  nbShapes = NewShapes.Extent();
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapFaces;
  for (i = 1; i <= nbShapes; i++)
  {

    TopExp_Explorer fExp(NewShapes.FindKey(i), TopAbs_FACE);
    for (; fExp.More(); fExp.Next())
    {
      const TopoDS_Shape& face = fExp.Current();
      if (mapFaces.Contains(face))
        continue;
      else
        mapFaces.Add(face);

      for (TopoDS_Iterator aIw(face); aIw.More(); aIw.Next())
      {
        if (aIw.Value().ShapeType() != TopAbs_WIRE)
          continue;
        for (TopoDS_Iterator aIIe(aIw.Value()); aIIe.More(); aIIe.Next())
        {

          const TopoDS_Shape& edge = aIIe.Value();

          if (EdgeFaces.Contains(edge))
          {
            EdgeFaces.ChangeFromKey(edge).Append(face);
          }
        }
      }
    }
  }

  NCollection_IndexedDataMap<TopoDS_Shape,
                             NCollection_List<TopoDS_Shape>,
                             TopTools_ShapeMapHasher>::Iterator anIterEF(EdgeFaces);
  for (; anIterEF.More(); anIterEF.Next())
  {
    NCollection_List<TopoDS_Shape>& listFaces = anIterEF.ChangeValue();
    int                             nbFaces   = listFaces.Extent();
    TopoDS_Shape                    edge      = anIterEF.Key();
    if (edge.Orientation() == TopAbs_INTERNAL)
      continue;
    bool isSeam = false;
    if (nbFaces == 1)
    {
      TopoDS_Face face = TopoDS::Face(listFaces.First());
      isSeam           = BRep_Tool::IsClosed(TopoDS::Edge(edge), face);
      if (isSeam)
      {

        BRep_Builder    aB;
        TopoDS_Shape    anewEdge = edge.EmptyCopied();
        TopoDS_Iterator aItV(edge);
        for (; aItV.More(); aItV.Next())
          aB.Add(anewEdge, aItV.Value());

        double                    first2d, last2d;
        occ::handle<Geom2d_Curve> c2dold =
          BRep_Tool::CurveOnSurface(TopoDS::Edge(edge),
                                    TopoDS::Face(listFaces.First()),
                                    first2d,
                                    last2d);

        occ::handle<Geom2d_Curve> c2d;
        BRep_Builder              B;
        B.UpdateEdge(TopoDS::Edge(anewEdge), c2d, c2d, TopoDS::Face(listFaces.First()), 0);
        B.UpdateEdge(TopoDS::Edge(anewEdge), c2dold, TopoDS::Face(listFaces.First()), 0);

        double aFirst, aLast;
        BRep_Tool::Range(TopoDS::Edge(edge), aFirst, aLast);
        aB.Range(TopoDS::Edge(anewEdge), aFirst, aLast);
        aB.Range(TopoDS::Edge(anewEdge), TopoDS::Face(listFaces.First()), first2d, last2d);
        myReShape->Replace(edge, anewEdge);
        edge = anewEdge;

        isSeam = false;
      }
    }
    bool isBoundFloat = (myFloatingEdgesMode && !nbFaces);
    bool isBound      = (myFaceMode && ((myNonmanifold && nbFaces) || (nbFaces == 1 && !isSeam)));
    if (isBound || isBoundFloat)
    {

      if (BRep_Tool::Degenerated(TopoDS::Edge(edge)))
        continue;

      NCollection_List<TopoDS_Shape> listFacesCopy;
      listFacesCopy.Append(listFaces);
      myBoundFaces.Add(edge, listFacesCopy);

      TopoDS_Vertex vFirst, vLast;
      TopExp::Vertices(TopoDS::Edge(edge), vFirst, vLast);
      if (vFirst.IsNull() || vLast.IsNull())
        continue;
      if (vFirst.Orientation() == TopAbs_INTERNAL || vLast.Orientation() == TopAbs_INTERNAL)
        continue;
      if (isBound)
      {

        if (!myVertexNode.Contains(vFirst))
          myVertexNode.Add(vFirst, vFirst);
        if (!myVertexNode.Contains(vLast))
          myVertexNode.Add(vLast, vLast);
      }
      else
      {

        if (!myVertexNodeFree.Contains(vFirst))
          myVertexNodeFree.Add(vFirst, vFirst);
        if (!myVertexNodeFree.Contains(vLast))
          myVertexNodeFree.Add(vLast, vLast);
      }
    }
  }
}

static bool CreateNewNodes(
  const NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                                                                                   NodeNearestNode,
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>&                       NodeVertices,
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& aVertexNode,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    aNodeEdges)
{

  BRep_Builder                                                             B;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> OldNodeNewNode;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    NewNodeOldNodes;
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator anIter(
    NodeNearestNode);
  for (; anIter.More(); anIter.Next())
  {

    const TopoDS_Shape& oldnode1 = anIter.Key();
    const TopoDS_Shape& oldnode2 = anIter.Value();

    if (!NodeNearestNode.Contains(oldnode2))
      continue;

    if (OldNodeNewNode.IsBound(oldnode1))
    {
      const TopoDS_Shape& newnode1 = OldNodeNewNode(oldnode1);
      if (OldNodeNewNode.IsBound(oldnode2))
      {
        TopoDS_Shape newnode2 = OldNodeNewNode(oldnode2);
        if (!newnode1.IsSame(newnode2))
        {

          NCollection_List<TopoDS_Shape>&          lnode1 = NewNodeOldNodes.ChangeFromKey(newnode1);
          NCollection_List<TopoDS_Shape>::Iterator itn(NewNodeOldNodes.FindFromKey(newnode2));
          for (; itn.More(); itn.Next())
          {
            const TopoDS_Shape& node2 = itn.Value();
            lnode1.Append(node2);
            OldNodeNewNode(node2) = newnode1;
          }
          NewNodeOldNodes.RemoveKey(newnode2);
        }
      }
      else
      {

        OldNodeNewNode.Bind(oldnode2, newnode1);
        NewNodeOldNodes.ChangeFromKey(newnode1).Append(oldnode2);
      }
    }
    else
    {
      if (OldNodeNewNode.IsBound(oldnode2))
      {

        const TopoDS_Shape& newnode2 = OldNodeNewNode(oldnode2);
        OldNodeNewNode.Bind(oldnode1, newnode2);
        NewNodeOldNodes.ChangeFromKey(newnode2).Append(oldnode1);
      }
      else
      {

        TopoDS_Vertex newnode;
        B.MakeVertex(newnode);
        OldNodeNewNode.Bind(oldnode1, newnode);
        OldNodeNewNode.Bind(oldnode2, newnode);
        NCollection_List<TopoDS_Shape> lnodes;
        lnodes.Append(oldnode1);
        lnodes.Append(oldnode2);
        NewNodeOldNodes.Add(newnode, lnodes);
      }
    }
  }

  if (!NewNodeOldNodes.Extent())
    return false;

  NCollection_IndexedDataMap<TopoDS_Shape,
                             NCollection_List<TopoDS_Shape>,
                             TopTools_ShapeMapHasher>::Iterator anIter1(NewNodeOldNodes);
  for (; anIter1.More(); anIter1.Next())
  {
    const TopoDS_Vertex& newnode = TopoDS::Vertex(anIter1.Key());

    gp_XYZ                                                 theCoordinates(0., 0., 0.);
    NCollection_List<TopoDS_Shape>                         lvert;
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> medge;
    NCollection_List<TopoDS_Shape>                         ledge;

    NCollection_List<TopoDS_Shape>::Iterator itn(anIter1.Value());
    for (; itn.More(); itn.Next())
    {
      const TopoDS_Shape& oldnode = itn.Value();

      NCollection_List<TopoDS_Shape>::Iterator itv(NodeVertices.FindFromKey(oldnode));
      for (; itv.More(); itv.Next())
      {
        const TopoDS_Vertex& vertex = TopoDS::Vertex(itv.Value());

        aVertexNode.ChangeFromKey(vertex) = newnode;

        theCoordinates += BRep_Tool::Pnt(vertex).XYZ();
        lvert.Append(vertex);
      }

      const NCollection_List<TopoDS_Shape>&    edges = aNodeEdges(oldnode);
      NCollection_List<TopoDS_Shape>::Iterator ite(edges);
      for (; ite.More(); ite.Next())
      {
        const TopoDS_Shape& edge = ite.Value();
        if (!medge.Contains(edge))
        {
          medge.Add(edge);
          ledge.Append(edge);
        }
      }

      aNodeEdges.UnBind(oldnode);
    }

    aNodeEdges.Bind(newnode, ledge);
    gp_Pnt center(theCoordinates / lvert.Extent());

    double                                   toler = 0.0;
    NCollection_List<TopoDS_Shape>::Iterator itv(lvert);
    for (; itv.More(); itv.Next())
    {
      const TopoDS_Vertex& vertex = TopoDS::Vertex(itv.Value());
      double t = center.Distance(BRep_Tool::Pnt(vertex)) + BRep_Tool::Tolerance(vertex);
      if (toler < t)
        toler = t;
    }

    B.UpdateVertex(newnode, center, toler);
  }

  return true;
}

static int IsMergedVertices(const TopoDS_Shape& face1,
                            const TopoDS_Shape& e1,
                            const TopoDS_Shape& e2,
                            const TopoDS_Shape& vtx1,
                            const TopoDS_Shape& vtx2)
{

  if (face1.IsNull())
    return (!IsClosedShape(e1, vtx1, vtx2));

  TopoDS_Shape    wire1, wire2;
  TopExp_Explorer itw(face1, TopAbs_WIRE);
  for (; itw.More() && (wire1.IsNull() || wire2.IsNull()); itw.Next())
  {
    TopoDS_Iterator ite(itw.Current(), false);
    for (; ite.More() && (wire1.IsNull() || wire2.IsNull()); ite.Next())
    {
      if (wire1.IsNull() && e1.IsSame(ite.Value()))
        wire1 = itw.Current();
      if (wire2.IsNull() && e2.IsSame(ite.Value()))
        wire2 = itw.Current();
    }
  }
  int Status = 0;
  if (!wire1.IsNull() && !wire2.IsNull())
  {
    if (wire1.IsSame(wire2))
    {
      for (TopoDS_Iterator aIte(wire1, false); aIte.More(); aIte.Next())
      {
        TopoDS_Vertex ve1, ve2;
        TopExp::Vertices(TopoDS::Edge(aIte.Value()), ve1, ve2);
        if ((ve1.IsSame(vtx1) && ve2.IsSame(vtx2)) || (ve2.IsSame(vtx1) && ve1.IsSame(vtx2)))
          return (IsClosedShape(aIte.Value(), vtx1, vtx2) ? 0 : 1);
      }
      if (IsClosedShape(wire1, vtx1, vtx2))
      {
        TopoDS_Vertex V1, V2;
        TopExp::Vertices(TopoDS::Wire(wire1), V1, V2);
        bool isEndVertex =
          ((V1.IsSame(vtx1) && V2.IsSame(vtx2)) || (V2.IsSame(vtx1) && V1.IsSame(vtx2)));
        if (!isEndVertex)
          Status = 1;
      }
      else
        Status = 1;
    }
    else
      Status = -1;
  }
  return Status;
}

static bool GlueVertices(
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& aVertexNode,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                                             aNodeEdges,
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>& aBoundFaces,
  const double                                               Tolerance,
  const Message_ProgressRange&                               theProgress)
{

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                         NodeVertices;
  NCollection_CellFilter<BRepBuilderAPI_VertexInspector> aFilter(Tolerance);
  BRepBuilderAPI_VertexInspector                         anInspector(Tolerance);
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator anIter1(
    aVertexNode);
  for (; anIter1.More(); anIter1.Next())
  {
    const TopoDS_Shape&  vertex = anIter1.Key();
    const TopoDS_Vertex& node   = TopoDS::Vertex(anIter1.Value());
    if (NodeVertices.Contains(node))
    {
      NodeVertices.ChangeFromKey(node).Append(vertex);
    }
    else
    {
      NCollection_List<TopoDS_Shape> vlist;
      vlist.Append(vertex);
      NodeVertices.Add(node, vlist);
      gp_Pnt aPnt = BRep_Tool::Pnt(TopoDS::Vertex(node));
      aFilter.Add(NodeVertices.FindIndex(node), aPnt.XYZ());
      anInspector.Add(aPnt.XYZ());
    }
  }
  int nbNodes = NodeVertices.Extent();
#ifdef OCCT_DEBUG
  std::cout << "Glueing " << nbNodes << " nodes..." << std::endl;
#endif

  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> NodeNearestNode;
  Message_ProgressScope aPS(theProgress, "Glueing nodes", nbNodes, true);
  for (int i = 1; i <= nbNodes && aPS.More(); i++, aPS.Next())
  {
    const TopoDS_Vertex& node1 = TopoDS::Vertex(NodeVertices.FindKey(i));

    gp_Pnt pt1 = BRep_Tool::Pnt(node1);
    anInspector.SetCurrent(pt1.XYZ());
    gp_XYZ aPntMin = anInspector.Shift(pt1.XYZ(), -Tolerance);
    gp_XYZ aPntMax = anInspector.Shift(pt1.XYZ(), Tolerance);
    aFilter.Inspect(aPntMin, aPntMax, anInspector);
    if (anInspector.ResInd().IsEmpty())
      continue;

    const NCollection_List<TopoDS_Shape>& ledges1 = aNodeEdges(node1);

    NCollection_Sequence<TopoDS_Shape> SeqNodes;
    NCollection_List<TopoDS_Shape>     listNodesSameEdge;

    NCollection_List<int>::Iterator iter1(anInspector.ResInd());
    for (; iter1.More(); iter1.Next())
    {
      const TopoDS_Vertex& node2 = TopoDS::Vertex(NodeVertices.FindKey(iter1.Value()));
      if (node1 == node2)
        continue;

      const NCollection_List<TopoDS_Shape>& ledges2 = aNodeEdges(node2);

      int Status = 0, isSameEdge = false;

      NCollection_List<TopoDS_Shape>::Iterator Ie1(ledges1);
      for (; Ie1.More() && !Status && !isSameEdge; Ie1.Next())
      {
        const TopoDS_Shape& e1 = Ie1.Value();

        TopoDS_Shape v1 = node1;
        {
          TopoDS_Vertex ov1, ov2;
          TopExp::Vertices(TopoDS::Edge(e1), ov1, ov2);
          if (aVertexNode.Contains(ov1))
          {
            if (node1.IsSame(aVertexNode.FindFromKey(ov1)))
              v1 = ov1;
          }
          if (aVertexNode.Contains(ov2))
          {
            if (node1.IsSame(aVertexNode.FindFromKey(ov2)))
              v1 = ov2;
          }
        }

        NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> Faces1;
        const NCollection_List<TopoDS_Shape>&                  lfac1 = aBoundFaces.FindFromKey(e1);
        if (lfac1.Extent())
        {
          NCollection_List<TopoDS_Shape>::Iterator itf(lfac1);
          for (; itf.More(); itf.Next())
            if (!itf.Value().IsNull())
              Faces1.Add(itf.Value());
        }

        NCollection_List<TopoDS_Shape>::Iterator Ie2(ledges2);
        for (; Ie2.More() && !Status && !isSameEdge; Ie2.Next())
        {
          const TopoDS_Shape& e2 = Ie2.Value();

          TopoDS_Shape v2 = node2;
          {
            TopoDS_Vertex ov1, ov2;
            TopExp::Vertices(TopoDS::Edge(e2), ov1, ov2);
            if (aVertexNode.Contains(ov1))
            {
              if (node2.IsSame(aVertexNode.FindFromKey(ov1)))
                v2 = ov1;
            }
            if (aVertexNode.Contains(ov2))
            {
              if (node2.IsSame(aVertexNode.FindFromKey(ov2)))
                v2 = ov2;
            }
          }

          const NCollection_List<TopoDS_Shape>& lfac2 = aBoundFaces.FindFromKey(e2);
          if (lfac2.Extent())
          {
            NCollection_List<TopoDS_Shape>::Iterator itf(lfac2);
            for (; itf.More() && !Status && !isSameEdge; itf.Next())
            {

              if (Faces1.Contains(itf.Value()))
              {
                int stat = IsMergedVertices(itf.Value(), e1, e2, v1, v2);
                if (stat == 1)
                  isSameEdge = true;
                else
                  Status = stat;
              }
            }
          }
          else if (Faces1.IsEmpty() && e1 == e2)
          {
            int stat = IsMergedVertices(TopoDS_Face(), e1, e1, v1, v2);
            if (stat == 1)
              isSameEdge = true;
            else
              Status = stat;
            break;
          }
        }
      }
      if (Status)
        continue;
      if (isSameEdge)
        listNodesSameEdge.Append(node2);

      gp_Pnt pt2  = BRep_Tool::Pnt(node2);
      double dist = pt1.Distance(pt2);
      if (dist < Tolerance)
      {
        bool isIns = false;
        for (int kk = 1; kk <= SeqNodes.Length() && !isIns; kk++)
        {
          gp_Pnt pt = BRep_Tool::Pnt(TopoDS::Vertex(SeqNodes.Value(kk)));
          if (dist < pt1.Distance(pt))
          {
            SeqNodes.InsertBefore(kk, node2);
            isIns = true;
          }
        }
        if (!isIns)
          SeqNodes.Append(node2);
      }
    }
    if (SeqNodes.Length())
    {

      if (listNodesSameEdge.Extent())
      {
        NCollection_List<TopoDS_Shape>::Iterator lInt(listNodesSameEdge);
        for (; lInt.More(); lInt.Next())
        {
          const TopoDS_Vertex& n2 = TopoDS::Vertex(lInt.Value());
          gp_Pnt               p2 = BRep_Tool::Pnt(n2);
          for (int k = 1; k <= SeqNodes.Length();)
          {
            const TopoDS_Vertex& n1 = TopoDS::Vertex(SeqNodes.Value(k));
            if (n1 != n2)
            {
              gp_Pnt p1 = BRep_Tool::Pnt(n1);
              if (p2.Distance(p1) >= pt1.Distance(p1))
              {
                k++;
                continue;
              }
            }
            SeqNodes.Remove(k);
          }
        }
      }

      if (SeqNodes.Length())
        NodeNearestNode.Add(node1, SeqNodes.First());
    }
    anInspector.ClearResList();
  }

  if (NodeNearestNode.IsEmpty())
    return false;

  return CreateNewNodes(NodeNearestNode, NodeVertices, aVertexNode, aNodeEdges);
}

void BRepBuilderAPI_Sewing::VerticesAssembling(const Message_ProgressRange& theProgress)
{
  int                   nbVert     = myVertexNode.Extent();
  int                   nbVertFree = myVertexNodeFree.Extent();
  Message_ProgressScope aPS(theProgress, "Vertices assembling", 2);
  if (nbVert || nbVertFree)
  {

    int i;
    for (i = 1; i <= myBoundFaces.Extent(); i++)
    {
      TopoDS_Shape bound = myBoundFaces.FindKey(i);
      for (TopoDS_Iterator itv(bound, false); itv.More(); itv.Next())
      {
        const TopoDS_Shape& node = itv.Value();
        if (myNodeSections.IsBound(node))
          myNodeSections(node).Append(bound);
        else
        {
          NCollection_List<TopoDS_Shape> lbnd;
          lbnd.Append(bound);
          myNodeSections.Bind(node, lbnd);
        }
      }
    }

    if (nbVert)
    {
#ifdef OCCT_DEBUG
      std::cout << "Assemble " << nbVert << " vertices on faces..." << std::endl;
#endif
      while (GlueVertices(myVertexNode, myNodeSections, myBoundFaces, myTolerance, aPS.Next()))
        ;
    }
    if (!aPS.More())
      return;
    if (nbVertFree)
    {
#ifdef OCCT_DEBUG
      std::cout << "Assemble " << nbVertFree << " vertices on floating edges..." << std::endl;
#endif
      while (GlueVertices(myVertexNodeFree, myNodeSections, myBoundFaces, myTolerance, aPS.Next()))
        ;
    }
  }
}

static void replaceNMVertices(const TopoDS_Edge&                    theEdge,
                              const TopoDS_Vertex&                  theV1,
                              const TopoDS_Vertex&                  theV2,
                              const occ::handle<BRepTools_ReShape>& theReShape)
{

  NCollection_Sequence<TopoDS_Shape> aSeqNMVert;
  NCollection_Sequence<double>       aSeqNMPars;
  bool                               hasNMVert = findNMVertices(theEdge, aSeqNMVert, aSeqNMPars);
  if (!hasNMVert)
    return;
  double first, last;
  BRep_Tool::Range(theEdge, first, last);
  TopLoc_Location         aLoc;
  occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(theEdge, aLoc, first, last);
  if (c3d.IsNull())
    return;
  NCollection_Sequence<TopoDS_Shape> aEdVert;
  NCollection_Sequence<double>       aEdParams;
  int                                i = 1, nb = aSeqNMPars.Length();

  for (; i <= nb; i++)
  {
    double apar = aSeqNMPars.Value(i);
    if (fabs(apar - first) <= Precision::PConfusion())
    {
      theReShape->Replace(aSeqNMVert.Value(i), theV1);
      continue;
    }
    if (fabs(apar - last) <= Precision::PConfusion())
    {
      theReShape->Replace(aSeqNMVert.Value(i), theV2);
      continue;
    }
    const TopoDS_Shape& aV = aSeqNMVert.Value(i);
    int                 j  = 1;
    for (; j <= aEdParams.Length(); j++)
    {
      double apar2 = aEdParams.Value(j);
      if (fabs(apar - apar2) <= Precision::PConfusion())
      {
        theReShape->Replace(aV, aEdVert.Value(j));
        break;
      }
      else if (apar < apar2)
      {
        TopoDS_Shape anewV = aV.EmptyCopied();
        aEdVert.InsertBefore(j, anewV);
        aEdParams.InsertBefore(j, apar);
        NCollection_List<occ::handle<BRep_PointRepresentation>>& alistrep =
          (*((occ::handle<BRep_TVertex>*)&anewV.TShape()))->ChangePoints();
        occ::handle<BRep_PointOnCurve> aPRep = new BRep_PointOnCurve(apar, c3d, aLoc);
        alistrep.Append(aPRep);
        theReShape->Replace(aV, anewV);
        break;
      }
    }
    if (j > aEdParams.Length())
    {
      TopoDS_Shape anewV = aV.EmptyCopied();
      aEdVert.Append(anewV);
      aEdParams.Append(apar);
      NCollection_List<occ::handle<BRep_PointRepresentation>>& alistrep =
        (*((occ::handle<BRep_TVertex>*)&anewV.TShape()))->ChangePoints();
      occ::handle<BRep_PointOnCurve> aPRep = new BRep_PointOnCurve(apar, c3d, aLoc);
      alistrep.Append(aPRep);
      theReShape->Replace(aV, anewV);
    }
  }

  int newnb = aEdParams.Length();
  if (newnb < nb)
  {

    TopoDS_Shape       anewEdge = theEdge.EmptyCopied();
    TopAbs_Orientation anOri    = theEdge.Orientation();
    anewEdge.Orientation(TopAbs_FORWARD);
    BRep_Builder aB;
    aB.Add(anewEdge, theV1);
    aB.Add(anewEdge, theV2);

    for (i = 1; i <= aEdVert.Length(); i++)
      aB.Add(anewEdge, aEdVert.Value(i));
    anewEdge.Orientation(anOri);
    theReShape->Replace(theEdge, anewEdge);
  }
}

static void ReplaceEdge(const TopoDS_Shape&                   oldEdge,
                        const TopoDS_Shape&                   theNewShape,
                        const occ::handle<BRepTools_ReShape>& aReShape)
{
  TopoDS_Shape oldShape = aReShape->Apply(oldEdge);
  TopoDS_Shape newShape = aReShape->Apply(theNewShape);
  if (oldShape.IsSame(newShape) || aReShape->IsRecorded(newShape))
    return;

  aReShape->Replace(oldShape, newShape);
  TopoDS_Vertex V1old, V2old, V1new, V2new;
  TopExp::Vertices(TopoDS::Edge(oldShape), V1old, V2old);
  TopAbs_Orientation Orold = oldShape.Orientation();
  TopAbs_Orientation Ornew = Orold;
  if (newShape.ShapeType() == TopAbs_EDGE)
  {
    TopoDS_Edge aEn = TopoDS::Edge(newShape);
    TopExp::Vertices(aEn, V1new, V2new);
    Ornew = aEn.Orientation();
    replaceNMVertices(aEn, V1new, V2new, aReShape);
  }
  else if (newShape.ShapeType() == TopAbs_WIRE)
  {
    for (TopExp_Explorer aex(newShape, TopAbs_EDGE); aex.More(); aex.Next())
    {
      TopoDS_Edge ed = TopoDS::Edge(aex.Current());
      Ornew          = ed.Orientation();
      TopoDS_Vertex aV1, aV2;
      TopExp::Vertices(ed, aV1, aV2);
      replaceNMVertices(ed, aV1, aV2, aReShape);
      if (V1new.IsNull())
        V1new = aV1;
      V2new = aV2;
    }
  }

  V1new.Orientation(V1old.Orientation());
  V2new.Orientation(V2old.Orientation());
  if (V1old.IsSame(V2old) && !V1old.IsSame(V1new) && !aReShape->IsRecorded(V1new))
  {
    aReShape->Replace(V1old, V1new);
    return;
  }
  if (Orold == Ornew)
  {
    V1new.Orientation(V1old.Orientation());
    V2new.Orientation(V2old.Orientation());
    if (!V1old.IsSame(V1new) && !V1old.IsSame(V2new) && !aReShape->IsRecorded(V1new))
      aReShape->Replace(V1old, V1new);
    if (!V2old.IsSame(V2new) && !V2old.IsSame(V1new) && !aReShape->IsRecorded(V2new))
      aReShape->Replace(V2old, V2new);
  }
  else
  {
    V1new.Orientation(V2old.Orientation());
    V2new.Orientation(V1old.Orientation());
    if (!V1old.IsSame(V2new) && !V1old.IsSame(V1new) && !aReShape->IsRecorded(V2new))
      aReShape->Replace(V1old, V2new);
    if (!V2old.IsSame(V2new) && !V2old.IsSame(V1new) && !aReShape->IsRecorded(V1new))
      aReShape->Replace(V2old, V1new);
  }
}

void BRepBuilderAPI_Sewing::Merging(const bool, const Message_ProgressRange& theProgress)
{
  BRep_Builder B;

  Message_ProgressScope aPS(theProgress, "Merging bounds", myBoundFaces.Extent());
  NCollection_IndexedDataMap<TopoDS_Shape,
                             NCollection_List<TopoDS_Shape>,
                             TopTools_ShapeMapHasher>::Iterator anIterB(myBoundFaces);
  for (; anIterB.More() && aPS.More(); anIterB.Next(), aPS.Next())
  {

    const TopoDS_Shape& bound = anIterB.Key();

    if (myMergedEdges.Contains(bound))
      continue;

    if (!anIterB.Value().Extent())
    {

      TopoDS_Vertex no1, no2;
      TopExp::Vertices(TopoDS::Edge(bound), no1, no2);
      TopoDS_Shape nno1 = no1, nno2 = no2;
      if (myVertexNodeFree.Contains(no1))
        nno1 = myVertexNodeFree.FindFromKey(no1);
      if (myVertexNodeFree.Contains(no2))
        nno2 = myVertexNodeFree.FindFromKey(no2);
      if (!no1.IsSame(nno1))
      {
        nno1.Orientation(no1.Orientation());
        myReShape->Replace(no1, nno1);
      }
      if (!no2.IsSame(nno2))
      {
        nno2.Orientation(no2.Orientation());
        myReShape->Replace(no2, nno2);
      }
      myMergedEdges.Add(bound);
      continue;
    }

    TopoDS_Wire BoundWire;
    bool        isPrevSplit        = false;
    bool        hasCuttingSections = myBoundSections.IsBound(bound);
    if (hasCuttingSections)
    {
      B.MakeWire(BoundWire);
      BoundWire.Orientation(bound.Orientation());

      NCollection_List<TopoDS_Shape>::Iterator its(myBoundSections(bound));
      for (; its.More(); its.Next())
      {
        TopoDS_Shape section = its.Value();
        B.Add(BoundWire, section);
        if (myMergedEdges.Contains(section))
          isPrevSplit = true;
      }
    }

    NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> MergedWithBound;
    if (!isPrevSplit)
    {

      NCollection_Sequence<TopoDS_Shape> seqMergedWithBound;
      NCollection_Sequence<bool>         seqMergedWithBoundOri;
      if (MergedNearestEdges(bound, seqMergedWithBound, seqMergedWithBoundOri))
      {

        MergedWithBound.Add(bound, bound);

        int ii = 1;
        while (ii <= seqMergedWithBound.Length())
        {
          TopoDS_Shape iedge = seqMergedWithBound.Value(ii);

          bool isRejected = (myMergedEdges.Contains(iedge) || MergedWithBound.Contains(iedge));
          if (!isRejected)
          {
            if (myBoundSections.IsBound(iedge))
            {

              NCollection_List<TopoDS_Shape>::Iterator lit(myBoundSections(iedge));
              for (; lit.More() && !isRejected; lit.Next())
              {
                const TopoDS_Shape& sec = lit.Value();

                isRejected = (myMergedEdges.Contains(sec) || MergedWithBound.Contains(sec));
              }
            }
            if (!isRejected)
            {
              if (mySectionBound.IsBound(iedge))
              {

                const TopoDS_Shape& bnd = mySectionBound(iedge);

                isRejected = (myMergedEdges.Contains(bnd) || MergedWithBound.Contains(bnd));
              }
            }
          }

          if (isRejected)
          {

            seqMergedWithBound.Remove(ii);
            seqMergedWithBoundOri.Remove(ii);
          }
          else
          {

            MergedWithBound.Add(iedge, iedge);
            ii++;
          }
        }
        int nbMerged = seqMergedWithBound.Length();
        if (nbMerged)
        {

          NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> ActuallyMerged;
          TopoDS_Edge MergedEdge = SameParameterEdge(bound,
                                                     seqMergedWithBound,
                                                     seqMergedWithBoundOri,
                                                     ActuallyMerged,
                                                     myReShape);
          bool        isForward  = false;
          if (!MergedEdge.IsNull())
            isForward = (MergedEdge.Orientation() == TopAbs_FORWARD);

          int nbActuallyMerged = 0;
          for (ii = 1; ii <= nbMerged; ii++)
          {
            const TopoDS_Shape& iedge = seqMergedWithBound(ii);
            if (ActuallyMerged.Contains(iedge))
            {
              nbActuallyMerged++;

              TopAbs_Orientation orient = iedge.Orientation();
              if (!isForward)
                orient = TopAbs::Reverse(orient);
              if (!seqMergedWithBoundOri(ii))
                orient = TopAbs::Reverse(orient);
              MergedWithBound.ChangeFromKey(iedge) = MergedEdge.Oriented(orient);
            }
            else
              MergedWithBound.RemoveKey(iedge);
          }
          if (nbActuallyMerged)
          {

            TopAbs_Orientation orient = bound.Orientation();
            if (!isForward)
              orient = TopAbs::Reverse(orient);
            MergedWithBound.ChangeFromKey(bound) = MergedEdge.Oriented(orient);
          }
          nbMerged = nbActuallyMerged;
        }

        if (!nbMerged)
          MergedWithBound.RemoveKey(bound);
      }
    }
    const bool isMerged = !MergedWithBound.IsEmpty();

    occ::handle<BRepTools_ReShape> SectionsReShape = new BRepTools_ReShape;
    NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>
      MergedWithSections;
    if (hasCuttingSections)
    {

      NCollection_List<TopoDS_Shape>::Iterator its(myBoundSections(bound));
      for (; its.More(); its.Next())
      {

        TopoDS_Shape section = its.Value();

        if (myMergedEdges.Contains(section))
          continue;

        NCollection_Sequence<TopoDS_Shape> seqMergedWithSection;
        NCollection_Sequence<bool>         seqMergedWithSectionOri;
        if (MergedNearestEdges(section, seqMergedWithSection, seqMergedWithSectionOri))
        {

          MergedWithSections.Add(section, section);

          int ii = 1;
          while (ii <= seqMergedWithSection.Length())
          {
            TopoDS_Shape iedge = seqMergedWithSection.Value(ii);

            bool isRejected = (myMergedEdges.Contains(iedge) || MergedWithSections.Contains(iedge));
            if (!isRejected)
            {
              if (myBoundSections.IsBound(iedge))
              {

                NCollection_List<TopoDS_Shape>::Iterator lit(myBoundSections(iedge));
                for (; lit.More() && !isRejected; lit.Next())
                {
                  const TopoDS_Shape& sec = lit.Value();

                  isRejected = (myMergedEdges.Contains(sec) || MergedWithSections.Contains(sec));
                }
              }
              if (!isRejected)
              {
                if (mySectionBound.IsBound(iedge))
                {

                  const TopoDS_Shape& bnd = mySectionBound(iedge);

                  isRejected = (myMergedEdges.Contains(bnd) || MergedWithSections.Contains(bnd));
                }
              }
            }

            if (isRejected)
            {

              seqMergedWithSection.Remove(ii);
              seqMergedWithSectionOri.Remove(ii);
            }
            else
            {

              MergedWithSections.Add(iedge, iedge);
              ii++;
            }
          }
          int nbMerged = seqMergedWithSection.Length();
          if (nbMerged)
          {

            NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> ActuallyMerged;
            TopoDS_Edge MergedEdge = SameParameterEdge(section,
                                                       seqMergedWithSection,
                                                       seqMergedWithSectionOri,
                                                       ActuallyMerged,
                                                       SectionsReShape);
            bool        isForward  = false;
            if (!MergedEdge.IsNull())
              isForward = (MergedEdge.Orientation() == TopAbs_FORWARD);

            int nbActuallyMerged = 0;
            for (ii = 1; ii <= nbMerged; ii++)
            {
              const TopoDS_Shape& iedge = seqMergedWithSection(ii);
              if (ActuallyMerged.Contains(iedge))
              {
                nbActuallyMerged++;

                TopAbs_Orientation orient = iedge.Orientation();
                if (!isForward)
                  orient = TopAbs::Reverse(orient);
                if (!seqMergedWithSectionOri(ii))
                  orient = TopAbs::Reverse(orient);
                const TopoDS_Shape& oedge               = MergedEdge.Oriented(orient);
                MergedWithSections.ChangeFromKey(iedge) = oedge;
                ReplaceEdge(myReShape->Apply(iedge), oedge, SectionsReShape);
              }
              else
                MergedWithSections.RemoveKey(iedge);
            }
            if (nbActuallyMerged)
            {

              TopAbs_Orientation orient = section.Orientation();
              if (!isForward)
                orient = TopAbs::Reverse(orient);
              const TopoDS_Shape& oedge                 = MergedEdge.Oriented(orient);
              MergedWithSections.ChangeFromKey(section) = oedge;
              ReplaceEdge(myReShape->Apply(section), oedge, SectionsReShape);
            }
            nbMerged = nbActuallyMerged;
          }

          if (!nbMerged)
            MergedWithSections.RemoveKey(section);
        }
        else if (isMerged)
        {

          MergedWithSections.Clear();
          break;
        }
      }
    }
    const bool isMergedSplit = !MergedWithSections.IsEmpty();

    if (!isMerged && !isMergedSplit)
    {

      if (isPrevSplit)
      {

        myReShape->Replace(myReShape->Apply(bound), myReShape->Apply(BoundWire));
      }

      continue;
    }

    bool isSplitted = ((!isMerged && isMergedSplit) || isPrevSplit);

    if (isMerged && isMergedSplit && !isPrevSplit)
    {

      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MapSplitEdges;
      NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator
        anItm(MergedWithSections);
      for (; anItm.More(); anItm.Next())
      {
        const TopoDS_Shape& edge = anItm.Key();
        MapSplitEdges.Add(edge);
      }

      NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator
        anItm1(MergedWithBound);
      for (; anItm1.More(); anItm1.Next())
      {

        const TopoDS_Shape& edge = anItm1.Key();

        if (MapSplitEdges.Contains(edge))
          MapSplitEdges.RemoveKey(edge);
        if (myBoundSections.IsBound(edge))
        {

          NCollection_List<TopoDS_Shape>::Iterator its(myBoundSections(edge));
          for (; its.More(); its.Next())
          {
            const TopoDS_Shape& sec = its.Value();

            if (MapSplitEdges.Contains(sec))
              MapSplitEdges.RemoveKey(sec);
          }
        }
      }

      double MinSplitTol = RealLast();
      for (int ii = 1; ii <= MapSplitEdges.Extent(); ii++)
      {
        const TopoDS_Edge& edge =
          TopoDS::Edge(MergedWithSections.FindFromKey(MapSplitEdges.FindKey(ii)));
        MinSplitTol = std::min(MinSplitTol, BRep_Tool::Tolerance(edge));
      }

      const TopoDS_Edge& BoundEdge    = TopoDS::Edge(MergedWithBound.FindFromKey(bound));
      double             BoundEdgeTol = BRep_Tool::Tolerance(BoundEdge);
      isSplitted = ((MinSplitTol < BoundEdgeTol + MinTolerance()) || myNonmanifold);
      isSplitted = (!MapSplitEdges.IsEmpty() && isSplitted);
    }

    if (isSplitted)
    {

      myReShape->Replace(myReShape->Apply(bound), myReShape->Apply(BoundWire));
      NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator
        anItm(MergedWithSections);
      for (; anItm.More(); anItm.Next())
      {
        const TopoDS_Shape& oldedge = anItm.Key();
        TopoDS_Shape        newedge = SectionsReShape->Apply(anItm.Value());
        ReplaceEdge(myReShape->Apply(oldedge), newedge, myReShape);
        myMergedEdges.Add(oldedge);
        if (myBoundSections.IsBound(oldedge))
          myBoundSections.UnBind(oldedge);
      }
    }
    else
    {

      NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator
        anItm(MergedWithBound);
      for (; anItm.More(); anItm.Next())
      {
        const TopoDS_Shape& oldedge = anItm.Key();
        const TopoDS_Shape& newedge = anItm.Value();
        ReplaceEdge(myReShape->Apply(oldedge), newedge, myReShape);
        myMergedEdges.Add(oldedge);
        if (myBoundSections.IsBound(oldedge))
          myBoundSections.UnBind(oldedge);
      }
      if (myBoundSections.IsBound(bound))
        myBoundSections.UnBind(bound);
      if (!myMergedEdges.Contains(bound))
        myMergedEdges.Add(bound);
    }
  }

  myNbVertices = myVertexNode.Extent() + myVertexNodeFree.Extent();
  myNodeSections.Clear();
  myVertexNode.Clear();
  myVertexNodeFree.Clear();
  myCuttingNode.Clear();
}

bool BRepBuilderAPI_Sewing::MergedNearestEdges(const TopoDS_Shape&                 edge,
                                               NCollection_Sequence<TopoDS_Shape>& SeqMergedEdge,
                                               NCollection_Sequence<bool>&         SeqMergedOri)
{

  TopoDS_Vertex no1, no2;
  TopExp::Vertices(TopoDS::Edge(edge), no1, no2);
  TopoDS_Shape nno1 = no1, nno2 = no2;
  bool         isNode1 = myVertexNode.Contains(no1);
  bool         isNode2 = myVertexNode.Contains(no2);
  if (isNode1)
    nno1 = myVertexNode.FindFromKey(no1);
  if (isNode2)
    nno2 = myVertexNode.FindFromKey(no2);

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> mapVert1;
  mapVert1.Add(nno1);
  if (myCuttingNode.IsBound(nno1))
  {
    NCollection_List<TopoDS_Shape>::Iterator ilv(myCuttingNode(nno1));
    for (; ilv.More(); ilv.Next())
    {
      TopoDS_Shape v1 = ilv.Value();
      mapVert1.Add(v1);
      if (!isNode1 && myCuttingNode.IsBound(v1))
      {
        NCollection_List<TopoDS_Shape>::Iterator ilvn(myCuttingNode(v1));
        for (; ilvn.More(); ilvn.Next())
        {
          TopoDS_Shape vn = ilvn.Value();
          mapVert1.Add(vn);
        }
      }
    }
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapVert2;
  mapVert2.Add(nno2);
  if (myCuttingNode.IsBound(nno2))
  {
    NCollection_List<TopoDS_Shape>::Iterator ilv(myCuttingNode(nno2));
    for (; ilv.More(); ilv.Next())
    {
      TopoDS_Shape v1 = ilv.Value();
      mapVert2.Add(v1);
      if (!isNode2 && myCuttingNode.IsBound(v1))
      {
        NCollection_List<TopoDS_Shape>::Iterator ilvn(myCuttingNode(v1));
        for (; ilvn.More(); ilvn.Next())
        {
          TopoDS_Shape vn = ilvn.Value();
          mapVert2.Add(vn);
        }
      }
    }
  }

  NCollection_Sequence<TopoDS_Shape> seqEdges;
  seqEdges.Append(edge);
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapEdges;
  mapEdges.Add(edge);
  for (int i = 1; i <= mapVert1.Extent(); i++)
  {
    const TopoDS_Shape& node1 = mapVert1.FindKey(i);
    if (!myNodeSections.IsBound(node1))
      continue;
    NCollection_List<TopoDS_Shape>::Iterator ilsec(myNodeSections(node1));
    for (; ilsec.More(); ilsec.Next())
    {
      TopoDS_Shape sec = ilsec.Value();
      if (sec.IsSame(edge))
        continue;

      TopoDS_Vertex vs1, vs2;
      TopExp::Vertices(TopoDS::Edge(sec), vs1, vs2);
      TopoDS_Shape vs1n = vs1, vs2n = vs2;
      if (myVertexNode.Contains(vs1))
        vs1n = myVertexNode.FindFromKey(vs1);
      if (myVertexNode.Contains(vs2))
        vs2n = myVertexNode.FindFromKey(vs2);
      if ((mapVert1.Contains(vs1n) && mapVert2.Contains(vs2n))
          || (mapVert1.Contains(vs2n) && mapVert2.Contains(vs1n)))
        if (mapEdges.Add(sec))
        {

          bool isRejected = myMergedEdges.Contains(sec);
          if (!isRejected && myBoundSections.IsBound(sec))
          {
            NCollection_List<TopoDS_Shape>::Iterator its(myBoundSections(sec));
            for (; its.More() && !isRejected; its.Next())
            {
              TopoDS_Shape section = its.Value();

              if (myMergedEdges.Contains(section))
                isRejected = true;
            }
          }
          if (!isRejected && mySectionBound.IsBound(sec))
          {
            const TopoDS_Shape& bnd = mySectionBound(sec);
            isRejected = (!myBoundSections.IsBound(bnd) || myMergedEdges.Contains(bnd));
          }

          if (!isRejected)
            seqEdges.Append(sec);
        }
    }
  }

  mapEdges.Clear();

  bool success = false;

  int nbSection = seqEdges.Length();
  if (nbSection > 1)
  {

    int i, indRef = 1;
    if (myNonmanifold)
    {
      double lenRef = 0.;
      for (i = 1; i <= nbSection; i++)
      {
        double                  f, l;
        occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(TopoDS::Edge(seqEdges(i)), f, l);
        GeomAdaptor_Curve       cAdapt(c3d);
        double                  len = GCPnts_AbscissaPoint::Length(cAdapt, f, l);
        if (len > lenRef)
        {
          indRef = i;
          lenRef = len;
        }
      }
      if (indRef != 1)
      {
        TopoDS_Shape longEdge = seqEdges(indRef);
        seqEdges(indRef)      = seqEdges(1);
        seqEdges(1)           = longEdge;
      }
    }

    NCollection_Sequence<bool>  seqForward;
    NCollection_Sequence<int>   seqCandidates;
    NCollection_IndexedMap<int> mapReference;
    mapReference.Add(indRef);
    if (FindCandidates(seqEdges, mapReference, seqCandidates, seqForward))
    {
      int nbCandidates = seqCandidates.Length();

      for (i = 1; i <= nbCandidates; i++)
      {

        TopoDS_Shape iedge = seqEdges(seqCandidates(i));
        bool         ori   = seqForward(i) != 0;
        SeqMergedEdge.Append(iedge);
        SeqMergedOri.Append(ori);
        if (!myNonmanifold)
          break;
      }
      success = (nbCandidates != 0);
    }
  }

  return success;
}

void BRepBuilderAPI_Sewing::Cutting(const Message_ProgressRange& theProgress)
{
  int i, nbVertices = myVertexNode.Extent();
  if (!nbVertices)
    return;

  double                                 eps = myTolerance * 0.5;
  NCollection_UBTree<int, Bnd_Box>       aTree;
  NCollection_UBTreeFiller<int, Bnd_Box> aTreeFiller(aTree);
  BRepBuilderAPI_BndBoxTreeSelector      aSelector;
  for (i = 1; i <= nbVertices; i++)
  {
    gp_Pnt  pt = BRep_Tool::Pnt(TopoDS::Vertex(myVertexNode.FindKey(i)));
    Bnd_Box aBox;
    aBox.Set(pt);
    aBox.Enlarge(eps);
    aTreeFiller.Add(i, aBox);
  }
  aTreeFiller.Fill();

  occ::handle<Geom_Curve> c3d;
  TopLoc_Location         loc;
  double                  first, last;

  int                   nbBounds = myBoundFaces.Extent();
  Message_ProgressScope aPS(theProgress, "Cutting bounds", nbBounds);
  NCollection_IndexedDataMap<TopoDS_Shape,
                             NCollection_List<TopoDS_Shape>,
                             TopTools_ShapeMapHasher>::Iterator anIterB(myBoundFaces);
  for (; anIterB.More() && aPS.More(); anIterB.Next(), aPS.Next())
  {
    const TopoDS_Edge& bound = TopoDS::Edge(anIterB.Key());

    if (!anIterB.Value().Extent())
      continue;

    c3d = BRep_Tool::Curve(bound, loc, first, last);
    if (c3d.IsNull())
      continue;
    if (!loc.IsIdentity())
    {
      c3d = occ::down_cast<Geom_Curve>(c3d->Copy());
      c3d->Transform(loc.Transformation());
    }

    NCollection_List<TopoDS_Shape> listSections;
    {

      TopoDS_Vertex                                                 V1, V2;
      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> CandidateVertices;
      {

        Bnd_Box           aGlobalBox;
        GeomAdaptor_Curve adptC(c3d, first, last);
        BndLib_Add3dCurve::Add(adptC, myTolerance, aGlobalBox);

        aSelector.SetCurrent(aGlobalBox);
        aTree.Select(aSelector);

        if (!aSelector.ResInd().Extent())
          continue;

        TopExp::Vertices(bound, V1, V2);
        const TopoDS_Shape& Node1 = myVertexNode.FindFromKey(V1);
        const TopoDS_Shape& Node2 = myVertexNode.FindFromKey(V2);

        NCollection_List<int>::Iterator itl(aSelector.ResInd());
        for (; itl.More(); itl.Next())
        {
          const int           index = itl.Value();
          const TopoDS_Shape& Node  = myVertexNode.FindFromIndex(index);
          if (!Node.IsSame(Node1) && !Node.IsSame(Node2))
          {
            TopoDS_Shape vertex = myVertexNode.FindKey(index);
            CandidateVertices.Add(vertex);
          }
        }
        aSelector.ClearResList();
      }
      int nbCandidates = CandidateVertices.Extent();
      if (!nbCandidates)
        continue;

      NCollection_Array1<double> arrPara(1, nbCandidates), arrDist(1, nbCandidates);
      NCollection_Array1<gp_Pnt> arrPnt(1, nbCandidates), arrProj(1, nbCandidates);
      for (int j = 1; j <= nbCandidates; j++)
        arrPnt(j) = BRep_Tool::Pnt(TopoDS::Vertex(CandidateVertices(j)));
      ProjectPointsOnCurve(arrPnt, c3d, first, last, arrDist, arrPara, arrProj, true);

      NCollection_Sequence<TopoDS_Shape> seqNode;
      NCollection_Sequence<double>       seqPara;
      CreateCuttingNodes(CandidateVertices,
                         bound,
                         V1,
                         V2,
                         arrDist,
                         arrPara,
                         arrProj,
                         seqNode,
                         seqPara);
      if (!seqPara.Length())
        continue;

      CreateSections(bound, seqNode, seqPara, listSections);
    }
    if (listSections.Extent() > 1)
    {

      NCollection_List<TopoDS_Shape>::Iterator its(listSections);
      for (; its.More(); its.Next())
      {
        TopoDS_Shape section = its.Value();

        for (TopoDS_Iterator itv(section); itv.More(); itv.Next())
        {
          TopoDS_Shape vertex = itv.Value();

          if (myVertexNode.Contains(vertex))
            vertex = TopoDS::Vertex(myVertexNode.FindFromKey(vertex));

          if (myNodeSections.IsBound(vertex))
            myNodeSections.ChangeFind(vertex).Append(section);
          else
          {
            NCollection_List<TopoDS_Shape> lsec;
            lsec.Append(section);
            myNodeSections.Bind(vertex, lsec);
          }
        }

        mySectionBound.Bind(section, bound);
      }

      myBoundSections.Bind(bound, listSections);
    }
  }
#ifdef OCCT_DEBUG
  std::cout << "From " << nbBounds << " bounds " << myBoundSections.Extent() << " were cut into "
            << mySectionBound.Extent() << " sections" << std::endl;
#endif
}

static void GetSeqEdges(
  const TopoDS_Shape&                 edge,
  NCollection_Sequence<TopoDS_Shape>& seqEdges,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    VertEdge)
{
  int numV = 0;
  for (TopoDS_Iterator Iv(edge, false); Iv.More(); Iv.Next())
  {
    const TopoDS_Vertex& V1 = TopoDS::Vertex(Iv.Value());
    numV++;
    if (VertEdge.IsBound(V1))
    {
      const NCollection_List<TopoDS_Shape>& listEdges = VertEdge.Find(V1);
      for (NCollection_List<TopoDS_Shape>::Iterator lIt(listEdges); lIt.More(); lIt.Next())
      {
        const TopoDS_Shape& edge1 = lIt.Value();
        if (edge1.IsSame(edge))
          continue;
        bool isContained = false;
        int  i, index = 1;
        for (i = 1; i <= seqEdges.Length() && !isContained; i++)
        {
          isContained = seqEdges.Value(i).IsSame(edge1);
          if (!isContained && seqEdges.Value(i).IsSame(edge))
            index = i;
        }
        if (!isContained)
        {
          if (numV == 1)
            seqEdges.InsertBefore(index, edge1);
          else
            seqEdges.InsertAfter(index, edge1);
          GetSeqEdges(edge1, seqEdges, VertEdge);
        }
      }
    }
  }
}

void BRepBuilderAPI_Sewing::GetFreeWires(
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MapFreeEdges,
  NCollection_Sequence<TopoDS_Shape>&                            seqWires)
{
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                     VertEdge;
  NCollection_Sequence<TopoDS_Shape> seqFreeEdges;
  for (int i = 1; i <= MapFreeEdges.Extent(); i++)
  {
    const TopoDS_Shape& edge = MapFreeEdges.FindKey(i);
    seqFreeEdges.Append(edge);
    for (TopoDS_Iterator Iv(edge, false); Iv.More(); Iv.Next())
    {
      const TopoDS_Vertex& V1 = TopoDS::Vertex(Iv.Value());
      if (VertEdge.IsBound(V1))
        VertEdge.ChangeFind(V1).Append(edge);
      else
      {
        NCollection_List<TopoDS_Shape> ls;
        ls.Append(edge);
        VertEdge.Bind(V1, ls);
      }
    }
  }
  BRep_Builder B;
  int          i, j;
  for (i = 1; i <= seqFreeEdges.Length(); i++)
  {
    NCollection_Sequence<TopoDS_Shape> seqEdges;
    const TopoDS_Shape&                edge = seqFreeEdges.Value(i);
    if (!MapFreeEdges.Contains(edge))
      continue;
    seqEdges.Append(edge);
    GetSeqEdges(edge, seqEdges, VertEdge);
    TopoDS_Wire wire;
    B.MakeWire(wire);
    for (j = 1; j <= seqEdges.Length(); j++)
    {
      B.Add(wire, seqEdges.Value(j));
      MapFreeEdges.RemoveKey(seqEdges.Value(j));
    }
    seqWires.Append(wire);
    if (MapFreeEdges.IsEmpty())
      break;
  }
}

static bool IsDegeneratedWire(const TopoDS_Shape& wire)
{
  if (wire.ShapeType() != TopAbs_WIRE)
    return false;

  TopoDS_Vertex V1, V2;

  double          wireLength = 0.0;
  TopLoc_Location loc;
  double          first, last;
  int             nume    = 0;
  int             isSmall = 0;
  for (TopoDS_Iterator aIt(wire, false); aIt.More(); aIt.Next())
  {
    nume++;
    TopoDS_Shape  edge = aIt.Value();
    TopoDS_Vertex Ve1, Ve2;
    TopExp::Vertices(TopoDS::Edge(edge), Ve1, Ve2);
    if (nume == 1)
    {
      V1 = Ve1;
      V2 = Ve2;
    }
    else
    {
      if (Ve1.IsSame(V1))
        V1 = Ve2;
      else if (Ve1.IsSame(V2))
        V2 = Ve2;
      if (Ve2.IsSame(V1))
        V1 = Ve1;
      else if (Ve2.IsSame(V2))
        V2 = Ve1;
    }
    occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(TopoDS::Edge(aIt.Value()), loc, first, last);
    if (!c3d.IsNull())
    {
      c3d = occ::down_cast<Geom_Curve>(c3d->Copy());
      if (!loc.IsIdentity())
      {

        c3d->Transform(loc.Transformation());
      }
      gp_Pnt pfirst = c3d->Value(first);
      gp_Pnt plast  = c3d->Value(last);
      gp_Pnt pmid   = c3d->Value((first + last) * 0.5);
      double length = 0;
      if (pfirst.Distance(plast) > pfirst.Distance(pmid))
      {
        length = pfirst.Distance(plast);
      }
      else
      {
        GeomAdaptor_Curve cAdapt(c3d);
        length = GCPnts_AbscissaPoint::Length(cAdapt, first, last);
      }
      double tole = BRep_Tool::Tolerance(Ve1) + BRep_Tool::Tolerance(Ve2);
      if (length <= tole)
        isSmall++;
      wireLength += length;
    }
  }
  if (isSmall == nume)
    return true;

  double tol = BRep_Tool::Tolerance(V1) + BRep_Tool::Tolerance(V2);

  return wireLength <= tol;
}

static TopoDS_Edge DegeneratedSection(const TopoDS_Shape& section, const TopoDS_Shape& face)
{

  if (BRep_Tool::Degenerated(TopoDS::Edge(section)))
    return TopoDS::Edge(section);

  TopLoc_Location         loc;
  double                  first, last;
  occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(TopoDS::Edge(section), loc, first, last);
  if (c3d.IsNull())
  {
    BRep_Builder aB;
    TopoDS_Edge  edge1 = TopoDS::Edge(section);
    aB.Degenerated(edge1, true);
    return edge1;
  }
  if (!loc.IsIdentity())
  {
    c3d = occ::down_cast<Geom_Curve>(c3d->Copy());
    c3d->Transform(loc.Transformation());
  }

  TopoDS_Vertex v1, v2;
  TopExp::Vertices(TopoDS::Edge(section), v1, v2);

  gp_Pnt p1, p2, p3;
  p1 = BRep_Tool::Pnt(v1);
  p3 = BRep_Tool::Pnt(v2);
  c3d->D0(0.5 * (first + last), p2);

  TopoDS_Edge edge;

  BRep_Builder aBuilder;
  edge = TopoDS::Edge(section);
  edge.EmptyCopy();
  if (v1.IsSame(v2))
  {
    TopoDS_Shape anEdge = edge.Oriented(TopAbs_FORWARD);
    aBuilder.Add(anEdge, v1.Oriented(TopAbs_FORWARD));
    aBuilder.Add(anEdge, v2.Oriented(TopAbs_REVERSED));
  }
  else
  {
    TopoDS_Vertex newVertex;
    if (p1.Distance(p3) < BRep_Tool::Tolerance(v1))
      newVertex = v1;
    else if (p1.Distance(p3) < BRep_Tool::Tolerance(v2))
      newVertex = v2;
    else
    {
      double d1           = BRep_Tool::Tolerance(v1) + p2.Distance(p1);
      double d2           = BRep_Tool::Tolerance(v2) + p2.Distance(p3);
      double newTolerance = std::max(d1, d2);
      aBuilder.MakeVertex(newVertex, p2, newTolerance);
    }
    TopoDS_Shape anEdge = edge.Oriented(TopAbs_FORWARD);
    aBuilder.Add(anEdge, newVertex.Oriented(TopAbs_FORWARD));
    aBuilder.Add(anEdge, newVertex.Oriented(TopAbs_REVERSED));
  }

  BRep_Tool::Range(TopoDS::Edge(section), first, last);
  TopoDS_Shape anEdge = edge.Oriented(TopAbs_FORWARD);
  aBuilder.Range(TopoDS::Edge(anEdge), first, last);
  aBuilder.Degenerated(edge, true);
  occ::handle<Geom_Curve> aC3dNew;
  if (!face.IsNull())
  {
    double                    af, al;
    occ::handle<Geom2d_Curve> aC2dt =
      BRep_Tool::CurveOnSurface(TopoDS::Edge(section), TopoDS::Face(face), af, al);
    aBuilder.UpdateEdge(edge, aC3dNew, 0);
    occ::handle<Geom2d_Curve> aC2dn = BRep_Tool::CurveOnSurface(edge, TopoDS::Face(face), af, al);
    if (aC2dn.IsNull())
      aBuilder.UpdateEdge(edge, aC2dt, TopoDS::Face(face), 0);
  }

  return edge;
}

void BRepBuilderAPI_Sewing::EdgeProcessing(const Message_ProgressRange& theProgress)
{

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>            MapFreeEdges;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> EdgeFace;
  Message_ProgressScope aPS(theProgress, "Edge processing", myBoundFaces.Extent());
  NCollection_IndexedDataMap<TopoDS_Shape,
                             NCollection_List<TopoDS_Shape>,
                             TopTools_ShapeMapHasher>::Iterator anIterB(myBoundFaces);
  for (; anIterB.More() && aPS.More(); anIterB.Next(), aPS.Next())
  {
    const TopoDS_Shape&                   bound     = anIterB.Key();
    const NCollection_List<TopoDS_Shape>& listFaces = anIterB.Value();
    if (listFaces.Extent() == 1)
    {
      if (myBoundSections.IsBound(bound))
      {
        NCollection_List<TopoDS_Shape>::Iterator liter(myBoundSections(bound));
        for (; liter.More(); liter.Next())
        {
          if (!myMergedEdges.Contains(liter.Value()))
          {
            const TopoDS_Shape& edge = myReShape->Apply(liter.Value());
            if (!MapFreeEdges.Contains(edge))
            {
              const TopoDS_Shape& face = listFaces.First();
              EdgeFace.Bind(edge, face);
              MapFreeEdges.Add(edge);
            }
          }
        }
      }
      else
      {
        if (!myMergedEdges.Contains(bound))
        {
          const TopoDS_Shape& edge = myReShape->Apply(bound);
          if (!MapFreeEdges.Contains(edge))
          {
            const TopoDS_Shape& face = listFaces.First();
            EdgeFace.Bind(edge, face);
            MapFreeEdges.Add(edge);
          }
        }
      }
    }
  }

  if (!MapFreeEdges.IsEmpty())
  {
    NCollection_Sequence<TopoDS_Shape> seqWires;
    GetFreeWires(MapFreeEdges, seqWires);
    for (int j = 1; j <= seqWires.Length(); j++)
    {
      const TopoDS_Wire& wire = TopoDS::Wire(seqWires.Value(j));
      if (!IsDegeneratedWire(wire))
        continue;
      for (TopoDS_Iterator Ie(wire, false); Ie.More(); Ie.Next())
      {
        TopoDS_Shape       aTmpShape = myReShape->Apply(Ie.Value());
        const TopoDS_Edge& edge      = TopoDS::Edge(aTmpShape);
        TopoDS_Shape       face;
        if (EdgeFace.IsBound(edge))
          face = EdgeFace.Find(edge);
        TopoDS_Shape degedge = DegeneratedSection(edge, face);
        if (degedge.IsNull())
          continue;
        if (!degedge.IsSame(edge))
          ReplaceEdge(edge, degedge, myReShape);
        if (BRep_Tool::Degenerated(TopoDS::Edge(degedge)))
          myDegenerated.Add(degedge);
      }
    }
  }
}

void BRepBuilderAPI_Sewing::EdgeRegularity(const Message_ProgressRange& theProgress)
{
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aMapEF;
  TopExp::MapShapesAndAncestors(mySewedShape, TopAbs_EDGE, TopAbs_FACE, aMapEF);

  Message_ProgressScope aPS(theProgress, "Encode edge regularity", myMergedEdges.Extent());
  for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator aMEIt(myMergedEdges);
       aMEIt.More() && aPS.More();
       aMEIt.Next(), aPS.Next())
  {
    TopoDS_Edge                           anEdge = TopoDS::Edge(myReShape->Apply(aMEIt.Value()));
    const NCollection_List<TopoDS_Shape>* aFaces = aMapEF.Seek(anEdge);

    if (aFaces && aFaces->Extent() == 2)
      BRepLib::EncodeRegularity(anEdge,
                                TopoDS::Face(aFaces->First()),
                                TopoDS::Face(aFaces->Last()));
  }

  myMergedEdges.Clear();
}

void BRepBuilderAPI_Sewing::CreateSewedShape()
{

  BRepTools_Quilt aQuilt;
  bool            isLocal = !myShape.IsNull();
  if (isLocal)
  {

    TopoDS_Shape ns = myReShape->Apply(myShape);
    aQuilt.Add(ns);
  }
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator anIter(
    myOldShapes);
  for (; anIter.More(); anIter.Next())
  {
    TopoDS_Shape sh = anIter.Value();
    if (!sh.IsNull())
    {
      sh                   = myReShape->Apply(sh);
      anIter.ChangeValue() = sh;
      if (!isLocal)
        aQuilt.Add(sh);
    }
  }
  TopoDS_Shape aNewShape = aQuilt.Shells();
  int          numsh     = 0;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> OldShells;

  BRep_Builder    aB;
  TopoDS_Compound aComp;
  aB.MakeCompound(aComp);
  for (TopoDS_Iterator aExpSh(aNewShape, false); aExpSh.More(); aExpSh.Next())
  {
    TopoDS_Shape sh       = aExpSh.Value();
    bool         hasEdges = false;
    if (sh.ShapeType() == TopAbs_SHELL)
    {
      if (myNonmanifold)
        hasEdges = !OldShells.Contains(sh);
      else
      {
        TopoDS_Shape face;
        int          numf = 0;
        for (TopExp_Explorer aExpF(sh, TopAbs_FACE); aExpF.More() && (numf < 2); aExpF.Next())
        {
          face = aExpF.Current();
          numf++;
        }
        if (numf == 1)
          aB.Add(aComp, face);
        else if (numf > 1)
          aB.Add(aComp, sh);
        if (numf)
          numsh++;
      }
    }
    else if (sh.ShapeType() == TopAbs_FACE)
    {
      if (myNonmanifold)
      {
        TopoDS_Shell ss;
        aB.MakeShell(ss);
        aB.Add(ss, sh);
        sh       = ss;
        hasEdges = true;
      }
      else
      {
        aB.Add(aComp, sh);
        numsh++;
      }
    }
    else
    {
      aB.Add(aComp, sh);
      numsh++;
    }
    if (hasEdges)
      OldShells.Add(sh);
  }

  if (myNonmanifold)
  {
    int nbOldShells = OldShells.Extent();
    if (nbOldShells == 1)
    {

      const TopoDS_Shape& sh = OldShells.FindKey(1);
      TopoDS_Shape        face;
      int                 numf = 0;
      for (TopExp_Explorer aExpF(sh, TopAbs_FACE); aExpF.More() && (numf < 2); aExpF.Next())
      {
        face = aExpF.Current();
        numf++;
      }
      if (numf == 1)
        aB.Add(aComp, face);
      else if (numf > 1)
        aB.Add(aComp, sh);
      if (numf)
        numsh++;
    }
    else if (nbOldShells)
    {

      NCollection_Map<int> IndexMerged;
      while (IndexMerged.Extent() < nbOldShells)
      {
        TopoDS_Shell                                           NewShell;
        NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> NewEdges;
        for (int i = 1; i <= nbOldShells; i++)
        {
          if (IndexMerged.Contains(i))
            continue;
          const TopoDS_Shell& shell = TopoDS::Shell(OldShells.FindKey(i));
          if (NewShell.IsNull())
          {
            aB.MakeShell(NewShell);
            TopoDS_Iterator aItSS(shell);
            for (; aItSS.More(); aItSS.Next())
              aB.Add(NewShell, aItSS.Value());

            for (TopExp_Explorer eexp(shell, TopAbs_EDGE); eexp.More(); eexp.Next())
            {
              const TopoDS_Shape& edge = eexp.Current();
              NewEdges.Add(edge);
            }
            IndexMerged.Add(i);
          }
          else
          {
            bool            hasSharedEdge = false;
            TopExp_Explorer eexp(shell, TopAbs_EDGE);
            for (; eexp.More() && !hasSharedEdge; eexp.Next())
              hasSharedEdge = NewEdges.Contains(eexp.Current());
            if (hasSharedEdge)
            {

              for (TopExp_Explorer eexp1(shell, TopAbs_EDGE); eexp1.More(); eexp1.Next())
              {
                const TopoDS_Shape& edge = eexp1.Current();
                NewEdges.Add(edge);
              }

              for (TopExp_Explorer fexp(shell, TopAbs_FACE); fexp.More(); fexp.Next())
              {
                const TopoDS_Shape& face = fexp.Current();
                aB.Add(NewShell, face);
              }
              IndexMerged.Add(i);
            }
          }
        }

        TopoDS_Shape    face;
        int             numf = 0;
        TopExp_Explorer aExpF(NewShell, TopAbs_FACE);
        for (; aExpF.More() && (numf < 2); aExpF.Next())
        {
          face = aExpF.Current();
          numf++;
        }
        if (numf == 1)
          aB.Add(aComp, face);
        else if (numf > 1)
          aB.Add(aComp, NewShell);
        if (numf)
          numsh++;
      }
    }
  }
  if (numsh == 1)
  {

    TopoDS_Iterator aIt(aComp, false);
    mySewedShape = aIt.Value();
  }
  else
    mySewedShape = aComp;
}

void BRepBuilderAPI_Sewing::CreateOutputInformations()
{

  int i;

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    edgeSections;

  for (i = 1; i <= myBoundFaces.Extent(); i++)
  {
    const TopoDS_Shape&            bound = myBoundFaces.FindKey(i);
    NCollection_List<TopoDS_Shape> lsect;
    if (myBoundSections.IsBound(bound))
      lsect = myBoundSections(bound);
    TopExp_Explorer aExp(myReShape->Apply(bound), TopAbs_EDGE);
    for (; aExp.More(); aExp.Next())
    {
      TopoDS_Shape                             sec  = bound;
      const TopoDS_Shape&                      edge = aExp.Current();
      NCollection_List<TopoDS_Shape>::Iterator aI(lsect);
      for (; aI.More(); aI.Next())
      {
        const TopoDS_Shape& section = aI.Value();
        if (edge.IsSame(myReShape->Apply(section)))
        {
          sec = section;
          break;
        }
      }
      if (edgeSections.Contains(edge))
        edgeSections.ChangeFromKey(edge).Append(sec);
      else
      {
        NCollection_List<TopoDS_Shape> listSec;
        listSec.Append(sec);
        edgeSections.Add(edge, listSec);
      }
    }
  }

  NCollection_IndexedDataMap<TopoDS_Shape,
                             NCollection_List<TopoDS_Shape>,
                             TopTools_ShapeMapHasher>::Iterator anIter(edgeSections);
  for (; anIter.More(); anIter.Next())
  {
    const TopoDS_Shape&                   edge        = anIter.Key();
    const NCollection_List<TopoDS_Shape>& listSection = anIter.Value();
    if (listSection.Extent() == 1)
    {
      if (BRep_Tool::Degenerated(TopoDS::Edge(edge)))
        myDegenerated.Add(edge);
      else
        myFreeEdges.Add(edge);
    }
    else if (listSection.Extent() == 2)
    {
      myContigousEdges.Add(edge, listSection);
    }
    else
    {
      myMultipleEdges.Add(edge);
    }
  }

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aEdgeMap;
  for (i = 1; i <= myBoundFaces.Extent(); i++)
  {
    const TopoDS_Shape& bound = myBoundFaces.FindKey(i);
    if (myBoundSections.IsBound(bound))
    {
      NCollection_List<TopoDS_Shape>::Iterator iter(myBoundSections(bound));
      for (; iter.More(); iter.Next())
      {
        const TopoDS_Shape& section = iter.Value();
        if (!myMergedEdges.Contains(section))
          continue;

        TopoDS_Shape nedge = myReShape->Apply(section);
        if (nedge.IsNull())
          continue;
        if (!bound.IsSame(section))
          if (myContigousEdges.Contains(nedge))
            myContigSecBound.Bind(section, bound);
      }
    }
  }
}

void BRepBuilderAPI_Sewing::ProjectPointsOnCurve(const NCollection_Array1<gp_Pnt>& arrPnt,
                                                 const occ::handle<Geom_Curve>&    c3d,
                                                 const double                      first,
                                                 const double                      last,
                                                 NCollection_Array1<double>&       arrDist,
                                                 NCollection_Array1<double>&       arrPara,
                                                 NCollection_Array1<gp_Pnt>&       arrProj,
                                                 const bool isConsiderEnds) const
{
  arrDist.Init(-1.0);

  GeomAdaptor_Curve GAC(c3d);
  Extrema_ExtPC     locProj;
  locProj.Initialize(GAC, first, last);
  gp_Pnt pfirst = GAC.Value(first), plast = GAC.Value(last);
  int    find = 1;

  int lind = arrPnt.Length();

  for (int i1 = find; i1 <= lind; i1++)
  {
    gp_Pnt pt          = arrPnt(i1);
    double worktol     = myTolerance;
    double distF2      = pfirst.SquareDistance(pt);
    double distL2      = plast.SquareDistance(pt);
    bool   isProjected = false;
    try
    {

      locProj.Perform(pt);
      if (locProj.IsDone() && locProj.NbExt() > 0)
      {
        double dist2Min = (isConsiderEnds || i1 == find || i1 == lind ? std::min(distF2, distL2)
                                                                      : Precision::Infinite());
        int    ind, indMin = 0;
        for (ind = 1; ind <= locProj.NbExt(); ind++)
        {
          double dProj2 = locProj.SquareDistance(ind);
          if (dProj2 < dist2Min)
          {
            indMin   = ind;
            dist2Min = dProj2;
          }
        }
        if (indMin)
        {
          isProjected               = true;
          Extrema_POnCurv pOnC      = locProj.Point(indMin);
          double          paramProj = pOnC.Parameter();
          gp_Pnt          ptProj    = GAC.Value(paramProj);
          double          distProj2 = ptProj.SquareDistance(pt);
          if (!locProj.IsMin(indMin))
          {
            if (std::min(distF2, distL2) < dist2Min)
            {
              if (distF2 < distL2)
              {
                paramProj = first;
                distProj2 = distF2;
                ptProj    = pfirst;
              }
              else
              {
                paramProj = last;
                distProj2 = distL2;
                ptProj    = plast;
              }
            }
          }
          if (distProj2 < worktol * worktol || !isConsiderEnds)
          {
            arrDist(i1) = sqrt(distProj2);
            arrPara(i1) = paramProj;
            arrProj(i1) = ptProj;
          }
        }
      }
    }
    catch (Standard_Failure const& anException)
    {
#ifdef OCCT_DEBUG
      std::cout << "Exception in BRepBuilderAPI_Sewing::ProjectPointsOnCurve: ";
      anException.Print(std::cout);
      std::cout << std::endl;
#endif
      (void)anException;
      worktol = MinTolerance();
    }
    if (!isProjected && isConsiderEnds)
    {
      if (std::min(distF2, distL2) < worktol * worktol)
      {
        if (distF2 < distL2)
        {
          arrDist(i1) = sqrt(distF2);
          arrPara(i1) = first;
          arrProj(i1) = pfirst;
        }
        else
        {
          arrDist(i1) = sqrt(distL2);
          arrPara(i1) = last;
          arrProj(i1) = plast;
        }
      }
    }
  }
}

void BRepBuilderAPI_Sewing::CreateCuttingNodes(
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MapVert,
  const TopoDS_Shape&                                                  bound,
  const TopoDS_Shape&                                                  vfirst,
  const TopoDS_Shape&                                                  vlast,
  const NCollection_Array1<double>&                                    arrDist,
  const NCollection_Array1<double>&                                    arrPara,
  const NCollection_Array1<gp_Pnt>&                                    arrPnt,
  NCollection_Sequence<TopoDS_Shape>&                                  seqVert,
  NCollection_Sequence<double>&                                        seqPara)
{
  int i, j, nbProj = MapVert.Extent();

  NCollection_Sequence<int> seqOrderedIndex;
  {
    NCollection_Sequence<double> seqOrderedDistance;
    for (i = 1; i <= nbProj; i++)
    {
      double distProj = arrDist(i);
      if (distProj < 0.0)
        continue;
      bool isInserted = false;
      for (j = 1; j <= seqOrderedIndex.Length() && !isInserted; j++)
      {
        isInserted = (distProj < seqOrderedDistance(j));
        if (isInserted)
        {
          seqOrderedIndex.InsertBefore(j, i);
          seqOrderedDistance.InsertBefore(j, distProj);
        }
      }
      if (!isInserted)
      {
        seqOrderedIndex.Append(i);
        seqOrderedDistance.Append(distProj);
      }
    }
  }
  nbProj = seqOrderedIndex.Length();
  if (!nbProj)
    return;

  BRep_Builder aBuilder;

  NCollection_Sequence<double> seqDist;
  NCollection_Sequence<gp_Pnt> seqPnt;
  {

    TopLoc_Location         loc;
    double                  first, last;
    occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(TopoDS::Edge(bound), loc, first, last);
    if (!loc.IsIdentity())
    {
      c3d = occ::down_cast<Geom_Curve>(c3d->Copy());
      c3d->Transform(loc.Transformation());
    }
    GeomAdaptor_Curve GAC(c3d);
    seqVert.Prepend(vfirst);
    seqVert.Append(vlast);
    seqPara.Prepend(first);
    seqPara.Append(last);
    seqDist.Prepend(-1.0);
    seqDist.Append(-1.0);
    seqPnt.Prepend(GAC.Value(first));
    seqPnt.Append(GAC.Value(last));
  }

  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> NodeCuttingVertex;
  for (i = 1; i <= nbProj; i++)
  {

    const int index   = seqOrderedIndex(i);
    double    disProj = arrDist(index);
    gp_Pnt    pntProj = arrPnt(index);

    TopoDS_Shape node = myVertexNode.FindFromKey(MapVert(index));
    if (NodeCuttingVertex.Contains(node))
      continue;

    int    indexMin = 1;
    double dist, distMin = pntProj.Distance(seqPnt(1));
    for (j = 2; j <= seqPnt.Length(); j++)
    {
      dist = pntProj.Distance(seqPnt(j));
      if (dist < distMin)
      {
        distMin  = dist;
        indexMin = j;
      }
    }

    if (distMin <= std::max(disProj * 0.1, MinTolerance()))
    {

      double jdist = seqDist.Value(indexMin);
      if (jdist < 0.0)
      {

        seqDist.SetValue(indexMin, disProj);
        const TopoDS_Shape& cvertex = seqVert.Value(indexMin);
        NodeCuttingVertex.Add(node, cvertex);
      }
      else
      {

        NodeCuttingVertex.Add(node, TopoDS_Vertex());
      }
    }
    else
    {

      TopoDS_Vertex cvertex;
      aBuilder.MakeVertex(cvertex, pntProj, Precision::Confusion());

      NodeCuttingVertex.Add(node, cvertex);

      double parProj = arrPara(index);
      for (j = 2; j <= seqPara.Length(); j++)
      {
        if (parProj <= seqPara.Value(j))
        {
          seqVert.InsertBefore(j, cvertex);
          seqPara.InsertBefore(j, parProj);
          seqDist.InsertBefore(j, disProj);
          seqPnt.InsertBefore(j, pntProj);
          break;
        }
      }
    }
  }

  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator aMIt(
    NodeCuttingVertex);
  for (; aMIt.More(); aMIt.Next())
  {
    TopoDS_Shape cnode = aMIt.Value();

    if (cnode.IsNull())
      continue;

    const TopoDS_Shape& node = aMIt.Key();
    if (myVertexNode.Contains(cnode))
    {

      cnode = myVertexNode.FindFromKey(cnode);
    }
    else
    {

      NCollection_List<TopoDS_Shape> ls;
      ls.Append(node);
      myCuttingNode.Bind(cnode, ls);
    }

    if (myCuttingNode.IsBound(node))
    {
      myCuttingNode.ChangeFind(node).Append(cnode);
    }
    else
    {
      NCollection_List<TopoDS_Shape> ls;
      ls.Append(cnode);
      myCuttingNode.Bind(node, ls);
    }
  }

  seqVert.Remove(1);
  seqVert.Remove(seqVert.Length());
  seqPara.Remove(1);
  seqPara.Remove(seqPara.Length());
}

void BRepBuilderAPI_Sewing::CreateSections(const TopoDS_Shape&                       section,
                                           const NCollection_Sequence<TopoDS_Shape>& seqNode,
                                           const NCollection_Sequence<double>&       seqPara,
                                           NCollection_List<TopoDS_Shape>&           listEdge)
{
  const TopoDS_Edge& sec = TopoDS::Edge(section);

  NCollection_Sequence<TopoDS_Shape> aSeqNMVert;
  NCollection_Sequence<double>       aSeqNMPars;
  findNMVertices(sec, aSeqNMVert, aSeqNMPars);

  BRep_Builder aBuilder;

  double first, last;
  BRep_Tool::Range(sec, first, last);

  double       par1, par2;
  TopoDS_Shape V1, V2;
  int          i, len = seqPara.Length() + 1;
  for (i = 1; i <= len; i++)
  {

    TopoDS_Edge edge = sec;
    edge.EmptyCopy();

    if (i == 1)
    {
      par1 = first;
      par2 = seqPara(i);
      V1   = TopExp::FirstVertex(sec);
      V2   = seqNode(i);
    }
    else if (i == len)
    {
      par1 = seqPara(i - 1);
      par2 = last;
      V1   = seqNode(i - 1);
      V2   = TopExp::LastVertex(sec);
    }
    else
    {
      par1 = seqPara(i - 1);
      par2 = seqPara(i);
      V1   = seqNode(i - 1);
      V2   = seqNode(i);
    }

    TopoDS_Shape aTmpShape = edge.Oriented(TopAbs_FORWARD);
    TopoDS_Edge  aTmpEdge  = TopoDS::Edge(aTmpShape);
    aTmpShape              = V1.Oriented(TopAbs_FORWARD);
    aBuilder.Add(aTmpEdge, aTmpShape);
    aTmpShape = V2.Oriented(TopAbs_REVERSED);
    aBuilder.Add(aTmpEdge, aTmpShape);
    aBuilder.Range(aTmpEdge, par1, par2);

    int k = 1;
    for (; k <= aSeqNMPars.Length(); k++)
    {
      double apar = aSeqNMPars.Value(k);
      if (apar >= par1 && apar <= par2)
      {
        aBuilder.Add(aTmpEdge, aSeqNMVert.Value(k));
        aSeqNMVert.Remove(k);
        aSeqNMPars.Remove(k);
        k--;
      }
    }
    listEdge.Append(edge);
  }

  const NCollection_List<TopoDS_Shape>& listFaces = myBoundFaces.FindFromKey(sec);
  if (!listFaces.Extent())
    return;

  double tolEdge = BRep_Tool::Tolerance(sec);

  NCollection_List<TopoDS_Shape>::Iterator itf(listFaces);
  for (; itf.More(); itf.Next())
  {

    const TopoDS_Face& fac = TopoDS::Face(itf.Value());

    double                    first2d = 0., last2d = 0., first2d1 = 0, last2d1 = 0.;
    occ::handle<Geom2d_Curve> c2d = BRep_Tool::CurveOnSurface(sec, fac, first2d, last2d);
    if (c2d.IsNull())
      continue;
    occ::handle<Geom2d_Curve> c2d1;
    bool                      isSeam = BRep_Tool::IsClosed(sec, fac);

    if (isSeam)
    {
      TopoDS_Edge secRev = TopoDS::Edge(sec.Reversed());

      c2d1 = BRep_Tool::CurveOnSurface(secRev, fac, first2d1, last2d1);
      if (c2d1.IsNull())
        continue;
    }

    occ::handle<Geom2d_Curve>                c2dNew, c2d1New;
    NCollection_List<TopoDS_Shape>::Iterator ite(listEdge);
    for (; ite.More(); ite.Next())
    {

      const TopoDS_Edge& edge = TopoDS::Edge(ite.Value());
      BRep_Tool::Range(edge, par1, par2);

      c2dNew = occ::down_cast<Geom2d_Curve>(c2d->Copy());

      if (!c2d1.IsNull())
      {
        c2d1New = occ::down_cast<Geom2d_Curve>(c2d1->Copy());
      }

      if (!isSeam && c2d1New.IsNull())
        aBuilder.UpdateEdge(edge, c2dNew, fac, tolEdge);
      else
      {
        TopAbs_Orientation Ori = edge.Orientation();
        if (fac.Orientation() == TopAbs_REVERSED)
          Ori = TopAbs::Reverse(Ori);

        if (Ori == TopAbs_FORWARD)
          aBuilder.UpdateEdge(edge, c2dNew, c2d1New, fac, tolEdge);
        else
          aBuilder.UpdateEdge(edge, c2d1New, c2dNew, fac, tolEdge);
      }
    }
  }
}

void BRepBuilderAPI_Sewing::SameParameterShape()
{
  if (!mySameParameterMode)
    return;
  TopExp_Explorer exp(mySewedShape, TopAbs_EDGE);

  for (; exp.More(); exp.Next())
  {
    const TopoDS_Edge& sec = TopoDS::Edge(exp.Current());
    try
    {

      BRepLib::SameParameter(sec, BRep_Tool::Tolerance(sec));
    }
    catch (Standard_Failure const&)
    {
#ifdef OCCT_DEBUG
      std::cout
        << "Fail: BRepBuilderAPI_Sewing::SameParameterShape exception in BRepLib::SameParameter"
        << std::endl;
#endif
      continue;
    }
  }
}

NCollection_CellFilter_Action BRepBuilderAPI_VertexInspector::Inspect(const int theTarget)
{

  const gp_XYZ& aPnt = myPoints.Value(theTarget - 1);
  double        aDx, aDy, aDz;
  aDx = myCurrent.X() - aPnt.X();
  aDy = myCurrent.Y() - aPnt.Y();
  aDz = myCurrent.Z() - aPnt.Z();

  if ((aDx * aDx <= myTol) && (aDy * aDy <= myTol) && (aDz * aDz <= myTol))
    myResInd.Append(theTarget);
  return CellFilter_Keep;
}

const occ::handle<BRepTools_ReShape>& BRepBuilderAPI_Sewing::GetContext() const
{
  return myReShape;
}

void BRepBuilderAPI_Sewing::SetContext(const occ::handle<BRepTools_ReShape>& theContext)
{
  myReShape = theContext;
}
