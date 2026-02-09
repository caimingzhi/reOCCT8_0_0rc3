#include <Extrema_ExtPC2d.hpp>
#include <Geom2dAPI_ProjectPointOnCurve.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

Geom2dAPI_ProjectPointOnCurve::Geom2dAPI_ProjectPointOnCurve()
    : myIndex(-1)
{
  myIsDone = false;
}

Geom2dAPI_ProjectPointOnCurve::Geom2dAPI_ProjectPointOnCurve(const gp_Pnt2d&                  P,
                                                             const occ::handle<Geom2d_Curve>& Curve)
{
  Init(P, Curve);
}

Geom2dAPI_ProjectPointOnCurve::Geom2dAPI_ProjectPointOnCurve(const gp_Pnt2d&                  P,
                                                             const occ::handle<Geom2d_Curve>& Curve,
                                                             const double                     Umin,
                                                             const double                     Usup)
{
  Init(P, Curve, Umin, Usup);
}

void Geom2dAPI_ProjectPointOnCurve::Init(const gp_Pnt2d& P, const occ::handle<Geom2d_Curve>& Curve)
{
  Init(P, Curve, Curve->FirstParameter(), Curve->LastParameter());
}

void Geom2dAPI_ProjectPointOnCurve::Init(const gp_Pnt2d&                  P,
                                         const occ::handle<Geom2d_Curve>& Curve,
                                         const double                     Umin,
                                         const double                     Usup)
{
  myC.Load(Curve, Umin, Usup);

  Extrema_ExtPC2d theExtPC2d(P, myC);

  myExtPC = theExtPC2d;

  myIsDone = myExtPC.IsDone() && (myExtPC.NbExt() > 0);

  if (myIsDone)
  {
    double Dist2, Dist2Min = myExtPC.SquareDistance(1);
    myIndex = 1;

    for (int i = 2; i <= myExtPC.NbExt(); i++)
    {
      Dist2 = myExtPC.SquareDistance(i);
      if (Dist2 < Dist2Min)
      {
        Dist2Min = Dist2;
        myIndex  = i;
      }
    }
  }
}

int Geom2dAPI_ProjectPointOnCurve::NbPoints() const
{
  if (myIsDone)
    return myExtPC.NbExt();
  else
    return 0;
}

gp_Pnt2d Geom2dAPI_ProjectPointOnCurve::Point(const int Index) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints(),
                               "Geom2dAPI_ProjectPointOnCurve::Point");
  return (myExtPC.Point(Index)).Value();
}

double Geom2dAPI_ProjectPointOnCurve::Parameter(const int Index) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints(),
                               "Geom2dAPI_ProjectPointOnCurve::Parameter");
  return (myExtPC.Point(Index)).Parameter();
}

void Geom2dAPI_ProjectPointOnCurve::Parameter(const int Index, double& U) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints(),
                               "Geom2dAPI_ProjectPointOnCurve::Parameter");
  U = (myExtPC.Point(Index)).Parameter();
}

double Geom2dAPI_ProjectPointOnCurve::Distance(const int Index) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints(),
                               "Geom2dAPI_ProjectPointOnCurve::Distance");
  return sqrt(myExtPC.SquareDistance(Index));
}

gp_Pnt2d Geom2dAPI_ProjectPointOnCurve::NearestPoint() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "Geom2dAPI_ProjectPointOnCurve:NearestPoint");

  return (myExtPC.Point(myIndex)).Value();
}

Geom2dAPI_ProjectPointOnCurve::operator int() const
{
  return NbPoints();
}

Geom2dAPI_ProjectPointOnCurve::operator gp_Pnt2d() const
{
  return NearestPoint();
}

double Geom2dAPI_ProjectPointOnCurve::LowerDistanceParameter() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "Geom2dAPI_ProjectPointOnCurve:LowerDistanceParameter");

  return (myExtPC.Point(myIndex)).Parameter();
}

double Geom2dAPI_ProjectPointOnCurve::LowerDistance() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "Geom2dAPI_ProjectPointOnCurve:LowerDistance");

  return sqrt(myExtPC.SquareDistance(myIndex));
}

Geom2dAPI_ProjectPointOnCurve::operator double() const
{
  return LowerDistance();
}
