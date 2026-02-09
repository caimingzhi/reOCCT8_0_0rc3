

#include <ElCLib.hpp>
#include <GccAna_Circ2dTanOnRad.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <Standard_NegativeValue.hpp>

GccAna_Circ2dTanOnRad::GccAna_Circ2dTanOnRad(const gp_Pnt2d&  Point1,
                                             const gp_Circ2d& OnCirc,
                                             const double     Radius,
                                             const double     Tolerance)
    : cirsol(1, 2),
      qualifier1(1, 2),
      TheSame1(1, 2),
      pnttg1sol(1, 2),
      pntcen3(1, 2),
      par1sol(1, 2),
      pararg1(1, 2),
      parcen3(1, 2)
{

  gp_Dir2d dirx(gp_Dir2d::D::X);
  double   Tol   = std::abs(Tolerance);
  WellDone       = false;
  NbrSol         = 0;
  double Roncirc = OnCirc.Radius();
  double dist1   = Point1.Distance(OnCirc.Location()) - Roncirc;
  double dist2   = Point1.Distance(OnCirc.Location()) + Roncirc;

  if (Radius < 0.0)
  {
    throw Standard_NegativeValue();
  }
  else if ((dist1 - Radius > Tol) || (Tol < Radius - dist2))
  {
    WellDone = true;
  }
  else
  {
    int signe = 0;
    if (std::abs(dist1 - Radius) < Tol)
    {
      signe = 1;
    }
    else if (std::abs(dist2 - Radius) < Tol)
    {
      signe = -1;
    }
    if (signe != 0)
    {
      gp_Ax2d axe(gp_Pnt2d(OnCirc.Location().XY()
                           - Roncirc
                               * gp_Dir2d(OnCirc.Location().X() - signe * Point1.X(),
                                          OnCirc.Location().Y() - signe * Point1.Y())
                                   .XY()),
                  dirx);
      cirsol(1) = gp_Circ2d(axe, Radius);

      qualifier1(1) = GccEnt_noqualifier;
      TheSame1(1)   = 0;
      pnttg1sol(1)  = Point1;
      pntcen3(1)    = cirsol(1).Location();
      pararg1(1)    = 0.0;
      par1sol(1)    = ElCLib::Parameter(cirsol(1), pnttg1sol(1));
      parcen3(1)    = ElCLib::Parameter(OnCirc, pntcen3(1));
      WellDone      = true;
      NbrSol        = 1;
    }
    else
    {
      IntAna2d_AnaIntersection Intp(OnCirc, gp_Circ2d(gp_Ax2d(Point1, dirx), Radius));
      if (Intp.IsDone())
      {
        if (!Intp.IsEmpty())
        {
          for (int i = 1; i <= Intp.NbPoints(); i++)
          {
            NbrSol++;
            gp_Pnt2d Center(Intp.Point(i).Value());
            cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius);

            qualifier1(1) = GccEnt_noqualifier;
            TheSame1(1)   = 0;
            pnttg1sol(1)  = Point1;
            pntcen3(1)    = cirsol(1).Location();
            par1sol(1)    = ElCLib::Parameter(cirsol(1), pnttg1sol(1));
            parcen3(1)    = ElCLib::Parameter(OnCirc, pntcen3(1));
            pararg1(1)    = 0.0;
          }
        }
        WellDone = true;
      }
    }
  }
}
