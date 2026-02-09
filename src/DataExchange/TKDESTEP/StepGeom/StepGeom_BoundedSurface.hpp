#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_Surface.hpp>

class StepGeom_BoundedSurface : public StepGeom_Surface
{

public:
  Standard_EXPORT StepGeom_BoundedSurface();

  DEFINE_STANDARD_RTTIEXT(StepGeom_BoundedSurface, StepGeom_Surface)
};
