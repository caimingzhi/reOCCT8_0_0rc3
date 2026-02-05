#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>
#include <StepVisual_CameraModelD3MultiClippingUnionSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class TCollection_HAsciiString;

class StepVisual_CameraModelD3MultiClippingUnion : public StepGeom_GeometricRepresentationItem
{
public:
  //! Returns a StepVisual_CameraModelD3MultiClippingUnion
  Standard_EXPORT StepVisual_CameraModelD3MultiClippingUnion();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theName,
    const occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingUnionSelect>>&
      theShapeClipping);

  void SetShapeClipping(
    const occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingUnionSelect>>&
      theShapeClipping)
  {
    myShapeClipping = theShapeClipping;
  }

  const occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingUnionSelect>>
    ShapeClipping()
  {
    return myShapeClipping;
  }
  DEFINE_STANDARD_RTTIEXT(StepVisual_CameraModelD3MultiClippingUnion,
                          StepGeom_GeometricRepresentationItem)

private:
  occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingUnionSelect>>
    myShapeClipping;
};
