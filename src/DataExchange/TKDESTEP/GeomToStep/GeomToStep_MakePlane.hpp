#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_Plane;
class gp_Pln;
class Geom_Plane;

class GeomToStep_MakePlane : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakePlane(
    const gp_Pln&           P,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakePlane(
    const occ::handle<Geom_Plane>& P,
    const StepData_Factors&        theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Plane>& Value() const;

private:
  occ::handle<StepGeom_Plane> thePlane;
};
