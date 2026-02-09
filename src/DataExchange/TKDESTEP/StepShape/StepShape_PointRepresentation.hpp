#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

class StepShape_PointRepresentation : public StepShape_ShapeRepresentation
{

public:
  Standard_EXPORT StepShape_PointRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_PointRepresentation, StepShape_ShapeRepresentation)
};
