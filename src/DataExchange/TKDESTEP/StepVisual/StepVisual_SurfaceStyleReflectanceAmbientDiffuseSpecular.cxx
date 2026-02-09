

#include <StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular,
                           StepVisual_SurfaceStyleReflectanceAmbientDiffuse)

StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular::
  StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular() = default;

void StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular::Init(
  const double                          theAmbientReflectance,
  const double                          theDiffuseReflectance,
  const double                          theSpecularReflectance,
  const double                          theSpecularExponent,
  const occ::handle<StepVisual_Colour>& theSpecularColour)
{
  StepVisual_SurfaceStyleReflectanceAmbientDiffuse::Init(theAmbientReflectance,
                                                         theDiffuseReflectance);
  mySpecularReflectance = theSpecularReflectance;
  mySpecularExponent    = theSpecularExponent;
  mySpecularColour      = theSpecularColour;
}

double StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular::SpecularReflectance() const
{
  return mySpecularReflectance;
}

void StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular::SetSpecularReflectance(
  const double theSpecularReflectance)
{
  mySpecularReflectance = theSpecularReflectance;
}

double StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular::SpecularExponent() const
{
  return mySpecularExponent;
}

void StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular::SetSpecularExponent(
  const double theSpecularExponent)
{
  mySpecularExponent = theSpecularExponent;
}

occ::handle<StepVisual_Colour> StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular::
  SpecularColour() const
{
  return mySpecularColour;
}

void StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular::SetSpecularColour(
  const occ::handle<StepVisual_Colour>& theSpecularColour)
{
  mySpecularColour = theSpecularColour;
}
