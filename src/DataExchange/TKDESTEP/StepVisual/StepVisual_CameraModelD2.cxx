

#include <StepVisual_CameraModelD2.hpp>
#include <StepVisual_PlanarBox.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_CameraModelD2, StepVisual_CameraModel)

StepVisual_CameraModelD2::StepVisual_CameraModelD2() = default;

void StepVisual_CameraModelD2::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                    const occ::handle<StepVisual_PlanarBox>&     aViewWindow,
                                    const bool aViewWindowClipping)
{

  viewWindow         = aViewWindow;
  viewWindowClipping = aViewWindowClipping;

  StepRepr_RepresentationItem::Init(aName);
}

void StepVisual_CameraModelD2::SetViewWindow(const occ::handle<StepVisual_PlanarBox>& aViewWindow)
{
  viewWindow = aViewWindow;
}

occ::handle<StepVisual_PlanarBox> StepVisual_CameraModelD2::ViewWindow() const
{
  return viewWindow;
}

void StepVisual_CameraModelD2::SetViewWindowClipping(const bool aViewWindowClipping)
{
  viewWindowClipping = aViewWindowClipping;
}

bool StepVisual_CameraModelD2::ViewWindowClipping() const
{
  return viewWindowClipping;
}
