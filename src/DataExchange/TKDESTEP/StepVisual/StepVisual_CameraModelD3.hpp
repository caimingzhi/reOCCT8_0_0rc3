#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_CameraModel.hpp>
class StepGeom_Axis2Placement3d;
class StepVisual_ViewVolume;
class TCollection_HAsciiString;

class StepVisual_CameraModelD3 : public StepVisual_CameraModel
{

public:
  //! Returns a CameraModelD3
  Standard_EXPORT StepVisual_CameraModelD3();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&  aName,
                            const occ::handle<StepGeom_Axis2Placement3d>& aViewReferenceSystem,
                            const occ::handle<StepVisual_ViewVolume>&     aPerspectiveOfVolume);

  Standard_EXPORT void SetViewReferenceSystem(
    const occ::handle<StepGeom_Axis2Placement3d>& aViewReferenceSystem);

  Standard_EXPORT occ::handle<StepGeom_Axis2Placement3d> ViewReferenceSystem() const;

  Standard_EXPORT void SetPerspectiveOfVolume(
    const occ::handle<StepVisual_ViewVolume>& aPerspectiveOfVolume);

  Standard_EXPORT occ::handle<StepVisual_ViewVolume> PerspectiveOfVolume() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_CameraModelD3, StepVisual_CameraModel)

private:
  occ::handle<StepGeom_Axis2Placement3d> viewReferenceSystem;
  occ::handle<StepVisual_ViewVolume>     perspectiveOfVolume;
};
