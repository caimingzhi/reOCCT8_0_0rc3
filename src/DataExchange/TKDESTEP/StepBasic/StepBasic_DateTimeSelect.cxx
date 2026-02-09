

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepBasic_Date.hpp>
#include <StepBasic_DateAndTime.hpp>
#include <StepBasic_DateTimeSelect.hpp>
#include <StepBasic_LocalTime.hpp>

StepBasic_DateTimeSelect::StepBasic_DateTimeSelect() = default;

int StepBasic_DateTimeSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Date)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_LocalTime)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_DateAndTime)))
    return 3;
  return 0;
}

occ::handle<StepBasic_Date> StepBasic_DateTimeSelect::Date() const
{
  return GetCasted(StepBasic_Date, Value());
}

occ::handle<StepBasic_LocalTime> StepBasic_DateTimeSelect::LocalTime() const
{
  return GetCasted(StepBasic_LocalTime, Value());
}

occ::handle<StepBasic_DateAndTime> StepBasic_DateTimeSelect::DateAndTime() const
{
  return GetCasted(StepBasic_DateAndTime, Value());
}
