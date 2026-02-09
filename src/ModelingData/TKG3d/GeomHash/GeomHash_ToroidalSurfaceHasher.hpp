#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <GeomHash_AxisPlacement.hpp>
#include <cmath>

struct GeomHash_ToroidalSurfaceHasher
{

  std::size_t operator()(const occ::handle<Geom_ToroidalSurface>& theTorus) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const GeomHash_AxisPlacement anAxisHasher;
    const std::size_t            aHashes[3] = {
      anAxisHasher(theTorus->Position().Ax2()),
      opencascade::hash(static_cast<int64_t>(std::round(theTorus->MajorRadius() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theTorus->MinorRadius() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<Geom_ToroidalSurface>& theTorus1,
                  const occ::handle<Geom_ToroidalSurface>& theTorus2) const noexcept
  {
    constexpr double             aTolerance = 1e-12;
    const GeomHash_AxisPlacement anAxisHasher;
    return anAxisHasher(theTorus1->Position().Ax2(), theTorus2->Position().Ax2())
           && std::abs(theTorus1->MajorRadius() - theTorus2->MajorRadius()) <= aTolerance
           && std::abs(theTorus1->MinorRadius() - theTorus2->MinorRadius()) <= aTolerance;
  }
};
