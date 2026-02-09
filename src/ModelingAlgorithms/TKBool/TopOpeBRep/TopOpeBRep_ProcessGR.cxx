#include <TopOpeBRep_FacesFiller.hpp>
#include <TopOpeBRep_FFDumper.hpp>
#include <TopOpeBRep_LineInter.hpp>
#include <TopOpeBRep_VPointInter.hpp>
#include <TopOpeBRepDS_Transition.hpp>

#include <Geom_Curve.hpp>
#include <GeomAPI_ProjectPointOnSurf.hpp>

#include <TopoDS.hpp>
#include <TopOpeBRep_FFTransitionTool.hpp>
#include <TopOpeBRep_VPointInterIterator.hpp>
#include <TopOpeBRep_GeomTool.hpp>
#include <Precision.hpp>
#include <Standard_CString.hpp>
#include <Standard_ProgramError.hpp>
#include <TopOpeBRep.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_SC.hpp>

#ifdef OCCT_DEBUG
  #include <Geom_TrimmedCurve.hpp>
  #include <Geom_Line.hpp>
extern bool TopOpeBRep_GettraceBIPS();
extern bool TopOpeBRep_GettraceDEGEN();

extern bool FUN_debnull(const TopoDS_Shape& s)
{
  bool isnull = s.IsNull();
  if (isnull)
    std::cout << "***";
  return isnull;
}
#endif

Standard_EXPORTEXTERN double GLOBAL_tolFF;

TopAbs_State TopOpeBRep_FacesFiller::StBipVPonF(const TopOpeBRep_VPointInter& vpf,
                                                const TopOpeBRep_VPointInter& vpl,
                                                const TopOpeBRep_LineInter&   Lrest,
                                                const bool                    isonedge1) const
{

#define M_OUT(st) (st == TopAbs_OUT);
#define M_IN(st) (st == TopAbs_IN);

  int          sind  = isonedge1 ? 2 : 1;
  TopAbs_State stf   = vpf.State(sind);
  TopAbs_State stl   = vpl.State(sind);
  bool         isout = M_OUT(stf);
  isout              = isout || M_OUT(stl);
  bool isin          = M_IN(stf);
  isin               = isin || M_IN(stl);
  if (isout)
    return TopAbs_OUT;
  if (isin)
    return TopAbs_IN;

  bool               isperiodic;
  const TopoDS_Edge& EArc = TopoDS::Edge(Lrest.Arc());
  BRepAdaptor_Curve  BAC(EArc);
  GeomAbs_CurveType  CT = BAC.GetType();
  isperiodic            = (CT == GeomAbs_Circle);
  isperiodic            = isperiodic || (CT == GeomAbs_Ellipse);

  TopOpeBRep_VPointInter vpff = vpf;
  TopOpeBRep_VPointInter vpll = vpl;

  if (isperiodic)
  {
#ifdef OCCT_DEBUG

#endif

    int IArc = 0;
    if (Lrest.ArcIsEdge(1))
      IArc = 1;
    if (Lrest.ArcIsEdge(2))
      IArc = 2;
    if (IArc == 0)
    {
#ifdef OCCT_DEBUG
      throw Standard_Failure("StBipVPonF");
#else
      return TopAbs_UNKNOWN;
#endif
    }
    int  ISI = (IArc == 1) ? 2 : 1;
    int  sif = vpf.ShapeIndex();
    int  sil = vpl.ShapeIndex();
    bool act = ((sif == 3) || (sif == ISI)) && ((sil == 3) || (sil == ISI));
    if (act)
    {
      TopOpeBRepDS_Transition Tf =
        TopOpeBRep_FFTransitionTool::ProcessLineTransition(vpf, ISI, vpf.Edge(ISI).Orientation());
      TopOpeBRepDS_Transition Tl =
        TopOpeBRep_FFTransitionTool::ProcessLineTransition(vpl, ISI, vpl.Edge(ISI).Orientation());
      bool toreverse = (Tf.Orientation(TopAbs_IN) == TopAbs_REVERSED);
      toreverse      = toreverse && (Tl.Orientation(TopAbs_IN) == TopAbs_FORWARD);
      if (toreverse)
      {
        vpff = vpl;
        vpll = vpf;
      }
    }
  }

  TopoDS_Shape F;
  if (isonedge1)
    F = myF2;
  else
    F = myF1;
  double uf = TopOpeBRep_FacesFiller::VPParamOnER(vpff, Lrest);
  double ul = TopOpeBRep_FacesFiller::VPParamOnER(vpll, Lrest);

  bool   badparametrized = (uf > ul);
  double f, l;
  f = BAC.FirstParameter();
  l = BAC.LastParameter();
  if (badparametrized)
  {
    if (isperiodic)
    {
      if (uf == l)
        uf = f;
      if (ul == f)
        ul = l;
    }
  }

  const TopoDS_Edge& arc = TopoDS::Edge(Lrest.Arc());
  BRepAdaptor_Curve  BC(arc);
  double             x      = 0.789;
  double             parmil = (1 - x) * uf + x * ul;
  gp_Pnt             pmil   = BC.Value(parmil);

#ifdef OCCT_DEBUG
#endif
  TopAbs_State st = FSC_StatePonFace(pmil, F, *myPShapeClassifier);
  return st;
}

