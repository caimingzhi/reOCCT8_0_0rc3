

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepVisual_SurfaceStyleBoundary.hpp>
#include <StepVisual_SurfaceStyleControlGrid.hpp>
#include <StepVisual_SurfaceStyleElementSelect.hpp>
#include <StepVisual_SurfaceStyleFillArea.hpp>
#include <StepVisual_SurfaceStyleParameterLine.hpp>
#include <StepVisual_SurfaceStyleRendering.hpp>

StepVisual_SurfaceStyleElementSelect::StepVisual_SurfaceStyleElementSelect() = default;

int StepVisual_SurfaceStyleElementSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_SurfaceStyleFillArea)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_SurfaceStyleBoundary)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_SurfaceStyleParameterLine)))
    return 3;

  if (ent->IsKind(STANDARD_TYPE(StepVisual_SurfaceStyleRendering)))
    return 7;
  return 0;
}

occ::handle<StepVisual_SurfaceStyleFillArea> StepVisual_SurfaceStyleElementSelect::
  SurfaceStyleFillArea() const
{
  return GetCasted(StepVisual_SurfaceStyleFillArea, Value());
}

occ::handle<StepVisual_SurfaceStyleBoundary> StepVisual_SurfaceStyleElementSelect::
  SurfaceStyleBoundary() const
{
  return GetCasted(StepVisual_SurfaceStyleBoundary, Value());
}

occ::handle<StepVisual_SurfaceStyleParameterLine> StepVisual_SurfaceStyleElementSelect::
  SurfaceStyleParameterLine() const
{
  return GetCasted(StepVisual_SurfaceStyleParameterLine, Value());
}

occ::handle<StepVisual_SurfaceStyleRendering> StepVisual_SurfaceStyleElementSelect::
  SurfaceStyleRendering() const
{
  return GetCasted(StepVisual_SurfaceStyleRendering, Value());
}
