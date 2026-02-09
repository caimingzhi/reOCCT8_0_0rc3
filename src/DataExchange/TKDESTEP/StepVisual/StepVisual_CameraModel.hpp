#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>

class StepVisual_CameraModel : public StepGeom_GeometricRepresentationItem
{

public:
  Standard_EXPORT StepVisual_CameraModel();

  DEFINE_STANDARD_RTTIEXT(StepVisual_CameraModel, StepGeom_GeometricRepresentationItem)
};
