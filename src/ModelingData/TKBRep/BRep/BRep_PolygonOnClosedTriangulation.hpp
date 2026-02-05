#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRep_PolygonOnTriangulation.hpp>
class Poly_PolygonOnTriangulation;
class Poly_Triangulation;
class TopLoc_Location;
class BRep_CurveRepresentation;

//! A representation by two arrays of nodes on a
//! triangulation.
class BRep_PolygonOnClosedTriangulation : public BRep_PolygonOnTriangulation
{

public:
  Standard_EXPORT BRep_PolygonOnClosedTriangulation(
    const occ::handle<Poly_PolygonOnTriangulation>& P1,
    const occ::handle<Poly_PolygonOnTriangulation>& P2,
    const occ::handle<Poly_Triangulation>&          Tr,
    const TopLoc_Location&                          L);

  //! Returns True.
  Standard_EXPORT bool IsPolygonOnClosedTriangulation() const override;

  Standard_EXPORT void PolygonOnTriangulation2(
    const occ::handle<Poly_PolygonOnTriangulation>& P2) override;

  Standard_EXPORT const occ::handle<Poly_PolygonOnTriangulation>& PolygonOnTriangulation2()
    const override;

  //! Return a copy of this representation.
  Standard_EXPORT occ::handle<BRep_CurveRepresentation> Copy() const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_PolygonOnClosedTriangulation, BRep_PolygonOnTriangulation)

private:
  occ::handle<Poly_PolygonOnTriangulation> myPolygon2;
};
