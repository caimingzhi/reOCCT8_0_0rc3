#include <Bisector_Bisec.hpp>
#include <Bisector_BisecAna.hpp>
#include <Bnd_Box2d.hpp>
#include <BndLib_Add2dCurve.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAlgo_FaceRestrictor.hpp>
#include <BRepAlgo_Loop.hpp>
#include <BRepClass3d_SolidClassifier.hpp>
#include <MAT_Node.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <BRepFill_Evolved.hpp>
#include <BRepFill_OffsetAncestors.hpp>
#include <BRepFill_OffsetWire.hpp>
#include <BRepFill_Pipe.hpp>
#include <BRepFill_TrimSurfaceTool.hpp>
#include <BRepLib.hpp>
#include <BRepLib_FindSurface.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <BRepLib_MakeFace.hpp>
#include <BRepLib_MakeVertex.hpp>
#include <BRepLib_MakeWire.hpp>
#include <BRepLProp.hpp>
#include <BRepMAT2d_BisectingLocus.hpp>
#include <BRepMAT2d_Explorer.hpp>
#include <BRepMAT2d_LinkTopoBilo.hpp>
#include <BRepSweep_Prism.hpp>
#include <BRepSweep_Revol.hpp>
#include <BRepTools.hpp>
#include <BRepTools_Modifier.hpp>
#include <BRepTools_Quilt.hpp>
#include <BRepTools_TrsfModification.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAPI_ExtremaCurveCurve.hpp>
#include <Geom2dInt_GInter.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomProjLib.hpp>
#include <gp.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax3.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <MAT2d_CutCurve.hpp>
#include <MAT_Arc.hpp>
#include <MAT_BasicElt.hpp>
#include <MAT_Graph.hpp>
#include <MAT_Side.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_NotImplemented.hpp>
#include <TopAbs.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

static double BRepFill_Confusion()
{
  double Tol = 1.e-6;
  return Tol;
}

static const TopoDS_Wire PutProfilAt(const TopoDS_Wire& ProfRef,
                                     const gp_Ax3&      AxeRef,
                                     const TopoDS_Edge& E,
                                     const TopoDS_Face& F,
                                     const bool         AtStart);

static void TrimFace(const TopoDS_Face&                  Face,
                     NCollection_Sequence<TopoDS_Shape>& TheEdges,
                     NCollection_Sequence<TopoDS_Shape>& S);

static void TrimEdge(const TopoDS_Edge&                        Edge,
                     const NCollection_Sequence<TopoDS_Shape>& TheEdgesControle,
                     NCollection_Sequence<TopoDS_Shape>&       TheVer,
                     NCollection_Sequence<double>&             ThePar,
                     NCollection_Sequence<TopoDS_Shape>&       S);

static int PosOnFace(double d1, double d2, double d3);

static void ComputeIntervals(const NCollection_Sequence<TopoDS_Shape>& VonF,
                             const NCollection_Sequence<TopoDS_Shape>& VOnL,
                             const NCollection_Sequence<gp_Pnt>&       ParOnF,
                             const NCollection_Sequence<gp_Pnt>&       ParOnL,
                             const BRepFill_TrimSurfaceTool&           Trim,
                             const occ::handle<Geom2d_Curve>&          Bis,
                             const TopoDS_Vertex&                      VS,
                             const TopoDS_Vertex&                      VE,
                             NCollection_Sequence<double>&             FirstPar,
                             NCollection_Sequence<double>&             LastPar,
                             NCollection_Sequence<TopoDS_Shape>&       FirstV,
                             NCollection_Sequence<TopoDS_Shape>&       LastV);

static double DistanceToOZ(const TopoDS_Vertex& V);

static double Altitud(const TopoDS_Vertex& V);

static bool DoubleOrNotInFace(const NCollection_Sequence<TopoDS_Shape>& EC, const TopoDS_Vertex& V);

static void SimpleExpression(const Bisector_Bisec& B, occ::handle<Geom2d_Curve>& Bis);

static TopAbs_Orientation Relative(const TopoDS_Wire&   W1,
                                   const TopoDS_Wire&   W2,
                                   const TopoDS_Vertex& V,
                                   bool&                Commun);

static void CutEdge(const TopoDS_Edge&              E,
                    const TopoDS_Face&              F,
                    NCollection_List<TopoDS_Shape>& Cuts);

static void CutEdgeProf(
  const TopoDS_Edge&                                                        E,
  const occ::handle<Geom_Plane>&                                            Plane,
  const occ::handle<Geom2d_Line>&                                           Line,
  NCollection_List<TopoDS_Shape>&                                           Cuts,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& MapVerRefMoved);

static int VertexFromNode(
  const occ::handle<MAT_Node>& aNode,
  const TopoDS_Edge&           E,
  const TopoDS_Vertex&         VF,
  const TopoDS_Vertex&         VL,
  NCollection_DataMap<occ::handle<MAT_Node>,
                      NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>>&
                 MapNodeVertex,
  TopoDS_Vertex& VS);

static void EdgeVertices(const TopoDS_Edge& E, TopoDS_Vertex& V1, TopoDS_Vertex& V2)
{
  if (E.Orientation() == TopAbs_REVERSED)
  {
    TopExp::Vertices(E, V2, V1);
  }
  else
  {
    TopExp::Vertices(E, V1, V2);
  }
}

BRepFill_Evolved::BRepFill_Evolved()
    : myIsDone(false),
      mySpineType(true)
{
}

BRepFill_Evolved::BRepFill_Evolved(const TopoDS_Wire&     Spine,
                                   const TopoDS_Wire&     Profile,
                                   const gp_Ax3&          AxeProf,
                                   const GeomAbs_JoinType Join,
                                   const bool             Solid)

    : myIsDone(false)
{
  Perform(Spine, Profile, AxeProf, Join, Solid);
}

BRepFill_Evolved::BRepFill_Evolved(const TopoDS_Face&     Spine,
                                   const TopoDS_Wire&     Profile,
                                   const gp_Ax3&          AxeProf,
                                   const GeomAbs_JoinType Join,
                                   const bool             Solid)
    : myIsDone(false)
{
  Perform(Spine, Profile, AxeProf, Join, Solid);
}

static bool IsVertical(const TopoDS_Edge& E)
{
  TopoDS_Vertex V1, V2;
  TopExp::Vertices(E, V1, V2);
  gp_Pnt P1 = BRep_Tool::Pnt(V1);
  gp_Pnt P2 = BRep_Tool::Pnt(V2);

  if (std::abs(P1.Y() - P2.Y()) < BRepFill_Confusion())
  {

    TopLoc_Location         Loc;
    double                  f, l;
    occ::handle<Geom_Curve> GC = BRep_Tool::Curve(E, Loc, f, l);
    if (GC->DynamicType() == STANDARD_TYPE(Geom_Line))
      return true;
  }
  return false;
}

static bool IsPlanar(const TopoDS_Edge& E)
{
  TopoDS_Vertex V1, V2;
  TopExp::Vertices(E, V1, V2);
  gp_Pnt P1 = BRep_Tool::Pnt(V1);
  gp_Pnt P2 = BRep_Tool::Pnt(V2);

  if (std::abs(P1.Z() - P2.Z()) < BRepFill_Confusion())
  {

    TopLoc_Location         Loc;
    double                  f, l;
    occ::handle<Geom_Curve> GC = BRep_Tool::Curve(E, Loc, f, l);
    if (GC->DynamicType() == STANDARD_TYPE(Geom_Line))
      return true;
  }
  return false;
}

static int Side(const TopoDS_Wire& Profil, const double Tol)
{
  TopoDS_Vertex V1, V2;

  TopExp_Explorer Explo(Profil, TopAbs_EDGE);

  int                TheSide;
  const TopoDS_Edge& E = TopoDS::Edge(Explo.Current());

  TopExp::Vertices(E, V1, V2);
  gp_Pnt P1 = BRep_Tool::Pnt(V1);
  gp_Pnt P2 = BRep_Tool::Pnt(V2);

  if (P1.Y() < -Tol || P2.Y() < -Tol)
    TheSide = 4;
  else
    TheSide = 1;
  if (IsVertical(E))
    TheSide += 2;
  else if (IsPlanar(E))
    TheSide++;
  return TheSide;
}

void BRepFill_Evolved::Perform(const TopoDS_Wire&     Spine,
                               const TopoDS_Wire&     Profile,
                               const gp_Ax3&          AxeProf,
                               const GeomAbs_JoinType Join,
                               const bool             Solid)
{
  mySpineType       = false;
  TopoDS_Face aFace = BRepLib_MakeFace(Spine, true);
  PrivatePerform(aFace, Profile, AxeProf, Join, Solid);
}

void BRepFill_Evolved::Perform(const TopoDS_Face&     Spine,
                               const TopoDS_Wire&     Profile,
                               const gp_Ax3&          AxeProf,
                               const GeomAbs_JoinType Join,
                               const bool             Solid)
{
  mySpineType = true;
  PrivatePerform(Spine, Profile, AxeProf, Join, Solid);
}

void BRepFill_Evolved::PrivatePerform(const TopoDS_Face&     Spine,
                                      const TopoDS_Wire&     Profile,
                                      const gp_Ax3&          AxeProf,
                                      const GeomAbs_JoinType Join,
                                      const bool             Solid)
{
  TopoDS_Shape aLocalShape = Spine.Oriented(TopAbs_FORWARD);
  mySpine                  = TopoDS::Face(aLocalShape);

  aLocalShape = Profile.Oriented(TopAbs_FORWARD);
  myProfile   = TopoDS::Wire(aLocalShape);

  myJoinType = Join;
  myMap.Clear();

  if (myJoinType > GeomAbs_Arc)
  {
    throw Standard_NotImplemented();
  }

  NCollection_List<TopoDS_Shape>           WorkProf;
  TopoDS_Face                              WorkSpine;
  NCollection_List<TopoDS_Shape>::Iterator WPIte;

  TopLoc_Location LSpine = FindLocation(mySpine);
  gp_Trsf         T;
  T.SetTransformation(AxeProf);
  TopLoc_Location LProfile(T);
  TopLoc_Location InitLS = mySpine.Location();
  TopLoc_Location InitLP = myProfile.Location();
  TransformInitWork(LSpine, LProfile);

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> MapProf, MapSpine;

  PrepareProfile(WorkProf, MapProf);
  PrepareSpine(WorkSpine, MapSpine);

  double      Tol     = BRepFill_Confusion();
  bool        YaLeft  = false;
  bool        YaRight = false;
  TopoDS_Wire SP;

  for (WPIte.Initialize(WorkProf); WPIte.More(); WPIte.Next())
  {
    SP = TopoDS::Wire(WPIte.Value());
    if (Side(SP, Tol) < 4)
      YaLeft = true;
    else
      YaRight = true;
    if (YaLeft && YaRight)
      break;
  }

  TopoDS_Face              Face;
  BRepMAT2d_BisectingLocus Locus;

  BRepFill_Evolved       CutVevo;
  TopoDS_Wire            WP;
  BRep_Builder           BB;
  BRepTools_WireExplorer WExp;

  BB.MakeWire(WP);

  for (WPIte.Initialize(WorkProf); WPIte.More(); WPIte.Next())
  {
    for (WExp.Init(TopoDS::Wire(WPIte.Value())); WExp.More(); WExp.Next())
    {
      BB.Add(WP, WExp.Current());
    }
  }
  CutVevo.SetWork(WorkSpine, WP);

  BRepTools_Quilt Glue;
  int             CSide;

  if (YaLeft)
  {

    BRepMAT2d_Explorer Exp(WorkSpine);
    Locus.Compute(Exp, 1, MAT_Left);
    BRepMAT2d_LinkTopoBilo Link(Exp, Locus);

    for (WPIte.Initialize(WorkProf); WPIte.More(); WPIte.Next())
    {
      SP    = TopoDS::Wire(WPIte.Value());
      CSide = Side(SP, Tol);

      BRepFill_Evolved Vevo;
      if (CSide == 1)
      {
        Vevo.ElementaryPerform(WorkSpine, SP, Locus, Link, Join);
      }
      else if (CSide == 2)
      {
        Vevo.PlanarPerform(WorkSpine, SP, Locus, Link, Join);
      }
      else if (CSide == 3)
      {
        Vevo.VerticalPerform(WorkSpine, SP, Locus, Link, Join);
      }
      CutVevo.Add(Vevo, SP, Glue);
    }
  }

  if (YaRight)
  {

    TopExp_Explorer SpineExp(WorkSpine, TopAbs_WIRE);
    for (; SpineExp.More(); SpineExp.Next())
    {

      BRepLib_MakeFace B(gp_Pln(0., 0., 1., 0.));
      TopoDS_Shape     aLocalShapeRev = SpineExp.Current().Reversed();
      B.Add(TopoDS::Wire(aLocalShapeRev));

      Face = B.Face();
      BRepMAT2d_Explorer Exp(Face);
      Locus.Compute(Exp, 1, MAT_Left);
      BRepMAT2d_LinkTopoBilo Link(Exp, Locus);

      for (WPIte.Initialize(WorkProf); WPIte.More(); WPIte.Next())
      {
        SP    = TopoDS::Wire(WPIte.Value());
        CSide = Side(SP, Tol);

        BRepFill_Evolved Vevo;
        if (CSide == 4)
        {
          Vevo.ElementaryPerform(Face, SP, Locus, Link, Join);
        }
        else if (CSide == 5)
        {
          Vevo.PlanarPerform(Face, SP, Locus, Link, Join);
        }
        else if (CSide == 6)
        {
          Vevo.VerticalPerform(Face, SP, Locus, Link, Join);
        }
        CutVevo.Add(Vevo, SP, Glue);
      }
    }
  }

  if (Solid)
    CutVevo.AddTopAndBottom(Glue);

  CutVevo.ContinuityOnOffsetEdge(WorkProf);

  TopoDS_Shape& SCV = CutVevo.ChangeShape();
  SCV               = Glue.Shells();

  Transfert(CutVevo, MapProf, MapSpine, LSpine.Inverted(), InitLS, InitLP);

  if (Solid)
    MakeSolid();

  BRepLib::UpdateTolerances(myShape, false);

  myIsDone = true;
}

