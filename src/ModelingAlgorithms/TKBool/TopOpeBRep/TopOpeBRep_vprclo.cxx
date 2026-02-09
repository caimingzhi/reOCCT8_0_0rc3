#include <BRep_Tool.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRep_FacesFiller.hpp>
#include <TopOpeBRep_FFDumper.hpp>
#include <TopOpeBRep_LineInter.hpp>
#include <TopOpeBRep_VPointInter.hpp>
#include <TopOpeBRep_VPointInterClassifier.hpp>
#include <TopOpeBRepDS_EXPORT.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_Transition.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_makeTransition.hpp>

#define M_ON(st) (st == TopAbs_ON)
#define M_REVERSED(st) (st == TopAbs_REVERSED)

#ifdef OCCT_DEBUG
Standard_EXPORT void debarc(const int i);
Standard_EXPORT void debooarc(const int i);
#endif

Standard_EXPORT occ::handle<TopOpeBRepDS_Interference> MakeEPVInterference(
  const TopOpeBRepDS_Transition& T,
  const int                      S,
  const int                      G,
  const double                   P,
  const TopOpeBRepDS_Kind        GK,
  const bool                     B);
Standard_EXPORT occ::handle<TopOpeBRepDS_Interference> MakeEPVInterference(
  const TopOpeBRepDS_Transition& T,
  const int                      S,
  const int                      G,
  const double                   P,
  const TopOpeBRepDS_Kind        GK,
  const TopOpeBRepDS_Kind        SK,
  const bool                     B);

static bool FUN_INlos(const TopoDS_Shape& S, const NCollection_List<TopoDS_Shape>& loS)
{
  NCollection_List<TopoDS_Shape>::Iterator it(loS);
  for (; it.More(); it.Next())
    if (it.Value().IsSame(S))
      return true;
  return false;
}

TopOpeBRepDS_Transition TopOpeBRep_FacesFiller::GetEdgeTrans(const TopOpeBRep_VPointInter& VP,
                                                             const TopOpeBRepDS_Kind       PVKind,
                                                             const int                     PVIndex,
                                                             const int          ShapeIndex,
                                                             const TopoDS_Face& F)
{

  int  OOShapeIndex = (ShapeIndex == 1) ? 2 : 1;
  int  vpsind       = VP.ShapeIndex();
  bool on2edges     = (vpsind == 3);
  bool isvalid      = on2edges || (vpsind == ShapeIndex);
  if (!isvalid)
    throw Standard_Failure("TopOpeBRep_FacesFiller::GetEdgeTrans");

  const TopoDS_Edge& edge    = TopoDS::Edge(VP.Edge(ShapeIndex));
  double             paredge = VP.EdgeParameter(ShapeIndex);

  TopoDS_Edge OOedge;

  double OOparedge = 0.;

  bool hasONedge = (VP.State(OOShapeIndex) == TopAbs_ON);
  bool hasOOedge = (on2edges) ? true : hasONedge;
  if (hasOOedge)
  {
    if (on2edges)
      OOparedge = VP.EdgeParameter(OOShapeIndex);
    else
      OOparedge = VP.EdgeONParameter(OOShapeIndex);
    TopoDS_Shape OOe;
    if (on2edges)
      OOe = VP.Edge(OOShapeIndex);
    else
      OOe = VP.EdgeON(OOShapeIndex);
    OOedge = TopoDS::Edge(OOe);
  }
  gp_Pnt2d OOuv = VP.SurfaceParameters(OOShapeIndex);

  double par1, par2;
  int    SIedgeIndex = (myHDS->HasShape(edge)) ? myHDS->Shape(edge) : 0;

  if (SIedgeIndex != 0)
  {
    bool isonboundper;
    FDS_LOIinfsup(myHDS->DS(),
                  edge,
                  paredge,
                  PVKind,
                  PVIndex,
                  myHDS->DS().ShapeInterferences(edge),
                  par1,
                  par2,
                  isonboundper);
  }
  else
    FUN_tool_bounds(edge, par1, par2);

  TopOpeBRepDS_Transition T;

  double tola   = Precision::Angular() * 1.e+2;
  bool   EtgF   = FUN_tool_EtgF(paredge, edge, OOuv, F, tola);
  bool   rest   = FUN_INlos(edge, myERL);
  bool   isse   = myHDS->DS().IsSectionEdge(edge);
  rest          = rest || isse;
  bool interf2d = EtgF && hasOOedge && rest;

  double                        factor = 1.e-4;
  TopOpeBRepTool_makeTransition MKT;
  bool                          ok = MKT.Initialize(edge, par1, par2, paredge, F, OOuv, factor);
  if (!ok)
    return T;
  bool isT2d = MKT.IsT2d();
  interf2d   = interf2d && isT2d;
  if (interf2d)
    ok = MKT.SetRest(OOedge, OOparedge);
  if (!ok)
    return T;

  TopAbs_State stb, sta;
  ok = MKT.MkTonE(stb, sta);
  if (!ok)
    return T;
  T.Before(stb);
  T.After(sta);
  return T;
}

