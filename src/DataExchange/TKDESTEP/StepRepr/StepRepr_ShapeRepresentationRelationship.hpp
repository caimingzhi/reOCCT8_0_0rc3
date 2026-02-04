#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationRelationship.hpp>

class StepRepr_ShapeRepresentationRelationship : public StepRepr_RepresentationRelationship
{

public:
  Standard_EXPORT StepRepr_ShapeRepresentationRelationship();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ShapeRepresentationRelationship,
                          StepRepr_RepresentationRelationship)
};

