#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <GeomHash_AxisPlacement.hpp>
#include <cmath>

struct GeomHash_CylindricalSurfaceHasher
{

  std::size_t operator()(const occ::handle<Geom_CylindricalSurface>& theCylinder) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const GeomHash_AxisPlacement anAxisHasher;
    const std::size_t            aHashes[2] = {
      anAxisHasher(theCylinder->Position().Ax2()),
      opencascade::hash(static_cast<int64_t>(std::round(theCylinder->Radius() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<Geom_CylindricalSurface>& theCylinder1,
                  const occ::handle<Geom_CylindricalSurface>& theCylinder2) const noexcept
  {
    constexpr double             aTolerance = 1e-12;
    const GeomHash_AxisPlacement anAxisHasher;
    return anAxisHasher(theCylinder1->Position().Ax2(), theCylinder2->Position().Ax2())
           && std::abs(theCylinder1->Radius() - theCylinder2->Radius()) <= aTolerance;
  }
};
