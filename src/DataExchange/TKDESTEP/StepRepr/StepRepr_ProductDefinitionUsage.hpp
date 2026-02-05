#pragma once

#include <Standard.hpp>

#include <StepBasic_ProductDefinitionRelationship.hpp>

//! Representation of STEP entity ProductDefinitionUsage
class StepRepr_ProductDefinitionUsage : public StepBasic_ProductDefinitionRelationship
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_ProductDefinitionUsage();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ProductDefinitionUsage, StepBasic_ProductDefinitionRelationship)
};
