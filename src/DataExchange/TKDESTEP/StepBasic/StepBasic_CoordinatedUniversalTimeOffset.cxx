

#include <Standard_Type.hpp>
#include <StepBasic_CoordinatedUniversalTimeOffset.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_CoordinatedUniversalTimeOffset, Standard_Transient)

StepBasic_CoordinatedUniversalTimeOffset::StepBasic_CoordinatedUniversalTimeOffset() = default;

void StepBasic_CoordinatedUniversalTimeOffset::Init(const int                     aHourOffset,
                                                    const bool                    hasAminuteOffset,
                                                    const int                     aMinuteOffset,
                                                    const StepBasic_AheadOrBehind aSense)
{

  hourOffset      = aHourOffset;
  hasMinuteOffset = hasAminuteOffset;
  minuteOffset    = aMinuteOffset;
  sense           = aSense;
}

void StepBasic_CoordinatedUniversalTimeOffset::SetHourOffset(const int aHourOffset)
{
  hourOffset = aHourOffset;
}

int StepBasic_CoordinatedUniversalTimeOffset::HourOffset() const
{
  return hourOffset;
}

void StepBasic_CoordinatedUniversalTimeOffset::SetMinuteOffset(const int aMinuteOffset)
{
  minuteOffset    = aMinuteOffset;
  hasMinuteOffset = true;
}

void StepBasic_CoordinatedUniversalTimeOffset::UnSetMinuteOffset()
{
  hasMinuteOffset = false;
}

int StepBasic_CoordinatedUniversalTimeOffset::MinuteOffset() const
{
  return minuteOffset;
}

bool StepBasic_CoordinatedUniversalTimeOffset::HasMinuteOffset() const
{
  return hasMinuteOffset;
}

void StepBasic_CoordinatedUniversalTimeOffset::SetSense(const StepBasic_AheadOrBehind aSense)
{
  sense = aSense;
}

StepBasic_AheadOrBehind StepBasic_CoordinatedUniversalTimeOffset::Sense() const
{
  return sense;
}
