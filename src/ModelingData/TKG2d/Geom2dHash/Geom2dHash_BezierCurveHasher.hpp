#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2dHash_PointHasher.hpp>
#include <cmath>

struct Geom2dHash_BezierCurveHasher
{

  std::size_t operator()(const occ::handle<Geom2d_BezierCurve>& theCurve) const noexcept
  {
    const std::size_t aHashes[3] = {opencascade::hash(theCurve->Degree()),
                                    opencascade::hash(theCurve->NbPoles()),
                                    opencascade::hash(static_cast<int>(theCurve->IsRational()))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<Geom2d_BezierCurve>& theCurve1,
                  const occ::handle<Geom2d_BezierCurve>& theCurve2) const noexcept
  {
    constexpr double aTolerance = 1e-12;

    if (theCurve1->Degree() != theCurve2->Degree())
    {
      return false;
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
