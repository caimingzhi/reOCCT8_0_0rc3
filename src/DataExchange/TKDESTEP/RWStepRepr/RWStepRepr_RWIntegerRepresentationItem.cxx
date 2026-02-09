#include "RWStepRepr_RWIntegerRepresentationItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_IntegerRepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepRepr_RWIntegerRepresentationItem::RWStepRepr_RWIntegerRepresentationItem() = default;

void RWStepRepr_RWIntegerRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepRepr_IntegerRepresentationItem>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "integer_representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  int aValue;
  data->ReadInteger(num, 2, "value", ach, aValue);

  ent->Init(aName, aValue);
}

void RWStepRepr_RWIntegerRepresentationItem::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepRepr_IntegerRepresentationItem>& ent) const
{
  SW.Send(ent->Name());
  SW.Send(ent->Value());
}
