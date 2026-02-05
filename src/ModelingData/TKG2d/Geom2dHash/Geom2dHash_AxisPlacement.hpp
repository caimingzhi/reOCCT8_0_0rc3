#pragma once

#include <Standard_HashUtils.hpp>
#include <gp_Ax22d.hpp>
#include <Geom2dHash_PointHasher.hpp>
#include <Geom2dHash_DirectionHasher.hpp>

//! OCCT-style hasher for gp_Ax22d (2D coordinate system).
//! Used for geometry deduplication.
struct Geom2dHash_AxisPlacement
{
  // Hashes a 2D axis placement by its location, X direction, and Y direction.
  std::size_t operator()(const gp_Ax22d& theAxisPlacement) const noexcept
  {
    const Geom2dHash_PointHasher     aPointHasher;
    const Geom2dHash_DirectionHasher aDirHasher;

    const std::size_t aHashes[3] = {aPointHasher(theAxisPlacement.Location()),
                                    aDirHasher(theAxisPlacement.XDirection()),
                                    aDirHasher(theAxisPlacement.YDirection())};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two 2D axis placements.
  bool operator()(const gp_Ax22d& theAxisPlacement1,
                  const gp_Ax22d& theAxisPlacement2) const noexcept
  {
    const Geom2dHash_PointHasher     aPointHasher;
    const Geom2dHash_DirectionHasher aDirHasher;

    return aPointHasher(theAxisPlacement1.Location(), theAxisPlacement2.Location())
           && aDirHasher(theAxisPlacement1.XDirection(), theAxisPlacement2.XDirection())
           && aDirHasher(theAxisPlacement1.YDirection(), theAxisPlacement2.YDirection());
  }
};
