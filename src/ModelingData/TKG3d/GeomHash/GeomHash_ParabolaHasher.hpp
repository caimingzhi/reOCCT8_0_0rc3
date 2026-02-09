#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_Parabola.hpp>
#include <GeomHash_AxisPlacement.hpp>
#include <cmath>

struct GeomHash_ParabolaHasher
{

  std::size_t operator()(const occ::handle<Geom_Parabola>& theParabola) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const GeomHash_AxisPlacement anAxisHasher;
    const std::size_t            aHashes[2] = {
      anAxisHasher(theParabola->Position()),
      opencascade::hash(static_cast<int64_t>(std::round(theParabola->Focal() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<Geom_Parabola>& theParabola1,
                  const occ::handle<Geom_Parabola>& theParabola2) const noexcept
  {
    constexpr double             aTolerance = 1e-12;
    const GeomHash_AxisPlacement anAxisHasher;

    return anAxisHasher(theParabola1->Position(), theParabola2->Position())
           && std::abs(theParabola1->Focal() - theParabola2->Focal()) <= aTolerance;
  }
};
