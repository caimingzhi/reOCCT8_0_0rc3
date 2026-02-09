#include <BRep_Tool.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_mkTondgE.hpp>
#include <TopOpeBRepTool_TOOL.hpp>

#define M_FORWARD(sta) (sta == TopAbs_FORWARD)
#define M_REVERSED(sta) (sta == TopAbs_REVERSED)
#define M_INTERNAL(sta) (sta == TopAbs_INTERNAL)
#define M_EXTERNAL(sta) (sta == TopAbs_EXTERNAL)

#define FORWARD (1)
#define REVERSED (2)
#define INTERNAL (3)
#define EXTERNAL (4)
#define CLOSING (5)

#define NOI (0)
#define MKI1 (1)
#define MKI2 (2)
#define MKI12 (3)

static double FUN_tola()
{
  double tola = Precision::Angular();
  return tola;
}

TopOpeBRepTool_mkTondgE::TopOpeBRepTool_mkTondgE() = default;

bool TopOpeBRepTool_mkTondgE::Initialize(const TopoDS_Edge& dgE,
                                         const TopoDS_Face& F,
                                         const gp_Pnt2d&    uvi,
                                         const TopoDS_Face& Fi)
{
  isT2d   = false;
  hasRest = false;
  myclE.Nullify();
  myEpari.Clear();

  mydgE = dgE;
  myF   = F;

  TopExp_Explorer      exv(mydgE, TopAbs_VERTEX);
  const TopoDS_Vertex& v   = TopoDS::Vertex(exv.Current());
  double               par = BRep_Tool::Parameter(v, mydgE);
  gp_Pnt2d             uv;
  bool                 ok = FUN_tool_paronEF(mydgE, par, myF, uv);
  if (!ok)
    return false;
  gp_Vec tmp;
  ok    = TopOpeBRepTool_TOOL::NggeomF(uv, myF, tmp);
  myngf = gp_Dir(tmp);
  if (!ok)
    return false;

  myuvi    = uvi;
  myFi     = Fi;
  bool oki = TopOpeBRepTool_TOOL::NggeomF(myuvi, myFi, tmp);
  myngfi   = gp_Dir(tmp);
  if (!oki)
    return false;

  double dot = myngf.Dot(myngfi);
  isT2d      = (std::abs(1 - std::abs(dot)) < FUN_tola());
  return true;
}

bool TopOpeBRepTool_mkTondgE::SetclE(const TopoDS_Edge& clE)
{
  myclE = clE;
  return true;
}

bool TopOpeBRepTool_mkTondgE::IsT2d() const
{
  return isT2d;
}

bool TopOpeBRepTool_mkTondgE::SetRest(const double pari, const TopoDS_Edge& Ei)
{
  hasRest   = true;
  bool clEi = TopOpeBRepTool_TOOL::IsClosingE(Ei, myFi);
  if (clEi)
  {
    hasRest = false;
    return false;
  }

  myEpari.Bind(Ei, pari);
  return true;
}

int TopOpeBRepTool_mkTondgE::GetAllRest(NCollection_List<TopoDS_Shape>& lEi)
{
  lEi.Clear();

  BRepAdaptor_Surface bs(myFi);
  double              tol3d = bs.Tolerance();
  double              tolu  = bs.UResolution(tol3d);
  double              tolv  = bs.VResolution(tol3d);
  TopExp_Explorer     ex(myFi, TopAbs_EDGE);
  for (; ex.More(); ex.Next())
  {
    const TopoDS_Edge& ei  = TopoDS::Edge(ex.Current());
    bool               cli = TopOpeBRepTool_TOOL::IsClosingE(ei, myFi);
    if (cli)
      continue;

    bool isbi = myEpari.IsBound(ei);
    if (isbi)
    {
      lEi.Append(ei);
      continue;
    }

    bool     isou, isov;
    gp_Dir2d d2d;
    gp_Pnt2d o2d;
    bool     uviso = TopOpeBRepTool_TOOL::UVISO(ei, myFi, isou, isov, d2d, o2d);
    if (!uviso)
      continue;

    bool ok = false;
    if (isou)
      ok = std::abs(o2d.X() - myuvi.X()) < tolu;
    if (isov)
      ok = std::abs(o2d.Y() - myuvi.Y()) < tolv;
    if (!ok)
      continue;

    double parei;
    TopOpeBRepTool_TOOL::ParISO(myuvi, ei, myFi, parei);
    myEpari.Bind(ei, parei);
    lEi.Append(ei);
  }
  int nEi = lEi.Extent();
  return nEi;
}

static bool FUN_getEc(const TopoDS_Face& f, const TopoDS_Vertex& v, TopoDS_Edge& cle)
{
  TopExp_Explorer exe(f, TopAbs_EDGE);
  for (; exe.More(); exe.Next())
  {
    const TopoDS_Edge& e      = TopoDS::Edge(exe.Current());
    bool               closed = TopOpeBRepTool_TOOL::IsClosingE(e, f);
    if (!closed)
      continue;
    TopExp_Explorer exv(e, TopAbs_VERTEX);
    for (; exv.More(); exv.Next())
    {
      if (exv.Current().IsSame(v))
      {
        cle = e;
        return true;
      }
    }
  }
  return false;
}

