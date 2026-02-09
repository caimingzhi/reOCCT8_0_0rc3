#pragma once

enum Aspect_ColorSpace
{
  Aspect_ColorSpace_sRGB   = 0,
  Aspect_ColorSpace_Linear = 1,
};

#include <Aspect_Eye.hpp>
#include <Aspect_FrustumLRBT.hpp>
#include <Aspect_GraphicsLibrary.hpp>

enum Aspect_XRActionType
{
  Aspect_XRActionType_InputDigital,
  Aspect_XRActionType_InputAnalog,
  Aspect_XRActionType_InputPose,
  Aspect_XRActionType_InputSkeletal,
  Aspect_XRActionType_OutputHaptic
};

#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

class Aspect_XRAction : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Aspect_XRAction, Standard_Transient)
public:
  const TCollection_AsciiString& Id() const { return myId; }

  Aspect_XRActionType Type() const { return myType; }

  bool IsValid() const { return myRawHandle != 0; }

  uint64_t RawHandle() const { return myRawHandle; }

  void SetRawHandle(uint64_t theHande) { myRawHandle = theHande; }

  Aspect_XRAction(const TCollection_AsciiString& theId, const Aspect_XRActionType theType)
      : myId(theId),
        myRawHandle(0),
        myType(theType)
  {
  }

protected:
  TCollection_AsciiString myId;
  uint64_t                myRawHandle;
  Aspect_XRActionType     myType;
};

class Aspect_XRActionSet : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Aspect_XRActionSet, Standard_Transient)
public:
  const TCollection_AsciiString& Id() const { return myId; }

  uint64_t RawHandle() const { return myRawHandle; }

  void SetRawHandle(uint64_t theHande) { myRawHandle = theHande; }

  void AddAction(const occ::handle<Aspect_XRAction>& theAction)
  {
    myActions.Add(theAction->Id(), theAction);
  }

  const NCollection_IndexedDataMap<TCollection_AsciiString, occ::handle<Aspect_XRAction>>& Actions()
    const
  {
    return myActions;
  }

  Aspect_XRActionSet(const TCollection_AsciiString& theId)
      : myId(theId),
        myRawHandle(0)
  {
  }

protected:
  TCollection_AsciiString                                                           myId;
  uint64_t                                                                          myRawHandle;
  NCollection_IndexedDataMap<TCollection_AsciiString, occ::handle<Aspect_XRAction>> myActions;
};

#include <NCollection_Vec3.hpp>

struct Aspect_XRAnalogActionData
{
  uint64_t ActiveOrigin;

  float                   UpdateTime;
  NCollection_Vec3<float> VecXYZ;
  NCollection_Vec3<float> DeltaXYZ;
  bool                    IsActive;

  bool IsChanged() { return !DeltaXYZ.IsEqual(NCollection_Vec3<float>(0.0f, 0.0f, 0.0f)); }

  Aspect_XRAnalogActionData()
      : ActiveOrigin(0),
        UpdateTime(0.0f),
        IsActive(false)
  {
  }
};

#include <Standard_TypeDef.hpp>

struct Aspect_XRDigitalActionData
{
  uint64_t ActiveOrigin;

  float UpdateTime;
  bool  IsActive;
  bool  IsPressed;
  bool  IsChanged;

  Aspect_XRDigitalActionData()
      : ActiveOrigin(0),
        UpdateTime(0.0f),
        IsActive(false),
        IsPressed(false),
        IsChanged(false)
  {
  }
};

enum Aspect_XRGenericAction
{
  Aspect_XRGenericAction_IsHeadsetOn,
  Aspect_XRGenericAction_InputAppMenu,
  Aspect_XRGenericAction_InputSysMenu,
  Aspect_XRGenericAction_InputTriggerPull,
  Aspect_XRGenericAction_InputTriggerClick,
  Aspect_XRGenericAction_InputGripClick,
  Aspect_XRGenericAction_InputTrackPadPosition,
  Aspect_XRGenericAction_InputTrackPadTouch,
  Aspect_XRGenericAction_InputTrackPadClick,
  Aspect_XRGenericAction_InputThumbstickPosition,

