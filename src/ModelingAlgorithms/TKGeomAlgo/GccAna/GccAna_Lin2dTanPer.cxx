

#include <ElCLib.hpp>
#include <GccAna_Lin2dTanPer.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <GccEnt_QualifiedCirc.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

GccAna_Lin2dTanPer::GccAna_Lin2dTanPer(const gp_Pnt2d& ThePnt, const gp_Lin2d& TheLin)
    : linsol(1, 1),
      qualifier1(1, 1),
      pnttg1sol(1, 1),
      pntint2sol(1, 1),
      par1sol(1, 1),
      par2sol(1, 1),
      pararg1(1, 1),
      pararg2(1, 1)
{

  linsol(1) = gp_Lin2d(ThePnt,
                       gp_Dir2d(-(TheLin.Direction().Y()),

                                TheLin.Direction().X()));

  pnttg1sol(1) = ThePnt;
  IntAna2d_AnaIntersection Intp(linsol(1), TheLin);
  if (Intp.IsDone())
  {
    if (!Intp.IsEmpty())
    {
      for (int i = 1; i <= Intp.NbPoints(); i++)
      {
        pntint2sol(1) = Intp.Point(i).Value();
      }
    }
  }
  par1sol(1) = ElCLib::Parameter(linsol(1), pnttg1sol(1));
  par2sol(1) = ElCLib::Parameter(linsol(1), pntint2sol(1));
  pararg1(1) = 0.;
  pararg2(1) = ElCLib::Parameter(TheLin, pntint2sol(1));
  NbrSol     = 1;
  WellDone   = true;
}

GccAna_Lin2dTanPer::GccAna_Lin2dTanPer(const gp_Pnt2d& ThePnt, const gp_Circ2d& TheCircle)
    : linsol(1, 1),
      qualifier1(1, 1),
      pnttg1sol(1, 1),
      pntint2sol(1, 1),
      par1sol(1, 1),
      par2sol(1, 1),
      pararg1(1, 1),
      pararg2(1, 1)
{

  linsol(1) = gp_Lin2d(ThePnt,

                       gp_Dir2d(TheCircle.Location().XY() - ThePnt.XY()));

  pnttg1sol(1) = ThePnt;
  IntAna2d_AnaIntersection Intp(linsol(1), TheCircle);
  if (Intp.IsDone())
  {
    if (!Intp.IsEmpty())
    {
      constexpr double maxdist = RealLast();
      for (int i = 1; i <= Intp.NbPoints(); i++)
      {
        if (Intp.Point(i).Value().Distance(ThePnt) < maxdist)
        {
          pntint2sol(1) = Intp.Point(i).Value();
        }
      }
    }
  }
  par1sol(1) = ElCLib::Parameter(linsol(1), pnttg1sol(1));
  par2sol(1) = ElCLib::Parameter(linsol(1), pntint2sol(1));
  pararg1(1) = 0.;
  pararg2(1) = ElCLib::Parameter(TheCircle, pntint2sol(1));
  NbrSol     = 1;
  WellDone   = true;
}

GccAna_Lin2dTanPer::GccAna_Lin2dTanPer(const GccEnt_QualifiedCirc& Qualified1,
                                       const gp_Lin2d&             TheLin)
    : linsol(1, 2),
      qualifier1(1, 2),
      pnttg1sol(1, 2),
      pntint2sol(1, 2),
      par1sol(1, 2),
      par2sol(1, 2),
      pararg1(1, 2),
      pararg2(1, 2)
{

  WellDone     = false;
  int nbsol    = 0;
  int signe    = 0;
  NbrSol       = 0;
  gp_Circ2d C1 = Qualified1.Qualified();

  if (Qualified1.IsEnclosed())
  {

    throw GccEnt_BadQualifier();
  }
  else if (Qualified1.IsEnclosing())
  {

    nbsol = 1;
    signe = -1;
  }
  else if (Qualified1.IsOutside())
  {

    nbsol = 1;
    signe = 1;
  }
  else
  {
    nbsol = 2;
    signe = -1;
  }
  gp_XY xy(C1.Radius() * TheLin.Direction().XY());
  for (int j = 1; j <= nbsol; j++)
  {
    signe = -signe;
    NbrSol++;
    linsol(NbrSol) = gp_Lin2d(gp_Pnt2d((C1.Location().XY()).Added(signe * xy)),

                              gp_Dir2d(-TheLin.Direction().Y(),

                                       TheLin.Direction().X()));

    pnttg1sol(NbrSol) = gp_Pnt2d((C1.Location().XY()).Added(signe * xy));
    IntAna2d_AnaIntersection Intp(linsol(NbrSol), TheLin);
    if (Intp.IsDone())
    {
      if (!Intp.IsEmpty())
      {
        for (int i = 1; i <= Intp.NbPoints(); i++)
        {
          pntint2sol(NbrSol) = Intp.Point(i).Value();
        }
      }
    }
    par1sol(NbrSol) = ElCLib::Parameter(linsol(NbrSol), pnttg1sol(NbrSol));
    par2sol(NbrSol) = ElCLib::Parameter(linsol(NbrSol), pntint2sol(NbrSol));
    pararg1(NbrSol) = ElCLib::Parameter(C1, pnttg1sol(NbrSol));
    pararg2(NbrSol) = ElCLib::Parameter(TheLin, pntint2sol(NbrSol));
    WellDone        = true;
  }
}