static void IsInversed(const TopoDS_Shape& S,
                       const TopoDS_Edge&  E1,
                       const TopoDS_Edge&  E2,
                       bool*               Inverse)
{

  Inverse[0] = Inverse[1] = false;
  if (S.ShapeType() != TopAbs_EDGE)
    return;

  gp_Pnt            P;
  gp_Vec            DS, DC1, DC2;
  BRepAdaptor_Curve CS(TopoDS::Edge(S));
  if (S.Orientation() == TopAbs_FORWARD)
  {
    CS.D1(CS.FirstParameter(), P, DS);
  }
  else
  {
    CS.D1(CS.LastParameter(), P, DS);
    DS.Reverse();
  }

  if (!BRep_Tool::Degenerated(E1))
  {
    BRepAdaptor_Curve C1(TopoDS::Edge(E1));
    if (E1.Orientation() == TopAbs_FORWARD)
    {
      C1.D1(C1.FirstParameter(), P, DC1);
    }
    else
    {
      C1.D1(C1.LastParameter(), P, DC1);
      DC1.Reverse();
    }
    Inverse[0] = (DS.Dot(DC1) < 0.);
  }
  else
    Inverse[0] = true;

  if (!BRep_Tool::Degenerated(E2))
  {
    BRepAdaptor_Curve C2(TopoDS::Edge(E2));
    if (E2.Orientation() == TopAbs_FORWARD)
    {
      C2.D1(C2.FirstParameter(), P, DC2);
    }
    else
    {
      C2.D1(C2.LastParameter(), P, DC2);
      DC2.Reverse();
    }
    Inverse[1] = (DS.Dot(DC2) < 0.);
  }
  else
    Inverse[1] = true;
}

void BRepFill_Evolved::SetWork(const TopoDS_Face& Sp, const TopoDS_Wire& Pr)
{
  mySpine   = Sp;
  myProfile = Pr;
}

static bool ConcaveSide(const TopoDS_Shape& S, const TopoDS_Face& F)
{

  if (S.ShapeType() == TopAbs_VERTEX)
    return false;

  if (S.ShapeType() == TopAbs_EDGE)
  {
    double                    f, l;
    occ::handle<Geom2d_Curve> G2d = BRep_Tool::CurveOnSurface(TopoDS::Edge(S), F, f, l);
    occ::handle<Geom2d_Curve> G2dOC;

    Geom2dAdaptor_Curve AC(G2d, f, l);
    if (AC.GetType() == GeomAbs_Circle)
    {
      bool Direct = AC.Circle().IsDirect();
      if (S.Orientation() == TopAbs_REVERSED)
        Direct = (!Direct);
      return Direct;
    }
  }
  return false;
}

