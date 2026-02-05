#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_CameraImage.hpp>

class StepVisual_CameraImage3dWithScale : public StepVisual_CameraImage
{

public:
  Standard_EXPORT StepVisual_CameraImage3dWithScale();

  DEFINE_STANDARD_RTTIEXT(StepVisual_CameraImage3dWithScale, StepVisual_CameraImage)
};
