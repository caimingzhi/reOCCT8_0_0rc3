#pragma once

#include <Standard.hpp>

#include <StepBasic_ProductDefinitionRelationship.hpp>

class StepRepr_ProductDefinitionUsage : public StepBasic_ProductDefinitionRelationship
{

public:
  Standard_EXPORT StepRepr_ProductDefinitionUsage();

  DEFINE_STANDARD_RTTIEXT(StepRepr_ProductDefinitionUsage, StepBasic_ProductDefinitionRelationship)
};
