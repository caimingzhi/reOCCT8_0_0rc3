#include <Bnd_Box.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepBndLib.hpp>
#include <BRepCheck_Wire.hpp>
#include <BRepExtrema_DistShapeShape.hpp>
#include <BRepFill.hpp>
#include <BRepFill_CompatibleWires.hpp>
#include <BRepGProp.hpp>
#include <BRepLib.hpp>
#include <BRepLib_FindSurface.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <BRepLib_MakeWire.hpp>
#include <BRepLProp.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <gp.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Pln.hpp>
#include <gp_Vec.hpp>
#include <GProp_PrincipalProps.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_NoSuchObject.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Sequence.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_IndexedDataMap.hpp>

#ifdef OCCT_DEBUG_EFV
static void EdgesFromVertex(const TopoDS_Wire&   W,
                            const TopoDS_Vertex& V,
                            TopoDS_Edge&         E1,
                            TopoDS_Edge&         E2)
{
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    Map;
  TopExp::MapShapesAndAncestors(W, TopAbs_VERTEX, TopAbs_EDGE, Map);

  const NCollection_List<TopoDS_Shape>& List = Map.FindFromKey(V);
  TopoDS_Edge                           e1   = TopoDS::Edge(List.First());
  TopoDS_Edge                           e2   = TopoDS::Edge(List.Last());

  BRepTools_WireExplorer anExp;
  int                    I1 = 0, I2 = 0, NE = 0;

  for (anExp.Init(W); anExp.More(); anExp.Next())
  {
    NE++;
    const TopoDS_Edge& ECur = anExp.Current();
    if (e1.IsSame(ECur))
    {
      I1 = NE;
    }
    if (e2.IsSame(ECur))
    {
      I2 = NE;
    }
  }

  if (std::abs(I2 - I1) == 1)
  {

    if (I2 == I1 + 1)
    {
      E1 = e1;
      E2 = e2;
    }
    else
    {
      E1 = e2;
      E2 = e1;
    }
  }
  else
  {

    if (I1 == 1 && I2 == NE)
    {
      E1 = e2;
      E2 = e1;
    }
    else
    {
      E1 = e1;
      E2 = e2;
    }
  }
}

#endif

static void AddNewEdge(const TopoDS_Shape&                                 theEdge,
                       const NCollection_DataMap<TopoDS_Shape,
                                                 NCollection_Sequence<TopoDS_Shape>,
                                                 TopTools_ShapeMapHasher>& theEdgeNewEdges,
                       NCollection_List<TopoDS_Shape>&                     ListNewEdges)
{
  if (theEdgeNewEdges.IsBound(theEdge))
  {
    const NCollection_Sequence<TopoDS_Shape>& NewEdges = theEdgeNewEdges(theEdge);
    for (int i = 1; i <= NewEdges.Length(); i++)
    {
      const TopoDS_Shape& anEdge = NewEdges(i);
      AddNewEdge(anEdge, theEdgeNewEdges, ListNewEdges);
    }
  }
  else
    ListNewEdges.Append(theEdge);
}

static void SeqOfVertices(const TopoDS_Wire& W, NCollection_Sequence<TopoDS_Shape>& S)
{
  S.Clear();
  int             jj;
  TopExp_Explorer PE;
  for (PE.Init(W, TopAbs_VERTEX); PE.More(); PE.Next())
  {
    bool trouve = false;
    for (jj = 1; jj <= S.Length() && (!trouve); jj++)
    {
      if (S.Value(jj).IsSame(PE.Current()))
        trouve = true;
    }
    if (!trouve)
      S.Append(PE.Current());
  }
}

static bool PlaneOfWire(const TopoDS_Wire& W, gp_Pln& P)
{
  bool                      isplane = true;
  BRepLib_FindSurface       findPlanarSurf;
  occ::handle<Geom_Surface> S;
  TopLoc_Location           L;

  GProp_GProps GP;
  gp_Pnt       Bary;
  bool         isBaryDefined = false;

  bool wClosed = W.Closed();
  if (!wClosed)
  {

    TopoDS_Vertex V1, V2;
    TopExp::Vertices(W, V1, V2);
    if (V1.IsSame(V2))
      wClosed = true;
  }

  if (wClosed)
  {
    int             nbEdges = 0;
    TopoDS_Iterator anIter;
    anIter.Initialize(W);
    for (; anIter.More(); anIter.Next())
      nbEdges++;

    if (nbEdges == 1)
    {
      GeomAdaptor_Curve AdC;
      double            first, last;
      anIter.Initialize(W);
      AdC.Load(BRep_Tool::Curve(TopoDS::Edge(anIter.Value()), first, last));

      if (AdC.GetType() == GeomAbs_Circle)
      {
        Bary          = AdC.Circle().Location();
        isBaryDefined = true;
      }

      if (AdC.GetType() == GeomAbs_Ellipse)
      {
        Bary          = AdC.Ellipse().Location();
        isBaryDefined = true;
      }
    }
  }

  if (!isBaryDefined)
  {
    BRepGProp::LinearProperties(W, GP);
    Bary = GP.CentreOfMass();
  }

  findPlanarSurf.Init(W, -1, true);
  if (findPlanarSurf.Found())
  {
    S = findPlanarSurf.Surface();
    L = findPlanarSurf.Location();
    if (!L.IsIdentity())
      S = occ::down_cast<Geom_Surface>(S->Transformed(L.Transformation()));
    P = (occ::down_cast<Geom_Plane>(S))->Pln();
    P.SetLocation(Bary);
  }
  else
  {

    GProp_PrincipalProps Pp = GP.PrincipalProperties();
    gp_Vec               Vec;
    double               R1, R2, R3, Tol = Precision::Confusion();
    Pp.RadiusOfGyration(R1, R2, R3);
    double RMax = std::max(std::max(R1, R2), R3);
    if ((std::abs(RMax - R1) < Tol && std::abs(RMax - R2) < Tol)
        || (std::abs(RMax - R1) < Tol && std::abs(RMax - R3) < Tol)
        || (std::abs(RMax - R2) < Tol && std::abs(RMax - R3) < Tol))
      isplane = false;
    else
    {
      if (R1 >= R2 && R1 >= R3)
      {
        Vec = Pp.FirstAxisOfInertia();
      }
      else if (R2 >= R1 && R2 >= R3)
      {
        Vec = Pp.SecondAxisOfInertia();
      }
      else if (R3 >= R1 && R3 >= R2)
      {
        Vec = Pp.ThirdAxisOfInertia();
      }
      gp_Dir NDir(Vec);
      if (R3 <= R2 && R3 <= R1)
      {
        Vec = Pp.ThirdAxisOfInertia();
      }
      else if (R2 <= R1 && R2 <= R3)
      {
        Vec = Pp.SecondAxisOfInertia();
      }
      else if (R1 <= R2 && R1 <= R3)
      {
        Vec = Pp.FirstAxisOfInertia();
      }
      gp_Dir     XDir(Vec);
      gp_Ax3     repere(Bary, NDir, XDir);
      Geom_Plane GPlan(repere);
      P = GPlan.Pln();
    }
  }

  return isplane;
}

static void WireContinuity(const TopoDS_Wire& W, GeomAbs_Shape& contW)
{
  contW = GeomAbs_CN;
  GeomAbs_Shape cont;
  bool          IsDegenerated = false;

  BRepTools_WireExplorer                           anExp;
  int                                              nbEdges = 0;
  occ::handle<NCollection_HSequence<TopoDS_Shape>> Edges =
    new NCollection_HSequence<TopoDS_Shape>();
  for (anExp.Init(W); anExp.More(); anExp.Next())
  {
    nbEdges++;
    Edges->Append(anExp.Current());
    if (BRep_Tool::Degenerated(anExp.Current()))
      IsDegenerated = true;
  }

  if (!IsDegenerated)
  {

    bool testconti = true;

    for (int j = 1; j <= nbEdges; j++)
    {

      TopoDS_Edge Edge1, Edge2;

      if (j == nbEdges)
      {
        Edge1 = TopoDS::Edge(Edges->Value(nbEdges));
        Edge2 = TopoDS::Edge(Edges->Value(1));
      }
      else
      {
        Edge1 = TopoDS::Edge(Edges->Value(j));
        Edge2 = TopoDS::Edge(Edges->Value(j + 1));
      }

      TopoDS_Vertex V1, V2, Vbid;
      TopExp::Vertices(Edge1, Vbid, V1, true);
      TopExp::Vertices(Edge2, V2, Vbid, true);
      double            U1 = BRep_Tool::Parameter(V1, Edge1);
      double            U2 = BRep_Tool::Parameter(V2, Edge2);
      BRepAdaptor_Curve Curve1(Edge1);
      BRepAdaptor_Curve Curve2(Edge2);
      double            Eps = BRep_Tool::Tolerance(V2) + BRep_Tool::Tolerance(V1);

      if (j == nbEdges)
        testconti = Curve1.Value(U1).IsEqual(Curve2.Value(U2), Eps);

      if (testconti)
      {
        cont = BRepLProp::Continuity(Curve1, Curve2, U1, U2, Eps, Precision::Angular());
        if (cont <= contW)
          contW = cont;
      }
    }
  }
}

static void TrimEdge(const TopoDS_Edge&                  CurrentEdge,
                     const NCollection_Sequence<double>& CutValues,
                     const double                        t0,
                     const double                        t1,
                     const bool                          SeqOrder,
                     NCollection_Sequence<TopoDS_Shape>& S)

