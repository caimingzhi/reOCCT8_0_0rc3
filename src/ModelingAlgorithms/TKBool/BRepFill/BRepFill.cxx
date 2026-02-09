#include <BRepFill.hpp>

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepExtrema_DistShapeShape.hpp>
#include <BRepExtrema_ExtPC.hpp>
#include <BRepLib.hpp>
#include <BRepLib_FindSurface.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <BRepLib_MakeFace.hpp>
#include <BRepLib_MakeWire.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <GCPnts_AbscissaPoint.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomFill_Generator.hpp>
#include <gp_Ax3.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_NoSuchObject.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Sequence.hpp>

static void MakeWire(const NCollection_Array1<TopoDS_Shape>& Edges,
                     const int                               rangdeb,
                     const bool                              forward,
                     TopoDS_Wire&                            newwire)
{
  BRep_Builder BW;
  int          rang, nbEdges = Edges.Length();
  BW.MakeWire(newwire);
  if (forward)
  {
    for (rang = rangdeb; rang <= nbEdges; rang++)
    {
      BW.Add(newwire, TopoDS::Edge(Edges(rang)));
    }
    for (rang = 1; rang < rangdeb; rang++)
    {
      BW.Add(newwire, TopoDS::Edge(Edges(rang)));
    }
  }

  else
  {
    TopoDS_Edge E;
    for (rang = rangdeb; rang >= 1; rang--)
    {
      E = TopoDS::Edge(Edges(rang));
      BW.Add(newwire, E.Reversed());
    }
    for (rang = nbEdges; rang > rangdeb; rang--)
    {
      E = TopoDS::Edge(Edges(rang));
      BW.Add(newwire, E.Reversed());
    }
  }
  newwire.Orientation(TopAbs_FORWARD);
  newwire.Closed(true);
}

static void CutEdge(const TopoDS_Edge&   CurrentEdge,
                    const double&        Param,
                    TopoDS_Edge&         E1,
                    TopoDS_Edge&         E2,
                    const TopoDS_Vertex& VRef)
{
  BRep_Builder            B;
  double                  first, last;
  occ::handle<Geom_Curve> C = BRep_Tool::Curve(CurrentEdge, first, last);
  TopoDS_Vertex           Vf, Vl, Vi;
  B.MakeVertex(Vi, C->Value(Param), Precision::Confusion());
  TopExp::Vertices(CurrentEdge, Vf, Vl);
  if (VRef.IsSame(Vf))
  {
    E1 = BRepLib_MakeEdge(C, Vf, Vi, first, Param);
    E2 = BRepLib_MakeEdge(C, Vi, Vl, Param, last);
  }
  else
  {
    E2 = BRepLib_MakeEdge(C, Vf, Vi, first, Param);
    E1 = BRepLib_MakeEdge(C, Vi, Vl, Param, last);
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

      m1               = (CutValues.Value(j) - t0) * (last - first) / (t1 - t0) + first;
      TopoDS_Edge CutE = BRepLib_MakeEdge(C, V0, Vbid, m0, m1);
      CutE.Orientation(CurrentOrient);
      S.Append(CutE);
      m0 = m1;
      V0 = TopExp::LastVertex(CutE);
      if (j == ndec)
      {

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

      m0               = (CutValues.Value(j) - t0) * (last - first) / (t1 - t0) + first;
      TopoDS_Edge CutE = BRepLib_MakeEdge(C, Vbid, V1, m0, m1);
      CutE.Orientation(CurrentOrient);
      S.Append(CutE);
      m1 = m0;
      V1 = TopExp::FirstVertex(CutE);
      if (j == 1)
      {

        TopoDS_Edge LastE = BRepLib_MakeEdge(C, Vf, V1, first, m1);
        LastE.Orientation(CurrentOrient);
        S.Append(LastE);
      }
    }
  }
}

