

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWSurfaceStyleSilhouette.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_SurfaceStyleSilhouette.hpp>

RWStepVisual_RWSurfaceStyleSilhouette::RWStepVisual_RWSurfaceStyleSilhouette() = default;

void RWStepVisual_RWSurfaceStyleSilhouette::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepVisual_SurfaceStyleSilhouette>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "surface_style_silhouette"))
    return;

  occ::handle<StepVisual_CurveStyle> aStyleOfSilhouette;

  data->ReadEntity(num,
                   1,
                   "style_of_silhouette",
                   ach,
                   STANDARD_TYPE(StepVisual_CurveStyle),
                   aStyleOfSilhouette);

  ent->Init(aStyleOfSilhouette);
}

void RWStepVisual_RWSurfaceStyleSilhouette::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepVisual_SurfaceStyleSilhouette>& ent) const
{

  SW.Send(ent->StyleOfSilhouette());
}

void RWStepVisual_RWSurfaceStyleSilhouette::Share(
  const occ::handle<StepVisual_SurfaceStyleSilhouette>& ent,
  Interface_EntityIterator&                             iter) const
{

  iter.GetOneItem(ent->StyleOfSilhouette());
}
