

#include <ElCLib.hpp>
#include <GccAna_Circ2dTanCen.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <GccEnt_QualifiedCirc.hpp>
#include <gp.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

GccAna_Circ2dTanCen::GccAna_Circ2dTanCen(const GccEnt_QualifiedCirc& Qualified1,
                                         const gp_Pnt2d&             Pcenter,
                                         const double                Tolerance)
    :

      cirsol(1, 2),
      qualifier1(1, 2),
      TheSame1(1, 2),
      pnttg1sol(1, 2),
      par1sol(1, 2),
      pararg1(1, 2)
{

  NbrSol        = 0;
  double Radius = 0.0;
  WellDone      = false;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsEnclosing() || Qualified1.IsOutside()
        || Qualified1.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }
  gp_Dir2d  dirx(gp_Dir2d::D::X);
  double    Tol = std::abs(Tolerance);
  gp_Circ2d C1  = Qualified1.Qualified();
  double    R1  = C1.Radius();
  gp_Pnt2d  center1(C1.Location());
  double    dist;
  int       signe  = 0;
  int       signe1 = 0;

  if (!Qualified1.IsUnqualified())
  {
    dist = Pcenter.Distance(center1);
    if (Qualified1.IsEnclosed())
    {

      if (dist - R1 <= Tol)
      {
        Radius = std::abs(R1 - dist);
        signe  = 1;
      }
      else
      {
        WellDone = true;
      }
    }
    else if (Qualified1.IsEnclosing())
    {

      Radius = R1 + dist;
      signe  = -1;
    }
    else if (Qualified1.IsOutside())
    {

      if (dist < R1 - Tol)
      {
        WellDone = true;
      }
      else
      {
        Radius = std::abs(R1 - dist);
        signe  = -1;
      }
    }
    if (signe != 0)
    {
      NbrSol++;
      cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Pcenter, dirx), Radius);

      qualifier1(NbrSol) = Qualified1.Qualifier();
      if (dist <= gp::Resolution())
      {
        TheSame1(NbrSol) = 1;
      }
      else
      {
        TheSame1(NbrSol) = 0;
        gp_Dir2d d(Pcenter.X() - center1.X(), Pcenter.Y() - center1.Y());
        pnttg1sol(NbrSol) = gp_Pnt2d(Pcenter.XY() + signe * Radius * d.XY());
        par1sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
        pararg1(NbrSol)   = ElCLib::Parameter(C1, pnttg1sol(NbrSol));
      }
      WellDone = true;
    }
  }
  else
  {

    dist = Pcenter.Distance(center1);
    if (dist >= gp::Resolution())
    {
      signe = 1;
      for (int i = 1; i <= 2; i++)
      {
        signe = -signe;
        if (R1 - dist <= 0.)
        {
          signe1 = -1;
        }
        else
        {
          signe1 = -signe;
        }
        Radius = std::abs(R1 + signe * dist);
        NbrSol++;
        cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Pcenter, dirx), Radius);

        double distcc1 = Pcenter.Distance(center1);
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
        TheSame1(NbrSol) = 0;
        WellDone         = true;
        gp_Dir2d d(Pcenter.X() - center1.X(), Pcenter.Y() - center1.Y());
        pnttg1sol(NbrSol) = gp_Pnt2d(Pcenter.XY() + signe1 * Radius * d.XY());
        par1sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
        pararg1(NbrSol)   = ElCLib::Parameter(C1, pnttg1sol(NbrSol));
      }
    }
    else
    {
      NbrSol++;
      cirsol(NbrSol) = gp_Circ2d(C1);

      qualifier1(1)    = Qualified1.Qualifier();
      TheSame1(NbrSol) = 1;
      WellDone         = true;
    }
  }
}

