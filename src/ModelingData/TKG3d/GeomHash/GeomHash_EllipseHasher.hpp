#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_Ellipse.hpp>
#include <GeomHash_AxisPlacement.hpp>
#include <cmath>

struct GeomHash_EllipseHasher
{

  std::size_t operator()(const occ::handle<Geom_Ellipse>& theEllipse) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const GeomHash_AxisPlacement anAxisHasher;
    const std::size_t            aHashes[3] = {
      anAxisHasher(theEllipse->Position()),
      opencascade::hash(static_cast<int64_t>(std::round(theEllipse->MajorRadius() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theEllipse->MinorRadius() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<Geom_Ellipse>& theEllipse1,
                  const occ::handle<Geom_Ellipse>& theEllipse2) const noexcept
  {
    constexpr double             aTolerance = 1e-12;
    const GeomHash_AxisPlacement anAxisHasher;

    return anAxisHasher(theEllipse1->Position(), theEllipse2->Position())
           && std::abs(theEllipse1->MajorRadius() - theEllipse2->MajorRadius()) <= aTolerance
           && std::abs(theEllipse1->MinorRadius() - theEllipse2->MinorRadius()) <= aTolerance;
  }
};
