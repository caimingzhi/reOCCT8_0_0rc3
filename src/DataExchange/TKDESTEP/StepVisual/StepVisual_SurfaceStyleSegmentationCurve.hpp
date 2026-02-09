#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepVisual_CurveStyle;

class StepVisual_SurfaceStyleSegmentationCurve : public Standard_Transient
{

public:
  Standard_EXPORT StepVisual_SurfaceStyleSegmentationCurve();

  Standard_EXPORT void Init(const occ::handle<StepVisual_CurveStyle>& aStyleOfSegmentationCurve);

  Standard_EXPORT void SetStyleOfSegmentationCurve(
    const occ::handle<StepVisual_CurveStyle>& aStyleOfSegmentationCurve);

  Standard_EXPORT occ::handle<StepVisual_CurveStyle> StyleOfSegmentationCurve() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleSegmentationCurve, Standard_Transient)

private:
  occ::handle<StepVisual_CurveStyle> styleOfSegmentationCurve;
};
