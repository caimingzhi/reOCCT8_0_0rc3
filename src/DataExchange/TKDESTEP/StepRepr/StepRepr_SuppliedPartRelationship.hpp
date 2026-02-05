#pragma once

#include <Standard.hpp>

#include <StepBasic_ProductDefinitionRelationship.hpp>

class StepRepr_SuppliedPartRelationship : public StepBasic_ProductDefinitionRelationship
{

public:
  Standard_EXPORT StepRepr_SuppliedPartRelationship();

  DEFINE_STANDARD_RTTIEXT(StepRepr_SuppliedPartRelationship,
                          StepBasic_ProductDefinitionRelationship)
};
