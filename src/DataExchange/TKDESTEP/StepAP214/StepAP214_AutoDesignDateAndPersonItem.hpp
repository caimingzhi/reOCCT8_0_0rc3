#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepAP214_AutoDesignOrganizationAssignment;
class StepBasic_Product;
class StepBasic_ProductDefinition;
class StepBasic_ProductDefinitionFormation;
class StepRepr_Representation;
class StepAP214_AutoDesignDocumentReference;
class StepRepr_ExternallyDefinedRepresentation;
class StepBasic_ProductDefinitionRelationship;
class StepBasic_ProductDefinitionWithAssociatedDocuments;

class StepAP214_AutoDesignDateAndPersonItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP214_AutoDesignDateAndPersonItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepAP214_AutoDesignOrganizationAssignment>
                  AutoDesignOrganizationAssignment() const;

  Standard_EXPORT occ::handle<StepBasic_Product> Product() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> ProductDefinitionFormation()
    const;

  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  Standard_EXPORT occ::handle<StepAP214_AutoDesignDocumentReference> AutoDesignDocumentReference()
    const;

  Standard_EXPORT occ::handle<StepRepr_ExternallyDefinedRepresentation>
                  ExternallyDefinedRepresentation() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionRelationship>
                  ProductDefinitionRelationship() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments>
                  ProductDefinitionWithAssociatedDocuments() const;
};
