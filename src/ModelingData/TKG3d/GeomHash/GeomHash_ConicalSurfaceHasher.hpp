#pragma once


#include <Standard_HashUtils.hpp>
#include <Geom_ConicalSurface.hpp>
#include <GeomHash_AxisPlacement.hpp>
#include <cmath>

//! OCCT-style hasher for Geom_ConicalSurface.
//! Used for geometry deduplication.
struct GeomHash_ConicalSurfaceHasher
{
  // Hashes the cone by its position, apex radius, and semi-angle.
  std::size_t operator()(const occ::handle<Geom_ConicalSurface>& theCone) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const GeomHash_AxisPlacement anAxisHasher;
    const std::size_t            aHashes[3] = {
      anAxisHasher(theCone->Position().Ax2()),
      opencascade::hash(static_cast<int64_t>(std::round(theCone->RefRadius() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theCone->SemiAngle() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two cones by their positions, radii, and semi-angles.
  bool operator()(const occ::handle<Geom_ConicalSurface>& theCone1,
                  const occ::handle<Geom_ConicalSurface>& theCone2) const noexcept
  {
    constexpr double             aTolerance = 1e-12;
    const GeomHash_AxisPlacement anAxisHasher;
    return anAxisHasher(theCone1->Position().Ax2(), theCone2->Position().Ax2())
           && std::abs(theCone1->RefRadius() - theCone2->RefRadius()) <= aTolerance
           && std::abs(theCone1->SemiAngle() - theCone2->SemiAngle()) <= aTolerance;
  }
};

