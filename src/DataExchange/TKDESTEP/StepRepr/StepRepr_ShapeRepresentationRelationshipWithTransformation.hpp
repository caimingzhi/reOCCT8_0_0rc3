#pragma once

#include <Standard.hpp>

#include <StepRepr_RepresentationRelationshipWithTransformation.hpp>

class StepRepr_ShapeRepresentationRelationshipWithTransformation
    : public StepRepr_RepresentationRelationshipWithTransformation
{

public:
  Standard_EXPORT StepRepr_ShapeRepresentationRelationshipWithTransformation();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ShapeRepresentationRelationshipWithTransformation,
                          StepRepr_RepresentationRelationshipWithTransformation)
};
