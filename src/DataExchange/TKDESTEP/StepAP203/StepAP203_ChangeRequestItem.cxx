#include <Standard_Transient.hpp>
#include <StepAP203_ChangeRequestItem.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>

//=================================================================================================

StepAP203_ChangeRequestItem::StepAP203_ChangeRequestItem() = default;

//=================================================================================================

int StepAP203_ChangeRequestItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 1;
  return 0;
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinitionFormation> StepAP203_ChangeRequestItem::
  ProductDefinitionFormation() const
{
  return occ::down_cast<StepBasic_ProductDefinitionFormation>(Value());
}
