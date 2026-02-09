

#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_SurfaceStyleBoundary.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleBoundary, Standard_Transient)

StepVisual_SurfaceStyleBoundary::StepVisual_SurfaceStyleBoundary() = default;

void StepVisual_SurfaceStyleBoundary::Init(
  const occ::handle<StepVisual_CurveStyle>& aStyleOfBoundary)
{

  styleOfBoundary = aStyleOfBoundary;
}

void StepVisual_SurfaceStyleBoundary::SetStyleOfBoundary(
  const occ::handle<StepVisual_CurveStyle>& aStyleOfBoundary)
{
  styleOfBoundary = aStyleOfBoundary;
}

occ::handle<StepVisual_CurveStyle> StepVisual_SurfaceStyleBoundary::StyleOfBoundary() const
{
  return styleOfBoundary;
}
