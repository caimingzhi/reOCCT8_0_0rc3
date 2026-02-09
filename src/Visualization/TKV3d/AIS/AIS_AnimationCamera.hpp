#pragma once

#include <AIS_Animation.hpp>

class Graphic3d_Camera;
class V3d_View;

class AIS_AnimationCamera : public AIS_Animation
{
  DEFINE_STANDARD_RTTIEXT(AIS_AnimationCamera, AIS_Animation)
public:
  Standard_EXPORT AIS_AnimationCamera(const TCollection_AsciiString& theAnimationName,
                                      const occ::handle<V3d_View>&   theView);

  const occ::handle<V3d_View>& View() const { return myView; }

  void SetView(const occ::handle<V3d_View>& theView) { myView = theView; }

  const occ::handle<Graphic3d_Camera>& CameraStart() const { return myCamStart; }

  void SetCameraStart(const occ::handle<Graphic3d_Camera>& theCameraStart)
  {
    myCamStart = theCameraStart;
  }

  const occ::handle<Graphic3d_Camera>& CameraEnd() const { return myCamEnd; }

  void SetCameraEnd(const occ::handle<Graphic3d_Camera>& theCameraEnd) { myCamEnd = theCameraEnd; }

protected:
  Standard_EXPORT void update(const AIS_AnimationProgress& theProgress) override;

protected:
  occ::handle<V3d_View>         myView;
  occ::handle<Graphic3d_Camera> myCamStart;
  occ::handle<Graphic3d_Camera> myCamEnd;
};
