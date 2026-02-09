

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepAP214_ApprovalItem.hpp>
#include <StepBasic_Date.hpp>
#include <StepBasic_DocumentFile.hpp>
#include <StepBasic_Effectivity.hpp>
#include <StepBasic_Group.hpp>
#include <StepBasic_GroupRelationship.hpp>
#include <StepBasic_Product.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_ProductDefinitionFormationRelationship.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepBasic_SecurityClassification.hpp>
#include <StepRepr_AssemblyComponentUsageSubstitute.hpp>
#include <StepRepr_ConfigurationItem.hpp>
#include <StepRepr_MaterialDesignation.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepRepr_ShapeAspectRelationship.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <StepVisual_MechanicalDesignGeometricPresentationRepresentation.hpp>
#include <StepVisual_PresentationArea.hpp>

StepAP214_ApprovalItem::StepAP214_ApprovalItem() = default;

int StepAP214_ApprovalItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{

  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_AssemblyComponentUsageSubstitute)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_DocumentFile)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MaterialDesignation)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_MechanicalDesignGeometricPresentationRepresentation)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationArea)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Product)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 7;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 8;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship)))
    return 9;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinition)))
    return 10;
  if (ent->IsKind(STANDARD_TYPE(StepShape_ShapeRepresentation)))
    return 11;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_SecurityClassification)))
    return 12;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ConfigurationItem)))
    return 13;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Date)))
    return 14;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Document)))
    return 15;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Effectivity)))
    return 16;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Group)))
    return 17;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_GroupRelationship)))
    return 18;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormationRelationship)))
    return 19;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_Representation)))
    return 20;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspectRelationship)))
    return 21;
  return 0;
}

occ::handle<StepRepr_AssemblyComponentUsageSubstitute> StepAP214_ApprovalItem::
  AssemblyComponentUsageSubstitute() const
{
  return GetCasted(StepRepr_AssemblyComponentUsageSubstitute, Value());
}

occ::handle<StepBasic_DocumentFile> StepAP214_ApprovalItem::DocumentFile() const
{
  return GetCasted(StepBasic_DocumentFile, Value());
}

occ::handle<StepRepr_MaterialDesignation> StepAP214_ApprovalItem::MaterialDesignation() const
{
  return GetCasted(StepRepr_MaterialDesignation, Value());
}

occ::handle<StepVisual_MechanicalDesignGeometricPresentationRepresentation> StepAP214_ApprovalItem::
  MechanicalDesignGeometricPresentationRepresentation() const
{
  return GetCasted(StepVisual_MechanicalDesignGeometricPresentationRepresentation, Value());
}

occ::handle<StepVisual_PresentationArea> StepAP214_ApprovalItem::PresentationArea() const
{
  return GetCasted(StepVisual_PresentationArea, Value());
}

occ::handle<StepBasic_Product> StepAP214_ApprovalItem::Product() const
{
  return GetCasted(StepBasic_Product, Value());
}

occ::handle<StepBasic_ProductDefinition> StepAP214_ApprovalItem::ProductDefinition() const
{
  return GetCasted(StepBasic_ProductDefinition, Value());
}

occ::handle<StepBasic_ProductDefinitionFormation> StepAP214_ApprovalItem::
  ProductDefinitionFormation() const
{
  return GetCasted(StepBasic_ProductDefinitionFormation, Value());
}

occ::handle<StepBasic_ProductDefinitionRelationship> StepAP214_ApprovalItem::
  ProductDefinitionRelationship() const
{
  return GetCasted(StepBasic_ProductDefinitionRelationship, Value());
}

occ::handle<StepRepr_PropertyDefinition> StepAP214_ApprovalItem::PropertyDefinition() const
{
  return GetCasted(StepRepr_PropertyDefinition, Value());
}

occ::handle<StepShape_ShapeRepresentation> StepAP214_ApprovalItem::ShapeRepresentation() const
{
  return GetCasted(StepShape_ShapeRepresentation, Value());
}

occ::handle<StepBasic_SecurityClassification> StepAP214_ApprovalItem::SecurityClassification() const
{
  return GetCasted(StepBasic_SecurityClassification, Value());
}

occ::handle<StepRepr_ConfigurationItem> StepAP214_ApprovalItem::ConfigurationItem() const
{
  return GetCasted(StepRepr_ConfigurationItem, Value());
}

occ::handle<StepBasic_Date> StepAP214_ApprovalItem::Date() const
{
  return GetCasted(StepBasic_Date, Value());
}

occ::handle<StepBasic_Document> StepAP214_ApprovalItem::Document() const
{
  return GetCasted(StepBasic_Document, Value());
}

occ::handle<StepBasic_Effectivity> StepAP214_ApprovalItem::Effectivity() const
{
  return GetCasted(StepBasic_Effectivity, Value());
}

occ::handle<StepBasic_Group> StepAP214_ApprovalItem::Group() const
{
  return GetCasted(StepBasic_Group, Value());
}

occ::handle<StepBasic_GroupRelationship> StepAP214_ApprovalItem::GroupRelationship() const
{
  return GetCasted(StepBasic_GroupRelationship, Value());
}

occ::handle<StepBasic_ProductDefinitionFormationRelationship> StepAP214_ApprovalItem::
  ProductDefinitionFormationRelationship() const
{
  return GetCasted(StepBasic_ProductDefinitionFormationRelationship, Value());
}

occ::handle<StepRepr_Representation> StepAP214_ApprovalItem::Representation() const
{
  return GetCasted(StepRepr_Representation, Value());
}

occ::handle<StepRepr_ShapeAspectRelationship> StepAP214_ApprovalItem::ShapeAspectRelationship()
  const
{
  return GetCasted(StepRepr_ShapeAspectRelationship, Value());
}
