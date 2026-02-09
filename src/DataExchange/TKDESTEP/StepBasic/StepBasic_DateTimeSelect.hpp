#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_Date;
class StepBasic_LocalTime;
class StepBasic_DateAndTime;

class StepBasic_DateTimeSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepBasic_DateTimeSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_Date> Date() const;

  Standard_EXPORT occ::handle<StepBasic_LocalTime> LocalTime() const;

  Standard_EXPORT occ::handle<StepBasic_DateAndTime> DateAndTime() const;
};
