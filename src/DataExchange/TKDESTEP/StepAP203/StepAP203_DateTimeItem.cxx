#include <Standard_Transient.hpp>
#include <StepAP203_Change.hpp>
#include <StepAP203_ChangeRequest.hpp>
#include <StepAP203_DateTimeItem.hpp>
#include <StepAP203_StartRequest.hpp>
#include <StepAP203_StartWork.hpp>
#include <StepBasic_ApprovalPersonOrganization.hpp>
#include <StepBasic_Certification.hpp>
#include <StepBasic_Contract.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_SecurityClassification.hpp>

//=================================================================================================

StepAP203_DateTimeItem::StepAP203_DateTimeItem() = default;

//=================================================================================================

int StepAP203_DateTimeItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepAP203_ChangeRequest)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepAP203_StartRequest)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepAP203_Change)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepAP203_StartWork)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ApprovalPersonOrganization)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Contract)))
    return 7;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_SecurityClassification)))
    return 8;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Certification)))
    return 9;
  return 0;
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinition> StepAP203_DateTimeItem::ProductDefinition() const
{
  return occ::down_cast<StepBasic_ProductDefinition>(Value());
}

//=================================================================================================

occ::handle<StepAP203_ChangeRequest> StepAP203_DateTimeItem::ChangeRequest() const
{
  return occ::down_cast<StepAP203_ChangeRequest>(Value());
}

//=================================================================================================

occ::handle<StepAP203_StartRequest> StepAP203_DateTimeItem::StartRequest() const
{
  return occ::down_cast<StepAP203_StartRequest>(Value());
}

//=================================================================================================

occ::handle<StepAP203_Change> StepAP203_DateTimeItem::Change() const
{
  return occ::down_cast<StepAP203_Change>(Value());
}

//=================================================================================================

occ::handle<StepAP203_StartWork> StepAP203_DateTimeItem::StartWork() const
{
  return occ::down_cast<StepAP203_StartWork>(Value());
}

//=================================================================================================

occ::handle<StepBasic_ApprovalPersonOrganization> StepAP203_DateTimeItem::
  ApprovalPersonOrganization() const
{
  return occ::down_cast<StepBasic_ApprovalPersonOrganization>(Value());
}

//=================================================================================================

occ::handle<StepBasic_Contract> StepAP203_DateTimeItem::Contract() const
{
  return occ::down_cast<StepBasic_Contract>(Value());
}

//=================================================================================================

occ::handle<StepBasic_SecurityClassification> StepAP203_DateTimeItem::SecurityClassification() const
{
  return occ::down_cast<StepBasic_SecurityClassification>(Value());
}

//=================================================================================================

occ::handle<StepBasic_Certification> StepAP203_DateTimeItem::Certification() const
{
  return occ::down_cast<StepBasic_Certification>(Value());
}
