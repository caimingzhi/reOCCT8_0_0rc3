#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepBasic_ProductDefinitionOrReference.hpp>
#include <StepBasic_ProductDefinitionReference.hpp>
#include <StepBasic_ProductDefinitionReferenceWithLocalRepresentation.hpp>

StepBasic_ProductDefinitionOrReference::StepBasic_ProductDefinitionOrReference() = default;

int StepBasic_ProductDefinitionOrReference::CaseNum(
  const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionReference)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionReferenceWithLocalRepresentation)))
    return 3;
  return 0;
}

occ::handle<StepBasic_ProductDefinition> StepBasic_ProductDefinitionOrReference::ProductDefinition()
  const
{
  return GetCasted(StepBasic_ProductDefinition, Value());
}

occ::handle<StepBasic_ProductDefinitionReference> StepBasic_ProductDefinitionOrReference::
  ProductDefinitionReference() const
{
  return GetCasted(StepBasic_ProductDefinitionReference, Value());
}

occ::handle<StepBasic_ProductDefinitionReferenceWithLocalRepresentation>
  StepBasic_ProductDefinitionOrReference::ProductDefinitionReferenceWithLocalRepresentation() const
{
  return GetCasted(StepBasic_ProductDefinitionReferenceWithLocalRepresentation, Value());
}
