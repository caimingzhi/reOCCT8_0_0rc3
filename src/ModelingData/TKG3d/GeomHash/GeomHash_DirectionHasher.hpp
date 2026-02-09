#pragma once

#include <Standard_HashUtils.hpp>
#include <gp_Dir.hpp>
#include <cmath>

struct GeomHash_DirectionHasher
{

  std::size_t operator()(const gp_Dir& theDirection) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const std::size_t aHashes[3] = {
      opencascade::hash(static_cast<int64_t>(std::round(theDirection.X() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theDirection.Y() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theDirection.Z() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const gp_Dir& theDirection1, const gp_Dir& theDirection2) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    return std::abs(theDirection1.X() - theDirection2.X()) <= aTolerance
           && std::abs(theDirection1.Y() - theDirection2.Y()) <= aTolerance
           && std::abs(theDirection1.Z() - theDirection2.Z()) <= aTolerance;
  }
};
