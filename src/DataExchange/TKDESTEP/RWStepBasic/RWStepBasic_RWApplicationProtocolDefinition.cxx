

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWApplicationProtocolDefinition.hpp"
#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ApplicationProtocolDefinition.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWApplicationProtocolDefinition::RWStepBasic_RWApplicationProtocolDefinition() =
  default;

void RWStepBasic_RWApplicationProtocolDefinition::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepBasic_ApplicationProtocolDefinition>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "application_protocol_definition"))
    return;

  occ::handle<TCollection_HAsciiString> aStatus;

  data->ReadString(num, 1, "status", ach, aStatus);

  occ::handle<TCollection_HAsciiString> aApplicationInterpretedModelSchemaName;

  data->ReadString(num,
                   2,
                   "application_interpreted_model_schema_name",
                   ach,
                   aApplicationInterpretedModelSchemaName);

  int aApplicationProtocolYear;

  data->ReadInteger(num, 3, "application_protocol_year", ach, aApplicationProtocolYear);

  occ::handle<StepBasic_ApplicationContext> aApplication;

  data->ReadEntity(num,
                   4,
                   "application",
                   ach,
                   STANDARD_TYPE(StepBasic_ApplicationContext),
                   aApplication);

  ent->Init(aStatus,
            aApplicationInterpretedModelSchemaName,
            aApplicationProtocolYear,
            aApplication);
}

void RWStepBasic_RWApplicationProtocolDefinition::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepBasic_ApplicationProtocolDefinition>& ent) const
{

  SW.Send(ent->Status());

  SW.Send(ent->ApplicationInterpretedModelSchemaName());

  SW.Send(ent->ApplicationProtocolYear());

  SW.Send(ent->Application());
}

void RWStepBasic_RWApplicationProtocolDefinition::Share(
  const occ::handle<StepBasic_ApplicationProtocolDefinition>& ent,
  Interface_EntityIterator&                                   iter) const
{

  iter.GetOneItem(ent->Application());
}
