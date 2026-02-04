#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_Approval;
class StepRepr_DescriptiveRepresentationItem;
class StepRepr_MaterialDesignation;
class StepBasic_ProductDefinition;
class StepBasic_ProductDefinitionRelationship;
class StepRepr_PropertyDefinition;
class StepRepr_Representation;
class StepRepr_ShapeAspect;
class StepRepr_ShapeAspectRelationship;
class StepAP214_AppliedExternalIdentificationAssignment;
class StepRepr_AssemblyComponentUsage;
class StepBasic_CharacterizedObject;
class StepShape_DimensionalSize;
class StepBasic_ExternallyDefinedItem;
class StepBasic_Group;
class StepBasic_GroupRelationship;
class StepBasic_ProductCategory;
class StepRepr_MeasureRepresentationItem;
class StepBasic_ProductDefinitionContext;
class StepRepr_RepresentationItem;

class StepAP214_DocumentReferenceItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a DocumentReferenceItem SelectType
  Standard_EXPORT StepAP214_DocumentReferenceItem();

  //! Recognizes a DocumentReferenceItem Kind Entity that is :
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Approval (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Approval> Approval() const;

  //! returns Value as a (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_DescriptiveRepresentationItem>
                  DescriptiveRepresentationItem() const;

  //! returns Value as a MaterialDesignation (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_MaterialDesignation> MaterialDesignation() const;

  //! returns Value as a ProductDefinition (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  //! returns Value as aProductDefinitionRelationship (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionRelationship>
                  ProductDefinitionRelationship() const;

  //! returns Value as a PropertyDefinition (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_PropertyDefinition> PropertyDefinition() const;

  //! returns Value as a Representation (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  //! returns Value as a ShapeAspect (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  //! returns Value as a ShapeAspectRelationship (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship() const;

  //! returns Value as a AppliedExternalIdentificationAssignment (Null if another type)
  Standard_EXPORT occ::handle<StepAP214_AppliedExternalIdentificationAssignment>
                  AppliedExternalIdentificationAssignment() const;

  //! returns Value as a AssemblyComponentUsage (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_AssemblyComponentUsage> AssemblyComponentUsage() const;

  //! returns Value as a CharacterizedObject (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_CharacterizedObject> CharacterizedObject() const;

  //! returns Value as a DimensionalSize (Null if another type)
  Standard_EXPORT occ::handle<StepShape_DimensionalSize> DimensionalSize() const;

  //! returns Value as a ExternallyDefinedItem (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ExternallyDefinedItem> ExternallyDefinedItem() const;

  //! returns Value as a Group (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Group> Group() const;

  //! returns Value as a GroupRelationship (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_GroupRelationship> GroupRelationship() const;

  //! returns Value as a MeasureRepresentationItem (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_MeasureRepresentationItem> MeasureRepresentationItem() const;

  //! returns Value as a ProductCategory (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductCategory> ProductCategory() const;

  //! returns Value as a ProductDefinitionContext (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionContext> ProductDefinitionContext() const;

  //! returns Value as a RepresentationItem (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> RepresentationItem() const;
};

