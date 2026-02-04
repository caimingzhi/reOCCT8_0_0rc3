#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <StepBasic_Date.hpp>

class StepBasic_CalendarDate : public StepBasic_Date
{

public:
  //! Returns a CalendarDate
  Standard_EXPORT StepBasic_CalendarDate();

  Standard_EXPORT void Init(const int aYearComponent,
                            const int aDayComponent,
                            const int aMonthComponent);

  Standard_EXPORT void SetDayComponent(const int aDayComponent);

  Standard_EXPORT int DayComponent() const;

  Standard_EXPORT void SetMonthComponent(const int aMonthComponent);

  Standard_EXPORT int MonthComponent() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_CalendarDate, StepBasic_Date)

private:
  int dayComponent;
  int monthComponent;
};

