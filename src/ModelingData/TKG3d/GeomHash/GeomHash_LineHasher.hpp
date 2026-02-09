#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_Line.hpp>
#include <GeomHash_PointHasher.hpp>
#include <GeomHash_DirectionHasher.hpp>

struct GeomHash_LineHasher
{

  std::size_t operator()(const occ::handle<Geom_Line>& theLine) const noexcept
  {
    const GeomHash_PointHasher     aPointHasher;
    const GeomHash_DirectionHasher aDirHasher;

    const std::size_t aHashes[2] = {aPointHasher(theLine->Position().Location()),
                                    aDirHasher(theLine->Position().Direction())};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<Geom_Line>& theLine1,
                  const occ::handle<Geom_Line>& theLine2) const noexcept
  {
    const GeomHash_PointHasher     aPointHasher;
    const GeomHash_DirectionHasher aDirHasher;

    return aPointHasher(theLine1->Position().Location(), theLine2->Position().Location())
           && aDirHasher(theLine1->Position().Direction(), theLine2->Position().Direction());
  }
};