void BRepFill_Evolved::ElementaryPerform(const TopoDS_Face&              Sp,
                                         const TopoDS_Wire&              Pr,
                                         const BRepMAT2d_BisectingLocus& Locus,
                                         BRepMAT2d_LinkTopoBilo&         Link,
                                         const GeomAbs_JoinType)
{

  TopoDS_Shape aLocalShape = Sp.Oriented(TopAbs_FORWARD);
  mySpine                  = TopoDS::Face(aLocalShape);

  myProfile = Pr;
  myMap.Clear();

  BRep_Builder myBuilder;
  myBuilder.MakeCompound(TopoDS::Compound(myShape));

  NCollection_DataMap<occ::handle<MAT_Node>,
                      NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>>
    MapNodeVertex;
  NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<TopoDS_Shape>, TopTools_ShapeMapHasher>
    MapBis;
  NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<double>, TopTools_ShapeMapHasher>
    MapVerPar;

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> EmptyMap;
  NCollection_Sequence<TopoDS_Shape>                                       EmptySeq;
  NCollection_List<TopoDS_Shape>                                           EmptyList;
  NCollection_Sequence<double>                                             EmptySeqOfReal;

  gp_Ax3 AxeRef(gp_Pnt(0., 0., 0.), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X));

  BRepTools_WireExplorer ProfExp;
  TopExp_Explorer        FaceExp;
  BRepTools_WireExplorer WireExp;

  for (FaceExp.Init(mySpine, TopAbs_WIRE); FaceExp.More(); FaceExp.Next())
  {

    for (WireExp.Init(TopoDS::Wire(FaceExp.Current())); WireExp.More(); WireExp.Next())
    {

      const TopoDS_Edge& CurrentEdge = WireExp.Current();
      TopoDS_Vertex      VFirst, VLast;
      EdgeVertices(CurrentEdge, VFirst, VLast);

      for (Link.Init(VLast); Link.More(); Link.Next())
      {

        MakeRevol(CurrentEdge, VLast, AxeRef);
      }

      for (Link.Init(CurrentEdge); Link.More(); Link.Next())
      {

        MakePipe(CurrentEdge, AxeRef);
      }
    }
  }

  occ::handle<MAT_Arc>      CurrentArc;
  occ::handle<Geom2d_Curve> Bis, PCurve1, PCurve2;
  occ::handle<Geom_Curve>   CBis;
  bool                      Reverse;
  TopoDS_Edge               CurrentEdge;
  TopoDS_Shape              S[2];
  TopoDS_Face               F[2];
  TopoDS_Edge               E[4];
  TopLoc_Location           L;
  int                       k;

  for (int i = 1; i <= Locus.Graph()->NumberOfArcs(); i++)
  {
    CurrentArc = Locus.Graph()->Arc(i);
    SimpleExpression(Locus.GeomBis(CurrentArc, Reverse), Bis);

    S[0] = Link.GeneratingShape(CurrentArc->FirstElement());
    S[1] = Link.GeneratingShape(CurrentArc->SecondElement());

    bool Concave0 = ConcaveSide(S[0], mySpine);
    bool Concave1 = ConcaveSide(S[1], mySpine);

    NCollection_Sequence<TopoDS_Shape> VOnF, VOnL;
    NCollection_Sequence<gp_Pnt>       ParOnF, ParOnL;

    NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<TopoDS_Shape>, TopTools_ShapeMapHasher>
      MapSeqVer;
    NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<gp_Pnt>, TopTools_ShapeMapHasher>
      MapSeqPar;

    for (ProfExp.Init(myProfile); ProfExp.More(); ProfExp.Next())
    {

      F[0] = TopoDS::Face(myMap(S[0])(ProfExp.Current()).First());
      F[1] = TopoDS::Face(myMap(S[1])(ProfExp.Current()).First());

      TopoDS_Vertex VF, VL;

      EdgeVertices(ProfExp.Current(), VF, VL);

      E[0] = TopoDS::Edge(myMap(S[0])(VF).First());
      E[1] = TopoDS::Edge(myMap(S[0])(VL).First());
      E[2] = TopoDS::Edge(myMap(S[1])(VF).First());
      E[3] = TopoDS::Edge(myMap(S[1])(VL).First());

      bool Inv0[2];
      bool Inv1[2];

      Inv0[0] = Inv0[1] = Inv1[0] = Inv1[1] = false;
      if (Concave0)
        IsInversed(S[0], E[0], E[1], Inv0);
      if (Concave1)
        IsInversed(S[1], E[2], E[3], Inv1);

      BRepFill_TrimSurfaceTool Trim(Bis, F[0], F[1], E[0], E[2], Inv0[0], Inv1[0]);

      TopoDS_Vertex         VS, VE;
      occ::handle<MAT_Node> Node1, Node2;

      if (Reverse)
      {
        Node1 = CurrentArc->SecondNode();
        Node2 = CurrentArc->FirstNode();
      }
      else
      {
        Node1 = CurrentArc->FirstNode();
        Node2 = CurrentArc->SecondNode();
      }

      if (Node1->OnBasicElt())
      {
        if (S[0].ShapeType() == TopAbs_VERTEX)
        {
          Node1 = CurrentArc->FirstElement()->StartArc()->FirstNode();
        }
        else if (S[1].ShapeType() == TopAbs_VERTEX)
        {
          Node1 = CurrentArc->SecondElement()->StartArc()->FirstNode();
        }
      }

      int StartOnF =
        VertexFromNode(Node1, TopoDS::Edge(ProfExp.Current()), VF, VL, MapNodeVertex, VS);

      int EndOnF =
        VertexFromNode(Node2, TopoDS::Edge(ProfExp.Current()), VF, VL, MapNodeVertex, VE);

      if (!MapSeqVer.IsBound(VF))
      {
        if (Inv0[0] || Inv1[0])
        {
          ParOnF.Clear();
          VOnF.Clear();
        }
        else
        {
          Trim.IntersectWith(E[0], E[2], ParOnF);
          VOnF.Clear();
          for (int s = 1; s <= ParOnF.Length(); s++)
          {
            TopoDS_Vertex VC;
            myBuilder.MakeVertex(VC);
            VOnF.Append(VC);
          }
          if (StartOnF == 1)
          {
            VOnF.SetValue(1, VS);
          }
          if (EndOnF == 1)
          {
            VOnF.SetValue(ParOnF.Length(), VE);
          }
        }
      }
      else
      {
        ParOnF = MapSeqPar(VF);
        VOnF   = MapSeqVer(VF);
      }

      if (!MapSeqVer.IsBound(VL))
      {
        if (Inv0[1] || Inv1[1])
        {
          ParOnL.Clear();
          VOnL.Clear();
        }
        else
        {
          Trim.IntersectWith(E[1], E[3], ParOnL);
          VOnL.Clear();
          for (int s = 1; s <= ParOnL.Length(); s++)
          {
            TopoDS_Vertex VC;
            myBuilder.MakeVertex(VC);
            VOnL.Append(VC);
          }
          if (StartOnF == 3)
          {
            VOnL.SetValue(1, VS);
          }
          if (EndOnF == 3)
          {
            VOnL.SetValue(ParOnL.Length(), VE);
          }
        }
      }
      else
      {
        ParOnL = MapSeqPar(VL);
        VOnL   = MapSeqVer(VL);
      }

      if ((StartOnF == 0) && (EndOnF == 0) && VOnL.IsEmpty() && VOnF.IsEmpty())

        continue;

      if ((StartOnF == 0) && (EndOnF == 0) && (VOnL.Length() + VOnF.Length() == 1))

        continue;

      NCollection_Sequence<double>       LastPar, FirstPar;
      NCollection_Sequence<TopoDS_Shape> FirstV, LastV;

      ComputeIntervals(VOnF,
                       VOnL,
                       ParOnF,
                       ParOnL,
                       Trim,
                       Bis,
                       VS,
                       VE,
                       FirstPar,
                       LastPar,
                       FirstV,
                       LastV);

      for (int Ti = 1; Ti <= FirstPar.Length(); Ti++)
      {
        TopoDS_Vertex V1 = TopoDS::Vertex(FirstV.Value(Ti));
        TopoDS_Vertex V2 = TopoDS::Vertex(LastV.Value(Ti));

        GeomAbs_Shape Continuity;

        Trim.Project(FirstPar.Value(Ti), LastPar.Value(Ti), CBis, PCurve1, PCurve2, Continuity);

        myBuilder.MakeEdge(CurrentEdge, CBis, BRepFill_Confusion());

        myBuilder.UpdateVertex(V1, CBis->Value(CBis->FirstParameter()), BRepFill_Confusion());
        myBuilder.UpdateVertex(V2, CBis->Value(CBis->LastParameter()), BRepFill_Confusion());

        myBuilder.Add(CurrentEdge, V1.Oriented(TopAbs_FORWARD));
        myBuilder.Add(CurrentEdge, V2.Oriented(TopAbs_REVERSED));

        myBuilder.Range(CurrentEdge, CBis->FirstParameter(), CBis->LastParameter());
        myBuilder.UpdateEdge(CurrentEdge, PCurve1, F[0], BRepFill_Confusion());
        myBuilder.UpdateEdge(CurrentEdge, PCurve2, F[1], BRepFill_Confusion());

        myBuilder.Continuity(CurrentEdge, F[0], F[1], Continuity);

        for (k = 0; k <= 1; k++)
        {
          if (!MapBis.IsBound(F[k]))
          {
            MapBis.Bind(F[k], EmptySeq);
          }
        }

        E[0].Orientation(BRepTools::OriEdgeInFace(E[0], F[0]));
        E[2].Orientation(BRepTools::OriEdgeInFace(E[2], F[1]));

        if (DistanceToOZ(VF) < DistanceToOZ(VL))
        {

          MapBis(F[0]).Append(CurrentEdge.Oriented(E[0].Orientation()));
          CurrentEdge.Orientation(TopAbs::Complement(E[2].Orientation()));
          MapBis(F[1]).Append(CurrentEdge);
        }
        else
        {

          MapBis(F[1]).Append(CurrentEdge.Oriented(E[2].Orientation()));
          CurrentEdge.Orientation(TopAbs::Complement(E[0].Orientation()));
          MapBis(F[0]).Append(CurrentEdge);
        }
      }

      for (k = 0; k <= 2; k = k + 2)
      {
        if (!MapSeqVer.IsBound(VF))
        {
          if (!VOnF.IsEmpty())
          {
            if (!MapBis.IsBound(E[k]))
            {
              MapBis.Bind(E[k], EmptySeq);
              MapVerPar.Bind(E[k], EmptySeqOfReal);
            }
            for (int ii = 1; ii <= VOnF.Length(); ii++)
            {
              MapBis(E[k]).Append(VOnF.Value(ii));
              if (k == 0)
                MapVerPar(E[k]).Append(ParOnF.Value(ii).Y());
              else
                MapVerPar(E[k]).Append(ParOnF.Value(ii).Z());
            }
          }
        }
      }

      for (k = 1; k <= 3; k = k + 2)
      {
        if (!MapSeqVer.IsBound(VL))
        {
          if (!VOnL.IsEmpty())
          {
            if (!MapBis.IsBound(E[k]))
            {
              MapBis.Bind(E[k], EmptySeq);
              MapVerPar.Bind(E[k], EmptySeqOfReal);
            }
            for (int ii = 1; ii <= VOnL.Length(); ii++)
            {
              MapBis(E[k]).Append(VOnL.Value(ii));
              if (k == 1)
                MapVerPar(E[k]).Append(ParOnL.Value(ii).Y());
              else
                MapVerPar(E[k]).Append(ParOnL.Value(ii).Z());
            }
          }
        }
      }

      MapSeqPar.Bind(VF, ParOnF);
      MapSeqVer.Bind(VF, VOnF);
      MapSeqPar.Bind(VL, ParOnL);
      MapSeqVer.Bind(VL, VOnL);
    }
  }

  NCollection_DataMap<
    TopoDS_Shape,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>,
    TopTools_ShapeMapHasher>::Iterator ite1;
  TopoDS_Shape                         CurrentProf, PrecProf;
  TopoDS_Face                          CurrentFace;
  TopoDS_Shape                         CurrentSpine;
  TopoDS_Vertex                        VCF, VCL;

  for (ite1.Initialize(myMap); ite1.More(); ite1.Next())
  {
    CurrentSpine = ite1.Key();

    for (ProfExp.Init(myProfile); ProfExp.More(); ProfExp.Next())
    {
      CurrentProf = ProfExp.Current();
      EdgeVertices(TopoDS::Edge(CurrentProf), VCF, VCL);
      CurrentEdge = TopoDS::Edge(myMap(CurrentSpine)(VCF).First());

      if (MapBis.IsBound(CurrentEdge))
      {

        TopoDS_Shape FaceControle;
        bool         YaFace = true;

        FaceControle = myMap(CurrentSpine)(CurrentProf).First();
        if (!MapBis.IsBound(FaceControle))
        {
          YaFace = false;
          if (!PrecProf.IsNull())
          {
            FaceControle = myMap(CurrentSpine)(PrecProf).First();
            if (MapBis.IsBound(FaceControle))
            {
              YaFace = true;
            }
          }
        }

        if (YaFace)
        {

          NCollection_Sequence<TopoDS_Shape> aSeqOfShape;
          TrimEdge(CurrentEdge,
                   MapBis(FaceControle),
                   MapBis(CurrentEdge),
                   MapVerPar(CurrentEdge),
                   aSeqOfShape);

          for (k = 1; k <= aSeqOfShape.Length(); k++)
          {
            myMap(CurrentSpine)(VCF).Append(aSeqOfShape.Value(k));
          }
        }
      }
      PrecProf = CurrentProf;
    }

    CurrentEdge = TopoDS::Edge(myMap(CurrentSpine)(VCL).First());

    if (MapBis.IsBound(CurrentEdge))
    {
      bool         YaFace = true;
      TopoDS_Shape FaceControle;

      FaceControle = myMap(CurrentSpine)(CurrentProf).First();
      if (!MapBis.IsBound(FaceControle))
      {
        YaFace = false;
      }

      if (YaFace && myMap(CurrentSpine)(VCL).Extent() <= 1)
      {
        NCollection_Sequence<TopoDS_Shape> aSeqOfShape;
        TrimEdge(CurrentEdge,
                 MapBis(FaceControle),
                 MapBis(CurrentEdge),
                 MapVerPar(CurrentEdge),
                 aSeqOfShape);

        for (k = 1; k <= aSeqOfShape.Length(); k++)
        {
          myMap(CurrentSpine)(VCL).Append(aSeqOfShape.Value(k));
        }
      }
    }
  }

  for (ite1.Initialize(myMap); ite1.More(); ite1.Next())
  {
    CurrentSpine = ite1.Key();

    for (ProfExp.Init(myProfile); ProfExp.More(); ProfExp.Next())
    {
      CurrentProf = ProfExp.Current();
      CurrentFace = TopoDS::Face(myMap(CurrentSpine)(CurrentProf).First());
      myMap(CurrentSpine)(CurrentProf).Clear();

      if (MapBis.IsBound(CurrentFace))
      {

        EdgeVertices(TopoDS::Edge(CurrentProf), VCF, VCL);

        NCollection_List<TopoDS_Shape>::Iterator itl;
        const NCollection_List<TopoDS_Shape>&    LF = myMap(CurrentSpine)(VCF);

        TopAbs_Orientation Ori = BRepTools::OriEdgeInFace(TopoDS::Edge(LF.First()), CurrentFace);
        for (itl.Initialize(LF), itl.Next(); itl.More(); itl.Next())
        {
          TopoDS_Edge RE = TopoDS::Edge(itl.Value());
          MapBis(CurrentFace).Append(RE.Oriented(Ori));
        }
        const NCollection_List<TopoDS_Shape>& LL = myMap(CurrentSpine)(VCL);
        Ori = BRepTools::OriEdgeInFace(TopoDS::Edge(LL.First()), CurrentFace);
        for (itl.Initialize(LL), itl.Next(); itl.More(); itl.Next())
        {
          TopoDS_Edge RE = TopoDS::Edge(itl.Value());
          MapBis(CurrentFace).Append(RE.Oriented(Ori));
        }

        NCollection_Sequence<TopoDS_Shape> aSeqOfShape;

        TrimFace(CurrentFace, MapBis(CurrentFace), aSeqOfShape);

        for (int ii = 1; ii <= aSeqOfShape.Length(); ii++)
        {
          myBuilder.Add(myShape, aSeqOfShape.Value(ii));
          myMap(CurrentSpine)(CurrentProf).Append(aSeqOfShape.Value(ii));
        }
      }
    }

    TopExp_Explorer                                        Explo(myProfile, TopAbs_VERTEX);
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> vmap;

    for (; Explo.More(); Explo.Next())
    {
      if (vmap.Add(Explo.Current()))
      {
        myMap(CurrentSpine)(Explo.Current()).RemoveFirst();
      }
    }
  }
  myIsDone = true;
}

