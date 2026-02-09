#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_SurfaceOfRevolution;
class Geom_SurfaceOfRevolution;

class GeomToStep_MakeSurfaceOfRevolution : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeSurfaceOfRevolution(
    const occ::handle<Geom_SurfaceOfRevolution>& RevSurf,
    const StepData_Factors&                      theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_SurfaceOfRevolution>& Value() const;

private:
  occ::handle<StepGeom_SurfaceOfRevolution> theSurfaceOfRevolution;
};
