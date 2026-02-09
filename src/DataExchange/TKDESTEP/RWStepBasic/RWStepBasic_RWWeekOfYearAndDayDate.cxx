

#include "RWStepBasic_RWWeekOfYearAndDayDate.hpp"
#include <StepBasic_WeekOfYearAndDayDate.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWWeekOfYearAndDayDate::RWStepBasic_RWWeekOfYearAndDayDate() = default;

void RWStepBasic_RWWeekOfYearAndDayDate::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepBasic_WeekOfYearAndDayDate>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "week_of_year_and_day_date"))
    return;

  int aYearComponent;

  data->ReadInteger(num, 1, "year_component", ach, aYearComponent);

  int aWeekComponent;

  data->ReadInteger(num, 2, "week_component", ach, aWeekComponent);

  int  aDayComponent;
  bool hasAdayComponent = true;
  if (data->IsParamDefined(num, 3))
  {

    data->ReadInteger(num, 3, "day_component", ach, aDayComponent);
  }
  else
  {
    hasAdayComponent = false;
    aDayComponent    = 0;
  }

  ent->Init(aYearComponent, aWeekComponent, hasAdayComponent, aDayComponent);
}

void RWStepBasic_RWWeekOfYearAndDayDate::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepBasic_WeekOfYearAndDayDate>& ent) const
{

  SW.Send(ent->YearComponent());

  SW.Send(ent->WeekComponent());

  bool hasAdayComponent = ent->HasDayComponent();
  if (hasAdayComponent)
  {
    SW.Send(ent->DayComponent());
  }
  else
  {
    SW.SendUndef();
  }
}
