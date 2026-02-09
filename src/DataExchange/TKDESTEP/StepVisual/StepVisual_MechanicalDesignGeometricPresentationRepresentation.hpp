#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_PresentationRepresentation.hpp>

class StepVisual_MechanicalDesignGeometricPresentationRepresentation
    : public StepVisual_PresentationRepresentation
{

public:
  Standard_EXPORT StepVisual_MechanicalDesignGeometricPresentationRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepVisual_MechanicalDesignGeometricPresentationRepresentation,
                          StepVisual_PresentationRepresentation)
};
