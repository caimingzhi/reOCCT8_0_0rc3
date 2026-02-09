#pragma once

#include <Aspect_XRSession.hpp>

class Aspect_OpenVRSession : public Aspect_XRSession
{
  DEFINE_STANDARD_RTTIEXT(Aspect_OpenVRSession, Aspect_XRSession)
public:
  Standard_EXPORT static bool IsHmdPresent();

public:
  Standard_EXPORT Aspect_OpenVRSession();

  Standard_EXPORT ~Aspect_OpenVRSession() override;

  Standard_EXPORT bool IsOpen() const override;

  Standard_EXPORT bool Open() override;

  Standard_EXPORT void Close() override;

  Standard_EXPORT bool WaitPoses() override;

  NCollection_Vec2<int> RecommendedViewport() const override { return myRendSize; }

  Standard_EXPORT NCollection_Mat4<double> EyeToHeadTransform(Aspect_Eye theEye) const override;

  Standard_EXPORT NCollection_Mat4<double> ProjectionMatrix(Aspect_Eye theEye,
                                                            double     theZNear,
                                                            double     theZFar) const override;

  bool HasProjectionFrustums() const override { return true; }

  Standard_EXPORT void ProcessEvents() override;

  Standard_EXPORT bool SubmitEye(void*                  theTexture,
                                 Aspect_GraphicsLibrary theGraphicsLib,
                                 Aspect_ColorSpace      theColorSpace,
                                 Aspect_Eye             theEye) override;

  Standard_EXPORT TCollection_AsciiString GetString(InfoString theInfo) const override;

  Standard_EXPORT int NamedTrackedDevice(Aspect_XRTrackedDeviceRole theDevice) const override;

  Standard_EXPORT Aspect_XRDigitalActionData
    GetDigitalActionData(const occ::handle<Aspect_XRAction>& theAction) const override;

  Standard_EXPORT Aspect_XRAnalogActionData
    GetAnalogActionData(const occ::handle<Aspect_XRAction>& theAction) const override;

  Standard_EXPORT Aspect_XRPoseActionData
    GetPoseActionDataForNextFrame(const occ::handle<Aspect_XRAction>& theAction) const override;

  Standard_EXPORT void SetTrackingOrigin(TrackingUniverseOrigin theOrigin) override;

protected:
  Standard_EXPORT TCollection_AsciiString defaultActionsManifest();

  Standard_EXPORT void closeVR();

  Standard_EXPORT virtual void updateProjectionFrustums();

  Standard_EXPORT virtual bool initInput();

  Standard_EXPORT virtual void onTrackedDeviceActivated(int theDeviceIndex);

  Standard_EXPORT virtual void onTrackedDeviceDeactivated(int theDeviceIndex);

  Standard_EXPORT virtual void onTrackedDeviceUpdated(int theDeviceIndex);

  Standard_EXPORT void triggerHapticVibrationAction(
    const occ::handle<Aspect_XRAction>& theAction,
    const Aspect_XRHapticActionData&    theParams) override;

  Standard_EXPORT occ::handle<Graphic3d_ArrayOfTriangles> loadRenderModel(
    int                         theDevice,
    bool                        theToApplyUnitFactor,
    occ::handle<Image_Texture>& theTexture) override;

protected:
  Standard_EXPORT void* getVRSystem() const;

private:
  struct VRContext;
  class VRImagePixmap;
  class VRTextureSource;

protected:
  VRContext*              myContext;
  TCollection_AsciiString myActionsManifest;
};
