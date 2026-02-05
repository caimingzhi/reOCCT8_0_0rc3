#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_PresentationArea.hpp>

class StepVisual_MechanicalDesignGeometricPresentationArea : public StepVisual_PresentationArea
{

public:
  //! Returns a MechanicalDesignGeometricPresentationArea
  Standard_EXPORT StepVisual_MechanicalDesignGeometricPresentationArea();

  DEFINE_STANDARD_RTTIEXT(StepVisual_MechanicalDesignGeometricPresentationArea,
                          StepVisual_PresentationArea)
};
