

#include "RWStepVisual_RWPreDefinedColour.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_PreDefinedColour.hpp>
#include <StepVisual_PreDefinedItem.hpp>

RWStepVisual_RWPreDefinedColour::RWStepVisual_RWPreDefinedColour() = default;

void RWStepVisual_RWPreDefinedColour::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepVisual_PreDefinedColour>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "pre_defined_colour"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->GetPreDefinedItem()->Init(aName);
}

void RWStepVisual_RWPreDefinedColour::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepVisual_PreDefinedColour>& ent) const
{

  SW.Send(ent->GetPreDefinedItem()->Name());
}