{
  S.Clear();
  int                     j, ndec = CutValues.Length();
  double                  first, last, m0, m1;
  occ::handle<Geom_Curve> C = BRep_Tool::Curve(CurrentEdge, first, last);

  TopoDS_Vertex      Vf, Vl, Vbid, V0, V1;
  TopAbs_Orientation CurrentOrient = CurrentEdge.Orientation();
  TopExp::Vertices(CurrentEdge, Vf, Vl);
  Vbid.Nullify();

  if (SeqOrder)
  {

    m0 = first;
    V0 = Vf;
    for (j = 1; j <= ndec; j++)
    {

      m1 = (CutValues.Value(j) - t0) * (last - first) / (t1 - t0) + first;
      if (std::abs(m0 - m1) < Precision::Confusion())
      {
        return;
      }
      TopoDS_Edge CutE = BRepLib_MakeEdge(C, V0, Vbid, m0, m1);
      CutE.Orientation(CurrentOrient);
      S.Append(CutE);
      m0 = m1;
      V0 = TopExp::LastVertex(CutE);
      if (j == ndec)
      {

        if (std::abs(m0 - last) < Precision::Confusion())
        {
          return;
        }
        TopoDS_Edge LastE = BRepLib_MakeEdge(C, V0, Vl, m0, last);
        LastE.Orientation(CurrentOrient);
        S.Append(LastE);
      }
    }
  }
  else
  {

    m1 = last;
    V1 = Vl;
    for (j = ndec; j >= 1; j--)
    {

      m0 = (CutValues.Value(j) - t0) * (last - first) / (t1 - t0) + first;
      if (std::abs(m0 - m1) < Precision::Confusion())
      {
        return;
      }
      TopoDS_Edge CutE = BRepLib_MakeEdge(C, Vbid, V1, m0, m1);
      CutE.Orientation(CurrentOrient);
      S.Append(CutE);
      m1 = m0;
      V1 = TopExp::FirstVertex(CutE);
      if (j == 1)
      {

        if (std::abs(first - m1) < Precision::Confusion())
        {
          return;
        }
        TopoDS_Edge LastE = BRepLib_MakeEdge(C, Vf, V1, first, m1);
        LastE.Orientation(CurrentOrient);
        S.Append(LastE);
      }
    }
  }
}

static bool SearchRoot(
  const TopoDS_Vertex& V,
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                 Map,
  TopoDS_Vertex& VRoot)
{
  bool trouve = false;
  VRoot.Nullify();
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator it;
  for (it.Initialize(Map); it.More(); it.Next())
  {
    const NCollection_List<TopoDS_Shape>&    List = it.Value();
    NCollection_List<TopoDS_Shape>::Iterator itL;
    bool                                     ilyest = false;
    for (itL.Initialize(List); itL.More(); itL.Next())
    {
      TopoDS_Vertex Vcur = TopoDS::Vertex(itL.Value());
      if (Vcur.IsSame(V))
      {
        ilyest = true;
      }
      if (ilyest)
        break;
    }
    if (ilyest)
    {
      trouve = true;
      VRoot  = TopoDS::Vertex(it.Key());
    }
    if (trouve)
      break;
  }
  return trouve;
}

static bool SearchVertex(const NCollection_List<TopoDS_Shape>& List,
                         const TopoDS_Wire&                    W,
                         TopoDS_Vertex&                        VonW)
{
  bool trouve = false;
  VonW.Nullify();
  NCollection_Sequence<TopoDS_Shape> SeqV;
  SeqOfVertices(W, SeqV);
  for (int ii = 1; ii <= SeqV.Length(); ii++)
  {
    TopoDS_Vertex                            Vi = TopoDS::Vertex(SeqV.Value(ii));
    NCollection_List<TopoDS_Shape>::Iterator itL;
    bool                                     ilyest = false;
    for (itL.Initialize(List); itL.More(); itL.Next())
    {
      TopoDS_Vertex Vcur = TopoDS::Vertex(itL.Value());
      if (Vcur.IsSame(Vi))
      {
        ilyest = true;
      }
      if (ilyest)
        break;
    }
    if (ilyest)
    {
      trouve = true;
      VonW   = Vi;
    }
    if (trouve)
      break;
  }
  return trouve;
}

static bool EdgeIntersectOnWire(
  const gp_Pnt& P1,
  const gp_Pnt& P2,
  double        percent,
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                     Map,
  const TopoDS_Wire& W,
  TopoDS_Vertex&     Vsol,
  TopoDS_Wire&       newW,
  NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    theEdgeNewEdges)
{

  BRepTools_WireExplorer anExp;

  bool   NewVertex = false;
  gp_Lin droite(P1, gp_Dir(gp_Vec(P1, P2)));

  Bnd_Box B;
  BRepBndLib::Add(W, B);
  double x1, x2, y1, y2, z1, z2;
  B.Get(x1, y1, z1, x2, y2, z2);
  gp_Pnt           BP1(x1, y1, z1), BP2(x2, y2, z2);
  double           diag         = BP1.Distance(BP2);
  double           dernierparam = diag;
  BRepLib_MakeEdge ME(droite, 0., dernierparam);
  TopoDS_Edge      ECur = BRepLib_MakeEdge(droite, 0., P1.Distance(P2));

  BRepExtrema_DistShapeShape DSS(ME.Edge(), W);
  if (DSS.IsDone())
  {

    int    isol = 1;
    gp_Pnt Psol = DSS.PointOnShape2(isol);
    double dss  = P2.Distance(Psol);
    for (int iss = 2; iss <= DSS.NbSolution(); iss++)
    {
      gp_Pnt Pss   = DSS.PointOnShape2(iss);
      double aDist = P2.Distance(Pss);
      if (dss > aDist)
      {
        dss  = aDist;
        isol = iss;
#ifdef OCCT_DEBUG
        Psol = Pss;
#endif
      }
    }

    NewVertex = (DSS.SupportTypeShape2(isol) != BRepExtrema_IsVertex);
    if (NewVertex)
    {
      TopoDS_Edge E   = TopoDS::Edge(DSS.SupportOnShape2(isol));
      double      tol = Precision::PConfusion();
      double      first, last, param;
      BRep_Tool::Range(E, first, last);
      tol = std::max(tol, percent * std::abs(last - first));
      DSS.ParOnEdgeS2(isol, param);
      if (std::abs(first - param) < tol)
      {
        NewVertex = false;
        Vsol      = TopExp::FirstVertex(E);
      }
      else if (std::abs(last - param) < tol)
      {
        NewVertex = false;
        Vsol      = TopExp::LastVertex(E);
      }

      if (!NewVertex)
      {
        TopoDS_Vertex VRoot;
        if (SearchRoot(Vsol, Map, VRoot))
          NewVertex = true;
      }
    }
    else
    {
      TopoDS_Shape aLocalShape = DSS.SupportOnShape2(isol);
      Vsol                     = TopoDS::Vertex(aLocalShape);
    }

    if (NewVertex)
    {
      TopoDS_Shape aLocalShape = DSS.SupportOnShape2(isol);
      TopoDS_Edge  E           = TopoDS::Edge(aLocalShape);

      NCollection_Sequence<TopoDS_Shape> EmptySeq;
      theEdgeNewEdges.Bind(E, EmptySeq);
      double first, last, param;
      DSS.ParOnEdgeS2(isol, param);
      BRep_Tool::Range(E, first, last);
      BRepLib_MakeWire MW;
      for (anExp.Init(W); anExp.More(); anExp.Next())
      {
        if (E.IsSame(anExp.Current()))
        {
          bool SO = (anExp.CurrentVertex().IsSame(TopExp::FirstVertex(E)));
          NCollection_Sequence<TopoDS_Shape> SE;
          SE.Clear();
          NCollection_Sequence<double> SR;
          SR.Clear();
          SR.Append(param);
          TrimEdge(E, SR, first, last, SO, SE);
          if (SE.IsEmpty())
          {
            return false;
          }
          theEdgeNewEdges(E) = SE;
          TopoDS_Vertex VV1, VV2;
          TopExp::Vertices(TopoDS::Edge(SE.Value(1)), VV1, VV2);
          if (TopExp::FirstVertex(E).IsSame(VV1) || TopExp::LastVertex(E).IsSame(VV1))
          {
            Vsol = VV2;
          }
          if (TopExp::FirstVertex(E).IsSame(VV2) || TopExp::LastVertex(E).IsSame(VV2))
          {
            Vsol = VV1;
          }
          for (int k = 1; k <= SE.Length(); k++)
          {
            MW.Add(TopoDS::Edge(SE.Value(k)));
          }
        }
        else
        {
          MW.Add(anExp.Current());
        }
      }
      newW = MW.Wire();
    }
    else
    {
      newW = W;
    }
  }

  return NewVertex;
}

static void Transform(const bool    WithRotation,
                      const gp_Pnt& P,
                      const gp_Pnt& Pos1,
                      const gp_Vec& Ax1,
                      const gp_Pnt& Pos2,
                      const gp_Vec& Ax2,
                      gp_Pnt&       Pnew)
{

  Pnew        = P.Translated(Pos1, Pos2);
  gp_Vec axe1 = Ax1, axe2 = Ax2;
  if (!axe1.IsParallel(axe2, 1.e-4))
  {
    gp_Vec Vtrans(Pos1, Pos2), Vsign;
    double alpha, beta, sign = 1;
    alpha = Vtrans.Dot(axe1);
    beta  = Vtrans.Dot(axe2);
    if (alpha < -1.e-7)
      axe1 *= -1;
    if (beta < 1.e-7)
      axe2 *= -1;
    alpha        = Vtrans.Dot(axe1);
    beta         = Vtrans.Dot(axe2);
    gp_Vec norm2 = axe1 ^ axe2;
    Vsign.SetLinearForm(Vtrans.Dot(axe1), axe2, -Vtrans.Dot(axe2), axe1);
    alpha       = Vsign.Dot(axe1);
    beta        = Vsign.Dot(axe2);
    bool pasnul = (std::abs(alpha) > 1.e-4 && std::abs(beta) > 1.e-4);
    if (alpha * beta > 0.0 && pasnul)
      sign = -1;
    gp_Ax1 Norm(Pos2, norm2);
    double ang = axe1.AngleWithRef(axe2, norm2);
    if (!WithRotation)
    {
      if (ang > M_PI / 2)
        ang = ang - M_PI;
      if (ang < -M_PI / 2)
        ang = ang + M_PI;
    }
    ang *= sign;
    Pnew = Pnew.Rotated(Norm, ang);
  }
}

