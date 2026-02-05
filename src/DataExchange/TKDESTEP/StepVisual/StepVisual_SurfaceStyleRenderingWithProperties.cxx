// Created on : Thu May 14 15:13:19 2020

#include <StepVisual_SurfaceStyleRenderingWithProperties.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleRenderingWithProperties,
                           StepVisual_SurfaceStyleRendering)

//=================================================================================================

StepVisual_SurfaceStyleRenderingWithProperties::StepVisual_SurfaceStyleRenderingWithProperties() =
  default;

//=================================================================================================

void StepVisual_SurfaceStyleRenderingWithProperties::Init(
  const StepVisual_ShadingSurfaceMethod theSurfaceStyleRendering_RenderingMethod,
  const occ::handle<StepVisual_Colour>& theSurfaceStyleRendering_SurfaceColour,
  const occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>>& theProperties)
{
  StepVisual_SurfaceStyleRendering::Init(theSurfaceStyleRendering_RenderingMethod,
                                         theSurfaceStyleRendering_SurfaceColour);

  myProperties = theProperties;
}

//=================================================================================================

occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>>
  StepVisual_SurfaceStyleRenderingWithProperties::Properties() const
{
  return myProperties;
}

//=================================================================================================

void StepVisual_SurfaceStyleRenderingWithProperties::SetProperties(
  const occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>>& theProperties)
{
  myProperties = theProperties;
}
