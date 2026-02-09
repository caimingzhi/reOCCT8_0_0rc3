

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepAP214_PresentedItemSelect.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>

StepAP214_PresentedItemSelect::StepAP214_PresentedItemSelect() = default;

int StepAP214_PresentedItemSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship)))
    return 2;
  return 0;
}

occ::handle<StepBasic_ProductDefinition> StepAP214_PresentedItemSelect::ProductDefinition() const
{
  return GetCasted(StepBasic_ProductDefinition, Value());
}

occ::handle<StepBasic_ProductDefinitionRelationship> StepAP214_PresentedItemSelect::
  ProductDefinitionRelationship() const
{
  return GetCasted(StepBasic_ProductDefinitionRelationship, Value());
}
