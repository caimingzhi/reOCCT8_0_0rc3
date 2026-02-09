#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

class StepShape_GeometricallyBoundedWireframeShapeRepresentation
    : public StepShape_ShapeRepresentation
{

public:
  Standard_EXPORT StepShape_GeometricallyBoundedWireframeShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_GeometricallyBoundedWireframeShapeRepresentation,
                          StepShape_ShapeRepresentation)
};
