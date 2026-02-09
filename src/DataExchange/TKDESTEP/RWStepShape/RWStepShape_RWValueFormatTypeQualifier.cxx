#include "RWStepShape_RWValueFormatTypeQualifier.hpp"

#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_ValueFormatTypeQualifier.hpp>

RWStepShape_RWValueFormatTypeQualifier::RWStepShape_RWValueFormatTypeQualifier() = default;

void RWStepShape_RWValueFormatTypeQualifier::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepShape_ValueFormatTypeQualifier>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "value_format_type_qualifier"))
    return;

  occ::handle<TCollection_HAsciiString> aFormatType;
  data->ReadString(num, 1, "format_type", ach, aFormatType);

  ent->Init(aFormatType);
}

void RWStepShape_RWValueFormatTypeQualifier::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepShape_ValueFormatTypeQualifier>& ent) const
{
  SW.Send(ent->FormatType());
}
