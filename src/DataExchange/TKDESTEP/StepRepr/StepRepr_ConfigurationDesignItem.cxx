#include <Standard_Transient.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepRepr_ConfigurationDesignItem.hpp>

//=================================================================================================

StepRepr_ConfigurationDesignItem::StepRepr_ConfigurationDesignItem() = default;

//=================================================================================================

int StepRepr_ConfigurationDesignItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 2;
  return 0;
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinition> StepRepr_ConfigurationDesignItem::ProductDefinition() const
{
  return occ::down_cast<StepBasic_ProductDefinition>(Value());
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinitionFormation> StepRepr_ConfigurationDesignItem::
  ProductDefinitionFormation() const
{
  return occ::down_cast<StepBasic_ProductDefinitionFormation>(Value());
}
