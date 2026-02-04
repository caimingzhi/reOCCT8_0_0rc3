#pragma once


#include <Standard_HashUtils.hpp>
#include <gp_Dir2d.hpp>
#include <cmath>

//! OCCT-style hasher for gp_Dir2d (2D directions).
//! Used for geometry deduplication.
struct Geom2dHash_DirectionHasher
{
  // Hashes the 2D direction by its XY components.
  std::size_t operator()(const gp_Dir2d& theDirection) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    // Round each component to tolerance precision before hashing
    const std::size_t aHashes[2] = {
      opencascade::hash(static_cast<int64_t>(std::round(theDirection.X() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theDirection.Y() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two 2D directions with fixed tolerance.
  bool operator()(const gp_Dir2d& theDirection1, const gp_Dir2d& theDirection2) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    return std::abs(theDirection1.X() - theDirection2.X()) <= aTolerance
           && std::abs(theDirection1.Y() - theDirection2.Y()) <= aTolerance;
  }
};

