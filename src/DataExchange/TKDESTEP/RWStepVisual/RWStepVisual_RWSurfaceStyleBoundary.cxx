

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWSurfaceStyleBoundary.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_SurfaceStyleBoundary.hpp>

RWStepVisual_RWSurfaceStyleBoundary::RWStepVisual_RWSurfaceStyleBoundary() = default;

void RWStepVisual_RWSurfaceStyleBoundary::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepVisual_SurfaceStyleBoundary>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "surface_style_boundary"))
    return;

  occ::handle<StepVisual_CurveStyle> aStyleOfBoundary;

  data->ReadEntity(num,
                   1,
                   "style_of_boundary",
                   ach,
                   STANDARD_TYPE(StepVisual_CurveStyle),
                   aStyleOfBoundary);

  ent->Init(aStyleOfBoundary);
}

void RWStepVisual_RWSurfaceStyleBoundary::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepVisual_SurfaceStyleBoundary>& ent) const
{

  SW.Send(ent->StyleOfBoundary());
}

void RWStepVisual_RWSurfaceStyleBoundary::Share(
  const occ::handle<StepVisual_SurfaceStyleBoundary>& ent,
  Interface_EntityIterator&                           iter) const
{

  iter.GetOneItem(ent->StyleOfBoundary());
}
