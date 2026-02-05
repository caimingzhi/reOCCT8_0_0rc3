#include <GC_MakePlane.hpp>
#include <gce_MakePln.hpp>
#include <Geom_Plane.hpp>
#include <gp.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <Standard_NotImplemented.hpp>
#include <StdFail_NotDone.hpp>
#include <NCollection_Array1.hpp>

GC_MakePlane::GC_MakePlane(const gp_Pln& Pl)
{
  TheError = gce_Done;
  ThePlane = new Geom_Plane(Pl);
}

GC_MakePlane::GC_MakePlane(const gp_Pnt& P, const gp_Dir& V)
{
  TheError = gce_Done;
  ThePlane = new Geom_Plane(P, V);
}

GC_MakePlane::GC_MakePlane(const double A, const double B, const double C, const double D)
{
  if (std::sqrt(A * A + B * B + C * C) <= gp::Resolution())
  {
    TheError = gce_BadEquation;
  }
  else
  {
    TheError = gce_Done;
    ThePlane = new Geom_Plane(gp_Pln(A, B, C, D));
  }
}

//=========================================================================
//   Creation d un Geom_Plane passant par trois points.                   +
//=========================================================================

GC_MakePlane::GC_MakePlane(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3)
{
  gce_MakePln Pl(P1, P2, P3);
  TheError = Pl.Status();
  if (TheError == gce_Done)
  {
    ThePlane = new Geom_Plane(Pl.Value());
  }
}

//=========================================================================
//   Creation d un Geom_Plane parallele a un pln a une distance donnee.   +
//=========================================================================

GC_MakePlane::GC_MakePlane(const gp_Pln& Pl, const double Dist)
{
  gp_Pln Pln = gce_MakePln(Pl, Dist);
  TheError   = gce_Done;
  ThePlane   = new Geom_Plane(Pln);
}

//=========================================================================
//   Creation d un Geom_Plane parallele a un pln passant par un point     +
//   <Point1>.                                                            +
//=========================================================================

GC_MakePlane::GC_MakePlane(const gp_Pln& Pl, const gp_Pnt& Point)
{
  gp_Pln Pln = gce_MakePln(Pl, Point);
  TheError   = gce_Done;
  ThePlane   = new Geom_Plane(Pln);
}

//=========================================================================
//  Creation d un Geom_Plane a partir d un Ax1 (Point + Normale).         +
//=========================================================================

GC_MakePlane::GC_MakePlane(const gp_Ax1& Axis)
{
  gp_Pln Pln = gce_MakePln(Axis);
  TheError   = gce_Done;
  ThePlane   = new Geom_Plane(Pln);
}

//=========================================================================
//  Creation d un Geom_Plane par un tableau de points.                    +
//=========================================================================

/*GC_MakePlane::GC_MakePlane(const NCollection_Array1<gp_Pnt>&    Pts     ,
                       double            ErrMax  ,
                       double            ErrMean ) {
  GC_MakePln Pln(Pts,ErrMax,ErrMean);
  TheError = Pln.Status();
  if (TheError == GC_Done) {
    ThePlane = new Geom_Plane(Pln.Value());
  }
}
*/

const occ::handle<Geom_Plane>& GC_MakePlane::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GC_MakePlane::Value() - no result");
  return ThePlane;
}
