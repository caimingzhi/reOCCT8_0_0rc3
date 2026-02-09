

#include "RWStepBasic_RWDate.hpp"
#include <StepBasic_Date.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWDate::RWStepBasic_RWDate() = default;

void RWStepBasic_RWDate::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                  const int                                   num,
                                  occ::handle<Interface_Check>&               ach,
                                  const occ::handle<StepBasic_Date>&          ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "date"))
    return;

  int aYearComponent;

  data->ReadInteger(num, 1, "year_component", ach, aYearComponent);

  ent->Init(aYearComponent);
}

void RWStepBasic_RWDate::WriteStep(StepData_StepWriter&               SW,
                                   const occ::handle<StepBasic_Date>& ent) const
{

  SW.Send(ent->YearComponent());
}
