#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_MappedItem.hpp>

class StepVisual_CameraImage : public StepRepr_MappedItem
{

public:
  //! Returns a CameraImage
  Standard_EXPORT StepVisual_CameraImage();

  DEFINE_STANDARD_RTTIEXT(StepVisual_CameraImage, StepRepr_MappedItem)
};

