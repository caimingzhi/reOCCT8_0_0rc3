

#include <StepGeom_Axis2Placement3d.hpp>
#include <StepVisual_CameraModelD3.hpp>
#include <StepVisual_ViewVolume.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_CameraModelD3, StepVisual_CameraModel)

StepVisual_CameraModelD3::StepVisual_CameraModelD3() = default;

void StepVisual_CameraModelD3::Init(
  const occ::handle<TCollection_HAsciiString>&  aName,
  const occ::handle<StepGeom_Axis2Placement3d>& aViewReferenceSystem,
  const occ::handle<StepVisual_ViewVolume>&     aPerspectiveOfVolume)
{

  viewReferenceSystem = aViewReferenceSystem;
  perspectiveOfVolume = aPerspectiveOfVolume;

  StepRepr_RepresentationItem::Init(aName);
}

void StepVisual_CameraModelD3::SetViewReferenceSystem(
  const occ::handle<StepGeom_Axis2Placement3d>& aViewReferenceSystem)
{
  viewReferenceSystem = aViewReferenceSystem;
}

occ::handle<StepGeom_Axis2Placement3d> StepVisual_CameraModelD3::ViewReferenceSystem() const
{
  return viewReferenceSystem;
}

void StepVisual_CameraModelD3::SetPerspectiveOfVolume(
  const occ::handle<StepVisual_ViewVolume>& aPerspectiveOfVolume)
{
  perspectiveOfVolume = aPerspectiveOfVolume;
}

occ::handle<StepVisual_ViewVolume> StepVisual_CameraModelD3::PerspectiveOfVolume() const
{
  return perspectiveOfVolume;
}