static void BuildConnectedEdges(const TopoDS_Wire&              aWire,
                                const TopoDS_Edge&              StartEdge,
                                const TopoDS_Vertex&            StartVertex,
                                NCollection_List<TopoDS_Shape>& ConnectedEdges)
{
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    MapVE;
  TopExp::MapShapesAndAncestors(aWire, TopAbs_VERTEX, TopAbs_EDGE, MapVE);
  TopoDS_Edge   CurEdge   = StartEdge;
  TopoDS_Vertex CurVertex = StartVertex;
  TopoDS_Vertex Origin, V1, V2;
  TopExp::Vertices(StartEdge, V1, V2);
  Origin = (V1.IsSame(StartVertex)) ? V2 : V1;

  for (;;)
  {
    NCollection_List<TopoDS_Shape>::Iterator itE(MapVE.FindFromKey(CurVertex));
    for (; itE.More(); itE.Next())
    {
      TopoDS_Edge anEdge = TopoDS::Edge(itE.Value());
      if (!anEdge.IsSame(CurEdge))
      {
        ConnectedEdges.Append(anEdge);
        TopExp::Vertices(anEdge, V1, V2);
        CurVertex = (V1.IsSame(CurVertex)) ? V2 : V1;
        CurEdge   = anEdge;
        break;
      }
    }
    if (CurVertex.IsSame(Origin))
      break;
  }
}

BRepFill_CompatibleWires::BRepFill_CompatibleWires()
    : myStatus(BRepFill_ThruSectionErrorStatus_NotDone)
{
}

BRepFill_CompatibleWires::BRepFill_CompatibleWires(
  const NCollection_Sequence<TopoDS_Shape>& Sections)
{
  Init(Sections);
}

void BRepFill_CompatibleWires::Init(const NCollection_Sequence<TopoDS_Shape>& Sections)
{
  myInit    = Sections;
  myWork    = Sections;
  myPercent = 0.1;
  myStatus  = BRepFill_ThruSectionErrorStatus_NotDone;
  myMap.Clear();
}

void BRepFill_CompatibleWires::SetPercent(const double Percent)
{
  if (0. < Percent && Percent < 1.)
    myPercent = Percent;
}

bool BRepFill_CompatibleWires::IsDone() const
{
  return myStatus == BRepFill_ThruSectionErrorStatus_Done;
}

const NCollection_Sequence<TopoDS_Shape>& BRepFill_CompatibleWires::Shape() const
{
  return myWork;
}

const NCollection_List<TopoDS_Shape>& BRepFill_CompatibleWires::GeneratedShapes(
  const TopoDS_Edge& SubSection) const
{

  if (myMap.IsBound(SubSection))
  {
    return myMap(SubSection);
  }
  else
  {
    static NCollection_List<TopoDS_Shape> Empty;
    return Empty;
  }
}

bool BRepFill_CompatibleWires::IsDegeneratedFirstSection() const
{
  return myDegen1;
}

bool BRepFill_CompatibleWires::IsDegeneratedLastSection() const
{
  return myDegen2;
}

void BRepFill_CompatibleWires::Perform(const bool WithRotation)
{
  myStatus = BRepFill_ThruSectionErrorStatus_Done;

  int                     nbSects = myWork.Length(), i;
  BRepTools_WireExplorer  anExp;
  int                     nbmax = 0, nbmin = 0;
  NCollection_Array1<int> nbEdges(1, nbSects);
  bool                    report;
  GeomAbs_Shape           contS = GeomAbs_CN;
  GeomAbs_Shape           cont;
  for (i = 1; i <= nbSects; i++)
  {
    TopoDS_Shape aLocalShape = myWork(i).Oriented(TopAbs_FORWARD);
    myWork(i)                = TopoDS::Wire(aLocalShape);

    TopoDS_Wire W = TopoDS::Wire(myWork(i));
    WireContinuity(W, cont);
    if (cont < contS)
      contS = cont;
    nbEdges(i) = 0;
    for (anExp.Init(W); anExp.More(); anExp.Next())
      nbEdges(i)++;
    if (i == 1)
      nbmin = nbEdges(i);
    if (nbmax < nbEdges(i))
      nbmax = nbEdges(i);
    if (nbmin > nbEdges(i))
      nbmin = nbEdges(i);
  }

  report = (nbmax != nbmin || contS >= GeomAbs_C1);

  NCollection_List<TopoDS_Shape> Empty;
  for (i = 1; i <= nbSects; i++)
  {
    TopoDS_Wire W = TopoDS::Wire(myWork(i));
    for (anExp.Init(W); anExp.More(); anExp.Next())
    {
      TopoDS_Edge E = TopoDS::Edge(anExp.Current());
      myMap.Bind(E, Empty);
      myMap(E).Append(E);
    }
  }

  int ideb = 1, ifin = myWork.Length();

  myDegen1 = true;
  for (anExp.Init(TopoDS::Wire(myWork(ideb))); anExp.More(); anExp.Next())
  {
    myDegen1 = myDegen1 && (BRep_Tool::Degenerated(anExp.Current()));
  }
  if (myDegen1)
    ideb++;

  myDegen2 = true;
  for (anExp.Init(TopoDS::Wire(myWork(ifin))); anExp.More(); anExp.Next())
  {
    myDegen2 = myDegen2 && (BRep_Tool::Degenerated(anExp.Current()));
  }
  if (myDegen2)
    ifin--;

  bool wClosed, allClosed = true, allOpen = true;
  for (i = ideb; i <= ifin; i++)
  {
    wClosed = myWork(i).Closed();
    if (!wClosed)
    {

      TopoDS_Vertex V1, V2;
      TopExp::Vertices(TopoDS::Wire(myWork(i)), V1, V2);
      if (V1.IsSame(V2))
        wClosed = true;
    }
    allClosed = (allClosed && wClosed);
    allOpen   = (allOpen && !wClosed);
  }

  if (allClosed)
  {

    if (report)
    {

      SameNumberByPolarMethod(WithRotation);
    }
    else
    {

      ComputeOrigin(false);
    }
  }
  else if (allOpen)
  {

    SearchOrigin();
    if (myStatus != BRepFill_ThruSectionErrorStatus_Done)
    {
      return;
    }

    if (report)
    {
      SameNumberByACR(report);
    }
  }
  else
  {

    myStatus = BRepFill_ThruSectionErrorStatus_NotSameTopology;
    return;
  }
}

const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
  BRepFill_CompatibleWires::Generated() const
{
  return myMap;
}

