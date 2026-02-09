#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_BSplineCurve.hpp>

class StepGeom_UniformCurve : public StepGeom_BSplineCurve
{

public:
  Standard_EXPORT StepGeom_UniformCurve();

  DEFINE_STANDARD_RTTIEXT(StepGeom_UniformCurve, StepGeom_BSplineCurve)
};
