

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepAP214_GroupItem.hpp>
#include <StepBasic_GroupRelationship.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <StepRepr_MappedItem.hpp>
#include <StepRepr_PropertyDefinitionRepresentation.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_RepresentationRelationshipWithTransformation.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepRepr_ShapeAspectRelationship.hpp>
#include <StepRepr_ShapeRepresentationRelationship.hpp>
#include <StepShape_TopologicalRepresentationItem.hpp>
#include <StepVisual_StyledItem.hpp>

StepAP214_GroupItem::StepAP214_GroupItem() = default;

int StepAP214_GroupItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_GeometricRepresentationItem)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_GroupRelationship)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MappedItem)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinitionRepresentation)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_Representation)))
    return 7;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_RepresentationItem)))
    return 8;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_RepresentationRelationshipWithTransformation)))
    return 9;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspect)))
    return 10;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspectRelationship)))
    return 11;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeRepresentationRelationship)))
    return 12;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_StyledItem)))
    return 13;
  if (ent->IsKind(STANDARD_TYPE(StepShape_TopologicalRepresentationItem)))
    return 14;
  return 0;
}

occ::handle<StepGeom_GeometricRepresentationItem> StepAP214_GroupItem::GeometricRepresentationItem()
  const
{
  return GetCasted(StepGeom_GeometricRepresentationItem, Value());
}

occ::handle<StepBasic_GroupRelationship> StepAP214_GroupItem::GroupRelationship() const
{
  return GetCasted(StepBasic_GroupRelationship, Value());
}

occ::handle<StepRepr_MappedItem> StepAP214_GroupItem::MappedItem() const
{
  return GetCasted(StepRepr_MappedItem, Value());
}

occ::handle<StepBasic_ProductDefinition> StepAP214_GroupItem::ProductDefinition() const
{
  return GetCasted(StepBasic_ProductDefinition, Value());
}

occ::handle<StepBasic_ProductDefinitionFormation> StepAP214_GroupItem::ProductDefinitionFormation()
  const
{
  return GetCasted(StepBasic_ProductDefinitionFormation, Value());
}

occ::handle<StepRepr_PropertyDefinitionRepresentation> StepAP214_GroupItem::
  PropertyDefinitionRepresentation() const
{
  return GetCasted(StepRepr_PropertyDefinitionRepresentation, Value());
}

occ::handle<StepRepr_Representation> StepAP214_GroupItem::Representation() const
{
  return GetCasted(StepRepr_Representation, Value());
}

occ::handle<StepRepr_RepresentationItem> StepAP214_GroupItem::RepresentationItem() const
{
  return GetCasted(StepRepr_RepresentationItem, Value());
}

occ::handle<StepRepr_RepresentationRelationshipWithTransformation> StepAP214_GroupItem::
  RepresentationRelationshipWithTransformation() const
{
  return GetCasted(StepRepr_RepresentationRelationshipWithTransformation, Value());
}

occ::handle<StepRepr_ShapeAspect> StepAP214_GroupItem::ShapeAspect() const
{
  return GetCasted(StepRepr_ShapeAspect, Value());
}

occ::handle<StepRepr_ShapeAspectRelationship> StepAP214_GroupItem::ShapeAspectRelationship() const
{
  return GetCasted(StepRepr_ShapeAspectRelationship, Value());
}

occ::handle<StepRepr_ShapeRepresentationRelationship> StepAP214_GroupItem::
  ShapeRepresentationRelationship() const
{
  return GetCasted(StepRepr_ShapeRepresentationRelationship, Value());
}

occ::handle<StepVisual_StyledItem> StepAP214_GroupItem::StyledItem() const
{
  return GetCasted(StepVisual_StyledItem, Value());
}

occ::handle<StepShape_TopologicalRepresentationItem> StepAP214_GroupItem::
  TopologicalRepresentationItem() const
{
  return GetCasted(StepShape_TopologicalRepresentationItem, Value());
}
