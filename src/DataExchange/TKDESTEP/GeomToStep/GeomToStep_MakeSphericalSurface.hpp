#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_SphericalSurface;
class Geom_SphericalSurface;

class GeomToStep_MakeSphericalSurface : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeSphericalSurface(
    const occ::handle<Geom_SphericalSurface>& CSurf,
    const StepData_Factors&                   theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_SphericalSurface>& Value() const;

private:
  occ::handle<StepGeom_SphericalSurface> theSphericalSurface;
};
