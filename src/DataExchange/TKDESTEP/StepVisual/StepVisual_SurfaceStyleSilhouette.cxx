

#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_SurfaceStyleSilhouette.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleSilhouette, Standard_Transient)

StepVisual_SurfaceStyleSilhouette::StepVisual_SurfaceStyleSilhouette() = default;

void StepVisual_SurfaceStyleSilhouette::Init(
  const occ::handle<StepVisual_CurveStyle>& aStyleOfSilhouette)
{

  styleOfSilhouette = aStyleOfSilhouette;
}

void StepVisual_SurfaceStyleSilhouette::SetStyleOfSilhouette(
  const occ::handle<StepVisual_CurveStyle>& aStyleOfSilhouette)
{
  styleOfSilhouette = aStyleOfSilhouette;
}

occ::handle<StepVisual_CurveStyle> StepVisual_SurfaceStyleSilhouette::StyleOfSilhouette() const
{
  return styleOfSilhouette;
}
