#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

class StepShape_EdgeBasedWireframeShapeRepresentation : public StepShape_ShapeRepresentation
{

public:
  Standard_EXPORT StepShape_EdgeBasedWireframeShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_EdgeBasedWireframeShapeRepresentation,
                          StepShape_ShapeRepresentation)
};
