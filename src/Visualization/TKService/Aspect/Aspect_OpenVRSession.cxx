

#include <Aspect_OpenVRSession.hpp>

#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Image_PixMap.hpp>
#include <Image_Texture.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <NCollection_LocalArray.hpp>
#include <OSD.hpp>
#include <OSD_Environment.hpp>
#include <OSD_File.hpp>
#include <OSD_Process.hpp>

#ifdef HAVE_OPENVR
  #include <openvr.h>

namespace
{

  static const char* getVRCompositorError(vr::EVRCompositorError theVRError)
  {
    switch (theVRError)
    {
      case vr::VRCompositorError_None:
        return "None";
      case vr::VRCompositorError_RequestFailed:
        return "Request Failed";
      case vr::VRCompositorError_IncompatibleVersion:
        return "Incompatible Version";
      case vr::VRCompositorError_DoNotHaveFocus:
        return "Do not have focus";
      case vr::VRCompositorError_InvalidTexture:
        return "Invalid Texture";
      case vr::VRCompositorError_IsNotSceneApplication:
        return "Is not scene application";
      case vr::VRCompositorError_TextureIsOnWrongDevice:
        return "Texture is on wrong device";
      case vr::VRCompositorError_TextureUsesUnsupportedFormat:
        return "Texture uses unsupported format";
      case vr::VRCompositorError_SharedTexturesNotSupported:
        return "Shared textures not supported";
      case vr::VRCompositorError_IndexOutOfRange:
        return "Index out of range";
      case vr::VRCompositorError_AlreadySubmitted:
        return "Already submitted";
      case vr::VRCompositorError_InvalidBounds:
        return "Invalid Bounds";
      case vr::VRCompositorError_AlreadySet:
        return "Already set";
    }
    return "UNKNOWN";
  }

  static const char* getVRInputError(vr::EVRInputError theVRError)
  {
    switch (theVRError)
    {
      case vr::VRInputError_None:
        return "None";
      case vr::VRInputError_NameNotFound:
        return "NameNotFound";
      case vr::VRInputError_WrongType:
        return "WrongType";
      case vr::VRInputError_InvalidHandle:
        return "InvalidHandle";
      case vr::VRInputError_InvalidParam:
        return "InvalidParam";
      case vr::VRInputError_NoSteam:
        return "NoSteam:";
      case vr::VRInputError_MaxCapacityReached:
        return "MaxCapacityReached";
      case vr::VRInputError_IPCError:
        return "IPCError";
      case vr::VRInputError_NoActiveActionSet:
        return "NoActiveActionSet";
      case vr::VRInputError_InvalidDevice:
        return "InvalidDevice";
      case vr::VRInputError_InvalidSkeleton:
        return "InvalidSkeleton";
      case vr::VRInputError_InvalidBoneCount:
        return "InvalidBoneCount";
      case vr::VRInputError_InvalidCompressedData:
        return "InvalidCompressedData";
      case vr::VRInputError_NoData:
        return "NoData";
      case vr::VRInputError_BufferTooSmall:
        return "BufferTooSmall";
      case vr::VRInputError_MismatchedActionManifest:
        return "MismatchedActionManifest";
      case vr::VRInputError_MissingSkeletonData:
        return "MissingSkeletonData";
      case vr::VRInputError_InvalidBoneIndex:
        return "InvalidBoneIndex";
      case vr::VRInputError_InvalidPriority:
        return "InvalidPriority";
      case vr::VRInputError_PermissionDenied:
        return "PermissionDenied";
      case vr::VRInputError_InvalidRenderModel:
        return "InvalidRenderModel";
    }
    return "UNKNOWN";
  }

  static NCollection_Mat4<double> mat44vr2Occ(const vr::HmdMatrix44_t& theMat4)
  {
    NCollection_Mat4<double> aMat4;
    for (int aRow = 0; aRow < 4; ++aRow)
    {
      aMat4.SetRow(aRow,
                   NCollection_Vec4<double>(theMat4.m[aRow][0],
                                            theMat4.m[aRow][1],
                                            theMat4.m[aRow][2],
                                            theMat4.m[aRow][3]));
    }
    return aMat4;
  }

  static gp_Trsf mat34vr2OccTrsf(const vr::HmdMatrix34_t& theMat4)
  {
    gp_Trsf aTrsf;
    aTrsf.SetValues(theMat4.m[0][0],
                    theMat4.m[0][1],
                    theMat4.m[0][2],
                    theMat4.m[0][3],
                    theMat4.m[1][0],
                    theMat4.m[1][1],
                    theMat4.m[1][2],
                    theMat4.m[1][3],
                    theMat4.m[2][0],
                    theMat4.m[2][1],
                    theMat4.m[2][2],
                    theMat4.m[2][3]);
    return aTrsf;
  }

  static Aspect_TrackedDevicePose poseVr2Occ(const vr::TrackedDevicePose_t& theVrPose,
                                             const double                   theUnitFactor)
  {
    Aspect_TrackedDevicePose aPose;
    aPose.Velocity.SetCoord(theVrPose.vVelocity.v[0],
                            theVrPose.vVelocity.v[1],
                            theVrPose.vVelocity.v[2]);
    aPose.AngularVelocity.SetCoord(theVrPose.vAngularVelocity.v[0],
                                   theVrPose.vAngularVelocity.v[1],
                                   theVrPose.vAngularVelocity.v[2]);
    aPose.IsValidPose       = theVrPose.bPoseIsValid;
    aPose.IsConnectedDevice = theVrPose.bDeviceIsConnected;
    if (aPose.IsValidPose)
    {
      aPose.Orientation = mat34vr2OccTrsf(theVrPose.mDeviceToAbsoluteTracking);
      if (theUnitFactor != 1.0)
      {
        aPose.Orientation.SetTranslationPart(aPose.Orientation.TranslationPart() * theUnitFactor);
      }
    }
    return aPose;
  }

