#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ProductDefinitionRelationship;
class StepBasic_ProductDefinition;
class StepRepr_ProductDefinitionShape;
class StepRepr_RepresentationRelationship;
class StepRepr_ShapeAspect;
class StepBasic_DocumentRelationship;

class StepAP214_AutoDesignPresentedItemSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP214_AutoDesignPresentedItemSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionRelationship>
                  ProductDefinitionRelationship() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  Standard_EXPORT occ::handle<StepRepr_ProductDefinitionShape> ProductDefinitionShape() const;

  Standard_EXPORT occ::handle<StepRepr_RepresentationRelationship> RepresentationRelationship()
    const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  Standard_EXPORT occ::handle<StepBasic_DocumentRelationship> DocumentRelationship() const;
};
