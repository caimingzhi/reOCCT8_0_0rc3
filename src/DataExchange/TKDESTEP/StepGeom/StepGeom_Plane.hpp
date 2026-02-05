#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_ElementarySurface.hpp>

class StepGeom_Plane : public StepGeom_ElementarySurface
{

public:
  //! Returns a Plane
  Standard_EXPORT StepGeom_Plane();

  DEFINE_STANDARD_RTTIEXT(StepGeom_Plane, StepGeom_ElementarySurface)
};
