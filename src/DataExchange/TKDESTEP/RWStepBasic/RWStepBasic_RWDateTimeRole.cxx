

#include "RWStepBasic_RWDateTimeRole.hpp"
#include <StepBasic_DateTimeRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWDateTimeRole::RWStepBasic_RWDateTimeRole() = default;

void RWStepBasic_RWDateTimeRole::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepBasic_DateTimeRole>&  ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "date_time_role"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepBasic_RWDateTimeRole::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepBasic_DateTimeRole>& ent) const
{

  SW.Send(ent->Name());
}