TopAbs_State TopOpeBRep_FacesFiller::StateVPonFace(const TopOpeBRep_VPointInter& VP) const
{
  int iVP = VP.ShapeIndex();
  if (iVP == 3)
    return TopAbs_ON;

  int          iother = (iVP == 1) ? 2 : 1;
  TopoDS_Shape F;
  if (iother == 1)
    F = myF1;
  else
    F = myF2;
  double u, v;
  if (iother == 1)
    VP.ParametersOnS1(u, v);
  else
    VP.ParametersOnS2(u, v);

  myPShapeClassifier->SetReference(TopoDS::Face(F));
  myPShapeClassifier->StateP2DReference(gp_Pnt2d(u, v));
  TopAbs_State state = myPShapeClassifier->State();

  return state;
}

void TopOpeBRep_FacesFiller::Lminmax(const TopOpeBRep_LineInter& L, double& pmin, double& pmax)
{
  pmin = RealLast();
  pmax = RealFirst();
  TopOpeBRep_VPointInterIterator VPI;
  VPI.Init(L, false);
  for (; VPI.More(); VPI.Next())
  {
    const TopOpeBRep_VPointInter& VP = VPI.CurrentVP();
    double                        p  = VP.ParameterOnLine();
    pmin                             = std::min(pmin, p);
    pmax                             = std::max(pmax, p);
  }
  double d     = std::abs(pmin - pmax);
  bool   id    = (d <= Precision::PConfusion());
  bool   isper = L.IsPeriodic();
  int    n     = L.NbVPoint();
  if (id && isper && n >= 2)
  {
    double per = L.Period();
    pmax       = pmin + per;
  }
}

bool TopOpeBRep_FacesFiller::LSameDomainERL(const TopOpeBRep_LineInter&           L,
                                            const NCollection_List<TopoDS_Shape>& ERL)
{
  bool isone = false;
  if (L.TypeLineCurve() == TopOpeBRep_WALKING)
    return isone;

  double f, l;
  TopOpeBRep_FacesFiller::Lminmax(L, f, l);
  double d = std::abs(f - l);

  {
    bool idINL = (L.INL() && (d == 0));
    if (idINL)
      return false;
  }

  bool id = (d <= Precision::PConfusion());
  if (id)
    return false;

  occ::handle<Geom_Curve> CL;
  TopOpeBRep_GeomTool::MakeCurve(f, l, L, CL);
  double t  = 0.417789;
  double p  = (1 - t) * f + t * l;
  gp_Pnt Pm = CL->Value(p);

  NCollection_List<TopoDS_Shape>::Iterator it;
  it.Initialize(ERL);
  for (; it.More(); it.Next())
  {
    const TopoDS_Edge& E      = TopoDS::Edge(it.Value());
    double             tolE   = BRep_Tool::Tolerance(E);
    double             maxtol = std::max(tolE, GLOBAL_tolFF);
    BRepAdaptor_Curve  BAC(E);
    f         = BAC.FirstParameter();
    l         = BAC.LastParameter();
    bool pinc = FUN_tool_PinC(Pm, BAC, f, l, maxtol);
    if (pinc)
    {
      isone = true;
      break;
    }
  }
  return isone;
}

