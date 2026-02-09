#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ProductDefinition;
class StepRepr_ShapeAspect;

class StepAP203_SpecifiedItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP203_SpecifiedItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;
};
