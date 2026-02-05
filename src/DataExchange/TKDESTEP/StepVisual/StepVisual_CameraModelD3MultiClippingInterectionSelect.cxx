#include <StepVisual_CameraModelD3MultiClippingInterectionSelect.hpp>
#include <MoniTool_Macros.hpp>
#include <StepGeom_Plane.hpp>
#include <StepVisual_CameraModelD3MultiClippingUnion.hpp>

//=================================================================================================

StepVisual_CameraModelD3MultiClippingInterectionSelect::
  StepVisual_CameraModelD3MultiClippingInterectionSelect() = default;

//=================================================================================================

int StepVisual_CameraModelD3MultiClippingInterectionSelect::CaseNum(
  const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Plane)))
    return 1;
  if (ent->IsInstance(STANDARD_TYPE(StepVisual_CameraModelD3MultiClippingUnion)))
    return 2;
  return 0;
}

occ::handle<StepGeom_Plane> StepVisual_CameraModelD3MultiClippingInterectionSelect::Plane() const
{
  return GetCasted(StepGeom_Plane, Value());
}

occ::handle<StepVisual_CameraModelD3MultiClippingUnion>
  StepVisual_CameraModelD3MultiClippingInterectionSelect::CameraModelD3MultiClippingUnion() const
{
  return GetCasted(StepVisual_CameraModelD3MultiClippingUnion, Value());
}