  TCollection_AsciiString defaultActionsManifestInit()
  {
    const TCollection_AsciiString THE_ACTIONS_JSON = "occtvr_actions.json";
    const TCollection_AsciiString aResRoot(OSD_Environment("CSF_OCCTResourcePath").Value());
    if (!aResRoot.IsEmpty())
    {
      if (OSD_File(aResRoot + "/" + THE_ACTIONS_JSON).Exists())
      {
        return aResRoot + "/" + THE_ACTIONS_JSON;
      }
      if (OSD_File(aResRoot + "/XRResources/" + THE_ACTIONS_JSON).Exists())
      {
        return aResRoot + "/XRResources/" + THE_ACTIONS_JSON;
      }
    }
    const TCollection_AsciiString aCasRoot(OSD_Environment("CASROOT").Value());
    if (!aCasRoot.IsEmpty())
    {
      if (OSD_File(aCasRoot + "/" + THE_ACTIONS_JSON).Exists())
      {
        return aCasRoot + "/" + THE_ACTIONS_JSON;
      }
      if (OSD_File(aCasRoot + "/XRResources/" + THE_ACTIONS_JSON).Exists())
      {
        return aCasRoot + "/XRResources/" + THE_ACTIONS_JSON;
      }
      if (OSD_File(aCasRoot + "/XRResources/src/" + THE_ACTIONS_JSON).Exists())
      {
        return aCasRoot + "/XRResources/src/" + THE_ACTIONS_JSON;
      }
    }
    return OSD_Process::ExecutableFolder() + "/occtvr_actions.json";
  }
} // namespace
#endif

IMPLEMENT_STANDARD_RTTIEXT(Aspect_OpenVRSession, Aspect_XRSession)

struct Aspect_OpenVRSession::VRContext
{
#ifdef HAVE_OPENVR

  vr::TrackedDevicePose_t TrackedPoses[vr::k_unMaxTrackedDeviceCount];

  vr::IVRSystem* System;

  VRContext()
      : System(nullptr)
  {
    memset(TrackedPoses, 0, sizeof(TrackedPoses));
  }

  bool PollNextEvent(vr::VREvent_t& theEvent)
  {
    return System->PollNextEvent(&theEvent, sizeof(vr::VREvent_t));
  }

  bool GetControllerState(vr::VRControllerState_t& theState, vr::TrackedDeviceIndex_t theDevice)
  {
    return System->GetControllerState(theDevice, &theState, sizeof(vr::VRControllerState_t&));
  }

  TCollection_AsciiString getVrTrackedDeviceString(vr::TrackedDeviceIndex_t  theDevice,
                                                   vr::TrackedDeviceProperty theProperty,
                                                   vr::TrackedPropertyError* theError = nullptr)
  {
    const uint32_t aBuffLen =
      System->GetStringTrackedDeviceProperty(theDevice, theProperty, nullptr, 0, theError);
    if (aBuffLen == 0)
    {
      return TCollection_AsciiString();
    }

    NCollection_LocalArray<char> aBuffer(aBuffLen + 1);
    System->GetStringTrackedDeviceProperty(theDevice, theProperty, aBuffer, aBuffLen, theError);
    aBuffer[aBuffLen] = '\0';
    const TCollection_AsciiString aResult(aBuffer);
    return aResult;
  }
#endif
};

#ifdef HAVE_OPENVR

class Aspect_OpenVRSession::VRImagePixmap : public Image_PixMap
{
public:
  VRImagePixmap()
      : myVrTexture(nullptr)
  {
  }

  bool Load(vr::TextureID_t theTexture, const TCollection_AsciiString& theVrModelName)
  {
    vr::RenderModel_TextureMap_t* aVrTexture = nullptr;
    vr::EVRRenderModelError       aVrError   = vr::VRRenderModelError_Loading;
    for (; aVrError == vr::VRRenderModelError_Loading;)
    {
      aVrError = vr::VRRenderModels()->LoadTexture_Async(theTexture, &aVrTexture);
      OSD::MilliSecSleep(1);
    }
    if (aVrError != vr::VRRenderModelError_None || aVrTexture == nullptr)
    {
      Message::SendFail(TCollection_AsciiString("OpenVR, Unable to load render model texture: ")
                        + theVrModelName + " - " + int(aVrError));
      return false;
    }

    InitWrapper(Image_Format_RGBA,
                (uint8_t*)aVrTexture->rubTextureMapData,
                aVrTexture->unWidth,
                aVrTexture->unHeight);
    myVrTexture = aVrTexture;
    return true;
  }

  ~VRImagePixmap() override
  {
    if (myVrTexture != nullptr)
    {
      vr::VRRenderModels()->FreeTexture(myVrTexture);
    }
  }

private:
  vr::RenderModel_TextureMap_t* myVrTexture;
};

class Aspect_OpenVRSession::VRTextureSource : public Image_Texture
{
public:
  VRTextureSource(vr::TextureID_t theTextureId, const TCollection_AsciiString& theVrModelName)
      : Image_Texture(""),
        myVrTextureId(theTextureId),
        myVrModelName(theVrModelName)
  {
    myTextureId = TCollection_AsciiString("texturevr://map_#") + (int)theTextureId;
  }

protected:
  occ::handle<Image_PixMap> ReadImage(const occ::handle<Image_SupportedFormats>&) const override
  {
    occ::handle<VRImagePixmap> aPixmap = new VRImagePixmap();
    if (!aPixmap->Load(myVrTextureId, myVrModelName))
    {
      return occ::handle<VRImagePixmap>();
    }
    return aPixmap;
  }

private:
  vr::TextureID_t         myVrTextureId;
  TCollection_AsciiString myVrModelName;
};
#endif

bool Aspect_OpenVRSession::IsHmdPresent()
{
#ifdef HAVE_OPENVR
  return vr::VR_IsHmdPresent();
#else
  return false;
#endif
}

