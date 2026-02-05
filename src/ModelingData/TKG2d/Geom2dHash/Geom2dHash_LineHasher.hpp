#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2dHash_PointHasher.hpp>
#include <Geom2dHash_DirectionHasher.hpp>

//! OCCT-style hasher for Geom2d_Line (2D line).
//! Used for geometry deduplication.
struct Geom2dHash_LineHasher
{
  // Hashes the line by its location and direction.
  std::size_t operator()(const occ::handle<Geom2d_Line>& theLine) const noexcept
  {
    const Geom2dHash_PointHasher     aPointHasher;
    const Geom2dHash_DirectionHasher aDirHasher;

    const std::size_t aHashes[2] = {aPointHasher(theLine->Position().Location()),
                                    aDirHasher(theLine->Position().Direction())};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two lines by their positions.
  bool operator()(const occ::handle<Geom2d_Line>& theLine1,
                  const occ::handle<Geom2d_Line>& theLine2) const noexcept
  {
    const Geom2dHash_PointHasher     aPointHasher;
    const Geom2dHash_DirectionHasher aDirHasher;

    return aPointHasher(theLine1->Position().Location(), theLine2->Position().Location())
           && aDirHasher(theLine1->Position().Direction(), theLine2->Position().Direction());
  }
};
