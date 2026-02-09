#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepRepr_ProductDefinitionShape;
class StepRepr_ShapeAspect;
class StepRepr_ShapeAspectRelationship;

class StepRepr_ShapeDefinition : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepRepr_ShapeDefinition();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepRepr_ProductDefinitionShape> ProductDefinitionShape() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship() const;
};