TCollection_AsciiString Aspect_OpenVRSession::defaultActionsManifest()
{
#ifdef HAVE_OPENVR
  static const TCollection_AsciiString THE_ACTIONS_JSON_FULL = defaultActionsManifestInit();
  return THE_ACTIONS_JSON_FULL;
#else
  return TCollection_AsciiString();
#endif
}

Aspect_OpenVRSession::Aspect_OpenVRSession()
    : myContext(new VRContext())
{
#ifdef HAVE_OPENVR
  myActionsManifest = defaultActionsManifest();
  myTrackedPoses.Resize(0, (int)vr::k_unMaxTrackedDeviceCount - 1, false);
  {
    occ::handle<Aspect_XRActionSet> aHeadActionSet =
      new Aspect_XRActionSet("/actions/generic_head");
    myActionSets.Add(aHeadActionSet->Id(), aHeadActionSet);

    occ::handle<Aspect_XRAction> aHeadsetOn =
      new Aspect_XRAction(aHeadActionSet->Id() + "/in/headset_on_head",
                          Aspect_XRActionType_InputDigital);
    aHeadActionSet->AddAction(aHeadsetOn);
    NCollection_Array1<occ::handle<Aspect_XRAction>>& aGenericSet =
      myRoleActions[Aspect_XRTrackedDeviceRole_Head];
    aGenericSet[Aspect_XRGenericAction_IsHeadsetOn] = aHeadsetOn;
  }
  for (int aHand = 0; aHand < 2; ++aHand)
  {
    NCollection_Array1<occ::handle<Aspect_XRAction>>& aGenericSet =
      myRoleActions[aHand == 0 ? Aspect_XRTrackedDeviceRole_LeftHand
                               : Aspect_XRTrackedDeviceRole_RightHand];
    occ::handle<Aspect_XRActionSet> anActionSet =
      new Aspect_XRActionSet(aHand == 0 ? "/actions/generic_left" : "/actions/generic_right");
    myActionSets.Add(anActionSet->Id(), anActionSet);

    occ::handle<Aspect_XRAction> anAppMenuClick =
      new Aspect_XRAction(anActionSet->Id() + "/in/appmenu_click",
                          Aspect_XRActionType_InputDigital);
    anActionSet->AddAction(anAppMenuClick);
    aGenericSet[Aspect_XRGenericAction_InputAppMenu] = anAppMenuClick;

    occ::handle<Aspect_XRAction> aSysMenuClick =
      new Aspect_XRAction(anActionSet->Id() + "/in/sysmenu_click",
                          Aspect_XRActionType_InputDigital);
    anActionSet->AddAction(aSysMenuClick);
    aGenericSet[Aspect_XRGenericAction_InputSysMenu] = aSysMenuClick;

    occ::handle<Aspect_XRAction> aTriggerPull =
      new Aspect_XRAction(anActionSet->Id() + "/in/trigger_pull", Aspect_XRActionType_InputAnalog);
    anActionSet->AddAction(aTriggerPull);
    aGenericSet[Aspect_XRGenericAction_InputTriggerPull] = aTriggerPull;

    occ::handle<Aspect_XRAction> aTriggerClick =
      new Aspect_XRAction(anActionSet->Id() + "/in/trigger_click",
                          Aspect_XRActionType_InputDigital);
    anActionSet->AddAction(aTriggerClick);
    aGenericSet[Aspect_XRGenericAction_InputTriggerClick] = aTriggerClick;

    occ::handle<Aspect_XRAction> aGripClick =
      new Aspect_XRAction(anActionSet->Id() + "/in/grip_click", Aspect_XRActionType_InputDigital);
    anActionSet->AddAction(aGripClick);
    aGenericSet[Aspect_XRGenericAction_InputGripClick] = aGripClick;

    occ::handle<Aspect_XRAction> aPadPos =
      new Aspect_XRAction(anActionSet->Id() + "/in/trackpad_position",
                          Aspect_XRActionType_InputAnalog);
    anActionSet->AddAction(aPadPos);
    aGenericSet[Aspect_XRGenericAction_InputTrackPadPosition] = aPadPos;

    occ::handle<Aspect_XRAction> aPadTouch =
      new Aspect_XRAction(anActionSet->Id() + "/in/trackpad_touch",
                          Aspect_XRActionType_InputDigital);
    anActionSet->AddAction(aPadTouch);
    aGenericSet[Aspect_XRGenericAction_InputTrackPadTouch] = aPadTouch;

    occ::handle<Aspect_XRAction> aPadClick =
      new Aspect_XRAction(anActionSet->Id() + "/in/trackpad_click",
                          Aspect_XRActionType_InputDigital);
    anActionSet->AddAction(aPadClick);
    aGenericSet[Aspect_XRGenericAction_InputTrackPadClick] = aPadClick;

    occ::handle<Aspect_XRAction> aPoseBase =
      new Aspect_XRAction(anActionSet->Id() + "/in/pose_base", Aspect_XRActionType_InputPose);
    anActionSet->AddAction(aPoseBase);
    aGenericSet[Aspect_XRGenericAction_InputPoseBase] = aPoseBase;

    occ::handle<Aspect_XRAction> aPoseFront =
      new Aspect_XRAction(anActionSet->Id() + "/in/pose_front", Aspect_XRActionType_InputPose);
    anActionSet->AddAction(aPoseFront);
    aGenericSet[Aspect_XRGenericAction_InputPoseFront] = aPoseFront;

    occ::handle<Aspect_XRAction> aPoseGrip =
      new Aspect_XRAction(anActionSet->Id() + "/in/pose_handgrip", Aspect_XRActionType_InputPose);
    anActionSet->AddAction(aPoseGrip);
    aGenericSet[Aspect_XRGenericAction_InputPoseHandGrip] = aPoseGrip;

    occ::handle<Aspect_XRAction> aPoseTip =
      new Aspect_XRAction(anActionSet->Id() + "/in/pose_tip", Aspect_XRActionType_InputPose);
    anActionSet->AddAction(aPoseTip);
    aGenericSet[Aspect_XRGenericAction_InputPoseFingerTip] = aPoseTip;

    occ::handle<Aspect_XRAction> aHaptic =
      new Aspect_XRAction(anActionSet->Id() + "/out/haptic", Aspect_XRActionType_OutputHaptic);
    anActionSet->AddAction(aHaptic);
    aGenericSet[Aspect_XRGenericAction_OutputHaptic] = aHaptic;

    occ::handle<Aspect_XRAction> aThumbsctickPos =
      new Aspect_XRAction(anActionSet->Id() + "/in/thumbstick_position",
                          Aspect_XRActionType_InputAnalog);
    anActionSet->AddAction(aThumbsctickPos);
    aGenericSet[Aspect_XRGenericAction_InputThumbstickPosition] = aThumbsctickPos;

    occ::handle<Aspect_XRAction> aThumbsctickTouch =
      new Aspect_XRAction(anActionSet->Id() + "/in/thumbstick_touch",
                          Aspect_XRActionType_InputDigital);
    anActionSet->AddAction(aThumbsctickTouch);
    aGenericSet[Aspect_XRGenericAction_InputThumbstickTouch] = aThumbsctickTouch;

    occ::handle<Aspect_XRAction> aThumbsctickClick =
      new Aspect_XRAction(anActionSet->Id() + "/in/thumbstick_click",
                          Aspect_XRActionType_InputDigital);
    anActionSet->AddAction(aThumbsctickClick);
    aGenericSet[Aspect_XRGenericAction_InputThumbstickClick] = aThumbsctickClick;
  }
#endif
}

