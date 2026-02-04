#pragma once


#include <Standard_Handle.hpp>
#include <cstddef>

class Geom_Surface;

//! Polymorphic hasher for Geom_Surface using RTTI dispatch.
//! Used for geometry deduplication.
struct GeomHash_SurfaceHasher
{
  // Hashes any Geom_Surface by dispatching to the appropriate specific hasher.
  Standard_EXPORT std::size_t operator()(
    const occ::handle<Geom_Surface>& theSurface) const noexcept;

  // Compares two surfaces using polymorphic dispatch.
  Standard_EXPORT bool operator()(const occ::handle<Geom_Surface>& theSurface1,
                                  const occ::handle<Geom_Surface>& theSurface2) const noexcept;
};

