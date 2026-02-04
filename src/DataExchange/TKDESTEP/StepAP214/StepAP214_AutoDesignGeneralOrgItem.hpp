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

  //! Returns a AutoDesignGeneralOrgItem SelectType
  Standard_EXPORT StepAP214_AutoDesignGeneralOrgItem();

  //! Recognizes a AutoDesignGeneralOrgItem Kind Entity that is :
  //! 1     Product from StepBasic,
  //! 2     ProductDefinition from StepBasic,
  //! 3     ProductDefinitionFormation from StepBasic,
  //! 4     ProductDefinitionRelationship from StepBasic,
  //! 5     ProductDefinitionWithAssociatedDocuments from StepBasic,
  //! 6     Representation from StepRepr
  //! 7     ExternallyDefinedRepresentation from StepRepr,
  //! 8     AutoDesignDocumentReference from StepAP214,
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Product (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Product> Product() const;

  //! returns Value as a ProductDefinition (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  //! returns Value as a ProductDefinitionFormation (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> ProductDefinitionFormation()
    const;

  //! returns Value as a ProductDefinitionRelationship (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionRelationship>
                  ProductDefinitionRelationship() const;

  //! returns Value as a ProductDefinitionWithAssociatedDocuments (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments>
                  ProductDefinitionWithAssociatedDocuments() const;

  //! returns Value as a Representation (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  //! returns Value as a Representation (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ExternallyDefinedRepresentation>
                  ExternallyDefinedRepresentation() const;

  Standard_EXPORT occ::handle<StepAP214_AutoDesignDocumentReference> AutoDesignDocumentReference()
    const;
};

