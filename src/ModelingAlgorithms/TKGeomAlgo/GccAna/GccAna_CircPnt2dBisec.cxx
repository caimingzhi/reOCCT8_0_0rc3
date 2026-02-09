#include <GccAna_CircPnt2dBisec.hpp>
#include <GccInt_BCirc.hpp>
#include <GccInt_BElips.hpp>
#include <GccInt_BHyper.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_BLine.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

GccAna_CircPnt2dBisec::GccAna_CircPnt2dBisec(const gp_Circ2d& Circle, const gp_Pnt2d& Point)
{
  circle      = Circle;
  point       = Point;
  myTolerance = 1.e-10;
  DefineSolutions();
}

GccAna_CircPnt2dBisec::GccAna_CircPnt2dBisec(const gp_Circ2d& Circle,
                                             const gp_Pnt2d&  Point,
                                             const double     Tolerance)
{
  circle      = Circle;
  point       = Point;
  myTolerance = 1.e-10;
  if (myTolerance < Tolerance)
    myTolerance = Tolerance;

  DefineSolutions();
}

void GccAna_CircPnt2dBisec::DefineSolutions()
{
  double dist = circle.Radius() - point.Distance(circle.Location());

  if (std::abs(dist) < myTolerance)
  {
    theposition = 0;
    NbrSol      = 1;
  }
  else if (dist > 0.0)
  {
    theposition = -1;
    NbrSol      = 1;
  }
  else
  {
    theposition = 1;
    NbrSol      = 2;
  }

  WellDone = true;
}

occ::handle<GccInt_Bisec> GccAna_CircPnt2dBisec::ThisSolution(const int Index) const
{

  if (!WellDone)
    throw StdFail_NotDone();

  if ((Index <= 0) || (Index > NbrSol))
    throw Standard_OutOfRange();

  occ::handle<GccInt_Bisec> bissol;
  double                    xpoint  = point.X();
  double                    ypoint  = point.Y();
  double                    xcencir = circle.Location().X();
  double                    ycencir = circle.Location().Y();
  double                    R1      = circle.Radius();
  double                    dist    = point.Distance(circle.Location());

  if (dist < myTolerance)
  {
    gp_Circ2d biscirpnt1(gp_Ax2d(point, gp_Dir2d(gp_Dir2d::D::X)), R1 / 2.);
    bissol = new GccInt_BCirc(biscirpnt1);
  }
  else
  {
    gp_Pnt2d center((xpoint + xcencir) / 2., (ypoint + ycencir) / 2.);
    gp_Ax2d  majax(center, gp_Dir2d(xpoint - xcencir, ypoint - ycencir));

    if (theposition == -1)
    {
      gp_Elips2d biscirpnt(majax, R1 / 2., std::sqrt(R1 * R1 - dist * dist) / 2.);
      bissol = new GccInt_BElips(biscirpnt);
    }

    else if (theposition == 0)
    {
      gp_Dir2d dirsol;
      if (circle.IsDirect())
        dirsol = gp_Dir2d(xcencir - xpoint, ycencir - ypoint);
      else
        dirsol = gp_Dir2d(xpoint - xcencir, ypoint - ycencir);
      gp_Lin2d biscirpnt(point, dirsol);
      bissol = new GccInt_BLine(biscirpnt);
    }

    else
    {

      double d1 = sqrt(dist * dist - R1 * R1) / 2.0;
      double d2 = R1 / 2.;
      if (Index == 1)
      {
        gp_Hypr2d biscirpnt1(majax, d2, d1);
        bissol = new GccInt_BHyper(biscirpnt1);
      }
      else
      {
        gp_Hypr2d biscirpnt1(majax, d2, d1);
        gp_Hypr2d biscirpnt2 = biscirpnt1.OtherBranch();
        bissol               = new GccInt_BHyper(biscirpnt2);
      }
    }
  }
  return bissol;
}

bool GccAna_CircPnt2dBisec::IsDone() const
{
  return WellDone;
}

int GccAna_CircPnt2dBisec::NbSolutions() const
{
  return NbrSol;
}
