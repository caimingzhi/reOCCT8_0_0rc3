#include <BRep_PointsOnSurface.hpp>
#include <Geom_Surface.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_PointsOnSurface, BRep_PointRepresentation)

//=================================================================================================

BRep_PointsOnSurface::BRep_PointsOnSurface(const double                     P,
                                           const occ::handle<Geom_Surface>& S,
                                           const TopLoc_Location&           L)
    : BRep_PointRepresentation(P, L),
      mySurface(S)
{
}

//=================================================================================================

const occ::handle<Geom_Surface>& BRep_PointsOnSurface::Surface() const
{
  return mySurface;
}

//=================================================================================================

void BRep_PointsOnSurface::Surface(const occ::handle<Geom_Surface>& S)
{
  mySurface = S;
}

//=================================================================================================

void BRep_PointsOnSurface::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, BRep_PointRepresentation)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, mySurface.get())
}
