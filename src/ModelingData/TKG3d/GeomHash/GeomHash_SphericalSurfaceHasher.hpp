#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_SphericalSurface.hpp>
#include <GeomHash_AxisPlacement.hpp>
#include <cmath>

struct GeomHash_SphericalSurfaceHasher
{

  std::size_t operator()(const occ::handle<Geom_SphericalSurface>& theSphere) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const GeomHash_AxisPlacement anAxisHasher;
    const std::size_t            aHashes[2] = {
      anAxisHasher(theSphere->Position().Ax2()),
      opencascade::hash(static_cast<int64_t>(std::round(theSphere->Radius() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<Geom_SphericalSurface>& theSphere1,
                  const occ::handle<Geom_SphericalSurface>& theSphere2) const noexcept
  {
    constexpr double             aTolerance = 1e-12;
    const GeomHash_AxisPlacement anAxisHasher;
    return anAxisHasher(theSphere1->Position().Ax2(), theSphere2->Position().Ax2())
           && std::abs(theSphere1->Radius() - theSphere2->Radius()) <= aTolerance;
  }
};
