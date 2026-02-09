

#include <MoniTool_Macros.hpp>
#include <StepAP214_SecurityClassificationItem.hpp>
#include <StepBasic_Action.hpp>
#include <StepBasic_DocumentFile.hpp>
#include <StepBasic_Product.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_VersionedActionRequest.hpp>
#include <StepBasic_GeneralProperty.hpp>
#include <StepRepr_ProductConcept.hpp>
#include <StepRepr_AssemblyComponentUsage.hpp>
#include <StepRepr_AssemblyComponentUsageSubstitute.hpp>
#include <StepRepr_ConfigurationDesign.hpp>
#include <StepRepr_ConfigurationEffectivity.hpp>
#include <StepRepr_MakeFromUsageOption.hpp>
#include <StepRepr_MaterialDesignation.hpp>
#include <StepRepr_ProductDefinitionUsage.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <StepVisual_DraughtingModel.hpp>
#include <StepVisual_MechanicalDesignGeometricPresentationRepresentation.hpp>
#include <StepVisual_PresentationArea.hpp>

StepAP214_SecurityClassificationItem::StepAP214_SecurityClassificationItem() = default;

int StepAP214_SecurityClassificationItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{

  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Action)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_AssemblyComponentUsage)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_AssemblyComponentUsageSubstitute)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ConfigurationDesign)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ConfigurationEffectivity)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Document)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_DocumentFile)))
    return 7;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_DraughtingModel)))
    return 8;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_GeneralProperty)))
    return 9;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MakeFromUsageOption)))
    return 10;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MaterialDesignation)))
    return 11;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_MechanicalDesignGeometricPresentationRepresentation)))
    return 12;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationArea)))
    return 13;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Product)))
    return 14;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ProductConcept)))
    return 15;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 16;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 17;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship)))
    return 18;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ProductDefinitionUsage)))
    return 19;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinition)))
    return 20;
  if (ent->IsKind(STANDARD_TYPE(StepShape_ShapeRepresentation)))
    return 21;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_VersionedActionRequest)))
    return 22;
  return 0;
}

occ::handle<StepBasic_Action> StepAP214_SecurityClassificationItem::Action() const
{
  return GetCasted(StepBasic_Action, Value());
}

occ::handle<StepRepr_AssemblyComponentUsage> StepAP214_SecurityClassificationItem::
  AssemblyComponentUsage() const
{
  return GetCasted(StepRepr_AssemblyComponentUsage, Value());
}

occ::handle<StepRepr_ConfigurationDesign> StepAP214_SecurityClassificationItem::
  ConfigurationDesign() const
{
  return GetCasted(StepRepr_ConfigurationDesign, Value());
}

occ::handle<StepRepr_ConfigurationEffectivity> StepAP214_SecurityClassificationItem::
  ConfigurationEffectivity() const
{
  return GetCasted(StepRepr_ConfigurationEffectivity, Value());
}

occ::handle<StepVisual_DraughtingModel> StepAP214_SecurityClassificationItem::DraughtingModel()
  const
{
  return GetCasted(StepVisual_DraughtingModel, Value());
}

occ::handle<StepBasic_GeneralProperty> StepAP214_SecurityClassificationItem::GeneralProperty() const
{
  return GetCasted(StepBasic_GeneralProperty, Value());
}

occ::handle<StepRepr_MakeFromUsageOption> StepAP214_SecurityClassificationItem::
  MakeFromUsageOption() const
{
  return GetCasted(StepRepr_MakeFromUsageOption, Value());
}

occ::handle<StepRepr_ProductConcept> StepAP214_SecurityClassificationItem::ProductConcept() const
{
  return GetCasted(StepRepr_ProductConcept, Value());
}

occ::handle<StepRepr_ProductDefinitionUsage> StepAP214_SecurityClassificationItem::
  ProductDefinitionUsage() const
{
  return GetCasted(StepRepr_ProductDefinitionUsage, Value());
}

occ::handle<StepBasic_VersionedActionRequest> StepAP214_SecurityClassificationItem::
  VersionedActionRequest() const
{
  return GetCasted(StepBasic_VersionedActionRequest, Value());
}
