#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

class StepShape_AdvancedBrepShapeRepresentation : public StepShape_ShapeRepresentation
{

public:
  //! Returns a AdvancedBrepShapeRepresentation
  Standard_EXPORT StepShape_AdvancedBrepShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_AdvancedBrepShapeRepresentation, StepShape_ShapeRepresentation)
};
