#pragma once

#include <Standard_HashUtils.hpp>
#include <gp_Ax2.hpp>
#include <GeomHash_PointHasher.hpp>
#include <GeomHash_DirectionHasher.hpp>

struct GeomHash_AxisPlacement
{

  std::size_t operator()(const gp_Ax2& theAxisPlacement) const noexcept
  {
    const GeomHash_PointHasher     aPointHasher;
    const GeomHash_DirectionHasher aDirectionHasher;

    const std::size_t aHashes[3] = {aPointHasher(theAxisPlacement.Location()),
                                    aDirectionHasher(theAxisPlacement.Direction()),
                                    aDirectionHasher(theAxisPlacement.XDirection())};

    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const gp_Ax2& theAxisPlacement1, const gp_Ax2& theAxisPlacement2) const noexcept
  {
    const GeomHash_PointHasher     aPointHasher;
    const GeomHash_DirectionHasher aDirectionHasher;

    return aPointHasher(theAxisPlacement1.Location(), theAxisPlacement2.Location())
           && aDirectionHasher(theAxisPlacement1.Direction(), theAxisPlacement2.Direction())
           && aDirectionHasher(theAxisPlacement1.XDirection(), theAxisPlacement2.XDirection());
  }
};
