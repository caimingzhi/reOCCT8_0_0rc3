#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_Hyperbola.hpp>
#include <GeomHash_AxisPlacement.hpp>
#include <cmath>

//! OCCT-style hasher for Geom_Hyperbola (3D hyperbola).
//! Used for geometry deduplication.
struct GeomHash_HyperbolaHasher
{
  // Hashes the hyperbola by its position, major radius, and minor radius.
  std::size_t operator()(const occ::handle<Geom_Hyperbola>& theHyperbola) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const GeomHash_AxisPlacement anAxisHasher;
    const std::size_t            aHashes[3] = {
      anAxisHasher(theHyperbola->Position()),
      opencascade::hash(static_cast<int64_t>(std::round(theHyperbola->MajorRadius() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theHyperbola->MinorRadius() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two hyperbolas by their positions and radii.
  bool operator()(const occ::handle<Geom_Hyperbola>& theHyperbola1,
                  const occ::handle<Geom_Hyperbola>& theHyperbola2) const noexcept
  {
    constexpr double             aTolerance = 1e-12;
    const GeomHash_AxisPlacement anAxisHasher;

    return anAxisHasher(theHyperbola1->Position(), theHyperbola2->Position())
           && std::abs(theHyperbola1->MajorRadius() - theHyperbola2->MajorRadius()) <= aTolerance
           && std::abs(theHyperbola1->MinorRadius() - theHyperbola2->MinorRadius()) <= aTolerance;
  }
};
