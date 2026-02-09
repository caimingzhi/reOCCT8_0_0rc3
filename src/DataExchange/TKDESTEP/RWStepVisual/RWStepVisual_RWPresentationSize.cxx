

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWPresentationSize.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_PlanarBox.hpp>
#include <StepVisual_PresentationSize.hpp>
#include <StepVisual_PresentationSizeAssignmentSelect.hpp>

RWStepVisual_RWPresentationSize::RWStepVisual_RWPresentationSize() = default;

void RWStepVisual_RWPresentationSize::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepVisual_PresentationSize>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "presentation_size"))
    return;

  StepVisual_PresentationSizeAssignmentSelect aUnit;

  data->ReadEntity(num, 1, "unit", ach, aUnit);

  occ::handle<StepVisual_PlanarBox> aSize;

  data->ReadEntity(num, 2, "size", ach, STANDARD_TYPE(StepVisual_PlanarBox), aSize);

  ent->Init(aUnit, aSize);
}

void RWStepVisual_RWPresentationSize::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepVisual_PresentationSize>& ent) const
{

  SW.Send(ent->Unit().Value());

  SW.Send(ent->Size());
}

void RWStepVisual_RWPresentationSize::Share(const occ::handle<StepVisual_PresentationSize>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->Unit().Value());

  iter.GetOneItem(ent->Size());
}
