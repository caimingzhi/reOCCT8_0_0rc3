#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepShape_ShapeRepresentation.hpp>

class StepVisual_TessellatedShapeRepresentation : public StepShape_ShapeRepresentation
{

public:
  Standard_EXPORT StepVisual_TessellatedShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedShapeRepresentation, StepShape_ShapeRepresentation)
};