TopoDS_Face BRepFill::Face(const TopoDS_Edge& Edge1, const TopoDS_Edge& Edge2)
{
  TopoDS_Face Face;

  BRep_Builder B;

  TopLoc_Location L, L1, L2;
  double          f1, f2, l1, l2, Tol;

  occ::handle<Geom_Curve> C1 = BRep_Tool::Curve(Edge1, L1, f1, l1);

  occ::handle<Geom_Curve> C2 = BRep_Tool::Curve(Edge2, L2, f2, l2);

  bool SameLoc = false;
  if (L1 == L2)
  {
    L  = L1;
    L1 = L2 = TopLoc_Location();
    SameLoc = true;
  }

  TopoDS_Vertex V1f, V1l, V2f, V2l;

  if (std::abs(f1 - C1->FirstParameter()) > Precision::PConfusion()
      || std::abs(l1 - C1->LastParameter()) > Precision::PConfusion())
  {
    C1 = new Geom_TrimmedCurve(C1, f1, l1);
  }
  else
  {
    C1 = occ::down_cast<Geom_Curve>(C1->Copy());
  }

  if (!SameLoc)
  {
    C1->Transform(L1.Transformation());
  }

  if (Edge1.Orientation() == TopAbs_REVERSED)
  {
    TopExp::Vertices(Edge1, V1l, V1f);
    C1->Reverse();
  }
  else
  {
    TopExp::Vertices(Edge1, V1f, V1l);
  }

  if (std::abs(f2 - C2->FirstParameter()) > Precision::PConfusion()
      || std::abs(l2 - C2->LastParameter()) > Precision::PConfusion())
  {
    C2 = new Geom_TrimmedCurve(C2, f2, l2);
  }
  else
  {
    C2 = occ::down_cast<Geom_Curve>(C2->Copy());
  }

  if (!SameLoc)
  {
    C2->Transform(L2.Transformation());
  }

  if (Edge2.Orientation() == TopAbs_REVERSED)
  {
    TopExp::Vertices(Edge2, V2l, V2f);
    C2->Reverse();
  }
  else
  {
    TopExp::Vertices(Edge2, V2f, V2l);
  }

  bool Closed = V1f.IsSame(V1l) && V2f.IsSame(V2l);

  GeomFill_Generator Generator;
  Generator.AddCurve(C1);
  Generator.AddCurve(C2);
  Generator.Perform(Precision::PConfusion());

  occ::handle<Geom_Surface> Surf = Generator.Surface();
  occ::handle<Geom_Curve>   Iso;

  B.MakeFace(Face, Surf, Precision::Confusion());

  Surf->Bounds(f1, l1, f2, l2);

  TopoDS_Edge Edge3, Edge4;

  Iso = Surf->UIso(f1);
  Tol = std::max(BRep_Tool::Tolerance(V1f), BRep_Tool::Tolerance(V2f));
  if (Iso->Value(f2).Distance(Iso->Value(l2)) > Tol)
  {
    B.MakeEdge(Edge3, Iso, Precision::Confusion());
  }
  else
  {
    B.MakeEdge(Edge3);
    B.Degenerated(Edge3, true);
  }
  V1f.Orientation(TopAbs_FORWARD);
  B.Add(Edge3, V1f);
  V2f.Orientation(TopAbs_REVERSED);
  B.Add(Edge3, V2f);
  B.Range(Edge3, f2, l2);

  if (Closed)
  {
    Edge4 = Edge3;
  }
  else
  {
    Iso = Surf->UIso(l1);
    Tol = std::max(BRep_Tool::Tolerance(V1l), BRep_Tool::Tolerance(V2l));
    if (Iso->Value(l2).Distance(Iso->Value(f2)) > Tol)
    {
      B.MakeEdge(Edge4, Iso, Precision::Confusion());
    }
    else
    {
      B.MakeEdge(Edge4);
      B.Degenerated(Edge4, true);
    }
    V1l.Orientation(TopAbs_FORWARD);
    B.Add(Edge4, V1l);
    V2l.Orientation(TopAbs_REVERSED);
    B.Add(Edge4, V2l);
    B.Range(Edge4, f2, l2);
  }

  TopoDS_Wire W;
  B.MakeWire(W);

  Edge3.Reverse();
  B.Add(W, Edge1);
  B.Add(W, Edge4);
  B.Add(W, Edge2.Reversed());
  B.Add(W, Edge3);
  W.Closed(true);

  B.Add(Face, W);

  double T = Precision::Confusion();

  if (Edge1.Orientation() == TopAbs_REVERSED)
  {
    B.UpdateEdge(Edge1, new Geom2d_Line(gp_Pnt2d(0, f2), gp_Dir2d(gp_Dir2d::D::NX)), Face, T);
    B.Range(Edge1, Face, -l1, -f1);
  }
  else
  {
    B.UpdateEdge(Edge1, new Geom2d_Line(gp_Pnt2d(0, f2), gp_Dir2d(gp_Dir2d::D::X)), Face, T);
    B.Range(Edge1, Face, f1, l1);
  }

  if (Edge2.Orientation() == TopAbs_REVERSED)
  {
    B.UpdateEdge(Edge2, new Geom2d_Line(gp_Pnt2d(0, l2), gp_Dir2d(gp_Dir2d::D::NX)), Face, T);
    B.Range(Edge2, Face, -l1, -f1);
  }
  else
  {
    B.UpdateEdge(Edge2, new Geom2d_Line(gp_Pnt2d(0, l2), gp_Dir2d(gp_Dir2d::D::X)), Face, T);
    B.Range(Edge2, Face, f1, l1);
  }

  if (Closed)
  {
    B.UpdateEdge(Edge3,
                 new Geom2d_Line(gp_Pnt2d(l1, 0), gp_Dir2d(gp_Dir2d::D::Y)),
                 new Geom2d_Line(gp_Pnt2d(f1, 0), gp_Dir2d(gp_Dir2d::D::Y)),
                 Face,
                 T);
  }
  else
  {
    B.UpdateEdge(Edge3, new Geom2d_Line(gp_Pnt2d(f1, 0), gp_Dir2d(gp_Dir2d::D::Y)), Face, T);
    B.UpdateEdge(Edge4, new Geom2d_Line(gp_Pnt2d(l1, 0), gp_Dir2d(gp_Dir2d::D::Y)), Face, T);
  }

  B.SameParameter(Edge1, false);
  B.SameParameter(Edge2, false);
  B.SameParameter(Edge3, false);
  B.SameParameter(Edge4, false);
  B.SameRange(Edge1, false);
  B.SameRange(Edge2, false);
  B.SameRange(Edge3, false);
  B.SameRange(Edge4, false);

  BRepLib::SameParameter(Face);

  if (SameLoc)
    Face.Move(L);
  return Face;
}

