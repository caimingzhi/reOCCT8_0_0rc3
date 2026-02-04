#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_Approval;
class StepBasic_DocumentRelationship;
class StepRepr_ExternallyDefinedRepresentation;
class StepRepr_MappedItem;
class StepRepr_MaterialDesignation;
class StepVisual_PresentationArea;
class StepVisual_PresentationView;
class StepBasic_ProductCategory;
class StepBasic_ProductDefinition;
class StepBasic_ProductDefinitionRelationship;
class StepRepr_PropertyDefinition;
class StepRepr_Representation;
class StepRepr_RepresentationRelationship;
class StepRepr_ShapeAspect;

class StepAP214_AutoDesignReferencingItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a AutoDesignReferencingItem SelectType
  Standard_EXPORT StepAP214_AutoDesignReferencingItem();

  //! Recognizes a AutoDesignReferencingItem Kind Entity that is :
  //! 1     Approval from StepBasic,
  //! 2     DocumentRelationship from StepBasic,
  //! 3     ExternallyDefinedRepresentation from StepRepr,
  //! 4     MappedItem from StepRepr,
  //! 5     MaterialDesignation from StepRepr,
  //! 6     PresentationArea from StepVisual,
  //! 7     PresentationView from StepVisual,
  //! 8     ProductCategory from StepBasic,
  //! 9     ProductDefinition from StepBasic,
  //! 10     ProductDefinitionRelationship from StepBasic,
  //! 11     PropertyDefinition from StepBasic,
  //! 12     Representation from StepRepr,
  //! 13     RepresentationRelationship from StepRepr,
  //! 14     ShapeAspect from StepRepr
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_Approval> Approval() const;

  Standard_EXPORT occ::handle<StepBasic_DocumentRelationship> DocumentRelationship() const;

  Standard_EXPORT occ::handle<StepRepr_ExternallyDefinedRepresentation>
                  ExternallyDefinedRepresentation() const;

  Standard_EXPORT occ::handle<StepRepr_MappedItem> MappedItem() const;

  Standard_EXPORT occ::handle<StepRepr_MaterialDesignation> MaterialDesignation() const;

  Standard_EXPORT occ::handle<StepVisual_PresentationArea> PresentationArea() const;

  Standard_EXPORT occ::handle<StepVisual_PresentationView> PresentationView() const;

  Standard_EXPORT occ::handle<StepBasic_ProductCategory> ProductCategory() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionRelationship>
                  ProductDefinitionRelationship() const;

  Standard_EXPORT occ::handle<StepRepr_PropertyDefinition> PropertyDefinition() const;

  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  Standard_EXPORT occ::handle<StepRepr_RepresentationRelationship> RepresentationRelationship()
    const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;
};