void BRepFill_Evolved::PlanarPerform(const TopoDS_Face&              Sp,
                                     const TopoDS_Wire&              Pr,
                                     const BRepMAT2d_BisectingLocus& Locus,
                                     BRepMAT2d_LinkTopoBilo&         Link,
                                     const GeomAbs_JoinType          Join)
{
  TopoDS_Shape aLocalShapeOriented = Sp.Oriented(TopAbs_FORWARD);
  mySpine                          = TopoDS::Face(aLocalShapeOriented);

  myProfile = Pr;
  myMap.Clear();

  BRep_Builder B;
  B.MakeCompound(TopoDS::Compound(myShape));

  BRepTools_WireExplorer ProfExp;
  TopExp_Explorer        Exp, exp1, exp2;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                           EmptyMap;
  NCollection_List<TopoDS_Shape>                                           EmptyList;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> MapVP;
  BRepFill_OffsetWire                                                      Paral;

  for (ProfExp.Init(myProfile); ProfExp.More(); ProfExp.Next())
  {
    const TopoDS_Edge&       E = ProfExp.Current();
    BRepAlgo_FaceRestrictor  FR;
    BRepFill_OffsetAncestors OffAnc;

    TopoDS_Vertex V[2];
    EdgeVertices(E, V[0], V[1]);
    double Alt = Altitud(V[0]);
    double Offset[2];
    Offset[0]    = DistanceToOZ(V[0]);
    Offset[1]    = DistanceToOZ(V[1]);
    bool IsMinV1 = (Offset[0] < Offset[1]);

    for (int i = 0; i <= 1; i++)
    {
      if (!MapVP.IsBound(V[i]))
      {

        Paral.PerformWithBiLo(mySpine, Offset[i], Locus, Link, Join, Alt);
        OffAnc.Perform(Paral);
        MapVP.Bind(V[i], Paral.Shape());

        for (Exp.Init(Paral.Shape(), TopAbs_EDGE); Exp.More(); Exp.Next())
        {
          const TopoDS_Edge&  WC = TopoDS::Edge(Exp.Current());
          const TopoDS_Shape& GS = OffAnc.Ancestor(WC);
          if (!myMap.IsBound(GS))
            myMap.Bind(GS, EmptyMap);
          if (!myMap(GS).IsBound(V[i]))
            myMap(GS).Bind(V[i], Paral.GeneratedShapes(GS));
        }
      }
      TopoDS_Shape Rest = MapVP(V[i]);

      bool ToReverse = false;
      if ((IsMinV1 && (i == 1)) || (!IsMinV1 && (i == 0)))
        ToReverse = true;

      if (!Rest.IsNull())
      {
        if (Rest.ShapeType() == TopAbs_WIRE)
        {
          if (ToReverse)
          {
            TopoDS_Shape aLocalShape = Rest.Reversed();
            TopoDS_Wire  aWire       = TopoDS::Wire(aLocalShape);
            FR.Add(aWire);
          }
          else
            FR.Add(TopoDS::Wire(Rest));
        }
        else
        {
          for (Exp.Init(Rest, TopAbs_WIRE); Exp.More(); Exp.Next())
          {
            TopoDS_Wire WCop = TopoDS::Wire(Exp.Current());
            if (ToReverse)
            {
              TopoDS_Shape aLocalShape = WCop.Reversed();
              TopoDS_Wire  bWire       = TopoDS::Wire(aLocalShape);

              FR.Add(bWire);
            }
            else
              FR.Add(WCop);
          }
        }
      }
    }

    gp_Trsf T;
    T.SetTranslation(gp_Vec(0, 0, Alt));
    TopLoc_Location LT(T);
    TopoDS_Shape    aLocalShape = mySpine.Moved(LT);
    FR.Init(TopoDS::Face(aLocalShape));

    FR.Perform();

    for (; FR.More(); FR.Next())
    {
      const TopoDS_Face& F = FR.Current();
      B.Add(myShape, F);

      for (Exp.Init(F, TopAbs_EDGE); Exp.More(); Exp.Next())
      {
        const TopoDS_Edge& CE = TopoDS::Edge(Exp.Current());
        if (OffAnc.HasAncestor(CE))
        {
          const TopoDS_Shape& InitE = OffAnc.Ancestor(CE);
          if (!myMap.IsBound(InitE))
            myMap.Bind(InitE, EmptyMap);
          if (!myMap(InitE).IsBound(E))
            myMap(InitE).Bind(E, EmptyList);
          myMap(InitE)(E).Append(F);
        }
      }
    }
  }
}

void BRepFill_Evolved::VerticalPerform(const TopoDS_Face&              Sp,
                                       const TopoDS_Wire&              Pr,
                                       const BRepMAT2d_BisectingLocus& Locus,
                                       BRepMAT2d_LinkTopoBilo&         Link,
                                       const GeomAbs_JoinType          Join)
{
  TopoDS_Shape aLocalShape = Sp.Oriented(TopAbs_FORWARD);
  mySpine                  = TopoDS::Face(aLocalShape);

  myProfile = Pr;
  myMap.Clear();

  BRep_Builder B;
  B.MakeCompound(TopoDS::Compound(myShape));

  BRepTools_WireExplorer   ProfExp;
  TopExp_Explorer          Exp;
  BRepFill_OffsetWire      Paral;
  BRepFill_OffsetAncestors OffAnc;
  TopoDS_Vertex            V1, V2;

  bool         First = true;
  TopoDS_Shape Base;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    EmptyMap;

  for (ProfExp.Init(myProfile); ProfExp.More(); ProfExp.Next())
  {
    const TopoDS_Edge& E = ProfExp.Current();
    EdgeVertices(E, V1, V2);
    double Alt1 = Altitud(V1);
    double Alt2 = Altitud(V2);

    if (First)
    {
      double Offset = DistanceToOZ(V1);
      if (std::abs(Offset) < BRepFill_Confusion())
      {
        Offset = 0.;
      }
      Paral.PerformWithBiLo(mySpine, Offset, Locus, Link, Join, Alt1);
      OffAnc.Perform(Paral);
      Base = Paral.Shape();

      for (Exp.Init(Base, TopAbs_EDGE); Exp.More(); Exp.Next())
      {
        const TopoDS_Edge&  anEdge = TopoDS::Edge(Exp.Current());
        const TopoDS_Shape& AE     = OffAnc.Ancestor(anEdge);
        if (!myMap.IsBound(AE))
        {
          myMap.Bind(AE, EmptyMap);
        }
        if (!myMap(AE).IsBound(V1))
        {
          NCollection_List<TopoDS_Shape> L;
          myMap(AE).Bind(V1, L);
        }
        myMap(AE)(V1).Append(anEdge);
      }
      First = false;
    }

    BRepSweep_Prism PS(Base, gp_Vec(0, 0, Alt2 - Alt1), false);

    Base = PS.LastShape();

    for (Exp.Init(PS.Shape(), TopAbs_FACE); Exp.More(); Exp.Next())
    {
      B.Add(myShape, Exp.Current());
    }

    NCollection_DataMap<
      TopoDS_Shape,
      NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>,
      TopTools_ShapeMapHasher>::Iterator it(myMap);

    for (; it.More(); it.Next())
    {
      const NCollection_List<TopoDS_Shape>&    LOF = it.Value()(V1);
      NCollection_List<TopoDS_Shape>::Iterator itLOF(LOF);
      if (!myMap(it.Key()).IsBound(V2))
      {
        NCollection_List<TopoDS_Shape> L;
        myMap(it.Key()).Bind(V2, L);
      }

      if (!myMap(it.Key()).IsBound(E))
      {
        NCollection_List<TopoDS_Shape> L;
        myMap(it.Key()).Bind(E, L);
      }

      for (; itLOF.More(); itLOF.Next())
      {
        const TopoDS_Shape& OS = itLOF.Value();
        myMap(it.Key())(V2).Append(PS.LastShape(OS));
        myMap(it.Key())(E).Append(PS.Shape(OS));
      }
    }
  }
}

static void Bubble(NCollection_Sequence<double>& Seq)
{
  bool Invert   = true;
  int  NbPoints = Seq.Length();

  while (Invert)
  {
    Invert = false;
    for (int i = 1; i < NbPoints; i++)
    {
      if (Seq.Value(i + 1) < Seq.Value(i))
      {
        Seq.Exchange(i, i + 1);
        Invert = true;
      }
    }
  }
}

void BRepFill_Evolved::PrepareProfile(
  NCollection_List<TopoDS_Shape>&                                           WorkProf,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& MapProf) const
{

  occ::handle<Geom_Plane>  Plane = new Geom_Plane(gp_Ax3(gp::YOZ()));
  occ::handle<Geom2d_Line> Line  = new Geom2d_Line(gp::OY2d());

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> MapVerRefMoved;

  TopoDS_Vertex                  V1, V2, VRef1, VRef2;
  TopoDS_Wire                    W;
  BRep_Builder                   B;
  NCollection_List<TopoDS_Shape> WP;
  B.MakeWire(W);
  WP.Append(W);

  BRepTools_WireExplorer Exp(myProfile);

  while (Exp.More())
  {
    NCollection_List<TopoDS_Shape> Cuts;
    bool                           NewWire = false;
    const TopoDS_Edge&             E       = TopoDS::Edge(Exp.Current());

    CutEdgeProf(E, Plane, Line, Cuts, MapVerRefMoved);

    EdgeVertices(E, VRef1, VRef2);

    if (Cuts.IsEmpty())
    {

      B.Add(W, E);
      MapProf.Bind(E, E);
    }
    else
    {
      while (!Cuts.IsEmpty())
      {
        const TopoDS_Edge& NE = TopoDS::Edge(Cuts.First());
        MapProf.Bind(NE, E);
        EdgeVertices(NE, V1, V2);
        if (!MapProf.IsBound(V1))
          MapProf.Bind(V1, E);
        if (!MapProf.IsBound(V2))
          MapProf.Bind(V2, E);

        B.Add(W, NE);
        Cuts.RemoveFirst();

        if (DistanceToOZ(V2) < BRepFill_Confusion() && DistanceToOZ(V1) > BRepFill_Confusion())
        {

          if (Cuts.IsEmpty())
          {

            NewWire = true;
          }
          else
          {

            B.MakeWire(W);
            WP.Append(W);
          }
        }
      }
    }
    Exp.Next();
    if (Exp.More() && NewWire)
    {
      B.MakeWire(W);
      WP.Append(W);
    }
  }

  NCollection_List<TopoDS_Shape>::Iterator ite;
  TopoDS_Wire                              CurW, NW;
  TopExp_Explorer                          EW;

  for (ite.Initialize(WP); ite.More(); ite.Next())
  {
    CurW         = TopoDS::Wire(ite.Value());
    bool YaModif = false;
    for (EW.Init(CurW, TopAbs_EDGE); EW.More(); EW.Next())
    {
      const TopoDS_Edge& EE = TopoDS::Edge(EW.Current());
      if (IsVertical(EE) || IsPlanar(EE))
      {
        YaModif = true;
        break;
      }
    }

    if (YaModif)
    {

      int Status = 0;

      for (EW.Init(CurW, TopAbs_EDGE); EW.More(); EW.Next())
      {
        const TopoDS_Edge& EE = TopoDS::Edge(EW.Current());
        if (IsVertical(EE))
        {
          if (Status != 3)
          {
            B.MakeWire(NW);
            WorkProf.Append(NW);
            Status = 3;
          }
        }
        else if (IsPlanar(EE))
        {
          if (Status != 2)
          {
            B.MakeWire(NW);
            WorkProf.Append(NW);
            Status = 2;
          }
        }
        else if (Status != 1)
        {
          B.MakeWire(NW);
          WorkProf.Append(NW);
          Status = 1;
        }
        B.Add(NW, EE);
      }
    }
    else
    {
      WorkProf.Append(CurW);
    }
  }

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator gilbert(
    MapVerRefMoved);
  for (; gilbert.More(); gilbert.Next())
  {
    MapProf.Bind(gilbert.Value(), gilbert.Key());
  }
}

void BRepFill_Evolved::PrepareSpine(
  TopoDS_Face&                                                              WorkSpine,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& MapSpine) const
{
  BRep_Builder                             B;
  NCollection_List<TopoDS_Shape>           Cuts;
  NCollection_List<TopoDS_Shape>::Iterator IteCuts;
  TopoDS_Vertex                            V1, V2;

  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S    = BRep_Tool::Surface(mySpine, L);
  double                           TolF = BRep_Tool::Tolerance(mySpine);
  B.MakeFace(WorkSpine, S, L, TolF);

  for (TopoDS_Iterator IteF(mySpine); IteF.More(); IteF.Next())
  {

    TopoDS_Wire NW;
    B.MakeWire(NW);
    bool IsClosed = IteF.Value().Closed();

    for (TopoDS_Iterator IteW(IteF.Value()); IteW.More(); IteW.Next())
    {

      TopoDS_Edge E = TopoDS::Edge(IteW.Value());
      EdgeVertices(E, V1, V2);
      MapSpine.Bind(V1, V1);
      MapSpine.Bind(V2, V2);
      Cuts.Clear();

      CutEdge(E, mySpine, Cuts);

      if (Cuts.IsEmpty())
      {
        B.Add(NW, E);
        MapSpine.Bind(E, E);
      }
      else
      {
        for (IteCuts.Initialize(Cuts); IteCuts.More(); IteCuts.Next())
        {
          const TopoDS_Edge& NE = TopoDS::Edge(IteCuts.Value());
          B.Add(NW, NE);
          MapSpine.Bind(NE, E);
          EdgeVertices(NE, V1, V2);
          if (!MapSpine.IsBound(V1))
            MapSpine.Bind(V1, E);
          if (!MapSpine.IsBound(V2))
            MapSpine.Bind(V2, E);
        }
      }
    }
    NW.Closed(IsClosed);
    B.Add(WorkSpine, NW);
  }

  BRepLib::BuildCurves3d(WorkSpine);
}

