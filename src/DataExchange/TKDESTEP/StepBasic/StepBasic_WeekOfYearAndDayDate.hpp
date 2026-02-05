#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <StepBasic_Date.hpp>

class StepBasic_WeekOfYearAndDayDate : public StepBasic_Date
{

public:
  //! Returns a WeekOfYearAndDayDate
  Standard_EXPORT StepBasic_WeekOfYearAndDayDate();

  Standard_EXPORT void Init(const int  aYearComponent,
                            const int  aWeekComponent,
                            const bool hasAdayComponent,
                            const int  aDayComponent);

  Standard_EXPORT void SetWeekComponent(const int aWeekComponent);

  Standard_EXPORT int WeekComponent() const;

  Standard_EXPORT void SetDayComponent(const int aDayComponent);

  Standard_EXPORT void UnSetDayComponent();

  Standard_EXPORT int DayComponent() const;

  Standard_EXPORT bool HasDayComponent() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_WeekOfYearAndDayDate, StepBasic_Date)

private:
  int  weekComponent;
  int  dayComponent;
  bool hasDayComponent;
};
