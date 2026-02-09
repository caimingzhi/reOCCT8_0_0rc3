#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2dHash_PointHasher.hpp>
#include <cmath>

struct Geom2dHash_BSplineCurveHasher
{

  std::size_t operator()(const occ::handle<Geom2d_BSplineCurve>& theCurve) const noexcept
  {
    const std::size_t aHashes[4] = {opencascade::hash(theCurve->Degree()),
                                    opencascade::hash(theCurve->NbPoles()),
                                    opencascade::hash(theCurve->NbKnots()),
                                    opencascade::hash(static_cast<int>(theCurve->IsRational()))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<Geom2d_BSplineCurve>& theCurve1,
                  const occ::handle<Geom2d_BSplineCurve>& theCurve2) const noexcept
  {
    constexpr double aTolerance = 1e-12;

    if (theCurve1->Degree() != theCurve2->Degree())
    {
      return false;
    }

    if (theCurve1->NbKnots() != theCurve2->NbKnots())
    {
      return false;
    }

    for (int i = 1; i <= theCurve1->NbKnots(); ++i)
    {
      if (std::abs(theCurve1->Knot(i) - theCurve2->Knot(i)) > aTolerance
          || theCurve1->Multiplicity(i) != theCurve2->Multiplicity(i))
      {
        return false;
      }
    }

    if (theCurve1->IsRational() != theCurve2->IsRational())
    {
      return false;
    }

    const Geom2dHash_PointHasher aPointHasher;

    for (int i = 1; i <= theCurve1->NbPoles(); ++i)
    {
      if (!aPointHasher(theCurve1->Pole(i), theCurve2->Pole(i)))
      {
        return false;
      }
    }

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
