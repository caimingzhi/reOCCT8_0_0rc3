#pragma once


#include <AIS_Animation.hpp>

class Graphic3d_Camera;
class V3d_View;

//! Camera animation.
class AIS_AnimationCamera : public AIS_Animation
{
  DEFINE_STANDARD_RTTIEXT(AIS_AnimationCamera, AIS_Animation)
public:
  //! Main constructor.
  Standard_EXPORT AIS_AnimationCamera(const TCollection_AsciiString& theAnimationName,
                                      const occ::handle<V3d_View>&   theView);

  //! Return the target view.
  const occ::handle<V3d_View>& View() const { return myView; }

  //! Set target view.
  void SetView(const occ::handle<V3d_View>& theView) { myView = theView; }

  //! Return camera start position.
  const occ::handle<Graphic3d_Camera>& CameraStart() const { return myCamStart; }

  //! Define camera start position.
  void SetCameraStart(const occ::handle<Graphic3d_Camera>& theCameraStart)
  {
    myCamStart = theCameraStart;
  }

  //! Return camera end position.
  const occ::handle<Graphic3d_Camera>& CameraEnd() const { return myCamEnd; }

  //! Define camera end position.
  void SetCameraEnd(const occ::handle<Graphic3d_Camera>& theCameraEnd) { myCamEnd = theCameraEnd; }

protected:
  //! Update the progress.
  Standard_EXPORT void update(const AIS_AnimationProgress& theProgress) override;

protected:
  occ::handle<V3d_View>         myView;     //!< view to setup camera
  occ::handle<Graphic3d_Camera> myCamStart; //!< starting camera position
  occ::handle<Graphic3d_Camera> myCamEnd;   //!< end camera position
};

