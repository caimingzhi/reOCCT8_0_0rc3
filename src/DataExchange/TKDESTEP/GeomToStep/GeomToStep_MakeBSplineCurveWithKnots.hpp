#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class Geom_BSplineCurve;
class Geom2d_BSplineCurve;
class StepGeom_BSplineCurveWithKnots;

class GeomToStep_MakeBSplineCurveWithKnots : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeBSplineCurveWithKnots(
    const occ::handle<Geom_BSplineCurve>& Bsplin,
    const StepData_Factors&               theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeBSplineCurveWithKnots(
    const occ::handle<Geom2d_BSplineCurve>& Bsplin,
    const StepData_Factors&                 theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_BSplineCurveWithKnots>& Value() const;

private:
  occ::handle<StepGeom_BSplineCurveWithKnots> theBSplineCurveWithKnots;
};
