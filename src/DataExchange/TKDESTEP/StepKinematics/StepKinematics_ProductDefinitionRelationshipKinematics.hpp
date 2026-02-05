#pragma once

#include <Standard.hpp>
#include <StepRepr_PropertyDefinition.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_CharacterizedDefinition.hpp>

//! Representation of STEP entity ProductDefinitionRelationshipKinematics
class StepKinematics_ProductDefinitionRelationshipKinematics : public StepRepr_PropertyDefinition
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_ProductDefinitionRelationshipKinematics();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_ProductDefinitionRelationshipKinematics,
                          StepRepr_PropertyDefinition)
};
