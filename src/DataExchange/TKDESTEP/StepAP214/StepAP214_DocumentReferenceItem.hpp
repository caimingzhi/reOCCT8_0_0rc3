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

  Standard_EXPORT StepAP214_DocumentReferenceItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_Approval> Approval() const;

  Standard_EXPORT occ::handle<StepRepr_DescriptiveRepresentationItem>
                  DescriptiveRepresentationItem() const;

  Standard_EXPORT occ::handle<StepRepr_MaterialDesignation> MaterialDesignation() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionRelationship>
                  ProductDefinitionRelationship() const;

  Standard_EXPORT occ::handle<StepRepr_PropertyDefinition> PropertyDefinition() const;

  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship() const;

  Standard_EXPORT occ::handle<StepAP214_AppliedExternalIdentificationAssignment>
                  AppliedExternalIdentificationAssignment() const;

  Standard_EXPORT occ::handle<StepRepr_AssemblyComponentUsage> AssemblyComponentUsage() const;

  Standard_EXPORT occ::handle<StepBasic_CharacterizedObject> CharacterizedObject() const;

  Standard_EXPORT occ::handle<StepShape_DimensionalSize> DimensionalSize() const;

  Standard_EXPORT occ::handle<StepBasic_ExternallyDefinedItem> ExternallyDefinedItem() const;

  Standard_EXPORT occ::handle<StepBasic_Group> Group() const;

  Standard_EXPORT occ::handle<StepBasic_GroupRelationship> GroupRelationship() const;

  Standard_EXPORT occ::handle<StepRepr_MeasureRepresentationItem> MeasureRepresentationItem() const;

  Standard_EXPORT occ::handle<StepBasic_ProductCategory> ProductCategory() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionContext> ProductDefinitionContext() const;

  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> RepresentationItem() const;
};
