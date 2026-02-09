

#include "RWStepVisual_RWPreDefinedItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_PreDefinedItem.hpp>

RWStepVisual_RWPreDefinedItem::RWStepVisual_RWPreDefinedItem() = default;

void RWStepVisual_RWPreDefinedItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepVisual_PreDefinedItem>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "pre_defined_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepVisual_RWPreDefinedItem::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepVisual_PreDefinedItem>& ent) const
{

  SW.Send(ent->Name());
}
