#include <Standard_Transient.hpp>
#include <StepBasic_Product.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_ProductOrFormationOrDefinition.hpp>

//=================================================================================================

StepBasic_ProductOrFormationOrDefinition::StepBasic_ProductOrFormationOrDefinition() = default;

//=================================================================================================

int StepBasic_ProductOrFormationOrDefinition::CaseNum(
  const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Product)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 3;
  return 0;
}

//=================================================================================================

occ::handle<StepBasic_Product> StepBasic_ProductOrFormationOrDefinition::Product() const
{
  return occ::down_cast<StepBasic_Product>(Value());
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinitionFormation> StepBasic_ProductOrFormationOrDefinition::
  ProductDefinitionFormation() const
{
  return occ::down_cast<StepBasic_ProductDefinitionFormation>(Value());
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinition> StepBasic_ProductOrFormationOrDefinition::
  ProductDefinition() const
{
  return occ::down_cast<StepBasic_ProductDefinition>(Value());
}
