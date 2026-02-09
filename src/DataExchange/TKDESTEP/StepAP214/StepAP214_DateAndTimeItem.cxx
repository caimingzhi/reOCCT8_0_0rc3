

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepAP214_AppliedOrganizationAssignment.hpp>
#include <StepAP214_AppliedPersonAndOrganizationAssignment.hpp>
#include <StepAP214_DateAndTimeItem.hpp>
#include <StepBasic_ApprovalPersonOrganization.hpp>
#include <StepBasic_DocumentFile.hpp>
#include <StepBasic_Effectivity.hpp>
#include <StepBasic_Product.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepBasic_SecurityClassification.hpp>
#include <StepRepr_AssemblyComponentUsageSubstitute.hpp>
#include <StepRepr_MaterialDesignation.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <StepVisual_MechanicalDesignGeometricPresentationRepresentation.hpp>
#include <StepVisual_PresentationArea.hpp>

StepAP214_DateAndTimeItem::StepAP214_DateAndTimeItem() = default;

int StepAP214_DateAndTimeItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ApprovalPersonOrganization)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedPersonAndOrganizationAssignment)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedOrganizationAssignment)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_AssemblyComponentUsageSubstitute)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_DocumentFile)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Effectivity)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MaterialDesignation)))
    return 7;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_MechanicalDesignGeometricPresentationRepresentation)))
    return 8;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationArea)))
    return 9;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Product)))
    return 10;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 11;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 12;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship)))
    return 13;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinition)))
    return 14;
  if (ent->IsKind(STANDARD_TYPE(StepShape_ShapeRepresentation)))
    return 15;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_SecurityClassification)))
    return 16;

  return 0;
}

occ::handle<StepBasic_ApprovalPersonOrganization> StepAP214_DateAndTimeItem::
  ApprovalPersonOrganization() const
{
  return GetCasted(StepBasic_ApprovalPersonOrganization, Value());
}

occ::handle<StepAP214_AppliedPersonAndOrganizationAssignment> StepAP214_DateAndTimeItem::
  AppliedPersonAndOrganizationAssignment() const
{
  return GetCasted(StepAP214_AppliedPersonAndOrganizationAssignment, Value());
}

occ::handle<StepAP214_AppliedOrganizationAssignment> StepAP214_DateAndTimeItem::
  AppliedOrganizationAssignment() const
{
  return GetCasted(StepAP214_AppliedOrganizationAssignment, Value());
}