const TopoDS_Shape& BRepFill_Evolved::Top() const
{
  return myTop;
}

const TopoDS_Shape& BRepFill_Evolved::Bottom() const
{
  return myBottom;
}

const NCollection_List<TopoDS_Shape>& BRepFill_Evolved::GeneratedShapes(
  const TopoDS_Shape& SpineShape,
  const TopoDS_Shape& ProfShape) const
{
  if (myMap.IsBound(SpineShape) && myMap(SpineShape).IsBound(ProfShape))
  {
    return myMap(SpineShape)(ProfShape);
  }
  else
  {
    static NCollection_List<TopoDS_Shape> Empty;
    return Empty;
  }
}

NCollection_DataMap<
  TopoDS_Shape,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>,
  TopTools_ShapeMapHasher>&
  BRepFill_Evolved::Generated()
{
  return myMap;
}

static TopAbs_Orientation Compare(const TopoDS_Edge& E1, const TopoDS_Edge& E2)
{
  TopAbs_Orientation OO = TopAbs_FORWARD;
  TopoDS_Vertex      V1[2], V2[2];
  TopExp::Vertices(E1, V1[0], V1[1]);
  TopExp::Vertices(E2, V2[0], V2[1]);
  gp_Pnt P1 = BRep_Tool::Pnt(V1[0]);
  gp_Pnt P2 = BRep_Tool::Pnt(V2[0]);
  gp_Pnt P3 = BRep_Tool::Pnt(V2[1]);
  if (P1.Distance(P3) < P1.Distance(P2))
    OO = TopAbs_REVERSED;

  return OO;
}

void BRepFill_Evolved::Add(BRepFill_Evolved& Vevo, const TopoDS_Wire& Prof, BRepTools_Quilt& Glue)

{
  NCollection_DataMap<
    TopoDS_Shape,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>,
    TopTools_ShapeMapHasher>& MapVevo = Vevo.Generated();
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator iteP;
  NCollection_DataMap<
    TopoDS_Shape,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>,
    TopTools_ShapeMapHasher>::Iterator iteS;
  TopoDS_Shape                         CurrentSpine, CurrentProf;

  if (Vevo.Shape().IsNull())
    return;

  TopExp_Explorer ExProf;
  for (ExProf.Init(Prof, TopAbs_VERTEX); ExProf.More(); ExProf.Next())
  {
    const TopoDS_Shape& VV = ExProf.Current();

    bool Commun = false;
    Relative(myProfile, Prof, TopoDS::Vertex(VV), Commun);

    if (Commun)
    {
      for (iteS.Initialize(myMap); iteS.More(); iteS.Next())
      {
        const TopoDS_Shape& SP = iteS.Key();
        if (iteS.Value().IsBound(VV) && MapVevo.IsBound(SP) && MapVevo(SP).IsBound(VV))
        {

          const NCollection_List<TopoDS_Shape>&    MyList   = myMap(SP)(VV);
          const NCollection_List<TopoDS_Shape>&    VevoList = Vevo.GeneratedShapes(SP, VV);
          NCollection_List<TopoDS_Shape>::Iterator MyIte(MyList);
          NCollection_List<TopoDS_Shape>::Iterator VevoIte(VevoList);
          for (; MyIte.More(); MyIte.Next(), VevoIte.Next())
          {
            const TopoDS_Edge& ME           = TopoDS::Edge(MyIte.Value());
            const TopoDS_Edge& VE           = TopoDS::Edge(VevoIte.Value());
            TopAbs_Orientation OG           = Compare(ME, VE);
            TopoDS_Shape       aLocalShape  = VE.Oriented(TopAbs_FORWARD);
            TopoDS_Shape       aLocalShape2 = ME.Oriented(OG);
            Glue.Bind(TopoDS::Edge(aLocalShape), TopoDS::Edge(aLocalShape2));
          }
        }
      }
    }
  }
  Glue.Add(Vevo.Shape());

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                 EmptyMap;
  NCollection_List<TopoDS_Shape> EmptyList;

  for (iteS.Initialize(MapVevo); iteS.More(); iteS.Next())
  {
    CurrentSpine = iteS.Key();
    for (iteP.Initialize(MapVevo(CurrentSpine)); iteP.More(); iteP.Next())
    {
      CurrentProf = iteP.Key();
      if (!myMap.IsBound(CurrentSpine))
      {

        myMap.Bind(CurrentSpine, EmptyMap);
      }
      if (!myMap(CurrentSpine).IsBound(CurrentProf))
      {
        myMap(CurrentSpine).Bind(CurrentProf, EmptyList);
        const NCollection_List<TopoDS_Shape>&    GenShapes = MapVevo(CurrentSpine)(CurrentProf);
        NCollection_List<TopoDS_Shape>::Iterator itl(GenShapes);
        for (; itl.More(); itl.Next())
        {

          if (Glue.IsCopied(itl.Value()))
            myMap(CurrentSpine)(CurrentProf).Append(Glue.Copy(itl.Value()));
          else
            myMap(CurrentSpine)(CurrentProf).Append(itl.Value());
        }
      }
    }
  }
}

TopoDS_Shape& BRepFill_Evolved::ChangeShape()
{
  return myShape;
}

void BRepFill_Evolved::Transfert(
  BRepFill_Evolved&                                                               Vevo,
  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& MapProf,
  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& MapSpine,
  const TopLoc_Location&                                                          LS,
  const TopLoc_Location&                                                          InitLS,
  const TopLoc_Location&                                                          InitLP)
{

  myShape = Vevo.Shape();
  mySpine.Location(InitLS);
  myProfile.Location(InitLP);
  myShape.Move(LS);

  BRep_Builder    B;
  TopExp_Explorer ex(myShape, TopAbs_EDGE);
  while (ex.More())
  {
    B.SameRange(TopoDS::Edge(ex.Current()), false);
    B.SameParameter(TopoDS::Edge(ex.Current()), false);
    BRepLib::SameParameter(TopoDS::Edge(ex.Current()));
    ex.Next();
  }

  NCollection_DataMap<
    TopoDS_Shape,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>,
    TopTools_ShapeMapHasher>::Iterator iteS;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator iteP;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                 EmptyMap;
  NCollection_List<TopoDS_Shape> EmptyList;
  TopoDS_Shape                   InitialSpine, InitialProf;

  NCollection_DataMap<
    TopoDS_Shape,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>,
    TopTools_ShapeMapHasher>& MapVevo = Vevo.Generated();

  for (iteS.Initialize(MapVevo); iteS.More(); iteS.Next())
  {
    InitialSpine = MapSpine(iteS.Key());
    InitialSpine.Move(LS);

    for (iteP.Initialize(MapVevo(iteS.Key())); iteP.More(); iteP.Next())
    {
      InitialProf = MapProf(iteP.Key());
      InitialProf.Location(InitLP);

      NCollection_List<TopoDS_Shape>& GenShapes =
        MapVevo.ChangeFind(iteS.Key()).ChangeFind(iteP.Key());

      NCollection_List<TopoDS_Shape>::Iterator itl;
      for (itl.Initialize(GenShapes); itl.More(); itl.Next())
      {
        itl.ChangeValue().Move(LS);
      }

      if (!myMap.IsBound(InitialSpine))
      {
        myMap.Bind(InitialSpine, EmptyMap);
      }

      if (!myMap(InitialSpine).IsBound(InitialProf))
      {
        myMap(InitialSpine).Bind(InitialProf, EmptyList);
      }
      myMap(InitialSpine)(InitialProf).Append(GenShapes);
    }
  }

  myTop = Vevo.Top();
  myTop.Move(LS);
  myBottom = Vevo.Bottom();
  myBottom.Move(LS);
}

bool BRepFill_Evolved::IsDone() const
{
  return myIsDone;
}

const TopoDS_Shape& BRepFill_Evolved::Shape() const
{
  return myShape;
}

GeomAbs_JoinType BRepFill_Evolved::JoinType() const
{
  return myJoinType;
}

void BRepFill_Evolved::AddTopAndBottom(BRepTools_Quilt& Glue)
{

  TopoDS_Vertex V[2];
  TopExp::Vertices(myProfile, V[0], V[1]);
  if (V[0].IsSame(V[1]))
    return;

  NCollection_List<TopoDS_Shape>::Iterator itL;
  bool                                     ToReverse = false;
  for (int i = 0; i <= 1; i++)
  {

    BRepAlgo_Loop Loop;

    gp_Pln      S(0., 0., 1., -Altitud(V[i]));
    TopoDS_Face F = BRepLib_MakeFace(S);
    Loop.Init(F);

    TopExp_Explorer                                        ExpSpine(mySpine, TopAbs_EDGE);
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> View;

    for (; ExpSpine.More(); ExpSpine.Next())
    {
      const TopoDS_Edge&                    ES                 = TopoDS::Edge(ExpSpine.Current());
      const NCollection_List<TopoDS_Shape>& L                  = GeneratedShapes(ES, V[i]);
      bool                                  ComputeOrientation = false;

      for (itL.Initialize(L); itL.More(); itL.Next())
      {
        const TopoDS_Edge& E = TopoDS::Edge(itL.Value());

        if (!ComputeOrientation)
        {
          BRepAdaptor_Curve C1(ES);
          BRepAdaptor_Curve C2(E);
          double            f, l, fs, ls;
          BRep_Tool::Range(E, f, l);
          BRep_Tool::Range(ES, fs, ls);
          double u  = 0.3 * f + 0.7 * l;
          double us = 0.3 * fs + 0.7 * ls;
          gp_Pnt P;
          gp_Vec V1, V2;
          C1.D1(us, P, V1);
          C2.D1(u, P, V2);
          ToReverse          = (V1.Dot(V2) < 0.);
          ComputeOrientation = true;
        }

        TopAbs_Orientation Or = ES.Orientation();
        if (ToReverse)
          Or = TopAbs::Reverse(Or);
        TopoDS_Shape aLocalShape = E.Oriented(Or);
        Loop.AddConstEdge(TopoDS::Edge(aLocalShape));
      }
    }

    gp_Pnt PV    = BRep_Tool::Pnt(V[i]);
    bool   IsOut = PV.Y() < 0;

    for (ExpSpine.Init(mySpine, TopAbs_VERTEX); ExpSpine.More(); ExpSpine.Next())
    {
      const TopoDS_Vertex& ES = TopoDS::Vertex(ExpSpine.Current());
      if (View.Add(ES))
      {
        const NCollection_List<TopoDS_Shape>& L = GeneratedShapes(ES, V[i]);
        for (itL.Initialize(L); itL.More(); itL.Next())
        {
          const TopoDS_Edge& E = TopoDS::Edge(itL.Value());
          if (!BRep_Tool::Degenerated(E))
          {

            BRepAdaptor_Curve C(E);
            double            f, l;
            BRep_Tool::Range(E, f, l);
            double u = 0.3 * f + 0.7 * l;
            gp_Pnt P = BRep_Tool::Pnt(ES);
            gp_Pnt PC;
            gp_Vec VC;
            C.D1(u, PC, VC);
            gp_Vec aPPC(P, PC);
            gp_Vec Prod = aPPC.Crossed(VC);
            if (IsOut)
            {
              ToReverse = Prod.Z() < 0.;
            }
            else
            {
              ToReverse = Prod.Z() > 0.;
            }
            TopAbs_Orientation Or = TopAbs_FORWARD;
            if (ToReverse)
              Or = TopAbs_REVERSED;
            TopoDS_Shape aLocalShape = E.Oriented(Or);
            Loop.AddConstEdge(TopoDS::Edge(aLocalShape));
          }
        }
      }
    }

    Loop.Perform();
    Loop.WiresToFaces();
    const NCollection_List<TopoDS_Shape>&    L = Loop.NewFaces();
    NCollection_List<TopoDS_Shape>::Iterator anIterL(L);

    TopoDS_Compound Bouchon;
    BRep_Builder    B;
    B.MakeCompound(Bouchon);
    int j = 0;

    for (anIterL.Initialize(L); anIterL.More(); anIterL.Next())
    {
      j++;
      Glue.Add(anIterL.Value());
      if (j == 1 && i == 0)
        myTop = anIterL.Value();
      if (j == 1 && i == 1)
        myBottom = anIterL.Value();
      B.Add(Bouchon, anIterL.Value());
    }
    if (i == 0 && j > 1)
      myTop = Bouchon;
    if (i == 1 && j > 1)
      myBottom = Bouchon;
  }
}

