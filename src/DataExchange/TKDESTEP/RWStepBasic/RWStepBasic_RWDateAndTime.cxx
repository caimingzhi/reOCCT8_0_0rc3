

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWDateAndTime.hpp"
#include <StepBasic_Date.hpp>
#include <StepBasic_DateAndTime.hpp>
#include <StepBasic_LocalTime.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWDateAndTime::RWStepBasic_RWDateAndTime() = default;

void RWStepBasic_RWDateAndTime::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepBasic_DateAndTime>&   ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "date_and_time"))
    return;

  occ::handle<StepBasic_Date> aDateComponent;

  data->ReadEntity(num, 1, "date_component", ach, STANDARD_TYPE(StepBasic_Date), aDateComponent);

  occ::handle<StepBasic_LocalTime> aTimeComponent;

  data
    ->ReadEntity(num, 2, "time_component", ach, STANDARD_TYPE(StepBasic_LocalTime), aTimeComponent);

  ent->Init(aDateComponent, aTimeComponent);
}

void RWStepBasic_RWDateAndTime::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepBasic_DateAndTime>& ent) const
{

  SW.Send(ent->DateComponent());

  SW.Send(ent->TimeComponent());
}

void RWStepBasic_RWDateAndTime::Share(const occ::handle<StepBasic_DateAndTime>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  iter.GetOneItem(ent->DateComponent());

  iter.GetOneItem(ent->TimeComponent());
}
