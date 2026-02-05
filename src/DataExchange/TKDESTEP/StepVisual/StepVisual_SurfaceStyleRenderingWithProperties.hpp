#pragma once

#include <Standard.hpp>
#include <StepVisual_SurfaceStyleRendering.hpp>

#include <StepVisual_ShadingSurfaceMethod.hpp>
#include <StepVisual_Colour.hpp>
#include <StepVisual_RenderingPropertiesSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//! Representation of STEP entity SurfaceStyleRenderingWithProperties
class StepVisual_SurfaceStyleRenderingWithProperties : public StepVisual_SurfaceStyleRendering
{
public:
  //! default constructor
  Standard_EXPORT StepVisual_SurfaceStyleRenderingWithProperties();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const StepVisual_ShadingSurfaceMethod theSurfaceStyleRendering_RenderingMethod,
    const occ::handle<StepVisual_Colour>& theSurfaceStyleRendering_SurfaceColour,
    const occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>>& theProperties);

  //! Returns field Properties
  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>>
                  Properties() const;
  //! Sets field Properties
  Standard_EXPORT void SetProperties(
    const occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>>& theProperties);

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleRenderingWithProperties,
                          StepVisual_SurfaceStyleRendering)

private:
  occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>> myProperties;
};
