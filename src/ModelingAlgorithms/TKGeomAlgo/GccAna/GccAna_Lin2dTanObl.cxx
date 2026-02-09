

#include <ElCLib.hpp>
#include <GccAna_Lin2dTanObl.hpp>
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

GccAna_Lin2dTanObl::GccAna_Lin2dTanObl(const gp_Pnt2d& ThePoint,
                                       const gp_Lin2d& TheLine,
                                       const double    TheAngle)
    : linsol(1, 1),
      qualifier1(1, 1),
      pnttg1sol(1, 1),
      pntint2sol(1, 1),
      par1sol(1, 1),
      par2sol(1, 1),
      pararg1(1, 1),
      pararg2(1, 1)
{

  double Cosa = TheLine.Direction().X();
  double Sina = TheLine.Direction().Y();
  linsol(1)   = gp_Lin2d(ThePoint,

                       gp_Dir2d(Cosa * std::cos(TheAngle) - Sina * std::sin(TheAngle),

                                Sina * std::cos(TheAngle) + std::sin(TheAngle) * Cosa));

  qualifier1(1) = GccEnt_noqualifier;
  pnttg1sol(1)  = ThePoint;
  IntAna2d_AnaIntersection Intp(linsol(1), TheLine);
  if (Intp.IsDone())
  {
    if (!Intp.IsEmpty())
    {
      for (int i = 1; i <= Intp.NbPoints(); i++)
      {
        pntint2sol(1) = Intp.Point(i).Value();
      }
    }
    par1sol(1) = ElCLib::Parameter(linsol(1), pnttg1sol(1));
    par2sol(1) = ElCLib::Parameter(linsol(1), pntint2sol(1));
    pararg1(1) = 0.;
    pararg2(1) = ElCLib::Parameter(TheLine, pntint2sol(1));
    NbrSol     = 1;
    WellDone   = true;
  }
  else
  {
    WellDone = false;
    NbrSol   = 0;
  }
}

GccAna_Lin2dTanObl::GccAna_Lin2dTanObl(const GccEnt_QualifiedCirc& Qualified1,
                                       const gp_Lin2d&             TheLine,
                                       const double                TheAngle)
    : linsol(1, 2),
      qualifier1(1, 2),
      pnttg1sol(1, 2),
      pntint2sol(1, 2),
      par1sol(1, 2),
      par2sol(1, 2),
      pararg1(1, 2),
      pararg2(1, 2)
{

  WellDone = false;
  NbrSol   = 0;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsEnclosing() || Qualified1.IsOutside()
        || Qualified1.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }
  double Cosa = TheLine.Direction().X();
  double Sina = TheLine.Direction().Y();
  if (Qualified1.IsEnclosed())
  {

    throw GccEnt_BadQualifier();
  }
  else
  {
    gp_Circ2d C1 = Qualified1.Qualified();
    double    R1 = C1.Radius();
    if (Qualified1.IsEnclosing())
    {

      gp_XY xy(std::cos(TheAngle) * Cosa - std::sin(TheAngle) * Sina,
               std::cos(TheAngle) * Sina + std::sin(TheAngle) * Cosa);
      pnttg1sol(1) = gp_Pnt2d(C1.Location().XY() + R1 * gp_XY(xy.Y(), -xy.X()));
      linsol(1)    = gp_Lin2d(pnttg1sol(1), gp_Dir2d(xy));

      qualifier1(1) = Qualified1.Qualifier();
      IntAna2d_AnaIntersection Intp(linsol(1), TheLine);
      NbrSol   = 1;
      WellDone = true;
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
    }
    else if (Qualified1.IsOutside())
    {

      gp_XY xy(std::cos(TheAngle) * Cosa - std::sin(TheAngle) * Sina,
               std::cos(TheAngle) * Sina + std::sin(TheAngle) * Cosa);
      pnttg1sol(1) = gp_Pnt2d(C1.Location().XY() + R1 * gp_XY(-xy.Y(), xy.X()));
      linsol(1)    = gp_Lin2d(pnttg1sol(1), gp_Dir2d(xy));

      qualifier1(1) = Qualified1.Qualifier();
      IntAna2d_AnaIntersection Intp(linsol(1), TheLine);
      WellDone = true;
      NbrSol   = 1;
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
    }
    else if (Qualified1.IsUnqualified())
    {

      gp_XY xy(std::cos(TheAngle) * Cosa - std::sin(TheAngle) * Sina,
               std::cos(TheAngle) * Sina + std::sin(TheAngle) * Cosa);
      pnttg1sol(1) = gp_Pnt2d(C1.Location().XY() + R1 * gp_XY(xy.Y(), -xy.X()));
      linsol(1)    = gp_Lin2d(pnttg1sol(1), gp_Dir2d(xy));

      qualifier1(1) = GccEnt_enclosing;
      IntAna2d_AnaIntersection Intp(linsol(1), TheLine);
      WellDone = true;
      NbrSol   = 1;
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
      pnttg1sol(2) = gp_Pnt2d(C1.Location().XY() + R1 * gp_XY(-xy.Y(), xy.X()));
      linsol(2)    = gp_Lin2d(pnttg1sol(2), gp_Dir2d(xy));

      qualifier1(2) = GccEnt_outside;
      Intp          = IntAna2d_AnaIntersection(linsol(1), TheLine);
      NbrSol++;
      WellDone = true;
      if (Intp.IsDone())
      {
        if (!Intp.IsEmpty())
        {
          for (int i = 1; i <= Intp.NbPoints(); i++)
          {
            pntint2sol(2) = Intp.Point(i).Value();
          }
        }
      }
    }
    for (int index = 1; index <= NbrSol; index++)
    {
      par1sol(index) = ElCLib::Parameter(linsol(index), pnttg1sol(index));
      pararg1(index) = ElCLib::Parameter(C1, pnttg1sol(index));
      par2sol(index) = ElCLib::Parameter(linsol(index), pntint2sol(index));
      pararg2(index) = ElCLib::Parameter(TheLine, pntint2sol(index));
    }
  }
}

bool GccAna_Lin2dTanObl::IsDone() const
{
  return WellDone;
}

int GccAna_Lin2dTanObl::NbSolutions() const
{
  if (!WellDone)
    throw StdFail_NotDone();
  return NbrSol;
}

gp_Lin2d GccAna_Lin2dTanObl::ThisSolution(const int Index) const
{
  if (!WellDone)
    throw StdFail_NotDone();
  if (Index <= 0 || Index > NbrSol)
    throw Standard_OutOfRange();

  return linsol(Index);
}

void GccAna_Lin2dTanObl::WhichQualifier(const int Index, GccEnt_Position& Qualif1) const
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

void GccAna_Lin2dTanObl::Tangency1(const int Index,
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
    ParSol = par1sol(Index);
    ParArg = pararg1(Index);
    PntSol = gp_Pnt2d(pnttg1sol(Index));
  }
}

void GccAna_Lin2dTanObl::Intersection2(const int Index,
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
