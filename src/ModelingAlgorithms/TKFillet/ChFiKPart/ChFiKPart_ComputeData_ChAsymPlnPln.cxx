#include <Adaptor3d_Surface.hpp>
#include <ChFiDS_Spine.hpp>
#include <ChFiDS_SurfData.hpp>
#include <ChFiKPart_ComputeData.hpp>
#include <ChFiKPart_ComputeData_Fcts.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <gp.hpp>
#include <gp_Ax3.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <IntAna_QuadQuadGeo.hpp>
#include <Precision.hpp>
#include <TopOpeBRepDS_DataStructure.hpp>

bool ChFiKPart_MakeChAsym(TopOpeBRepDS_DataStructure&         DStr,
                          const occ::handle<ChFiDS_SurfData>& Data,
                          const gp_Pln&                       Pl1,
                          const gp_Pln&                       Pl2,
                          const TopAbs_Orientation            Or1,
                          const TopAbs_Orientation            Or2,
                          const double                        Dis,
                          const double                        Angle,
                          const gp_Lin&                       Spine,
                          const double                        First,
                          const TopAbs_Orientation            Of1,
                          const bool                          DisOnP1)
{

  gp_Ax3 Pos1 = Pl1.Position();
  gp_Dir D1   = Pos1.XDirection().Crossed(Pos1.YDirection());
  if (Or1 == TopAbs_REVERSED)
  {
    D1.Reverse();
  }

  gp_Ax3 Pos2 = Pl2.Position();
  gp_Dir D2   = Pos2.XDirection().Crossed(Pos2.YDirection());
  if (Or2 == TopAbs_REVERSED)
  {
    D2.Reverse();
  }

  IntAna_QuadQuadGeo LInt(Pl1, Pl2, Precision::Angular(), Precision::Confusion());

  gp_Pnt P;
  double Fint;
  if (LInt.IsDone())
  {
    Fint = ElCLib::Parameter(LInt.Line(1), ElCLib::Value(First, Spine));
    P    = ElCLib::Value(Fint, LInt.Line(1));
  }
  else
  {
    return false;
  }

  gp_Dir LinAx1     = Spine.Direction();
  gp_Dir VecTransl1 = LinAx1.Crossed(D1);
  if (VecTransl1.Dot(D2) < 0.)
    VecTransl1.Reverse();

  gp_Dir VecTransl2 = LinAx1.Crossed(D2);
  if (VecTransl2.Dot(D1) < 0.)
    VecTransl2.Reverse();

  double cosP, sinP, dis1, dis2;
  cosP = VecTransl1.Dot(VecTransl2);
  sinP = sqrt(1. - cosP * cosP);

  if (DisOnP1)
  {
    dis1 = Dis;
    dis2 = Dis / (cosP + sinP / std::tan(Angle));
  }
  else
  {
    dis1 = Dis / (cosP + sinP / std::tan(Angle));
    dis2 = Dis;
  }

  gp_Pnt P1(P.X() + dis1 * VecTransl1.X(),
            P.Y() + dis1 * VecTransl1.Y(),
            P.Z() + dis1 * VecTransl1.Z());

  gp_Pnt P2(P.X() + dis2 * VecTransl2.X(),
            P.Y() + dis2 * VecTransl2.Y(),
            P.Z() + dis2 * VecTransl2.Z());

  gp_Pnt Po((P1.X() + P2.X()) / 2., (P1.Y() + P2.Y()) / 2., (P1.Z() + P2.Z()) / 2.);

  gp_Pnt Pp = ElCLib::Value(Fint + 10., LInt.Line(1));
  gp_Pnt P22(Pp.X() + dis2 * VecTransl2.X(),
             Pp.Y() + dis2 * VecTransl2.Y(),
             Pp.Z() + dis2 * VecTransl2.Z());

  gp_Dir V1(P2.X() - P1.X(), P2.Y() - P1.Y(), P2.Z() - P1.Z());
  gp_Dir V2(P22.X() - P1.X(), P22.Y() - P1.Y(), P22.Z() - P1.Z());
  gp_Dir AxisPlan = V1.Crossed(V2);

  gp_Dir xdir = LinAx1;
  gp_Ax3 PlanAx3(Po, AxisPlan, xdir);
  if (PlanAx3.YDirection().Dot(D2) >= 0.)
    PlanAx3.YReverse();

  occ::handle<Geom_Plane> gpl = new Geom_Plane(PlanAx3);
  Data->ChangeSurf(ChFiKPart_IndexSurfaceInDS(gpl, DStr));

  gp_Dir norpl    = Pos1.XDirection().Crossed(Pos1.YDirection());
  gp_Dir norface1 = norpl;
  if (Of1 == TopAbs_REVERSED)
  {
    norface1.Reverse();
  }

  gp_Dir norplch = gpl->Pln().Position().XDirection().Crossed(gpl->Pln().Position().YDirection());

  gp_Dir DirCh12(gp_Vec(P1, P2));
  bool   toreverse = (norplch.Dot(norface1) <= 0.);
  if (VecTransl1.Dot(DirCh12) > 0)
    toreverse = !toreverse;

  if (toreverse)
    Data->ChangeOrientation() = TopAbs_REVERSED;
  else
    Data->ChangeOrientation() = TopAbs_FORWARD;

  gp_Lin                 linPln(P1, xdir);
  occ::handle<Geom_Line> GLinPln1 = new Geom_Line(linPln);

  double u, v;
  ElSLib::PlaneParameters(Pos1, P1, u, v);
  gp_Pnt2d                 p2dPln(u, v);
  gp_Dir2d                 dir2dPln(xdir.Dot(Pos1.XDirection()), xdir.Dot(Pos1.YDirection()));
  gp_Lin2d                 lin2dPln(p2dPln, dir2dPln);
  occ::handle<Geom2d_Line> GLin2dPln1 = new Geom2d_Line(lin2dPln);

  ElSLib::PlaneParameters(PlanAx3, P1, u, v);
  p2dPln.SetCoord(u, v);
  lin2dPln.SetLocation(p2dPln);
  lin2dPln.SetDirection(gp::DX2d());
  occ::handle<Geom2d_Line> GLin2dPlnCh1 = new Geom2d_Line(lin2dPln);

  TopAbs_Orientation trans;
  toreverse = (norplch.Dot(norpl) <= 0.);
  if (VecTransl1.Dot(DirCh12) > 0)
    toreverse = !toreverse;
  if (toreverse)
    trans = TopAbs_FORWARD;
  else
    trans = TopAbs_REVERSED;

  Data->ChangeInterferenceOnS1().SetInterference(ChFiKPart_IndexCurveInDS(GLinPln1, DStr),
                                                 trans,
                                                 GLin2dPln1,
                                                 GLin2dPlnCh1);

  linPln.SetLocation(P2);
  occ::handle<Geom_Line> GLinPln2 = new Geom_Line(linPln);

  ElSLib::PlaneParameters(Pos2, P2, u, v);
  p2dPln.SetCoord(u, v);
  dir2dPln.SetCoord(xdir.Dot(Pos2.XDirection()), xdir.Dot(Pos2.YDirection()));
  lin2dPln.SetLocation(p2dPln);
  lin2dPln.SetDirection(dir2dPln);
  occ::handle<Geom2d_Line> GLin2dPln2 = new Geom2d_Line(lin2dPln);

  ElSLib::PlaneParameters(PlanAx3, P2, u, v);
  p2dPln.SetCoord(u, v);
  lin2dPln.SetLocation(p2dPln);
  lin2dPln.SetDirection(gp::DX2d());
  occ::handle<Geom2d_Line> GLin2dPlnCh2 = new Geom2d_Line(lin2dPln);

  norpl     = Pos2.XDirection().Crossed(Pos2.YDirection());
  toreverse = (norplch.Dot(norpl) <= 0.);
  if (VecTransl2.Dot(DirCh12) < 0)
    toreverse = !toreverse;
  if (toreverse)
    trans = TopAbs_REVERSED;
  else
    trans = TopAbs_FORWARD;

  Data->ChangeInterferenceOnS2().SetInterference(ChFiKPart_IndexCurveInDS(GLinPln2, DStr),
                                                 trans,
                                                 GLin2dPln2,
                                                 GLin2dPlnCh2);

  return true;
}
