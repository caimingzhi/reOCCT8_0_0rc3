#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRep_CurveRepresentation.hpp>
class Poly_PolygonOnTriangulation;
class Poly_Triangulation;
class TopLoc_Location;

class BRep_PolygonOnTriangulation : public BRep_CurveRepresentation
{

public:
  Standard_EXPORT BRep_PolygonOnTriangulation(const occ::handle<Poly_PolygonOnTriangulation>& P,
                                              const occ::handle<Poly_Triangulation>&          T,
                                              const TopLoc_Location&                          L);

  Standard_EXPORT bool IsPolygonOnTriangulation() const override;

  Standard_EXPORT bool IsPolygonOnTriangulation(const occ::handle<Poly_Triangulation>& T,
                                                const TopLoc_Location& L) const override;

  Standard_EXPORT void PolygonOnTriangulation(
    const occ::handle<Poly_PolygonOnTriangulation>& P) override;

  Standard_EXPORT const occ::handle<Poly_Triangulation>& Triangulation() const override;

  Standard_EXPORT const occ::handle<Poly_PolygonOnTriangulation>& PolygonOnTriangulation()
    const override;

  Standard_EXPORT occ::handle<BRep_CurveRepresentation> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_PolygonOnTriangulation, BRep_CurveRepresentation)

private:
  occ::handle<Poly_PolygonOnTriangulation> myPolygon;
  occ::handle<Poly_Triangulation>          myTriangulation;
};
