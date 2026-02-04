#pragma once


#include <Standard_HashUtils.hpp>
#include <Geom2d_OffsetCurve.hpp>
#include <Geom2dHash_CurveHasher.hpp>
#include <cmath>

//! OCCT-style hasher for Geom2d_OffsetCurve (2D offset curve).
//! Used for geometry deduplication.
struct Geom2dHash_OffsetCurveHasher
{
  // Hashes the offset curve by its offset distance and basis curve.
  std::size_t operator()(const occ::handle<Geom2d_OffsetCurve>& theCurve) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const Geom2dHash_CurveHasher aCurveHasher;
    const std::size_t            aHashes[2] = {
      aCurveHasher(theCurve->BasisCurve()),
      opencascade::hash(static_cast<int64_t>(std::round(theCurve->Offset() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two offset curves.
  bool operator()(const occ::handle<Geom2d_OffsetCurve>& theCurve1,
                  const occ::handle<Geom2d_OffsetCurve>& theCurve2) const noexcept
  {
    constexpr double aTolerance = 1e-12;

    const Geom2dHash_CurveHasher aCurveHasher;

    return aCurveHasher(theCurve1->BasisCurve(), theCurve2->BasisCurve())
           && std::abs(theCurve1->Offset() - theCurve2->Offset()) <= aTolerance;
  }
};

