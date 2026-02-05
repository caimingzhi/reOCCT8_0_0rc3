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

  //! Returns a ApprovalItem SelectType
  Standard_EXPORT StepAP214_ApprovalItem();

  //! Recognizes a ApprovalItem Kind Entity that is :
  //! 1 -> AssemblyComponentUsageSubstitute
  //! 2 -> DocumentFile
  //! 3 -> MaterialDesignation
  //! 4 -> MechanicalDesignGeometricPresentationRepresentation
  //! 5 -> PresentationArea
  //! 6 -> Product
  //! 7 -> ProductDefinition
  //! 8 -> ProductDefinitionFormation
  //! 9 -> ProductDefinitionRelationship
  //! 10 -> PropertyDefinition
  //! 11 -> ShapeRepresentation
  //! 12 -> SecurityClassification
  //! 13 -> ConfigurationItem
  //! 14 -> Date
  //! 15 -> Document
  //! 16 -> Effectivity
  //! 17 -> Group
  //! 18 -> GroupRelationship
  //! 19 -> ProductDefinitionFormationRelationship
  //! 20 -> Representation
  //! 21 -> ShapeAspectRelationship
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a AssemblyComponentUsageSubstitute (Null if another type)
  Standard_EXPORT virtual occ::handle<StepRepr_AssemblyComponentUsageSubstitute>
    AssemblyComponentUsageSubstitute() const;

  //! returns Value as a DocumentFile (Null if another type)
  Standard_EXPORT virtual occ::handle<StepBasic_DocumentFile> DocumentFile() const;

  //! returns Value as a MaterialDesignation (Null if another type)
  Standard_EXPORT virtual occ::handle<StepRepr_MaterialDesignation> MaterialDesignation() const;

  //! returns Value as a MechanicalDesignGeometricPresentationRepresentation (Null if another type)
  Standard_EXPORT virtual occ::handle<
    StepVisual_MechanicalDesignGeometricPresentationRepresentation>
    MechanicalDesignGeometricPresentationRepresentation() const;

  //! returns Value as a PresentationArea (Null if another type)
  Standard_EXPORT virtual occ::handle<StepVisual_PresentationArea> PresentationArea() const;

  //! returns Value as a Product (Null if another type)
  Standard_EXPORT virtual occ::handle<StepBasic_Product> Product() const;

  //! returns Value as a ProductDefinition (Null if another type)
  Standard_EXPORT virtual occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  //! returns Value as a ProductDefinitionFormation (Null if another type)
  Standard_EXPORT virtual occ::handle<StepBasic_ProductDefinitionFormation>
    ProductDefinitionFormation() const;

  //! returns Value as aProductDefinitionRelationship (Null if another type)
  Standard_EXPORT virtual occ::handle<StepBasic_ProductDefinitionRelationship>
    ProductDefinitionRelationship() const;

  //! returns Value as a PropertyDefinition (Null if another type)
  Standard_EXPORT virtual occ::handle<StepRepr_PropertyDefinition> PropertyDefinition() const;

  //! returns Value as a ShapeRepresentation (Null if another type)
  Standard_EXPORT virtual occ::handle<StepShape_ShapeRepresentation> ShapeRepresentation() const;

  //! returns Value as a SecurityClassification (Null if another type)
  Standard_EXPORT virtual occ::handle<StepBasic_SecurityClassification> SecurityClassification()
    const;

  //! returns Value as a ConfigurationItem (Null if another type)
  Standard_EXPORT virtual occ::handle<StepRepr_ConfigurationItem> ConfigurationItem() const;

  //! returns Value as a Date (Null if another type)
  Standard_EXPORT virtual occ::handle<StepBasic_Date> Date() const;

  //! returns Value as a Document (Null if another type)
  Standard_EXPORT virtual occ::handle<StepBasic_Document> Document() const;

  //! returns Value as a Effectivity (Null if another type)
  Standard_EXPORT virtual occ::handle<StepBasic_Effectivity> Effectivity() const;

  //! returns Value as a Group (Null if another type)
  Standard_EXPORT virtual occ::handle<StepBasic_Group> Group() const;

  //! returns Value as a GroupRelationship (Null if another type)
  Standard_EXPORT virtual occ::handle<StepBasic_GroupRelationship> GroupRelationship() const;

  //! returns Value as a ProductDefinitionFormationRelationship (Null if another type)
  Standard_EXPORT virtual occ::handle<StepBasic_ProductDefinitionFormationRelationship>
    ProductDefinitionFormationRelationship() const;

  //! returns Value as a Representation (Null if another type)
  Standard_EXPORT virtual occ::handle<StepRepr_Representation> Representation() const;

  //! returns Value as a ShapeAspectRelationship (Null if another type)
  Standard_EXPORT virtual occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship()
    const;
};