void BRepFill_Evolved::MakeSolid()
{

  TopExp_Explorer exp(myShape, TopAbs_SHELL);
  int             ish = 0;
  TopoDS_Compound Res;
  TopoDS_Solid    Sol;
  BRep_Builder    B;
  B.MakeCompound(Res);

  for (; exp.More(); exp.Next())
  {
    const TopoDS_Shape& Sh = exp.Current();
    B.MakeSolid(Sol);
    B.Add(Sol, Sh);
    BRepClass3d_SolidClassifier SC(Sol);
    SC.PerformInfinitePoint(BRepFill_Confusion());
    if (SC.State() == TopAbs_IN)
    {
      B.MakeSolid(Sol);
      B.Add(Sol, Sh.Reversed());
    }
    B.Add(Res, Sol);
    ish++;
  }
  if (ish == 1)
  {
    myShape = Sol;
  }
  else
  {
    myShape = Res;
  }
}

void BRepFill_Evolved::MakePipe(const TopoDS_Edge& SE, const gp_Ax3& AxeRef)
{
  BRepTools_WireExplorer ProfExp;
  TopExp_Explorer        FaceExp;

  gp_Trsf trsf;
  if (Side(myProfile, BRepFill_Confusion()) > 3)
  {
    trsf.SetRotation(gp::OZ(), M_PI);
  }
  TopLoc_Location DumLoc(trsf);
  TopoDS_Shape    aLocalShape = myProfile.Moved(DumLoc);
  TopoDS_Wire     DummyProf   = PutProfilAt(TopoDS::Wire(aLocalShape), AxeRef, SE, mySpine, true);

  occ::handle<BRepTools_TrsfModification> TrsfMod = new BRepTools_TrsfModification(gp_Trsf());
  BRepTools_Modifier                      Modif(DummyProf, TrsfMod);

  TopoDS_Wire GenProf = TopoDS::Wire(Modif.ModifiedShape(DummyProf));

  BRepFill_Pipe Pipe(BRepLib_MakeWire(SE), GenProf);

  BRepTools_WireExplorer         GenProfExp;
  NCollection_List<TopoDS_Shape> L;
  TopoDS_Vertex                  VF, VL, VFG, VLG;
  bool                           FirstVertex = true;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> P;

  myMap.Bind(SE, P);

  for (ProfExp.Init(myProfile), GenProfExp.Init(GenProf); ProfExp.More();
       ProfExp.Next(), GenProfExp.Next())
  {

    EdgeVertices(ProfExp.Current(), VF, VL);
    EdgeVertices(GenProfExp.Current(), VFG, VLG);

    if (FirstVertex)
    {
      myMap(SE).Bind(VF, L);
      myMap(SE)(VF).Append(Pipe.Edge(SE, VFG));
      FirstVertex = false;
    }
    myMap(SE).Bind(VL, L);
    myMap(SE)(VL).Append(Pipe.Edge(SE, VLG));
    myMap(SE).Bind(ProfExp.Current(), L);
    myMap(SE)(ProfExp.Current()).Append(Pipe.Face(SE, GenProfExp.Current()));
  }
}

void BRepFill_Evolved::MakeRevol(const TopoDS_Edge&   SE,
                                 const TopoDS_Vertex& VLast,
                                 const gp_Ax3&        AxeRef)
{
  BRepTools_WireExplorer ProfExp;
  TopExp_Explorer        FaceExp;

  gp_Trsf trsf;
  if (Side(myProfile, BRepFill_Confusion()) > 3)
  {
    trsf.SetRotation(gp::OZ(), M_PI);
  }
  TopLoc_Location DumLoc(trsf);
  TopoDS_Shape    aLocalShape = myProfile.Moved(DumLoc);
  TopoDS_Wire     GenProf     = PutProfilAt(TopoDS::Wire(aLocalShape), AxeRef, SE, mySpine, false);

  gp_Ax1 AxeRev(BRep_Tool::Pnt(VLast), -gp::DZ());

  gp_Trsf dummy;
  dummy.SetRotation(AxeRev, 1.5 * M_PI);
  TopLoc_Location DummyLoc(dummy);
  GenProf.Move(DummyLoc);

  BRepSweep_Revol Rev(GenProf, AxeRev, true);

  BRepTools_WireExplorer         GenProfExp;
  NCollection_List<TopoDS_Shape> L;
  TopoDS_Vertex                  VF, VL, VFG, VLG;
  bool                           FirstVertex = true;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> R;

  myMap.Bind(VLast, R);

  for (ProfExp.Init(myProfile), GenProfExp.Init(GenProf); ProfExp.More();
       ProfExp.Next(), GenProfExp.Next())
  {

    EdgeVertices(ProfExp.Current(), VF, VL);
    EdgeVertices(GenProfExp.Current(), VFG, VLG);

    TopAbs_Orientation Or = GenProfExp.Current().Orientation();

    if (FirstVertex)
    {
      myMap(VLast).Bind(VF, L);
      const TopoDS_Shape& RV = Rev.Shape(VFG);

      TopAbs_Orientation OO = RV.Orientation();
      myMap(VLast)(VF).Append(RV.Oriented(OO));
      FirstVertex = false;
    }
    myMap(VLast).Bind(ProfExp.Current(), L);
    const TopoDS_Shape& RF = Rev.Shape(GenProfExp.Current());
    TopAbs_Orientation  OO = TopAbs::Compose(RF.Orientation(), Or);

    myMap(VLast)(ProfExp.Current()).Append(RF.Oriented(OO));
    myMap(VLast).Bind(VL, L);
    const TopoDS_Shape& RV = Rev.Shape(VLG);

    OO = RV.Orientation();
    myMap(VLast)(VL).Append(RV.Oriented(OO));
  }
}

TopLoc_Location BRepFill_Evolved::FindLocation(const TopoDS_Face& Face) const
{
  TopLoc_Location           L;
  occ::handle<Geom_Surface> S;
  S = BRep_Tool::Surface(Face, L);

  if (!S->IsKind(STANDARD_TYPE(Geom_Plane)))
  {
    BRepLib_FindSurface FS(Face, -1, true);
    if (FS.Found())
    {
      S = FS.Surface();
      L = FS.Location();
    }
    else
      throw Standard_NoSuchObject("BRepFill_Evolved : The Face is not planar");
  }

  if (!L.IsIdentity())
    S = occ::down_cast<Geom_Surface>(S->Transformed(L.Transformation()));

  occ::handle<Geom_Plane> P    = occ::down_cast<Geom_Plane>(S);
  gp_Ax3                  Axis = P->Position();

  gp_Trsf T;
  gp_Ax3  AxeRef(gp_Pnt(0., 0., 0.), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X));
  T.SetTransformation(AxeRef, Axis);

  return TopLoc_Location(T);
}

void BRepFill_Evolved::TransformInitWork(const TopLoc_Location& LS, const TopLoc_Location& LP)
{
  mySpine.Move(LS);
  myProfile.Move(LP);
}

void BRepFill_Evolved::ContinuityOnOffsetEdge(const NCollection_List<TopoDS_Shape>&)
{
  BRepTools_WireExplorer WExp;
  NCollection_DataMap<
    TopoDS_Shape,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>,
    TopTools_ShapeMapHasher>::Iterator iteS;
  TopoDS_Vertex                        VF, VL, V;
  TopoDS_Edge                          PrecE, CurE, FirstE;
  BRep_Builder                         B;

  WExp.Init(myProfile);
  FirstE = WExp.Current();
  PrecE  = FirstE;
  EdgeVertices(FirstE, VF, V);
  if (WExp.More())
    WExp.Next();

  for (; WExp.More(); WExp.Next())
  {
    CurE = WExp.Current();
    V    = WExp.CurrentVertex();

    if (DistanceToOZ(V) <= BRepFill_Confusion())
    {

      double            U1 = BRep_Tool::Parameter(V, CurE);
      double            U2 = BRep_Tool::Parameter(V, PrecE);
      BRepAdaptor_Curve Curve1(CurE);
      BRepAdaptor_Curve Curve2(PrecE);
      GeomAbs_Shape     Continuity = BRepLProp::Continuity(Curve1, Curve2, U1, U2);

      if (Continuity >= 1)
      {

        for (iteS.Initialize(myMap); iteS.More(); iteS.Next())
        {
          const TopoDS_Shape& SP = iteS.Key();
          if (myMap(SP).IsBound(V) && myMap(SP).IsBound(CurE) && myMap(SP).IsBound(PrecE))
          {
            if (!myMap(SP)(V).IsEmpty() && !myMap(SP)(CurE).IsEmpty()
                && !myMap(SP)(PrecE).IsEmpty())
              B.Continuity(TopoDS::Edge(myMap(SP)(V).First()),
                           TopoDS::Face(myMap(SP)(CurE).First()),
                           TopoDS::Face(myMap(SP)(PrecE).First()),
                           Continuity);
          }
        }
      }
    }
    PrecE = CurE;
  }

  EdgeVertices(PrecE, V, VL);

  if (VF.IsSame(VL))
  {

    double            U1 = BRep_Tool::Parameter(VF, CurE);
    double            U2 = BRep_Tool::Parameter(VF, FirstE);
    BRepAdaptor_Curve Curve1(CurE);
    BRepAdaptor_Curve Curve2(FirstE);
    GeomAbs_Shape     Continuity = BRepLProp::Continuity(Curve1, Curve2, U1, U2);

    if (Continuity >= 1)
    {

      for (iteS.Initialize(myMap); iteS.More(); iteS.Next())
      {
        const TopoDS_Shape& SP = iteS.Key();
        if (myMap(SP).IsBound(VF) && myMap(SP).IsBound(CurE) && myMap(SP).IsBound(FirstE))
        {
          if (!myMap(SP)(VF).IsEmpty() && !myMap(SP)(CurE).IsEmpty()
              && !myMap(SP)(FirstE).IsEmpty())
            B.Continuity(TopoDS::Edge(myMap(SP)(VF).First()),
                         TopoDS::Face(myMap(SP)(CurE).First()),
                         TopoDS::Face(myMap(SP)(FirstE).First()),
                         Continuity);
        }
      }
    }
  }
}

