

#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_SurfaceStyleControlGrid.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleControlGrid, Standard_Transient)

StepVisual_SurfaceStyleControlGrid::StepVisual_SurfaceStyleControlGrid() = default;

void StepVisual_SurfaceStyleControlGrid::Init(
  const occ::handle<StepVisual_CurveStyle>& aStyleOfControlGrid)
{

  styleOfControlGrid = aStyleOfControlGrid;
}

void StepVisual_SurfaceStyleControlGrid::SetStyleOfControlGrid(
  const occ::handle<StepVisual_CurveStyle>& aStyleOfControlGrid)
{
  styleOfControlGrid = aStyleOfControlGrid;
}

occ::handle<StepVisual_CurveStyle> StepVisual_SurfaceStyleControlGrid::StyleOfControlGrid() const
{
  return styleOfControlGrid;
}
