#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_SurfaceCurve.hpp>
class StepGeom_BoundedCurve;

//! complex type: bounded_curve + surface_curve
//! needed for curve_bounded_surfaces (S4132)
class StepGeom_SurfaceCurveAndBoundedCurve : public StepGeom_SurfaceCurve
{

public:
  //! creates empty object
  Standard_EXPORT StepGeom_SurfaceCurveAndBoundedCurve();

  //! returns field BoundedCurve
  Standard_EXPORT occ::handle<StepGeom_BoundedCurve>& BoundedCurve();

  DEFINE_STANDARD_RTTIEXT(StepGeom_SurfaceCurveAndBoundedCurve, StepGeom_SurfaceCurve)

private:
  occ::handle<StepGeom_BoundedCurve> myBoundedCurve;
};