static void AddDegeneratedEdge(TopoDS_Face& F, TopoDS_Wire& W)
{
  TopLoc_Location           L;
  occ::handle<Geom_Surface> S = BRep_Tool::Surface(F, L);
  if (S->DynamicType() == STANDARD_TYPE(Geom_RectangularTrimmedSurface))
  {
    occ::handle<Geom_Surface> SB =
      occ::down_cast<Geom_RectangularTrimmedSurface>(S)->BasisSurface();
    if (SB->DynamicType() == STANDARD_TYPE(Geom_Plane))
    {
      return;
    }
  }

  if (S->DynamicType() == STANDARD_TYPE(Geom_Plane))
  {
    return;
  }

  BRep_Builder B;
  double       TolConf = 1.e-4;

  bool Change = true;

  while (Change)
  {
    Change = false;
    BRepTools_WireExplorer WE(W, F);
    gp_Pnt2d               PF, PrevP, P1, P2;
    TopoDS_Vertex          VF, V1, V2;

    for (; WE.More(); WE.Next())
    {
      const TopoDS_Edge& CE = WE.Current();
      EdgeVertices(CE, V1, V2);
      if (CE.Orientation() == TopAbs_REVERSED)
        BRep_Tool::UVPoints(CE, F, P2, P1);
      else
        BRep_Tool::UVPoints(CE, F, P1, P2);
      if (VF.IsNull())
      {
        VF = V1;
        PF = P1;
      }
      else
      {
        if (!P1.IsEqual(PrevP, TolConf))
        {

          Change = true;
          gp_Vec2d                         V(PrevP, P1);
          occ::handle<Geom2d_Line>         C2d = new Geom2d_Line(PrevP, gp_Dir2d(V));
          double                           f = 0, l = PrevP.Distance(P1);
          occ::handle<Geom2d_TrimmedCurve> CT = new Geom2d_TrimmedCurve(C2d, f, l);
          TopoDS_Edge                      NE = BRepLib_MakeEdge(C2d, S);
          B.Degenerated(NE, true);
          B.Add(NE, V1.Oriented(TopAbs_FORWARD));
          B.Add(NE, V1.Oriented(TopAbs_REVERSED));
          B.Range(NE, f, l);
          B.Add(W, NE);
          break;
        }
      }
      PrevP = P2;
    }
    if (!Change && VF.IsSame(V2))
    {
      if (!PF.IsEqual(P2, TolConf))
      {

        Change = true;
        gp_Vec2d                         V(P2, PF);
        occ::handle<Geom2d_Line>         C2d = new Geom2d_Line(P2, gp_Dir2d(V));
        double                           f = 0, l = P2.Distance(PF);
        occ::handle<Geom2d_TrimmedCurve> CT = new Geom2d_TrimmedCurve(C2d, f, l);
        TopoDS_Edge                      NE = BRepLib_MakeEdge(C2d, S);
        B.Degenerated(NE, true);
        B.Add(NE, VF.Oriented(TopAbs_FORWARD));
        B.Add(NE, VF.Oriented(TopAbs_REVERSED));
        B.Range(NE, f, l);
        B.Add(W, NE);
      }
    }
  }
}

void TrimFace(const TopoDS_Face&                  Face,
              NCollection_Sequence<TopoDS_Shape>& TheEdges,
              NCollection_Sequence<TopoDS_Shape>& S)
{

  BRep_Builder TheBuilder;

  int         NbEdges;
  bool        NewWire = true;
  bool        AddEdge = false;
  TopoDS_Wire GoodWire;

  while (!TheEdges.IsEmpty())
  {

    BRepLib_MakeWire MWire(TopoDS::Edge(TheEdges.First()));
    GoodWire = MWire.Wire();
    TheEdges.Remove(1);
    NbEdges = TheEdges.Length();
    NewWire = false;

    while (!NewWire)
    {
      AddEdge = false;

      for (int i = 1; i <= NbEdges && !AddEdge; i++)
      {
        const TopoDS_Edge& E = TopoDS::Edge(TheEdges.Value(i));
        if (BRep_Tool::Degenerated(E))
        {
          TheEdges.Remove(i);
          AddEdge  = true;
          NbEdges  = TheEdges.Length();
          GoodWire = MWire.Wire();
        }
        else
        {
          MWire.Add(E);
          if (MWire.Error() == BRepLib_WireDone)
          {

            TheEdges.Remove(i);
            AddEdge  = true;
            NbEdges  = TheEdges.Length();
            GoodWire = MWire.Wire();
          }
        }
      }
      NewWire = (!AddEdge);
    }
    TopoDS_Shape aLocalShape = Face.EmptyCopied();
    TopoDS_Face  FaceCut     = TopoDS::Face(aLocalShape);

    FaceCut.Orientation(TopAbs_FORWARD);
    BRepTools::Update(FaceCut);
    AddDegeneratedEdge(FaceCut, GoodWire);
    TheBuilder.Add(FaceCut, GoodWire);
    FaceCut.Orientation(Face.Orientation());
    S.Append(FaceCut);
  }
}

const TopoDS_Wire PutProfilAt(const TopoDS_Wire& ProfRef,
                              const gp_Ax3&      AxeRef,
                              const TopoDS_Edge& E,
                              const TopoDS_Face& F,
                              const bool         AtStart)
{
  gp_Vec2d                  D1;
  gp_Pnt2d                  P;
  TopoDS_Wire               Prof;
  occ::handle<Geom2d_Curve> C2d;
  double                    First, Last;

  C2d = BRep_Tool::CurveOnSurface(E, F, First, Last);
  if (C2d.IsNull())
  {
    throw Standard_ConstructionError("ConstructionError in PutProfilAt");
  }

  if (E.Orientation() == TopAbs_REVERSED)
  {
    if (!AtStart)
      C2d->D1(First, P, D1);
    else
      C2d->D1(Last, P, D1);
    D1.Reverse();
  }
  else
  {
    if (!AtStart)
      C2d->D1(Last, P, D1);
    else
      C2d->D1(First, P, D1);
  }
  gp_Pnt P3d(P.X(), P.Y(), 0.);
  gp_Vec V3d(D1.X(), D1.Y(), 0.);

  gp_Ax3  Ax(P3d, gp::DZ(), V3d);
  gp_Trsf Trans;
  Trans.SetTransformation(Ax, AxeRef);
  TopoDS_Shape aLocalShape = ProfRef.Moved(TopLoc_Location(Trans));
  Prof                     = TopoDS::Wire(aLocalShape);

  return Prof;
}

void TrimEdge(const TopoDS_Edge&                        Edge,
              const NCollection_Sequence<TopoDS_Shape>& TheEdgesControle,
              NCollection_Sequence<TopoDS_Shape>&       TheVer,
              NCollection_Sequence<double>&             ThePar,
              NCollection_Sequence<TopoDS_Shape>&       S)
{
  bool         Change = true;
  BRep_Builder TheBuilder;
  S.Clear();

  while (Change)
  {
    Change = false;
    for (int i = 1; i < ThePar.Length(); i++)
    {
      if (ThePar.Value(i) > ThePar.Value(i + 1))
      {
        ThePar.Exchange(i, i + 1);
        TheVer.Exchange(i, i + 1);
        Change = true;
      }
    }
  }

  if (!BRep_Tool::Degenerated(Edge))
  {
    for (int k = 1; k <= TheVer.Length(); k++)
    {
      if (DoubleOrNotInFace(TheEdgesControle, TopoDS::Vertex(TheVer.Value(k))))
      {
        TheVer.Remove(k);
        ThePar.Remove(k);
        k--;
      }
    }
  }

  if (!BRep_Tool::Degenerated(Edge))
  {
    for (int k = 1; k < TheVer.Length(); k++)
    {
      if (TheVer.Value(k).IsSame(TheVer.Value(k + 1)))
      {
        TheVer.Remove(k + 1);
        ThePar.Remove(k + 1);
        if (DoubleOrNotInFace(TheEdgesControle, TopoDS::Vertex(TheVer.Value(k))))
        {
          TheVer.Remove(k);
          ThePar.Remove(k);
        }
        k--;
      }
    }
  }

  for (int k = 1; k < TheVer.Length(); k = k + 2)
  {
    TopoDS_Shape aLocalShape = Edge.EmptyCopied();
    TopoDS_Edge  NewEdge     = TopoDS::Edge(aLocalShape);

    if (NewEdge.Orientation() == TopAbs_REVERSED)
    {
      TheBuilder.Add(NewEdge, TheVer.Value(k).Oriented(TopAbs_REVERSED));
      TheBuilder.Add(NewEdge, TheVer.Value(k + 1).Oriented(TopAbs_FORWARD));
    }
    else
    {
      TheBuilder.Add(NewEdge, TheVer.Value(k).Oriented(TopAbs_FORWARD));
      TheBuilder.Add(NewEdge, TheVer.Value(k + 1).Oriented(TopAbs_REVERSED));
    }
    TheBuilder.Range(NewEdge, ThePar.Value(k), ThePar.Value(k + 1));

    BRepLib::UpdateTolerances(NewEdge, false);

    S.Append(NewEdge);
  }
}

void ComputeIntervals(const NCollection_Sequence<TopoDS_Shape>& VOnF,
                      const NCollection_Sequence<TopoDS_Shape>& VOnL,
                      const NCollection_Sequence<gp_Pnt>&       ParOnF,
                      const NCollection_Sequence<gp_Pnt>&       ParOnL,
                      const BRepFill_TrimSurfaceTool&           Trim,
                      const occ::handle<Geom2d_Curve>&          Bis,
                      const TopoDS_Vertex&                      VS,
                      const TopoDS_Vertex&                      VE,
                      NCollection_Sequence<double>&             FirstPar,
                      NCollection_Sequence<double>&             LastPar,
                      NCollection_Sequence<TopoDS_Shape>&       FirstV,
                      NCollection_Sequence<TopoDS_Shape>&       LastV)
{
  int          IOnF = 1, IOnL = 1;
  double       U1 = 0., U2;
  TopoDS_Shape V1, V2;

  if (!VS.IsNull())
  {
    U1 = Bis->FirstParameter();
    V1 = VS;
  }
  while (IOnF <= VOnF.Length() || IOnL <= VOnL.Length())
  {

    if (IOnL > VOnL.Length()
        || (IOnF <= VOnF.Length() && ParOnF.Value(IOnF).X() < ParOnL.Value(IOnL).X()))
    {

      U2 = ParOnF.Value(IOnF).X();
      V2 = VOnF.Value(IOnF);
      IOnF++;
    }
    else
    {
      U2 = ParOnL.Value(IOnL).X();
      V2 = VOnL.Value(IOnL);
      IOnL++;
    }

    if (!V1.IsNull() && !V2.IsSame(V1))
    {
      gp_Pnt2d P = Bis->Value((U2 + U1) * 0.5);
      if (Trim.IsOnFace(P))
      {
        FirstPar.Append(U1);
        LastPar.Append(U2);
        FirstV.Append(V1);
        LastV.Append(V2);
      }
    }
    U1 = U2;
    V1 = V2;
  }

  if (!VE.IsNull())
  {
    U2 = Bis->LastParameter();
    V2 = VE;
    if (!V2.IsSame(V1))
    {
      gp_Pnt2d P = Bis->Value((U2 + U1) * 0.5);
      if (Trim.IsOnFace(P))
      {
        FirstPar.Append(U1);
        LastPar.Append(U2);
        FirstV.Append(V1);
        LastV.Append(V2);
      }
    }
  }
}

static TopAbs_Orientation Relative(const TopoDS_Wire&   W1,
                                   const TopoDS_Wire&   W2,
                                   const TopoDS_Vertex& V,
                                   bool&                Commun)
{
  TopExp_Explorer Exp;
  TopoDS_Edge     E1, E2;
  TopoDS_Vertex   V1, V2;

  for (Exp.Init(W1, TopAbs_EDGE); Exp.More(); Exp.Next())
  {
    const TopoDS_Edge& E = TopoDS::Edge(Exp.Current());
    TopExp::Vertices(E, V1, V2);
    if (V1.IsSame(V) || V2.IsSame(V))
    {
      E1 = E;
      break;
    }
  }
  for (Exp.Init(W2, TopAbs_EDGE); Exp.More(); Exp.Next())
  {
    const TopoDS_Edge& E = TopoDS::Edge(Exp.Current());
    TopExp::Vertices(E, V1, V2);
    if (V1.IsSame(V) || V2.IsSame(V))
    {
      E2 = E;
      break;
    }
  }

  if (E1.IsNull() || E2.IsNull())
  {
    Commun = false;
    return TopAbs_FORWARD;
  }
  Commun = true;

  TopoDS_Wire WW1 = BRepLib_MakeWire(E1);
  TopoDS_Wire WW2 = BRepLib_MakeWire(E2);
  double      Tol = BRepFill_Confusion();
  if (Side(WW1, Tol) < 4 && Side(WW2, Tol) < 4)
    return TopAbs_FORWARD;
  if (Side(WW1, Tol) > 4 && Side(WW2, Tol) > 4)
    return TopAbs_FORWARD;

  return TopAbs_REVERSED;
}

