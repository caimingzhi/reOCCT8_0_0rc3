

#include <ElCLib.hpp>
#include <GccAna_Circ2d3Tan.hpp>
#include <GccAna_CircPnt2dBisec.hpp>
#include <GccAna_Pnt2dBisec.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <GccEnt_QualifiedCirc.hpp>
#include <GccInt_BElips.hpp>
#include <GccInt_IType.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <Precision.hpp>
#include <NCollection_Array1.hpp>

GccAna_Circ2d3Tan::GccAna_Circ2d3Tan(const GccEnt_QualifiedCirc& Qualified1,
                                     const gp_Pnt2d&             Point2,
                                     const gp_Pnt2d&             Point3,
                                     const double                Tolerance)
    :

      cirsol(1, 2),
      qualifier1(1, 2),
      qualifier2(1, 2),
      qualifier3(1, 2),
      TheSame1(1, 2),
      TheSame2(1, 2),
      TheSame3(1, 2),
      pnttg1sol(1, 2),
      pnttg2sol(1, 2),
      pnttg3sol(1, 2),
      par1sol(1, 2),
      par2sol(1, 2),
      par3sol(1, 2),
      pararg1(1, 2),
      pararg2(1, 2),
      pararg3(1, 2)
{

  gp_Dir2d dirx(gp_Dir2d::D::X);
  double   Tol = std::abs(Tolerance);
  WellDone     = false;
  NbrSol       = 0;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsEnclosing() || Qualified1.IsOutside()
        || Qualified1.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }

  gp_Circ2d                  C1 = Qualified1.Qualified();
  double                     R1 = C1.Radius();
  gp_Pnt2d                   center1(C1.Location());
  NCollection_Array1<double> Radius(1, 2);

  if (Point2.IsEqual(Point3, Precision::Confusion()))
  {
    WellDone = false;
    return;
  }

  GccAna_Pnt2dBisec     Bis1(Point2, Point3);
  GccAna_CircPnt2dBisec Bis2(C1, Point2);

  if (Bis1.IsDone() && Bis2.IsDone())
  {
    int nbsolution2 = Bis2.NbSolutions();
    for (int i = 1; i <= nbsolution2; i++)
    {
      occ::handle<GccInt_Bisec> Sol2 = Bis2.ThisSolution(i);
      GccInt_IType              typ2 = Sol2->ArcType();
      gp_Lin2d                  Sol1(Bis1.ThisSolution());
      IntAna2d_AnaIntersection  Intp;
      if (typ2 == GccInt_Cir)
      {
        Intp.Perform(Sol1, Sol2->Circle());
      }
      else if (typ2 == GccInt_Lin)
      {
        Intp.Perform(Sol1, Sol2->Line());
      }
      else if (typ2 == GccInt_Hpr)
      {
        Intp.Perform(Sol1, IntAna2d_Conic(Sol2->Hyperbola()));
      }
      else if (typ2 == GccInt_Ell)
      {
        Intp.Perform(Sol1, IntAna2d_Conic(Sol2->Ellipse()));
      }

      if (Intp.IsDone())
      {
        if (!Intp.IsEmpty())
        {
          for (int j = 1; j <= Intp.NbPoints(); j++)
          {
            gp_Pnt2d Center(Intp.Point(j).Value());
            double   dist1  = Center.Distance(center1);
            double   dist2  = Center.Distance(Point2);
            double   dist3  = Center.Distance(Point3);
            int      nbsol1 = 0;

            int  nbsol3 = 0;
            bool ok     = false;
            if (Qualified1.IsEnclosed())
            {
              if (dist1 - R1 < Tolerance)
              {
                Radius(1) = std::abs(R1 - dist1);
                nbsol1    = 1;
                ok        = true;
              }
            }
            else if (Qualified1.IsOutside())
            {
              if (R1 - dist1 < Tolerance)
              {
                Radius(1) = std::abs(R1 - dist1);
                nbsol1    = 1;
                ok        = true;
              }
            }
            else if (Qualified1.IsEnclosing())
            {
              ok        = true;
              nbsol1    = 1;
              Radius(1) = R1 + dist1;
            }
            else if (Qualified1.IsUnqualified())
            {
              ok        = true;
              nbsol1    = 2;
              Radius(1) = std::abs(R1 - dist1);
              Radius(2) = R1 + dist1;
            }
            if (ok)
            {
              ok = false;
              for (int ii = 1; ii <= nbsol1; ii++)
              {

                if (std::abs(dist2 - Radius(ii)) <= Tol && std::abs(dist3 - Radius(ii)) <= Tol)
                {
                  nbsol3 = ii;
                  ok     = true;
                }
              }
            }

            if (ok)
            {

              if (NbrSol >= 2)
                break;
              NbrSol++;

              cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius(nbsol3));

              double distcc1 = Center.Distance(center1);
              if (!Qualified1.IsUnqualified())
              {
                qualifier1(NbrSol) = Qualified1.Qualifier();
              }
              else if (std::abs(distcc1 + Radius(nbsol3) - R1) < Tol)
              {
                qualifier1(NbrSol) = GccEnt_enclosed;
              }
              else if (std::abs(distcc1 - R1 - Radius(nbsol3)) < Tol)
              {
                qualifier1(NbrSol) = GccEnt_outside;
              }
              else
              {
                qualifier1(NbrSol) = GccEnt_enclosing;
              }
              qualifier2(NbrSol) = GccEnt_noqualifier;
              qualifier3(NbrSol) = GccEnt_noqualifier;
              if (Center.Distance(center1) <= Tolerance
                  && std::abs(Radius(nbsol3) - R1) <= Tolerance)
              {
                TheSame1(NbrSol) = 1;
              }
              else
              {
                TheSame1(NbrSol) = 0;
                gp_Dir2d dc(center1.XY() - Center.XY());
                if (qualifier1(NbrSol) == GccEnt_enclosed)

                  dc.Reverse();

                pnttg1sol(NbrSol) = gp_Pnt2d(Center.XY() + Radius(nbsol3) * dc.XY());
                par1sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
                pararg1(NbrSol)   = ElCLib::Parameter(C1, pnttg1sol(NbrSol));
              }

              TheSame2(NbrSol)  = 0;
              pnttg2sol(NbrSol) = Point2;
              par2sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg2sol(NbrSol));
              pararg2(NbrSol)   = 0.;
              TheSame3(NbrSol)  = 0;
              pnttg3sol(NbrSol) = Point3;
              par3sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg3sol(NbrSol));
              pararg3(NbrSol)   = 0.;
            }
          }
        }
        WellDone = true;
      }
    }
  }
}
