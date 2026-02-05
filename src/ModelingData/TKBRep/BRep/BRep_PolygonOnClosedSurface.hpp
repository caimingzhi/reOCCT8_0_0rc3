#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRep_PolygonOnSurface.hpp>
class Poly_Polygon2D;
class Geom_Surface;
class TopLoc_Location;
class BRep_CurveRepresentation;

//! Representation by two 2d polygons in the parametric
//! space of a surface.
class BRep_PolygonOnClosedSurface : public BRep_PolygonOnSurface
{

public:
  Standard_EXPORT BRep_PolygonOnClosedSurface(const occ::handle<Poly_Polygon2D>& P1,
                                              const occ::handle<Poly_Polygon2D>& P2,
                                              const occ::handle<Geom_Surface>&   S,
                                              const TopLoc_Location&             L);

  //! returns True.
  Standard_EXPORT bool IsPolygonOnClosedSurface() const override;

  Standard_EXPORT const occ::handle<Poly_Polygon2D>& Polygon2() const override;

  Standard_EXPORT void Polygon2(const occ::handle<Poly_Polygon2D>& P) override;

  //! Return a copy of this representation.
  Standard_EXPORT occ::handle<BRep_CurveRepresentation> Copy() const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_PolygonOnClosedSurface, BRep_PolygonOnSurface)

private:
  occ::handle<Poly_Polygon2D> myPolygon2;
};
