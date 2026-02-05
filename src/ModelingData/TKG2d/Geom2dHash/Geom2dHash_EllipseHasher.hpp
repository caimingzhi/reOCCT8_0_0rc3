#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom2d_Ellipse.hpp>
#include <Geom2dHash_AxisPlacement.hpp>
#include <cmath>

//! OCCT-style hasher for Geom2d_Ellipse (2D ellipse).
//! Used for geometry deduplication.
struct Geom2dHash_EllipseHasher
{
  // Hashes the ellipse by its position, major radius, and minor radius.
  std::size_t operator()(const occ::handle<Geom2d_Ellipse>& theEllipse) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const Geom2dHash_AxisPlacement anAxisHasher;
    const std::size_t              aHashes[3] = {
      anAxisHasher(theEllipse->Position()),
      opencascade::hash(static_cast<int64_t>(std::round(theEllipse->MajorRadius() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theEllipse->MinorRadius() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two ellipses by their positions and radii.
  bool operator()(const occ::handle<Geom2d_Ellipse>& theEllipse1,
                  const occ::handle<Geom2d_Ellipse>& theEllipse2) const noexcept
  {
    constexpr double               aTolerance = 1e-12;
    const Geom2dHash_AxisPlacement anAxisHasher;

    return anAxisHasher(theEllipse1->Position(), theEllipse2->Position())
           && std::abs(theEllipse1->MajorRadius() - theEllipse2->MajorRadius()) <= aTolerance
           && std::abs(theEllipse1->MinorRadius() - theEllipse2->MinorRadius()) <= aTolerance;
  }
};
