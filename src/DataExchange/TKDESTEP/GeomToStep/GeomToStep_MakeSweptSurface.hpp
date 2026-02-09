#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_SweptSurface;
class Geom_SweptSurface;

class GeomToStep_MakeSweptSurface : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeSweptSurface(
    const occ::handle<Geom_SweptSurface>& S,
    const StepData_Factors&               theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_SweptSurface>& Value() const;

private:
  occ::handle<StepGeom_SweptSurface> theSweptSurface;
};
