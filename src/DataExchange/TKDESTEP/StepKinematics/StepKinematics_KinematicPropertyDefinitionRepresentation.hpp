#pragma once

#include <Standard.hpp>
#include <StepRepr_PropertyDefinitionRepresentation.hpp>

#include <StepRepr_RepresentedDefinition.hpp>
#include <StepRepr_Representation.hpp>

class StepKinematics_KinematicPropertyDefinitionRepresentation
    : public StepRepr_PropertyDefinitionRepresentation
{
public:
  Standard_EXPORT StepKinematics_KinematicPropertyDefinitionRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_KinematicPropertyDefinitionRepresentation,
                          StepRepr_PropertyDefinitionRepresentation)
};
