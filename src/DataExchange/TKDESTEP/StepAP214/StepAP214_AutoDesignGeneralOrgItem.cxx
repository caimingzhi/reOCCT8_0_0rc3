

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepAP214_AutoDesignDocumentReference.hpp>
#include <StepAP214_AutoDesignGeneralOrgItem.hpp>
#include <StepBasic_Product.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepBasic_ProductDefinitionWithAssociatedDocuments.hpp>
#include <StepRepr_ExternallyDefinedRepresentation.hpp>
#include <StepRepr_Representation.hpp>

StepAP214_AutoDesignGeneralOrgItem::StepAP214_AutoDesignGeneralOrgItem() = default;

int StepAP214_AutoDesignGeneralOrgItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Product)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionWithAssociatedDocuments)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_Representation)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ExternallyDefinedRepresentation)))
    return 7;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AutoDesignDocumentReference)))
    return 8;
  return 0;
}

occ::handle<StepBasic_Product> StepAP214_AutoDesignGeneralOrgItem::Product() const
{
  return GetCasted(StepBasic_Product, Value());
}

occ::handle<StepBasic_ProductDefinition> StepAP214_AutoDesignGeneralOrgItem::ProductDefinition()
  const
{
  return GetCasted(StepBasic_ProductDefinition, Value());
}

occ::handle<StepBasic_ProductDefinitionFormation> StepAP214_AutoDesignGeneralOrgItem::
  ProductDefinitionFormation() const
{
  return GetCasted(StepBasic_ProductDefinitionFormation, Value());
}

occ::handle<StepBasic_ProductDefinitionRelationship> StepAP214_AutoDesignGeneralOrgItem::
  ProductDefinitionRelationship() const
{
  return GetCasted(StepBasic_ProductDefinitionRelationship, Value());
}

occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments> StepAP214_AutoDesignGeneralOrgItem::
  ProductDefinitionWithAssociatedDocuments() const
{
  return GetCasted(StepBasic_ProductDefinitionWithAssociatedDocuments, Value());
}

occ::handle<StepRepr_Representation> StepAP214_AutoDesignGeneralOrgItem::Representation() const
{
  return GetCasted(StepRepr_Representation, Value());
}

occ::handle<StepRepr_ExternallyDefinedRepresentation> StepAP214_AutoDesignGeneralOrgItem::
  ExternallyDefinedRepresentation() const
{
  return GetCasted(StepRepr_ExternallyDefinedRepresentation, Value());
}

occ::handle<StepAP214_AutoDesignDocumentReference> StepAP214_AutoDesignGeneralOrgItem::
  AutoDesignDocumentReference() const
{
  return GetCasted(StepAP214_AutoDesignDocumentReference, Value());
}
