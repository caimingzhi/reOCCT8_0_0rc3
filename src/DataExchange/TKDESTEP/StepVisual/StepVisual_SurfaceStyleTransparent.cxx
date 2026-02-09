

#include <StepVisual_SurfaceStyleTransparent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleTransparent, Standard_Transient)

StepVisual_SurfaceStyleTransparent::StepVisual_SurfaceStyleTransparent() = default;

void StepVisual_SurfaceStyleTransparent::Init(const double theTransparency)
{

  myTransparency = theTransparency;
}

double StepVisual_SurfaceStyleTransparent::Transparency() const
{
  return myTransparency;
}

void StepVisual_SurfaceStyleTransparent::SetTransparency(const double theTransparency)
{
  myTransparency = theTransparency;
}
