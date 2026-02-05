#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_Line.hpp>
#include <GeomHash_PointHasher.hpp>
#include <GeomHash_DirectionHasher.hpp>

//! OCCT-style hasher for Geom_Line (3D line).
//! Used for geometry deduplication.
struct GeomHash_LineHasher
{
  // Hashes the line by its location and direction.
  std::size_t operator()(const occ::handle<Geom_Line>& theLine) const noexcept
  {
    const GeomHash_PointHasher     aPointHasher;
    const GeomHash_DirectionHasher aDirHasher;

    const std::size_t aHashes[2] = {aPointHasher(theLine->Position().Location()),
                                    aDirHasher(theLine->Position().Direction())};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two lines by their positions.
  bool operator()(const occ::handle<Geom_Line>& theLine1,
                  const occ::handle<Geom_Line>& theLine2) const noexcept
  {
    const GeomHash_PointHasher     aPointHasher;
    const GeomHash_DirectionHasher aDirHasher;

    return aPointHasher(theLine1->Position().Location(), theLine2->Position().Location())
           && aDirHasher(theLine1->Position().Direction(), theLine2->Position().Direction());
  }
};