GccAna_Lin2dTanPer::GccAna_Lin2dTanPer(const GccEnt_QualifiedCirc& Qualified1,
                                       const gp_Circ2d&            TheCircle)
    : linsol(1, 2),
      qualifier1(1, 2),
      pnttg1sol(1, 2),
      pntint2sol(1, 2),
      par1sol(1, 2),
      par2sol(1, 2),
      pararg1(1, 2),
      pararg2(1, 2)
{

  WellDone        = false;
  NbrSol          = 0;
  int       signe = 0;
  gp_Circ2d C1    = Qualified1.Qualified();

  if (Qualified1.IsEnclosed())
  {

    throw GccEnt_BadQualifier();
  }
  else if (Qualified1.IsEnclosing())
  {

    signe         = -1;
    qualifier1(1) = GccEnt_enclosing;
  }
  else if (Qualified1.IsOutside())
  {

    signe         = 1;
    qualifier1(1) = GccEnt_outside;
  }
  else if (Qualified1.IsUnqualified())
  {

    signe         = -1;
    qualifier1(1) = GccEnt_enclosing;
    qualifier1(2) = GccEnt_outside;
  }
  for (int j = 1; j <= 2; j++)
  {
    NbrSol++;
    signe = -signe;
    gp_Dir2d D1(TheCircle.Location().XY() - C1.Location().XY());
    linsol(NbrSol) = gp_Lin2d(gp_Pnt2d((C1.Location().XY()) +

                                       signe * (D1.XY() * C1.Radius())),
                              gp_Dir2d(-D1.Y(), D1.X()));

    pnttg1sol(NbrSol) = gp_Pnt2d((C1.Location().XY()) + signe * (D1.XY() * C1.Radius()));
    IntAna2d_AnaIntersection Intp(linsol(NbrSol), TheCircle);
    if (Intp.IsDone())
    {
      if (!Intp.IsEmpty())
      {
        constexpr double maxdist = RealLast();
        for (int i = 1; i <= Intp.NbPoints(); i++)
        {
          if (Intp.Point(i).Value().Distance(pnttg1sol(NbrSol)) < maxdist)
          {
            pntint2sol(NbrSol) = Intp.Point(i).Value();
          }
        }
      }
    }
    par1sol(NbrSol) = ElCLib::Parameter(linsol(NbrSol), pnttg1sol(NbrSol));
    par2sol(NbrSol) = ElCLib::Parameter(linsol(NbrSol), pntint2sol(NbrSol));
    pararg1(NbrSol) = ElCLib::Parameter(C1, pnttg1sol(NbrSol));
    pararg2(NbrSol) = ElCLib::Parameter(TheCircle, pntint2sol(NbrSol));
    WellDone        = true;
  }
}

bool GccAna_Lin2dTanPer::IsDone() const
{
  return WellDone;
}

int GccAna_Lin2dTanPer::NbSolutions() const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  return NbrSol;
}

gp_Lin2d GccAna_Lin2dTanPer::ThisSolution(const int Index) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_RangeError();
  }
  return linsol(Index);
}

void GccAna_Lin2dTanPer::WhichQualifier(const int Index, GccEnt_Position& Qualif1) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  else
  {
    Qualif1 = qualifier1(Index);
  }
}

void GccAna_Lin2dTanPer::Tangency1(const int Index,
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

void GccAna_Lin2dTanPer::Intersection2(const int Index,
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
    ParSol = par2sol(Index);
    ParArg = pararg2(Index);
    PntSol = gp_Pnt2d(pntint2sol(Index));
  }
}
