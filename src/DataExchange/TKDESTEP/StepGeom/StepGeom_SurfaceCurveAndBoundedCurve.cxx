#include <StepGeom_BoundedCurve.hpp>
#include <StepGeom_SurfaceCurveAndBoundedCurve.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_SurfaceCurveAndBoundedCurve, StepGeom_SurfaceCurve)

StepGeom_SurfaceCurveAndBoundedCurve::StepGeom_SurfaceCurveAndBoundedCurve() = default;

occ::handle<StepGeom_BoundedCurve>& StepGeom_SurfaceCurveAndBoundedCurve::BoundedCurve()
{
  return myBoundedCurve;
}
