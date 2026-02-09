

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWSurfaceStyleFillArea.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_FillAreaStyle.hpp>
#include <StepVisual_SurfaceStyleFillArea.hpp>

RWStepVisual_RWSurfaceStyleFillArea::RWStepVisual_RWSurfaceStyleFillArea() = default;

void RWStepVisual_RWSurfaceStyleFillArea::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepVisual_SurfaceStyleFillArea>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "surface_style_fill_area"))
    return;

  occ::handle<StepVisual_FillAreaStyle> aFillArea;

  data->ReadEntity(num, 1, "fill_area", ach, STANDARD_TYPE(StepVisual_FillAreaStyle), aFillArea);

  ent->Init(aFillArea);
}

void RWStepVisual_RWSurfaceStyleFillArea::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepVisual_SurfaceStyleFillArea>& ent) const
{

  SW.Send(ent->FillArea());
}

void RWStepVisual_RWSurfaceStyleFillArea::Share(
  const occ::handle<StepVisual_SurfaceStyleFillArea>& ent,
  Interface_EntityIterator&                           iter) const
{

  iter.GetOneItem(ent->FillArea());
}
