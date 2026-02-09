

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWSurfaceStyleSegmentationCurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_SurfaceStyleSegmentationCurve.hpp>

RWStepVisual_RWSurfaceStyleSegmentationCurve::RWStepVisual_RWSurfaceStyleSegmentationCurve() =
  default;

void RWStepVisual_RWSurfaceStyleSegmentationCurve::ReadStep(
  const occ::handle<StepData_StepReaderData>&                  data,
  const int                                                    num,
  occ::handle<Interface_Check>&                                ach,
  const occ::handle<StepVisual_SurfaceStyleSegmentationCurve>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "surface_style_segmentation_curve"))
    return;

  occ::handle<StepVisual_CurveStyle> aStyleOfSegmentationCurve;

  data->ReadEntity(num,
                   1,
                   "style_of_segmentation_curve",
                   ach,
                   STANDARD_TYPE(StepVisual_CurveStyle),
                   aStyleOfSegmentationCurve);

  ent->Init(aStyleOfSegmentationCurve);
}

void RWStepVisual_RWSurfaceStyleSegmentationCurve::WriteStep(
  StepData_StepWriter&                                         SW,
  const occ::handle<StepVisual_SurfaceStyleSegmentationCurve>& ent) const
{

  SW.Send(ent->StyleOfSegmentationCurve());
}

void RWStepVisual_RWSurfaceStyleSegmentationCurve::Share(
  const occ::handle<StepVisual_SurfaceStyleSegmentationCurve>& ent,
  Interface_EntityIterator&                                    iter) const
{

  iter.GetOneItem(ent->StyleOfSegmentationCurve());
}
