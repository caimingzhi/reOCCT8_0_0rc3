#include <GeomAdaptor_SurfaceOfRevolution.hpp>
#include <BRep_Tool.hpp>
#include <BRepFill_ApproxSeewing.hpp>
#include <BRepFill_ComputeCLine.hpp>
#include <BRepFill_MultiLine.hpp>
#include <BRepFill_TrimSurfaceTool.hpp>
#include <BRepIntCurveSurface_Inter.hpp>
#include <ElCLib.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dAPI_ProjectPointOnCurve.hpp>
#include <Geom2dInt_GInter.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Plane.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomProjLib.hpp>
#include <gp.hpp>
#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <IntRes2d_IntersectionSegment.hpp>
#include <Precision.hpp>
#include <Standard_NotImplemented.hpp>
#include <StdFail_NotDone.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>

#include <cstdio>
#ifdef OCCT_DEBUG
static bool Affich = false;
static int  NBCALL = 0;
#endif

BRepFill_TrimSurfaceTool::BRepFill_TrimSurfaceTool(const occ::handle<Geom2d_Curve>& Bis,
                                                   const TopoDS_Face&               Face1,
                                                   const TopoDS_Face&               Face2,
                                                   const TopoDS_Edge&               Edge1,
                                                   const TopoDS_Edge&               Edge2,
                                                   const bool                       Inv1,
                                                   const bool                       Inv2)
    : myFace1(Face1),
      myFace2(Face2),
      myEdge1(Edge1),
      myEdge2(Edge2),
      myInv1(Inv1),
      myInv2(Inv2),
      myBis(Bis)
{
#ifdef OCCT_DEBUG
  if (Affich)
  {
    NBCALL++;
    std::cout << " ---------->TrimSurfaceTool : NBCALL = " << NBCALL << std::endl;
  }
#endif
}

static void Bubble(NCollection_Sequence<gp_Pnt>& Seq)
{
  bool Invert   = true;
  int  NbPoints = Seq.Length();
  while (Invert)
  {
    Invert = false;
    for (int i = 1; i < NbPoints; i++)
    {
      gp_Pnt P1 = Seq.Value(i);
      gp_Pnt P2 = Seq.Value(i + 1);
      if (P2.X() < P1.X())
      {
        Seq.Exchange(i, i + 1);
        Invert = true;
      }
    }
  }
}

static double EvalPhase(const TopoDS_Edge&         Edge,
                        const TopoDS_Face&         Face,
                        const GeomAdaptor_Surface& GAS,
                        const gp_Ax3&              Axis)
{
  gp_Pnt2d PE1, PE2, PF1, PF2;
  double   VDeg;
  double   V = 0.;
  BRep_Tool::UVPoints(Edge, Face, PE1, PE2);
  VDeg = PE1.Y();
  TopExp_Explorer Exp(Face, TopAbs_EDGE);
  for (; Exp.More(); Exp.Next())
  {
    if (!TopoDS::Edge(Exp.Current()).IsSame(Edge))
    {
      BRep_Tool::UVPoints(TopoDS::Edge(Exp.Current()), Face, PF1, PF2);
      V = (std::abs(PF1.Y() - VDeg) > std::abs(PF2.Y() - VDeg)) ? PF1.Y() : PF2.Y();
      break;
    }
  }
  gp_Pnt P = GAS.Value(0., V);

  if (gp_Vec(Axis.Location(), P).Dot(Axis.XDirection()) < 0.)
    return M_PI;
  else
    return 0.;
}

