#include <ElCLib.hpp>
#include <GccAna_Circ2d2TanOn.hpp>
#include <GccAna_CircPnt2dBisec.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <GccEnt_QualifiedCirc.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <Precision.hpp>
#include <NCollection_Array1.hpp>

GccAna_Circ2d2TanOn::GccAna_Circ2d2TanOn(const GccEnt_QualifiedCirc& Qualified1,
                                         const gp_Pnt2d&             Point2,
                                         const gp_Circ2d&            OnCirc,
                                         const double                Tolerance)
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
  if (!(Qualified1.IsEnclosed() || Qualified1.IsEnclosing() || Qualified1.IsOutside()
        || Qualified1.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }
  double                     Tol = std::abs(Tolerance);
  NCollection_Array1<double> Radius(1, 2);
  gp_Dir2d                   dirx(gp_Dir2d::D::X);
  gp_Circ2d                  C1 = Qualified1.Qualified();
  double                     R1 = C1.Radius();
  gp_Pnt2d                   center1(C1.Location());

  //=========================================================================
  //   Processing of boundary cases.                                          +
  //=========================================================================

  int nbsol1 = 1;
  //  int nbsol2 = 0;
  double   Ron     = OnCirc.Radius();
  double   distcco = OnCirc.Location().Distance(center1);
  gp_Pnt2d pinterm;
  gp_Dir2d dircc;
  bool     SameCenter(false);
  if (!OnCirc.Location().IsEqual(center1, Precision::Confusion()))
  {
    dircc          = gp_Dir2d(OnCirc.Location().XY() - center1.XY());
    pinterm        = gp_Pnt2d(center1.XY() + (distcco - Ron) * dircc.XY());
    double distcc2 = pinterm.Distance(Point2);
    double distcc1 = pinterm.Distance(center1);
    double d1      = std::abs(distcc2 - std::abs(distcc1 - R1));
    double d2      = std::abs(distcc2 - (distcc1 + R1));
    if (d1 > Tol || d2 > Tol)
    {
      if (!SameCenter)
        pinterm = gp_Pnt2d(center1.XY() + (distcco + Ron) * dircc.XY());
      distcc2 = pinterm.Distance(Point2);
      distcc1 = pinterm.Distance(center1);
      d1      = std::abs(distcc2 - std::abs(distcc1 - R1));
      d2      = std::abs(distcc2 - (distcc1 + R1));
      if (d1 > Tol || d2 > Tol)
      {
        nbsol1 = 0;
      }
    }
    if (nbsol1 > 0)
    {
      if (Qualified1.IsEnclosed() || Qualified1.IsOutside())
      {
        nbsol1    = 1;
        Radius(1) = std::abs(distcc1 - R1);
      }
      else if (Qualified1.IsEnclosing())
      {
        nbsol1    = 1;
        Radius(1) = R1 + distcc1;
      }
      else if (Qualified1.IsUnqualified())
      {
        nbsol1    = 2;
        Radius(1) = std::abs(distcc1 - R1);
        Radius(2) = R1 + distcc1;
      }
      for (int i = 1; i <= nbsol1; i++)
      {
        WellDone = true;
        if (i != 1 || !SameCenter)
        {
          NbrSol++;
          cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(pinterm, dirx), Radius(i));
          //    ===========================================================
          gp_Dir2d dc1;
          if (!SameCenter)
            dc1 = gp_Dir2d(center1.XY() - pinterm.XY());
          if (!Qualified1.IsUnqualified())
          {
            qualifier1(NbrSol) = Qualified1.Qualifier();
          }
          else if (std::abs(distcc1 + Radius(i) - R1) < Tol)
          {
            qualifier1(NbrSol) = GccEnt_enclosed;
          }
          else if (std::abs(distcc1 - R1 - Radius(i)) < Tol)
          {
            qualifier1(NbrSol) = GccEnt_outside;
          }
          else
          {
            qualifier1(NbrSol) = GccEnt_enclosing;
          }
          qualifier2(NbrSol) = GccEnt_noqualifier;
          if (!SameCenter)
            pnttg1sol(NbrSol) = gp_Pnt2d(pinterm.XY() + Radius(i) * dc1.XY());
          else
            pnttg1sol(NbrSol) = gp_Pnt2d(pinterm.XY());
          pnttg2sol(NbrSol) = Point2;
          pntcen(NbrSol)    = cirsol(NbrSol).Location();
          par1sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
          pararg1(NbrSol)   = ElCLib::Parameter(C1, pnttg1sol(NbrSol));
          par2sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg2sol(NbrSol));
          pararg2(NbrSol)   = 0.;
          parcen3(NbrSol)   = ElCLib::Parameter(OnCirc, pntcen(NbrSol));
        }
      }
      if (WellDone)
      {
        return;
      }
    }
  }

  //=========================================================================
  //   General case.                                                         +
  //=========================================================================

  GccAna_CircPnt2dBisec Bis(C1, Point2);
  if (Bis.IsDone())
  {
    int nbsolution = Bis.NbSolutions();
    for (int i = 1; i <= nbsolution; i++)
    {

      occ::handle<GccInt_Bisec> Sol  = Bis.ThisSolution(i);
      GccInt_IType              type = Sol->ArcType();
      IntAna2d_AnaIntersection  Intp;
      if (type == GccInt_Lin)
      {
        Intp.Perform(Sol->Line(), OnCirc);
      }
      else if (type == GccInt_Cir)
      {
        Intp.Perform(OnCirc, Sol->Circle());
      }
      else if (type == GccInt_Hpr)
      {
        Intp.Perform(OnCirc, IntAna2d_Conic(Sol->Hyperbola()));
      }
      else if (type == GccInt_Ell)
      {
        Intp.Perform(OnCirc, IntAna2d_Conic(Sol->Ellipse()));
      }
      if (Intp.IsDone())
      {
        if ((!Intp.IsEmpty()) && (!Intp.ParallelElements()) && (!Intp.IdenticalElements()))
        {
          for (int j = 1; j <= Intp.NbPoints(); j++)
          {
            gp_Pnt2d Center(Intp.Point(j).Value());
            double   dist1 = center1.Distance(Center);
            int      nbsol = 1;
            bool     ok    = false;
            if (Qualified1.IsEnclosed())
            {
              if (dist1 - C1.Radius() <= Tol)
              {
                ok        = true;
                Radius(1) = std::abs(C1.Radius() - dist1);
              }
            }
            else if (Qualified1.IsOutside())
            {
              if (C1.Radius() - dist1 <= Tol)
              {
                ok        = true;
                Radius(1) = std::abs(C1.Radius() - dist1);
              }
            }
            else if (Qualified1.IsEnclosing())
            {
              ok        = true;
              Radius(1) = C1.Radius() + dist1;
            }
            else if (Qualified1.IsUnqualified())
            {
              ok        = true;
              nbsol     = 2;
              Radius(1) = std::abs(C1.Radius() - dist1);
              Radius(2) = C1.Radius() + dist1;
            }
            if (ok)
            {
              for (int k = 1; k <= nbsol; k++)
              {

                // pop : protection against case center1 == Center
                if (center1.IsEqual(Center, Precision::Confusion()))
                {
                  continue;
                }
                if (OnCirc.Distance(Center) > Tol)
                {
                  continue;
                }
                if (NbrSol == 4)
                  break;
                NbrSol++;
                cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius(k));
                //              ==========================================================
                double distcc1 = Center.Distance(center1);
                if (!Qualified1.IsUnqualified())
                {
                  qualifier1(NbrSol) = Qualified1.Qualifier();
                }
                else if (std::abs(distcc1 + Radius(k) - R1) < Tol)
                {
                  qualifier1(NbrSol) = GccEnt_enclosed;
                }
                else if (std::abs(distcc1 - R1 - Radius(k)) < Tol)
                {
                  qualifier1(NbrSol) = GccEnt_outside;
                }
                else
                {
                  qualifier1(NbrSol) = GccEnt_enclosing;
                }
                qualifier2(NbrSol) = GccEnt_noqualifier;
                if (distcc1 <= Tol && std::abs(Radius(k) - C1.Radius()) <= Tol)
                {
                  TheSame1(NbrSol) = 1;
                }
                else
                {
                  TheSame1(NbrSol) = 0;
                  gp_Dir2d dc1(center1.XY() - Center.XY());
                  pnttg1sol(NbrSol) = gp_Pnt2d(Center.XY() + Radius(k) * dc1.XY());
                  par1sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
                  pararg1(NbrSol)   = ElCLib::Parameter(C1, pnttg1sol(NbrSol));
                }
                TheSame2(NbrSol)  = 0;
                pntcen(NbrSol)    = Center;
                pnttg2sol(NbrSol) = Point2;
                pararg2(NbrSol)   = 0.;
                par2sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg2sol(NbrSol));
                parcen3(NbrSol)   = ElCLib::Parameter(OnCirc, pntcen(NbrSol));
              }
            }
          }
        }
        WellDone = true;
      }
    }
  }
}