bool TopOpeBRep_FacesFiller::IsVPtransLok(const TopOpeBRep_LineInter& L,
                                          const int                   iVP,
                                          const int                   SI12,
                                          TopOpeBRepDS_Transition&    T)
{
  const TopOpeBRep_VPointInter& VP     = L.VPoint(iVP);
  bool                          is1    = (SI12 == 1);
  bool                          VPonEd = (is1 && VP.IsOnDomS1());
  VPonEd                               = VPonEd || (!is1 && VP.IsOnDomS2());
  if (!VPonEd)
    return false;

  const TopoDS_Edge& E = TopoDS::Edge(VP.Edge(SI12));
  TopAbs_Orientation O = E.Orientation();
  T                    = TopOpeBRep_FFTransitionTool::ProcessLineTransition(VP, SI12, O);
  bool u               = T.IsUnknown();
  return (!u);
}

bool TopOpeBRep_FacesFiller::TransvpOK(const TopOpeBRep_LineInter& L,
                                       const int                   ivp,
                                       const int                   SI,
                                       const bool                  isINOUT)
{
#define M_INOUT(stf, stl) ((stf == TopAbs_IN) && (stl == TopAbs_OUT))
#define M_OUTIN(stf, stl) ((stf == TopAbs_OUT) && (stl == TopAbs_IN))

  TopOpeBRepDS_Transition T;
  bool                    ok = TopOpeBRep_FacesFiller::IsVPtransLok(L, ivp, SI, T);
  if (ok)
  {
    TopAbs_State stb = T.Before();
    TopAbs_State sta = T.After();
    if (isINOUT)
      ok = M_INOUT(stb, sta);
    else
      ok = M_OUTIN(stb, sta);
  }
  return ok;
}

double TopOpeBRep_FacesFiller::VPParamOnER(const TopOpeBRep_VPointInter& vp,
                                           const TopOpeBRep_LineInter&   Lrest)
{

  const TopoDS_Edge& E       = TopoDS::Edge(Lrest.Arc());
  bool               isedge1 = Lrest.ArcIsEdge(1);
  bool               isedge2 = Lrest.ArcIsEdge(2);
  if (isedge1 && vp.IsVertexOnS1())
  {
    const TopoDS_Vertex& v1 = TopoDS::Vertex(vp.VertexOnS1());
    double               rr = BRep_Tool::Parameter(v1, E);
    return rr;
  }
  if (isedge2 && vp.IsVertexOnS2())
  {
    const TopoDS_Vertex& v2 = TopoDS::Vertex(vp.VertexOnS2());
    double               rr = BRep_Tool::Parameter(v2, E);
    return rr;
  }

  if (isedge1 && vp.IsOnDomS1())
    return vp.ParameterOnArc1();
  if (isedge2 && vp.IsOnDomS2())
    return vp.ParameterOnArc2();

  double tolee = BRep_Tool::Tolerance(E);
  tolee        = tolee * 1.e2;
  double param, dist;
  bool   projok = FUN_tool_projPonE(vp.Value(), tolee, E, param, dist);
  if (!projok)
  {
    throw Standard_ProgramError("TopOpeBRep_FacesFiller::VPParamOnER");
  }
  return param;
}

Standard_EXPORT bool FUN_EqualPonR(const TopOpeBRep_LineInter&,
                                   const TopOpeBRep_VPointInter& VP1,
                                   const TopOpeBRep_VPointInter& VP2)
{
  gp_Pnt P1    = VP1.Value();
  gp_Pnt P2    = VP2.Value();
  double Ptol1 = VP1.Tolerance(), Ptol2 = VP2.Tolerance();
  double Ptol   = (Ptol1 > Ptol2) ? Ptol1 : Ptol2;
  bool   Pequal = P1.IsEqual(P2, Ptol);
  return Pequal;
}

Standard_EXPORT bool FUN_EqualponR(const TopOpeBRep_LineInter&   Lrest,
                                   const TopOpeBRep_VPointInter& VP1,
                                   const TopOpeBRep_VPointInter& VP2)
{
  double p1     = TopOpeBRep_FacesFiller::VPParamOnER(VP1, Lrest);
  double p2     = TopOpeBRep_FacesFiller::VPParamOnER(VP2, Lrest);
  bool   pequal = fabs(p1 - p2) < Precision::PConfusion();
  return pequal;
}

bool TopOpeBRep_FacesFiller::EqualpPonR(const TopOpeBRep_LineInter&   Lrest,
                                        const TopOpeBRep_VPointInter& VP1,
                                        const TopOpeBRep_VPointInter& VP2)
{
  bool Pequal  = ::FUN_EqualPonR(Lrest, VP1, VP2);
  bool pequal  = ::FUN_EqualponR(Lrest, VP1, VP2);
  bool pPequal = Pequal && pequal;
  return pPequal;
}
