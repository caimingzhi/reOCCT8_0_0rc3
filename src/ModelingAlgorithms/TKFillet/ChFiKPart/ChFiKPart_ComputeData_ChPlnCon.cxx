#include <Adaptor3d_Surface.hpp>
#include <ChFiDS_Spine.hpp>
#include <ChFiDS_SurfData.hpp>
#include <ChFiKPart_ComputeData.hpp>
#include <ChFiKPart_ComputeData_ChAsymPlnCon.hpp>
#include <ChFiKPart_ComputeData_Fcts.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <gp_Ax3.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <TopOpeBRepDS_DataStructure.hpp>

bool ChFiKPart_MakeChamfer(TopOpeBRepDS_DataStructure&         DStr,
                           const occ::handle<ChFiDS_SurfData>& Data,
                           const ChFiDS_ChamfMode              theMode,
                           const gp_Pln&                       Pln,
                           const gp_Cone&                      Con,
                           const double                        fu,
                           const double                        lu,
                           const TopAbs_Orientation            Or1,
                           const TopAbs_Orientation            Or2,
                           const double                        theDis1,
                           const double                        theDis2,
                           const gp_Circ&                      Spine,
                           const double                        First,
                           const TopAbs_Orientation            Ofpl,
                           const bool                          plandab)
{

  double angcon = Con.SemiAngle();

  double Dis1 = theDis1, Dis2 = theDis2;
  double Alpha        = M_PI / 2 - angcon;
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

  double sincon = std::abs(std::sin(angcon));
  double angle;
  bool   IsResol;

  gp_Ax3 PosPl = Pln.Position();
  gp_Dir Dpl   = PosPl.XDirection().Crossed(PosPl.YDirection());
  if (Or1 == TopAbs_REVERSED)
    Dpl.Reverse();

  gp_Pnt Or = Con.Location();
  double u, v;
  ElSLib::PlaneParameters(PosPl, Or, u, v);
#ifdef OCCT_DEBUG
  gp_Pnt2d pt2dPln(u, v);
#endif
  ElSLib::PlaneD0(u, v, PosPl, Or);

  gp_Pnt PtSp;
  gp_Vec DSp;
  ElCLib::D1(First, Spine, PtSp, DSp);
#ifdef OCCT_DEBUG
  gp_Dir Dx(gp_Vec(Or, PtSp));
#endif

  gp_Vec deru, derv;
  gp_Pnt PtCon;
  ElSLib::Parameters(Con, PtSp, u, v);
  ElSLib::D1(u, v, Con, PtCon, deru, derv);
  gp_Dir Dcon(deru.Crossed(derv));
  if (Or2 == TopAbs_REVERSED)
    Dcon.Reverse();

  bool ouvert = (Dpl.Dot(Dcon) >= 0.);

  if (!ouvert)
  {
    if (std::abs(Dis1 - Dis2 * sincon) > Precision::Confusion())
    {
      double abscos = std::abs(Dis2 - Dis1 * sincon);
      angle         = std::atan((Dis1 * std::cos(angcon)) / abscos);
    }
    else
    {
      angle = angcon;
    }
  }
  else
  {
    angle = std::atan((Dis1 * std::cos(angcon)) / (Dis2 + Dis1 * sincon));
  }

  bool DisOnP = false;

  IsResol = ChFiKPart_MakeChAsym(DStr,
                                 Data,
                                 Pln,
                                 Con,
                                 fu,
                                 lu,
                                 Or1,
                                 Or2,
                                 Dis2,
                                 angle,
                                 Spine,
                                 First,
                                 Ofpl,
                                 plandab,
                                 DisOnP);

  return IsResol;
}