static void EvalParameters(const TopoDS_Edge&               Edge,
                           const TopoDS_Face&               Face,
                           const occ::handle<Geom2d_Curve>& Bis,
                           NCollection_Sequence<gp_Pnt>&    Seq)
{
  bool Degener = BRep_Tool::Degenerated(Edge);

  TopLoc_Location L;
  double          f, l;

  occ::handle<Geom_TrimmedCurve> CT;
  occ::handle<Geom_Plane>        Plane = new Geom_Plane(0, 0, 1, 0);

  Geom2dInt_GInter Intersector;

  int    NbPoints, NbSegments;
  double U1, U2;
  gp_Pnt P;

  double Tol  = 1.e-6;
  double TolC = 0.;

  if (!Degener)
  {
    occ::handle<Geom_Curve> C = BRep_Tool::Curve(Edge, L, f, l);
    CT                        = new Geom_TrimmedCurve(C, f, l);
    CT->Transform(L.Transformation());

    occ::handle<Geom2d_Curve> C2d = GeomProjLib::Curve2d(CT, Plane);

    Geom2dAdaptor_Curve AC(C2d);
    Geom2dAdaptor_Curve ABis(Bis);

    Intersector = Geom2dInt_GInter(ABis, AC, TolC, Tol);

    if (!Intersector.IsDone())
    {
      throw StdFail_NotDone("BRepFill_TrimSurfaceTool::IntersectWith");
    }

    NbPoints = Intersector.NbPoints();

    if (NbPoints < 1)
    {

      GeomAbs_CurveType CType = AC.GetType(), BisType = ABis.GetType();
      bool              canElongateC = CType != GeomAbs_BezierCurve && CType != GeomAbs_BSplineCurve
                          && CType != GeomAbs_OffsetCurve && CType != GeomAbs_OtherCurve;
      bool canElongateBis = BisType != GeomAbs_BezierCurve && BisType != GeomAbs_BSplineCurve
                            && BisType != GeomAbs_OffsetCurve && BisType != GeomAbs_OtherCurve;

      occ::handle<Geom2d_TrimmedCurve> TBis = occ::down_cast<Geom2d_TrimmedCurve>(Bis);
      occ::handle<Geom2d_TrimmedCurve> TC2d = occ::down_cast<Geom2d_TrimmedCurve>(C2d);

      if (canElongateC)
      {
        TC2d->SetTrim(TC2d->FirstParameter() - Tol, TC2d->LastParameter() + Tol);
        AC.Load(TC2d);
      }
      if (canElongateBis)
      {
        TBis->SetTrim(TBis->FirstParameter() - Tol, TBis->LastParameter() + Tol);
        ABis.Load(TBis);
      }
      Intersector = Geom2dInt_GInter(ABis, AC, TolC, Tol * 10);

      if (!Intersector.IsDone())
      {
        throw StdFail_NotDone("BRepFill_TrimSurfaceTool::IntersectWith");
      }

      NbPoints = Intersector.NbPoints();
    }

    if (NbPoints > 0)
    {

      for (int i = 1; i <= NbPoints; i++)
      {
        U1 = Intersector.Point(i).ParamOnFirst();
        U2 = Intersector.Point(i).ParamOnSecond();
        P  = gp_Pnt(U1, U2, 0.);
        Seq.Append(P);
      }
    }

    NbSegments = Intersector.NbSegments();

    if (NbSegments > 0)
    {
#ifdef OCCT_DEBUG
      std::cout << " IntersectWith : " << NbSegments << " Segments of intersection" << std::endl;
#endif
      IntRes2d_IntersectionSegment Seg;
      for (int i = 1; i <= NbSegments; i++)
      {
        Seg = Intersector.Segment(i);
        U1  = Seg.FirstPoint().ParamOnFirst();
        U1 += Seg.LastPoint().ParamOnFirst();
        U1 /= 2.;
        U2 = Seg.FirstPoint().ParamOnSecond();
        U2 += Seg.LastPoint().ParamOnSecond();
        U2 /= 2.;
        P = gp_Pnt(U1, U2, 0.);
        Seq.Append(P);
      }
    }

    Bubble(Seq);

    gp_Pnt P1, P2;
    for (int i = 1; i < NbPoints; i++)
    {
      P1 = Seq.Value(i);
      P2 = Seq.Value(i + 1);
      if (P2.X() - P1.X() < Tol)
      {

        Seq.Remove(i--);
        NbPoints--;
      }
    }
  }
  else
  {

    gp_Pnt   P3d = BRep_Tool::Pnt(TopExp::FirstVertex(Edge));
    gp_Pnt2d P2d(P3d.X(), P3d.Y());

    double   UBis = Bis->FirstParameter();
    gp_Pnt2d PBis = Bis->Value(UBis);

    if (Precision::IsPositiveInfinite(std::abs(PBis.X()))
        || Precision::IsPositiveInfinite(std::abs(PBis.Y())) || PBis.Distance(P2d) > Tol)
    {

      UBis = Bis->LastParameter();
      if (UBis >= Precision::Infinite())
        return;
      PBis = Bis->Value(UBis);
      if (PBis.Distance(P2d) > Tol)
        return;
    }

    occ::handle<Geom_Surface> GS = BRep_Tool::Surface(Face);
    GeomAdaptor_Surface       GAS(GS);

    gp_Ax3 Axis;
    double Phase = 0.;

    switch (GAS.GetType())
    {

      case GeomAbs_Sphere:
        Axis = GAS.Sphere().Position();
        break;
      case GeomAbs_Cone:
      {

        Axis  = GAS.Cone().Position();
        Phase = EvalPhase(Edge, Face, GAS, Axis);
        break;
      }
      case GeomAbs_Torus:
        Axis = GAS.Torus().Position();
        break;
      case GeomAbs_Cylinder:
        Axis = GAS.Cylinder().Position();
        break;
      case GeomAbs_SurfaceOfRevolution:
      {

        occ::handle<Geom_SurfaceOfRevolution> GSRev = occ::down_cast<Geom_SurfaceOfRevolution>(GS);
        occ::handle<GeomAdaptor_Curve>        HC    = new GeomAdaptor_Curve(GSRev->BasisCurve());
        GeomAdaptor_SurfaceOfRevolution       ASRev(HC, GAS.AxeOfRevolution());
        Axis  = ASRev.Axis();
        Phase = EvalPhase(Edge, Face, GAS, Axis);
        break;
      }
      default:
        throw Standard_NotImplemented(" BRepFill_TrimSurfaceTool");
    }

    gp_Vec2d D12d = Bis->DN(UBis, 1);
    gp_Vec   D1(D12d.X(), D12d.Y(), 0.);

    double U = Axis.XDirection().AngleWithRef(D1, Axis.XDirection() ^ Axis.YDirection());
    U += Phase;
    if (U < 0.)
      U += 2 * M_PI;

    P = gp_Pnt(Bis->FirstParameter(), U, 0.);
    Seq.Append(P);
  }
}

