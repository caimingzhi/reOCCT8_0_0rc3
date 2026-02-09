#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_GeneralProperty;
class StepRepr_PropertyDefinition;
class StepRepr_PropertyDefinitionRelationship;
class StepRepr_ShapeAspect;
class StepRepr_ShapeAspectRelationship;

class StepRepr_RepresentedDefinition : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepRepr_RepresentedDefinition();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_GeneralProperty> GeneralProperty() const;

  Standard_EXPORT occ::handle<StepRepr_PropertyDefinition> PropertyDefinition() const;

  Standard_EXPORT occ::handle<StepRepr_PropertyDefinitionRelationship>
                  PropertyDefinitionRelationship() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship() const;
};
