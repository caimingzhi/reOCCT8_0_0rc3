#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class StepBasic_CoordinatedUniversalTimeOffset;

class StepBasic_LocalTime : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_LocalTime();

  Standard_EXPORT void Init(const int    aHourComponent,
                            const bool   hasAminuteComponent,
                            const int    aMinuteComponent,
                            const bool   hasAsecondComponent,
                            const double aSecondComponent,
                            const occ::handle<StepBasic_CoordinatedUniversalTimeOffset>& aZone);

  Standard_EXPORT void SetHourComponent(const int aHourComponent);

  Standard_EXPORT int HourComponent() const;

  Standard_EXPORT void SetMinuteComponent(const int aMinuteComponent);

  Standard_EXPORT void UnSetMinuteComponent();

  Standard_EXPORT int MinuteComponent() const;

  Standard_EXPORT bool HasMinuteComponent() const;

  Standard_EXPORT void SetSecondComponent(const double aSecondComponent);

  Standard_EXPORT void UnSetSecondComponent();

  Standard_EXPORT double SecondComponent() const;

  Standard_EXPORT bool HasSecondComponent() const;

  Standard_EXPORT void SetZone(const occ::handle<StepBasic_CoordinatedUniversalTimeOffset>& aZone);

  Standard_EXPORT occ::handle<StepBasic_CoordinatedUniversalTimeOffset> Zone() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_LocalTime, Standard_Transient)

private:
  int                                                   hourComponent;
  int                                                   minuteComponent;
  double                                                secondComponent;
  occ::handle<StepBasic_CoordinatedUniversalTimeOffset> zone;
  bool                                                  hasMinuteComponent;
  bool                                                  hasSecondComponent;
};
