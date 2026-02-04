#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_CameraModelD3.hpp>
#include <StepVisual_CameraModelD3MultiClippingInterectionSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class StepGeom_Axis2Placement3d;
class StepVisual_ViewVolume;
class TCollection_HAsciiString;

class StepVisual_CameraModelD3MultiClipping : public StepVisual_CameraModelD3
{
public:
  //! Returns a CameraModelD3MultiClipping
  Standard_EXPORT StepVisual_CameraModelD3MultiClipping();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&  theName,
    const occ::handle<StepGeom_Axis2Placement3d>& theViewReferenceSystem,
    const occ::handle<StepVisual_ViewVolume>&     thePerspectiveOfVolume,
    const occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingInterectionSelect>>&
      theShapeClipping);

  void SetShapeClipping(
    const occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingInterectionSelect>>&
      theShapeClipping)
  {
    myShapeClipping = theShapeClipping;
  }

  const occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingInterectionSelect>>
    ShapeClipping()
  {
    return myShapeClipping;
  }
  DEFINE_STANDARD_RTTIEXT(StepVisual_CameraModelD3MultiClipping, StepVisual_CameraModelD3)

private:
  occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingInterectionSelect>>
    myShapeClipping;
};
