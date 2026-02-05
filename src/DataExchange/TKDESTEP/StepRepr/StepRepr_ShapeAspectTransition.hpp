#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspectRelationship.hpp>

//! Representation of STEP entity ShapeAspectTransition
class StepRepr_ShapeAspectTransition : public StepRepr_ShapeAspectRelationship
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_ShapeAspectTransition();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ShapeAspectTransition, StepRepr_ShapeAspectRelationship)
};
