#pragma once


#include <Standard_HashUtils.hpp>
#include <gp_Pnt2d.hpp>
#include <cmath>

//! OCCT-style hasher for gp_Pnt2d (2D points).
//! Used for geometry deduplication.
struct Geom2dHash_PointHasher
{
  // Hashes the 2D point by its XY coordinates.
  std::size_t operator()(const gp_Pnt2d& thePoint) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    // Round each coordinate to tolerance precision before hashing
    const std::size_t aHashes[2] = {
      opencascade::hash(static_cast<int64_t>(std::round(thePoint.X() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(thePoint.Y() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two 2D points with fixed tolerance.
  bool operator()(const gp_Pnt2d& thePoint1, const gp_Pnt2d& thePoint2) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    return std::abs(thePoint1.X() - thePoint2.X()) <= aTolerance
           && std::abs(thePoint1.Y() - thePoint2.Y()) <= aTolerance;
  }
};

