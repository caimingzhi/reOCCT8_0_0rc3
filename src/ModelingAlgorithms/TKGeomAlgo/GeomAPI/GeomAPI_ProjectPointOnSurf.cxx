#include <GeomAPI_ProjectPointOnSurf.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

//=================================================================================================

GeomAPI_ProjectPointOnSurf::GeomAPI_ProjectPointOnSurf()
    : myIsDone(false),
      myIndex(0)
{
}

//=================================================================================================

GeomAPI_ProjectPointOnSurf::GeomAPI_ProjectPointOnSurf(const gp_Pnt&                    P,
                                                       const occ::handle<Geom_Surface>& Surface,
                                                       const Extrema_ExtAlgo            theProjAlgo)
{
  Init(P, Surface, theProjAlgo);
}

//=================================================================================================

GeomAPI_ProjectPointOnSurf::GeomAPI_ProjectPointOnSurf(const gp_Pnt&                    P,
                                                       const occ::handle<Geom_Surface>& Surface,
                                                       const double                     Tolerance,
                                                       const Extrema_ExtAlgo            theProjAlgo)
{
  Init(P, Surface, Tolerance, theProjAlgo);
}

//=================================================================================================

GeomAPI_ProjectPointOnSurf::GeomAPI_ProjectPointOnSurf(const gp_Pnt&                    P,
                                                       const occ::handle<Geom_Surface>& Surface,
                                                       const double                     Umin,
                                                       const double                     Usup,
                                                       const double                     Vmin,
                                                       const double                     Vsup,
                                                       const Extrema_ExtAlgo            theProjAlgo)

{
  Init(P, Surface, Umin, Usup, Vmin, Vsup, theProjAlgo);
}

//=================================================================================================

GeomAPI_ProjectPointOnSurf::GeomAPI_ProjectPointOnSurf(const gp_Pnt&                    P,
                                                       const occ::handle<Geom_Surface>& Surface,
                                                       const double                     Umin,
                                                       const double                     Usup,
                                                       const double                     Vmin,
                                                       const double                     Vsup,
                                                       const double                     Tolerance,
                                                       const Extrema_ExtAlgo            theProjAlgo)

{
  Init(P, Surface, Umin, Usup, Vmin, Vsup, Tolerance, theProjAlgo);
}

//=================================================================================================

void GeomAPI_ProjectPointOnSurf::Init()
{
  myIsDone = myExtPS.IsDone() && (myExtPS.NbExt() > 0);

  if (myIsDone)
  {
    // evaluate the lower distance and its index;
    double Dist2, Dist2Min = myExtPS.SquareDistance(1);
    myIndex = 1;

    for (int i = 2; i <= myExtPS.NbExt(); i++)
    {
      Dist2 = myExtPS.SquareDistance(i);
      if (Dist2 < Dist2Min)
      {
        Dist2Min = Dist2;
        myIndex  = i;
      }
    }
  }
}

//=================================================================================================

void GeomAPI_ProjectPointOnSurf::Init(const gp_Pnt&                    P,
                                      const occ::handle<Geom_Surface>& Surface,
                                      const Extrema_ExtAlgo            theProjAlgo)

{
  Init(P, Surface, Precision::Confusion(), theProjAlgo);
}

//=================================================================================================

void GeomAPI_ProjectPointOnSurf::Init(const gp_Pnt&                    P,
                                      const occ::handle<Geom_Surface>& Surface,
                                      const double                     Tolerance,
                                      const Extrema_ExtAlgo            theProjAlgo)

{

  // modified by NIZNHY-PKV Mon Apr  8 11:13:37 2002 f XXX
  double Umin, Usup, Vmin, Vsup;
  Surface->Bounds(Umin, Usup, Vmin, Vsup);
  myGeomAdaptor.Load(Surface, Umin, Usup, Vmin, Vsup);

  myExtPS.SetAlgo(theProjAlgo);
  myExtPS.Initialize(myGeomAdaptor, Umin, Usup, Vmin, Vsup, Tolerance, Tolerance);
  myExtPS.Perform(P);

  Init();
}

//=================================================================================================

void GeomAPI_ProjectPointOnSurf::Init(const gp_Pnt&                    P,
                                      const occ::handle<Geom_Surface>& Surface,
                                      const double                     Umin,
                                      const double                     Usup,
                                      const double                     Vmin,
                                      const double                     Vsup,
                                      const Extrema_ExtAlgo            theProjAlgo)
{
  constexpr double Tolerance = Precision::PConfusion();

  myGeomAdaptor.Load(Surface, Umin, Usup, Vmin, Vsup);

  myExtPS.SetAlgo(theProjAlgo);
  myExtPS.Initialize(myGeomAdaptor, Umin, Usup, Vmin, Vsup, Tolerance, Tolerance);
  myExtPS.Perform(P);

  Init();
}