TopoDS_Shell BRepFill::Shell(const TopoDS_Wire& Wire1, const TopoDS_Wire& Wire2)
{
  TopoDS_Shell Shell;
  TopoDS_Face  Face;
  TopoDS_Shape S1, S2;
  TopoDS_Edge  Edge1, Edge2, Edge3, Edge4, Couture;

  BRep_Builder B;

  B.MakeShell(Shell);

  TopExp_Explorer ex1;
  TopExp_Explorer ex2;

  bool Closed = Wire1.Closed() && Wire2.Closed();

  bool thefirst = true;

  ex1.Init(Wire1, TopAbs_EDGE);
  ex2.Init(Wire2, TopAbs_EDGE);

  while (ex1.More() && ex2.More())
  {

    Edge1 = TopoDS::Edge(ex1.Current());
    Edge2 = TopoDS::Edge(ex2.Current());

    bool Periodic = BRep_Tool::IsClosed(Edge1) && BRep_Tool::IsClosed(Edge2);

    ex1.Next();
    ex2.Next();

    TopLoc_Location L, L1, L2;
    double          f1, l1, f2, l2, Tol;

    occ::handle<Geom_Curve> C1 = BRep_Tool::Curve(Edge1, L1, f1, l1);
    occ::handle<Geom_Curve> C2 = BRep_Tool::Curve(Edge2, L2, f2, l2);

    bool SameLoc = false;
    if (L1 == L2)
    {
      L  = L1;
      L1 = L2 = TopLoc_Location();
      SameLoc = true;
    }

    TopoDS_Vertex V1f, V1l, V2f, V2l;

    if (std::abs(f1 - C1->FirstParameter()) > Precision::PConfusion()
        || std::abs(l1 - C1->LastParameter()) > Precision::PConfusion())
    {
      C1 = new Geom_TrimmedCurve(C1, f1, l1);
    }
    else
    {
      C1 = occ::down_cast<Geom_Curve>(C1->Copy());
    }
    if (!SameLoc)
    {
      C1->Transform(L1.Transformation());
    }
    if (Edge1.Orientation() == TopAbs_REVERSED)
    {
      TopExp::Vertices(Edge1, V1l, V1f);
      C1->Reverse();
    }
    else
      TopExp::Vertices(Edge1, V1f, V1l);

    if (std::abs(f2 - C2->FirstParameter()) > Precision::PConfusion()
        || std::abs(l2 - C2->LastParameter()) > Precision::PConfusion())
    {
      C2 = new Geom_TrimmedCurve(C2, f2, l2);
    }
    else
    {
      C2 = occ::down_cast<Geom_Curve>(C2->Copy());
    }
    if (!SameLoc)
    {
      C2->Transform(L2.Transformation());
    }
    if (Edge2.Orientation() == TopAbs_REVERSED)
    {
      TopExp::Vertices(Edge2, V2l, V2f);
      C2->Reverse();
    }
    else
      TopExp::Vertices(Edge2, V2f, V2l);

    GeomFill_Generator Generator;
    Generator.AddCurve(C1);
    Generator.AddCurve(C2);
    Generator.Perform(Precision::PConfusion());

    occ::handle<Geom_Surface> Surf = Generator.Surface();
    occ::handle<Geom_Curve>   Iso;

    B.MakeFace(Face, Surf, Precision::Confusion());

    Surf->Bounds(f1, l1, f2, l2);

    if (thefirst)
    {
      Iso = Surf->UIso(f1);

      Tol = std::max(BRep_Tool::Tolerance(V1f), BRep_Tool::Tolerance(V2f));
      if (Iso->Value(f2).Distance(Iso->Value(l2)) > Tol)
      {
        B.MakeEdge(Edge3, Iso, Precision::Confusion());
      }
      else
      {
        B.MakeEdge(Edge3);
        B.Degenerated(Edge3, true);
      }
      V1f.Orientation(TopAbs_FORWARD);
      B.Add(Edge3, V1f);
      V2f.Orientation(TopAbs_REVERSED);
      B.Add(Edge3, V2f);
      B.Range(Edge3, f2, l2);
      if (Closed)
      {
        Couture = Edge3;
      }
      Edge3.Reverse();
      thefirst = false;
    }
    else
    {
      Edge3 = Edge4;
      Edge3.Reverse();
    }

    if (Closed && !ex1.More() && !ex2.More())
    {
      Edge4 = Couture;
    }
    else
    {
      Iso = Surf->UIso(l1);

      Tol = std::max(BRep_Tool::Tolerance(V1l), BRep_Tool::Tolerance(V2l));
      if (Iso->Value(l2).Distance(Iso->Value(f2)) > Tol)
      {
        B.MakeEdge(Edge4, Iso, Precision::Confusion());
      }
      else
      {
        B.MakeEdge(Edge4);
        B.Degenerated(Edge4, true);
      }
      V1l.Orientation(TopAbs_FORWARD);
      B.Add(Edge4, V1l);
      V2l.Orientation(TopAbs_REVERSED);
      B.Add(Edge4, V2l);
      B.Range(Edge4, f2, l2);
    }

    TopoDS_Wire W;
    B.MakeWire(W);

    B.Add(W, Edge1);
    B.Add(W, Edge4);
    B.Add(W, Edge2.Reversed());
    B.Add(W, Edge3);
    W.Closed(true);

    B.Add(Face, W);

    if (SameLoc)
      Face.Move(L);

    B.Add(Shell, Face);

    double T = Precision::Confusion();

    if (Edge1.Orientation() == TopAbs_REVERSED)
    {
      B.UpdateEdge(Edge1, new Geom2d_Line(gp_Pnt2d(0, f2), gp_Dir2d(gp_Dir2d::D::NX)), Face, T);
      B.Range(Edge1, Face, -l1, -f1);
    }
    else
    {
      B.UpdateEdge(Edge1, new Geom2d_Line(gp_Pnt2d(0, f2), gp_Dir2d(gp_Dir2d::D::X)), Face, T);
      B.Range(Edge1, Face, f1, l1);
    }

    if (Edge2.Orientation() == TopAbs_REVERSED)
    {
      B.UpdateEdge(Edge2, new Geom2d_Line(gp_Pnt2d(0, l2), gp_Dir2d(gp_Dir2d::D::NX)), Face, T);
      B.Range(Edge2, Face, -l1, -f1);
    }
    else
    {
      B.UpdateEdge(Edge2, new Geom2d_Line(gp_Pnt2d(0, l2), gp_Dir2d(gp_Dir2d::D::X)), Face, T);
      B.Range(Edge2, Face, f1, l1);
    }

    if (Periodic)
    {
      B.UpdateEdge(Edge3,
                   new Geom2d_Line(gp_Pnt2d(l1, 0), gp_Dir2d(gp_Dir2d::D::Y)),
                   new Geom2d_Line(gp_Pnt2d(f1, 0), gp_Dir2d(gp_Dir2d::D::Y)),
                   Face,
                   T);
    }
    else
    {
      B.UpdateEdge(Edge3, new Geom2d_Line(gp_Pnt2d(f1, 0), gp_Dir2d(gp_Dir2d::D::Y)), Face, T);
      B.UpdateEdge(Edge4, new Geom2d_Line(gp_Pnt2d(l1, 0), gp_Dir2d(gp_Dir2d::D::Y)), Face, T);
    }

    B.SameParameter(Edge1, false);
    B.SameParameter(Edge2, false);
    B.SameParameter(Edge3, false);
    B.SameParameter(Edge4, false);
    B.SameRange(Edge1, false);
    B.SameRange(Edge2, false);
    B.SameRange(Edge3, false);
    B.SameRange(Edge4, false);
  }

  Shell.Closed(BRep_Tool::IsClosed(Shell));
  BRepLib::SameParameter(Shell);
  return Shell;
}

