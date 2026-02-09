

#include <StepVisual_SurfaceStyleReflectanceAmbient.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleReflectanceAmbient, Standard_Transient)

StepVisual_SurfaceStyleReflectanceAmbient::StepVisual_SurfaceStyleReflectanceAmbient() = default;

void StepVisual_SurfaceStyleReflectanceAmbient::Init(const double theAmbientReflectance)
{

  myAmbientReflectance = theAmbientReflectance;
}

double StepVisual_SurfaceStyleReflectanceAmbient::AmbientReflectance() const
{
  return myAmbientReflectance;
}

void StepVisual_SurfaceStyleReflectanceAmbient::SetAmbientReflectance(
  const double theAmbientReflectance)
{
  myAmbientReflectance = theAmbientReflectance;
}
