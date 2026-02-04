#pragma once


#include <Standard_HashUtils.hpp>
#include <gp_Dir.hpp>
#include <cmath>

//! OCCT-style hasher for gp_Dir (3D directions).
//! Used for geometry deduplication.
struct GeomHash_DirectionHasher
{
  // Hashes the 3D direction by its XYZ components.
  std::size_t operator()(const gp_Dir& theDirection) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    // Round each component to tolerance precision before hashing
    const std::size_t aHashes[3] = {
      opencascade::hash(static_cast<int64_t>(std::round(theDirection.X() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theDirection.Y() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theDirection.Z() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two 3D directions with fixed tolerance.
  bool operator()(const gp_Dir& theDirection1, const gp_Dir& theDirection2) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    return std::abs(theDirection1.X() - theDirection2.X()) <= aTolerance
           && std::abs(theDirection1.Y() - theDirection2.Y()) <= aTolerance
           && std::abs(theDirection1.Z() - theDirection2.Z()) <= aTolerance;
  }
};

