#include <Standard_Transient.hpp>
#include <StepAP203_ApprovedItem.hpp>
#include <StepAP203_Change.hpp>
#include <StepAP203_ChangeRequest.hpp>
#include <StepAP203_StartRequest.hpp>
#include <StepAP203_StartWork.hpp>
#include <StepBasic_Certification.hpp>
#include <StepBasic_Contract.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_SecurityClassification.hpp>
#include <StepRepr_ConfigurationEffectivity.hpp>
#include <StepRepr_ConfigurationItem.hpp>

StepAP203_ApprovedItem::StepAP203_ApprovedItem() = default;

int StepAP203_ApprovedItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ConfigurationEffectivity)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ConfigurationItem)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_SecurityClassification)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepAP203_ChangeRequest)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepAP203_Change)))
    return 7;
  if (ent->IsKind(STANDARD_TYPE(StepAP203_StartRequest)))
    return 8;
  if (ent->IsKind(STANDARD_TYPE(StepAP203_StartWork)))
    return 9;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Certification)))
    return 10;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Contract)))
    return 11;
  return 0;
}

occ::handle<StepBasic_ProductDefinitionFormation> StepAP203_ApprovedItem::
  ProductDefinitionFormation() const
{
  return occ::down_cast<StepBasic_ProductDefinitionFormation>(Value());
}

occ::handle<StepBasic_ProductDefinition> StepAP203_ApprovedItem::ProductDefinition() const
{
  return occ::down_cast<StepBasic_ProductDefinition>(Value());
}

occ::handle<StepRepr_ConfigurationEffectivity> StepAP203_ApprovedItem::ConfigurationEffectivity()
  const
{
  return occ::down_cast<StepRepr_ConfigurationEffectivity>(Value());
}

occ::handle<StepRepr_ConfigurationItem> StepAP203_ApprovedItem::ConfigurationItem() const
{
  return occ::down_cast<StepRepr_ConfigurationItem>(Value());
}

occ::handle<StepBasic_SecurityClassification> StepAP203_ApprovedItem::SecurityClassification() const
{
  return occ::down_cast<StepBasic_SecurityClassification>(Value());
}

occ::handle<StepAP203_ChangeRequest> StepAP203_ApprovedItem::ChangeRequest() const
{
  return occ::down_cast<StepAP203_ChangeRequest>(Value());
}

occ::handle<StepAP203_Change> StepAP203_ApprovedItem::Change() const
{
  return occ::down_cast<StepAP203_Change>(Value());
}

occ::handle<StepAP203_StartRequest> StepAP203_ApprovedItem::StartRequest() const
{
  return occ::down_cast<StepAP203_StartRequest>(Value());
}

occ::handle<StepAP203_StartWork> StepAP203_ApprovedItem::StartWork() const
{
  return occ::down_cast<StepAP203_StartWork>(Value());
}

occ::handle<StepBasic_Certification> StepAP203_ApprovedItem::Certification() const
{
  return occ::down_cast<StepBasic_Certification>(Value());
}

occ::handle<StepBasic_Contract> StepAP203_ApprovedItem::Contract() const
{
  return occ::down_cast<StepBasic_Contract>(Value());
}
