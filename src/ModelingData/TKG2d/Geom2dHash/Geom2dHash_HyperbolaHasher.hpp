#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom2d_Hyperbola.hpp>
#include <Geom2dHash_AxisPlacement.hpp>
#include <cmath>

//! OCCT-style hasher for Geom2d_Hyperbola (2D hyperbola).
//! Used for geometry deduplication.
struct Geom2dHash_HyperbolaHasher
{
  // Hashes the hyperbola by its position, major radius, and minor radius.
  std::size_t operator()(const occ::handle<Geom2d_Hyperbola>& theHyperbola) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const Geom2dHash_AxisPlacement anAxisHasher;
    const std::size_t              aHashes[3] = {
      anAxisHasher(theHyperbola->Position()),
      opencascade::hash(static_cast<int64_t>(std::round(theHyperbola->MajorRadius() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theHyperbola->MinorRadius() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two hyperbolas by their positions and radii.
  bool operator()(const occ::handle<Geom2d_Hyperbola>& theHyperbola1,
                  const occ::handle<Geom2d_Hyperbola>& theHyperbola2) const noexcept
  {
    constexpr double               aTolerance = 1e-12;
    const Geom2dHash_AxisPlacement anAxisHasher;

    return anAxisHasher(theHyperbola1->Position(), theHyperbola2->Position())
           && std::abs(theHyperbola1->MajorRadius() - theHyperbola2->MajorRadius()) <= aTolerance
           && std::abs(theHyperbola1->MinorRadius() - theHyperbola2->MinorRadius()) <= aTolerance;
  }
};
