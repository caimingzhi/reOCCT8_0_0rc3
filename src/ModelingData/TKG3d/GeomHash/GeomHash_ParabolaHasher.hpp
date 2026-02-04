#pragma once


#include <Standard_HashUtils.hpp>
#include <Geom_Parabola.hpp>
#include <GeomHash_AxisPlacement.hpp>
#include <cmath>

//! OCCT-style hasher for Geom_Parabola (3D parabola).
//! Used for geometry deduplication.
struct GeomHash_ParabolaHasher
{
  // Hashes the parabola by its position and focal length.
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

  // Compares two parabolas by their positions and focal lengths.
  bool operator()(const occ::handle<Geom_Parabola>& theParabola1,
                  const occ::handle<Geom_Parabola>& theParabola2) const noexcept
  {
    constexpr double             aTolerance = 1e-12;
    const GeomHash_AxisPlacement anAxisHasher;

    return anAxisHasher(theParabola1->Position(), theParabola2->Position())
           && std::abs(theParabola1->Focal() - theParabola2->Focal()) <= aTolerance;
  }
};

