#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom2d_Curve;
class Adaptor2d_Curve2d;

class Geom2dAdaptor
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Geom2d_Curve> MakeCurve(const Adaptor2d_Curve2d& HC);
};
