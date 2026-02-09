

#include <Standard_Type.hpp>
#include <StepBasic_CoordinatedUniversalTimeOffset.hpp>
#include <StepBasic_LocalTime.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_LocalTime, Standard_Transient)

StepBasic_LocalTime::StepBasic_LocalTime() = default;

void StepBasic_LocalTime::Init(const int    aHourComponent,
                               const bool   hasAminuteComponent,
                               const int    aMinuteComponent,
                               const bool   hasAsecondComponent,
                               const double aSecondComponent,
                               const occ::handle<StepBasic_CoordinatedUniversalTimeOffset>& aZone)
{

  hourComponent      = aHourComponent;
  hasMinuteComponent = hasAminuteComponent;
  minuteComponent    = aMinuteComponent;
  hasSecondComponent = hasAsecondComponent;
  secondComponent    = aSecondComponent;
  zone               = aZone;
}

void StepBasic_LocalTime::SetHourComponent(const int aHourComponent)
{
  hourComponent = aHourComponent;
}

int StepBasic_LocalTime::HourComponent() const
{
  return hourComponent;
}

void StepBasic_LocalTime::SetMinuteComponent(const int aMinuteComponent)
{
  minuteComponent    = aMinuteComponent;
  hasMinuteComponent = true;
}

void StepBasic_LocalTime::UnSetMinuteComponent()
{
  hasMinuteComponent = false;
}

int StepBasic_LocalTime::MinuteComponent() const
{
  return minuteComponent;
}

bool StepBasic_LocalTime::HasMinuteComponent() const
{
  return hasMinuteComponent;
}

void StepBasic_LocalTime::SetSecondComponent(const double aSecondComponent)
{
  secondComponent    = aSecondComponent;
  hasSecondComponent = true;
}

void StepBasic_LocalTime::UnSetSecondComponent()
{
  hasSecondComponent = false;
}

double StepBasic_LocalTime::SecondComponent() const
{
  return secondComponent;
}

bool StepBasic_LocalTime::HasSecondComponent() const
{
  return hasSecondComponent;
}

void StepBasic_LocalTime::SetZone(
  const occ::handle<StepBasic_CoordinatedUniversalTimeOffset>& aZone)
{
  zone = aZone;
}

occ::handle<StepBasic_CoordinatedUniversalTimeOffset> StepBasic_LocalTime::Zone() const
{
  return zone;
}
