#include <BRep_CurveRepresentation.hpp>
#include <BRep_PolygonOnSurface.hpp>
#include <Geom_Surface.hpp>
#include <Poly_Polygon2D.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_PolygonOnSurface, BRep_CurveRepresentation)

//=================================================================================================

BRep_PolygonOnSurface::BRep_PolygonOnSurface(const occ::handle<Poly_Polygon2D>& P,
                                             const occ::handle<Geom_Surface>&   S,
                                             const TopLoc_Location&             L)
    : BRep_CurveRepresentation(L),
      myPolygon2D(P),
      mySurface(S)
{
}

//=================================================================================================

bool BRep_PolygonOnSurface::IsPolygonOnSurface() const
{
  return true;
}

//=================================================================================================

bool BRep_PolygonOnSurface::IsPolygonOnSurface(const occ::handle<Geom_Surface>& S,
                                               const TopLoc_Location&           L) const
{
  return (S == mySurface) && (L == myLocation);
}

//=================================================================================================

const occ::handle<Geom_Surface>& BRep_PolygonOnSurface::Surface() const
{
  return mySurface;
}

//=================================================================================================

const occ::handle<Poly_Polygon2D>& BRep_PolygonOnSurface::Polygon() const
{
  return myPolygon2D;
}

//=================================================================================================

void BRep_PolygonOnSurface::Polygon(const occ::handle<Poly_Polygon2D>& P)
{
  myPolygon2D = P;
}

//=================================================================================================

occ::handle<BRep_CurveRepresentation> BRep_PolygonOnSurface::Copy() const
{
  occ::handle<BRep_PolygonOnSurface> P =
    new BRep_PolygonOnSurface(myPolygon2D, mySurface, Location());
  return P;
}

//=================================================================================================

void BRep_PolygonOnSurface::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, BRep_CurveRepresentation)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myPolygon2D.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, mySurface.get())
}
