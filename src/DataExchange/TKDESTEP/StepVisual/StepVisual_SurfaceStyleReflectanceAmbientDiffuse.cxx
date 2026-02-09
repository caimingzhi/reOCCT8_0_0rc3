

#include <StepVisual_SurfaceStyleReflectanceAmbientDiffuse.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleReflectanceAmbientDiffuse,
                           StepVisual_SurfaceStyleReflectanceAmbient)

StepVisual_SurfaceStyleReflectanceAmbientDiffuse::
  StepVisual_SurfaceStyleReflectanceAmbientDiffuse() = default;

void StepVisual_SurfaceStyleReflectanceAmbientDiffuse::Init(const double theAmbientReflectance,
                                                            const double theDiffuseReflectance)
{
  StepVisual_SurfaceStyleReflectanceAmbient::Init(theAmbientReflectance);
  myDiffuseReflectance = theDiffuseReflectance;
}

double StepVisual_SurfaceStyleReflectanceAmbientDiffuse::DiffuseReflectance() const
{
  return myDiffuseReflectance;
}

void StepVisual_SurfaceStyleReflectanceAmbientDiffuse::SetDiffuseReflectance(
  const double theDiffuseReflectance)
{
  myDiffuseReflectance = theDiffuseReflectance;
}
