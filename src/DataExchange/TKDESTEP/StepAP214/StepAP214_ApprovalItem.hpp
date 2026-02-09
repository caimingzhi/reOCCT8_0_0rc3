#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepRepr_AssemblyComponentUsageSubstitute;
class StepBasic_DocumentFile;
class StepRepr_MaterialDesignation;
class StepVisual_MechanicalDesignGeometricPresentationRepresentation;
class StepVisual_PresentationArea;
class StepBasic_Product;
class StepBasic_ProductDefinition;
class StepBasic_ProductDefinitionFormation;
class StepBasic_ProductDefinitionRelationship;
class StepRepr_PropertyDefinition;
class StepShape_ShapeRepresentation;
class StepBasic_SecurityClassification;
class StepRepr_ConfigurationItem;
class StepBasic_Date;
class StepBasic_Document;
class StepBasic_Effectivity;
class StepBasic_Group;
class StepBasic_GroupRelationship;
class StepBasic_ProductDefinitionFormationRelationship;
class StepRepr_Representation;
class StepRepr_ShapeAspectRelationship;

class StepAP214_ApprovalItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP214_ApprovalItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT virtual occ::handle<StepRepr_AssemblyComponentUsageSubstitute>
    AssemblyComponentUsageSubstitute() const;

  Standard_EXPORT virtual occ::handle<StepBasic_DocumentFile> DocumentFile() const;

  Standard_EXPORT virtual occ::handle<StepRepr_MaterialDesignation> MaterialDesignation() const;

  Standard_EXPORT virtual occ::handle<
    StepVisual_MechanicalDesignGeometricPresentationRepresentation>
    MechanicalDesignGeometricPresentationRepresentation() const;

  Standard_EXPORT virtual occ::handle<StepVisual_PresentationArea> PresentationArea() const;

  Standard_EXPORT virtual occ::handle<StepBasic_Product> Product() const;

  Standard_EXPORT virtual occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  Standard_EXPORT virtual occ::handle<StepBasic_ProductDefinitionFormation>
    ProductDefinitionFormation() const;

  Standard_EXPORT virtual occ::handle<StepBasic_ProductDefinitionRelationship>
    ProductDefinitionRelationship() const;

  Standard_EXPORT virtual occ::handle<StepRepr_PropertyDefinition> PropertyDefinition() const;

  Standard_EXPORT virtual occ::handle<StepShape_ShapeRepresentation> ShapeRepresentation() const;

  Standard_EXPORT virtual occ::handle<StepBasic_SecurityClassification> SecurityClassification()
    const;

  Standard_EXPORT virtual occ::handle<StepRepr_ConfigurationItem> ConfigurationItem() const;

  Standard_EXPORT virtual occ::handle<StepBasic_Date> Date() const;

  Standard_EXPORT virtual occ::handle<StepBasic_Document> Document() const;

  Standard_EXPORT virtual occ::handle<StepBasic_Effectivity> Effectivity() const;

  Standard_EXPORT virtual occ::handle<StepBasic_Group> Group() const;

  Standard_EXPORT virtual occ::handle<StepBasic_GroupRelationship> GroupRelationship() const;

  Standard_EXPORT virtual occ::handle<StepBasic_ProductDefinitionFormationRelationship>
    ProductDefinitionFormationRelationship() const;

  Standard_EXPORT virtual occ::handle<StepRepr_Representation> Representation() const;

  Standard_EXPORT virtual occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship()
    const;
};