void BRepFill_CompatibleWires::SameNumberByPolarMethod(const bool WithRotation)
{

  int                    NbSects = myWork.Length();
  BRepTools_WireExplorer anExp;
  NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<TopoDS_Shape>, TopTools_ShapeMapHasher>
    EdgeNewEdges;

  bool allClosed = true;
  int  i, ii, ideb = 1, ifin = NbSects;

  for (i = 1; i <= NbSects; i++)
  {
    occ::handle<BRepCheck_Wire> Checker = new BRepCheck_Wire(TopoDS::Wire(myWork(i)));
    allClosed                           = (allClosed && (Checker->Closed() == BRepCheck_NoError));
  }
  if (!allClosed)
  {
    myStatus = BRepFill_ThruSectionErrorStatus_NotSameTopology;
    return;
  }

  if (myDegen1)
    ideb++;
  if (myDegen2)
    ifin--;
  bool vClosed = (!myDegen1) && (!myDegen2) && (myWork(ideb).IsSame(myWork(ifin)));

  for (i = ideb; i <= ifin; i++)
  {
    bool            hasDegEdge = false;
    TopoDS_Iterator anItw(myWork(i));
    for (; anItw.More(); anItw.Next())
    {
      const TopoDS_Edge& anEdge = TopoDS::Edge(anItw.Value());
      if (BRep_Tool::Degenerated(anEdge))
      {
        hasDegEdge = true;
        break;
      }
    }
    if (hasDegEdge)
    {
      TopoDS_Wire  aNewWire;
      BRep_Builder aBBuilder;
      aBBuilder.MakeWire(aNewWire);
      for (anItw.Initialize(myWork(i)); anItw.More(); anItw.Next())
      {
        const TopoDS_Edge& anEdge = TopoDS::Edge(anItw.Value());
        if (!BRep_Tool::Degenerated(anEdge))
          aBBuilder.Add(aNewWire, anEdge);
      }
      myWork(i) = aNewWire;
    }
  }

  int NbMaxV = 0;
  for (i = 1; i <= NbSects; i++)
  {
    for (anExp.Init(TopoDS::Wire(myWork(i))); anExp.More(); anExp.Next())
    {
      NbMaxV++;
    }
  }

  gp_Pln                                   P;
  occ::handle<NCollection_HArray1<gp_Pnt>> Pos = new (NCollection_HArray1<gp_Pnt>)(1, NbSects);
  occ::handle<NCollection_HArray1<gp_Vec>> Axe = new (NCollection_HArray1<gp_Vec>)(1, NbSects);
  for (i = ideb; i <= ifin; i++)
  {
    if (PlaneOfWire(TopoDS::Wire(myWork(i)), P))
    {
      Pos->SetValue(i, P.Location());
      Axe->SetValue(i, gp_Vec(P.Axis().Direction()));
    }
  }
  NCollection_Sequence<TopoDS_Shape> SeqV;
  if (myDegen1)
  {
    SeqOfVertices(TopoDS::Wire(myWork(1)), SeqV);
    Pos->SetValue(1, BRep_Tool::Pnt(TopoDS::Vertex(SeqV.Value(1))));
    Axe->SetValue(1, Axe->Value(ideb));
  }
  if (myDegen2)
  {
    SeqOfVertices(TopoDS::Wire(myWork(NbSects)), SeqV);
    Pos->SetValue(NbSects, BRep_Tool::Pnt(TopoDS::Vertex(SeqV.Value(1))));
    Axe->SetValue(NbSects, Axe->Value(ifin));
  }

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> RMap;
  RMap.Clear();

  for (i = ifin; i > ideb; i--)
  {

    const TopoDS_Wire& wire1 = TopoDS::Wire(myWork(i));

    SeqOfVertices(wire1, SeqV);
    if (SeqV.Length() > NbMaxV)
    {
      myStatus = BRepFill_ThruSectionErrorStatus_Failed;
      return;
    }

    for (ii = 1; ii <= SeqV.Length(); ii++)
    {

      TopoDS_Vertex Vi = TopoDS::Vertex(SeqV.Value(ii));

      NCollection_List<TopoDS_Shape> Init;
      Init.Clear();
      RMap.Bind(Vi, Init);

      gp_Pnt Pi = BRep_Tool::Pnt(Vi);

      gp_Pnt Pnew;
      Transform(WithRotation,
                Pi,
                Pos->Value(i),
                Axe->Value(i),
                Pos->Value(i - 1),
                Axe->Value(i - 1),
                Pnew);

      TopoDS_Shape  Support;
      bool          NewVertex;
      TopoDS_Vertex Vsol;
      TopoDS_Wire   newwire;
      if (Pnew.Distance(Pos->Value(i - 1)) > Precision::Confusion())
      {
        double percent = myPercent;
        NewVertex      = EdgeIntersectOnWire(Pos->Value(i - 1),
                                        Pnew,
                                        percent,
                                        RMap,
                                        TopoDS::Wire(myWork(i - 1)),
                                        Vsol,
                                        newwire,
                                        EdgeNewEdges);
        if (NewVertex)
          myWork(i - 1) = newwire;
        RMap(Vi).Append(Vsol);
      }
    }
  }

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> MapVLV;
  SeqOfVertices(TopoDS::Wire(myWork(ideb)), SeqV);
  int SizeMap = SeqV.Length();
  MapVLV.Clear();
  for (ii = 1; ii <= SizeMap; ii++)
  {
    TopoDS_Vertex                  Vi = TopoDS::Vertex(SeqV.Value(ii));
    NCollection_List<TopoDS_Shape> Init;
    Init.Clear();
    Init.Append(Vi);
    MapVLV.Bind(Vi, Init);
    int           NbV = 1;
    TopoDS_Vertex V0, V1;
    V0           = Vi;
    bool tantque = SearchRoot(V0, RMap, V1);
    while (tantque)
    {
      MapVLV(Vi).Append(V1);
      NbV++;

      if (V1.IsSame(Vi) || NbV >= myWork.Length())
      {
        tantque = false;
      }
      else
      {
        V0      = V1;
        tantque = SearchRoot(V0, RMap, V1);
      }
    }
  }

  for (i = ideb; i < ifin; i++)
  {

    const TopoDS_Wire& wire1 = TopoDS::Wire(myWork(i));

    SeqOfVertices(wire1, SeqV);
    if (SeqV.Length() > NbMaxV || SeqV.Length() > SizeMap)
    {
      myStatus = BRepFill_ThruSectionErrorStatus_Failed;
      return;
    }

    const TopoDS_Wire& wire2 = TopoDS::Wire(myWork(i + 1));

    for (ii = 1; ii <= SeqV.Length(); ii++)
    {

      TopoDS_Vertex Vi = TopoDS::Vertex(SeqV.Value(ii));
      TopoDS_Vertex VRoot;
      VRoot.Nullify();
      bool intersect = true;
      if (SearchRoot(Vi, MapVLV, VRoot))
      {
        const NCollection_List<TopoDS_Shape>& LVi = MapVLV(VRoot);
        TopoDS_Vertex                         VonW;
        VonW.Nullify();
        intersect = (!SearchVertex(LVi, wire2, VonW));
      }

      if (intersect)
      {

        gp_Pnt Pi = BRep_Tool::Pnt(Vi);

        gp_Pnt Pnew;
        Transform(WithRotation,
                  Pi,
                  Pos->Value(i),
                  Axe->Value(i),
                  Pos->Value(i + 1),
                  Axe->Value(i + 1),
                  Pnew);

        TopoDS_Shape  Support;
        bool          NewVertex;
        TopoDS_Vertex Vsol;
        TopoDS_Wire   newwire;
        if (Pnew.Distance(Pos->Value(i + 1)) > Precision::Confusion())
        {
          double percent = myPercent;
          NewVertex      = EdgeIntersectOnWire(Pos->Value(i + 1),
                                          Pnew,
                                          percent,
                                          MapVLV,
                                          TopoDS::Wire(myWork(i + 1)),
                                          Vsol,
                                          newwire,
                                          EdgeNewEdges);
          MapVLV(VRoot).Append(Vsol);
          if (NewVertex)
            myWork(i + 1) = newwire;
        }
      }
    }
  }

  TopoDS_Wire wire = TopoDS::Wire(myWork(ideb));

  int ibout = ifin;
  if (vClosed)
    ibout--;

  for (i = ideb + 1; i <= ibout; i++)
  {

    BRepLib_MakeWire MW;

    anExp.Init(wire);
    TopoDS_Edge   ECur = anExp.Current();
    TopoDS_Vertex VF, VL;
    TopExp::Vertices(ECur, VF, VL, true);
    double                                   U1 = BRep_Tool::Parameter(VF, ECur);
    double                                   U2 = BRep_Tool::Parameter(VL, ECur);
    BRepAdaptor_Curve                        Curve(ECur);
    gp_Pnt                                   PPs = Curve.Value(0.1 * (U1 + 9 * U2));
    NCollection_List<TopoDS_Shape>::Iterator itF(MapVLV(VF)), itL(MapVLV(VL));
    int                                      rang = ideb;
    while (rang < i)
    {
      itF.Next();
      itL.Next();
      rang++;
    }
    TopoDS_Vertex   V1 = TopoDS::Vertex(itF.Value()), V2 = TopoDS::Vertex(itL.Value());
    TopoDS_Edge     Esol;
    double          scalmax = 0.;
    TopoDS_Iterator itW(myWork(i));

    for (; itW.More(); itW.Next())
    {
      TopoDS_Edge   E = TopoDS::Edge(itW.Value());
      TopoDS_Vertex VVF, VVL;
      TopExp::Vertices(E, VVF, VVL, true);

      double scal1, scal2;
      if ((V1.IsSame(VVF) && V2.IsSame(VVL)) || (V2.IsSame(VVF) && V1.IsSame(VVL)))
      {
        double            U1param = BRep_Tool::Parameter(VVF, E);
        double            U2param = BRep_Tool::Parameter(VVL, E);
        BRepAdaptor_Curve CurveE(E);
        gp_Pnt            PP1 = CurveE.Value(0.1 * (U1param + 9 * U2param));
        gp_Pnt            PP2 = CurveE.Value(0.1 * (9 * U1param + U2param));

        for (rang = i; rang > ideb; rang--)
        {
          Transform(WithRotation,
                    PP1,
                    Pos->Value(rang),
                    Axe->Value(rang),
                    Pos->Value(rang - 1),
                    Axe->Value(rang - 1),
                    PP1);
          Transform(WithRotation,
                    PP2,
                    Pos->Value(rang),
                    Axe->Value(rang),
                    Pos->Value(rang - 1),
                    Axe->Value(rang - 1),
                    PP2);
        }
        gp_Vec Ns(Pos->Value(ideb), PPs);
        Ns = Ns.Normalized();
        gp_Vec N1(Pos->Value(ideb), PP1);
        N1 = N1.Normalized();
        gp_Vec N2(Pos->Value(ideb), PP2);
        N2    = N2.Normalized();
        scal1 = N1.Dot(Ns);
        if (scal1 > scalmax)
        {
          scalmax = scal1;
          Esol    = E;
        }
        scal2 = N2.Dot(Ns);
        if (scal2 > scalmax)
        {
          scalmax                  = scal2;
          TopoDS_Shape aLocalShape = E.Reversed();
          Esol                     = TopoDS::Edge(aLocalShape);
        }
      }
    }
    if (Esol.IsNull())
    {
      myStatus = BRepFill_ThruSectionErrorStatus_ProfilesInconsistent;
      return;
    }
    MW.Add(Esol);

    NCollection_List<TopoDS_Shape> ConnectedEdges;
    BuildConnectedEdges(TopoDS::Wire(myWork(i)), Esol, V2, ConnectedEdges);

    NCollection_List<TopoDS_Shape>::Iterator itCE(ConnectedEdges);
    for (; anExp.More() && itCE.More(); anExp.Next(), itCE.Next())
    {
      ECur = anExp.Current();
      TopExp::Vertices(ECur, VF, VL, true);
      U1 = BRep_Tool::Parameter(VF, ECur);
      U2 = BRep_Tool::Parameter(VL, ECur);
      Curve.Initialize(ECur);
      PPs = Curve.Value(0.1 * (U1 + 9 * U2));

      TopoDS_Edge   E = TopoDS::Edge(itCE.Value());
      TopoDS_Vertex VVF, VVL;
      TopExp::Vertices(E, VVF, VVL, true);

      double scal1, scal2;
      U1 = BRep_Tool::Parameter(VVF, E);
      U2 = BRep_Tool::Parameter(VVL, E);
      Curve.Initialize(E);
      gp_Pnt PP1 = Curve.Value(0.1 * (U1 + 9 * U2));
      gp_Pnt PP2 = Curve.Value(0.1 * (9 * U1 + U2));

      for (rang = i; rang > ideb; rang--)
      {
        Transform(WithRotation,
                  PP1,
                  Pos->Value(rang),
                  Axe->Value(rang),
                  Pos->Value(rang - 1),
                  Axe->Value(rang - 1),
                  PP1);
        Transform(WithRotation,
                  PP2,
                  Pos->Value(rang),
                  Axe->Value(rang),
                  Pos->Value(rang - 1),
                  Axe->Value(rang - 1),
                  PP2);
      }
      gp_Vec Ns(Pos->Value(ideb), PPs);
      Ns = Ns.Normalized();
      gp_Vec N1(Pos->Value(ideb), PP1);
      N1 = N1.Normalized();
      gp_Vec N2(Pos->Value(ideb), PP2);
      N2    = N2.Normalized();
      scal1 = N1.Dot(Ns);
      scal2 = N2.Dot(Ns);
      if (scal2 > scal1)
        E.Reverse();
      MW.Add(E);
    }
    myWork(i) = MW.Wire();
  }

  if (vClosed)
  {
    TopoDS_Iterator iter1(myWork(myWork.Length())), iter2(myWork(1));
    for (; iter1.More(); iter1.Next(), iter2.Next())
    {
      const TopoDS_Shape& anEdge   = iter1.Value();
      const TopoDS_Shape& aNewEdge = iter2.Value();
      if (!anEdge.IsSame(aNewEdge))
      {
        NCollection_Sequence<TopoDS_Shape> aSeq;
        aSeq.Append(aNewEdge);
        EdgeNewEdges.Bind(anEdge, aSeq);
      }
    }
    myWork(myWork.Length()) = myWork(1);
  }

  int nbmax = 0, nbmin = 0;
  for (i = ideb; i <= ifin; i++)
  {
    int nbEdges = 0;
    for (anExp.Init(TopoDS::Wire(myWork(i))); anExp.More(); anExp.Next())
    {
      nbEdges++;
    }
    if (i == ideb)
      nbmin = nbEdges;
    if (nbmax < nbEdges)
      nbmax = nbEdges;
    if (nbmin > nbEdges)
      nbmin = nbEdges;
  }
  if (nbmin != nbmax)
  {
    myStatus = BRepFill_ThruSectionErrorStatus_Failed;
    return;
  }

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator itmap(myMap);
  for (; itmap.More(); itmap.Next())
  {
    const TopoDS_Shape&            anEdge = itmap.Key();
    NCollection_List<TopoDS_Shape> ListOfNewEdges;

    AddNewEdge(anEdge, EdgeNewEdges, ListOfNewEdges);

    myMap(anEdge) = ListOfNewEdges;
  }
}

