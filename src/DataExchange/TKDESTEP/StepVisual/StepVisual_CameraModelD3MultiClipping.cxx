#include <StepGeom_Axis2Placement3d.hpp>
#include <StepVisual_CameraModelD3MultiClipping.hpp>
#include <StepVisual_ViewVolume.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_CameraModelD3MultiClipping, StepVisual_CameraModelD3)

//=================================================================================================

StepVisual_CameraModelD3MultiClipping::StepVisual_CameraModelD3MultiClipping() = default;

//=================================================================================================

void StepVisual_CameraModelD3MultiClipping::Init(
  const occ::handle<TCollection_HAsciiString>&  theName,
  const occ::handle<StepGeom_Axis2Placement3d>& theViewReferenceSystem,
  const occ::handle<StepVisual_ViewVolume>&     thePerspectiveOfVolume,
  const occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingInterectionSelect>>&
    theShapeClipping)
{
  // Own field
  myShapeClipping = theShapeClipping;
  // Inherited fields
  StepVisual_CameraModelD3::Init(theName, theViewReferenceSystem, thePerspectiveOfVolume);
}
