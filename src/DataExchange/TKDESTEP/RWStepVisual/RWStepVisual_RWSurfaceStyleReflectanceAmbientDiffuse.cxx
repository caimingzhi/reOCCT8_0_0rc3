

#include "RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuse.hpp"
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_SurfaceStyleReflectanceAmbientDiffuse.hpp>
#include <Standard_Real.hpp>

RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuse::
  RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuse() = default;

void RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuse::ReadStep(
  const occ::handle<StepData_StepReaderData>&                          theData,
  const int                                                            theNum,
  occ::handle<Interface_Check>&                                        theAch,
  const occ::handle<StepVisual_SurfaceStyleReflectanceAmbientDiffuse>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 2, theAch, "surface_style_reflectance_ambient_diffuse"))
    return;

  double aAmbientReflectance;
  theData->ReadReal(theNum, 1, "ambient_reflectance", theAch, aAmbientReflectance);

  double aDiffuseReflectance;
  theData->ReadReal(theNum, 2, "diffuse_reflectance", theAch, aDiffuseReflectance);

  theEnt->Init(aAmbientReflectance, aDiffuseReflectance);
}

void RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuse::WriteStep(
  StepData_StepWriter&                                                 theSW,
  const occ::handle<StepVisual_SurfaceStyleReflectanceAmbientDiffuse>& theEnt) const
{

  theSW.Send(theEnt->AmbientReflectance());

  theSW.Send(theEnt->DiffuseReflectance());
}

void RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuse::Share(
  const occ::handle<StepVisual_SurfaceStyleReflectanceAmbientDiffuse>&,
  Interface_EntityIterator&) const
{
}
