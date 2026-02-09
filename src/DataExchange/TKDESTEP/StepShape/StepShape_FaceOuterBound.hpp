#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_FaceBound.hpp>

class StepShape_FaceOuterBound : public StepShape_FaceBound
{

public:
  Standard_EXPORT StepShape_FaceOuterBound();

  DEFINE_STANDARD_RTTIEXT(StepShape_FaceOuterBound, StepShape_FaceBound)
};
