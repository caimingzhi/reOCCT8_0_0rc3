#pragma once


#include <Standard_HashUtils.hpp>
#include <Geom_OffsetCurve.hpp>
#include <GeomHash_DirectionHasher.hpp>
#include <GeomHash_CurveHasher.hpp>
#include <cmath>

//! OCCT-style hasher for Geom_OffsetCurve (3D offset curve).
//! Used for geometry deduplication.
struct GeomHash_OffsetCurveHasher
{
  // Hashes the offset curve by its offset distance, direction, and basis curve.
  std::size_t operator()(const occ::handle<Geom_OffsetCurve>& theCurve) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const GeomHash_DirectionHasher aDirHasher;
    const GeomHash_CurveHasher     aCurveHasher;
    const std::size_t              aHashes[3] = {
      aCurveHasher(theCurve->BasisCurve()),
      opencascade::hash(static_cast<int64_t>(std::round(theCurve->Offset() * aFactor))),
      aDirHasher(theCurve->Direction())};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two offset curves.
  bool operator()(const occ::handle<Geom_OffsetCurve>& theCurve1,
                  const occ::handle<Geom_OffsetCurve>& theCurve2) const noexcept
  {
    constexpr double aTolerance = 1e-12;

    const GeomHash_DirectionHasher aDirHasher;
    const GeomHash_CurveHasher     aCurveHasher;

    return aCurveHasher(theCurve1->BasisCurve(), theCurve2->BasisCurve())
           && std::abs(theCurve1->Offset() - theCurve2->Offset()) <= aTolerance
           && aDirHasher(theCurve1->Direction(), theCurve2->Direction());
  }
};

