#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dHash_CurveHasher.hpp>
#include <cmath>

//! OCCT-style hasher for Geom2d_TrimmedCurve (2D trimmed curve).
//! Used for geometry deduplication.
struct Geom2dHash_TrimmedCurveHasher
{
  // Hashes the trimmed curve by its parameters and basis curve.
  std::size_t operator()(const occ::handle<Geom2d_TrimmedCurve>& theCurve) const noexcept
  {
    constexpr double aTolerance = 1e-12;
    constexpr double aFactor    = 1.0 / aTolerance;

    const Geom2dHash_CurveHasher aCurveHasher;
    const std::size_t            aHashes[3] = {
      aCurveHasher(theCurve->BasisCurve()),
      opencascade::hash(static_cast<int64_t>(std::round(theCurve->FirstParameter() * aFactor))),
      opencascade::hash(static_cast<int64_t>(std::round(theCurve->LastParameter() * aFactor)))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two trimmed curves.
  bool operator()(const occ::handle<Geom2d_TrimmedCurve>& theCurve1,
                  const occ::handle<Geom2d_TrimmedCurve>& theCurve2) const noexcept
  {
    constexpr double aTolerance = 1e-12;

    const Geom2dHash_CurveHasher aCurveHasher;

    return aCurveHasher(theCurve1->BasisCurve(), theCurve2->BasisCurve())
           && std::abs(theCurve1->FirstParameter() - theCurve2->FirstParameter()) <= aTolerance
           && std::abs(theCurve1->LastParameter() - theCurve2->LastParameter()) <= aTolerance;
  }
};
