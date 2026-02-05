#include <StepVisual_CameraModelD3MultiClippingIntersection.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_CameraModelD3MultiClippingIntersection,
                           StepGeom_GeometricRepresentationItem)

//=================================================================================================

StepVisual_CameraModelD3MultiClippingIntersection::
  StepVisual_CameraModelD3MultiClippingIntersection() = default;

//=================================================================================================

void StepVisual_CameraModelD3MultiClippingIntersection::Init(
  const occ::handle<TCollection_HAsciiString>& theName,
  const occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingInterectionSelect>>&
    theShapeClipping)
{
  // Own field
  myShapeClipping = theShapeClipping;
  // Inherited fields
  StepGeom_GeometricRepresentationItem::Init(theName);
}