void BRepFill::Axe(const TopoDS_Shape& Spine,
                   const TopoDS_Wire&  Profile,
                   gp_Ax3&             AxeProf,
                   bool&               ProfOnSpine,
                   const double        Tol)
{
  gp_Pnt Loc, Loc1, Loc2;
  gp_Vec Tang, Tang1, Tang2, Normal;

  occ::handle<Geom_Surface> S;
  TopLoc_Location           L;

  TopoDS_Face aFace;

  if (Spine.ShapeType() == TopAbs_FACE)
  {
    aFace = TopoDS::Face(Spine);
    S     = BRep_Tool::Surface(TopoDS::Face(Spine), L);
    if (!S->IsKind(STANDARD_TYPE(Geom_Plane)))
    {
      BRepLib_FindSurface FS(TopoDS::Face(Spine), -1, true);
      if (FS.Found())
      {
        S = FS.Surface();
        L = FS.Location();
      }
      else
      {
        throw Standard_NoSuchObject("BRepFill_Evolved : The Face is not planar");
      }
    }
  }
  else if (Spine.ShapeType() == TopAbs_WIRE)
  {
    aFace = BRepLib_MakeFace(TopoDS::Wire(Spine), true);
    S     = BRep_Tool::Surface(aFace, L);
  }

  if (S.IsNull())
    throw Standard_DomainError("BRepFill_Evolved::Axe");

  if (!L.IsIdentity())
    S = occ::down_cast<Geom_Surface>(S->Transformed(L.Transformation()));

  Normal = occ::down_cast<Geom_Plane>(S)->Pln().Axis().Direction();

  double DistMin = Precision::Infinite();
  double Dist;

  double            Tol2 = 1.e-10;
  TopExp_Explorer   PE, SE;
  BRepExtrema_ExtPC BE;
  double            Par = 0., f, l;

  gp_Pnt P1, P2;

  bool IsOnVertex = false;
  SE.Init(aFace.Oriented(TopAbs_FORWARD), TopAbs_VERTEX);

  for (; SE.More(); SE.Next())
  {
    P1 = BRep_Tool::Pnt(TopoDS::Vertex(SE.Current()));

    PE.Init(Profile, TopAbs_VERTEX);
    for (; PE.More(); PE.Next())
    {
      P2              = BRep_Tool::Pnt(TopoDS::Vertex(PE.Current()));
      double DistP1P2 = P1.SquareDistance(P2);
      IsOnVertex      = (DistP1P2 <= Tol2);
      if (IsOnVertex)
        break;
    }

    if (IsOnVertex)
      break;
  }

  if (IsOnVertex)
  {

    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>
      Map;
    TopExp::MapShapesAndAncestors(aFace.Oriented(TopAbs_FORWARD), TopAbs_VERTEX, TopAbs_EDGE, Map);

    const TopoDS_Vertex&                  VonF = TopoDS::Vertex(SE.Current());
    const NCollection_List<TopoDS_Shape>& List = Map.FindFromKey(VonF);
    const TopoDS_Edge&                    E1   = TopoDS::Edge(List.First());
    const TopoDS_Edge&                    E2   = TopoDS::Edge(List.Last());

    occ::handle<Geom_Curve> CE1  = BRep_Tool::Curve(E1, L, f, l);
    double                  Par1 = BRep_Tool::Parameter(VonF, E1, aFace);
    CE1->D1(Par1, Loc1, Tang1);
    if (!L.IsIdentity())
    {
      Tang1.Transform(L.Transformation());
      Loc1.Transform(L.Transformation());
    }
    if (E1.Orientation() == TopAbs_REVERSED)
      Tang1.Reverse();

    occ::handle<Geom_Curve> CE2  = BRep_Tool::Curve(E2, L, f, l);
    double                  Par2 = BRep_Tool::Parameter(VonF, E2, aFace);
    CE2->D1(Par2, Loc2, Tang2);
    if (!L.IsIdentity())
    {
      Tang2.Transform(L.Transformation());
      Loc2.Transform(L.Transformation());
    }
    if (E2.Orientation() == TopAbs_REVERSED)
      Tang2.Reverse();

    Tang1.Normalize();
    Tang2.Normalize();
    double        sca1 = 0., sca2 = 0.;
    TopoDS_Vertex V1, V2;
    TopoDS_Edge   E;
    for (PE.Init(Profile, TopAbs_EDGE); PE.More(); PE.Next())
    {
      E = TopoDS::Edge(PE.Current());
      TopExp::Vertices(E, V1, V2);
      P1 = BRep_Tool::Pnt(V1);
      P2 = BRep_Tool::Pnt(V2);
      gp_Vec vec(P1, P2);
      sca1 += std::abs(Tang1.Dot(vec));
      sca2 += std::abs(Tang2.Dot(vec));
    }

    if (std::abs(sca1) < std::abs(sca2))
    {
      Loc  = Loc1;
      Tang = Tang1;
    }
    else
    {
      Loc  = Loc2;
      Tang = Tang2;
    }
    DistMin = 0.;
  }
  else
  {
    SE.Init(aFace.Oriented(TopAbs_FORWARD), TopAbs_EDGE);
    for (; SE.More(); SE.Next())
    {
      const TopoDS_Edge& E = TopoDS::Edge(SE.Current());
      BE.Initialize(E);
      for (PE.Init(Profile, TopAbs_VERTEX); PE.More(); PE.Next())
      {
        Dist                   = Precision::Infinite();
        const TopoDS_Vertex& V = TopoDS::Vertex(PE.Current());
        BE.Perform(V);
        if (BE.IsDone())
        {

          for (int i = 1; i <= BE.NbExt(); i++)
          {
            if (BE.IsMin(i))
            {
              Dist = sqrt(BE.SquareDistance(i));
              Par  = BE.Parameter(i);
              break;
            }
          }
        }

        if (Dist < DistMin)
        {
          DistMin = Dist;
          BRepAdaptor_Curve BAC(E);
          BAC.D1(Par, Loc, Tang);
          if (E.Orientation() == TopAbs_REVERSED)
            Tang.Reverse();
        }
      }
    }
  }

  ProfOnSpine = (DistMin < Tol);

  gp_Ax3 A3(Loc, Normal, Tang);
  AxeProf = A3;
}

