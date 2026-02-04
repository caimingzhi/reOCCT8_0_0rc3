#pragma once


#include <Standard_HashUtils.hpp>
#include <Geom2d_Parabola.hpp>
#include <Geom2dHash_AxisPlacement.hpp>
#include <cmath>

//! OCCT-style hasher for Geom2d_Parabola (2D parabola).
//! Used for geometry deduplication.
struct Geom2dHash_ParabolaHasher
{
  // Hashes the parabola by its position and focal length.
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

  // Compares two parabolas by their positions and focal lengths.
  bool operator()(const occ::handle<Geom2d_Parabola>& theParabola1,
                  const occ::handle<Geom2d_Parabola>& theParabola2) const noexcept
  {
    constexpr double               aTolerance = 1e-12;
    const Geom2dHash_AxisPlacement anAxisHasher;

    return anAxisHasher(theParabola1->Position(), theParabola2->Position())
           && std::abs(theParabola1->Focal() - theParabola2->Focal()) <= aTolerance;
  }
};

