#include <Extrema_ExtSS.hpp>
#include <Extrema_POnSurf.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomAPI_ExtremaSurfaceSurface.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

//=================================================================================================

GeomAPI_ExtremaSurfaceSurface::GeomAPI_ExtremaSurfaceSurface()
    : myIsDone(false),
      myIndex(0)
{
}

//=================================================================================================

GeomAPI_ExtremaSurfaceSurface::GeomAPI_ExtremaSurfaceSurface(const occ::handle<Geom_Surface>& S1,
                                                             const occ::handle<Geom_Surface>& S2)
{
  Init(S1, S2);
}

//=================================================================================================

GeomAPI_ExtremaSurfaceSurface::GeomAPI_ExtremaSurfaceSurface(const occ::handle<Geom_Surface>& S1,
                                                             const occ::handle<Geom_Surface>& S2,
                                                             const double                     U1min,
                                                             const double                     U1max,
                                                             const double                     V1min,
                                                             const double                     V1max,
                                                             const double                     U2min,
                                                             const double                     U2max,
                                                             const double                     V2min,
                                                             const double                     V2max)
{
  Init(S1, S2, U1min, U1max, V1min, V1max, U2min, U2max, V2min, V2max);
}

//=================================================================================================

void GeomAPI_ExtremaSurfaceSurface::Init(const occ::handle<Geom_Surface>& S1,
                                         const occ::handle<Geom_Surface>& S2)
{
  GeomAdaptor_Surface TheSurface1(S1);
  GeomAdaptor_Surface TheSurface2(S2);

  constexpr double Tol = Precision::PConfusion();

  Extrema_ExtSS theExtSS(TheSurface1, TheSurface2, Tol, Tol);
  myExtSS = theExtSS;

  myIsDone = myExtSS.IsDone() && (myExtSS.NbExt() > 0);

  if (myIsDone)
  {

    // evaluate the lower distance and its index;

    double Dist2, Dist2Min = myExtSS.SquareDistance(1);
    myIndex = 1;

    for (int i = 2; i <= myExtSS.NbExt(); i++)
    {
      Dist2 = myExtSS.SquareDistance(i);
      if (Dist2 < Dist2Min)
      {
        Dist2Min = Dist2;
        myIndex  = i;
      }
    }
  }
}

//=================================================================================================

void GeomAPI_ExtremaSurfaceSurface::Init(const occ::handle<Geom_Surface>& S1,
                                         const occ::handle<Geom_Surface>& S2,
                                         const double                     U1min,
                                         const double                     U1max,
                                         const double                     V1min,
                                         const double                     V1max,
                                         const double                     U2min,
                                         const double                     U2max,
                                         const double                     V2min,
                                         const double                     V2max)
{
  GeomAdaptor_Surface TheSurface1(S1, U1min, U1max, V1min, V1max);
  GeomAdaptor_Surface TheSurface2(S2, U2min, U2max, V2min, V2max);

  constexpr double Tol = Precision::PConfusion();
  Extrema_ExtSS    theExtSS(TheSurface1,
                         TheSurface2,
                         U1min,
                         U1max,
                         V1min,
                         V1max,
                         U2min,
                         U2max,
                         V2min,
                         V2max,
                         Tol,
                         Tol);

  myExtSS  = theExtSS;
  myIsDone = myExtSS.IsDone() && (myExtSS.NbExt() > 0);

  if (myIsDone)
  {

    // evaluate the lower distance and its index;

    double Dist2, Dist2Min = myExtSS.SquareDistance(1);
    myIndex = 1;

    for (int i = 2; i <= myExtSS.NbExt(); i++)
    {
      Dist2 = myExtSS.SquareDistance(i);
      if (Dist2 < Dist2Min)
      {
        Dist2Min = Dist2;
        myIndex  = i;
      }
    }
  }
}

//=================================================================================================

int GeomAPI_ExtremaSurfaceSurface::NbExtrema() const
{
  if (myIsDone)
    return myExtSS.NbExt();
  else
    return 0;
}

//=================================================================================================

void GeomAPI_ExtremaSurfaceSurface::Points(const int Index, gp_Pnt& P1, gp_Pnt& P2) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbExtrema(),
                               "GeomAPI_ExtremaCurveCurve::Points");

  Extrema_POnSurf PS1, PS2;
  myExtSS.Points(Index, PS1, PS2);

  P1 = PS1.Value();
  P2 = PS2.Value();
}

//=================================================================================================

void GeomAPI_ExtremaSurfaceSurface::Parameters(const int Index,
                                               double&   U1,
                                               double&   V1,
                                               double&   U2,
                                               double&   V2) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbExtrema(),
                               "GeomAPI_ExtremaCurveCurve::Parameters");

  Extrema_POnSurf PS1, PS2;
  myExtSS.Points(Index, PS1, PS2);

  PS1.Parameter(U1, V1);
  PS2.Parameter(U2, V2);
}

//=================================================================================================

double GeomAPI_ExtremaSurfaceSurface::Distance(const int Index) const
{
  Standard_OutOfRange_Raise_if(Index < 1 || Index > NbExtrema(),
                               "GeomAPI_ExtremaCurveCurve::Distance");

  return sqrt(myExtSS.SquareDistance(Index));
}

//=================================================================================================

void GeomAPI_ExtremaSurfaceSurface::NearestPoints(gp_Pnt& P1, gp_Pnt& P2) const
{
  StdFail_NotDone_Raise_if(!myIsDone, "GeomAPI_ExtremaSurfaceSurface::NearestPoints");

  Points(myIndex, P1, P2);
}

//=================================================================================================

void GeomAPI_ExtremaSurfaceSurface::LowerDistanceParameters(double& U1,
                                                            double& V1,
                                                            double& U2,
                                                            double& V2) const
{
  StdFail_NotDone_Raise_if(!myIsDone, "GeomAPI_ExtremaSurfaceSurface::LowerDistanceParameters");

  Parameters(myIndex, U1, V1, U2, V2);
}

//=================================================================================================

double GeomAPI_ExtremaSurfaceSurface::LowerDistance() const
{
  StdFail_NotDone_Raise_if(!myIsDone, "GeomAPI_ExtremaSurfaceSurface::LowerDistance");

  return sqrt(myExtSS.SquareDistance(myIndex));
}

//=================================================================================================

GeomAPI_ExtremaSurfaceSurface::operator double() const
{
  return LowerDistance();
}

//=================================================================================================

GeomAPI_ExtremaSurfaceSurface::operator int() const
{
  return NbExtrema();
}
