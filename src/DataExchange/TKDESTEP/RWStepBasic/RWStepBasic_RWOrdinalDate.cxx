

#include "RWStepBasic_RWOrdinalDate.hpp"
#include <StepBasic_OrdinalDate.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWOrdinalDate::RWStepBasic_RWOrdinalDate() = default;

void RWStepBasic_RWOrdinalDate::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepBasic_OrdinalDate>&   ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "ordinal_date"))
    return;

  int aYearComponent;

  data->ReadInteger(num, 1, "year_component", ach, aYearComponent);

  int aDayComponent;

  data->ReadInteger(num, 2, "day_component", ach, aDayComponent);

  ent->Init(aYearComponent, aDayComponent);
}

void RWStepBasic_RWOrdinalDate::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepBasic_OrdinalDate>& ent) const
{

  SW.Send(ent->YearComponent());

  SW.Send(ent->DayComponent());
}
