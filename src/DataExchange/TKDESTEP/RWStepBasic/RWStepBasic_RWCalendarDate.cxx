

#include "RWStepBasic_RWCalendarDate.hpp"
#include <StepBasic_CalendarDate.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWCalendarDate::RWStepBasic_RWCalendarDate() = default;

void RWStepBasic_RWCalendarDate::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepBasic_CalendarDate>&  ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "calendar_date"))
    return;

  int aYearComponent;

  data->ReadInteger(num, 1, "year_component", ach, aYearComponent);

  int aDayComponent;

  data->ReadInteger(num, 2, "day_component", ach, aDayComponent);

  int aMonthComponent;

  data->ReadInteger(num, 3, "month_component", ach, aMonthComponent);

  ent->Init(aYearComponent, aDayComponent, aMonthComponent);
}

void RWStepBasic_RWCalendarDate::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepBasic_CalendarDate>& ent) const
{

  SW.Send(ent->YearComponent());

  SW.Send(ent->DayComponent());

  SW.Send(ent->MonthComponent());
}
