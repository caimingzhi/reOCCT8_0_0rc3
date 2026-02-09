

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWBackgroundColour.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_BackgroundColour.hpp>

RWStepVisual_RWBackgroundColour::RWStepVisual_RWBackgroundColour() = default;

void RWStepVisual_RWBackgroundColour::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepVisual_BackgroundColour>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "background_colour"))
    return;

  StepVisual_AreaOrView aPresentation;

  data->ReadEntity(num, 1, "presentation", ach, aPresentation);

  ent->Init(aPresentation);
}

void RWStepVisual_RWBackgroundColour::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepVisual_BackgroundColour>& ent) const
{

  SW.Send(ent->Presentation().Value());
}

void RWStepVisual_RWBackgroundColour::Share(const occ::handle<StepVisual_BackgroundColour>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->Presentation().Value());
}
