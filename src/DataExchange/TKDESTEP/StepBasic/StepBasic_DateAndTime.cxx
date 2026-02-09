

#include <Standard_Type.hpp>
#include <StepBasic_Date.hpp>
#include <StepBasic_DateAndTime.hpp>
#include <StepBasic_LocalTime.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DateAndTime, Standard_Transient)

StepBasic_DateAndTime::StepBasic_DateAndTime() = default;

void StepBasic_DateAndTime::Init(const occ::handle<StepBasic_Date>&      aDateComponent,
                                 const occ::handle<StepBasic_LocalTime>& aTimeComponent)
{

  dateComponent = aDateComponent;
  timeComponent = aTimeComponent;
}

void StepBasic_DateAndTime::SetDateComponent(const occ::handle<StepBasic_Date>& aDateComponent)
{
  dateComponent = aDateComponent;
}

occ::handle<StepBasic_Date> StepBasic_DateAndTime::DateComponent() const
{
  return dateComponent;
}

void StepBasic_DateAndTime::SetTimeComponent(const occ::handle<StepBasic_LocalTime>& aTimeComponent)
{
  timeComponent = aTimeComponent;
}

occ::handle<StepBasic_LocalTime> StepBasic_DateAndTime::TimeComponent() const
{
  return timeComponent;
}
