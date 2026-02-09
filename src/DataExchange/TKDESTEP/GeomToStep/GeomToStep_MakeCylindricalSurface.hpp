#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_CylindricalSurface;
class Geom_CylindricalSurface;

class GeomToStep_MakeCylindricalSurface : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeCylindricalSurface(
    const occ::handle<Geom_CylindricalSurface>& CSurf,
    const StepData_Factors&                     theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_CylindricalSurface>& Value() const;

private:
  occ::handle<StepGeom_CylindricalSurface> theCylindricalSurface;
};
