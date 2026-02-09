#include <ElCLib.hpp>
#include <GccAna_Circ2d2TanOn.hpp>
#include <GccAna_LinPnt2dBisec.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <GccEnt_QualifiedLin.hpp>
#include <GccInt_BLine.hpp>
#include <GccInt_IType.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <IntAna2d_IntPoint.hpp>

GccAna_Circ2d2TanOn::GccAna_Circ2d2TanOn(const GccEnt_QualifiedLin& Qualified1,
                                         const gp_Pnt2d&            Point2,
                                         const gp_Circ2d&           OnCirc,
                                         const double               Tolerance)
    : cirsol(1, 4),
      qualifier1(1, 4),
      qualifier2(1, 4),
      TheSame1(1, 4),
      TheSame2(1, 4),
      pnttg1sol(1, 4),
      pnttg2sol(1, 4),
      pntcen(1, 4),
      par1sol(1, 4),
      par2sol(1, 4),
      pararg1(1, 4),
      pararg2(1, 4),
      parcen3(1, 4)
{

  TheSame1.Init(0);
  TheSame2.Init(0);
  WellDone = false;
  NbrSol   = 0;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsOutside() || Qualified1.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }
  double   Tol = std::abs(Tolerance);
  gp_Dir2d dirx(gp_Dir2d::D::X);
  gp_Lin2d L1 = Qualified1.Qualified();
  gp_Pnt2d originL1(L1.Location());
  gp_Dir2d dirL1(L1.Direction());
  gp_Dir2d normL1(-dirL1.Y(), dirL1.X());

  double   Ron    = OnCirc.Radius();
  double   distpc = OnCirc.Location().Distance(Point2);
  gp_Dir2d dir(OnCirc.Location().XY() - Point2.XY());
  gp_Pnt2d pinterm(Point2.XY() + (distpc + Ron) * dir.XY());
  double   dist1 = L1.Distance(pinterm);

  if (std::abs(dist1 - distpc + Ron) <= Tol)
  {
    dir = gp_Dir2d(-dirL1.Y(), dirL1.X());
    gp_Dir2d direc(originL1.XY() - pinterm.XY());
    if (Qualified1.IsOutside())
    {
      if (direc.Dot(dir) >= 0.0)
      {
        WellDone = true;
      }
    }
    else if (Qualified1.IsEnclosed())
    {
      if (direc.Dot(dir) <= 0.0)
      {
        WellDone = true;
      }
    }
    else
    {
      WellDone = true;
    }
    if (WellDone)
    {
      NbrSol++;
      cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(pinterm, dirx), dist1);

      gp_Dir2d dc1(originL1.XY() - pinterm.XY());
      double   sign = dc1.Dot(normL1);
      if (!Qualified1.IsUnqualified())
      {
        qualifier1(NbrSol) = Qualified1.Qualifier();
      }
      else if (dc1.Dot(normL1) > 0.0)
      {
        qualifier1(NbrSol) = GccEnt_outside;
      }
      else
      {
        qualifier1(NbrSol) = GccEnt_enclosed;
      }
      qualifier2(NbrSol) = GccEnt_noqualifier;
      dc1                = gp_Dir2d(sign * gp_XY(-dirL1.Y(), dirL1.X()));
      pnttg1sol(NbrSol)  = gp_Pnt2d(pinterm.XY() + dist1 * dc1.XY());
      par1sol(NbrSol)    = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
      pararg1(NbrSol)    = ElCLib::Parameter(L1, pnttg1sol(NbrSol));
      pntcen(NbrSol)     = pinterm;
      parcen3(NbrSol)    = ElCLib::Parameter(OnCirc, pntcen(NbrSol));
      parcen3(NbrSol)    = 0.;
      pnttg2sol(NbrSol)  = Point2;
      pararg2(NbrSol)    = 0.;
      par2sol(NbrSol)    = ElCLib::Parameter(cirsol(NbrSol), pnttg2sol(NbrSol));
      return;
    }
  }

  GccAna_LinPnt2dBisec Bis(L1, Point2);
  if (Bis.IsDone())
  {
    occ::handle<GccInt_Bisec> Sol  = Bis.ThisSolution();
    GccInt_IType              type = Sol->ArcType();
    IntAna2d_AnaIntersection  Intp;
    if (type == GccInt_Lin)
    {
      Intp.Perform(Sol->Line(), OnCirc);
    }
    if (type == GccInt_Par)
    {
      Intp.Perform(OnCirc, IntAna2d_Conic(Sol->Parabola()));
    }
    if (Intp.IsDone())
    {
      if (!Intp.IsEmpty())
      {
        for (int j = 1; j <= Intp.NbPoints(); j++)
        {
          gp_Pnt2d Center(Intp.Point(j).Value());
          double   Radius = L1.Distance(Center);

          bool ok = false;
          if (Qualified1.IsEnclosed())
          {
            if ((((originL1.X() - Center.X()) * (-dirL1.Y()))
                 + ((originL1.Y() - Center.Y()) * (dirL1.X())))
                <= 0)
            {
              ok = true;
            }
          }
          else if (Qualified1.IsOutside())
          {
            if ((((originL1.X() - Center.X()) * (-dirL1.Y()))
                 + ((originL1.Y() - Center.Y()) * (dirL1.X())))
                >= 0)
            {
              ok = true;
            }
          }
          else if (Qualified1.IsUnqualified())
          {
            ok = true;
          }
          if (ok)
          {
            NbrSol++;
            cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius);

            TheSame1(NbrSol) = 0;
            TheSame2(NbrSol) = 0;
            gp_Dir2d dc1(originL1.XY() - Center.XY());
            double   sign = dc1.Dot(normL1);
            if (!Qualified1.IsUnqualified())
            {
              qualifier1(NbrSol) = Qualified1.Qualifier();
            }
            else if (dc1.Dot(normL1) > 0.0)
            {
              qualifier1(NbrSol) = GccEnt_outside;
            }
            else
            {
              qualifier1(NbrSol) = GccEnt_enclosed;
            }
            qualifier2(NbrSol) = GccEnt_noqualifier;
            dc1                = gp_Dir2d(sign * gp_XY(-dirL1.Y(), dirL1.X()));
            pnttg1sol(NbrSol)  = gp_Pnt2d(Center.XY() + dist1 * dc1.XY());
            par1sol(NbrSol)    = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
            pararg1(NbrSol)    = ElCLib::Parameter(L1, pnttg1sol(NbrSol));
            pntcen(NbrSol)     = Center;
            parcen3(NbrSol)    = ElCLib::Parameter(OnCirc, pntcen(NbrSol));
            pnttg2sol(NbrSol)  = Point2;
            pararg2(NbrSol)    = 0.;
            par2sol(NbrSol)    = ElCLib::Parameter(cirsol(NbrSol), pnttg2sol(NbrSol));
            qualifier2(NbrSol) = GccEnt_noqualifier;
          }
        }
      }
      WellDone = true;
    }
  }
}
