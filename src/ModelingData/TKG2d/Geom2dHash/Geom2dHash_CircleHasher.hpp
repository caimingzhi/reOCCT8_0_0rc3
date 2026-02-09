#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2dHash_AxisPlacement.hpp>
#include <cmath>

struct Geom2dHash_CircleHasher
{

  std::size_t operator()(const occ::handle<Geom2d_Circle>& theCircle) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const Geom2dHash_AxisPlacement anAxisHasher;
    const std::size_t              aHashes[2] = {
      anAxisHasher(theCircle->Position()),
      opencascade::hash(static_cast<int64_t>(std::round(theCircle->Radius() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<Geom2d_Circle>& theCircle1,
                  const occ::handle<Geom2d_Circle>& theCircle2) const noexcept
  {
    constexpr double               aTolerance = 1e-12;
    const Geom2dHash_AxisPlacement anAxisHasher;

    return anAxisHasher(theCircle1->Position(), theCircle2->Position())
           && std::abs(theCircle1->Radius() - theCircle2->Radius()) <= aTolerance;
  }
};
