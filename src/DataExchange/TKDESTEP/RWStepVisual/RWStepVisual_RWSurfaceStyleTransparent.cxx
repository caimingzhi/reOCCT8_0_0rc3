

#include "RWStepVisual_RWSurfaceStyleTransparent.hpp"
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_SurfaceStyleTransparent.hpp>
#include <Standard_Real.hpp>

RWStepVisual_RWSurfaceStyleTransparent::RWStepVisual_RWSurfaceStyleTransparent() = default;

void RWStepVisual_RWSurfaceStyleTransparent::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepVisual_SurfaceStyleTransparent>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "surface_style_transparent"))
    return;

  double aTransparency;
  data->ReadReal(num, 1, "transparency", ach, aTransparency);

  ent->Init(aTransparency);
}

void RWStepVisual_RWSurfaceStyleTransparent::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepVisual_SurfaceStyleTransparent>& ent) const
{

  SW.Send(ent->Transparency());
}

void RWStepVisual_RWSurfaceStyleTransparent::Share(
  const occ::handle<StepVisual_SurfaceStyleTransparent>&,
  Interface_EntityIterator&) const
{
}
