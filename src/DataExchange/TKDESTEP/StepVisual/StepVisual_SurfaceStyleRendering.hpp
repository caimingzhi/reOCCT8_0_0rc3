#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

#include <StepVisual_ShadingSurfaceMethod.hpp>
#include <StepVisual_Colour.hpp>

class StepVisual_SurfaceStyleRendering : public Standard_Transient
{
public:
  Standard_EXPORT StepVisual_SurfaceStyleRendering();

  Standard_EXPORT void Init(const StepVisual_ShadingSurfaceMethod theRenderingMethod,
                            const occ::handle<StepVisual_Colour>& theSurfaceColour);

  Standard_EXPORT StepVisual_ShadingSurfaceMethod RenderingMethod() const;

  Standard_EXPORT void SetRenderingMethod(const StepVisual_ShadingSurfaceMethod theRenderingMethod);

  Standard_EXPORT occ::handle<StepVisual_Colour> SurfaceColour() const;

  Standard_EXPORT void SetSurfaceColour(const occ::handle<StepVisual_Colour>& theSurfaceColour);

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleRendering, Standard_Transient)

private:
  StepVisual_ShadingSurfaceMethod myRenderingMethod;
  occ::handle<StepVisual_Colour>  mySurfaceColour;
};
