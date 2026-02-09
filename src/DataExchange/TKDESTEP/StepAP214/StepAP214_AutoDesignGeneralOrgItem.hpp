#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_Product;
class StepBasic_ProductDefinition;
class StepBasic_ProductDefinitionFormation;
class StepBasic_ProductDefinitionRelationship;
class StepBasic_ProductDefinitionWithAssociatedDocuments;
class StepRepr_Representation;
class StepRepr_ExternallyDefinedRepresentation;
class StepAP214_AutoDesignDocumentReference;

class StepAP214_AutoDesignGeneralOrgItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP214_AutoDesignGeneralOrgItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_Product> Product() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> ProductDefinitionFormation()
    const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionRelationship>
                  ProductDefinitionRelationship() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments>
                  ProductDefinitionWithAssociatedDocuments() const;

  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  Standard_EXPORT occ::handle<StepRepr_ExternallyDefinedRepresentation>
                  ExternallyDefinedRepresentation() const;

  Standard_EXPORT occ::handle<StepAP214_AutoDesignDocumentReference> AutoDesignDocumentReference()
    const;
};
