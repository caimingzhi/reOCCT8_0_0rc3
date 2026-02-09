

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWPresentationLayerUsage.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_PresentationLayerAssignment.hpp>
#include <StepVisual_PresentationLayerUsage.hpp>
#include <StepVisual_PresentationRepresentation.hpp>

RWStepVisual_RWPresentationLayerUsage::RWStepVisual_RWPresentationLayerUsage() = default;

void RWStepVisual_RWPresentationLayerUsage::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepVisual_PresentationLayerUsage>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "presentation_layer_usage"))
    return;

  occ::handle<StepVisual_PresentationLayerAssignment> pla;
  occ::handle<StepVisual_PresentationRepresentation>  pr;

  data->ReadEntity(num,
                   1,
                   "assignment",
                   ach,
                   STANDARD_TYPE(StepVisual_PresentationLayerAssignment),
                   pla);

  data->ReadEntity(num,
                   2,
                   "presentation",
                   ach,
                   STANDARD_TYPE(StepVisual_PresentationRepresentation),
                   pr);

  ent->Init(pla, pr);
}

void RWStepVisual_RWPresentationLayerUsage::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepVisual_PresentationLayerUsage>& ent) const
{

  SW.Send(ent->Assignment());
  SW.Send(ent->Presentation());
}

void RWStepVisual_RWPresentationLayerUsage::Share(
  const occ::handle<StepVisual_PresentationLayerUsage>& ent,
  Interface_EntityIterator&                             iter) const
{
  iter.AddItem(ent->Assignment());
  iter.AddItem(ent->Presentation());
}
