

#include <ElCLib.hpp>
#include <GccAna_Lin2dBisec.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <gp_XY.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

GccAna_Lin2dBisec::GccAna_Lin2dBisec(const gp_Lin2d& Lin1, const gp_Lin2d& Lin2)
    : linsol(1, 2),
      pntint1sol(1, 2),
      pntint2sol(1, 2),
      par1sol(1, 2),
      par2sol(1, 2),
      pararg1(1, 2),
      pararg2(1, 2)
{

  WellDone = false;
  NbrSol   = 0;

  IntAna2d_AnaIntersection Intp(Lin1, Lin2);
  if (Intp.IsDone())
  {

    if (Intp.ParallelElements())
    {
      if (Intp.IdenticalElements())
      {
        NbrSol         = 1;
        WellDone       = true;
        linsol(NbrSol) = gp_Lin2d(Lin1);
      }
      else
      {

        double dist  = Lin1.Distance(Lin2.Location()) / 2.0;
        double cross = gp_Vec2d(-Lin2.Direction().Y(), Lin2.Direction().X())
                         .Dot(gp_Vec2d(Lin2.Location(), Lin1.Location()));
        if (cross < 0)
          dist = -dist;
        NbrSol++;
        WellDone = true;
        linsol(NbrSol) =
          gp_Lin2d(gp_Pnt2d(Lin2.Location().XY() +

                            gp_XY(-Lin2.Direction().Y() * dist, Lin2.Direction().X() * dist)),

                   Lin2.Direction());
      }
    }

    else
    {
      if (!Intp.IsEmpty())
      {
        for (int i = 1; i <= Intp.NbPoints(); i++)
        {
          NbrSol++;
          linsol(NbrSol) = gp_Lin2d(Intp.Point(i).Value(),

                                    gp_Dir2d(Lin1.Direction().XY() + Lin2.Direction().XY()));

          NbrSol++;
          linsol(NbrSol) = gp_Lin2d(Intp.Point(i).Value(),

                                    gp_Dir2d(Lin1.Direction().XY() - Lin2.Direction().XY()));

          if (Lin1.Angle(Lin2) >= 0.)
          {
            linsol(NbrSol).Reverse();
          }
          WellDone = true;
        }
      }
    }
  }

  for (int i = 1; i <= NbrSol; i++)
  {
    pntint1sol(i) = linsol(i).Location();
    pntint2sol(i) = pntint1sol(i);
    par1sol(i)    = ElCLib::Parameter(linsol(i), pntint1sol(i));
    par2sol(i)    = ElCLib::Parameter(linsol(i), pntint2sol(i));
    pararg1(i)    = ElCLib::Parameter(Lin1, pntint1sol(i));
    pararg2(i)    = ElCLib::Parameter(Lin2, pntint2sol(i));
  }
}

bool GccAna_Lin2dBisec::IsDone() const
{
  return WellDone;
}

int GccAna_Lin2dBisec::NbSolutions() const
{
  if (!WellDone)
    throw StdFail_NotDone();
  return NbrSol;
}

gp_Lin2d GccAna_Lin2dBisec::ThisSolution(const int Index) const
{
  if (!WellDone)
    throw StdFail_NotDone();
  if (Index <= 0 || Index > NbrSol)
    throw Standard_OutOfRange();
  return linsol(Index);
}

void GccAna_Lin2dBisec::Intersection1(const int Index,
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
    PntSol = gp_Pnt2d(pntint1sol(Index));
  }
}

void GccAna_Lin2dBisec::Intersection2(const int Index,
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
