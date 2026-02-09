#pragma once

#include <Standard_HashUtils.hpp>
#include <Geom_Plane.hpp>
#include <GeomHash_AxisPlacement.hpp>

struct GeomHash_PlaneHasher
{

  std::size_t operator()(const occ::handle<Geom_Plane>& thePlane) const noexcept
  {
    const GeomHash_AxisPlacement anAxisHasher;
    return anAxisHasher(thePlane->Position().Ax2());
  }

  bool operator()(const occ::handle<Geom_Plane>& thePlane1,
                  const occ::handle<Geom_Plane>& thePlane2) const noexcept
  {
    const GeomHash_AxisPlacement anAxisHasher;
    return anAxisHasher(thePlane1->Position().Ax2(), thePlane2->Position().Ax2());
  }
};