  Aspect_XRGenericAction_InputThumbstickTouch,
  Aspect_XRGenericAction_InputThumbstickClick,
  Aspect_XRGenericAction_InputPoseBase,
  Aspect_XRGenericAction_InputPoseFront,
  Aspect_XRGenericAction_InputPoseHandGrip,
  Aspect_XRGenericAction_InputPoseFingerTip,
  Aspect_XRGenericAction_OutputHaptic
};

enum
{
  Aspect_XRGenericAction_NB = Aspect_XRGenericAction_OutputHaptic + 1
};

#include <Aspect_XRHapticActionData.hpp>

#include <gp_Trsf.hpp>
#include <NCollection_Array1.hpp>

struct Aspect_TrackedDevicePose
{
  gp_Trsf Orientation;
  gp_Vec  Velocity;
  gp_Vec  AngularVelocity;
  bool    IsValidPose;
  bool    IsConnectedDevice;

  Aspect_TrackedDevicePose()
      : IsValidPose(false),
        IsConnectedDevice(false)
  {
  }
};

#include <Standard_TypeDef.hpp>

struct Aspect_XRPoseActionData
{
  Aspect_TrackedDevicePose Pose;
  uint64_t                 ActiveOrigin;

  bool IsActive;

  Aspect_XRPoseActionData()
      : ActiveOrigin(0),
        IsActive(false)
  {
  }
};

#include <Aspect_XRTrackedDeviceRole.hpp>
#include <gp_Trsf.hpp>
#include <NCollection_Array1.hpp>

class Graphic3d_ArrayOfTriangles;
class Image_Texture;

class Aspect_XRSession : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Aspect_XRSession, Standard_Transient)
public:
  enum TrackingUniverseOrigin
  {
    TrackingUniverseOrigin_Seated,
    TrackingUniverseOrigin_Standing,
  };