static bool FUN_MkTonE(const gp_Vec& faxis,
                       const gp_Vec& dirINcle,
                       const gp_Vec& xxi,
                       const gp_Vec&,
                       double& par1,
                       double& par2,
                       bool&   outin)
{

  gp_Vec tgi = xxi.Crossed(faxis);

  double tola  = FUN_tola();
  double dot1  = dirINcle.Dot(xxi);
  bool   isONi = (std::abs(dot1) < tola);

  double ang = 1.e7;
  if (isONi)
  {
    double dot = dirINcle.Dot(tgi);
    ang        = (dot > 0) ? 0 : M_PI;

    outin = true;
  }
  else
  {
    if (!isONi)
      ang = TopOpeBRepTool_TOOL::Matter(dirINcle, tgi.Reversed(), faxis);

    double dot = isONi ? 0 : (dirINcle ^ tgi).Dot(faxis);
    if (dot1 < 0)
      outin = (dot > 0);
    else
      outin = (dot < 0);
  }

  double Cang = (ang > M_PI) ? ang - M_PI : ang + M_PI;
  par1        = outin ? ang : Cang;
  par2        = outin ? Cang : ang;
  return true;
}

bool TopOpeBRepTool_mkTondgE::MkTonE(int& mkT, double& par1, double& par2)
{
  if (isT2d)
    return false;

  mkT  = NOI;
  par1 = par2 = 1.e7;

  TopExp_Explorer      exv(mydgE, TopAbs_VERTEX);
  const TopoDS_Vertex& v = TopoDS::Vertex(exv.Current());

  if (myclE.IsNull())
  {
    bool find = FUN_getEc(myF, v, myclE);
    if (!find)
      return false;
  }

  int    ovcle;
  gp_Vec dirINcle;
  bool   ok = TopOpeBRepTool_TOOL::TgINSIDE(v, myclE, dirINcle, ovcle);
  if (!ok)
    return NOI;

  gp_Vec faxis = myngf;
  if (ovcle == FORWARD)
    faxis.Reverse();

  gp_Vec xxi;
  ok = TopOpeBRepTool_TOOL::NggeomF(myuvi, myFi, xxi);
  if (!ok)
    return false;
  if (M_FORWARD(myFi.Orientation()))
    xxi.Reverse();

  bool outin;
  ok = FUN_MkTonE(faxis, dirINcle, xxi, myngf, par1, par2, outin);
  if (ok)
    mkT = MKI12;
  return ok;
}

bool TopOpeBRepTool_mkTondgE::MkTonE(const TopoDS_Edge& ei, int& mkT, double& par1, double& par2)

{
  mkT  = NOI;
  par1 = par2 = 1.e7;
  hasRest     = myEpari.IsBound(ei);
  if (!hasRest)
    return false;
  const double pari = myEpari.Find(ei);

  double pfi, pli;
  FUN_tool_bounds(ei, pfi, pli);
  double tolpi = TopOpeBRepTool_TOOL::TolP(ei, myFi);
  bool   onfi = (std::abs(pari - pfi) < tolpi), onli = (std::abs(pari - pli) < tolpi);
  gp_Vec tgin1di;
  bool   ok = TopOpeBRepTool_TOOL::TggeomE(pari, ei, tgin1di);
  if (!ok)
    return false;
  if (onli)
    tgin1di.Reverse();

  TopExp_Explorer      exv(mydgE, TopAbs_VERTEX);
  const TopoDS_Vertex& v = TopoDS::Vertex(exv.Current());

  if (myclE.IsNull())
  {
    bool find = FUN_getEc(myF, v, myclE);
    if (!find)
      return false;
  }

  int    ovcle;
  gp_Vec dirINcle;
  ok = TopOpeBRepTool_TOOL::TgINSIDE(v, myclE, dirINcle, ovcle);
  if (!ok)
    return NOI;

  if (isT2d && !hasRest)
    return false;

  gp_Vec faxis = myngf;
  if (ovcle == FORWARD)
    faxis.Reverse();

  gp_Dir xxi;

  gp_Dir xxri;

  TopoDS_Vertex vclo;
  bool          closedi = TopOpeBRepTool_TOOL::ClosedE(ei, vclo);
  bool          outin;
  if (isT2d)
  {

    ok = TopOpeBRepTool_TOOL::XX(myuvi, myFi, pari, ei, xxi);
    if (!ok)
      return false;

    ok = FUN_MkTonE(faxis, dirINcle, xxi, myngf, par1, par2, outin);
    if (!ok)
      return false;

    if (!onfi && !onli)
    {
      mkT = MKI12;
      return true;
    }

    if (closedi)
    {
      mkT = MKI12;
      return true;
    }

    xxri = tgin1di;
  }
  else
  {

    gp_Vec tmp;
    ok  = TopOpeBRepTool_TOOL::NggeomF(myuvi, myFi, tmp);
    xxi = gp_Dir(tmp);
    if (!ok)
      return false;
    if (M_FORWARD(myFi.Orientation()))
      xxi.Reverse();

    ok = FUN_MkTonE(faxis, dirINcle, xxi, myngf, par1, par2, outin);
    if (!ok)
      return false;

    ok = TopOpeBRepTool_TOOL::XX(myuvi, myFi, pari, ei, xxri);
    if (!ok)
      return false;

    mkT        = MKI12;
    gp_Vec tgi = xxi.Crossed(faxis);
    double dot = tgi.Dot(xxri);
    if (std::abs(dot) < FUN_tola())
    {
      if ((!onfi && !onli) || closedi)
      {
        mkT = MKI12;
        return true;
      }
      else
        dot = tgi.Dot(tgin1di);
    }
    bool keepang = (dot > 0);
    if (keepang)
      mkT = outin ? MKI1 : MKI2;
    else
      mkT = outin ? MKI2 : MKI1;
    return true;
  }

  mkT            = MKI12;
  gp_Vec tgi     = xxi.Crossed(faxis);
  double dot     = tgi.Dot(xxri);
  bool   keepang = (dot > 0);
  if (keepang)
    mkT = outin ? MKI1 : MKI2;
  else
    mkT = outin ? MKI2 : MKI1;

  return true;
}
