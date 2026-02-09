#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepGeom_GeometricRepresentationItem;
class StepBasic_GroupRelationship;
class StepRepr_MappedItem;
class StepBasic_ProductDefinition;
class StepBasic_ProductDefinitionFormation;
class StepRepr_PropertyDefinitionRepresentation;
class StepRepr_Representation;
class StepRepr_RepresentationItem;
class StepRepr_RepresentationRelationshipWithTransformation;
class StepRepr_ShapeAspect;
class StepRepr_ShapeAspectRelationship;
class StepRepr_ShapeRepresentationRelationship;
class StepVisual_StyledItem;
class StepShape_TopologicalRepresentationItem;

class StepAP214_GroupItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP214_GroupItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT virtual occ::handle<StepGeom_GeometricRepresentationItem>
    GeometricRepresentationItem() const;

  Standard_EXPORT virtual occ::handle<StepBasic_GroupRelationship> GroupRelationship() const;

  Standard_EXPORT virtual occ::handle<StepRepr_MappedItem> MappedItem() const;

  Standard_EXPORT virtual occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  Standard_EXPORT virtual occ::handle<StepBasic_ProductDefinitionFormation>
    ProductDefinitionFormation() const;

  Standard_EXPORT virtual occ::handle<StepRepr_PropertyDefinitionRepresentation>
    PropertyDefinitionRepresentation() const;

  Standard_EXPORT virtual occ::handle<StepRepr_Representation> Representation() const;

  Standard_EXPORT virtual occ::handle<StepRepr_RepresentationItem> RepresentationItem() const;

  Standard_EXPORT virtual occ::handle<StepRepr_RepresentationRelationshipWithTransformation>
    RepresentationRelationshipWithTransformation() const;

  Standard_EXPORT virtual occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  Standard_EXPORT virtual occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship()
    const;

  Standard_EXPORT virtual occ::handle<StepRepr_ShapeRepresentationRelationship>
    ShapeRepresentationRelationship() const;

  Standard_EXPORT virtual occ::handle<StepVisual_StyledItem> StyledItem() const;

  Standard_EXPORT virtual occ::handle<StepShape_TopologicalRepresentationItem>
    TopologicalRepresentationItem() const;
};