void BRepFill_CompatibleWires::SameNumberByACR(const bool report)
{

  int                    ideb = 1, ifin = myWork.Length();
  BRepTools_WireExplorer anExp;

  if (myDegen1)
    ideb++;
  if (myDegen2)
    ifin--;
  bool vClosed = (!myDegen1) && (!myDegen2) && (myWork(ideb).IsSame(myWork(ifin)));

  int                     nbSects = myWork.Length(), i;
  int                     nbmax = 0, nbmin = 0;
  NCollection_Array1<int> nbEdges(1, nbSects);
  for (i = 1; i <= nbSects; i++)
  {
    nbEdges(i) = 0;
    for (anExp.Init(TopoDS::Wire(myWork(i))); anExp.More(); anExp.Next())
    {
      nbEdges(i)++;
    }
    if (i == 1)
      nbmin = nbEdges(i);
    if (nbmax < nbEdges(i))
      nbmax = nbEdges(i);
    if (nbmin > nbEdges(i))
      nbmin = nbEdges(i);
  }

  if (nbmax > 1)
  {

    if (report || nbmin < nbmax)
    {

      int                        nbdec = (nbmax - 1) * nbSects + 1;
      NCollection_Array1<double> dec(1, nbdec);
      dec.Init(0);
      dec(2) = 1;

      NCollection_Array1<double> WireLen(1, nbSects);

      int j, k, l;
      for (i = 1; i <= nbSects; i++)
      {

        const TopoDS_Wire& wire1 = TopoDS::Wire(myWork(i));
        int                nbE   = 0;
        for (anExp.Init(wire1); anExp.More(); anExp.Next())
        {
          nbE++;
        }

        NCollection_Array1<double> ACR(0, nbE);
        ACR.Init(0);
        BRepFill::ComputeACR(wire1, ACR);
        WireLen(i) = ACR(0);

        for (j = 1; j < ACR.Length() - 1; j++)
        {
          k = 1;
          while (dec(k) < ACR(j))
          {
            k++;
            if (k > nbdec)
              break;
          }
          if (dec(k - 1) < ACR(j) && ACR(j) < dec(k))
          {
            for (l = nbdec - 1; l >= k; l--)
            {
              dec(l + 1) = dec(l);
            }
            dec(k) = ACR(j);
          }
        }
      }

      k = 1;
      while (dec(k) < 1)
      {
        k++;
        if (k > nbdec)
          break;
      }
      nbdec = k - 1;
      NCollection_Array1<double> dec2(1, nbdec);
      for (k = 1; k <= nbdec; k++)
      {
        dec2(k) = dec(k);
      }

      NCollection_Map<int> CutsToRemove;
      for (k = 1; k <= nbdec; k++)
      {
        double Knot1          = dec2(k);
        double Knot2          = (k == nbdec) ? 1. : dec2(k + 1);
        double AllLengthsNull = true;
        for (i = 1; i <= nbSects; i++)
        {
          double EdgeLen = (Knot2 - Knot1) * WireLen(i);
          if (EdgeLen > Precision::Confusion())
          {
            AllLengthsNull = false;
            break;
          }
        }
        if (AllLengthsNull)
          CutsToRemove.Add(k);
      }
      int                        NewNbDec = nbdec - CutsToRemove.Extent();
      NCollection_Array1<double> dec3(1, NewNbDec);
      i = 1;
      for (k = 1; k <= nbdec; k++)
        if (!CutsToRemove.Contains(k))
          dec3(i++) = dec2(k);

      for (i = 1; i <= nbSects; i++)
      {
        const TopoDS_Wire& oldwire = TopoDS::Wire(myWork(i));
        double             tol     = Precision::Confusion();
        if (WireLen(i) > gp::Resolution())
          tol /= WireLen(i);
        TopoDS_Wire            newwire = BRepFill::InsertACR(oldwire, dec3, tol);
        BRepTools_WireExplorer anExp1, anExp2;
        anExp1.Init(oldwire);
        anExp2.Init(newwire);
        for (; anExp1.More(); anExp1.Next())
        {
          const TopoDS_Edge& Ecur = anExp1.Current();
          if (!Ecur.IsSame(TopoDS::Edge(anExp2.Current())))
          {
            NCollection_List<TopoDS_Shape> LE;
            LE.Clear();
            gp_Pnt               P1, P2;
            const TopoDS_Vertex& V1 = anExp1.CurrentVertex();
            TopoDS_Vertex        VF, VR;
            TopExp::Vertices(Ecur, VF, VR, true);
            if (V1.IsSame(VF))
              P1 = BRep_Tool::Pnt(VR);
            if (V1.IsSame(VR))
              P1 = BRep_Tool::Pnt(VF);
            TopoDS_Vertex V2 = anExp2.CurrentVertex();
            TopExp::Vertices(TopoDS::Edge(anExp2.Current()), VF, VR, true);
            if (V2.IsSame(VF))
              P2 = BRep_Tool::Pnt(VR);
            if (V2.IsSame(VR))
              P2 = BRep_Tool::Pnt(VF);
            while (P1.Distance(P2) > 1.e-3)
            {
              LE.Append(anExp2.Current());
              anExp2.Next();
              V2 = anExp2.CurrentVertex();
              TopExp::Vertices(TopoDS::Edge(anExp2.Current()), VF, VR, true);
              if (V2.IsSame(VF))
                P2 = BRep_Tool::Pnt(VR);
              if (V2.IsSame(VR))
                P2 = BRep_Tool::Pnt(VF);
              if (P1.Distance(P2) <= 1.e-3)
              {
                LE.Append(anExp2.Current());
                anExp2.Next();
              }
            }

            NCollection_DataMap<TopoDS_Shape,
                                NCollection_List<TopoDS_Shape>,
                                TopTools_ShapeMapHasher>::Iterator itmap;

            TopoDS_Edge Ancestor;
            bool        found = false;

            for (itmap.Initialize(myMap); itmap.More() && (!found); itmap.Next())
            {
              NCollection_List<TopoDS_Shape>::Iterator itlist(itmap.Value());
              while (itlist.More() && (!found))
              {
                TopoDS_Edge ECur = TopoDS::Edge(itlist.Value());

                if (Ecur.IsSame(ECur))
                {
                  Ancestor = TopoDS::Edge(itmap.Key());
                  found    = true;
                  myMap(Ancestor).InsertBefore(LE, itlist);
                  myMap(Ancestor).Remove(itlist);
                }
                if (itlist.More())
                  itlist.Next();
              }
            }
          }
          else
          {
            anExp2.Next();
          }
        }
        myWork(i) = newwire;
      }
    }
  }

  if (vClosed)
    myWork(myWork.Length()) = myWork(1);

  nbmax = 0;
  for (i = ideb; i <= ifin; i++)
  {
    nbEdges(i) = 0;
    for (anExp.Init(TopoDS::Wire(myWork(i))); anExp.More(); anExp.Next())
    {
      nbEdges(i)++;
    }
    if (i == ideb)
      nbmin = nbEdges(i);
    if (nbmax < nbEdges(i))
      nbmax = nbEdges(i);
    if (nbmin > nbEdges(i))
      nbmin = nbEdges(i);
  }
  if (nbmax != nbmin)
  {
    myStatus = BRepFill_ThruSectionErrorStatus_Failed;
    return;
  }
}

