#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

#include <StepVisual_ShadingSurfaceMethod.hpp>
#include <StepVisual_Colour.hpp>

//! Representation of STEP entity SurfaceStyleRendering
class StepVisual_SurfaceStyleRendering : public Standard_Transient
{
public:
  //! default constructor
  Standard_EXPORT StepVisual_SurfaceStyleRendering();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const StepVisual_ShadingSurfaceMethod theRenderingMethod,
                            const occ::handle<StepVisual_Colour>& theSurfaceColour);

  //! Returns field RenderingMethod
  Standard_EXPORT StepVisual_ShadingSurfaceMethod RenderingMethod() const;
  //! Sets field RenderingMethod
  Standard_EXPORT void SetRenderingMethod(const StepVisual_ShadingSurfaceMethod theRenderingMethod);

  //! Returns field SurfaceColour
  Standard_EXPORT occ::handle<StepVisual_Colour> SurfaceColour() const;
  //! Sets field SurfaceColour
  Standard_EXPORT void SetSurfaceColour(const occ::handle<StepVisual_Colour>& theSurfaceColour);

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleRendering, Standard_Transient)

private:
  StepVisual_ShadingSurfaceMethod myRenderingMethod;
  occ::handle<StepVisual_Colour>  mySurfaceColour;
};
