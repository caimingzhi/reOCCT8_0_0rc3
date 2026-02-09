#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

enum StepElement_UnspecifiedValue
{
  StepElement_Unspecified
};

class Standard_Transient;
class StepData_SelectMember;

class StepElement_MeasureOrUnspecifiedValue : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  Standard_EXPORT void SetContextDependentMeasure(const double aVal);

  Standard_EXPORT double ContextDependentMeasure() const;

  Standard_EXPORT void SetUnspecifiedValue(const StepElement_UnspecifiedValue aVal);

  Standard_EXPORT StepElement_UnspecifiedValue UnspecifiedValue() const;
};
