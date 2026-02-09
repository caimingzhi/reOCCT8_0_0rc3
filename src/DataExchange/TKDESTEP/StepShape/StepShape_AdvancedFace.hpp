#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_FaceSurface.hpp>

class StepShape_AdvancedFace : public StepShape_FaceSurface
{

public:
  Standard_EXPORT StepShape_AdvancedFace();

  DEFINE_STANDARD_RTTIEXT(StepShape_AdvancedFace, StepShape_FaceSurface)
};
