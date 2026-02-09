#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_SurfaceCurve.hpp>
class StepGeom_BoundedCurve;

class StepGeom_SurfaceCurveAndBoundedCurve : public StepGeom_SurfaceCurve
{

public:
  Standard_EXPORT StepGeom_SurfaceCurveAndBoundedCurve();

  Standard_EXPORT occ::handle<StepGeom_BoundedCurve>& BoundedCurve();

  DEFINE_STANDARD_RTTIEXT(StepGeom_SurfaceCurveAndBoundedCurve, StepGeom_SurfaceCurve)

private:
  occ::handle<StepGeom_BoundedCurve> myBoundedCurve;
};
