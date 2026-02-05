#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_Representation.hpp>

class StepShape_ShapeRepresentation : public StepRepr_Representation
{

public:
  //! Returns a ShapeRepresentation
  Standard_EXPORT StepShape_ShapeRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepShape_ShapeRepresentation, StepRepr_Representation)
};