//=================================================================================================

void GeomAPI_ProjectPointOnSurf::Init(const gp_Pnt&                    P,
                                      const occ::handle<Geom_Surface>& Surface,
                                      const double                     Umin,
                                      const double                     Usup,
                                      const double                     Vmin,
                                      const double                     Vsup,
                                      const double                     Tolerance,
                                      const Extrema_ExtAlgo            theProjAlgo)
{
  myGeomAdaptor.Load(Surface, Umin, Usup, Vmin, Vsup);

  myExtPS.SetAlgo(theProjAlgo);
  myExtPS.Initialize(myGeomAdaptor, Umin, Usup, Vmin, Vsup, Tolerance, Tolerance);
  myExtPS.Perform(P);

  Init();
}

//=================================================================================================

void GeomAPI_ProjectPointOnSurf::Init(const occ::handle<Geom_Surface>& Surface,
                                      const double                     Umin,
                                      const double                     Usup,
                                      const double                     Vmin,
                                      const double                     Vsup,
                                      const Extrema_ExtAlgo            theProjAlgo)
{
  constexpr double Tolerance = Precision::PConfusion();

  myGeomAdaptor.Load(Surface, Umin, Usup, Vmin, Vsup);

  myExtPS.SetAlgo(theProjAlgo);
  myExtPS.Initialize(myGeomAdaptor, Umin, Usup, Vmin, Vsup, Tolerance, Tolerance);

  myIsDone = false;
}

//=================================================================================================

void GeomAPI_ProjectPointOnSurf::Init(const occ::handle<Geom_Surface>& Surface,
                                      const double                     Umin,
                                      const double                     Usup,
                                      const double                     Vmin,
                                      const double                     Vsup,
                                      const double                     Tolerance,
                                      const Extrema_ExtAlgo            theProjAlgo)
{

  myGeomAdaptor.Load(Surface, Umin, Usup, Vmin, Vsup);

  myExtPS.SetAlgo(theProjAlgo);
  myExtPS.Initialize(myGeomAdaptor, Umin, Usup, Vmin, Vsup, Tolerance, Tolerance);
  myIsDone = false;
}

//=================================================================================================

void GeomAPI_ProjectPointOnSurf::Perform(const gp_Pnt& P)
{
  myExtPS.Perform(P);
  Init();
}

//=================================================================================================

bool GeomAPI_ProjectPointOnSurf::IsDone() const
{
  return myIsDone;
}

//=================================================================================================

int GeomAPI_ProjectPointOnSurf::NbPoints() const
{
  if (myIsDone)
  {
    return myExtPS.NbExt();
  }
  else
  {
    return 0;
  }
}

//=================================================================================================

gp_Pnt GeomAPI_ProjectPointOnSurf::Point(const int Index) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints(),
                               "GeomAPI_ProjectPointOnSurf::Point");
  return (myExtPS.Point(Index)).Value();
}

//=================================================================================================

void GeomAPI_ProjectPointOnSurf::Parameters(const int Index, double& U, double& V) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints(),
                               "GeomAPI_ProjectPointOnSurf::Parameter");
  (myExtPS.Point(Index)).Parameter(U, V);
}

//=================================================================================================

double GeomAPI_ProjectPointOnSurf::Distance(const int Index) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbPoints(),
                               "GeomAPI_ProjectPointOnSurf::Distance");
  return sqrt(myExtPS.SquareDistance(Index));
}

//=================================================================================================

gp_Pnt GeomAPI_ProjectPointOnSurf::NearestPoint() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "GeomAPI_ProjectPointOnSurf::NearestPoint");

  return (myExtPS.Point(myIndex)).Value();
}

//=================================================================================================

GeomAPI_ProjectPointOnSurf::operator int() const
{
  return NbPoints();
}

//=================================================================================================

GeomAPI_ProjectPointOnSurf::operator gp_Pnt() const
{
  return NearestPoint();
}

//=================================================================================================

void GeomAPI_ProjectPointOnSurf::LowerDistanceParameters(double& U, double& V) const
{
  StdFail_NotDone_Raise_if(!myIsDone, "GeomAPI_ProjectPointOnSurf::LowerDistanceParameters");

  (myExtPS.Point(myIndex)).Parameter(U, V);
}

//=================================================================================================

double GeomAPI_ProjectPointOnSurf::LowerDistance() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "GeomAPI_ProjectPointOnSurf::LowerDistance");

  return sqrt(myExtPS.SquareDistance(myIndex));
}

//=================================================================================================

GeomAPI_ProjectPointOnSurf::operator double() const
{
  return LowerDistance();
}
