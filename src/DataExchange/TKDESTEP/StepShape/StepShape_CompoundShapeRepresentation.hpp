#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

class StepShape_CompoundShapeRepresentation : public StepShape_ShapeRepresentation
{

public:
  Standard_EXPORT StepShape_CompoundShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_CompoundShapeRepresentation, StepShape_ShapeRepresentation)
};