public:
  virtual bool IsOpen() const = 0;

  virtual bool Open() = 0;

  virtual void Close() = 0;

  virtual bool WaitPoses() = 0;

  virtual NCollection_Vec2<int> RecommendedViewport() const = 0;

  virtual NCollection_Mat4<double> EyeToHeadTransform(Aspect_Eye theEye) const = 0;

  NCollection_Mat4<double> HeadToEyeTransform(Aspect_Eye theEye) const
  {
    NCollection_Mat4<double> aMat;
    EyeToHeadTransform(theEye).Inverted(aMat);
    return aMat;
  }

  virtual NCollection_Mat4<double> ProjectionMatrix(Aspect_Eye theEye,
                                                    double     theZNear,
                                                    double     theZFar) const = 0;

  virtual bool HasProjectionFrustums() const = 0;

  virtual void ProcessEvents() = 0;

  virtual bool SubmitEye(void*                  theTexture,
                         Aspect_GraphicsLibrary theGraphicsLib,
                         Aspect_ColorSpace      theColorSpace,
                         Aspect_Eye             theEye) = 0;

  double UnitFactor() const { return myUnitFactor; }

  void SetUnitFactor(double theFactor) { myUnitFactor = theFactor; }

  double Aspect() const { return myAspect; }

  double FieldOfView() const { return myFieldOfView; }

  double IOD() const { return myIod; }

  float DisplayFrequency() const { return myDispFreq; }

  const Aspect_FrustumLRBT<double>& ProjectionFrustum(Aspect_Eye theEye) const
  {
    return theEye == Aspect_Eye_Right ? myFrustumR : myFrustumL;
  }

  const gp_Trsf& HeadPose() const { return myHeadPose; }

  gp_Trsf LeftHandPose() const
  {
    const int aDevice = NamedTrackedDevice(Aspect_XRTrackedDeviceRole_LeftHand);
    return aDevice != -1 ? myTrackedPoses[aDevice].Orientation : gp_Trsf();
  }

  gp_Trsf RightHandPose() const
  {
    const int aDevice = NamedTrackedDevice(Aspect_XRTrackedDeviceRole_RightHand);
    return aDevice != -1 ? myTrackedPoses[aDevice].Orientation : gp_Trsf();
  }

  const NCollection_Array1<Aspect_TrackedDevicePose>& TrackedPoses() const
  {
    return myTrackedPoses;
  }

  bool HasTrackedPose(int theDevice) const { return myTrackedPoses[theDevice].IsValidPose; }

  virtual int NamedTrackedDevice(Aspect_XRTrackedDeviceRole theDevice) const = 0;

  occ::handle<Graphic3d_ArrayOfTriangles> LoadRenderModel(int                         theDevice,
                                                          occ::handle<Image_Texture>& theTexture)
  {
    return loadRenderModel(theDevice, true, theTexture);
  }

  occ::handle<Graphic3d_ArrayOfTriangles> LoadRenderModel(int  theDevice,
                                                          bool theToApplyUnitFactor,
                                                          occ::handle<Image_Texture>& theTexture)
  {
    return loadRenderModel(theDevice, theToApplyUnitFactor, theTexture);
  }

  virtual Aspect_XRDigitalActionData GetDigitalActionData(
    const occ::handle<Aspect_XRAction>& theAction) const = 0;

  virtual Aspect_XRAnalogActionData GetAnalogActionData(
    const occ::handle<Aspect_XRAction>& theAction) const = 0;

  virtual Aspect_XRPoseActionData GetPoseActionDataForNextFrame(
    const occ::handle<Aspect_XRAction>& theAction) const = 0;

  Standard_EXPORT void TriggerHapticVibrationAction(const occ::handle<Aspect_XRAction>& theAction,
                                                    const Aspect_XRHapticActionData&    theParams);

  Standard_EXPORT void AbortHapticVibrationAction(const occ::handle<Aspect_XRAction>& theAction);

  TrackingUniverseOrigin TrackingOrigin() const { return myTrackOrigin; }

  virtual void SetTrackingOrigin(TrackingUniverseOrigin theOrigin) { myTrackOrigin = theOrigin; }

  const occ::handle<Aspect_XRAction>& GenericAction(Aspect_XRTrackedDeviceRole theDevice,
                                                    Aspect_XRGenericAction     theAction) const
  {
    const NCollection_Array1<occ::handle<Aspect_XRAction>>& anActions = myRoleActions[theDevice];
    return anActions[theAction];
  }

public:
  enum InfoString
  {
    InfoString_Vendor,
    InfoString_Device,
    InfoString_Tracker,
    InfoString_SerialNumber,
  };

  virtual TCollection_AsciiString GetString(InfoString theInfo) const = 0;

protected:
  Standard_EXPORT Aspect_XRSession();

  virtual occ::handle<Graphic3d_ArrayOfTriangles> loadRenderModel(
    int                         theDevice,
    bool                        theToApplyUnitFactor,
    occ::handle<Image_Texture>& theTexture) = 0;

  virtual void triggerHapticVibrationAction(const occ::handle<Aspect_XRAction>& theAction,
                                            const Aspect_XRHapticActionData&    theParams) = 0;

protected:
  NCollection_Array1<occ::handle<Aspect_XRAction>>

    myRoleActions[Aspect_XRTrackedDeviceRole_NB];
  NCollection_IndexedDataMap<TCollection_AsciiString, occ::handle<Aspect_XRActionSet>> myActionSets;
  TrackingUniverseOrigin                       myTrackOrigin;
  NCollection_Array1<Aspect_TrackedDevicePose> myTrackedPoses;
  gp_Trsf                                      myHeadPose;
  NCollection_Vec2<int>                        myRendSize;
  Aspect_FrustumLRBT<double>                   myFrustumL;
  Aspect_FrustumLRBT<double>                   myFrustumR;
  double                                       myUnitFactor;

  double myAspect;
  double myFieldOfView;
  double myIod;
  float  myDispFreq;
};
