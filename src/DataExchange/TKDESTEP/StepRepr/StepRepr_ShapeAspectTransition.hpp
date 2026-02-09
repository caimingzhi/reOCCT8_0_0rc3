#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspectRelationship.hpp>

class StepRepr_ShapeAspectTransition : public StepRepr_ShapeAspectRelationship
{

public:
  Standard_EXPORT StepRepr_ShapeAspectTransition();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ShapeAspectTransition, StepRepr_ShapeAspectRelationship)
};
