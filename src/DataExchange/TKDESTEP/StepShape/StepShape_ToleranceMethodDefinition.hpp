#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepShape_ToleranceValue;
class StepShape_LimitsAndFits;

//! Added for Dimensional Tolerances
class StepShape_ToleranceMethodDefinition : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepShape_ToleranceMethodDefinition();

  //! Recognizes a kind of ValueQualifier Select Type :
  //! 1 -> ToleranceValue from StepShape
  //! 2 -> LimitsAndFits from StepShape
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as ToleranceValue
  Standard_EXPORT occ::handle<StepShape_ToleranceValue> ToleranceValue() const;

  //! Returns Value as LimitsAndFits
  Standard_EXPORT occ::handle<StepShape_LimitsAndFits> LimitsAndFits() const;
};
