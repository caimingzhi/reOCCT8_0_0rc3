#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_BoundedCurve;
class Geom_BoundedCurve;
class Geom2d_BoundedCurve;

class GeomToStep_MakeBoundedCurve : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeBoundedCurve(
    const occ::handle<Geom_BoundedCurve>& C,
    const StepData_Factors&               theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeBoundedCurve(
    const occ::handle<Geom2d_BoundedCurve>& C,
    const StepData_Factors&                 theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_BoundedCurve>& Value() const;

private:
  occ::handle<StepGeom_BoundedCurve> theBoundedCurve;
};
