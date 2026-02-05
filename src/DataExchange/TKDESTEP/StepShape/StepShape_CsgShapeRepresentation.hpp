#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

class StepShape_CsgShapeRepresentation : public StepShape_ShapeRepresentation
{

public:
  //! Returns a CsgShapeRepresentation
  Standard_EXPORT StepShape_CsgShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_CsgShapeRepresentation, StepShape_ShapeRepresentation)
};
