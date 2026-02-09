

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepAP214_AutoDesignDateAndPersonAssignment.hpp>
#include <StepAP214_AutoDesignDateAndTimeItem.hpp>
#include <StepBasic_ApprovalPersonOrganization.hpp>
#include <StepBasic_ProductDefinitionEffectivity.hpp>

StepAP214_AutoDesignDateAndTimeItem::StepAP214_AutoDesignDateAndTimeItem() = default;

int StepAP214_AutoDesignDateAndTimeItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ApprovalPersonOrganization)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AutoDesignDateAndPersonAssignment)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionEffectivity)))
    return 3;
  return 0;
}

occ::handle<StepBasic_ApprovalPersonOrganization> StepAP214_AutoDesignDateAndTimeItem::
  ApprovalPersonOrganization() const
{
  return GetCasted(StepBasic_ApprovalPersonOrganization, Value());
}

occ::handle<StepAP214_AutoDesignDateAndPersonAssignment> StepAP214_AutoDesignDateAndTimeItem::
  AutoDesignDateAndPersonAssignment() const
{
  return GetCasted(StepAP214_AutoDesignDateAndPersonAssignment, Value());
}

occ::handle<StepBasic_ProductDefinitionEffectivity> StepAP214_AutoDesignDateAndTimeItem::
  ProductDefinitionEffectivity() const
{
  return GetCasted(StepBasic_ProductDefinitionEffectivity, Value());
}
