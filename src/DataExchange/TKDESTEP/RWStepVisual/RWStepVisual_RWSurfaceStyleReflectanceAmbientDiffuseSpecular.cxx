

#include "RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuseSpecular.hpp"
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular.hpp>
#include <StepVisual_Colour.hpp>
#include <Standard_Real.hpp>

RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuseSpecular::
  RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuseSpecular() = default;

void RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuseSpecular::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                  theData,
  const int                                                                    theNum,
  occ::handle<Interface_Check>&                                                theAch,
  const occ::handle<StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular>& theEnt) const
{

  if (!theData->CheckNbParams(theNum,
                              5,
                              theAch,
                              "surface_style_reflectance_ambient_diffuse_specular"))
    return;

  double aAmbientReflectance;
  theData->ReadReal(theNum, 1, "ambient_reflectance", theAch, aAmbientReflectance);

  double aDiffuseReflectance;
  theData->ReadReal(theNum, 2, "diffuse_reflectance", theAch, aDiffuseReflectance);

  double aSpecularReflectance;
  theData->ReadReal(theNum, 3, "specular_reflectance", theAch, aSpecularReflectance);

  double aSpecularExponent;
  theData->ReadReal(theNum, 4, "specular_exponent", theAch, aSpecularExponent);

  occ::handle<StepVisual_Colour> aSpecularColour;
  theData->ReadEntity(theNum,
                      5,
                      "specular_colour",
                      theAch,
                      STANDARD_TYPE(StepVisual_Colour),
                      aSpecularColour);

  theEnt->Init(aAmbientReflectance,
               aDiffuseReflectance,
               aSpecularReflectance,
               aSpecularExponent,
               aSpecularColour);
}

void RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuseSpecular::WriteStep(
  StepData_StepWriter&                                                         theSW,
  const occ::handle<StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular>& theEnt) const
{

  theSW.Send(theEnt->AmbientReflectance());

  theSW.Send(theEnt->DiffuseReflectance());

  theSW.Send(theEnt->SpecularReflectance());
  theSW.Send(theEnt->SpecularExponent());
  theSW.Send(theEnt->SpecularColour());
}

void RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuseSpecular::Share(
  const occ::handle<StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular>& theEnt,
  Interface_EntityIterator&                                                    theIter) const
{

  theIter.AddItem(theEnt->SpecularColour());
}
