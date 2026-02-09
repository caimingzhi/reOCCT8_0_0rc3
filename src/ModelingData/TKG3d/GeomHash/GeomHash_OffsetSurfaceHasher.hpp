#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_OffsetSurface.hpp>
#include <GeomHash_SurfaceHasher.hpp>
#include <cmath>

struct GeomHash_OffsetSurfaceHasher
{

  std::size_t operator()(const occ::handle<Geom_OffsetSurface>& theSurface) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const GeomHash_SurfaceHasher aSurfaceHasher;
    const std::size_t            aHashes[2] = {
      aSurfaceHasher(theSurface->BasisSurface()),
      opencascade::hash(static_cast<int64_t>(std::round(theSurface->Offset() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<Geom_OffsetSurface>& theSurface1,
                  const occ::handle<Geom_OffsetSurface>& theSurface2) const noexcept
  {
    constexpr double aTolerance = 1e-12;

    const GeomHash_SurfaceHasher aSurfaceHasher;

    return aSurfaceHasher(theSurface1->BasisSurface(), theSurface2->BasisSurface())
           && std::abs(theSurface1->Offset() - theSurface2->Offset()) <= aTolerance;
  }
};
