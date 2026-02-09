#pragma once

#include <Standard_Handle.hpp>
#include <cstddef>

class Geom2d_Curve;

struct Geom2dHash_CurveHasher
{

  Standard_EXPORT std::size_t operator()(const occ::handle<Geom2d_Curve>& theCurve) const noexcept;

  Standard_EXPORT bool operator()(const occ::handle<Geom2d_Curve>& theCurve1,
                                  const occ::handle<Geom2d_Curve>& theCurve2) const noexcept;
};