Aspect_OpenVRSession::~Aspect_OpenVRSession()
{
  closeVR();
  delete myContext;
}

void Aspect_OpenVRSession::closeVR()
{
#ifdef HAVE_OPENVR
  if (myContext->System != nullptr)
  {
    vr::VR_Shutdown();
    myContext->System = nullptr;
  }
#endif
}

void* Aspect_OpenVRSession::getVRSystem() const
{
#ifdef HAVE_OPENVR
  return myContext->System;
#else
  return nullptr;
#endif
}

void Aspect_OpenVRSession::Close()
{
  closeVR();
}

bool Aspect_OpenVRSession::IsOpen() const
{
#ifdef HAVE_OPENVR
  return myContext->System != nullptr;
#else
  return false;
#endif
}

bool Aspect_OpenVRSession::Open()
{
#ifdef HAVE_OPENVR
  if (myContext->System != nullptr)
  {
    return true;
  }

  vr::EVRInitError aVrError = vr::VRInitError_None;
  myContext->System         = vr::VR_Init(&aVrError, vr::VRApplication_Scene);
  if (aVrError != vr::VRInitError_None)
  {
    myContext->System = nullptr;
    Message::SendFail(TCollection_AsciiString("OpenVR, Unable to init VR runtime: ")
                      + vr::VR_GetVRInitErrorAsEnglishDescription(aVrError));
    Close();
    return false;
  }

  NCollection_Vec2<uint32_t> aRenderSize;
  myContext->System->GetRecommendedRenderTargetSize(&aRenderSize.x(), &aRenderSize.y());
  myRendSize = NCollection_Vec2<int>(aRenderSize);
  myDispFreq = myContext->System->GetFloatTrackedDeviceProperty(vr::k_unTrackedDeviceIndex_Hmd,
                                                                vr::Prop_DisplayFrequency_Float);
  if (myRendSize.x() <= 0 || myRendSize.y() <= 0)
  {
    Close();
    return false;
  }
  updateProjectionFrustums();
  initInput();
  return true;
#else
  Message::SendFail("Open CASCADE has been built without OpenVR support");
  return false;
#endif
}

bool Aspect_OpenVRSession::initInput()
{
#ifdef HAVE_OPENVR
  if (myContext->System == nullptr)
  {
    return false;
  }

  if (!OSD_File(myActionsManifest).Exists())
  {
    Message::SendFail(TCollection_AsciiString("OpenVR, Unable to open actions manifest '")
                      + myActionsManifest + "'");
    return false;
  }

  vr::EVRInputError aVrError = vr::VRInput()->SetActionManifestPath(myActionsManifest.ToCString());
  if (aVrError != vr::VRInputError_None)
  {
    Message::SendFail(TCollection_AsciiString("OpenVR, Unable to load actions manifest '")
                      + myActionsManifest + "': " + getVRInputError(aVrError));
    return false;
  }

  bool hasErrors = false;
  for (NCollection_IndexedDataMap<TCollection_AsciiString,
                                  occ::handle<Aspect_XRActionSet>>::Iterator aSetIter(myActionSets);
       aSetIter.More();
       aSetIter.Next())
  {
    const occ::handle<Aspect_XRActionSet>& anActionSet = aSetIter.Value();
    for (NCollection_IndexedDataMap<TCollection_AsciiString, occ::handle<Aspect_XRAction>>::Iterator
           anActionIter(anActionSet->Actions());
         anActionIter.More();
         anActionIter.Next())
    {
      const occ::handle<Aspect_XRAction>& anAction       = anActionIter.Value();
      vr::VRActionHandle_t                anActionHandle = 0;
      aVrError = vr::VRInput()->GetActionHandle(anAction->Id().ToCString(), &anActionHandle);
      if (aVrError == vr::VRInputError_None)
      {
        anAction->SetRawHandle(anActionHandle);
      }
      else
      {
        hasErrors = true;
        Message::SendFail(TCollection_AsciiString("OpenVR, Unable to load action '")
                          + anAction->Id() + "' from '" + myActionsManifest
                          + "': " + getVRInputError(aVrError));
      }
    }

    vr::VRActionSetHandle_t anActionSetHandle = 0;
    aVrError = vr::VRInput()->GetActionSetHandle(anActionSet->Id().ToCString(), &anActionSetHandle);
    if (aVrError == vr::VRInputError_None)
    {
      anActionSet->SetRawHandle(anActionSetHandle);
    }
    else
    {
      hasErrors = true;
      Message::SendFail(TCollection_AsciiString("OpenVR, Unable to load action set '")
                        + anActionSet->Id() + "' from '" + myActionsManifest
                        + "': " + getVRInputError(aVrError));
    }
  }
  return !hasErrors;
#else
  return false;
#endif
}

