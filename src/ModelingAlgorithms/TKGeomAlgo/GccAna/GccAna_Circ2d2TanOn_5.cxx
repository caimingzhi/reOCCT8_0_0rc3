#include <ElCLib.hpp>
#include <GccAna_Circ2d2TanOn.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_IntPoint.hpp>

GccAna_Circ2d2TanOn::GccAna_Circ2d2TanOn(const gp_Pnt2d& Point1,
                                         const gp_Pnt2d& Point2,
                                         const gp_Lin2d& OnLine,
                                         const double    Tolerance)
    : cirsol(1, 2),
      qualifier1(1, 2),
      qualifier2(1, 2),
      TheSame1(1, 2),
      TheSame2(1, 2),
      pnttg1sol(1, 2),
      pnttg2sol(1, 2),
      pntcen(1, 2),
      par1sol(1, 2),
      par2sol(1, 2),
      pararg1(1, 2),
      pararg2(1, 2),
      parcen3(1, 2)
{
  TheSame1.Init(0);
  TheSame2.Init(0);
  WellDone = false;
  NbrSol   = 0;

  gp_Dir2d dirx(gp_Dir2d::D::X);
  double   dist = Point1.Distance(Point2);
  if (dist < std::abs(Tolerance))
  {
    WellDone = true;
  }
  else
  {
    gp_Lin2d                 L1(gp_Pnt2d((Point1.XY() + Point2.XY()) / 2.0),
                gp_Dir2d(Point1.Y() - Point2.Y(), Point2.X() - Point1.X()));
    IntAna2d_AnaIntersection Intp(L1, OnLine);
    if (Intp.IsDone())
    {
      if (!Intp.IsEmpty())
      {
        for (int i = 1; i <= Intp.NbPoints(); i++)
        {
          NbrSol++;
          gp_Ax2d axe(Intp.Point(i).Value(), dirx);
          cirsol(NbrSol) = gp_Circ2d(axe, Point1.Distance(Intp.Point(i).Value()));

          qualifier1(NbrSol) = GccEnt_noqualifier;
          qualifier2(NbrSol) = GccEnt_noqualifier;
          pnttg1sol(NbrSol)  = Point1;
          pnttg2sol(NbrSol)  = Point2;
          pntcen(NbrSol)     = cirsol(NbrSol).Location();
          pararg1(NbrSol)    = 0.;
          pararg2(NbrSol)    = 0.;
          par1sol(NbrSol)    = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
          par2sol(NbrSol)    = ElCLib::Parameter(cirsol(NbrSol), pnttg2sol(NbrSol));
          parcen3(NbrSol)    = ElCLib::Parameter(OnLine, pntcen(NbrSol));
        }
      }
      WellDone = true;
    }
  }
}
