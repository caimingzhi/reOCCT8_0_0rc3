#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_BSplineSurface.hpp>
#include <GeomHash_PointHasher.hpp>
#include <cmath>

struct GeomHash_BSplineSurfaceHasher
{

  std::size_t operator()(const occ::handle<Geom_BSplineSurface>& theSurface) const noexcept
  {
    const std::size_t aHashes[7] = {
      opencascade::hash(theSurface->UDegree()),
      opencascade::hash(theSurface->VDegree()),
      opencascade::hash(theSurface->NbUPoles()),
      opencascade::hash(theSurface->NbVPoles()),
      opencascade::hash(theSurface->NbUKnots()),
      opencascade::hash(theSurface->NbVKnots()),
      opencascade::hash(static_cast<int>(theSurface->IsURational())
                        | (static_cast<int>(theSurface->IsVRational()) << 1))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<Geom_BSplineSurface>& theSurface1,
                  const occ::handle<Geom_BSplineSurface>& theSurface2) const noexcept
  {
    constexpr double aTolerance = 1e-12;

    if (theSurface1->UDegree() != theSurface2->UDegree()
        || theSurface1->VDegree() != theSurface2->VDegree())
    {
      return false;
    }

    if (theSurface1->NbUKnots() != theSurface2->NbUKnots()
        || theSurface1->NbVKnots() != theSurface2->NbVKnots())
    {
      return false;
    }

    for (int i = 1; i <= theSurface1->NbUKnots(); ++i)
    {
      if (std::abs(theSurface1->UKnot(i) - theSurface2->UKnot(i)) > aTolerance
          || theSurface1->UMultiplicity(i) != theSurface2->UMultiplicity(i))
      {
        return false;
      }
    }

    for (int i = 1; i <= theSurface1->NbVKnots(); ++i)
    {
      if (std::abs(theSurface1->VKnot(i) - theSurface2->VKnot(i)) > aTolerance
          || theSurface1->VMultiplicity(i) != theSurface2->VMultiplicity(i))
      {
        return false;
      }
    }

    if (theSurface1->IsURational() != theSurface2->IsURational()
        || theSurface1->IsVRational() != theSurface2->IsVRational())
    {
      return false;
    }

    const GeomHash_PointHasher aPointHasher;

    for (int i = 1; i <= theSurface1->NbUPoles(); ++i)
    {
      for (int j = 1; j <= theSurface1->NbVPoles(); ++j)
      {
        if (!aPointHasher(theSurface1->Pole(i, j), theSurface2->Pole(i, j)))
        {
          return false;
        }
      }
    }

    if (theSurface1->IsURational() || theSurface1->IsVRational())
    {
      for (int i = 1; i <= theSurface1->NbUPoles(); ++i)
      {
        for (int j = 1; j <= theSurface1->NbVPoles(); ++j)
        {
          if (std::abs(theSurface1->Weight(i, j) - theSurface2->Weight(i, j)) > aTolerance)
          {
            return false;
          }
        }
      }
    }

    return true;
  }
};
