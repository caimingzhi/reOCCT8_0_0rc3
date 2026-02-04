#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <StepVisual_CameraModel.hpp>
class StepVisual_PlanarBox;
class TCollection_HAsciiString;

class StepVisual_CameraModelD2 : public StepVisual_CameraModel
{

public:
  //! Returns a CameraModelD2
  Standard_EXPORT StepVisual_CameraModelD2();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepVisual_PlanarBox>&     aViewWindow,
                            const bool                                   aViewWindowClipping);

  Standard_EXPORT void SetViewWindow(const occ::handle<StepVisual_PlanarBox>& aViewWindow);

  Standard_EXPORT occ::handle<StepVisual_PlanarBox> ViewWindow() const;

  Standard_EXPORT void SetViewWindowClipping(const bool aViewWindowClipping);

  Standard_EXPORT bool ViewWindowClipping() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_CameraModelD2, StepVisual_CameraModel)

private:
  occ::handle<StepVisual_PlanarBox> viewWindow;
  bool                              viewWindowClipping;
};

