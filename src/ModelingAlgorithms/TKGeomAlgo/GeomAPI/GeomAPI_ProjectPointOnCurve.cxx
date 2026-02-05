#include <Extrema_ExtPC.hpp>
#include <GeomAPI_ProjectPointOnCurve.hpp>
#include <gp_Pnt.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

//=================================================================================================

GeomAPI_ProjectPointOnCurve::GeomAPI_ProjectPointOnCurve()
    : myIsDone(false),
      myIndex(0)
{
}

//=================================================================================================

GeomAPI_ProjectPointOnCurve::GeomAPI_ProjectPointOnCurve(const gp_Pnt&                  P,
                                                         const occ::handle<Geom_Curve>& Curve)
{
  Init(P, Curve);
}

//=================================================================================================

GeomAPI_ProjectPointOnCurve::GeomAPI_ProjectPointOnCurve(const gp_Pnt&                  P,
                                                         const occ::handle<Geom_Curve>& Curve,
                                                         const double                   Umin,
                                                         const double                   Usup)
{
  Init(P, Curve, Umin, Usup);
}

//=================================================================================================

void GeomAPI_ProjectPointOnCurve::Init(const gp_Pnt& P, const occ::handle<Geom_Curve>& Curve)
{
  myC.Load(Curve);
  /*
    Extrema_ExtPC theExtPC(P, myC);
    myExtPC = theExtPC;
  */
  myExtPC.Initialize(myC, myC.FirstParameter(), myC.LastParameter());
  myExtPC.Perform(P);

  myIsDone = myExtPC.IsDone() && (myExtPC.NbExt() > 0);

  if (myIsDone)
  {

    // evaluate the lower distance and its index;

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

//=================================================================================================

void GeomAPI_ProjectPointOnCurve::Init(const gp_Pnt&                  P,
                                       const occ::handle<Geom_Curve>& Curve,
                                       const double                   Umin,
                                       const double                   Usup)
{
  myC.Load(Curve, Umin, Usup);
  /*
    Extrema_ExtPC theExtPC(P, myC);
    myExtPC = theExtPC;
  */
  myExtPC.Initialize(myC, myC.FirstParameter(), myC.LastParameter());
  myExtPC.Perform(P);

  myIsDone = myExtPC.IsDone() && (myExtPC.NbExt() > 0);

  if (myIsDone)
  {

    // evaluate the lower distance and its index;

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

// modified by NIZNHY-PKV Wed Apr  3 17:48:51 2002f
//=================================================================================================

void GeomAPI_ProjectPointOnCurve::Init(const occ::handle<Geom_Curve>& Curve,
                                       const double                   Umin,
                                       const double                   Usup)
{
  myC.Load(Curve, Umin, Usup);
  // myExtPC = Extrema_ExtPC(P, myC);
  myExtPC.Initialize(myC, Umin, Usup);
  myIsDone = false;
}

//=================================================================================================

void GeomAPI_ProjectPointOnCurve::Perform(const gp_Pnt& aP3D)
{
  myExtPC.Perform(aP3D);

  myIsDone = myExtPC.IsDone() && (myExtPC.NbExt() > 0);
  if (myIsDone)
  {
    // evaluate the lower distance and its index;
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

// modified by NIZNHY-PKV Wed Apr  3 17:48:53 2002t
//=================================================================================================

int GeomAPI_ProjectPointOnCurve::NbPoints() const
{
  if (myIsDone)
    return myExtPC.NbExt();
  else
    return 0;
}

//=================================================================================================

gp_Pnt GeomAPI_ProjectPointOnCurve::Point(const int Index) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints(),
                               "GeomAPI_ProjectPointOnCurve::Point");
  return (myExtPC.Point(Index)).Value();
}

//=================================================================================================

double GeomAPI_ProjectPointOnCurve::Parameter(const int Index) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints(),
                               "GeomAPI_ProjectPointOnCurve::Parameter");
  return (myExtPC.Point(Index)).Parameter();
}

//=================================================================================================

void GeomAPI_ProjectPointOnCurve::Parameter(const int Index, double& U) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints(),
                               "GeomAPI_ProjectPointOnCurve::Parameter");
  U = (myExtPC.Point(Index)).Parameter();
}

//=================================================================================================

double GeomAPI_ProjectPointOnCurve::Distance(const int Index) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints(),
                               "GeomAPI_ProjectPointOnCurve::Distance");
  return sqrt(myExtPC.SquareDistance(Index));
}

//=================================================================================================

gp_Pnt GeomAPI_ProjectPointOnCurve::NearestPoint() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "GeomAPI_ProjectPointOnCurve::NearestPoint");

  return (myExtPC.Point(myIndex)).Value();
}

//=================================================================================================

GeomAPI_ProjectPointOnCurve::operator int() const
{
  return NbPoints();
}

//=================================================================================================

GeomAPI_ProjectPointOnCurve::operator gp_Pnt() const
{
  return NearestPoint();
}

//=================================================================================================

double GeomAPI_ProjectPointOnCurve::LowerDistanceParameter() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "GeomAPI_ProjectPointOnCurve::LowerDistanceParameter");

  return (myExtPC.Point(myIndex)).Parameter();
}

//=================================================================================================

double GeomAPI_ProjectPointOnCurve::LowerDistance() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "GeomAPI_ProjectPointOnCurve::LowerDistance");

  return sqrt(myExtPC.SquareDistance(myIndex));
}

//=================================================================================================

GeomAPI_ProjectPointOnCurve::operator double() const
{
  return LowerDistance();
}
