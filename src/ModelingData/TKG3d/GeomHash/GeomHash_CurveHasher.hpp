#pragma once

#include <Standard_Handle.hpp>
#include <cstddef>

class Geom_Curve;

struct GeomHash_CurveHasher
{

  Standard_EXPORT std::size_t operator()(const occ::handle<Geom_Curve>& theCurve) const noexcept;

  Standard_EXPORT bool operator()(const occ::handle<Geom_Curve>& theCurve1,
                                  const occ::handle<Geom_Curve>& theCurve2) const noexcept;
};
