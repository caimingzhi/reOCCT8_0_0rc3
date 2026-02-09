

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWPresentedItemRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_PresentedItem.hpp>
#include <StepVisual_PresentedItemRepresentation.hpp>

RWStepVisual_RWPresentedItemRepresentation::RWStepVisual_RWPresentedItemRepresentation() = default;

void RWStepVisual_RWPresentedItemRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                data,
  const int                                                  num,
  occ::handle<Interface_Check>&                              ach,
  const occ::handle<StepVisual_PresentedItemRepresentation>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "presented_item_representation"))
    return;

  StepVisual_PresentationRepresentationSelect prs;

  data->ReadEntity(num, 1, "date_time", ach, prs);

  occ::handle<StepVisual_PresentedItem> pi;

  data->ReadEntity(num, 2, "dated_approval", ach, STANDARD_TYPE(StepVisual_PresentedItem), pi);

  ent->Init(prs, pi);
}

void RWStepVisual_RWPresentedItemRepresentation::WriteStep(
  StepData_StepWriter&                                       SW,
  const occ::handle<StepVisual_PresentedItemRepresentation>& ent) const
{

  SW.Send(ent->Presentation().Value());
  SW.Send(ent->Item());
}

void RWStepVisual_RWPresentedItemRepresentation::Share(
  const occ::handle<StepVisual_PresentedItemRepresentation>& ent,
  Interface_EntityIterator&                                  iter) const
{

  iter.GetOneItem(ent->Presentation().Value());
  iter.GetOneItem(ent->Item());
}
