

#include <Standard_Type.hpp>
#include <StepBasic_WeekOfYearAndDayDate.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_WeekOfYearAndDayDate, StepBasic_Date)

StepBasic_WeekOfYearAndDayDate::StepBasic_WeekOfYearAndDayDate() = default;

void StepBasic_WeekOfYearAndDayDate::Init(const int  aYearComponent,
                                          const int  aWeekComponent,
                                          const bool hasAdayComponent,
                                          const int  aDayComponent)
{

  weekComponent   = aWeekComponent;
  hasDayComponent = hasAdayComponent;
  dayComponent    = aDayComponent;

  StepBasic_Date::Init(aYearComponent);
}

void StepBasic_WeekOfYearAndDayDate::SetWeekComponent(const int aWeekComponent)
{
  weekComponent = aWeekComponent;
}

int StepBasic_WeekOfYearAndDayDate::WeekComponent() const
{
  return weekComponent;
}

void StepBasic_WeekOfYearAndDayDate::SetDayComponent(const int aDayComponent)
{
  dayComponent    = aDayComponent;
  hasDayComponent = true;
}

void StepBasic_WeekOfYearAndDayDate::UnSetDayComponent()
{
  hasDayComponent = false;
}

int StepBasic_WeekOfYearAndDayDate::DayComponent() const
{
  return dayComponent;
}

bool StepBasic_WeekOfYearAndDayDate::HasDayComponent() const
{
  return hasDayComponent;
}
