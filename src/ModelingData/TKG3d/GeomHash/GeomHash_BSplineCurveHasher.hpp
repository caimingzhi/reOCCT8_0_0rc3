#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_BSplineCurve.hpp>
#include <GeomHash_PointHasher.hpp>
#include <cmath>

//! OCCT-style hasher for Geom_BSplineCurve (3D B-spline curve).
//! Used for geometry deduplication.
//! Hashes only metadata (degree, pole count, knot count, rationality) for efficiency.
struct GeomHash_BSplineCurveHasher
{
  // Hashes the B-spline curve metadata only.
  std::size_t operator()(const occ::handle<Geom_BSplineCurve>& theCurve) const noexcept
  {
    const std::size_t aHashes[4] = {opencascade::hash(theCurve->Degree()),
                                    opencascade::hash(theCurve->NbPoles()),
                                    opencascade::hash(theCurve->NbKnots()),
                                    opencascade::hash(static_cast<int>(theCurve->IsRational()))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two B-spline curves by full geometric data.
  bool operator()(const occ::handle<Geom_BSplineCurve>& theCurve1,
                  const occ::handle<Geom_BSplineCurve>& theCurve2) const noexcept
  {
    constexpr double aTolerance = 1e-12;

    // Compare degrees
    if (theCurve1->Degree() != theCurve2->Degree())
    {
      return false;
    }

    // Compare knot counts
    if (theCurve1->NbKnots() != theCurve2->NbKnots())
    {
      return false;
    }

    // Compare knots and multiplicities
    for (int i = 1; i <= theCurve1->NbKnots(); ++i)
    {
      if (std::abs(theCurve1->Knot(i) - theCurve2->Knot(i)) > aTolerance
          || theCurve1->Multiplicity(i) != theCurve2->Multiplicity(i))
      {
        return false;
      }
    }

    // Compare rationality
    if (theCurve1->IsRational() != theCurve2->IsRational())
    {
      return false;
    }

    const GeomHash_PointHasher aPointHasher;

    // Compare poles
    for (int i = 1; i <= theCurve1->NbPoles(); ++i)
    {
      if (!aPointHasher(theCurve1->Pole(i), theCurve2->Pole(i)))
      {
        return false;
      }
    }

    // Compare weights if rational
    if (theCurve1->IsRational())
    {
      for (int i = 1; i <= theCurve1->NbPoles(); ++i)
      {
        if (std::abs(theCurve1->Weight(i) - theCurve2->Weight(i)) > aTolerance)
        {
          return false;
        }
      }
    }

    return true;
  }
};
