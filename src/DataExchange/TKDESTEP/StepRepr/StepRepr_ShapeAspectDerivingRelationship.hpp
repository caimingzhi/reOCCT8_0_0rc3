#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspectRelationship.hpp>

//! Added for Dimensional Tolerances
class StepRepr_ShapeAspectDerivingRelationship : public StepRepr_ShapeAspectRelationship
{

public:
  Standard_EXPORT StepRepr_ShapeAspectDerivingRelationship();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ShapeAspectDerivingRelationship,
                          StepRepr_ShapeAspectRelationship)
};