TCollection_AsciiString Aspect_OpenVRSession::GetString(InfoString theInfo) const
{
#ifdef HAVE_OPENVR
  if (myContext->System != nullptr)
  {
    vr::ETrackedDeviceProperty aVrProp = vr::Prop_Invalid;
    switch (theInfo)
    {
      case InfoString_Vendor:
        aVrProp = vr::Prop_ManufacturerName_String;
        break;
      case InfoString_Device:
        aVrProp = vr::Prop_ModelNumber_String;
        break;
      case InfoString_Tracker:
        aVrProp = vr::Prop_TrackingSystemName_String;
        break;
      case InfoString_SerialNumber:
        aVrProp = vr::Prop_SerialNumber_String;
        break;
    }
    if (aVrProp != vr::Prop_Invalid)
    {
      return myContext->getVrTrackedDeviceString(vr::k_unTrackedDeviceIndex_Hmd, aVrProp);
    }
  }
#else
  (void)theInfo;
#endif
  return TCollection_AsciiString();
}

int Aspect_OpenVRSession::NamedTrackedDevice(Aspect_XRTrackedDeviceRole theDevice) const
{
#ifdef HAVE_OPENVR
  if (myContext->System != nullptr)
  {
    vr::TrackedDeviceIndex_t aDevIndex = vr::k_unTrackedDeviceIndexInvalid;
    switch (theDevice)
    {
      case Aspect_XRTrackedDeviceRole_Head:
        aDevIndex = vr::k_unTrackedDeviceIndex_Hmd;
        break;
      case Aspect_XRTrackedDeviceRole_LeftHand:
        aDevIndex = myContext->System->GetTrackedDeviceIndexForControllerRole(
          vr::TrackedControllerRole_LeftHand);
        break;
      case Aspect_XRTrackedDeviceRole_RightHand:
        aDevIndex = myContext->System->GetTrackedDeviceIndexForControllerRole(
          vr::TrackedControllerRole_RightHand);
        break;
      case Aspect_XRTrackedDeviceRole_Other:
        break;
    }
    if (aDevIndex == vr::k_unTrackedDeviceIndexInvalid)
    {
      return -1;
    }
    return (int)aDevIndex;
  }
#else
  (void)theDevice;
#endif
  return -1;
}

occ::handle<Graphic3d_ArrayOfTriangles> Aspect_OpenVRSession::loadRenderModel(
  int                         theDevice,
  bool                        theToApplyUnitFactor,
  occ::handle<Image_Texture>& theTexture)
{
  if (theDevice < 0)
  {
    return occ::handle<Graphic3d_ArrayOfTriangles>();
  }
#ifdef HAVE_OPENVR
  if (myContext->System == nullptr)
  {
    return occ::handle<Graphic3d_ArrayOfTriangles>();
  }

  const TCollection_AsciiString aRenderModelName =
    myContext->getVrTrackedDeviceString(theDevice, vr::Prop_RenderModelName_String);
  if (aRenderModelName.IsEmpty())
  {
    return occ::handle<Graphic3d_ArrayOfTriangles>();
  }

  vr::RenderModel_t*      aVrModel = nullptr;
  vr::EVRRenderModelError aVrError = vr::VRRenderModelError_Loading;
  for (; aVrError == vr::VRRenderModelError_Loading;)
  {
    aVrError = vr::VRRenderModels()->LoadRenderModel_Async(aRenderModelName.ToCString(), &aVrModel);
    OSD::MilliSecSleep(1);
  }
  if (aVrError != vr::VRRenderModelError_None)
  {
    Message::SendFail(TCollection_AsciiString("OpenVR, Unable to load render model: ")
                      + aRenderModelName + " - " + int(aVrError));
    return occ::handle<Graphic3d_ArrayOfTriangles>();
  }

  if (aVrModel->diffuseTextureId >= 0)
  {
    theTexture = new VRTextureSource(aVrModel->diffuseTextureId, aRenderModelName);
  }

  const float aScale                            = theToApplyUnitFactor ? float(myUnitFactor) : 1.0f;
  occ::handle<Graphic3d_ArrayOfTriangles> aTris = new Graphic3d_ArrayOfTriangles(
    (int)aVrModel->unVertexCount,
    (int)aVrModel->unTriangleCount * 3,
    Graphic3d_ArrayFlags_VertexNormal | Graphic3d_ArrayFlags_VertexTexel);
  for (uint32_t aVertIter = 0; aVertIter < aVrModel->unVertexCount; ++aVertIter)
  {
    const vr::RenderModel_Vertex_t& aVert = aVrModel->rVertexData[aVertIter];
    aTris->AddVertex(aVert.vPosition.v[0] * aScale,
                     aVert.vPosition.v[1] * aScale,
                     aVert.vPosition.v[2] * aScale,
                     aVert.vNormal.v[0],
                     aVert.vNormal.v[1],
                     aVert.vNormal.v[2],
                     aVert.rfTextureCoord[0],
                     aVert.rfTextureCoord[1]);
  }
  for (uint32_t aTriIter = 0; aTriIter < aVrModel->unTriangleCount; ++aTriIter)
  {
    aTris->AddEdges(aVrModel->rIndexData[aTriIter * 3 + 0] + 1,
                    aVrModel->rIndexData[aTriIter * 3 + 1] + 1,
                    aVrModel->rIndexData[aTriIter * 3 + 2] + 1);
  }

  vr::VRRenderModels()->FreeRenderModel(aVrModel);
  return aTris;
#else
  (void)theToApplyUnitFactor;
  (void)theTexture;
  return occ::handle<Graphic3d_ArrayOfTriangles>();
#endif
}