void BRepFill_TrimSurfaceTool::IntersectWith(const TopoDS_Edge&            EdgeOnF1,
                                             const TopoDS_Edge&            EdgeOnF2,
                                             NCollection_Sequence<gp_Pnt>& Points) const
{
  Points.Clear();
  NCollection_Sequence<gp_Pnt> Points2;

  EvalParameters(EdgeOnF1, myFace1, myBis, Points);
  EvalParameters(EdgeOnF2, myFace2, myBis, Points2);

  StdFail_NotDone_Raise_if(Points.Length() != Points2.Length(),
                           "BRepFill_TrimSurfaceTool::IntersectWith: incoherent intersection");

  gp_Pnt PSeq;
  int    NbPoints = Points.Length();
  for (int i = 1; i <= NbPoints; i++)
  {
    PSeq = Points(i);
    PSeq.SetZ((Points2.Value(i)).Y());
    Points.SetValue(i, PSeq);
  }
}

bool BRepFill_TrimSurfaceTool::IsOnFace(const gp_Pnt2d& Point) const
{
  gp_Pnt P(Point.X(), Point.Y(), 0.);
  gp_Lin Line(P, gp::DZ());

  BRepIntCurveSurface_Inter Inter;

  Inter.Init(myFace1, Line, 1e-6);
  if (Inter.More())
    return true;

  Inter.Init(myFace2, Line, 1e-6);
  return Inter.More();
}

double BRepFill_TrimSurfaceTool::ProjOn(const gp_Pnt2d& Point, const TopoDS_Edge& Edge) const
{
  TopLoc_Location L;
  double          f, l;

  occ::handle<Geom_Curve>        C1 = BRep_Tool::Curve(Edge, L, f, l);
  occ::handle<Geom_TrimmedCurve> CT = new Geom_TrimmedCurve(C1, f, l);
  CT->Transform(L.Transformation());

  occ::handle<Geom_Plane>   Plane = new Geom_Plane(0, 0, 1, 0);
  occ::handle<Geom2d_Curve> C2d   = GeomProjLib::Curve2d(CT, Plane);

  Geom2dAPI_ProjectPointOnCurve Projector(Point, C2d);
#ifdef OCCT_DEBUG
  double Dist = Projector.LowerDistance();
  if (Dist > Precision::Confusion())
  {
    std::cout << " *** WARNING  TrimSurfaceTool:  *** " << std::endl;
    std::cout << "      --> the point is not on the edge" << std::endl;
    std::cout << "          distance  = " << Dist << std::endl;
  }
#endif

  double U = Projector.LowerDistanceParameter();
  return U;
}

void BRepFill_TrimSurfaceTool::Project(const double               U1,
                                       const double               U2,
                                       occ::handle<Geom_Curve>&   Curve,
                                       occ::handle<Geom2d_Curve>& PCurve1,
                                       occ::handle<Geom2d_Curve>& PCurve2,
                                       GeomAbs_Shape&             Cont) const
{
  occ::handle<Geom2d_TrimmedCurve> CT = new Geom2d_TrimmedCurve(myBis, U1, U2);
  BRepFill_MultiLine               ML(myFace1, myFace2, myEdge1, myEdge2, myInv1, myInv2, CT);

  Cont = ML.Continuity();

  if (ML.IsParticularCase())
  {
    ML.Curves(Curve, PCurve1, PCurve2);
  }
  else
  {
    BRepFill_ApproxSeewing AppSeew(ML);

    Curve   = AppSeew.Curve();
    PCurve1 = AppSeew.CurveOnF1();
    PCurve2 = AppSeew.CurveOnF2();
  }
}
