

#include "RWStepVisual_RWSurfaceStyleReflectanceAmbient.hpp"
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_SurfaceStyleReflectanceAmbient.hpp>
#include <Standard_Real.hpp>

RWStepVisual_RWSurfaceStyleReflectanceAmbient::RWStepVisual_RWSurfaceStyleReflectanceAmbient() =
  default;

void RWStepVisual_RWSurfaceStyleReflectanceAmbient::ReadStep(
  const occ::handle<StepData_StepReaderData>&                   data,
  const int                                                     num,
  occ::handle<Interface_Check>&                                 ach,
  const occ::handle<StepVisual_SurfaceStyleReflectanceAmbient>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "surface_style_reflectance_ambient"))
    return;

  double aAmbientReflectance;
  data->ReadReal(num, 1, "ambient_reflectance", ach, aAmbientReflectance);

  ent->Init(aAmbientReflectance);
}

void RWStepVisual_RWSurfaceStyleReflectanceAmbient::WriteStep(
  StepData_StepWriter&                                          SW,
  const occ::handle<StepVisual_SurfaceStyleReflectanceAmbient>& ent) const
{

  SW.Send(ent->AmbientReflectance());
}

void RWStepVisual_RWSurfaceStyleReflectanceAmbient::Share(
  const occ::handle<StepVisual_SurfaceStyleReflectanceAmbient>&,
  Interface_EntityIterator&) const
{
}