GccAna_Circ2dTanCen::GccAna_Circ2dTanCen(const gp_Lin2d& Linetan, const gp_Pnt2d& Pcenter)
    :

      cirsol(1, 1),
      qualifier1(1, 1),
      TheSame1(1, 1),
      pnttg1sol(1, 1),
      par1sol(1, 1),
      pararg1(1, 1)
{

  gp_Dir2d dirx(gp_Dir2d::D::X);
  double   rayon = Linetan.Distance(Pcenter);
  cirsol(1)      = gp_Circ2d(gp_Ax2d(Pcenter, dirx), rayon);

  qualifier1(1) = GccEnt_noqualifier;
  TheSame1(1)   = 0;
  double xloc   = Linetan.Location().X();
  double yloc   = Linetan.Location().Y();
  double xdir   = Linetan.Direction().X();
  double ydir   = Linetan.Direction().Y();

  if (gp_Dir2d(xloc - Pcenter.X(), yloc - Pcenter.Y()).Dot(gp_Dir2d(-ydir, xdir)) > 0.0)
  {
    pnttg1sol(1) = gp_Pnt2d(Pcenter.XY() + rayon * gp_XY(-ydir, xdir));
    par1sol(1)   = ElCLib::Parameter(cirsol(1), pnttg1sol(1));
    pararg1(1)   = ElCLib::Parameter(Linetan, pnttg1sol(1));
  }
  else
  {
    pnttg1sol(1) = gp_Pnt2d(Pcenter.XY() + rayon * gp_XY(ydir, -xdir));
    par1sol(1)   = ElCLib::Parameter(cirsol(1), pnttg1sol(1));
    pararg1(1)   = ElCLib::Parameter(Linetan, pnttg1sol(1));
  }
  NbrSol   = 1;
  WellDone = true;
}

GccAna_Circ2dTanCen::GccAna_Circ2dTanCen(const gp_Pnt2d& Point1, const gp_Pnt2d& Pcenter)
    :

      cirsol(1, 1),
      qualifier1(1, 1),
      TheSame1(1, 1),
      pnttg1sol(1, 1),
      par1sol(1, 1),
      pararg1(1, 1)
{

  gp_Dir2d dirx(gp_Dir2d::D::X);
  double   rayon = Point1.Distance(Pcenter);
  cirsol(1)      = gp_Circ2d(gp_Ax2d(Pcenter, dirx), rayon);

  qualifier1(1) = GccEnt_noqualifier;
  TheSame1(1)   = 0;
  pnttg1sol(1)  = Point1;
  par1sol(1)    = ElCLib::Parameter(cirsol(1), pnttg1sol(1));
  pararg1(1)    = 0.0;
  NbrSol        = 1;
  WellDone      = true;
}

bool GccAna_Circ2dTanCen::IsDone() const
{
  return WellDone;
}

int GccAna_Circ2dTanCen::NbSolutions() const
{
  return NbrSol;
}

gp_Circ2d GccAna_Circ2dTanCen::ThisSolution(const int Index) const
{
  if (Index > NbrSol || Index <= 0)
  {
    throw Standard_OutOfRange();
  }
  return cirsol(Index);
}

void GccAna_Circ2dTanCen::WhichQualifier(const int Index, GccEnt_Position& Qualif1) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  else if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  else
  {
    Qualif1 = qualifier1(Index);
  }
}

void GccAna_Circ2dTanCen::Tangency1(const int Index,
                                    double&   ParSol,
                                    double&   ParArg,
                                    gp_Pnt2d& PntSol) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  else if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  else
  {
    if (TheSame1(Index) == 0)
    {
      PntSol = gp_Pnt2d(pnttg1sol(Index));
      ParSol = par1sol(Index);
      ParArg = pararg1(Index);
    }
    else
    {
      throw StdFail_NotDone();
    }
  }
}

bool GccAna_Circ2dTanCen::IsTheSame1(const int Index) const
{
  if (!WellDone)
    throw StdFail_NotDone();
  if (Index <= 0 || Index > NbrSol)
    throw Standard_OutOfRange();

  if (TheSame1(Index) == 0)
    return false;

  return true;
}
