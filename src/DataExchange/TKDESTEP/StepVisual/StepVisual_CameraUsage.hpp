#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationMap.hpp>

class StepVisual_CameraUsage : public StepRepr_RepresentationMap
{

public:
  //! Returns a CameraUsage
  Standard_EXPORT StepVisual_CameraUsage();

  DEFINE_STANDARD_RTTIEXT(StepVisual_CameraUsage, StepRepr_RepresentationMap)
};

