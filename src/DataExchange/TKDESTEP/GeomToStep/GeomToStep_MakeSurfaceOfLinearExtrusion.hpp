#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_SurfaceOfLinearExtrusion;
class Geom_SurfaceOfLinearExtrusion;

class GeomToStep_MakeSurfaceOfLinearExtrusion : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeSurfaceOfLinearExtrusion(
    const occ::handle<Geom_SurfaceOfLinearExtrusion>& CSurf,
    const StepData_Factors&                           theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_SurfaceOfLinearExtrusion>& Value() const;

private:
  occ::handle<StepGeom_SurfaceOfLinearExtrusion> theSurfaceOfLinearExtrusion;
};
