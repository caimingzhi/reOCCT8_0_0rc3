#pragma once

#include <Standard.hpp>
#include <StepVisual_SurfaceStyleRendering.hpp>

#include <StepVisual_ShadingSurfaceMethod.hpp>
#include <StepVisual_Colour.hpp>
#include <StepVisual_RenderingPropertiesSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class StepVisual_SurfaceStyleRenderingWithProperties : public StepVisual_SurfaceStyleRendering
{
public:
  Standard_EXPORT StepVisual_SurfaceStyleRenderingWithProperties();

  Standard_EXPORT void Init(
    const StepVisual_ShadingSurfaceMethod theSurfaceStyleRendering_RenderingMethod,
    const occ::handle<StepVisual_Colour>& theSurfaceStyleRendering_SurfaceColour,
    const occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>>& theProperties);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>>
                  Properties() const;

  Standard_EXPORT void SetProperties(
    const occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>>& theProperties);

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleRenderingWithProperties,
                          StepVisual_SurfaceStyleRendering)

private:
  occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>> myProperties;
};
