#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom_Curve;
class Adaptor3d_Curve;
class Geom_Surface;
class Adaptor3d_Surface;

class GeomAdaptor
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Geom_Curve> MakeCurve(const Adaptor3d_Curve& C);

  Standard_EXPORT static occ::handle<Geom_Surface> MakeSurface(const Adaptor3d_Surface& theS,
                                                               const bool theTrimFlag = true);
};
