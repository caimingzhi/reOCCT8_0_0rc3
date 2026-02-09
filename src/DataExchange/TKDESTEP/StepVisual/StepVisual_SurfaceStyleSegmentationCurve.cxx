

#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_SurfaceStyleSegmentationCurve.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleSegmentationCurve, Standard_Transient)

StepVisual_SurfaceStyleSegmentationCurve::StepVisual_SurfaceStyleSegmentationCurve() = default;

void StepVisual_SurfaceStyleSegmentationCurve::Init(
  const occ::handle<StepVisual_CurveStyle>& aStyleOfSegmentationCurve)
{

  styleOfSegmentationCurve = aStyleOfSegmentationCurve;
}

void StepVisual_SurfaceStyleSegmentationCurve::SetStyleOfSegmentationCurve(
  const occ::handle<StepVisual_CurveStyle>& aStyleOfSegmentationCurve)
{
  styleOfSegmentationCurve = aStyleOfSegmentationCurve;
}

occ::handle<StepVisual_CurveStyle> StepVisual_SurfaceStyleSegmentationCurve::
  StyleOfSegmentationCurve() const
{
  return styleOfSegmentationCurve;
}