NCollection_Mat4<double> Aspect_OpenVRSession::EyeToHeadTransform(Aspect_Eye theEye) const
{
#ifdef HAVE_OPENVR
  if (myContext->System != nullptr)
  {
    const vr::HmdMatrix34_t aMatVr = myContext->System->GetEyeToHeadTransform(
      theEye == Aspect_Eye_Right ? vr::Eye_Right : vr::Eye_Left);
    gp_Trsf aTrsf = mat34vr2OccTrsf(aMatVr);
    if (myUnitFactor != 1.0)
    {
      aTrsf.SetTranslationPart(aTrsf.TranslationPart() * myUnitFactor);
    }
    NCollection_Mat4<double> aMat4;
    aTrsf.GetMat4(aMat4);
    return aMat4;
  }
#else
  (void)theEye;
#endif
  return NCollection_Mat4<double>();
}

NCollection_Mat4<double> Aspect_OpenVRSession::ProjectionMatrix(Aspect_Eye theEye,
                                                                double     theZNear,
                                                                double     theZFar) const
{
#ifdef HAVE_OPENVR
  if (myContext->System != nullptr)
  {
    const vr::HmdMatrix44_t aMat4 = myContext->System->GetProjectionMatrix(
      theEye == Aspect_Eye_Right ? vr::Eye_Right : vr::Eye_Left,
      (float)theZNear,
      (float)theZFar);
    return mat44vr2Occ(aMat4);
  }
#else
  (void)theEye;
  (void)theZNear;
  (void)theZFar;
#endif
  return NCollection_Mat4<double>();
}

void Aspect_OpenVRSession::updateProjectionFrustums()
{
#ifdef HAVE_OPENVR
  Aspect_FrustumLRBT<float> aFrustL, aFrustR;
  myContext->System->GetProjectionRaw(vr::Eye_Left,
                                      &aFrustL.Left,
                                      &aFrustL.Right,
                                      &aFrustL.Top,
                                      &aFrustL.Bottom);
  myContext->System->GetProjectionRaw(vr::Eye_Right,
                                      &aFrustR.Left,
                                      &aFrustR.Right,
                                      &aFrustR.Top,
                                      &aFrustR.Bottom);
  myFrustumL = Aspect_FrustumLRBT<double>(aFrustL);
  myFrustumR = Aspect_FrustumLRBT<double>(aFrustR);
  std::swap(myFrustumL.Top, myFrustumL.Bottom);
  std::swap(myFrustumR.Top, myFrustumR.Bottom);

  const NCollection_Vec2<double> aTanHalfFov(
    NCollection_Vec4<float>(-aFrustL.Left, aFrustL.Right, -aFrustR.Left, aFrustR.Right).maxComp(),
    NCollection_Vec4<float>(-aFrustL.Top, aFrustL.Bottom, -aFrustR.Top, aFrustR.Bottom).maxComp());
  myAspect      = aTanHalfFov.x() / aTanHalfFov.y();
  myFieldOfView = 2.0 * std::atan(aTanHalfFov.y()) * 180.0 / M_PI;

  myIod = myContext->System->GetFloatTrackedDeviceProperty(vr::k_unTrackedDeviceIndex_Hmd,
                                                           vr::Prop_UserIpdMeters_Float);
  myIod *= myUnitFactor;
#endif
}

void Aspect_OpenVRSession::SetTrackingOrigin(TrackingUniverseOrigin theOrigin)
{
#ifdef HAVE_OPENVR
  if (myContext->System != nullptr)
  {
    vr::ETrackingUniverseOrigin anOrigin = vr::TrackingUniverseStanding;
    switch (theOrigin)
    {
      case TrackingUniverseOrigin_Seated:
        anOrigin = vr::TrackingUniverseSeated;
        break;
      case TrackingUniverseOrigin_Standing:
        anOrigin = vr::TrackingUniverseStanding;
        break;
    }
    vr::VRCompositor()->SetTrackingSpace(anOrigin);
  }
#endif
  myTrackOrigin = theOrigin;
}

