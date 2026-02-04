#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ShapeRepresentation.hpp>

class StepShape_TransitionalShapeRepresentation : public StepShape_ShapeRepresentation
{

public:
  //! Returns a TransitionalShapeRepresentation
  Standard_EXPORT StepShape_TransitionalShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_TransitionalShapeRepresentation, StepShape_ShapeRepresentation)
};

