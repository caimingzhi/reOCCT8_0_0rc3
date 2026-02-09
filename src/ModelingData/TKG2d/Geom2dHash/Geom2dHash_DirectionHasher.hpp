#pragma once

#include <Standard_HashUtils.hpp>
#include <gp_Dir2d.hpp>
#include <cmath>

struct Geom2dHash_DirectionHasher
{

  std::size_t operator()(const gp_Dir2d& theDirection) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const std::size_t aHashes[2] = {
      opencascade::hash(static_cast<int64_t>(std::round(theDirection.X() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theDirection.Y() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const gp_Dir2d& theDirection1, const gp_Dir2d& theDirection2) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    return std::abs(theDirection1.X() - theDirection2.X()) <= aTolerance
           && std::abs(theDirection1.Y() - theDirection2.Y()) <= aTolerance;
  }
};
