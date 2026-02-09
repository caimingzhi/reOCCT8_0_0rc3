#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_BSplineSurface.hpp>

class StepGeom_BezierSurface : public StepGeom_BSplineSurface
{

public:
  Standard_EXPORT StepGeom_BezierSurface();

  DEFINE_STANDARD_RTTIEXT(StepGeom_BezierSurface, StepGeom_BSplineSurface)
};
