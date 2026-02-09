#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_BSplineSurface.hpp>

class StepGeom_QuasiUniformSurface : public StepGeom_BSplineSurface
{

public:
  Standard_EXPORT StepGeom_QuasiUniformSurface();

  DEFINE_STANDARD_RTTIEXT(StepGeom_QuasiUniformSurface, StepGeom_BSplineSurface)
};
