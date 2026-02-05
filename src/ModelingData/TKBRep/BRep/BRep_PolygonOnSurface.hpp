#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRep_CurveRepresentation.hpp>
class Poly_Polygon2D;
class Geom_Surface;
class TopLoc_Location;

//! Representation of a 2D polygon in the parametric
//! space of a surface.
class BRep_PolygonOnSurface : public BRep_CurveRepresentation
{

public:
  Standard_EXPORT BRep_PolygonOnSurface(const occ::handle<Poly_Polygon2D>& P,
                                        const occ::handle<Geom_Surface>&   S,
                                        const TopLoc_Location&             L);

  //! A 2D polygon representation in the parametric
  //! space of a surface.
  Standard_EXPORT bool IsPolygonOnSurface() const override;

  //! A 2D polygon representation in the parametric
  //! space of a surface.
  Standard_EXPORT bool IsPolygonOnSurface(const occ::handle<Geom_Surface>& S,
                                          const TopLoc_Location&           L) const override;

  Standard_EXPORT const occ::handle<Geom_Surface>& Surface() const override;

  Standard_EXPORT const occ::handle<Poly_Polygon2D>& Polygon() const override;

  Standard_EXPORT void Polygon(const occ::handle<Poly_Polygon2D>& P) override;

  //! Return a copy of this representation.
  Standard_EXPORT occ::handle<BRep_CurveRepresentation> Copy() const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_PolygonOnSurface, BRep_CurveRepresentation)

private:
  occ::handle<Poly_Polygon2D> myPolygon2D;
  occ::handle<Geom_Surface>   mySurface;
};
