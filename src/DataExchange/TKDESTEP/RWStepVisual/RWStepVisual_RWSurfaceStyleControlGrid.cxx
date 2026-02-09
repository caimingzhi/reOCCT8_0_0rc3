

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWSurfaceStyleControlGrid.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_SurfaceStyleControlGrid.hpp>

RWStepVisual_RWSurfaceStyleControlGrid::RWStepVisual_RWSurfaceStyleControlGrid() = default;

void RWStepVisual_RWSurfaceStyleControlGrid::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepVisual_SurfaceStyleControlGrid>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "surface_style_control_grid"))
    return;

  occ::handle<StepVisual_CurveStyle> aStyleOfControlGrid;

  data->ReadEntity(num,
                   1,
                   "style_of_control_grid",
                   ach,
                   STANDARD_TYPE(StepVisual_CurveStyle),
                   aStyleOfControlGrid);

  ent->Init(aStyleOfControlGrid);
}

void RWStepVisual_RWSurfaceStyleControlGrid::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepVisual_SurfaceStyleControlGrid>& ent) const
{

  SW.Send(ent->StyleOfControlGrid());
}

void RWStepVisual_RWSurfaceStyleControlGrid::Share(
  const occ::handle<StepVisual_SurfaceStyleControlGrid>& ent,
  Interface_EntityIterator&                              iter) const
{

  iter.GetOneItem(ent->StyleOfControlGrid());
}
