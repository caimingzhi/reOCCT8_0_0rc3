#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <StepBasic_AheadOrBehind.hpp>
#include <Standard_Transient.hpp>

class StepBasic_CoordinatedUniversalTimeOffset : public Standard_Transient
{

public:
  //! Returns a CoordinatedUniversalTimeOffset
  Standard_EXPORT StepBasic_CoordinatedUniversalTimeOffset();

  Standard_EXPORT void Init(const int                     aHourOffset,
                            const bool                    hasAminuteOffset,
                            const int                     aMinuteOffset,
                            const StepBasic_AheadOrBehind aSense);

  Standard_EXPORT void SetHourOffset(const int aHourOffset);

  Standard_EXPORT int HourOffset() const;

  Standard_EXPORT void SetMinuteOffset(const int aMinuteOffset);

  Standard_EXPORT void UnSetMinuteOffset();

  Standard_EXPORT int MinuteOffset() const;

  Standard_EXPORT bool HasMinuteOffset() const;

  Standard_EXPORT void SetSense(const StepBasic_AheadOrBehind aSense);

  Standard_EXPORT StepBasic_AheadOrBehind Sense() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_CoordinatedUniversalTimeOffset, Standard_Transient)

private:
  int                     hourOffset;
  int                     minuteOffset;
  StepBasic_AheadOrBehind sense;
  bool                    hasMinuteOffset;
};

