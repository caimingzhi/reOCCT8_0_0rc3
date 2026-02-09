#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRep_CurveRepresentation.hpp>
class Poly_Polygon2D;
class Geom_Surface;
class TopLoc_Location;

class BRep_PolygonOnSurface : public BRep_CurveRepresentation
{

public:
  Standard_EXPORT BRep_PolygonOnSurface(const occ::handle<Poly_Polygon2D>& P,
                                        const occ::handle<Geom_Surface>&   S,
                                        const TopLoc_Location&             L);

  Standard_EXPORT bool IsPolygonOnSurface() const override;

  Standard_EXPORT bool IsPolygonOnSurface(const occ::handle<Geom_Surface>& S,
                                          const TopLoc_Location&           L) const override;

  Standard_EXPORT const occ::handle<Geom_Surface>& Surface() const override;

  Standard_EXPORT const occ::handle<Poly_Polygon2D>& Polygon() const override;

  Standard_EXPORT void Polygon(const occ::handle<Poly_Polygon2D>& P) override;

  Standard_EXPORT occ::handle<BRep_CurveRepresentation> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_PolygonOnSurface, BRep_CurveRepresentation)

private:
  occ::handle<Poly_Polygon2D> myPolygon2D;
  occ::handle<Geom_Surface>   mySurface;
};
