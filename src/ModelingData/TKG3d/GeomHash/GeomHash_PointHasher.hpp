#pragma once

#include <Standard_HashUtils.hpp>
#include <gp_Pnt.hpp>
#include <cmath>

struct GeomHash_PointHasher
{

  std::size_t operator()(const gp_Pnt& thePoint) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const std::size_t aHashes[3] = {
      opencascade::hash(static_cast<int64_t>(std::round(thePoint.X() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(thePoint.Y() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(thePoint.Z() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const gp_Pnt& thePoint1, const gp_Pnt& thePoint2) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    return std::abs(thePoint1.X() - thePoint2.X()) <= aTolerance
           && std::abs(thePoint1.Y() - thePoint2.Y()) <= aTolerance
           && std::abs(thePoint1.Z() - thePoint2.Z()) <= aTolerance;
  }
};
