

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepAP214_AutoDesignPresentedItemSelect.hpp>
#include <StepBasic_DocumentRelationship.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_RepresentationRelationship.hpp>
#include <StepRepr_ShapeAspect.hpp>

StepAP214_AutoDesignPresentedItemSelect::StepAP214_AutoDesignPresentedItemSelect() = default;

int StepAP214_AutoDesignPresentedItemSelect::CaseNum(
  const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ProductDefinitionShape)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_RepresentationRelationship)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspect)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_DocumentRelationship)))
    return 6;
  return 0;
}

occ::handle<StepBasic_ProductDefinition> StepAP214_AutoDesignPresentedItemSelect::
  ProductDefinition() const
{
  return GetCasted(StepBasic_ProductDefinition, Value());
}

occ::handle<StepBasic_ProductDefinitionRelationship> StepAP214_AutoDesignPresentedItemSelect::
  ProductDefinitionRelationship() const
{
  return GetCasted(StepBasic_ProductDefinitionRelationship, Value());
}

occ::handle<StepRepr_ProductDefinitionShape> StepAP214_AutoDesignPresentedItemSelect::
  ProductDefinitionShape() const
{
  return GetCasted(StepRepr_ProductDefinitionShape, Value());
}

occ::handle<StepRepr_RepresentationRelationship> StepAP214_AutoDesignPresentedItemSelect::
  RepresentationRelationship() const
{
  return GetCasted(StepRepr_RepresentationRelationship, Value());
}

occ::handle<StepRepr_ShapeAspect> StepAP214_AutoDesignPresentedItemSelect::ShapeAspect() const
{
  return GetCasted(StepRepr_ShapeAspect, Value());
}

occ::handle<StepBasic_DocumentRelationship> StepAP214_AutoDesignPresentedItemSelect::
  DocumentRelationship() const
{
  return GetCasted(StepBasic_DocumentRelationship, Value());
}
