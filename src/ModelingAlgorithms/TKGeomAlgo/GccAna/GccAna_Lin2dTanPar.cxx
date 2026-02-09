

#include <ElCLib.hpp>
#include <GccAna_Lin2dTanPar.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <GccEnt_QualifiedCirc.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

GccAna_Lin2dTanPar::GccAna_Lin2dTanPar(const gp_Pnt2d& ThePoint, const gp_Lin2d& Lin1)
    : linsol(1, 1),
      qualifier1(1, 1),
      pnttg1sol(1, 1),
      par1sol(1, 1),
      pararg1(1, 1)
{

  linsol(1) = gp_Lin2d(ThePoint, Lin1.Direction());

  qualifier1(1) = GccEnt_noqualifier;
  pnttg1sol(1)  = ThePoint;
  par1sol(1)    = 0.;
  pararg1(1)    = 0.;
  NbrSol        = 1;
  WellDone      = true;
}

GccAna_Lin2dTanPar::GccAna_Lin2dTanPar(const GccEnt_QualifiedCirc& Qualified1, const gp_Lin2d& Lin1)
    : linsol(1, 2),
      qualifier1(1, 2),
      pnttg1sol(1, 2),
      par1sol(1, 2),
      pararg1(1, 2)
{

  WellDone  = false;
  int signe = 0;
  int nbsol = 0;
  NbrSol    = 0;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsEnclosing() || Qualified1.IsOutside()
        || Qualified1.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }
  gp_Circ2d C1   = Qualified1.Qualified();
  double    xdir = (Lin1.Direction()).X();
  double    ydir = (Lin1.Direction()).Y();

  if (Qualified1.IsEnclosed())
  {
    throw GccEnt_BadQualifier();
  }

  else if (Qualified1.IsEnclosing())
  {

    nbsol         = 1;
    signe         = 1;
    qualifier1(1) = GccEnt_enclosing;
  }
  else if (Qualified1.IsOutside())
  {

    nbsol         = 1;
    signe         = -1;
    qualifier1(1) = GccEnt_outside;
  }
  else
  {
    nbsol         = 2;
    signe         = -1;
    qualifier1(1) = GccEnt_outside;
    qualifier1(2) = GccEnt_enclosing;
  }
  gp_XY xy(-C1.Radius() * ydir, C1.Radius() * xdir);
  for (int j = 1; j <= nbsol; j++)
  {
    signe = -signe;
    NbrSol++;
    linsol(NbrSol) = gp_Lin2d(gp_Pnt2d((C1.Location().XY()).Added(signe * xy)),

                              Lin1.Direction());

    pnttg1sol(NbrSol) = gp_Pnt2d((C1.Location().XY()).Added(signe * xy));
    par1sol(NbrSol)   = 0.;
    pararg1(NbrSol)   = ElCLib::Parameter(C1, pnttg1sol(NbrSol));
    WellDone          = true;
  }
}

bool GccAna_Lin2dTanPar::IsDone() const
{
  return WellDone;
}

int GccAna_Lin2dTanPar::NbSolutions() const
{
  if (!WellDone)
    throw StdFail_NotDone();
  return NbrSol;
}

gp_Lin2d GccAna_Lin2dTanPar::ThisSolution(const int Index) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  else if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  return linsol(Index);
}

void GccAna_Lin2dTanPar::WhichQualifier(const int Index, GccEnt_Position& Qualif1) const
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

void GccAna_Lin2dTanPar::Tangency1(const int Index,
                                   double&   ParSol,
                                   double&   ParArg,
                                   gp_Pnt2d& Pnt) const
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
    ParSol = par1sol(Index);
    ParArg = pararg1(Index);
    Pnt    = gp_Pnt2d(pnttg1sol(Index));
  }
}
