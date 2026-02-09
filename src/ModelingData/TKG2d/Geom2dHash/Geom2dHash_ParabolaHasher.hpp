#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom2d_Parabola.hpp>
#include <Geom2dHash_AxisPlacement.hpp>
#include <cmath>

struct Geom2dHash_ParabolaHasher
{

  std::size_t operator()(const occ::handle<Geom2d_Parabola>& theParabola) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const Geom2dHash_AxisPlacement anAxisHasher;
    const std::size_t              aHashes[2] = {
      anAxisHasher(theParabola->Position()),
      opencascade::hash(static_cast<int64_t>(std::round(theParabola->Focal() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<Geom2d_Parabola>& theParabola1,
                  const occ::handle<Geom2d_Parabola>& theParabola2) const noexcept
  {
    constexpr double               aTolerance = 1e-12;
    const Geom2dHash_AxisPlacement anAxisHasher;

    return anAxisHasher(theParabola1->Position(), theParabola2->Position())
           && std::abs(theParabola1->Focal() - theParabola2->Focal()) <= aTolerance;
  }
};
