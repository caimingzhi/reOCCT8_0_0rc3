

#include "RWStepBasic_RWDateRole.hpp"
#include <StepBasic_DateRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWDateRole::RWStepBasic_RWDateRole() = default;

void RWStepBasic_RWDateRole::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepBasic_DateRole>&      ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "date_role"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepBasic_RWDateRole::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepBasic_DateRole>& ent) const
{

  SW.Send(ent->Name());
}
