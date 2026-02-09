#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom_Plane;

class ShapeBuild
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Geom_Plane> PlaneXOY();
};
