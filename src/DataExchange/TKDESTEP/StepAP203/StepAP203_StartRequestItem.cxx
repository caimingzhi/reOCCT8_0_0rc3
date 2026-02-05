#include <Standard_Transient.hpp>
#include <StepAP203_StartRequestItem.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>

//=================================================================================================

StepAP203_StartRequestItem::StepAP203_StartRequestItem() = default;

//=================================================================================================

int StepAP203_StartRequestItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 1;
  return 0;
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinitionFormation> StepAP203_StartRequestItem::
  ProductDefinitionFormation() const
{
  return occ::down_cast<StepBasic_ProductDefinitionFormation>(Value());
}
