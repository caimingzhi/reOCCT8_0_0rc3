

#include <StepVisual_SurfaceStyleRendering.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleRendering, Standard_Transient)

StepVisual_SurfaceStyleRendering::StepVisual_SurfaceStyleRendering() = default;

void StepVisual_SurfaceStyleRendering::Init(
  const StepVisual_ShadingSurfaceMethod theRenderingMethod,
  const occ::handle<StepVisual_Colour>& theSurfaceColour)
{

  myRenderingMethod = theRenderingMethod;

  mySurfaceColour = theSurfaceColour;
}

StepVisual_ShadingSurfaceMethod StepVisual_SurfaceStyleRendering::RenderingMethod() const
{
  return myRenderingMethod;
}

void StepVisual_SurfaceStyleRendering::SetRenderingMethod(
  const StepVisual_ShadingSurfaceMethod theRenderingMethod)
{
  myRenderingMethod = theRenderingMethod;
}

occ::handle<StepVisual_Colour> StepVisual_SurfaceStyleRendering::SurfaceColour() const
{
  return mySurfaceColour;
}

void StepVisual_SurfaceStyleRendering::SetSurfaceColour(
  const occ::handle<StepVisual_Colour>& theSurfaceColour)
{
  mySurfaceColour = theSurfaceColour;
}
