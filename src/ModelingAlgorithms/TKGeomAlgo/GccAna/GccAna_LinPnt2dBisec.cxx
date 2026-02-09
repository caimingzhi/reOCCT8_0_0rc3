#include <GccAna_LinPnt2dBisec.hpp>
#include <GccInt_BLine.hpp>
#include <GccInt_BParab.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <StdFail_NotDone.hpp>

GccAna_LinPnt2dBisec::GccAna_LinPnt2dBisec(const gp_Lin2d& Line1, const gp_Pnt2d& Point2)
{

  WellDone = false;

  double xdir = Line1.Direction().X();
  double ydir = Line1.Direction().Y();
  double xloc = Line1.Location().X();
  double yloc = Line1.Location().Y();
  double dist = Line1.Distance(Point2);

  if (dist > 1.e-10)
  {
    double xpoint2 = Point2.X();
    double ypoint2 = Point2.Y();
    if ((-ydir * (xpoint2 - xloc) + xdir * (ypoint2 - yloc)) > 0.0)
    {
      gp_Ax2d    axeparab(gp_Pnt2d(Point2.XY() - dist / 2. * gp_XY(-ydir, xdir)),
                       gp_Dir2d(-ydir, xdir));
      gp_Parab2d bislinpnt(axeparab, dist / 2.0);
      bissol = new GccInt_BParab(bislinpnt);
    }
    else
    {
      gp_Ax2d    axeparab(gp_Pnt2d(Point2.XY() + dist / 2. * gp_XY(-ydir, xdir)),
                       gp_Dir2d(ydir, -xdir));
      gp_Parab2d bislinpnt(axeparab, dist / 2.0);
      bissol = new GccInt_BParab(bislinpnt);
    }
    WellDone = true;
  }
  else
  {
    gp_Lin2d bislinpnt(Point2, gp_Dir2d(-ydir, xdir));
    bissol = new GccInt_BLine(bislinpnt);

    WellDone = true;
  }
}

bool GccAna_LinPnt2dBisec::IsDone() const
{
  return WellDone;
}

occ::handle<GccInt_Bisec> GccAna_LinPnt2dBisec::ThisSolution() const
{
  if (!WellDone)
    throw StdFail_NotDone();

  return bissol;
}
