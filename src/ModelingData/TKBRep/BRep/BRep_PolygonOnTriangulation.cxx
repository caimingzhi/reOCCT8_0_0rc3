#include <BRep_CurveRepresentation.hpp>
#include <BRep_PolygonOnTriangulation.hpp>
#include <Poly_PolygonOnTriangulation.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_PolygonOnTriangulation, BRep_CurveRepresentation)

//=================================================================================================

BRep_PolygonOnTriangulation::BRep_PolygonOnTriangulation(
  const occ::handle<Poly_PolygonOnTriangulation>& P,
  const occ::handle<Poly_Triangulation>&          T,
  const TopLoc_Location&                          L)
    : BRep_CurveRepresentation(L),
      myPolygon(P),
      myTriangulation(T)
{
}

//=================================================================================================

bool BRep_PolygonOnTriangulation::IsPolygonOnTriangulation() const
{
  return true;
}

//=================================================================================================

bool BRep_PolygonOnTriangulation::IsPolygonOnTriangulation(const occ::handle<Poly_Triangulation>& T,
                                                           const TopLoc_Location& L) const
{
  return (T == myTriangulation) && (L == myLocation);
}

//=================================================================================================

void BRep_PolygonOnTriangulation::PolygonOnTriangulation(
  const occ::handle<Poly_PolygonOnTriangulation>& P)
{
  myPolygon = P;
}

//=================================================================================================

const occ::handle<Poly_PolygonOnTriangulation>& BRep_PolygonOnTriangulation::
  PolygonOnTriangulation() const
{
  return myPolygon;
}

//=================================================================================================

const occ::handle<Poly_Triangulation>& BRep_PolygonOnTriangulation::Triangulation() const
{
  return myTriangulation;
}

//=================================================================================================

occ::handle<BRep_CurveRepresentation> BRep_PolygonOnTriangulation::Copy() const
{
  occ::handle<BRep_PolygonOnTriangulation> P =
    new BRep_PolygonOnTriangulation(myPolygon, myTriangulation, Location());

  return P;
}

//=================================================================================================

void BRep_PolygonOnTriangulation::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, BRep_CurveRepresentation)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myPolygon.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myTriangulation.get())
}
