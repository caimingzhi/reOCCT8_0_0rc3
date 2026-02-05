#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_BSplineSurface.hpp>

class StepGeom_UniformSurface : public StepGeom_BSplineSurface
{

public:
  //! Returns a UniformSurface
  Standard_EXPORT StepGeom_UniformSurface();

  DEFINE_STANDARD_RTTIEXT(StepGeom_UniformSurface, StepGeom_BSplineSurface)
};
