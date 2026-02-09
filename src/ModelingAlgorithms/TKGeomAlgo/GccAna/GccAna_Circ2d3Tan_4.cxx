

#include <ElCLib.hpp>
#include <GccAna_Circ2d3Tan.hpp>
#include <GccAna_Circ2dBisec.hpp>
#include <GccAna_CircPnt2dBisec.hpp>
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
#include <NCollection_Array1.hpp>

static int MaxSol = 20;

GccAna_Circ2d3Tan::GccAna_Circ2d3Tan(const GccEnt_QualifiedCirc& Qualified1,
                                     const GccEnt_QualifiedCirc& Qualified2,
                                     const gp_Pnt2d&             Point3,
                                     const double                Tolerance)
    :

      cirsol(1, MaxSol),
      qualifier1(1, MaxSol),
      qualifier2(1, MaxSol),
      qualifier3(1, MaxSol),
      TheSame1(1, MaxSol),
      TheSame2(1, MaxSol),
      TheSame3(1, MaxSol),
      pnttg1sol(1, MaxSol),
      pnttg2sol(1, MaxSol),
      pnttg3sol(1, MaxSol),
      par1sol(1, MaxSol),
      par2sol(1, MaxSol),
      par3sol(1, MaxSol),
      pararg1(1, MaxSol),
      pararg2(1, MaxSol),
      pararg3(1, MaxSol)
{

  gp_Dir2d dirx(gp_Dir2d::D::X);
  double   Tol = std::abs(Tolerance);
  WellDone     = false;
  NbrSol       = 0;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsEnclosing() || Qualified1.IsOutside()
        || Qualified1.IsUnqualified())
      || !(Qualified2.IsEnclosed() || Qualified2.IsEnclosing() || Qualified2.IsOutside()
           || Qualified2.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }

  gp_Circ2d C1(Qualified1.Qualified());
  gp_Circ2d C2(Qualified2.Qualified());
  double    R1 = C1.Radius();
  double    R2 = C2.Radius();
  gp_Pnt2d  center1(C1.Location());
  gp_Pnt2d  center2(C2.Location());

  NCollection_Array1<double> Radius(1, 2);
  GccAna_Circ2dBisec         Bis1(C1, C2);
  GccAna_CircPnt2dBisec      Bis2(C1, Point3);
  if (Bis1.IsDone() && Bis2.IsDone())
  {
    int nbsolution1 = Bis1.NbSolutions();
    int nbsolution2 = Bis2.NbSolutions();
    for (int i = 1; i <= nbsolution1; i++)
    {
      occ::handle<GccInt_Bisec> Sol1 = Bis1.ThisSolution(i);
      GccInt_IType              typ1 = Sol1->ArcType();
      IntAna2d_AnaIntersection  Intp;
      for (int k = 1; k <= nbsolution2; k++)
      {
        occ::handle<GccInt_Bisec> Sol2 = Bis2.ThisSolution(k);
        GccInt_IType              typ2 = Sol2->ArcType();
        if (typ1 == GccInt_Cir)
        {
          if (typ2 == GccInt_Cir)
          {
            Intp.Perform(Sol1->Circle(), Sol2->Circle());
          }
          else if (typ2 == GccInt_Lin)
          {
            Intp.Perform(Sol2->Line(), Sol1->Circle());
          }
          else if (typ2 == GccInt_Hpr)
          {
            Intp.Perform(Sol1->Circle(), IntAna2d_Conic(Sol2->Hyperbola()));
          }
          else if (typ2 == GccInt_Ell)
          {
            Intp.Perform(Sol1->Circle(), IntAna2d_Conic(Sol2->Ellipse()));
          }
        }
        else if (typ1 == GccInt_Ell)
        {
          if (typ2 == GccInt_Cir)
          {
            Intp.Perform(Sol2->Circle(), IntAna2d_Conic(Sol1->Ellipse()));
          }
          else if (typ2 == GccInt_Lin)
          {
            Intp.Perform(Sol2->Line(), IntAna2d_Conic(Sol1->Ellipse()));
          }
          else if (typ2 == GccInt_Hpr)
          {
            Intp.Perform(Sol1->Ellipse(), IntAna2d_Conic(Sol2->Hyperbola()));
          }
          else if (typ2 == GccInt_Ell)
          {
            Intp.Perform(Sol1->Ellipse(), IntAna2d_Conic(Sol2->Ellipse()));
          }
        }
        else if (typ1 == GccInt_Lin)
        {
          if (typ2 == GccInt_Cir)
          {
            Intp.Perform(Sol1->Line(), Sol2->Circle());
          }
          else if (typ2 == GccInt_Lin)
          {
            Intp.Perform(Sol1->Line(), Sol2->Line());
          }
          else if (typ2 == GccInt_Hpr)
          {
            Intp.Perform(Sol1->Line(), IntAna2d_Conic(Sol2->Hyperbola()));
          }
          else if (typ2 == GccInt_Ell)
          {
            Intp.Perform(Sol1->Line(), IntAna2d_Conic(Sol2->Ellipse()));
          }
        }
        else if (typ1 == GccInt_Hpr)
        {
          if (typ2 == GccInt_Cir)
          {
            Intp.Perform(Sol2->Circle(), IntAna2d_Conic(Sol1->Hyperbola()));
          }
          else if (typ2 == GccInt_Lin)
          {
            Intp.Perform(Sol2->Line(), IntAna2d_Conic(Sol1->Hyperbola()));
          }
          else if (typ2 == GccInt_Hpr)
          {
            Intp.Perform(Sol2->Hyperbola(), IntAna2d_Conic(Sol1->Hyperbola()));
          }
          else if (typ2 == GccInt_Ell)
          {
            Intp.Perform(Sol2->Ellipse(), IntAna2d_Conic(Sol1->Hyperbola()));
          }
        }
        if (Intp.IsDone())
        {
          if (!Intp.IsEmpty())
          {
            for (int j = 1; j <= Intp.NbPoints(); j++)
            {
              double   Rradius = 0;
              gp_Pnt2d Center(Intp.Point(j).Value());
              double   dist1  = Center.Distance(center1);
              double   dist2  = Center.Distance(center2);
              double   dist3  = Center.Distance(Point3);
              int      nbsol1 = 0;
              int      nbsol2 = 0;
              int      nbsol3 = 0;
              bool     ok     = false;
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
              if (Qualified2.IsEnclosed() && ok)
              {
                if (dist2 - R2 < Tolerance)
                {
                  for (int ii = 1; ii <= nbsol1; ii++)
                  {
                    if (std::abs(Radius(ii) - std::abs(R2 - dist2)) < Tol)
                    {
                      Radius(1) = std::abs(R2 - dist2);
                      ok        = true;
                      nbsol2    = 1;
                    }
                  }
                }
              }
              else if (Qualified2.IsOutside() && ok)
              {
                if (R2 - dist2 < Tolerance)
                {
                  for (int ii = 1; ii <= nbsol1; ii++)
                  {
                    if (std::abs(Radius(ii) - std::abs(R2 - dist2)) < Tol)
                    {
                      Radius(1) = std::abs(R2 - dist2);
                      ok        = true;
                      nbsol2    = 1;
                    }
                  }
                }
              }
              else if (Qualified2.IsEnclosing() && ok)
              {
                for (int ii = 1; ii <= nbsol1; ii++)
                {
                  if (std::abs(Radius(ii) - R2 - dist2) < Tol)
                  {
                    Radius(1) = R2 + dist2;
                    ok        = true;
                    nbsol2    = 1;
                  }
                }
              }
              else if (Qualified2.IsUnqualified() && ok)
              {
                for (int ii = 1; ii <= nbsol1; ii++)
                {
                  if (std::abs(Radius(ii) - std::abs(R2 - dist2)) < Tol)
                  {
                    Rradius = std::abs(R2 - dist2);
                    ok      = true;
                    nbsol2++;
                  }
                  else if (std::abs(Radius(ii) - R2 - dist2) < Tol)
                  {
                    Rradius = R2 + dist2;
                    ok      = true;
                    nbsol2++;
                  }
                }
                if (nbsol2 == 1)
                {
                  Radius(1) = Rradius;
                }
                else if (nbsol2 == 2)
                {
                  Radius(1) = std::abs(R2 - dist2);
                  Radius(2) = R2 + dist2;
                }
              }
              for (int ii = 1; ii <= nbsol2; ii++)
              {
                if (std::abs(dist3 - Radius(ii)) <= Tol)
                {
                  nbsol3++;
                  ok = true;
                }
              }
              if (ok)
              {
                for (int k1 = 1; k1 <= nbsol3; k1++)
                {
                  NbrSol++;
                  cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius(k1));

                  double distcc1 = Center.Distance(center1);
                  if (!Qualified1.IsUnqualified())
                  {
                    qualifier1(NbrSol) = Qualified1.Qualifier();
                  }
                  else if (std::abs(distcc1 + Radius(k1) - R1) < Tol)
                  {
                    qualifier1(NbrSol) = GccEnt_enclosed;
                  }
                  else if (std::abs(distcc1 - R1 - Radius(k1)) < Tol)
                  {
                    qualifier1(NbrSol) = GccEnt_outside;
                  }
                  else
                  {
                    qualifier1(NbrSol) = GccEnt_enclosing;
                  }

                  double distcc2 = Center.Distance(center2);
                  if (!Qualified2.IsUnqualified())
                  {
                    qualifier2(NbrSol) = Qualified2.Qualifier();
                  }
                  else if (std::abs(distcc2 + Radius(k1) - R2) < Tol)
                  {
                    qualifier2(NbrSol) = GccEnt_enclosed;
                  }
                  else if (std::abs(distcc2 - R2 - Radius(k1)) < Tol)
                  {
                    qualifier2(NbrSol) = GccEnt_outside;
                  }
                  else
                  {
                    qualifier2(NbrSol) = GccEnt_enclosing;
                  }
                  qualifier3(NbrSol) = GccEnt_noqualifier;
                  if (Center.Distance(center1) <= Tolerance
                      && std::abs(Radius(k1) - R1) <= Tolerance)
                  {
                    TheSame1(NbrSol) = 1;
                  }
                  else
                  {
                    TheSame1(NbrSol) = 0;
                    gp_Dir2d dc(center1.XY() - Center.XY());
                    if (qualifier1(NbrSol) == GccEnt_enclosed)

                      dc.Reverse();

                    pnttg1sol(NbrSol) = gp_Pnt2d(Center.XY() + Radius(k1) * dc.XY());
                    par1sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
                    pararg1(NbrSol)   = ElCLib::Parameter(C1, pnttg1sol(NbrSol));
                  }
                  if (Center.Distance(center2) <= Tolerance
                      && std::abs(Radius(k1) - R2) <= Tolerance)
                  {
                    TheSame2(NbrSol) = 1;
                  }
                  else
                  {
                    TheSame2(NbrSol) = 0;
                    gp_Dir2d dc(center2.XY() - Center.XY());

                    double alpha = 1.;
                    if (center1.Distance(center2) <= Tolerance)
                      alpha = -1;
                    pnttg2sol(NbrSol) = gp_Pnt2d(Center.XY() + alpha * Radius(k1) * dc.XY());
                    par2sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg2sol(NbrSol));
                    pararg2(NbrSol)   = ElCLib::Parameter(C2, pnttg2sol(NbrSol));
                  }
                  TheSame3(NbrSol)  = 0;
                  pnttg3sol(NbrSol) = Point3;
                  par3sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg3sol(NbrSol));
                  pararg3(NbrSol)   = 0.;
                  WellDone          = true;
                  if (NbrSol == MaxSol)
                    break;
                }
              }
            }
          }
          WellDone = true;
          if (NbrSol == MaxSol)
            break;
        }
        if (NbrSol == MaxSol)
          break;
      }
      if (NbrSol == MaxSol)
        break;
    }
  }

  int kk;
  for (kk = 1; kk <= NbrSol; kk++)
  {
    gp_Circ2d CC = cirsol(kk);
    double    NR = CC.Location().Distance(Point3);
    if (std::abs(NR - CC.Radius()) > Tol)
    {
      cirsol(kk).SetRadius(NR);
    }
  }

  double Tol2 = Tol * Tol;
  for (kk = 1; kk < NbrSol; kk++)
  {
    gp_Pnt2d PK = cirsol(kk).Location();
    for (int ll = kk + 1; ll <= NbrSol; ll++)
    {
      gp_Pnt2d PL = cirsol(ll).Location();
      if (PK.SquareDistance(PL) < Tol2)
      {
        for (int mm = ll + 1; mm <= NbrSol; mm++)
        {
          cirsol(mm - 1)     = cirsol(mm);
          pnttg1sol(mm - 1)  = pnttg1sol(mm);
          pnttg2sol(mm - 1)  = pnttg2sol(mm);
          pnttg3sol(mm - 1)  = pnttg3sol(mm);
          par1sol(mm - 1)    = par1sol(mm);
          par2sol(mm - 1)    = par2sol(mm);
          par3sol(mm - 1)    = par3sol(mm);
          pararg1(mm - 1)    = pararg1(mm);
          pararg2(mm - 1)    = pararg2(mm);
          pararg3(mm - 1)    = pararg3(mm);
          qualifier1(mm - 1) = qualifier1(mm);
          qualifier2(mm - 1) = qualifier2(mm);
          qualifier3(mm - 1) = qualifier3(mm);
        }
        NbrSol--;
      }
    }
  }
}
