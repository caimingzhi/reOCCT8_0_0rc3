#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepShape_ToleranceValue;
class StepShape_LimitsAndFits;

class StepShape_ToleranceMethodDefinition : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepShape_ToleranceMethodDefinition();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepShape_ToleranceValue> ToleranceValue() const;

  Standard_EXPORT occ::handle<StepShape_LimitsAndFits> LimitsAndFits() const;
};
