#include <Adaptor3d_Surface.hpp>
#include <ChFiDS_SurfData.hpp>
#include <ChFiKPart_ComputeData.hpp>
#include <ChFiKPart_ComputeData_Fcts.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_Circle.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <gp.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax3.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <IntAna_QuadQuadGeo.hpp>
#include <Precision.hpp>
#include <TopOpeBRepDS_DataStructure.hpp>

bool ChFiKPart_MakeRotule(TopOpeBRepDS_DataStructure&         DStr,
                          const occ::handle<ChFiDS_SurfData>& Data,
                          const gp_Pln&                       pl,
                          const gp_Pln&                       pl1,
                          const gp_Pln&                       pl2,
                          const TopAbs_Orientation            opl,
                          const TopAbs_Orientation            opl1,
                          const TopAbs_Orientation            opl2,
                          const double                        r,
                          const TopAbs_Orientation            ofpl)
{

  gp_Ax3 pos    = pl.Position();
  gp_Dir dpl    = pos.XDirection().Crossed(pos.YDirection());
  gp_Dir dfpl   = dpl;
  gp_Dir dplnat = dpl;
  if (opl == TopAbs_REVERSED)
  {
    dpl.Reverse();
  }
  if (ofpl == TopAbs_REVERSED)
  {
    dfpl.Reverse();
  }
  pos         = pl1.Position();
  gp_Dir dpl1 = pos.XDirection().Crossed(pos.YDirection());
  if (opl1 == TopAbs_REVERSED)
  {
    dpl1.Reverse();
  }
  pos         = pl2.Position();
  gp_Dir dpl2 = pos.XDirection().Crossed(pos.YDirection());
  if (opl2 == TopAbs_REVERSED)
  {
    dpl2.Reverse();
  }

  double alpha = dpl1.Angle(dpl2);

  IntAna_QuadQuadGeo LInt(pl1, pl2, Precision::Angular(), Precision::Confusion());
  gp_Pnt             ptor, pcirc;
  if (LInt.IsDone())
  {

    pcirc = ElCLib::Value(ElCLib::Parameter(LInt.Line(1), pl.Location()), LInt.Line(1));
    ptor.SetCoord(pcirc.X() + r * dpl.X(), pcirc.Y() + r * dpl.Y(), pcirc.Z() + r * dpl.Z());
  }
  else
  {
    return false;
  }

  gp_Ax3 ppos(ptor, dpl.Reversed(), dpl1);
  if (ppos.YDirection().Dot(dpl2) < 0.)
    ppos.YReverse();
  occ::handle<Geom_ToroidalSurface> gtor = new Geom_ToroidalSurface(ppos, r, r);
  Data->ChangeSurf(ChFiKPart_IndexSurfaceInDS(gtor, DStr));

  gp_Pnt pp;
  gp_Vec du, dv;
  ElSLib::TorusD1(0., M_PI / 2, ppos, r, r, pp, du, dv);
  gp_Dir drot(du.Crossed(dv));
  bool   reversecur = (drot.Dot(dplnat) <= 0.);
  bool   reversefil = (drot.Dot(dfpl) <= 0.);
  if (reversefil)
  {
    Data->ChangeOrientation() = TopAbs_REVERSED;
  }
  else
  {
    Data->ChangeOrientation() = TopAbs_FORWARD;
  }

  gp_Ax2 circAx2 = ppos.Ax2();
  circAx2.SetLocation(pcirc);
  occ::handle<Geom_Circle> GC = new Geom_Circle(circAx2, r);
  double                   u, v;
  ElSLib::Parameters(pl, pcirc, u, v);
  gp_Pnt2d p2dcirc(u, v);
  gp_Dir2d dx2d(dpl1.Dot(pl.Position().XDirection()), dpl1.Dot(pl.Position().YDirection()));
  gp_Dir2d dy2d(ppos.YDirection().Dot(pl.Position().XDirection()),
                ppos.YDirection().Dot(pl.Position().YDirection()));
  gp_Ax22d circ2dax(p2dcirc, dx2d, dy2d);
  occ::handle<Geom2d_Circle> GC2d = new Geom2d_Circle(circ2dax, r);
  gp_Pnt2d                   p2dlin(0., M_PI / 2);
  occ::handle<Geom2d_Line>   GL2d  = new Geom2d_Line(p2dlin, gp::DX2d());
  TopAbs_Orientation         trans = TopAbs_REVERSED;
  if (reversecur)
    trans = TopAbs_FORWARD;
  Data->ChangeInterferenceOnS1().SetInterference(ChFiKPart_IndexCurveInDS(GC, DStr),
                                                 trans,
                                                 GC2d,
                                                 GL2d);

  occ::handle<Geom_Curve>   bid;
  occ::handle<Geom2d_Curve> bid2d;
  p2dlin.SetCoord(0., M_PI);
  occ::handle<Geom2d_Line> GL2dcoin = new Geom2d_Line(p2dlin, gp::DX2d());
  Data->ChangeInterferenceOnS2().SetInterference(ChFiKPart_IndexCurveInDS(bid, DStr),
                                                 trans,
                                                 bid2d,
                                                 GL2dcoin);

  Data->ChangeVertexFirstOnS1().SetPoint(pp);
  ElSLib::TorusD0(alpha, M_PI / 2, ppos, r, r, pp);
  Data->ChangeVertexLastOnS1().SetPoint(pp);
  Data->ChangeInterferenceOnS1().SetFirstParameter(0.);
  Data->ChangeInterferenceOnS1().SetLastParameter(alpha);
  Data->ChangeInterferenceOnS2().SetFirstParameter(0.);
  Data->ChangeInterferenceOnS2().SetLastParameter(alpha);

  return true;
}
