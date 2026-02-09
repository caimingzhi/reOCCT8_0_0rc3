#include <Standard_Transient.hpp>
#include <StepAP203_ClassifiedItem.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepRepr_AssemblyComponentUsage.hpp>

StepAP203_ClassifiedItem::StepAP203_ClassifiedItem() = default;

int StepAP203_ClassifiedItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_AssemblyComponentUsage)))
    return 2;
  return 0;
}

occ::handle<StepBasic_ProductDefinitionFormation> StepAP203_ClassifiedItem::
  ProductDefinitionFormation() const
{
  return occ::down_cast<StepBasic_ProductDefinitionFormation>(Value());
}

occ::handle<StepRepr_AssemblyComponentUsage> StepAP203_ClassifiedItem::AssemblyComponentUsage()
  const
{
  return occ::down_cast<StepRepr_AssemblyComponentUsage>(Value());
}
