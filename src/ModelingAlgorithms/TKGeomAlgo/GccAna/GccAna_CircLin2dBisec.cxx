#include <GccAna_CircLin2dBisec.hpp>
#include <GccInt_BLine.hpp>
#include <GccInt_BParab.hpp>
#include <gp.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_XY.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

GccAna_CircLin2dBisec::GccAna_CircLin2dBisec(const gp_Circ2d& Circle, const gp_Lin2d& Line)
    :

      circle(Circle),
      line(Line)
{

  NbrSol   = 2;
  WellDone = true;
}

occ::handle<GccInt_Bisec> GccAna_CircLin2dBisec::ThisSolution(const int Index) const
{

  if (!WellDone)
    throw StdFail_NotDone();

  if ((Index <= 0) || (Index > NbrSol))
    throw Standard_OutOfRange();

  occ::handle<GccInt_Bisec> bissol;
  double                    xdir    = line.Direction().X();
  double                    ydir    = line.Direction().Y();
  double                    xloc    = line.Location().X();
  double                    yloc    = line.Location().Y();
  double                    xcencir = circle.Location().X();
  double                    ycencir = circle.Location().Y();
  double                    R1      = circle.Radius();
  double                    dist    = line.Distance(circle.Location());
  if ((std::abs(line.Distance(circle.Location()) - circle.Radius()) <= gp::Resolution())
      && (Index == 1))
  {
    gp_Lin2d biscirlin1(circle.Location(), gp_Dir2d(-ydir, xdir));
    bissol = new GccInt_BLine(biscirlin1);
  }
  else
  {
    int signe;
    if ((-ydir * (xcencir - xloc) + xdir * (ycencir - yloc)) > 0.0)
    {
      signe = 1;
    }
    else
    {
      signe = -1;
    }
    gp_Ax2d axeparab1;

    gp_Parab2d biscirlin;
    if (dist != R1)
    {
      if (Index == 1)
      {
        axeparab1 = gp_Ax2d(gp_Pnt2d(gp_XY(xcencir + signe * ydir * (dist + R1) / 2,
                                           ycencir - signe * xdir * (dist + R1) / 2.)),
                            gp_Dir2d(-signe * ydir, signe * xdir));
        biscirlin = gp_Parab2d(axeparab1, (dist + R1) / 2.0);
      }
      else
      {
        if (dist < R1)
        {
          axeparab1 = gp_Ax2d(gp_Pnt2d(gp_XY(xcencir + signe * ydir * (dist - R1) / 2,
                                             ycencir - signe * xdir * (dist - R1) / 2.)),
                              gp_Dir2d(signe * ydir, -signe * xdir));
        }
        else
        {
          axeparab1 = gp_Ax2d(gp_Pnt2d(gp_XY(xcencir + signe * ydir * (dist - R1) / 2,
                                             ycencir - signe * xdir * (dist - R1) / 2.)),
                              gp_Dir2d(-signe * ydir, signe * xdir));
        }
        biscirlin = gp_Parab2d(axeparab1, std::abs(dist - R1) / 2.0);
      }
      bissol = new GccInt_BParab(biscirlin);
    }
    else
    {
      axeparab1 = gp_Ax2d(gp_Pnt2d(gp_XY(xcencir + signe * ydir * (dist + R1) / 2.,
                                         ycencir - signe * xdir * (dist + R1) / 2.)),
                          gp_Dir2d(signe * (-ydir), signe * xdir));
      biscirlin = gp_Parab2d(axeparab1, R1);
      bissol    = new GccInt_BParab(biscirlin);
    }
  }

  return bissol;
}

bool GccAna_CircLin2dBisec::IsDone() const
{
  return WellDone;
}

int GccAna_CircLin2dBisec::NbSolutions() const
{
  return NbrSol;
}