void BRepFill::SearchOrigin(TopoDS_Wire& W, const gp_Pnt& P, const gp_Vec& Dir, const double Tol)
{
  if (!W.Closed())
    throw Standard_NoSuchObject("BRepFill::SearchOrigin : the wire must be closed");

  bool          NewVertex = false;
  double        theparam  = 1.e101, angle;
  TopoDS_Vertex V;
  TopoDS_Edge   E, Eref;
  BRep_Builder  B;

  W.Orientation(TopAbs_FORWARD);

  B.MakeVertex(V, P, Tol);
  BRepExtrema_DistShapeShape DSS(V, W);
  if (DSS.IsDone())
  {
    int    isol = 1;
    double dss  = P.Distance(DSS.PointOnShape2(isol));
    for (int iss = 2; iss <= DSS.NbSolution(); iss++)
      if (dss > P.Distance(DSS.PointOnShape2(iss)))
      {
        dss  = P.Distance(DSS.PointOnShape2(iss));
        isol = iss;
      }
    TopoDS_Shape supp = DSS.SupportOnShape2(isol);
    if (DSS.SupportTypeShape2(isol) == BRepExtrema_IsVertex)
    {
      V = TopoDS::Vertex(supp);
    }
    else
    {
      TopoDS_Vertex Vf, Vl;
      double        d, dist;
      E = TopoDS::Edge(supp);
      TopExp::Vertices(E, Vf, Vl);

      dist = P.Distance(BRep_Tool::Pnt(Vf));
      if (dist < Tol)
      {
        V = Vl;
      }

      d = P.Distance(BRep_Tool::Pnt(Vl));
      if ((d < Tol) && (d < dist))
      {
        V    = Vf;
        dist = d;
      }
      NewVertex = (dist > Tol);
      if (NewVertex)
      {
        DSS.ParOnEdgeS2(isol, theparam);
      }
    }
  }
#ifdef OCCT_DEBUG
  else
  {
    std::cout << "BRepFill::SearchOrigine : Echec Distance" << std::endl;
  }
#endif

  int                    ii, rangdeb = 0, NbEdges = 0;
  bool                   forward;
  BRepTools_WireExplorer exp;

  for (exp.Init(W); exp.More(); exp.Next())
    NbEdges++;
  if (NewVertex)
  {
    NbEdges++;
    Eref = E;
  }

  NCollection_Array1<TopoDS_Shape> Edges(1, NbEdges);
  for (exp.Init(W), ii = 1; exp.More(); exp.Next(), ii++)
  {
    E = exp.Current();
    if (NewVertex && E.IsSame(Eref))
    {
      TopoDS_Edge E1, E2;
      CutEdge(E, theparam, E1, E2, exp.CurrentVertex());
      Edges(ii) = E1;
      ii++;
      Edges(ii) = E2;
      rangdeb   = ii;
    }
    else
    {
      Edges(ii) = E;
    }
    if (!NewVertex && V.IsSame(exp.CurrentVertex()))
    {
      rangdeb = ii;
    }
  }
  if (rangdeb == 0)
    rangdeb = NbEdges;

  E = TopoDS::Edge(Edges(rangdeb));
  if (!NewVertex)
  {

    theparam = BRep_Tool::Parameter(V, E);
  }
  BRepAdaptor_Curve AC(E);
  gp_Pnt            Pe;
  gp_Vec            Ve;
  AC.D1(theparam, Pe, Ve);
  if (E.Orientation() == TopAbs_REVERSED)
  {
    Ve *= -1;
  }
  angle = Ve.Angle(Dir);
  if (angle > M_PI)
    angle = 2 * M_PI - angle;
  forward = (angle <= M_PI / 2);

  MakeWire(Edges, rangdeb, forward, W);
  W.Closed(true);
}

