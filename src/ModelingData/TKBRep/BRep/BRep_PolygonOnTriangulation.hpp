#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRep_CurveRepresentation.hpp>
class Poly_PolygonOnTriangulation;
class Poly_Triangulation;
class TopLoc_Location;

//! A representation by an array of nodes on a
//! triangulation.
class BRep_PolygonOnTriangulation : public BRep_CurveRepresentation
{

public:
  Standard_EXPORT BRep_PolygonOnTriangulation(const occ::handle<Poly_PolygonOnTriangulation>& P,
                                              const occ::handle<Poly_Triangulation>&          T,
                                              const TopLoc_Location&                          L);

  //! returns True.
  Standard_EXPORT bool IsPolygonOnTriangulation() const override;

  //! Is it a polygon in the definition of <T> with
  //! location <L>.
  Standard_EXPORT bool IsPolygonOnTriangulation(const occ::handle<Poly_Triangulation>& T,
                                                const TopLoc_Location& L) const override;

  //! returns True.
  Standard_EXPORT void PolygonOnTriangulation(
    const occ::handle<Poly_PolygonOnTriangulation>& P) override;

  Standard_EXPORT const occ::handle<Poly_Triangulation>& Triangulation() const override;

  Standard_EXPORT const occ::handle<Poly_PolygonOnTriangulation>& PolygonOnTriangulation()
    const override;

  //! Return a copy of this representation.
  Standard_EXPORT occ::handle<BRep_CurveRepresentation> Copy() const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_PolygonOnTriangulation, BRep_CurveRepresentation)

private:
  occ::handle<Poly_PolygonOnTriangulation> myPolygon;
  occ::handle<Poly_Triangulation>          myTriangulation;
};
