

#include <StepVisual_FillAreaStyle.hpp>
#include <StepVisual_SurfaceStyleFillArea.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleFillArea, Standard_Transient)

StepVisual_SurfaceStyleFillArea::StepVisual_SurfaceStyleFillArea() = default;

void StepVisual_SurfaceStyleFillArea::Init(const occ::handle<StepVisual_FillAreaStyle>& aFillArea)
{

  fillArea = aFillArea;
}

void StepVisual_SurfaceStyleFillArea::SetFillArea(
  const occ::handle<StepVisual_FillAreaStyle>& aFillArea)
{
  fillArea = aFillArea;
}

occ::handle<StepVisual_FillAreaStyle> StepVisual_SurfaceStyleFillArea::FillArea() const
{
  return fillArea;
}