void BRepFill::ComputeACR(const TopoDS_Wire& wire, NCollection_Array1<double>& ACR)
{

  BRepTools_WireExplorer anExp;
  int                    nbEdges = 0, i;

  ACR.Init(0);
  for (anExp.Init(wire); anExp.More(); anExp.Next())
  {
    nbEdges++;
    TopoDS_Edge Ecur = TopoDS::Edge(anExp.Current());
    ACR(nbEdges)     = ACR(nbEdges - 1);
    if (!BRep_Tool::Degenerated(Ecur))
    {
      BRepAdaptor_Curve anEcur(Ecur);
      ACR(nbEdges) += GCPnts_AbscissaPoint::Length(anEcur);
    }
  }

  ACR(0) = ACR(nbEdges);

  if (ACR(0) > Precision::Confusion())
  {
    for (i = 1; i <= nbEdges; i++)
    {
      ACR(i) /= ACR(0);
    }
  }
  else
  {

    ACR(nbEdges) = 1;
  }
}

TopoDS_Wire BRepFill::InsertACR(const TopoDS_Wire&                wire,
                                const NCollection_Array1<double>& ACRcuts,
                                const double                      prec)
{

  BRepTools_WireExplorer anExp;
  int                    nbEdges = 0;
  for (anExp.Init(wire); anExp.More(); anExp.Next())
  {
    nbEdges++;
  }
  NCollection_Array1<double> ACRwire(0, nbEdges);
  ComputeACR(wire, ACRwire);

  int                        i, j, nmax = ACRcuts.Length();
  NCollection_Array1<double> paradec(1, nmax);
  BRepLib_MakeWire           MW;

  double t0, t1 = 0;
  nbEdges = 0;

  for (anExp.Init(wire); anExp.More(); anExp.Next())
  {
    nbEdges++;
    t0 = t1;
    t1 = ACRwire(nbEdges);

    int ndec = 0;
    for (i = 1; i <= ACRcuts.Length(); i++)
    {
      if (t0 + prec < ACRcuts(i) && ACRcuts(i) < t1 - prec)
      {
        ndec++;
        paradec(ndec) = ACRcuts(i);
      }
    }

    const TopoDS_Edge&   E = anExp.Current();
    const TopoDS_Vertex& V = anExp.CurrentVertex();

    if (ndec == 0 || BRep_Tool::Degenerated(E))
    {

      MW.Add(E);
    }
    else
    {

      bool                               SO = (V.IsSame(TopExp::FirstVertex(E)));
      NCollection_Sequence<TopoDS_Shape> SE;
      SE.Clear();
      NCollection_Sequence<double> SR;
      SR.Clear();

      if (E.Orientation() == TopAbs_FORWARD)
      {
        for (j = 1; j <= ndec; j++)
          SR.Append(paradec(j));
      }
      else
      {
        for (j = 1; j <= ndec; j++)
          SR.Append(t0 + t1 - paradec(ndec + 1 - j));
      }
      TrimEdge(E, SR, t0, t1, SO, SE);
      for (j = 1; j <= SE.Length(); j++)
      {
        MW.Add(TopoDS::Edge(SE.Value(j)));
      }
    }
  }

  TopAbs_Orientation Orien       = wire.Orientation();
  TopoDS_Shape       aLocalShape = MW.Wire();
  aLocalShape.Orientation(Orien);
  TopoDS_Wire wres = TopoDS::Wire(aLocalShape);

  return wres;
}
