#include <Standard_Transient.hpp>
#include <StepAP203_CertifiedItem.hpp>
#include <StepRepr_SuppliedPartRelationship.hpp>

StepAP203_CertifiedItem::StepAP203_CertifiedItem() = default;

int StepAP203_CertifiedItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_SuppliedPartRelationship)))
    return 1;
  return 0;
}

occ::handle<StepRepr_SuppliedPartRelationship> StepAP203_CertifiedItem::SuppliedPartRelationship()
  const
{
  return occ::down_cast<StepRepr_SuppliedPartRelationship>(Value());
}
