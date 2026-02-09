

#include <Standard_Type.hpp>
#include <StepBasic_OrdinalDate.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_OrdinalDate, StepBasic_Date)

StepBasic_OrdinalDate::StepBasic_OrdinalDate() = default;

void StepBasic_OrdinalDate::Init(const int aYearComponent, const int aDayComponent)
{

  dayComponent = aDayComponent;

  StepBasic_Date::Init(aYearComponent);
}

void StepBasic_OrdinalDate::SetDayComponent(const int aDayComponent)
{
  dayComponent = aDayComponent;
}

int StepBasic_OrdinalDate::DayComponent() const
{
  return dayComponent;
}