void BRepFill_CompatibleWires::ComputeOrigin(const bool)
{

  TopoDS_Vertex Vdeb, Vfin;

  BRepTools_WireExplorer anExp;

  bool wClosed, allClosed = true;

  int NbSects = myWork.Length();
  int i, ideb = 1, ifin = NbSects;

  if (myDegen1)
    ideb++;
  if (myDegen2)
    ifin--;
  bool vClosed = (!myDegen1) && (!myDegen2) && (myWork(ideb).IsSame(myWork(ifin)));

  for (i = ideb; i <= ifin; i++)
  {
    wClosed = myWork(i).Closed();
    if (!wClosed)
    {

      TopoDS_Vertex V1, V2;
      TopExp::Vertices(TopoDS::Wire(myWork(i)), V1, V2);
      if (V1.IsSame(V2))
        wClosed = true;
    }
    allClosed = (allClosed && wClosed);
  }

  if (!allClosed)
  {
    myStatus = BRepFill_ThruSectionErrorStatus_NotSameTopology;
    return;
  }

  NCollection_Sequence<TopoDS_Shape> PrevSeq;
  NCollection_Sequence<TopoDS_Shape> PrevEseq;
  int                                theLength = 0;
  const TopoDS_Wire&                 wire      = TopoDS::Wire(myWork(ideb));
  for (anExp.Init(wire); anExp.More(); anExp.Next())
  {
    PrevSeq.Append(anExp.CurrentVertex());
    PrevEseq.Append(anExp.Current());
    theLength++;
  }

  int nbs, NbSamples = 0;
  if (theLength <= 2)
    NbSamples = 4;
  gp_Pln FirstPlane;
  PlaneOfWire(TopoDS::Wire(myWork(ideb)), FirstPlane);
  gp_Pnt PrevBary           = FirstPlane.Location();
  gp_Vec NormalOfFirstPlane = FirstPlane.Axis().Direction();
  for (i = ideb + 1; i <= ifin; i++)
  {
    const TopoDS_Wire& aWire = TopoDS::Wire(myWork(i));

    gp_Pln CurPlane;
    PlaneOfWire(aWire, CurPlane);
    gp_Pnt CurBary = CurPlane.Location();
    gp_Vec aVec(PrevBary, CurBary);
    gp_Vec anOffsetProj = (aVec * NormalOfFirstPlane) * NormalOfFirstPlane;
    CurBary.Translate(-anOffsetProj);
    gp_Vec Offset(CurBary, PrevBary);

    TopoDS_Wire  newwire;
    BRep_Builder BB;
    BB.MakeWire(newwire);

    NCollection_Sequence<TopoDS_Shape> SeqVertices, SeqEdges;
    for (anExp.Init(aWire); anExp.More(); anExp.Next())
    {
      SeqVertices.Append(anExp.CurrentVertex());
      SeqEdges.Append(anExp.Current());
    }

    double MinSumDist = Precision::Infinite();
    int    jmin       = 1, j, k, n;
    bool   forward    = false;
    if (i == myWork.Length() && myDegen2)
    {

      jmin    = 1;
      forward = true;
    }
    else
      for (j = 1; j <= theLength; j++)
      {

        double SumDist = 0.;
        for (k = j, n = 1; k <= theLength; k++, n++)
        {
          const TopoDS_Vertex& Vprev = TopoDS::Vertex(PrevSeq(n));
          gp_Pnt               Pprev = BRep_Tool::Pnt(Vprev);
          const TopoDS_Vertex& V     = TopoDS::Vertex(SeqVertices(k));
          gp_Pnt               P     = BRep_Tool::Pnt(V).XYZ() + Offset.XYZ();
          SumDist += Pprev.Distance(P);
          if (NbSamples > 0)
          {
            const TopoDS_Edge& PrevEdge = TopoDS::Edge(PrevEseq(n));
            const TopoDS_Edge& CurEdge  = TopoDS::Edge(SeqEdges(k));
            BRepAdaptor_Curve  PrevEcurve(PrevEdge);
            BRepAdaptor_Curve  Ecurve(CurEdge);
            double             SampleOnPrev =
              (PrevEcurve.LastParameter() - PrevEcurve.FirstParameter()) / NbSamples;
            double SampleOnCur = (Ecurve.LastParameter() - Ecurve.FirstParameter()) / NbSamples;
            for (nbs = 1; nbs <= NbSamples - 1; nbs++)
            {
              double ParOnPrev =
                (PrevEdge.Orientation() == TopAbs_FORWARD)
                  ? (PrevEcurve.FirstParameter() + nbs * SampleOnPrev)
                  : (PrevEcurve.FirstParameter() + (NbSamples - nbs) * SampleOnPrev);
              double ParOnCur = (CurEdge.Orientation() == TopAbs_FORWARD)
                                  ? (Ecurve.FirstParameter() + nbs * SampleOnCur)
                                  : (Ecurve.FirstParameter() + (NbSamples - nbs) * SampleOnCur);
              gp_Pnt PonPrev  = PrevEcurve.Value(ParOnPrev);
              gp_Pnt PonCur   = Ecurve.Value(ParOnCur).XYZ() + Offset.XYZ();
              SumDist += PonPrev.Distance(PonCur);
            }
          }
        }
        for (k = 1; k < j; k++, n++)
        {
          const TopoDS_Vertex& Vprev = TopoDS::Vertex(PrevSeq(n));
          gp_Pnt               Pprev = BRep_Tool::Pnt(Vprev);
          const TopoDS_Vertex& V     = TopoDS::Vertex(SeqVertices(k));
          gp_Pnt               P     = BRep_Tool::Pnt(V).XYZ() + Offset.XYZ();
          SumDist += Pprev.Distance(P);
          if (NbSamples > 0)
          {
            const TopoDS_Edge& PrevEdge = TopoDS::Edge(PrevEseq(n));
            const TopoDS_Edge& CurEdge  = TopoDS::Edge(SeqEdges(k));
            BRepAdaptor_Curve  PrevEcurve(PrevEdge);
            BRepAdaptor_Curve  Ecurve(CurEdge);
            double             SampleOnPrev =
              (PrevEcurve.LastParameter() - PrevEcurve.FirstParameter()) / NbSamples;
            double SampleOnCur = (Ecurve.LastParameter() - Ecurve.FirstParameter()) / NbSamples;
            for (nbs = 1; nbs <= NbSamples - 1; nbs++)
            {
              double ParOnPrev =
                (PrevEdge.Orientation() == TopAbs_FORWARD)
                  ? (PrevEcurve.FirstParameter() + nbs * SampleOnPrev)
                  : (PrevEcurve.FirstParameter() + (NbSamples - nbs) * SampleOnPrev);
              double ParOnCur = (CurEdge.Orientation() == TopAbs_FORWARD)
                                  ? (Ecurve.FirstParameter() + nbs * SampleOnCur)
                                  : (Ecurve.FirstParameter() + (NbSamples - nbs) * SampleOnCur);
              gp_Pnt PonPrev  = PrevEcurve.Value(ParOnPrev);
              gp_Pnt PonCur   = Ecurve.Value(ParOnCur).XYZ() + Offset.XYZ();
              SumDist += PonPrev.Distance(PonCur);
            }
          }
        }
        if (SumDist < MinSumDist)
        {
          MinSumDist = SumDist;
          jmin       = j;
          forward    = true;
        }

        SumDist = 0.;
        for (k = j, n = 1; k >= 1; k--, n++)
        {
          const TopoDS_Vertex& Vprev = TopoDS::Vertex(PrevSeq(n));
          gp_Pnt               Pprev = BRep_Tool::Pnt(Vprev);
          const TopoDS_Vertex& V     = TopoDS::Vertex(SeqVertices(k));
          gp_Pnt               P     = BRep_Tool::Pnt(V).XYZ() + Offset.XYZ();
          SumDist += Pprev.Distance(P);
          if (NbSamples > 0)
          {
            int k_cur = k - 1;
            if (k_cur == 0)
              k_cur = theLength;
            const TopoDS_Edge& PrevEdge = TopoDS::Edge(PrevEseq(n));
            const TopoDS_Edge& CurEdge  = TopoDS::Edge(SeqEdges(k_cur));
            BRepAdaptor_Curve  PrevEcurve(PrevEdge);
            BRepAdaptor_Curve  Ecurve(CurEdge);
            double             SampleOnPrev =
              (PrevEcurve.LastParameter() - PrevEcurve.FirstParameter()) / NbSamples;
            double SampleOnCur = (Ecurve.LastParameter() - Ecurve.FirstParameter()) / NbSamples;
            for (nbs = 1; nbs <= NbSamples - 1; nbs++)
            {
              double ParOnPrev =
                (PrevEdge.Orientation() == TopAbs_FORWARD)
                  ? (PrevEcurve.FirstParameter() + nbs * SampleOnPrev)
                  : (PrevEcurve.FirstParameter() + (NbSamples - nbs) * SampleOnPrev);
              double ParOnCur = (CurEdge.Orientation() == TopAbs_FORWARD)
                                  ? (Ecurve.FirstParameter() + (NbSamples - nbs) * SampleOnCur)
                                  : (Ecurve.FirstParameter() + nbs * SampleOnCur);
              gp_Pnt PonPrev  = PrevEcurve.Value(ParOnPrev);
              gp_Pnt PonCur   = Ecurve.Value(ParOnCur).XYZ() + Offset.XYZ();
              SumDist += PonPrev.Distance(PonCur);
            }
          }
        }
        for (k = theLength; k > j; k--, n++)
        {
          const TopoDS_Vertex& Vprev = TopoDS::Vertex(PrevSeq(n));
          gp_Pnt               Pprev = BRep_Tool::Pnt(Vprev);
          const TopoDS_Vertex& V     = TopoDS::Vertex(SeqVertices(k));
          gp_Pnt               P     = BRep_Tool::Pnt(V).XYZ() + Offset.XYZ();
          SumDist += Pprev.Distance(P);
          if (NbSamples > 0)
          {
            const TopoDS_Edge& PrevEdge = TopoDS::Edge(PrevEseq(n));
            const TopoDS_Edge& CurEdge  = TopoDS::Edge(SeqEdges(k - 1));
            BRepAdaptor_Curve  PrevEcurve(PrevEdge);
            BRepAdaptor_Curve  Ecurve(CurEdge);
            double             SampleOnPrev =
              (PrevEcurve.LastParameter() - PrevEcurve.FirstParameter()) / NbSamples;
            double SampleOnCur = (Ecurve.LastParameter() - Ecurve.FirstParameter()) / NbSamples;
            for (nbs = 1; nbs <= NbSamples - 1; nbs++)
            {
              double ParOnPrev =
                (PrevEdge.Orientation() == TopAbs_FORWARD)
                  ? (PrevEcurve.FirstParameter() + nbs * SampleOnPrev)
                  : (PrevEcurve.FirstParameter() + (NbSamples - nbs) * SampleOnPrev);
              double ParOnCur = (CurEdge.Orientation() == TopAbs_FORWARD)
                                  ? (Ecurve.FirstParameter() + (NbSamples - nbs) * SampleOnCur)
                                  : (Ecurve.FirstParameter() + nbs * SampleOnCur);
              gp_Pnt PonPrev  = PrevEcurve.Value(ParOnPrev);
              gp_Pnt PonCur   = Ecurve.Value(ParOnCur).XYZ() + Offset.XYZ();
              SumDist += PonPrev.Distance(PonCur);
            }
          }
        }
        if (SumDist < MinSumDist)
        {
          MinSumDist = SumDist;
          jmin       = j;
          forward    = false;
        }
      }

    PrevSeq.Clear();
    PrevEseq.Clear();
    if (forward)
    {
      for (j = jmin; j <= theLength; j++)
      {
        BB.Add(newwire, TopoDS::Edge(SeqEdges(j)));
        PrevSeq.Append(SeqVertices(j));
        PrevEseq.Append(SeqEdges(j));
      }
      for (j = 1; j < jmin; j++)
      {
        BB.Add(newwire, TopoDS::Edge(SeqEdges(j)));
        PrevSeq.Append(SeqVertices(j));
        PrevEseq.Append(SeqEdges(j));
      }
    }
    else
    {
      for (j = jmin - 1; j >= 1; j--)
      {
        TopoDS_Shape aLocalShape = SeqEdges(j).Reversed();
        BB.Add(newwire, TopoDS::Edge(aLocalShape));

        PrevEseq.Append(SeqEdges(j).Reversed());
      }
      for (j = theLength; j >= jmin; j--)
      {
        TopoDS_Shape aLocalShape = SeqEdges(j).Reversed();
        BB.Add(newwire, TopoDS::Edge(aLocalShape));

        PrevEseq.Append(SeqEdges(j).Reversed());
      }
      for (j = jmin; j >= 1; j--)
        PrevSeq.Append(SeqVertices(j));
      for (j = theLength; j > jmin; j--)
        PrevSeq.Append(SeqVertices(j));
    }

    newwire.Closed(true);
    newwire.Orientation(TopAbs_FORWARD);
    myWork(i) = newwire;

    PrevBary = CurBary;
  }
#ifdef OCCT_DEBUG_EFV

  gp_Pnt PPs;
  gp_Pnt Pdeb, Psuiv;

  for (i = ideb; i <= myWork.Length(); i++)
  {

    const TopoDS_Wire& wire = TopoDS::Wire(myWork(i));

    int nbEdges = 0;
    for (anExp.Init(TopoDS::Wire(myWork(i))); anExp.More(); anExp.Next())
      nbEdges++;
    TopExp::Vertices(wire, Vdeb, Vfin);
    bool wClosed = wire.Closed();
    if (!wClosed)
    {

      if (Vdeb.IsSame(Vfin))
        wClosed = true;
    }

    TopoDS_Vertex Vsuiv, VF, VR;
    TopoDS_Wire   newwire;
    BRep_Builder  BW;
    BW.MakeWire(newwire);
    if (i == ideb)
    {
      anExp.Init(wire);
      const TopoDS_Edge Ecur = TopoDS::Edge(anExp.Current());
      TopExp::Vertices(Ecur, VF, VR);
      if (Vdeb.IsSame(VF))
        Vsuiv = VR;
      else if (Vdeb.IsSame(VR))
        Vsuiv = VF;
      else
      {

        if (VR.IsSame(TopoDS::Vertex(anExp.CurrentVertex())))
        {
          Vdeb  = VR;
          Vsuiv = VF;
        }
        else
        {
          Vdeb  = VF;
          Vsuiv = VR;
        }
      }
      Pdeb                 = BRep_Tool::Pnt(Vdeb);
      Psuiv                = BRep_Tool::Pnt(Vsuiv);
      double            U1 = BRep_Tool::Parameter(Vdeb, Ecur);
      double            U2 = BRep_Tool::Parameter(Vsuiv, Ecur);
      BRepAdaptor_Curve Curve(Ecur);
      PPs          = Curve.Value(0.25 * (U1 + 3 * U2));
      myWork(ideb) = wire;
    }
    else
    {

      gp_Pnt Pnew, Pnext, PPn;
      Transform(true,
                Pdeb,
                Pos->Value(i - 1),
                Axe->Value(i - 1),
                Pos->Value(i),
                Axe->Value(i),
                Pnew);
      Transform(true,
                Psuiv,
                Pos->Value(i - 1),
                Axe->Value(i - 1),
                Pos->Value(i),
                Axe->Value(i),
                Pnext);
      Transform(true, PPs, Pos->Value(i - 1), Axe->Value(i - 1), Pos->Value(i), Axe->Value(i), PPn);

      double        distmini, dist;
      int           rang = 0, rangdeb = 0;
      TopoDS_Vertex Vmini;
      gp_Pnt        Pmini, P1, P2;
      SeqOfVertices(wire, SeqV);
      if (SeqV.Length() > NbMaxV)
      {
        myStatus = BRepFill::ThruSectionsError_Failed;
        return;
      }
      if (!polar)
      {

        distmini = Precision::Infinite();
        for (int ii = 1; ii <= SeqV.Length(); ii++)
        {
          P1   = BRep_Tool::Pnt(TopoDS::Vertex(SeqV.Value(ii)));
          dist = P1.Distance(Pnew);
          if (dist < distmini)
          {
            distmini = dist;
            Vmini    = TopoDS::Vertex(SeqV.Value(ii));
          }
        }
        if (!Vmini.IsNull())
          Pmini = BRep_Tool::Pnt(Vmini);
      }
      else
      {

        double        angmin, angV, eta = Precision::Angular();
        TopoDS_Vertex Vopti;
        angmin   = M_PI / 2;
        distmini = Precision::Infinite();
        gp_Dir dir0(gp_Vec(Pnew, P.Location()));
        for (int ii = 1; ii <= SeqV.Length(); ii++)
        {
          P1   = BRep_Tool::Pnt(TopoDS::Vertex(SeqV.Value(ii)));
          dist = Pnew.Distance(P1);
          if (dist < Precision::Confusion())
          {
            angV = 0.0;
          }
          else
          {
            gp_Dir dir1(gp_Vec(Pnew, P1));
            angV = dir1.Angle(dir0);
          }
          if (angV > M_PI / 2)
            angV = M_PI - angV;
          if (angmin > angV + eta)
          {
            distmini = dist;
            angmin   = angV;
            Vopti    = TopoDS::Vertex(SeqV.Value(ii));
          }
          else if (std::abs(angmin - angV) < eta)
          {
            if (dist < distmini)
            {
              distmini = dist;
              angmin   = angV;
              Vopti    = TopoDS::Vertex(SeqV.Value(ii));
            }
          }
        }
        gp_Pnt Popti;
        if (!Vopti.IsNull())
          Popti = BRep_Tool::Pnt(Vopti);
        Vmini = Vopti;
      }

      distmini = Precision::Infinite();
      for (anExp.Init(wire); anExp.More(); anExp.Next())
      {
        TopoDS_Edge   Ecur = anExp.Current();
        TopoDS_Vertex Vcur = anExp.CurrentVertex();
        TopExp::Vertices(Ecur, VF, VR);
        if (VF.IsSame(Vmini))
        {
          P1   = BRep_Tool::Pnt(VR);
          dist = P1.Distance(Pnext);
          if (dist <= distmini)
          {
            distmini = dist;
            Vsuiv    = VR;
          }
        }
        if (VR.IsSame(Vmini))
        {
          P1   = BRep_Tool::Pnt(VF);
          dist = P1.Distance(Pnext);
          if (dist < distmini)
          {
            distmini = dist;
            Vsuiv    = VF;
          }
        }
      }

      bool parcours = false;
      if (i == myWork.Length() && myDegen2)
      {

        rangdeb  = 1;
        parcours = true;
      }
      else
      {

        gp_Pnt        Pbout = Pnext;
        TopoDS_Edge   E1, E2;
        TopoDS_Vertex V1, V2;
        EdgesFromVertex(wire, Vmini, E1, E2);

        TopExp::Vertices(E1, V1, V2, true);
  #ifndef OCCT_DEBUG
        double U1 = 0, U2 = 0;
  #else
        double U1, U2;
  #endif
        if (Vmini.IsSame(V1))
        {
          P1 = BRep_Tool::Pnt(V2);
          U1 = 0.25 * (BRep_Tool::Parameter(V1, E1) + 3 * BRep_Tool::Parameter(V2, E1));
        }
        if (Vmini.IsSame(V2))
        {
          P1 = BRep_Tool::Pnt(V1);
          U1 = 0.25 * (3 * BRep_Tool::Parameter(V1, E1) + BRep_Tool::Parameter(V2, E1));
        }

        TopExp::Vertices(E2, V1, V2, true);
        if (Vmini.IsSame(V1))
        {
          P2 = BRep_Tool::Pnt(V2);
          U2 = 0.25 * (BRep_Tool::Parameter(V1, E2) + 3 * BRep_Tool::Parameter(V2, E2));
        }
        if (Vmini.IsSame(V2))
        {
          P2 = BRep_Tool::Pnt(V1);
          U2 = 0.25 * (3 * BRep_Tool::Parameter(V1, E2) + BRep_Tool::Parameter(V2, E2));
        }

        if (std::abs(Pbout.Distance(P1) - Pbout.Distance(P2)) < Precision::Confusion())
        {

          Pbout = PPn;
          BRepAdaptor_Curve Curve1(E1);
          P1 = Curve1.Value(U1);
          BRepAdaptor_Curve Curve2(E2);
          P2 = Curve2.Value(U2);
        }

        rangdeb = 0;
        if (Pbout.Distance(P1) < Pbout.Distance(P2))
        {

          parcours = false;
          rang     = 0;
          for (anExp.Init(wire); anExp.More(); anExp.Next())
          {
            rang++;
            TopoDS_Edge Ecur = anExp.Current();
            if (E1.IsSame(Ecur))
            {
              rangdeb = rang;
            }
          }
          BRepAdaptor_Curve Curve(E1);
          PPs = Curve.Value(U1);
        }
        else
        {

          parcours = true;
          rang     = 0;
          for (anExp.Init(wire); anExp.More(); anExp.Next())
          {
            rang++;
            TopoDS_Edge Ecur = anExp.Current();
            if (E2.IsSame(Ecur))
            {
              rangdeb = rang;
            }
          }
          BRepAdaptor_Curve Curve(E2);
          PPs = Curve.Value(U2);
        }
      }

      NCollection_Sequence<TopoDS_Shape> SeqEdges;
      SeqEdges.Clear();
      for (anExp.Init(TopoDS::Wire(wire)); anExp.More(); anExp.Next())
      {
        SeqEdges.Append(anExp.Current());
      }
      if (parcours)
      {
        for (rang = rangdeb; rang <= nbEdges; rang++)
        {
          BW.Add(newwire, TopoDS::Edge(SeqEdges.Value(rang)));
        }
        for (rang = 1; rang < rangdeb; rang++)
        {
          BW.Add(newwire, TopoDS::Edge(SeqEdges.Value(rang)));
        }
      }
      else
      {
        for (rang = rangdeb; rang >= 1; rang--)
        {
          TopoDS_Shape aLocalShape = SeqEdges.Value(rang).Reversed();
          BW.Add(newwire, TopoDS::Edge(aLocalShape));
        }
        for (rang = nbEdges; rang > rangdeb; rang--)
        {
          TopoDS_Shape aLocalShape = SeqEdges.Value(rang).Reversed();
          BW.Add(newwire, TopoDS::Edge(aLocalShape));
        }
      }

      myWork(i) = newwire.Oriented(TopAbs_FORWARD);

      if (!Vmini.IsNull())
        Pdeb = BRep_Tool::Pnt(Vmini);
      if (!Vsuiv.IsNull())
        Psuiv = BRep_Tool::Pnt(Vsuiv);
    }
  }
#endif

  if (vClosed)
    myWork(myWork.Length()) = myWork(1);
}

