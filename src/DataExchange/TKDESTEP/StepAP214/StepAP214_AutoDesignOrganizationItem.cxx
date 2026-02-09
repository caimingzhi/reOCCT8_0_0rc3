

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepAP214_AutoDesignOrganizationItem.hpp>
#include <StepBasic_Document.hpp>
#include <StepBasic_PhysicallyModeledProductDefinition.hpp>

StepAP214_AutoDesignOrganizationItem::StepAP214_AutoDesignOrganizationItem() = default;

int StepAP214_AutoDesignOrganizationItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  int num = StepAP214_AutoDesignGeneralOrgItem::CaseNum(ent);
  if (num > 0)
    return num;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Document)))
    return 9;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_PhysicallyModeledProductDefinition)))
    return 10;
  return 0;
}

occ::handle<StepBasic_Document> StepAP214_AutoDesignOrganizationItem::Document() const
{
  return GetCasted(StepBasic_Document, Value());
}

occ::handle<StepBasic_PhysicallyModeledProductDefinition> StepAP214_AutoDesignOrganizationItem::
  PhysicallyModeledProductDefinition() const
{
  return GetCasted(StepBasic_PhysicallyModeledProductDefinition, Value());
}
