#include <BRep_PointOnCurveOnSurface.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Surface.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_PointOnCurveOnSurface, BRep_PointsOnSurface)

BRep_PointOnCurveOnSurface::BRep_PointOnCurveOnSurface(const double                     P,
                                                       const occ::handle<Geom2d_Curve>& C,
                                                       const occ::handle<Geom_Surface>& S,
                                                       const TopLoc_Location&           L)
    : BRep_PointsOnSurface(P, S, L),
      myPCurve(C)
{
}

bool BRep_PointOnCurveOnSurface::IsPointOnCurveOnSurface() const
{
  return true;
}

bool BRep_PointOnCurveOnSurface::IsPointOnCurveOnSurface(const occ::handle<Geom2d_Curve>& PC,
                                                         const occ::handle<Geom_Surface>& S,
                                                         const TopLoc_Location&           L) const
{
  return (myPCurve == PC) && (Surface() == S) && (Location() == L);
}

const occ::handle<Geom2d_Curve>& BRep_PointOnCurveOnSurface::PCurve() const
{
  return myPCurve;
}

void BRep_PointOnCurveOnSurface::PCurve(const occ::handle<Geom2d_Curve>& C)
{
  myPCurve = C;
}

void BRep_PointOnCurveOnSurface::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, BRep_PointRepresentation)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myPCurve.get())
}
