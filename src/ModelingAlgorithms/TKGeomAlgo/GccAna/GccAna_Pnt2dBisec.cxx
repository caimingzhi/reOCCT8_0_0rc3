#include <GccAna_NoSolution.hpp>
#include <GccAna_Pnt2dBisec.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <StdFail_NotDone.hpp>

GccAna_Pnt2dBisec::GccAna_Pnt2dBisec(const gp_Pnt2d& Point1, const gp_Pnt2d& Point2)
{

  WellDone = false;

  if (Point1.Distance(Point2) > 1.e-10)
  {
    gp_Dir2d dir1(Point2.XY() - Point1.XY());
    linsol = gp_Lin2d(gp_Pnt2d((Point2.X() + Point1.X()) / 2.,

                               (Point2.Y() + Point1.Y()) / 2.),

                      gp_Dir2d(-dir1.Y(), dir1.X()));

    HasSol   = true;
    WellDone = true;
  }
  else
  {
    HasSol   = false;
    WellDone = true;
  }
}

bool GccAna_Pnt2dBisec::IsDone() const
{
  return WellDone;
}

bool GccAna_Pnt2dBisec::HasSolution() const
{
  return HasSol;
}

gp_Lin2d GccAna_Pnt2dBisec::ThisSolution() const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  else if (!HasSol)
  {
    throw GccAna_NoSolution();
  }
  return linsol;
}
