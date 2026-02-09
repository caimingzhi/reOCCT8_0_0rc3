#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_Conic;
class Geom_Conic;
class Geom2d_Conic;

class GeomToStep_MakeConic : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeConic(
    const occ::handle<Geom_Conic>& C,
    const StepData_Factors&        theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeConic(
    const occ::handle<Geom2d_Conic>& C,
    const StepData_Factors&          theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Conic>& Value() const;

private:
  occ::handle<StepGeom_Conic> theConic;
};
