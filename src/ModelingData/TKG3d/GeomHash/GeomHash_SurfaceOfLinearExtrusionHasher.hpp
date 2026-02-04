#pragma once


#include <Standard_HashUtils.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <GeomHash_DirectionHasher.hpp>
#include <GeomHash_CurveHasher.hpp>

//! OCCT-style hasher for Geom_SurfaceOfLinearExtrusion.
//! Used for geometry deduplication.
struct GeomHash_SurfaceOfLinearExtrusionHasher
{
  // Hashes the extrusion surface by its direction and basis curve.
  std::size_t operator()(
    const occ::handle<Geom_SurfaceOfLinearExtrusion>& theSurface) const noexcept
  {
    const GeomHash_DirectionHasher aDirHasher;
    const GeomHash_CurveHasher     aCurveHasher;
    const std::size_t              aHashes[2] = {aCurveHasher(theSurface->BasisCurve()),
                                                 aDirHasher(theSurface->Direction())};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two extrusion surfaces.
  bool operator()(const occ::handle<Geom_SurfaceOfLinearExtrusion>& theSurface1,
                  const occ::handle<Geom_SurfaceOfLinearExtrusion>& theSurface2) const noexcept
  {
    const GeomHash_DirectionHasher aDirHasher;
    const GeomHash_CurveHasher     aCurveHasher;

    return aCurveHasher(theSurface1->BasisCurve(), theSurface2->BasisCurve())
           && aDirHasher(theSurface1->Direction(), theSurface2->Direction());
  }
};

