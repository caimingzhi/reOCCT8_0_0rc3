#pragma once

#include <Standard_Handle.hpp>
#include <cstddef>

class Geom_Surface;

struct GeomHash_SurfaceHasher
{

  Standard_EXPORT std::size_t operator()(
    const occ::handle<Geom_Surface>& theSurface) const noexcept;

  Standard_EXPORT bool operator()(const occ::handle<Geom_Surface>& theSurface1,
                                  const occ::handle<Geom_Surface>& theSurface2) const noexcept;
};
