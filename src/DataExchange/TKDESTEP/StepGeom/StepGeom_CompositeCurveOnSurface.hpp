#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_CompositeCurve.hpp>

class StepGeom_CompositeCurveOnSurface : public StepGeom_CompositeCurve
{

public:
  //! Returns a CompositeCurveOnSurface
  Standard_EXPORT StepGeom_CompositeCurveOnSurface();

  DEFINE_STANDARD_RTTIEXT(StepGeom_CompositeCurveOnSurface, StepGeom_CompositeCurve)
};
