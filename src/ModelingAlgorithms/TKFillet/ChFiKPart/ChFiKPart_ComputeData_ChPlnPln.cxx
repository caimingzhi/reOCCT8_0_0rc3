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

//=======================================================================
// function : MakeChamfer
// Purpose  : Compute the chamfer in the particular case plane/plane.
//           Compute the SurfData <Data> of the chamfer on the <Spine>
//           between the plane <Pl1> and the plane <Pl2>, with distances
//           <Dis1> on <Pl1> and <Dis2> on <Pl2>.
//           <First> is the parameter of the start point on the <Spine>
//           <Or1> and <Or2> are the orientations of the plane <Pl1> and
//           <Pl2>, and <Of1> the orientation of the face build on the
//           plane <Pl1>.
// Out      : True if the chamfer has been computed
//           False else
//=======================================================================
bool ChFiKPart_MakeChamfer(TopOpeBRepDS_DataStructure&         DStr,
                           const occ::handle<ChFiDS_SurfData>& Data,
                           const ChFiDS_ChamfMode              theMode,
                           const gp_Pln&                       Pl1,
                           const gp_Pln&                       Pl2,
                           const TopAbs_Orientation            Or1,
                           const TopAbs_Orientation            Or2,
                           const double                        theDis1,
                           const double                        theDis2,
                           const gp_Lin&                       Spine,
                           const double                        First,
                           const TopAbs_Orientation            Of1)
{

  // Creation of the plane which carry the chamfer

  // compute the normals to the planes Pl1 and Pl2
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

  // compute the intersection line of Pl1 and Pl2
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
  if (VecTransl1.Dot(D2) <= 0.)
    VecTransl1.Reverse();

  gp_Dir VecTransl2 = LinAx1.Crossed(D2);
  if (VecTransl2.Dot(D1) <= 0.)
    VecTransl2.Reverse();

  double Dis1 = theDis1, Dis2 = theDis2;
  double Alpha        = VecTransl1.Angle(VecTransl2);
  double CosHalfAlpha = std::cos(Alpha / 2);
  if (theMode == ChFiDS_ConstThroatChamfer)
    Dis1 = Dis2 = theDis1 / CosHalfAlpha;
  else if (theMode == ChFiDS_ConstThroatWithPenetrationChamfer)
  {
    double aDis1    = std::min(theDis1, theDis2);
    double aDis2    = std::max(theDis1, theDis2);
    double dis1dis1 = aDis1 * aDis1, dis2dis2 = aDis2 * aDis2;
    double SinAlpha   = std::sin(Alpha);
    double CosAlpha   = std::cos(Alpha);
    double CotanAlpha = CosAlpha / SinAlpha;
    Dis1              = sqrt(dis2dis2 - dis1dis1) - aDis1 * CotanAlpha;
    double CosBeta    = sqrt(1 - dis1dis1 / dis2dis2) * CosAlpha + aDis1 / aDis2 * SinAlpha;
    double FullDist1  = aDis2 / CosBeta;
    Dis2              = FullDist1 - aDis1 / SinAlpha;
  }

  // Compute a point on the plane Pl1 and on the chamfer
  gp_Pnt P1(P.X() + Dis1 * VecTransl1.X(),
            P.Y() + Dis1 * VecTransl1.Y(),
            P.Z() + Dis1 * VecTransl1.Z());

  // Point on the plane Pl2 and on the chamfer
  gp_Pnt P2(P.X() + Dis2 * VecTransl2.X(),
            P.Y() + Dis2 * VecTransl2.Y(),
            P.Z() + Dis2 * VecTransl2.Z());

  // the middle point of P1 P2 is the origin of the chamfer
  gp_Pnt Po((P1.X() + P2.X()) / 2., (P1.Y() + P2.Y()) / 2., (P1.Z() + P2.Z()) / 2.);

  // compute a second point on the plane Pl2
  gp_Pnt Pp = ElCLib::Value(Fint + 10., LInt.Line(1));
  gp_Pnt P22(Pp.X() + Dis2 * VecTransl2.X(),
             Pp.Y() + Dis2 * VecTransl2.Y(),
             Pp.Z() + Dis2 * VecTransl2.Z());

  // Compute the normal vector <AxisPlan> to the chamfer's plane
  gp_Dir V1(P2.X() - P1.X(), P2.Y() - P1.Y(), P2.Z() - P1.Z());
  gp_Dir V2(P22.X() - P1.X(), P22.Y() - P1.Y(), P22.Z() - P1.Z());
  gp_Dir AxisPlan = V1.Crossed(V2);

  gp_Dir xdir = LinAx1; // u axis
  gp_Ax3 PlanAx3(Po, AxisPlan, xdir);
  if (PlanAx3.YDirection().Dot(D2) >= 0.)
    PlanAx3.YReverse();

  occ::handle<Geom_Plane> gpl = new Geom_Plane(PlanAx3);
  Data->ChangeSurf(ChFiKPart_IndexSurfaceInDS(gpl, DStr));

  // About the orientation of the chamfer plane
  // Compute the normal to the face 1
  gp_Dir norpl    = Pos1.XDirection().Crossed(Pos1.YDirection());
  gp_Dir norface1 = norpl;
  if (Of1 == TopAbs_REVERSED)
  {
    norface1.Reverse();
  }

  // Compute the orientation of the chamfer plane
  gp_Dir norplch = gpl->Pln().Position().XDirection().Crossed(gpl->Pln().Position().YDirection());

  gp_Dir DirCh12(gp_Vec(P1, P2));
  bool   toreverse = (norplch.Dot(norface1) <= 0.);
  if (VecTransl1.Dot(DirCh12) > 0)
    toreverse = !toreverse;

  if (toreverse)
    Data->ChangeOrientation() = TopAbs_REVERSED;
  else
    Data->ChangeOrientation() = TopAbs_FORWARD;

  // Loading of the FaceInterferences with pcurves & 3d curves.

  // case face 1
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

  // case face 2

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
