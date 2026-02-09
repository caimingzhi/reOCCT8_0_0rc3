#include <Adaptor3d_Surface.hpp>
#include <ChFiDS_SurfData.hpp>
#include <ChFiKPart_ComputeData.hpp>
#include <ChFiKPart_ComputeData_Fcts.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_Circle.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <gp.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax3.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <TopOpeBRepDS_DataStructure.hpp>

bool ChFiKPart_MakeChAsym(TopOpeBRepDS_DataStructure&         DStr,
                          const occ::handle<ChFiDS_SurfData>& Data,
                          const gp_Pln&                       Pln,
                          const gp_Cone&                      Con,
                          const double                        fu,
                          const double                        lu,
                          const TopAbs_Orientation            Or1,
                          const TopAbs_Orientation            Or2,
                          const double                        Dis,
                          const double                        Angle,
                          const gp_Circ&                      Spine,
                          const double                        First,
                          const TopAbs_Orientation            Ofpl,
                          const bool                          plandab,
                          const bool                          DisOnP)
{

  gp_Ax3 PosPl = Pln.Position();
  gp_Dir Dpl   = PosPl.XDirection().Crossed(PosPl.YDirection());
  gp_Dir norf  = Dpl;
  if (Ofpl == TopAbs_REVERSED)
    norf.Reverse();
  if (Or1 == TopAbs_REVERSED)
    Dpl.Reverse();

  gp_Pnt Or = Con.Location();
  double u, v;
  ElSLib::PlaneParameters(PosPl, Or, u, v);
  gp_Pnt2d pt2dPln(u, v);
  ElSLib::PlaneD0(u, v, PosPl, Or);
  gp_Pnt PtPl = Or;

  gp_Pnt PtSp;
  gp_Vec DSp;
  ElCLib::D1(First, Spine, PtSp, DSp);
  gp_Dir Dx(gp_Vec(PtPl, PtSp));

  gp_Vec deru, derv;
  gp_Pnt PtCon;
  ElSLib::Parameters(Con, PtSp, u, v);
  ElSLib::D1(u, v, Con, PtCon, deru, derv);
  gp_Dir Dcon(deru.Crossed(derv));
  if (Or2 == TopAbs_REVERSED)
    Dcon.Reverse();

  bool dedans = (Dx.Dot(Dcon) <= 0.);
  bool ouvert = (Dpl.Dot(Dcon) >= 0.);

  double angCon = Con.SemiAngle();
  double move;
  double ChamfRad, SemiAngl;
  bool   pointu = false;
  double dis;
  bool   iscylinder = false;
  bool   isConPar   = false;

  if ((plandab && DisOnP) || (!plandab && !DisOnP))
  {
    double tgang = std::tan(Angle), Dis11;
    double tgCon = std::abs(std::tan(angCon));
    if (ouvert)
    {
      move  = Dis * tgang / (1. - tgCon * tgang);
      Dis11 = move * tgCon;
      dis   = Dis + Dis11;
    }
    else
    {
      move  = Dis * tgang / (1. + tgCon * tgang);
      Dis11 = move * tgCon;
      dis   = Dis - Dis11;
    }

    if (dedans)
    {
      ChamfRad = Spine.Radius() - Dis;
      if (std::abs(ChamfRad) < Precision::Confusion())
        pointu = true;
      if (ChamfRad < 0)
      {
#ifdef OCCT_DEBUG
        std::cout << "the chamfer can't pass" << std::endl;
#endif
        return false;
      }
      SemiAngl = M_PI / 2. - Angle;
    }
    else
    {
      ChamfRad = Spine.Radius() + Dis;
      SemiAngl = Angle - M_PI / 2.;
    }

    if (ouvert)
    {
      if (std::abs(angCon) - std::abs(SemiAngl) > -Precision::Confusion())
      {
#ifdef OCCT_DEBUG
        std::cout << "wrong choice of angle for the chamfer" << std::endl;
#endif
        return false;
      }
    }
  }
  else
  {
    double Dis1;
    move = Dis * std::cos(angCon);
    if (ouvert)
    {
      SemiAngl = std::abs(angCon) + Angle;

      if ((M_PI / 2. - SemiAngl) < Precision::Confusion())
      {
#ifdef OCCT_DEBUG
        std::cout << "wrong choice of angle for the chamfer" << std::endl;
#endif
        return false;
      }
      Dis1 = move * std::tan(SemiAngl) - Dis * std::abs(std::sin(angCon));

      if (!dedans)
        SemiAngl = -SemiAngl;
    }
    else
    {
      SemiAngl = std::abs(angCon) - Angle;

      if (std::abs(SemiAngl) < Precision::Confusion())
      {
        iscylinder = true;
        Dis1       = Dis * std::abs(std::sin(angCon));
      }
      else
      {
        Dis1 = Dis * std::abs(std::sin(angCon)) - move * std::tan(SemiAngl);
      }

      if (SemiAngl > Precision::Confusion())
        isConPar = true;

      if (dedans)
        SemiAngl = -SemiAngl;
    }

    if (dedans)
    {
      ChamfRad = Spine.Radius() - Dis1;

      if (std::abs(ChamfRad) < Precision::Confusion())
        pointu = true;
      if (ChamfRad < 0)
      {
#ifdef OCCT_DEBUG
        std::cout << "the chamfer can't pass" << std::endl;
#endif
        return false;
      }
    }
    else
    {
      ChamfRad = Spine.Radius() + Dis1;
    }

    if (ouvert)
      dis = Dis1 + Dis * std::abs(std::sin(angCon));
    else
      dis = Dis1 - Dis * std::abs(std::sin(angCon));
  }

  Or.SetCoord(Or.X() + move * Dpl.X(), Or.Y() + move * Dpl.Y(), Or.Z() + move * Dpl.Z());
  gp_Pnt Pt(Or.X() + dis * PosPl.XDirection().X(),
            Or.Y() + dis * PosPl.XDirection().Y(),
            Or.Z() + dis * PosPl.XDirection().Z());

  gp_Ax3 ChamfAx3(PtPl, Dpl, Dx);

  if (iscylinder)
  {
    occ::handle<Geom_CylindricalSurface> gcyl = new Geom_CylindricalSurface(ChamfAx3, ChamfRad);

    if (!plandab)
    {
      gcyl->VReverse();
      ChamfAx3 = gcyl->Position();
    }

    if (ChamfAx3.YDirection().Dot(DSp) <= 0.)
    {
      ChamfAx3.YReverse();
      gcyl->SetPosition(ChamfAx3);
    }

    Data->ChangeSurf(ChFiKPart_IndexSurfaceInDS(gcyl, DStr));

    bool   torevcha = !ChamfAx3.Direct();
    gp_Dir cylaxe   = (ChamfAx3.Axis()).Direction();
    torevcha        = ((torevcha && !plandab) || (!torevcha && plandab));

    if (torevcha)
      cylaxe.Reverse();
    bool toreverse = (norf.Dot(cylaxe) < 0.);

    if ((toreverse && dedans) || (!toreverse && !dedans))
      Data->ChangeOrientation() = TopAbs_REVERSED;
    else
      Data->ChangeOrientation() = TopAbs_FORWARD;

    occ::handle<Geom_Circle>   GCirPln;
    occ::handle<Geom2d_Circle> GCir2dPln;
    gp_Ax2                     CirAx2 = ChamfAx3.Ax2();
    CirAx2.SetLocation(PtPl);

    Pt.SetCoord(PtPl.X() + ChamfRad * Dx.X(),
                PtPl.Y() + ChamfRad * Dx.Y(),
                PtPl.Z() + ChamfRad * Dx.Z());
    gp_Circ CirPln(CirAx2, ChamfRad);
    GCirPln = new Geom_Circle(CirPln);

    ElSLib::PlaneParameters(PosPl, Pt, u, v);
    gp_Pnt2d  p2dPln(u, v);
    gp_Dir2d  d2d(DSp.Dot(PosPl.XDirection()), DSp.Dot(PosPl.YDirection()));
    gp_Ax22d  ax2dPln(pt2dPln, gp_Dir2d(gp_Vec2d(pt2dPln, p2dPln)), d2d);
    gp_Circ2d cir2dPln(ax2dPln, ChamfRad);
    GCir2dPln = new Geom2d_Circle(cir2dPln);

    gp_Pnt2d p2dch;
    p2dch.SetCoord(0., 0.);

    gp_Lin2d                 lin2dch(p2dch, gp::DX2d());
    occ::handle<Geom2d_Line> GLin2dCh1 = new Geom2d_Line(lin2dch);

    TopAbs_Orientation trans;
    gp_Dir             norpl = PosPl.XDirection().Crossed(PosPl.YDirection());
    toreverse                = (norpl.Dot(cylaxe) < 0.);

    toreverse = (toreverse && plandab) || (!toreverse && !plandab);

    if ((toreverse && dedans) || (!toreverse && !dedans))
    {
      trans = TopAbs_FORWARD;
    }
    else
    {
      trans = TopAbs_REVERSED;
    }

    if (plandab)
    {
      Data->ChangeInterferenceOnS1().SetInterference(ChFiKPart_IndexCurveInDS(GCirPln, DStr),
                                                     trans,
                                                     GCir2dPln,
                                                     GLin2dCh1);
    }
    else
    {
      Data->ChangeInterferenceOnS2().SetInterference(ChFiKPart_IndexCurveInDS(GCirPln, DStr),
                                                     trans,
                                                     GCir2dPln,
                                                     GLin2dCh1);
    }

    double Rad;
    if (dedans)
      Rad = ChamfRad + dis;
    else
      Rad = ChamfRad - dis;

    CirAx2.SetLocation(Or);
    gp_Circ                  CirCon(CirAx2, Rad);
    occ::handle<Geom_Circle> GCirCon = new Geom_Circle(CirCon);

    if (plandab)
      v = sqrt(dis * dis + move * move);
    else
      v = -sqrt(dis * dis + move * move);
    p2dch.SetCoord(0., v);
    ElSLib::CylinderD1(0., v, ChamfAx3, ChamfRad, Pt, deru, derv);
    lin2dch.SetLocation(p2dch);
    occ::handle<Geom2d_Line> GLin2dCh2 = new Geom2d_Line(lin2dch);

    Pt.SetCoord(Or.X() + Rad * Dx.X(), Or.Y() + Rad * Dx.Y(), Or.Z() + Rad * Dx.Z());
    ElSLib::Parameters(Con, Pt, u, v);
    double tol = Precision::PConfusion();
    if (u >= 2 * M_PI - tol && u <= 2 * M_PI)
      u = 0.;
    if (u >= fu - tol && u < fu)
      u = fu;
    if (u <= lu + tol && u > lu)
      u = lu;
    if (u < fu || u > lu)
      u = ElCLib::InPeriod(u, fu, fu + 2 * M_PI);
    ElSLib::D1(u, v, Con, Pt, deru, derv);
    gp_Pnt2d p2dCon(u, v);
    gp_Dir2d d2dCon;
    if (deru.Dot(DSp) <= 0.)
      d2dCon = -gp::DX2d();
    else
      d2dCon = gp::DX2d();
    gp_Lin2d                 lin2dCon(p2dCon, d2dCon);
    occ::handle<Geom2d_Line> GLin2dCon = new Geom2d_Line(lin2dCon);

    gp_Dir norcon = deru.Crossed(derv);

    gp_Dir DirCon = (Con.Axis()).Direction();
    if (angCon > Precision::Confusion())
      DirCon.Reverse();
    bool torevcon = (norcon.Dot(DirCon) < 0.);

    if ((torevcon && dedans) || (!torevcon && !dedans))
    {
      trans = TopAbs_REVERSED;
    }
    else
    {
      trans = TopAbs_FORWARD;
    }

    if (plandab)
    {
      Data->ChangeInterferenceOnS2().SetInterference(ChFiKPart_IndexCurveInDS(GCirCon, DStr),
                                                     trans,
                                                     GLin2dCon,
                                                     GLin2dCh2);
    }
    else
    {
      Data->ChangeInterferenceOnS1().SetInterference(ChFiKPart_IndexCurveInDS(GCirCon, DStr),
                                                     trans,
                                                     GLin2dCon,
                                                     GLin2dCh2);
    }
  }
  else
  {
    occ::handle<Geom_ConicalSurface> gcon = new Geom_ConicalSurface(ChamfAx3, SemiAngl, ChamfRad);

    if (!plandab)
    {
      gcon->VReverse();
      ChamfAx3 = gcon->Position();
      SemiAngl = gcon->SemiAngle();
    }

    if (ChamfAx3.YDirection().Dot(DSp) <= 0.)
    {
      ChamfAx3.YReverse();
      gcon->SetPosition(ChamfAx3);
    }

    Data->ChangeSurf(ChFiKPart_IndexSurfaceInDS(gcon, DStr));

    gp_Pnt P;
    u = 0.;
    if (plandab)
      v = sqrt(dis * dis + move * move);
    else
      v = -sqrt(dis * dis + move * move);

    ElSLib::ConeD1(u, v, ChamfAx3, ChamfRad, SemiAngl, P, deru, derv);
    gp_Dir norchamf(deru.Crossed(derv));

    bool toreverse = (norf.Dot(norchamf) < 0.);

    if (isConPar)
      toreverse = !toreverse;

    if (toreverse)
      Data->ChangeOrientation() = TopAbs_REVERSED;
    else
      Data->ChangeOrientation() = TopAbs_FORWARD;

    occ::handle<Geom_Circle>   GCirPln;
    occ::handle<Geom2d_Circle> GCir2dPln;
    gp_Ax2                     CirAx2 = ChamfAx3.Ax2();
    CirAx2.SetLocation(PtPl);

    if (!pointu)
    {
      Pt.SetCoord(PtPl.X() + ChamfRad * Dx.X(),
                  PtPl.Y() + ChamfRad * Dx.Y(),
                  PtPl.Z() + ChamfRad * Dx.Z());
      gp_Circ CirPln(CirAx2, ChamfRad);
      GCirPln = new Geom_Circle(CirPln);

      ElSLib::PlaneParameters(PosPl, Pt, u, v);
      gp_Pnt2d  p2dPln(u, v);
      gp_Dir2d  d2d(DSp.Dot(PosPl.XDirection()), DSp.Dot(PosPl.YDirection()));
      gp_Ax22d  ax2dPln(pt2dPln, gp_Dir2d(gp_Vec2d(pt2dPln, p2dPln)), d2d);
      gp_Circ2d cir2dPln(ax2dPln, ChamfRad);
      GCir2dPln = new Geom2d_Circle(cir2dPln);
    }

    gp_Pnt2d p2dch;
    p2dch.SetCoord(0., 0.);
    ElSLib::ConeD1(0., 0., ChamfAx3, ChamfRad, SemiAngl, Pt, deru, derv);
    gp_Lin2d                 lin2dch(p2dch, gp::DX2d());
    occ::handle<Geom2d_Line> GLin2dCh1 = new Geom2d_Line(lin2dch);

    TopAbs_Orientation trans;
    gp_Dir             norpl = PosPl.XDirection().Crossed(PosPl.YDirection());
    if (!pointu)
      norchamf.SetXYZ(deru.Crossed(derv).XYZ());
    toreverse = (norchamf.Dot(norpl) <= 0.);

    if (isConPar)
      toreverse = !toreverse;

    if ((toreverse && plandab) || (!toreverse && !plandab))
    {
      trans = TopAbs_FORWARD;
    }
    else
    {
      trans = TopAbs_REVERSED;
    }

    if (plandab)
    {
      Data->ChangeInterferenceOnS1().SetInterference(ChFiKPart_IndexCurveInDS(GCirPln, DStr),
                                                     trans,
                                                     GCir2dPln,
                                                     GLin2dCh1);
    }
    else
    {
      Data->ChangeInterferenceOnS2().SetInterference(ChFiKPart_IndexCurveInDS(GCirPln, DStr),
                                                     trans,
                                                     GCir2dPln,
                                                     GLin2dCh1);
    }

    double Rad;
    if (dedans)
      Rad = ChamfRad + dis;
    else
      Rad = ChamfRad - dis;

    CirAx2.SetLocation(Or);
    gp_Circ                  CirCon(CirAx2, Rad);
    occ::handle<Geom_Circle> GCirCon = new Geom_Circle(CirCon);

    if (plandab)
      v = sqrt(dis * dis + move * move);
    else
      v = -sqrt(dis * dis + move * move);
    p2dch.SetCoord(0., v);
    ElSLib::ConeD1(0., v, ChamfAx3, ChamfRad, SemiAngl, Pt, deru, derv);
    lin2dch.SetLocation(p2dch);
    occ::handle<Geom2d_Line> GLin2dCh2 = new Geom2d_Line(lin2dch);

    norchamf.SetXYZ(deru.Crossed(derv).XYZ());

    Pt.SetCoord(Or.X() + Rad * Dx.X(), Or.Y() + Rad * Dx.Y(), Or.Z() + Rad * Dx.Z());
    ElSLib::Parameters(Con, Pt, u, v);
    double tol = Precision::PConfusion();
    if (u >= 2 * M_PI - tol && u <= 2 * M_PI)
      u = 0.;
    if (u >= fu - tol && u < fu)
      u = fu;
    if (u <= lu + tol && u > lu)
      u = lu;
    if (u < fu || u > lu)
      u = ElCLib::InPeriod(u, fu, fu + 2 * M_PI);
    ElSLib::D1(u, v, Con, Pt, deru, derv);
    gp_Pnt2d p2dCon(u, v);
    gp_Dir2d d2dCon;
    if (deru.Dot(DSp) <= 0.)
      d2dCon = -gp::DX2d();
    else
      d2dCon = gp::DX2d();
    gp_Lin2d                 lin2dCon(p2dCon, d2dCon);
    occ::handle<Geom2d_Line> GLin2dCon = new Geom2d_Line(lin2dCon);

    gp_Dir norcon = deru.Crossed(derv);

    gp_Dir DirCon   = (Con.Axis()).Direction();
    gp_Dir DirChamf = (gcon->Axis()).Direction();
    if (angCon > Precision::Confusion())
      DirCon.Reverse();
    if (SemiAngl > Precision::Confusion())
      DirChamf.Reverse();

    bool torevcon = (norcon.Dot(DirCon) > 0.);
    bool torevcha = (norchamf.Dot(DirChamf) > 0.);

    toreverse = ((torevcon && !torevcha) || (!torevcon && torevcha));

    if ((toreverse && plandab) || (!toreverse && !plandab))
    {
      trans = TopAbs_REVERSED;
    }
    else
    {
      trans = TopAbs_FORWARD;
    }

    if (plandab)
    {
      Data->ChangeInterferenceOnS2().SetInterference(ChFiKPart_IndexCurveInDS(GCirCon, DStr),
                                                     trans,
                                                     GLin2dCon,
                                                     GLin2dCh2);
    }
    else
    {
      Data->ChangeInterferenceOnS1().SetInterference(ChFiKPart_IndexCurveInDS(GCirCon, DStr),
                                                     trans,
                                                     GLin2dCon,
                                                     GLin2dCh2);
    }
  }
  return true;
}
