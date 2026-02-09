#include <StepVisual_CameraModelD3MultiClippingUnionSelect.hpp>
#include <MoniTool_Macros.hpp>
#include <StepGeom_Plane.hpp>
#include <StepVisual_CameraModelD3MultiClippingIntersection.hpp>

StepVisual_CameraModelD3MultiClippingUnionSelect::
  StepVisual_CameraModelD3MultiClippingUnionSelect() = default;

int StepVisual_CameraModelD3MultiClippingUnionSelect::CaseNum(
  const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Plane)))
    return 1;
  if (ent->IsInstance(STANDARD_TYPE(StepVisual_CameraModelD3MultiClippingIntersection)))
    return 2;
  return 0;
}

occ::handle<StepGeom_Plane> StepVisual_CameraModelD3MultiClippingUnionSelect::Plane() const
{
  return GetCasted(StepGeom_Plane, Value());
}

occ::handle<StepVisual_CameraModelD3MultiClippingIntersection>
  StepVisual_CameraModelD3MultiClippingUnionSelect::CameraModelD3MultiClippingIntersection() const
{
  return GetCasted(StepVisual_CameraModelD3MultiClippingIntersection, Value());
}
