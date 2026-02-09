

#include <Standard_Type.hpp>
#include <StepBasic_CalendarDate.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_CalendarDate, StepBasic_Date)

StepBasic_CalendarDate::StepBasic_CalendarDate() = default;

void StepBasic_CalendarDate::Init(const int aYearComponent,
                                  const int aDayComponent,
                                  const int aMonthComponent)
{

  dayComponent   = aDayComponent;
  monthComponent = aMonthComponent;

  StepBasic_Date::Init(aYearComponent);
}

void StepBasic_CalendarDate::SetDayComponent(const int aDayComponent)
{
  dayComponent = aDayComponent;
}

int StepBasic_CalendarDate::DayComponent() const
{
  return dayComponent;
}

void StepBasic_CalendarDate::SetMonthComponent(const int aMonthComponent)
{
  monthComponent = aMonthComponent;
}

int StepBasic_CalendarDate::MonthComponent() const
{
  return monthComponent;
}
