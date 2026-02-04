#pragma once


#include <Standard_HashUtils.hpp>
#include <Geom_Plane.hpp>
#include <GeomHash_AxisPlacement.hpp>

//! OCCT-style hasher for Geom_Plane surfaces.
//! Used for geometry deduplication.
struct GeomHash_PlaneHasher
{
  // Hashes the plane by its position (location, normal, reference direction).
  std::size_t operator()(const occ::handle<Geom_Plane>& thePlane) const noexcept
  {
    const GeomHash_AxisPlacement anAxisHasher;
    return anAxisHasher(thePlane->Position().Ax2());
  }

  // Compares two planes by their positions.
  bool operator()(const occ::handle<Geom_Plane>& thePlane1,
                  const occ::handle<Geom_Plane>& thePlane2) const noexcept
  {
    const GeomHash_AxisPlacement anAxisHasher;
    return anAxisHasher(thePlane1->Position().Ax2(), thePlane2->Position().Ax2());
  }
};

