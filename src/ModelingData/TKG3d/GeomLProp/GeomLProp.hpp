#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_Shape.hpp>
class Geom_Curve;

class GeomLProp
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static GeomAbs_Shape Continuity(const occ::handle<Geom_Curve>& C1,
                                                  const occ::handle<Geom_Curve>& C2,
                                                  const double                   u1,
                                                  const double                   u2,
                                                  const bool                     r1,
                                                  const bool                     r2,
                                                  const double                   tl,
                                                  const double                   ta);

  Standard_EXPORT static GeomAbs_Shape Continuity(const occ::handle<Geom_Curve>& C1,
                                                  const occ::handle<Geom_Curve>& C2,
                                                  const double                   u1,
                                                  const double                   u2,
                                                  const bool                     r1,
                                                  const bool                     r2);
};
