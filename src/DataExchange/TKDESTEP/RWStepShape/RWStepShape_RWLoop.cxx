

#include "RWStepShape_RWLoop.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_Loop.hpp>

RWStepShape_RWLoop::RWStepShape_RWLoop() = default;

void RWStepShape_RWLoop::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                  const int                                   num,
                                  occ::handle<Interface_Check>&               ach,
                                  const occ::handle<StepShape_Loop>&          ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "loop"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepShape_RWLoop::WriteStep(StepData_StepWriter&               SW,
                                   const occ::handle<StepShape_Loop>& ent) const
{

  SW.Send(ent->Name());
}
