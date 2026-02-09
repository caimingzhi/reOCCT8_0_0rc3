#include <gp_Vec.hpp>
#include <gp_Pnt2d.hpp>
#include <BRep_Tool.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_TOOL.hpp>

#define M_FORWARD(ori) (ori == TopAbs_FORWARD)
#define M_REVERSED(ori) (ori == TopAbs_REVERSED)
#define M_INTERNAL(ori) (ori == TopAbs_INTERNAL)
#define M_EXTERNAL(ori) (ori == TopAbs_EXTERNAL)

Standard_EXPORT gp_Dir FUN_tool_nCinsideS(const gp_Dir& tgC, const gp_Dir& ngS)
{

  gp_Dir XX(ngS ^ tgC);
  return XX;
}

Standard_EXPORT gp_Dir2d FUN_tool_nC2dINSIDES(const gp_Dir2d& tgC2d)
{

  gp_Dir X, Y, Z;
  Z = gp_Dir(gp_Dir::D::Z);
  X = gp_Dir(tgC2d.X(), tgC2d.Y(), 0.);
  Y = Z ^ X;
  gp_Dir2d xx(Y.X(), Y.Y());
  return xx;
}

Standard_EXPORT gp_Vec FUN_tool_getgeomxx(const TopoDS_Face&,
                                          const TopoDS_Edge& Ei,
                                          const double       parEi,
                                          const gp_Dir&      ngFi)
{

  gp_Vec tgEi;
  bool   ok = TopOpeBRepTool_TOOL::TggeomE(parEi, Ei, tgEi);
  if (!ok)
    return gp_Vec(0., 0., 0.);
  gp_Dir XX = FUN_tool_nCinsideS(tgEi, ngFi);
  return XX;
}

Standard_EXPORT gp_Vec FUN_tool_getgeomxx(const TopoDS_Face& Fi,
                                          const TopoDS_Edge& Ei,
                                          const double       parOnEi)
{
  gp_Vec   xx(1., 0., 0.);
  gp_Pnt2d uvi;
  bool     ok = FUN_tool_paronEF(Ei, parOnEi, Fi, uvi);
  if (!ok)
    return xx;
  gp_Vec ngFi = FUN_tool_nggeomF(uvi, Fi);
  xx          = FUN_tool_getgeomxx(Fi, Ei, parOnEi, ngFi);
  return xx;
}

Standard_EXPORT bool FUN_tool_getxx(const TopoDS_Face& Fi,
                                    const TopoDS_Edge& Ei,
                                    const double       parEi,
                                    const gp_Dir&      ngFi,
                                    gp_Dir&            XX)
{
  gp_Vec xx = FUN_tool_getgeomxx(Fi, Ei, parEi, ngFi);
  if (xx.Magnitude() < gp::Resolution())
    return false;
  XX = gp_Dir(xx);
  TopAbs_Orientation oriEinF;
  bool               ok = FUN_tool_orientEinFFORWARD(Ei, Fi, oriEinF);
  if (!ok)
    return false;
  if (M_REVERSED(oriEinF))
    XX.Reverse();
  return true;
}

Standard_EXPORT bool FUN_tool_getxx(const TopoDS_Face& Fi,
                                    const TopoDS_Edge& Ei,
                                    const double       parEi,
                                    gp_Dir&            XX)
{
  double   tolFi = BRep_Tool::Tolerance(Fi) * 1.e2;
  gp_Pnt2d uv;
  bool     ok = FUN_tool_parF(Ei, parEi, Fi, uv, tolFi);
  if (!ok)
    return false;
  gp_Vec ng = FUN_tool_nggeomF(uv, Fi);
  ok        = FUN_tool_getxx(Fi, Ei, parEi, ng, XX);
  return ok;
}

Standard_EXPORT bool FUN_tool_getdxx(const TopoDS_Face& F,
                                     const TopoDS_Edge& E,

                                     const double,
                                     gp_Vec2d& dxx)

{
  dxx = gp_Vec2d(0., 0.);
  TopAbs_Orientation oEinFF;
  bool               ok = FUN_tool_orientEinFFORWARD(E, F, oEinFF);
  if (!ok)
    return false;
  if (M_INTERNAL(oEinFF) || M_EXTERNAL(oEinFF))
    return false;

  bool     isoU, isoV;
  gp_Dir2d d2d;
  gp_Pnt2d o2d;
  bool     iso = TopOpeBRepTool_TOOL::UVISO(E, F, isoU, isoV, d2d, o2d);
  if (!iso)
    return false;
  double u1, u2, v1, v2;
  ok = FUN_tool_isobounds(F, u1, u2, v1, v2);
  if (!ok)
    return false;

  double xpar = isoU ? o2d.X() : o2d.Y();
  double xinf = isoU ? u1 : v1;
  double xsup = isoU ? u2 : v2;

  ok = ::FUN_nearestISO(F, xpar, isoU, xinf, xsup);
  if (!ok)
    return false;

  double ypar            = isoU ? d2d.Y() : d2d.X();
  bool   matterAFTERxpar = false;
  if (isoU)
    matterAFTERxpar = (ypar < 0.);
  if (isoV)
    matterAFTERxpar = (ypar > 0.);
  if (oEinFF == TopAbs_REVERSED)
    matterAFTERxpar = !matterAFTERxpar;

  double dx = 0.;
  if (matterAFTERxpar)
    dx = xsup - xpar;
  else
    dx = xinf - xpar;

  if (isoU)
    dxx = gp_Vec2d(dx, 0.);
  if (isoV)
    dxx = gp_Vec2d(0., dx);
  return true;
}
