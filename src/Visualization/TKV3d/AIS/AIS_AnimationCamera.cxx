#include <AIS_AnimationCamera.hpp>

#include <V3d_View.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_AnimationCamera, AIS_Animation)

AIS_AnimationCamera::AIS_AnimationCamera(const TCollection_AsciiString& theAnimationName,
                                         const occ::handle<V3d_View>&   theView)
    : AIS_Animation(theAnimationName),
      myView(theView)
{
}

void AIS_AnimationCamera::update(const AIS_AnimationProgress& theProgress)
{
  if (myView.IsNull() || myCamStart.IsNull() || myCamEnd.IsNull())
  {
    return;
  }

  occ::handle<Graphic3d_Camera> aCamera = myView->Camera();

  NCollection_Lerp<occ::handle<Graphic3d_Camera>> aCamLerp(myCamStart, myCamEnd);
  aCamLerp.Interpolate(HasOwnDuration() ? theProgress.LocalNormalized : 1.0, aCamera);

  const bool aPrevImmUpdate = myView->SetImmediateUpdate(false);
  myView->SetCamera(aCamera);
  myView->SetImmediateUpdate(aPrevImmUpdate);
  myView->Invalidate();
}
