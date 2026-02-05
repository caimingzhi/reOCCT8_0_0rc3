#include <Standard_Transient.hpp>
#include <StepAP203_WorkItem.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>

//=================================================================================================

StepAP203_WorkItem::StepAP203_WorkItem() = default;

//=================================================================================================

int StepAP203_WorkItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 1;
  return 0;
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinitionFormation> StepAP203_WorkItem::ProductDefinitionFormation()
  const
{
  return occ::down_cast<StepBasic_ProductDefinitionFormation>(Value());
}
