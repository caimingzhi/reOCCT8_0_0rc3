

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_FillAreaStyle.hpp>
#include <StepVisual_NullStyleMember.hpp>
#include <StepVisual_PointStyle.hpp>
#include <StepVisual_PresentationStyleSelect.hpp>
#include <StepVisual_SurfaceStyleUsage.hpp>

StepVisual_PresentationStyleSelect::StepVisual_PresentationStyleSelect() = default;

int StepVisual_PresentationStyleSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PointStyle)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_CurveStyle)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_SurfaceStyleUsage)))
    return 3;

  if (ent->IsKind(STANDARD_TYPE(StepVisual_NullStyleMember)))
    return 7;
  return 0;
}

occ::handle<StepVisual_PointStyle> StepVisual_PresentationStyleSelect::PointStyle() const
{
  return GetCasted(StepVisual_PointStyle, Value());
}

occ::handle<StepVisual_CurveStyle> StepVisual_PresentationStyleSelect::CurveStyle() const
{
  return GetCasted(StepVisual_CurveStyle, Value());
}

occ::handle<StepVisual_NullStyleMember> StepVisual_PresentationStyleSelect::NullStyle() const
{
  return GetCasted(StepVisual_NullStyleMember, Value());
}

occ::handle<StepVisual_SurfaceStyleUsage> StepVisual_PresentationStyleSelect::SurfaceStyleUsage()
  const
{
  return GetCasted(StepVisual_SurfaceStyleUsage, Value());
}
