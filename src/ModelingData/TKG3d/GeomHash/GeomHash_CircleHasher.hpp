#pragma once


#include <Standard_HashUtils.hpp>
#include <Geom_Circle.hpp>
#include <GeomHash_AxisPlacement.hpp>
#include <cmath>

//! OCCT-style hasher for Geom_Circle (3D circle).
//! Used for geometry deduplication.
struct GeomHash_CircleHasher
{
  // Hashes the circle by its position and radius.
  std::size_t operator()(const occ::handle<Geom_Circle>& theCircle) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const GeomHash_AxisPlacement anAxisHasher;
    const std::size_t            aHashes[2] = {
      anAxisHasher(theCircle->Position()),
      opencascade::hash(static_cast<int64_t>(std::round(theCircle->Radius() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two circles by their positions and radii.
  bool operator()(const occ::handle<Geom_Circle>& theCircle1,
                  const occ::handle<Geom_Circle>& theCircle2) const noexcept
  {
    constexpr double             aTolerance = 1e-12;
    const GeomHash_AxisPlacement anAxisHasher;

    return anAxisHasher(theCircle1->Position(), theCircle2->Position())
           && std::abs(theCircle1->Radius() - theCircle2->Radius()) <= aTolerance;
  }
};

