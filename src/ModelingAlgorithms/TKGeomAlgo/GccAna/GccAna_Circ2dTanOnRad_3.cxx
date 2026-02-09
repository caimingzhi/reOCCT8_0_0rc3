

#include <ElCLib.hpp>
#include <GccAna_Circ2dTanOnRad.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <GccEnt_QualifiedCirc.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <Standard_NegativeValue.hpp>
#include <NCollection_Array1.hpp>

GccAna_Circ2dTanOnRad::GccAna_Circ2dTanOnRad(const GccEnt_QualifiedCirc& Qualified1,
                                             const gp_Circ2d&            OnCirc,
                                             const double                Radius,
                                             const double                Tolerance)
    : cirsol(1, 4),
      qualifier1(1, 4),
      TheSame1(1, 4),
      pnttg1sol(1, 4),
      pntcen3(1, 4),
      par1sol(1, 4),
      pararg1(1, 4),
      parcen3(1, 4)
{

  TheSame1.Init(0);
  gp_Dir2d dirx(gp_Dir2d::D::X);
  double   Tol = std::abs(Tolerance);
  int      signe[5];
  signe[0] = 0;
  signe[1] = 0;
  signe[2] = 0;
  signe[3] = 0;
  signe[4] = 0;
  double disparal[2];
  int    nparal = 0;
  int    sign   = 0;
  WellDone      = false;
  NbrSol        = 0;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsEnclosing() || Qualified1.IsOutside()
        || Qualified1.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }
  gp_Circ2d                    C1 = Qualified1.Qualified();
  NCollection_Array1<gp_Pnt2d> Center(1, 4);
  NCollection_Array1<gp_Dir2d> dir1on(1, 4);

  if (Radius < 0.0)
  {
    throw Standard_NegativeValue();
  }
  else
  {
    double   R1  = C1.Radius();
    double   R2  = OnCirc.Radius();
    double   c1x = C1.Location().X();
    double   c1y = C1.Location().Y();
    gp_Pnt2d center1(c1x, c1y);
    double   dist = OnCirc.Location().Distance(center1);
    double   onx  = OnCirc.Location().X();
    double   ony  = OnCirc.Location().Y();
    if (Qualified1.IsEnclosed())
    {

      if ((Radius - R1 > Tol) || (R1 - dist - R2 - Radius > Tol))
      {
        WellDone = true;
      }
      else
      {
        if (std::abs(Radius - R1) < Tol)
        {
          if (OnCirc.Distance(center1) < Tol)
          {
            NbrSol         = 1;
            cirsol(NbrSol) = C1;

            qualifier1(NbrSol) = Qualified1.Qualifier();
            TheSame1(NbrSol)   = 1;
            pntcen3(NbrSol)    = center1;
            parcen3(NbrSol)    = ElCLib::Parameter(OnCirc, pntcen3(NbrSol));
            WellDone           = true;
          }
          else
          {
            WellDone = false;
          }
        }
        else if (std::abs(R1 - dist - R2 - Radius) <= Tol)
        {
          dir1on(1) = gp_Dir2d(c1x - onx, c1y - ony);
          sign      = -1;
        }
        else
        {
          nparal      = 1;
          disparal[0] = std::abs(R1 - Radius);
        }
      }
    }
    else if (Qualified1.IsEnclosing())
    {

      if ((Tol < R1 - Radius) || (Tol < R1 + dist - R2 - Radius) || (Radius - R1 - dist - R2 > Tol))
      {
        WellDone = true;
      }
      else
      {
        if (std::abs(Radius - R1) < Tol)
        {
          if (OnCirc.Distance(center1) < Tol)
          {
            NbrSol         = 1;
            cirsol(NbrSol) = C1;

            qualifier1(NbrSol) = Qualified1.Qualifier();
            TheSame1(NbrSol)   = 1;
            pntcen3(NbrSol)    = center1;
            parcen3(NbrSol)    = ElCLib::Parameter(OnCirc, pntcen3(NbrSol));
            WellDone           = true;
          }
          else
          {
            WellDone = true;
          }
        }
        else if ((std::abs(R1 + dist - R2 - Radius) < Tol)
                 || (std::abs(Radius - R1 - dist - R2) < Tol))
        {
          dir1on(1) = gp_Dir2d(c1x - onx, c1y - ony);
          if (std::abs(R1 + dist - R2 - Radius) < Tol)
          {
            sign = 1;
          }
          else
          {
            sign = -1;
          }
        }
        else
        {
          nparal      = 1;
          disparal[0] = std::abs(R1 - Radius);
        }
      }
    }
    else if (Qualified1.IsOutside())
    {

      if ((dist - R2 - R1 - Radius > Tol) || (Radius - dist - R2 + R1 > Tol))
      {
        WellDone = true;
      }
      else
      {
        dir1on(1) = gp_Dir2d(c1x - onx, c1y - ony);
        if (std::abs(R1 - dist - R2 + Radius) < Tol)
        {
          sign = -1;
        }
        else if (std::abs(dist - R1 - R2 - Radius) < Tol)
        {
          sign = 1;
        }
        else
        {
          nparal      = 1;
          disparal[0] = std::abs(R1 + Radius);
        }
      }
    }
    else
    {
      if ((dist - R2 - R1 - Radius > Tol) || (Radius - dist - R1 - R2 > Tol))
      {
        WellDone = true;
      }
      else if ((R1 - dist - R2 > Tol) && (Tol < R1 - R2 - dist - Radius))
      {
        WellDone = true;
      }
      else
      {
        dir1on(1) = gp_Dir2d(c1x - onx, c1y - ony);
        if (std::abs(dist - R1 - R2 - Radius) < Tol)
        {
          sign = 1;
        }
        else if (dist + R1 + R2 - Radius < 0.0)
        {
          sign = -1;
        }
        else if ((R1 - dist + R2 > 0.0) && (R1 - R2 - dist - Radius > 0.0))
        {
          sign = -1;
        }
        else
        {
          nparal      = 2;
          disparal[0] = std::abs(R1 + Radius);
          disparal[1] = std::abs(R1 - Radius);
        }
      }
    }
    for (int jj = 0; jj < nparal; jj++)
    {
      IntAna2d_AnaIntersection Intp(OnCirc, gp_Circ2d(gp_Ax2d(center1, dirx), disparal[jj]));
      if (Intp.IsDone())
      {
        if (!Intp.IsEmpty())
        {
          for (int i = 1; i <= Intp.NbPoints(); i++)
          {
            NbrSol++;
            Center(NbrSol) = gp_Pnt2d(Intp.Point(i).Value());
            cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center(NbrSol), dirx), Radius);

            double distcc1 = Center(NbrSol).Distance(center1);
            if (!Qualified1.IsUnqualified())
            {
              qualifier1(NbrSol) = Qualified1.Qualifier();
            }
            else if (std::abs(distcc1 + Radius - R1) < Tol)
            {
              qualifier1(NbrSol) = GccEnt_enclosed;
            }
            else if (std::abs(distcc1 - R1 - Radius) < Tol)
            {
              qualifier1(NbrSol) = GccEnt_outside;
            }
            else
            {
              qualifier1(NbrSol) = GccEnt_enclosing;
            }
            dir1on(NbrSol) = gp_Dir2d(c1x - Center(NbrSol).X(), c1y - Center(NbrSol).Y());
            if ((R1 > Radius) && (Center(NbrSol).Distance(center1) <= R1))
            {
              signe[NbrSol - 1] = -1;
            }
            else
            {
              signe[NbrSol - 1] = 1;
            }
          }
        }
        WellDone = true;
      }
    }
    if (sign != 0)
    {
      Center(1) = gp_Pnt2d(OnCirc.Location().XY() + sign * R2 * dir1on(1).XY());
      cirsol(1) = gp_Circ2d(gp_Ax2d(Center(1), dirx), Radius);

      double distcc1 = Center(1).Distance(center1);
      if (!Qualified1.IsUnqualified())
      {
        qualifier1(NbrSol) = Qualified1.Qualifier();
      }
      else if (std::abs(distcc1 + Radius - R1) < Tol)
      {
        qualifier1(NbrSol) = GccEnt_enclosed;
      }
      else if (std::abs(distcc1 - R1 - Radius) < Tol)
      {
        qualifier1(NbrSol) = GccEnt_outside;
      }
      else
      {
        qualifier1(NbrSol) = GccEnt_enclosing;
      }
      NbrSol            = 1;
      signe[NbrSol - 1] = 1;
      WellDone          = true;
    }
    int ii = 0;
    while (signe[ii] != 0)
    {
      pnttg1sol(ii + 1) = gp_Pnt2d(Center(ii + 1).XY() + signe[ii] * Radius * dir1on(ii + 1).XY());
      pntcen3(ii + 1)   = cirsol(ii + 1).Location();
      pararg1(ii + 1)   = ElCLib::Parameter(C1, pnttg1sol(ii + 1));
      par1sol(ii + 1)   = ElCLib::Parameter(cirsol(ii + 1), pnttg1sol(ii + 1));
      parcen3(ii + 1)   = ElCLib::Parameter(OnCirc, pntcen3(ii + 1));
      ii++;
    }
  }
}
