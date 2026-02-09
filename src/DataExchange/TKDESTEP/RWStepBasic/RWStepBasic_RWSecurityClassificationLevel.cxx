

#include "RWStepBasic_RWSecurityClassificationLevel.hpp"
#include <StepBasic_SecurityClassificationLevel.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWSecurityClassificationLevel::RWStepBasic_RWSecurityClassificationLevel() = default;

void RWStepBasic_RWSecurityClassificationLevel::ReadStep(
  const occ::handle<StepData_StepReaderData>&               data,
  const int                                                 num,
  occ::handle<Interface_Check>&                             ach,
  const occ::handle<StepBasic_SecurityClassificationLevel>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "security_classification_level"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepBasic_RWSecurityClassificationLevel::WriteStep(
  StepData_StepWriter&                                      SW,
  const occ::handle<StepBasic_SecurityClassificationLevel>& ent) const
{

  SW.Send(ent->Name());
}
