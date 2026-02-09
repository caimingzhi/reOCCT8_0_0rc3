#include <BRep_CurveRepresentation.hpp>
#include <BRep_PolygonOnClosedTriangulation.hpp>
#include <Poly_PolygonOnTriangulation.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_PolygonOnClosedTriangulation, BRep_PolygonOnTriangulation)

BRep_PolygonOnClosedTriangulation::BRep_PolygonOnClosedTriangulation(
  const occ::handle<Poly_PolygonOnTriangulation>& P1,
  const occ::handle<Poly_PolygonOnTriangulation>& P2,
  const occ::handle<Poly_Triangulation>&          T,
  const TopLoc_Location&                          L)
    : BRep_PolygonOnTriangulation(P1, T, L),
      myPolygon2(P2)
{
}

bool BRep_PolygonOnClosedTriangulation::IsPolygonOnClosedTriangulation() const
{
  return true;
}

void BRep_PolygonOnClosedTriangulation::PolygonOnTriangulation2(
  const occ::handle<Poly_PolygonOnTriangulation>& P2)
{
  myPolygon2 = P2;
}

const occ::handle<Poly_PolygonOnTriangulation>& BRep_PolygonOnClosedTriangulation::
  PolygonOnTriangulation2() const
{
  return myPolygon2;
}

occ::handle<BRep_CurveRepresentation> BRep_PolygonOnClosedTriangulation::Copy() const
{
  occ::handle<BRep_PolygonOnClosedTriangulation> P;
  P = new BRep_PolygonOnClosedTriangulation(PolygonOnTriangulation(),
                                            myPolygon2,
                                            Triangulation(),
                                            Location());

  return P;
}

void BRep_PolygonOnClosedTriangulation::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, BRep_PolygonOnTriangulation)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myPolygon2.get())
}
