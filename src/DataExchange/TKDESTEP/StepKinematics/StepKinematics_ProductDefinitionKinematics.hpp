#pragma once


#include <Standard.hpp>
#include <StepRepr_PropertyDefinition.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_CharacterizedDefinition.hpp>

//! Representation of STEP entity ProductDefinitionKinematics
class StepKinematics_ProductDefinitionKinematics : public StepRepr_PropertyDefinition
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_ProductDefinitionKinematics();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_ProductDefinitionKinematics, StepRepr_PropertyDefinition)
};