bool Aspect_OpenVRSession::WaitPoses()
{
#ifdef HAVE_OPENVR
  if (myContext->System == nullptr)
  {
    return false;
  }

  switch (vr::VRCompositor()->GetTrackingSpace())
  {
    case vr::TrackingUniverseSeated:
      myTrackOrigin = TrackingUniverseOrigin_Seated;
      break;
    case vr::TrackingUniverseRawAndUncalibrated:
    case vr::TrackingUniverseStanding:
      myTrackOrigin = TrackingUniverseOrigin_Standing;
      break;
  }

  const vr::EVRCompositorError aVRError =
    vr::VRCompositor()->WaitGetPoses(myContext->TrackedPoses,
                                     vr::k_unMaxTrackedDeviceCount,
                                     nullptr,
                                     0);
  if (aVRError != vr::VRCompositorError_None)
  {
    Message::SendTrace(TCollection_AsciiString("Compositor wait poses error: ")
                       + getVRCompositorError(aVRError));
  }

  for (int aPoseIter = myTrackedPoses.Lower(); aPoseIter <= myTrackedPoses.Upper(); ++aPoseIter)
  {
    const vr::TrackedDevicePose_t& aVrPose = myContext->TrackedPoses[aPoseIter];
    myTrackedPoses[aPoseIter]              = poseVr2Occ(aVrPose, myUnitFactor);
  }

  if (myContext->TrackedPoses[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
  {
    myHeadPose = myTrackedPoses[vr::k_unTrackedDeviceIndex_Hmd].Orientation;
    updateProjectionFrustums();
  }
  return aVRError != vr::VRCompositorError_None;
#else
  return false;
#endif
}

Aspect_XRDigitalActionData Aspect_OpenVRSession::GetDigitalActionData(
  const occ::handle<Aspect_XRAction>& theAction) const
{
  if (theAction.IsNull() || theAction->Type() != Aspect_XRActionType_InputDigital)
  {
    throw Standard_ProgramError(
      "Aspect_OpenVRSession::GetDigitalActionData() called for wrong action");
  }

  Aspect_XRDigitalActionData anActionData;
#ifdef HAVE_OPENVR
  if (myContext->System != nullptr && theAction->RawHandle() != 0)
  {
    vr::InputDigitalActionData_t aNewData = {};
    vr::EVRInputError            anInErr =
      vr::VRInput()->GetDigitalActionData(theAction->RawHandle(),
                                          &aNewData,
                                          sizeof(aNewData),
                                          vr::k_ulInvalidInputValueHandle);
    if (anInErr != vr::VRInputError_None)
    {
      Message::SendFail(TCollection_AsciiString("Input Error on '") + theAction->Id()
                        + "': " + getVRInputError(anInErr));
      return anActionData;
    }

    anActionData.IsActive     = aNewData.bActive;
    anActionData.IsChanged    = aNewData.bChanged;
    anActionData.IsPressed    = aNewData.bState;
    anActionData.UpdateTime   = aNewData.fUpdateTime;
    anActionData.ActiveOrigin = aNewData.activeOrigin;
  }
#endif
  return anActionData;
}

Aspect_XRAnalogActionData Aspect_OpenVRSession::GetAnalogActionData(
  const occ::handle<Aspect_XRAction>& theAction) const
{
  if (theAction.IsNull() || theAction->Type() != Aspect_XRActionType_InputAnalog)
  {
    throw Standard_ProgramError(
      "Aspect_OpenVRSession::GetAnalogActionData() called for wrong action");
  }

  Aspect_XRAnalogActionData anActionData;
#ifdef HAVE_OPENVR
  if (myContext->System != nullptr && theAction->RawHandle() != 0)
  {
    vr::InputAnalogActionData_t aNewData = {};
    vr::EVRInputError           anInErr = vr::VRInput()->GetAnalogActionData(theAction->RawHandle(),
                                                                   &aNewData,
                                                                   sizeof(aNewData),
                                                                   vr::k_ulInvalidInputValueHandle);
    if (anInErr != vr::VRInputError_None)
    {
      Message::SendFail(TCollection_AsciiString("Input Error on '") + theAction->Id()
                        + "': " + getVRInputError(anInErr));
      return anActionData;
    }

    anActionData.IsActive = aNewData.bActive;
    anActionData.VecXYZ.SetValues(aNewData.x, aNewData.y, aNewData.z);
    anActionData.DeltaXYZ.SetValues(aNewData.deltaX, aNewData.deltaY, aNewData.deltaZ);
    anActionData.UpdateTime   = aNewData.fUpdateTime;
    anActionData.ActiveOrigin = aNewData.activeOrigin;
  }
#endif
  return anActionData;
}

Aspect_XRPoseActionData Aspect_OpenVRSession::GetPoseActionDataForNextFrame(
  const occ::handle<Aspect_XRAction>& theAction) const
{
  if (theAction.IsNull() || theAction->Type() != Aspect_XRActionType_InputPose)
  {
    throw Standard_ProgramError(
      "Aspect_OpenVRSession::GetPoseActionDataForNextFrame() called for wrong action");
  }

  Aspect_XRPoseActionData anActionData;
#ifdef HAVE_OPENVR
  if (myContext->System != nullptr && theAction->RawHandle() != 0)
  {
    vr::ETrackingUniverseOrigin anOrigin = vr::TrackingUniverseSeated;
    switch (myTrackOrigin)
    {
      case TrackingUniverseOrigin_Seated:
        anOrigin = vr::TrackingUniverseSeated;
        break;
      case TrackingUniverseOrigin_Standing:
        anOrigin = vr::TrackingUniverseStanding;
        break;
    }
    vr::InputPoseActionData_t aNewData = {};
    vr::EVRInputError         anInErr =
      vr::VRInput()->GetPoseActionDataForNextFrame(theAction->RawHandle(),
                                                   anOrigin,
                                                   &aNewData,
                                                   sizeof(aNewData),
                                                   vr::k_ulInvalidInputValueHandle);
    if (anInErr != vr::VRInputError_None)
    {
      Message::SendFail(TCollection_AsciiString("Input Error on '") + theAction->Id()
                        + "': " + getVRInputError(anInErr));
      return anActionData;
    }

    anActionData.Pose         = poseVr2Occ(aNewData.pose, myUnitFactor);
    anActionData.IsActive     = aNewData.bActive;
    anActionData.ActiveOrigin = aNewData.activeOrigin;
  }
#endif
  return anActionData;
}

void Aspect_OpenVRSession::triggerHapticVibrationAction(
  const occ::handle<Aspect_XRAction>& theAction,
  const Aspect_XRHapticActionData&    theParams)
{
  if (theAction.IsNull() || theAction->Type() != Aspect_XRActionType_OutputHaptic)
  {
    throw Standard_ProgramError(
      "Aspect_OpenVRSession::triggerHapticVibrationAction() called for wrong action");
  }

#ifdef HAVE_OPENVR
  if (myContext->System != nullptr && theAction->RawHandle() != 0)
  {
    Aspect_XRHapticActionData aParams = theParams;
    if (!theParams.IsValid())
    {

      aParams.Duration  = 0.0f;
      aParams.Frequency = 1.0f;
      aParams.Amplitude = 0.1f;
    }
    vr::EVRInputError anInErr =
      vr::VRInput()->TriggerHapticVibrationAction(theAction->RawHandle(),
                                                  aParams.Delay,
                                                  aParams.Duration,
                                                  aParams.Frequency,
                                                  aParams.Amplitude,
                                                  vr::k_ulInvalidInputValueHandle);
    if (anInErr != vr::VRInputError_None)
    {
      Message::SendFail(TCollection_AsciiString("Output Error on '") + theAction->Id()
                        + "': " + getVRInputError(anInErr));
    }
  }
#else
  (void)theParams;
#endif
}

void Aspect_OpenVRSession::ProcessEvents()
{
#ifdef HAVE_OPENVR
  if (myContext->System == nullptr)
  {
    return;
  }

  vr::VREvent_t aVREvent = {};
  for (; myContext->PollNextEvent(aVREvent);)
  {
    switch (aVREvent.eventType)
    {
      case vr::VREvent_TrackedDeviceActivated:
        onTrackedDeviceActivated((int)aVREvent.trackedDeviceIndex);
        break;
      case vr::VREvent_TrackedDeviceDeactivated:
        onTrackedDeviceDeactivated((int)aVREvent.trackedDeviceIndex);
        break;
      case vr::VREvent_TrackedDeviceUpdated:
        onTrackedDeviceUpdated((int)aVREvent.trackedDeviceIndex);
        break;
    }
  }

  if (myActionSets.Extent() > 0)
  {
    NCollection_LocalArray<vr::VRActiveActionSet_t, 8> anActionSets(myActionSets.Extent());
    memset(anActionSets, 0, sizeof(vr::VRActiveActionSet_t) * myActionSets.Extent());
    for (int aSetIter = 0; aSetIter < myActionSets.Extent(); ++aSetIter)
    {
      anActionSets[aSetIter].ulActionSet = myActionSets.FindFromIndex(aSetIter + 1)->RawHandle();
    }
    vr::VRInput()->UpdateActionState(anActionSets,
                                     sizeof(vr::VRActiveActionSet_t),
                                     myActionSets.Extent());
  }

  WaitPoses();

  for (NCollection_IndexedDataMap<TCollection_AsciiString,
                                  occ::handle<Aspect_XRActionSet>>::Iterator aSetIter(myActionSets);
       aSetIter.More();
       aSetIter.Next())
  {
    const occ::handle<Aspect_XRActionSet>& anActionSet = aSetIter.Value();
    for (NCollection_IndexedDataMap<TCollection_AsciiString, occ::handle<Aspect_XRAction>>::Iterator
           anActionIter(anActionSet->Actions());
         anActionIter.More();
         anActionIter.Next())
    {
      const occ::handle<Aspect_XRAction>& anAction = anActionIter.Value();
      if (anAction->RawHandle() == 0 || anAction->Id().IsEmpty())
      {
        continue;
      }

      switch (anAction->Type())
      {
        case Aspect_XRActionType_InputDigital:
        {
          GetDigitalActionData(anAction);
          break;
        }
        case Aspect_XRActionType_InputAnalog:
        {
          GetAnalogActionData(anAction);
          break;
        }
        case Aspect_XRActionType_InputPose:
        {
          GetPoseActionDataForNextFrame(anAction);
          break;
        }
        default:
          break;
      }
    }
  }

#endif
}

void Aspect_OpenVRSession::onTrackedDeviceActivated(int theDeviceIndex)
{
  Message::SendTrace(TCollection_AsciiString("OpenVR, Device ") + theDeviceIndex + " attached");
}

void Aspect_OpenVRSession::onTrackedDeviceDeactivated(int theDeviceIndex)
{
  Message::SendTrace(TCollection_AsciiString("OpenVR, Device ") + theDeviceIndex + " detached");
}

void Aspect_OpenVRSession::onTrackedDeviceUpdated(int theDeviceIndex)
{
  Message::SendTrace(TCollection_AsciiString("OpenVR, Device ") + theDeviceIndex + " updated");
}

bool Aspect_OpenVRSession::SubmitEye(void*                  theTexture,
                                     Aspect_GraphicsLibrary theGraphicsLib,
                                     Aspect_ColorSpace      theColorSpace,
                                     Aspect_Eye             theEye)
{
  if (theTexture == nullptr)
  {
    return false;
  }
#ifdef HAVE_OPENVR
  if (myContext->System == nullptr)
  {
    return false;
  }

  vr::Texture_t aVRTexture = {(void*)theTexture, vr::TextureType_OpenGL, vr::ColorSpace_Gamma};
  switch (theGraphicsLib)
  {
    case Aspect_GraphicsLibrary_OpenGL:
      aVRTexture.eType = vr::TextureType_OpenGL;
      break;
    default:
      Message::SendFail("Compositor error: unsupported Graphics API");
      return false;
  }
  switch (theColorSpace)
  {
    case Aspect_ColorSpace_sRGB:
      aVRTexture.eColorSpace = vr::ColorSpace_Gamma;
      break;
    case Aspect_ColorSpace_Linear:
      aVRTexture.eColorSpace = vr::ColorSpace_Linear;
      break;
  }

  const vr::EVRCompositorError aVRError =
    vr::VRCompositor()->Submit(theEye == Aspect_Eye_Right ? vr::Eye_Right : vr::Eye_Left,
                               &aVRTexture);
  if (aVRError != vr::VRCompositorError_None)
  {
    if (aVRError != vr::VRCompositorError_AlreadySubmitted)
    {
      Message::SendFail(TCollection_AsciiString("Compositor Error: ")
                        + getVRCompositorError(aVRError));
    }
    else
    {
      Message::SendTrace(TCollection_AsciiString("Compositor Error: ")
                         + getVRCompositorError(aVRError));
    }
    return false;
  }
  return true;
#else
  (void)theGraphicsLib;
  (void)theColorSpace;
  (void)theEye;
  return false;
#endif
}
