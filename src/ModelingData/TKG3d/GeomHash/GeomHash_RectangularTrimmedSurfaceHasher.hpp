#pragma once


#include <Standard_HashUtils.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <GeomHash_SurfaceHasher.hpp>
#include <cmath>

//! OCCT-style hasher for Geom_RectangularTrimmedSurface.
//! Used for geometry deduplication.
struct GeomHash_RectangularTrimmedSurfaceHasher
{
  // Hashes the trimmed surface by its trim bounds and basis surface.
  std::size_t operator()(
    const occ::handle<Geom_RectangularTrimmedSurface>& theSurface) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const GeomHash_SurfaceHasher aSurfaceHasher;

    double aU1, aU2, aV1, aV2;
    theSurface->Bounds(aU1, aU2, aV1, aV2);

    const std::size_t aHashes[5] = {
      aSurfaceHasher(theSurface->BasisSurface()),
      opencascade::hash(static_cast<int64_t>(std::round(aU1 * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(aU2 * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(aV1 * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(aV2 * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two trimmed surfaces by their trim bounds and basis surfaces.
  bool operator()(const occ::handle<Geom_RectangularTrimmedSurface>& theSurface1,
                  const occ::handle<Geom_RectangularTrimmedSurface>& theSurface2) const noexcept
  {
    constexpr double aTolerance = 1e-12;

    const GeomHash_SurfaceHasher aSurfaceHasher;

    // Compare basis surfaces
    if (!aSurfaceHasher(theSurface1->BasisSurface(), theSurface2->BasisSurface()))
    {
      return false;
    }

    // Compare trim bounds
    double aU1_1, aU2_1, aV1_1, aV2_1;
    double aU1_2, aU2_2, aV1_2, aV2_2;
    theSurface1->Bounds(aU1_1, aU2_1, aV1_1, aV2_1);
    theSurface2->Bounds(aU1_2, aU2_2, aV1_2, aV2_2);

    return std::abs(aU1_1 - aU1_2) <= aTolerance && std::abs(aU2_1 - aU2_2) <= aTolerance
           && std::abs(aV1_1 - aV1_2) <= aTolerance && std::abs(aV2_1 - aV2_2) <= aTolerance;
  }
};

