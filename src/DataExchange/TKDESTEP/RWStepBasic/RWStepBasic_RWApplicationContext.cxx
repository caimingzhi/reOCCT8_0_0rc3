

#include "RWStepBasic_RWApplicationContext.hpp"
#include <StepBasic_ApplicationContext.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWApplicationContext::RWStepBasic_RWApplicationContext() = default;

void RWStepBasic_RWApplicationContext::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepBasic_ApplicationContext>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "application_context"))
    return;

  occ::handle<TCollection_HAsciiString> aApplication;

  data->ReadString(num, 1, "application", ach, aApplication);

  ent->Init(aApplication);
}

void RWStepBasic_RWApplicationContext::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepBasic_ApplicationContext>& ent) const
{

  SW.Send(ent->Application());
}