void BRepFill_CompatibleWires::SearchOrigin()
{

  gp_Pln P0, P;

  TopoDS_Vertex Vdeb, Vfin;
  gp_Pnt        Pdeb, Pfin;

  BRepTools_WireExplorer anExp;

  bool allOpen = true;
  int  ideb = 1, ifin = myWork.Length();
  if (myDegen1)
    ideb++;
  if (myDegen2)
    ifin--;
  bool vClosed = (!myDegen1) && (!myDegen2) && (myWork(ideb).IsSame(myWork(ifin)));

  int i;
  for (i = ideb; i <= ifin; i++)
  {
    allOpen = (allOpen && !myWork(i).Closed());
  }
  if (!allOpen)
  {
    myStatus = BRepFill_ThruSectionErrorStatus_NotSameTopology;
    return;
  }

  TopoDS_Wire wire1 = TopoDS::Wire(myWork(ideb));
  wire1.Orientation(TopAbs_FORWARD);
  TopExp::Vertices(wire1, Vdeb, Vfin);
  Pdeb         = BRep_Tool::Pnt(Vdeb);
  Pfin         = BRep_Tool::Pnt(Vfin);
  bool isline0 = (!PlaneOfWire(wire1, P0)), isline;
  myWork(ideb) = wire1;

  anExp.Init(wire1);
  TopoDS_Edge E0 = anExp.Current(), E;

  for (i = ideb + 1; i <= ifin; i++)
  {

    TopoDS_Wire wire = TopoDS::Wire(myWork(i));
    wire.Orientation(TopAbs_FORWARD);

    NCollection_Sequence<TopoDS_Shape> SeqEdges;
    SeqEdges.Clear();
    int nbEdges = 0;

    for (anExp.Init(wire), E = anExp.Current(); anExp.More(); anExp.Next())
    {
      SeqEdges.Append(anExp.Current());
      nbEdges++;
    }
    TopExp::Vertices(wire, Vdeb, Vfin);
    isline = (!PlaneOfWire(wire, P));

    TopoDS_Vertex Vmini;
    TopoDS_Wire   newwire;
    BRep_Builder  BW;
    BW.MakeWire(newwire);
    bool parcours = true;

    if (isline0 || isline)
    {

      gp_Pnt P1 = BRep_Tool::Pnt(Vdeb), P2 = BRep_Tool::Pnt(Vfin);
      double dist1, dist2;
      dist1    = Pdeb.Distance(P1) + Pfin.Distance(P2);
      dist2    = Pdeb.Distance(P2) + Pfin.Distance(P1);
      parcours = (dist2 >= dist1);
    }

    else
    {

      gp_Pnt P1 = BRep_Tool::Pnt(Vdeb), P1o = Pdeb, P2 = BRep_Tool::Pnt(Vfin), P2o = Pfin;

      if (P1.IsEqual(P2, Precision::Confusion()) || P1o.IsEqual(P2o, Precision::Confusion()))
      {
        BRepAdaptor_Curve Curve0(E0), Curve(E);
        Curve0.D0(Curve0.FirstParameter() + Precision::Confusion(), P2o);
        Curve.D0(Curve.FirstParameter() + Precision::Confusion(), P2);
      };
      gp_Vec VDebFin0(P1o, P2o), VDebFin(P1, P2);
      double AStraight = VDebFin0.Angle(VDebFin);
      parcours         = (AStraight < M_PI / 2.0);
    }

    int rang;
    if (parcours)
    {
      for (rang = 1; rang <= nbEdges; rang++)
      {
        TopoDS_Shape alocalshape = SeqEdges.Value(rang);
        BW.Add(newwire, TopoDS::Edge(alocalshape));
      }
    }
    else
    {
      for (rang = nbEdges; rang >= 1; rang--)
      {
        TopoDS_Shape alocalshape = SeqEdges.Value(rang).Reversed();
        BW.Add(newwire, TopoDS::Edge(alocalshape));
      }
    }

    newwire.Oriented(TopAbs_FORWARD);
    myWork(i) = newwire;

    if (parcours)
    {
      Pdeb = BRep_Tool::Pnt(Vdeb);
      Pfin = BRep_Tool::Pnt(Vfin);
    }
    else
    {
      Pfin = BRep_Tool::Pnt(Vdeb);
      Pdeb = BRep_Tool::Pnt(Vfin);
    }
    P0      = P;
    isline0 = isline;

    E0 = E;
  }

  if (vClosed)
    myWork(myWork.Length()) = myWork(1);
}
