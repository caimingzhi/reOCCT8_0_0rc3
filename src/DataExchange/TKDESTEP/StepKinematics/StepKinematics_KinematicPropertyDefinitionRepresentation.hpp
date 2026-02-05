#pragma once

#include <Standard.hpp>
#include <StepRepr_PropertyDefinitionRepresentation.hpp>

#include <StepRepr_RepresentedDefinition.hpp>
#include <StepRepr_Representation.hpp>

//! Representation of STEP entity KinematicPropertyDefinitionRepresentation
class StepKinematics_KinematicPropertyDefinitionRepresentation
    : public StepRepr_PropertyDefinitionRepresentation
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_KinematicPropertyDefinitionRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_KinematicPropertyDefinitionRepresentation,
                          StepRepr_PropertyDefinitionRepresentation)
};
