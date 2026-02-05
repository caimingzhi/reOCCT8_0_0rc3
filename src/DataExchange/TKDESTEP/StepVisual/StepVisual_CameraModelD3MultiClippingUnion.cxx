#include <StepVisual_CameraModelD3MultiClippingUnion.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_CameraModelD3MultiClippingUnion,
                           StepGeom_GeometricRepresentationItem)

//=================================================================================================

StepVisual_CameraModelD3MultiClippingUnion::StepVisual_CameraModelD3MultiClippingUnion() = default;

//=================================================================================================

void StepVisual_CameraModelD3MultiClippingUnion::Init(
  const occ::handle<TCollection_HAsciiString>& theName,
  const occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingUnionSelect>>&
    theShapeClipping)
{
  // Own field
  myShapeClipping = theShapeClipping;
  // Inherited fields
  StepGeom_GeometricRepresentationItem::Init(theName);
}
