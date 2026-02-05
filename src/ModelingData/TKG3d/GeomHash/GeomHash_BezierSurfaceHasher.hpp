#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_BezierSurface.hpp>
#include <GeomHash_PointHasher.hpp>
#include <cmath>

//! OCCT-style hasher for Geom_BezierSurface.
//! Used for geometry deduplication.
//! Hashes only metadata (degrees, pole counts, rationality) for efficiency.
struct GeomHash_BezierSurfaceHasher
{
  // Hashes the Bezier surface metadata only.
  std::size_t operator()(const occ::handle<Geom_BezierSurface>& theSurface) const noexcept
  {
    const std::size_t aHashes[5] = {
      opencascade::hash(theSurface->UDegree()),
      opencascade::hash(theSurface->VDegree()),
      opencascade::hash(theSurface->NbUPoles()),
      opencascade::hash(theSurface->NbVPoles()),
      opencascade::hash(static_cast<int>(theSurface->IsURational())
                        | (static_cast<int>(theSurface->IsVRational()) << 1))};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two Bezier surfaces by full geometric data.
  bool operator()(const occ::handle<Geom_BezierSurface>& theSurface1,
                  const occ::handle<Geom_BezierSurface>& theSurface2) const noexcept
  {
    constexpr double aTolerance = 1e-12;

    // Compare degrees
    if (theSurface1->UDegree() != theSurface2->UDegree()
        || theSurface1->VDegree() != theSurface2->VDegree())
    {
      return false;
    }

    // Compare rationality
    if (theSurface1->IsURational() != theSurface2->IsURational()
        || theSurface1->IsVRational() != theSurface2->IsVRational())
    {
      return false;
    }

    const GeomHash_PointHasher aPointHasher;

    // Compare poles
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

    // Compare weights if rational
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
