#include <Standard_Transient.hpp>
#include <StepAP203_ContractedItem.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>

//=================================================================================================

StepAP203_ContractedItem::StepAP203_ContractedItem() = default;

//=================================================================================================

int StepAP203_ContractedItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 1;
  return 0;
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinitionFormation> StepAP203_ContractedItem::
  ProductDefinitionFormation() const
{
  return occ::down_cast<StepBasic_ProductDefinitionFormation>(Value());
}
