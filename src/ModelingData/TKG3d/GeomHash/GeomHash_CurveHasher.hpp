#pragma once


#include <Standard_Handle.hpp>
#include <cstddef>

class Geom_Curve;

//! Polymorphic hasher for Geom_Curve using RTTI dispatch.
//! Used for geometry deduplication.
struct GeomHash_CurveHasher
{
  // Hashes any Geom_Curve by dispatching to the appropriate specific hasher.
  Standard_EXPORT std::size_t operator()(const occ::handle<Geom_Curve>& theCurve) const noexcept;

  // Compares two curves using polymorphic dispatch.
  Standard_EXPORT bool operator()(const occ::handle<Geom_Curve>& theCurve1,
                                  const occ::handle<Geom_Curve>& theCurve2) const noexcept;
};

