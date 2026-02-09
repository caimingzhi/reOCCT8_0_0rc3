

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWSecurityClassification.hpp"
#include <StepBasic_SecurityClassification.hpp>
#include <StepBasic_SecurityClassificationLevel.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWSecurityClassification::RWStepBasic_RWSecurityClassification() = default;

void RWStepBasic_RWSecurityClassification::ReadStep(
  const occ::handle<StepData_StepReaderData>&          data,
  const int                                            num,
  occ::handle<Interface_Check>&                        ach,
  const occ::handle<StepBasic_SecurityClassification>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "security_classification"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aPurpose;

  data->ReadString(num, 2, "purpose", ach, aPurpose);

  occ::handle<StepBasic_SecurityClassificationLevel> aSecurityLevel;

  data->ReadEntity(num,
                   3,
                   "security_level",
                   ach,
                   STANDARD_TYPE(StepBasic_SecurityClassificationLevel),
                   aSecurityLevel);

  ent->Init(aName, aPurpose, aSecurityLevel);
}

void RWStepBasic_RWSecurityClassification::WriteStep(
  StepData_StepWriter&                                 SW,
  const occ::handle<StepBasic_SecurityClassification>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Purpose());

  SW.Send(ent->SecurityLevel());
}

void RWStepBasic_RWSecurityClassification::Share(
  const occ::handle<StepBasic_SecurityClassification>& ent,
  Interface_EntityIterator&                            iter) const
{

  iter.GetOneItem(ent->SecurityLevel());
}