int PosOnFace(double d1, double d2, double d3)
{
  if (std::abs(d1 - d2) <= BRepFill_Confusion())
    return 1;
  if (std::abs(d1 - d3) <= BRepFill_Confusion())
    return 3;

  if (d2 < d3)
  {
    if (d1 > (d2 + BRepFill_Confusion()) && d1 < (d3 - BRepFill_Confusion()))
      return 2;
  }
  else
  {
    if (d1 > (d3 + BRepFill_Confusion()) && d1 < (d2 - BRepFill_Confusion()))
      return 2;
  }
  return 0;
}

bool DoubleOrNotInFace(const NCollection_Sequence<TopoDS_Shape>& EC, const TopoDS_Vertex& V)
{
  bool Vu = false;

  for (int i = 1; i <= EC.Length(); i++)
  {
    TopoDS_Vertex V1, V2;
    TopExp::Vertices(TopoDS::Edge(EC.Value(i)), V1, V2);
    if (V1.IsSame(V))
    {
      if (Vu)
        return true;
      else
        Vu = true;
    }
    if (V2.IsSame(V))
    {
      if (Vu)
        return true;
      else
        Vu = true;
    }
  }
  return !Vu;
}

double DistanceToOZ(const TopoDS_Vertex& V)
{
  gp_Pnt PV3d = BRep_Tool::Pnt(V);
  return std::abs(PV3d.Y());
}

double Altitud(const TopoDS_Vertex& V)
{
  gp_Pnt PV3d = BRep_Tool::Pnt(V);
  return PV3d.Z();
}

void SimpleExpression(const Bisector_Bisec& B, occ::handle<Geom2d_Curve>& Bis)
{
  Bis = B.Value();

  occ::handle<Standard_Type> BT = Bis->DynamicType();
  if (BT == STANDARD_TYPE(Geom2d_TrimmedCurve))
  {
    occ::handle<Geom2d_TrimmedCurve> TrBis  = occ::down_cast<Geom2d_TrimmedCurve>(Bis);
    occ::handle<Geom2d_Curve>        BasBis = TrBis->BasisCurve();
    BT                                      = BasBis->DynamicType();
    if (BT == STANDARD_TYPE(Bisector_BisecAna))
    {
      Bis = occ::down_cast<Bisector_BisecAna>(BasBis)->Geom2dCurve();
      Bis = new Geom2d_TrimmedCurve(Bis, TrBis->FirstParameter(), TrBis->LastParameter());
    }
  }
}

void CutEdgeProf(
  const TopoDS_Edge&                                                        E,
  const occ::handle<Geom_Plane>&                                            Plane,
  const occ::handle<Geom2d_Line>&                                           Line,
  NCollection_List<TopoDS_Shape>&                                           Cuts,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& MapVerRefMoved)
{
  Cuts.Clear();

  double                         f, l;
  occ::handle<Geom_Curve>        C;
  occ::handle<Geom_TrimmedCurve> CT;
  occ::handle<Geom2d_Curve>      C2d;
  TopLoc_Location                L;

  C  = BRep_Tool::Curve(E, L, f, l);
  CT = new Geom_TrimmedCurve(C, f, l);
  CT->Transform(L.Transformation());

  gp_Dir Normal = Plane->Pln().Axis().Direction();
  C             = GeomProjLib::ProjectOnPlane(CT, Plane, Normal, false);
  C2d           = GeomProjLib::Curve2d(C, Plane);

  NCollection_Sequence<double> Seq;

  double U1 = -Precision::Infinite();
  double U2 = Precision::Infinite();
  f         = C2d->FirstParameter();
  l         = C2d->LastParameter();

  Bnd_Box2d           B;
  Geom2dAdaptor_Curve AC2d(C2d);
  BndLib_Add2dCurve::Add(AC2d, BRepFill_Confusion(), B);
  double xmin, xmax;
  B.Get(xmin, U1, xmax, U2);

  if (U1 != U2)
  {
    Geom2dAPI_ExtremaCurveCurve Extrema(Line, C2d, U1 - 1., U2 + 1., f, l);

    int i, Nb = Extrema.NbExtrema();
    for (i = 1; i <= Nb; i++)
    {
      Extrema.Parameters(i, U1, U2);
      Seq.Append(U2);
    }
  }

  Geom2dAdaptor_Curve ALine(Line);
  constexpr double    Tol  = Precision::Intersection();
  double              TolC = 0.;

  Geom2dInt_GInter Intersector(ALine, AC2d, TolC, Tol);
  int              i, Nb = Intersector.NbPoints();

  for (i = 1; i <= Nb; i++)
  {
    Seq.Append(Intersector.Point(i).ParamOnSecond());
  }

  BRep_Builder  Builder;
  TopoDS_Vertex VV, Vf, Vl, VRf, VRl;
  TopExp::Vertices(E, VRf, VRl);

  if (!MapVerRefMoved.IsBound(VRf))
  {
    Builder.MakeVertex(Vf, C->Value(f), BRep_Tool::Tolerance(VRf));
    MapVerRefMoved.Bind(VRf, Vf);
  }
  else
  {
    Vf = TopoDS::Vertex(MapVerRefMoved(VRf));
  }

  if (!MapVerRefMoved.IsBound(VRl))
  {
    Builder.MakeVertex(Vl, C->Value(l), BRep_Tool::Tolerance(VRl));
    MapVerRefMoved.Bind(VRl, Vl);
  }
  else
  {
    Vl = TopoDS::Vertex(MapVerRefMoved(VRl));
  }

  if (!Seq.IsEmpty())
  {

    Bubble(Seq);

    bool Empty = false;

    double CurParam = f;
    double Param;

    while (!Empty)
    {
      Param = Seq.First();
      Seq.Remove(1);
      Empty = Seq.IsEmpty();
      if (std::abs(Param - CurParam) > BRepFill_Confusion()
          && std::abs(Param - l) > BRepFill_Confusion())
      {

        VV = BRepLib_MakeVertex(C->Value(Param));

        TopoDS_Edge EE = BRepLib_MakeEdge(C, Vf, VV);
        EE.Orientation(E.Orientation());
        if (EE.Orientation() == TopAbs_FORWARD)
          Cuts.Append(EE);
        else
          Cuts.Prepend(EE);

        CurParam = Param;
        Vf       = VV;
      }
    }
  }

  TopoDS_Edge EE = BRepLib_MakeEdge(C, Vf, Vl);
  EE.Orientation(E.Orientation());
  if (EE.Orientation() == TopAbs_FORWARD)
    Cuts.Append(EE);
  else
    Cuts.Prepend(EE);
}

void CutEdge(const TopoDS_Edge& E, const TopoDS_Face& F, NCollection_List<TopoDS_Shape>& Cuts)
{
  Cuts.Clear();
  MAT2d_CutCurve                   Cuter;
  double                           f, l;
  occ::handle<Geom2d_Curve>        C2d;
  occ::handle<Geom2d_TrimmedCurve> CT2d;

  TopoDS_Vertex V1, V2, VF, VL;
  TopExp::Vertices(E, V1, V2);
  BRep_Builder B;

  C2d  = BRep_Tool::CurveOnSurface(E, F, f, l);
  CT2d = new Geom2d_TrimmedCurve(C2d, f, l);

  if (CT2d->BasisCurve()->IsKind(STANDARD_TYPE(Geom2d_Circle)) && BRep_Tool::IsClosed(E))
  {

    double   m1 = (2 * f + l) / 3.;
    double   m2 = (f + 2 * l) / 3.;
    gp_Pnt2d P1 = CT2d->Value(m1);
    gp_Pnt2d P2 = CT2d->Value(m2);

    TopoDS_Vertex VL1          = BRepLib_MakeVertex(gp_Pnt(P1.X(), P1.Y(), 0.));
    TopoDS_Vertex VL2          = BRepLib_MakeVertex(gp_Pnt(P2.X(), P2.Y(), 0.));
    TopoDS_Shape  aLocalShape1 = E.EmptyCopied();
    TopoDS_Shape  aLocalShape2 = E.EmptyCopied();
    TopoDS_Shape  aLocalShape3 = E.EmptyCopied();
    TopoDS_Edge   FE           = TopoDS::Edge(aLocalShape1);
    TopoDS_Edge   ME           = TopoDS::Edge(aLocalShape2);
    TopoDS_Edge   LE           = TopoDS::Edge(aLocalShape3);

    FE.Orientation(TopAbs_FORWARD);
    ME.Orientation(TopAbs_FORWARD);
    LE.Orientation(TopAbs_FORWARD);

    B.Add(FE, V1);
    B.Add(FE, VL1.Oriented(TopAbs_REVERSED));
    B.Range(FE, f, m1);

    B.Add(ME, VL1.Oriented(TopAbs_FORWARD));
    B.Add(ME, VL2.Oriented(TopAbs_REVERSED));
    B.Range(ME, m1, m2);

    B.Add(LE, VL2.Oriented(TopAbs_FORWARD));
    B.Add(LE, V2);
    B.Range(LE, m2, l);

    Cuts.Append(FE.Oriented(E.Orientation()));
    Cuts.Append(ME.Oriented(E.Orientation()));
    Cuts.Append(LE.Oriented(E.Orientation()));

    return;
  }

  Cuter.Perform(CT2d);

  if (Cuter.UnModified())
  {

    return;
  }
  else
  {

    VF = V1;

    for (int k = 1; k <= Cuter.NbCurves(); k++)
    {
      occ::handle<Geom2d_TrimmedCurve> CC = Cuter.Value(k);
      if (k == Cuter.NbCurves())
      {
        VL = V2;
      }
      else
      {
        gp_Pnt2d P = CC->Value(CC->LastParameter());
        VL         = BRepLib_MakeVertex(gp_Pnt(P.X(), P.Y(), 0.));
      }
      TopoDS_Shape aLocalShape = E.EmptyCopied();
      TopoDS_Edge  NE          = TopoDS::Edge(aLocalShape);

      NE.Orientation(TopAbs_FORWARD);
      B.Add(NE, VF.Oriented(TopAbs_FORWARD));
      B.Add(NE, VL.Oriented(TopAbs_REVERSED));
      B.Range(NE, CC->FirstParameter(), CC->LastParameter());
      Cuts.Append(NE.Oriented(E.Orientation()));
      VF = VL;
    }
  }
}

int VertexFromNode(
  const occ::handle<MAT_Node>& aNode,
  const TopoDS_Edge&           E,
  const TopoDS_Vertex&         VF,
  const TopoDS_Vertex&         VL,
  NCollection_DataMap<occ::handle<MAT_Node>,
                      NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>>&
                 MapNodeVertex,
  TopoDS_Vertex& VN)
{
  TopoDS_Shape                                                             ShapeOnNode;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> EmptyMap;
  int                                                                      Status = 0;
  BRep_Builder                                                             B;

  if (!aNode->Infinite())
  {
    Status = PosOnFace(aNode->Distance(), DistanceToOZ(VF), DistanceToOZ(VL));
  }
  if (Status == 2)
    ShapeOnNode = E;
  else if (Status == 1)
    ShapeOnNode = VF;
  else if (Status == 3)
    ShapeOnNode = VL;

  if (!ShapeOnNode.IsNull())
  {

    if (MapNodeVertex.IsBound(aNode) && MapNodeVertex(aNode).IsBound(ShapeOnNode))
    {
      VN = TopoDS::Vertex(MapNodeVertex(aNode)(ShapeOnNode));
    }
    else
    {
      B.MakeVertex(VN);
      if (!MapNodeVertex.IsBound(aNode))
      {
        MapNodeVertex.Bind(aNode, EmptyMap);
      }
      MapNodeVertex(aNode).Bind(ShapeOnNode, VN);
    }
  }
  return Status;
}
