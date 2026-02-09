

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepAP214_AppliedExternalIdentificationAssignment.hpp>
#include <StepAP214_DocumentReferenceItem.hpp>
#include <StepBasic_Approval.hpp>
#include <StepBasic_CharacterizedObject.hpp>
#include <StepBasic_ExternallyDefinedItem.hpp>
#include <StepBasic_Group.hpp>
#include <StepBasic_GroupRelationship.hpp>
#include <StepBasic_ProductCategory.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionContext.hpp>
#include <StepRepr_AssemblyComponentUsage.hpp>
#include <StepRepr_DescriptiveRepresentationItem.hpp>
#include <StepRepr_MaterialDesignation.hpp>
#include <StepRepr_MeasureRepresentationItem.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepRepr_ShapeAspectRelationship.hpp>
#include <StepShape_DimensionalSize.hpp>

StepAP214_DocumentReferenceItem::StepAP214_DocumentReferenceItem() = default;

int StepAP214_DocumentReferenceItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Approval)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_DescriptiveRepresentationItem)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MaterialDesignation)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinition)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_Representation)))
    return 7;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspect)))
    return 8;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspectRelationship)))
    return 9;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedExternalIdentificationAssignment)))
    return 10;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_AssemblyComponentUsage)))
    return 11;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_CharacterizedObject)))
    return 12;
  if (ent->IsKind(STANDARD_TYPE(StepShape_DimensionalSize)))
    return 13;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ExternallyDefinedItem)))
    return 14;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Group)))
    return 15;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_GroupRelationship)))
    return 16;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MeasureRepresentationItem)))
    return 17;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductCategory)))
    return 18;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionContext)))
    return 19;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_RepresentationItem)))
    return 20;
  return 0;
}

occ::handle<StepBasic_Approval> StepAP214_DocumentReferenceItem::Approval() const
{
  return GetCasted(StepBasic_Approval, Value());
}

occ::handle<StepRepr_DescriptiveRepresentationItem> StepAP214_DocumentReferenceItem::
  DescriptiveRepresentationItem() const
{
  return GetCasted(StepRepr_DescriptiveRepresentationItem, Value());
}

occ::handle<StepRepr_MaterialDesignation> StepAP214_DocumentReferenceItem::MaterialDesignation()
  const
{
  return GetCasted(StepRepr_MaterialDesignation, Value());
}

occ::handle<StepBasic_ProductDefinition> StepAP214_DocumentReferenceItem::ProductDefinition() const
{
  return GetCasted(StepBasic_ProductDefinition, Value());
}

occ::handle<StepBasic_ProductDefinitionRelationship> StepAP214_DocumentReferenceItem::
  ProductDefinitionRelationship() const
{
  return GetCasted(StepBasic_ProductDefinitionRelationship, Value());
}

occ::handle<StepRepr_PropertyDefinition> StepAP214_DocumentReferenceItem::PropertyDefinition() const
{
  return GetCasted(StepRepr_PropertyDefinition, Value());
}

occ::handle<StepRepr_Representation> StepAP214_DocumentReferenceItem::Representation() const
{
  return GetCasted(StepRepr_Representation, Value());
}

occ::handle<StepRepr_ShapeAspect> StepAP214_DocumentReferenceItem::ShapeAspect() const
{
  return GetCasted(StepRepr_ShapeAspect, Value());
}

occ::handle<StepRepr_ShapeAspectRelationship> StepAP214_DocumentReferenceItem::
  ShapeAspectRelationship() const
{
  return GetCasted(StepRepr_ShapeAspectRelationship, Value());
}

occ::handle<StepAP214_AppliedExternalIdentificationAssignment> StepAP214_DocumentReferenceItem::
  AppliedExternalIdentificationAssignment() const
{
  return GetCasted(StepAP214_AppliedExternalIdentificationAssignment, Value());
}

occ::handle<StepRepr_AssemblyComponentUsage> StepAP214_DocumentReferenceItem::
  AssemblyComponentUsage() const
{
  return GetCasted(StepRepr_AssemblyComponentUsage, Value());
}

occ::handle<StepBasic_CharacterizedObject> StepAP214_DocumentReferenceItem::CharacterizedObject()
  const
{
  return GetCasted(StepBasic_CharacterizedObject, Value());
}

occ::handle<StepShape_DimensionalSize> StepAP214_DocumentReferenceItem::DimensionalSize() const
{
  return GetCasted(StepShape_DimensionalSize, Value());
}

occ::handle<StepBasic_ExternallyDefinedItem> StepAP214_DocumentReferenceItem::
  ExternallyDefinedItem() const
{
  return GetCasted(StepBasic_ExternallyDefinedItem, Value());
}

occ::handle<StepBasic_Group> StepAP214_DocumentReferenceItem::Group() const
{
  return GetCasted(StepBasic_Group, Value());
}

occ::handle<StepBasic_GroupRelationship> StepAP214_DocumentReferenceItem::GroupRelationship() const
{
  return GetCasted(StepBasic_GroupRelationship, Value());
}

occ::handle<StepRepr_MeasureRepresentationItem> StepAP214_DocumentReferenceItem::
  MeasureRepresentationItem() const
{
  return GetCasted(StepRepr_MeasureRepresentationItem, Value());
}

occ::handle<StepBasic_ProductCategory> StepAP214_DocumentReferenceItem::ProductCategory() const
{
  return GetCasted(StepBasic_ProductCategory, Value());
}

occ::handle<StepBasic_ProductDefinitionContext> StepAP214_DocumentReferenceItem::
  ProductDefinitionContext() const
{
  return GetCasted(StepBasic_ProductDefinitionContext, Value());
}

occ::handle<StepRepr_RepresentationItem> StepAP214_DocumentReferenceItem::RepresentationItem() const
{
  return GetCasted(StepRepr_RepresentationItem, Value());
}
