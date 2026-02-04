#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepVisual_CurveStyle;

class StepVisual_SurfaceStyleSilhouette : public Standard_Transient
{

public:
  //! Returns a SurfaceStyleSilhouette
  Standard_EXPORT StepVisual_SurfaceStyleSilhouette();

  Standard_EXPORT void Init(const occ::handle<StepVisual_CurveStyle>& aStyleOfSilhouette);

  Standard_EXPORT void SetStyleOfSilhouette(
    const occ::handle<StepVisual_CurveStyle>& aStyleOfSilhouette);

  Standard_EXPORT occ::handle<StepVisual_CurveStyle> StyleOfSilhouette() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleSilhouette, Standard_Transient)

private:
  occ::handle<StepVisual_CurveStyle> styleOfSilhouette;
};

