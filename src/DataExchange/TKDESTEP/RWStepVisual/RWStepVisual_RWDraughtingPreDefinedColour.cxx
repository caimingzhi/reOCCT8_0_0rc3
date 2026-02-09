

#include "RWStepVisual_RWDraughtingPreDefinedColour.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_DraughtingPreDefinedColour.hpp>
#include <StepVisual_PreDefinedItem.hpp>

RWStepVisual_RWDraughtingPreDefinedColour::RWStepVisual_RWDraughtingPreDefinedColour() = default;

void RWStepVisual_RWDraughtingPreDefinedColour::ReadStep(
  const occ::handle<StepData_StepReaderData>&               data,
  const int                                                 num,
  occ::handle<Interface_Check>&                             ach,
  const occ::handle<StepVisual_DraughtingPreDefinedColour>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "draughting_pre_defined_colour has not 1 parameter(s)"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->GetPreDefinedItem()->Init(aName);
}

void RWStepVisual_RWDraughtingPreDefinedColour::WriteStep(
  StepData_StepWriter&                                      SW,
  const occ::handle<StepVisual_DraughtingPreDefinedColour>& ent) const
{

  SW.Send(ent->GetPreDefinedItem()->Name());
}
