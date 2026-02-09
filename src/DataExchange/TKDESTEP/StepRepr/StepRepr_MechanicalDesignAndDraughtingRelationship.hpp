#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationRelationship.hpp>

class StepRepr_MechanicalDesignAndDraughtingRelationship
    : public StepRepr_RepresentationRelationship
{
public:
  Standard_EXPORT StepRepr_MechanicalDesignAndDraughtingRelationship();

  DEFINE_STANDARD_RTTIEXT(StepRepr_MechanicalDesignAndDraughtingRelationship,
                          StepRepr_RepresentationRelationship)
};