void TopOpeBRep_FacesFiller::ProcessVPonclosingR(const TopOpeBRep_VPointInter& VP,

                                                 const TopoDS_Shape&,
                                                 const int                      ShapeIndex,
                                                 const TopOpeBRepDS_Transition& transEdge,
                                                 const TopOpeBRepDS_Kind        PVKind,
                                                 const int                      PVIndex,

                                                 const bool,

                                                 const occ::handle<TopOpeBRepDS_Interference>&)
{

  bool isvertex     = (PVKind == TopOpeBRepDS_VERTEX);
  int  absindex     = VP.ShapeIndex();
  int  OOShapeIndex = (ShapeIndex == 1) ? 2 : 1;
  bool on2edges     = (absindex == 3);
  bool hasONedge    = (VP.State(OOShapeIndex) == TopAbs_ON);
  bool hasOOedge    = (on2edges) ? true : hasONedge;

  TopoDS_Face Face    = (*this).Face(ShapeIndex);
  TopoDS_Face OOFace  = (*this).Face(OOShapeIndex);
  int         iOOFace = myDS->Shape(OOFace);
  if (iOOFace == 0)
    iOOFace = myDS->AddShape(OOFace, OOShapeIndex);

  const TopoDS_Edge& edge = TopoDS::Edge(VP.Edge(ShapeIndex));
  if (!myDS->HasShape(edge))
    myDS->AddShape(edge, ShapeIndex);

  double paredge = VP.EdgeParameter(ShapeIndex);

  int         OOedgeIndex = 0;
  TopoDS_Edge OOedge;
  if (hasOOedge)
  {
    TopoDS_Shape OOe;
    if (on2edges)
      OOe = VP.Edge(OOShapeIndex);
    else
      OOe = VP.EdgeON(OOShapeIndex);
    OOedge = TopoDS::Edge(OOe);
    if (myDS->HasShape(OOedge))
      OOedgeIndex = myDS->Shape(OOedge);
    else
      OOedgeIndex = myDS->AddShape(OOedge, OOShapeIndex);
  }

  bool                    Tunk = transEdge.IsUnknown();
  TopOpeBRepDS_Transition transAdd;
  bool                    newtransEdge = Tunk;
  if (newtransEdge)
    transAdd = GetEdgeTrans(VP, PVKind, PVIndex, ShapeIndex, OOFace);
  else
    transAdd = transEdge;

  {
    TopOpeBRepDS_Transition T = transAdd;
    T.Index(iOOFace);
    occ::handle<TopOpeBRepDS_Interference> EPI =
      ::MakeEPVInterference(T, iOOFace, PVIndex, paredge, PVKind, TopOpeBRepDS_FACE, isvertex);
    myHDS->StoreInterference(EPI, edge);
  }
  if (hasOOedge)
  {
    TopOpeBRepDS_Transition T = transAdd;
    T.Index(iOOFace);
    occ::handle<TopOpeBRepDS_Interference> EPI =
      ::MakeEPVInterference(T, OOedgeIndex, PVIndex, paredge, PVKind, isvertex);
    myHDS->StoreInterference(EPI, edge);
  }
}
