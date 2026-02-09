#include <BRep_PointOnSurface.hpp>
#include <Geom_Surface.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_PointOnSurface, BRep_PointsOnSurface)

BRep_PointOnSurface::BRep_PointOnSurface(const double                     P1,
                                         const double                     P2,
                                         const occ::handle<Geom_Surface>& S,
                                         const TopLoc_Location&           L)
    : BRep_PointsOnSurface(P1, S, L),
      myParameter2(P2)
{
}

bool BRep_PointOnSurface::IsPointOnSurface() const
{
  return true;
}

bool BRep_PointOnSurface::IsPointOnSurface(const occ::handle<Geom_Surface>& S,
                                           const TopLoc_Location&           L) const
{
  return (Surface() == S) && (Location() == L);
}

double BRep_PointOnSurface::Parameter2() const
{
  return myParameter2;
}

void BRep_PointOnSurface::Parameter2(const double P)
{
  myParameter2 = P;
}
