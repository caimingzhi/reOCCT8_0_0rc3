#include <ElCLib.hpp>
#include <GccAna_Circ2d2TanRad.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <GccEnt_QualifiedLin.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <Standard_NegativeValue.hpp>
#include <NCollection_Array1.hpp>

GccAna_Circ2d2TanRad::GccAna_Circ2d2TanRad(const GccEnt_QualifiedLin& Qualified1,
                                           const gp_Pnt2d&            Point2,
                                           const double               Radius,
                                           const double               Tolerance)
    : qualifier1(1, 2),
      qualifier2(1, 2),
      TheSame1(1, 2),
      TheSame2(1, 2),
      cirsol(1, 2),
      pnttg1sol(1, 2),
      pnttg2sol(1, 2),
      par1sol(1, 2),
      par2sol(1, 2),
      pararg1(1, 2),
      pararg2(1, 2)
{

  gp_Dir2d dirx(gp_Dir2d::D::X);
  double   Tol = std::abs(Tolerance);
  NbrSol       = 0;
  WellDone     = false;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsOutside() || Qualified1.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }
  int                        nbsol  = 0;
  int                        nbcote = 0;
  NCollection_Array1<double> cote(1, 2);
  gp_Lin2d                   L1     = Qualified1.Qualified();
  double                     displ1 = L1.Distance(Point2);
  double                     xdir   = (L1.Direction()).X();
  double                     ydir   = (L1.Direction()).Y();
  double                     lxloc  = (L1.Location()).X();
  double                     lyloc  = (L1.Location()).Y();
  gp_Pnt2d                   origin1(lxloc, lyloc);
  gp_Dir2d                   normL1(-ydir, xdir);
  double                     cxloc = Point2.X();
  double                     cyloc = Point2.Y();

  if (Radius < 0.0)
  {
    throw Standard_NegativeValue();
  }

  else
  {
    if (displ1 - Radius * 2.0 > Tol)
    {
      WellDone = true;
    }
    else if (Qualified1.IsEnclosed())
    {

      if ((-ydir * (cxloc - lxloc) + xdir * (cyloc - lyloc) < 0.0))
      {
        WellDone = true;
      }
      else
      {
        if (displ1 - Radius * 2.0 > 0.0)
        {
          nbsol   = 2;
          NbrSol  = 1;
          nbcote  = 1;
          cote(1) = 1.0;
        }
        else
        {
          nbsol   = 1;
          nbcote  = 1;
          cote(1) = 1.0;
        }
      }
    }
    else if (Qualified1.IsOutside())
    {

      if ((-ydir * (cxloc - lxloc) + xdir * (cyloc - lyloc) > 0.0))
      {
        WellDone = true;
      }
      else
      {
        if (displ1 - Radius * 2.0 > 0.0)
        {
          nbsol   = 2;
          nbcote  = 1;
          cote(1) = -1.0;
        }
        else
        {
          nbsol   = 1;
          nbcote  = 1;
          cote(1) = -1.0;
        }
      }
    }
    else if (Qualified1.IsUnqualified())
    {

      if (displ1 - Radius * 2.0 > 0.0)
      {
        if ((-ydir * (cxloc - lxloc) + xdir * (cyloc - lyloc) > 0.0))
        {
          nbsol   = 2;
          nbcote  = 1;
          cote(1) = 1.0;
        }
        else if ((-ydir * (cxloc - lxloc) + xdir * (cyloc - lyloc) < 0.0))
        {
          nbsol   = 2;
          nbcote  = 1;
          cote(1) = -1.0;
        }
      }
      else
      {
        nbsol   = 1;
        nbcote  = 2;
        cote(1) = 1.0;
        cote(2) = -1.0;
      }
    }

    if (nbsol == 1)
    {
      if (displ1 < 1.e-10)
      {

        for (int jcote = 1; jcote <= nbcote; jcote++)
        {
          NbrSol++;
          gp_Pnt2d Center(cxloc - cote(jcote) * ydir * Radius, cyloc + cote(jcote) * xdir * Radius);
          cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius);

          qualifier2(NbrSol) = GccEnt_noqualifier;
          if (!Qualified1.IsUnqualified())
          {
            qualifier1(NbrSol) = Qualified1.Qualifier();
          }
          else if (cote(jcote) > 0.0)
          {
            qualifier1(NbrSol) = GccEnt_outside;
          }
          else
          {
            qualifier1(NbrSol) = GccEnt_enclosed;
          }
          TheSame1(NbrSol)  = 0;
          TheSame2(NbrSol)  = 0;
          pnttg1sol(NbrSol) = Point2;
          pnttg2sol(NbrSol) = Point2;
        }
        WellDone = true;
      }
      else
      {
        gp_Circ2d cirint(gp_Ax2d(Point2, dirx), Radius);
        for (int jcote = 1; jcote <= nbcote; jcote++)
        {
          gp_Lin2d linint(
            gp_Pnt2d(lxloc - cote(jcote) * ydir * Radius, lyloc + cote(jcote) * xdir * Radius),
            L1.Direction());
          IntAna2d_AnaIntersection Intp(linint, cirint);
          if (Intp.IsDone())
          {
            if (!Intp.IsEmpty())
            {
              for (int i = 1; i <= Intp.NbPoints() && NbrSol < 2; i++)
              {
                NbrSol++;
                gp_Pnt2d Center(Intp.Point(i).Value());
                cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius);

                gp_Dir2d dc1(origin1.XY() - Center.XY());
                qualifier2(NbrSol) = GccEnt_noqualifier;
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
                TheSame1(NbrSol) = 0;
                TheSame2(NbrSol) = 0;
                pnttg1sol(NbrSol) =
                  gp_Pnt2d(Center.XY() + cote(jcote) * Radius * gp_XY(ydir, -xdir));
                pnttg2sol(NbrSol) = Point2;
              }
            }
            WellDone = true;
          }
        }
      }
    }

    else if (nbsol == 2)
    {
      gp_Pnt2d Center(Point2.XY() + cote(1) * Radius * gp_XY(-ydir, xdir));
      WellDone  = true;
      NbrSol    = 1;
      cirsol(1) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius);

      qualifier2(1) = GccEnt_noqualifier;
      TheSame1(1)   = 0;
      TheSame2(1)   = 0;
      pnttg1sol(1)  = gp_Pnt2d(Center.XY() + cote(1) * Radius * gp_XY(ydir, -xdir));
      pnttg2sol(1)  = Point2;
    }
  }

  for (int i = 1; i <= NbrSol; i++)
  {
    par1sol(i) = ElCLib::Parameter(cirsol(i), pnttg1sol(i));
    pararg1(i) = ElCLib::Parameter(L1, pnttg1sol(i));
    par2sol(i) = ElCLib::Parameter(cirsol(i), pnttg2sol(i));
    pararg2(i) = 0.;
  }
}
