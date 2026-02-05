#pragma once

// Copyright (c) 2020 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

//! Texture color spaces accepted by XR composer.
enum Aspect_ColorSpace
{
  Aspect_ColorSpace_sRGB   = 0, //!< non-linear sRGB color space
  Aspect_ColorSpace_Linear = 1, //!< linear RGB color space
};

#include <Aspect_Eye.hpp>
#include <Aspect_FrustumLRBT.hpp>
#include <Aspect_GraphicsLibrary.hpp>

// Copyright (c) 2020 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

// Copyright (c) 2020 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

// Copyright (c) 2020 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

//! XR action type.
enum Aspect_XRActionType
{
  Aspect_XRActionType_InputDigital,  //!< boolean input (like button)
  Aspect_XRActionType_InputAnalog,   //!< analog input (1/2/3 axes)
  Aspect_XRActionType_InputPose,     //!< positional input
  Aspect_XRActionType_InputSkeletal, //!< skeletal input
  Aspect_XRActionType_OutputHaptic   //!< haptic output (vibration)
};

#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

//! XR action definition.
class Aspect_XRAction : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Aspect_XRAction, Standard_Transient)
public:
  //! Return action id.
  const TCollection_AsciiString& Id() const { return myId; }

  //! Return action type.
  Aspect_XRActionType Type() const { return myType; }

  //! Return TRUE if action is defined.
  bool IsValid() const { return myRawHandle != 0; }

  //! Return action handle.
  uint64_t RawHandle() const { return myRawHandle; }

  //! Set action handle.
  void SetRawHandle(uint64_t theHande) { myRawHandle = theHande; }

  //! Main constructor.
  Aspect_XRAction(const TCollection_AsciiString& theId, const Aspect_XRActionType theType)
      : myId(theId),
        myRawHandle(0),
        myType(theType)
  {
  }

protected:
  TCollection_AsciiString myId;        //!< action id
  uint64_t                myRawHandle; //!< action handle
  Aspect_XRActionType     myType;      //!< action type
};

//! Map of actions with action Id as a key.

//! XR action set.
class Aspect_XRActionSet : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Aspect_XRActionSet, Standard_Transient)
public:
  //! Return action id.
  const TCollection_AsciiString& Id() const { return myId; }

  //! Return action handle.
  uint64_t RawHandle() const { return myRawHandle; }

  //! Set action handle.
  void SetRawHandle(uint64_t theHande) { myRawHandle = theHande; }

  //! Add action.
  void AddAction(const occ::handle<Aspect_XRAction>& theAction)
  {
    myActions.Add(theAction->Id(), theAction);
  }

  //! Return map of actions.
  const NCollection_IndexedDataMap<TCollection_AsciiString, occ::handle<Aspect_XRAction>>& Actions()
    const
  {
    return myActions;
  }

  //! Main constructor.
  Aspect_XRActionSet(const TCollection_AsciiString& theId)
      : myId(theId),
        myRawHandle(0)
  {
  }

protected:
  TCollection_AsciiString myId;        //!< action set id
  uint64_t                myRawHandle; //!< action set handle
  NCollection_IndexedDataMap<TCollection_AsciiString, occ::handle<Aspect_XRAction>>
    myActions; //!< map of actions
};

// Copyright (c) 2020 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <NCollection_Vec3.hpp>

//! Analog input XR action data.
struct Aspect_XRAnalogActionData
{
  uint64_t ActiveOrigin; //!< The origin that caused this action's current state
                         // clang-format off
  float                   UpdateTime;   //!< Time relative to now when this event happened. Will be negative to indicate a past time
  NCollection_Vec3<float> VecXYZ;       //!< the current state of this action
  NCollection_Vec3<float> DeltaXYZ;     //!< deltas since the previous update
  bool                    IsActive;     //!< whether or not this action is currently available to be bound in the active action set
                         // clang-format on

  //! Return TRUE if delta is non-zero.
  bool IsChanged() { return !DeltaXYZ.IsEqual(NCollection_Vec3<float>(0.0f, 0.0f, 0.0f)); }

  //! Empty constructor.
  Aspect_XRAnalogActionData()
      : ActiveOrigin(0),
        UpdateTime(0.0f),
        IsActive(false)
  {
  }
};

// Copyright (c) 2020 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <Standard_TypeDef.hpp>

//! Digital input XR action data.
struct Aspect_XRDigitalActionData
{
  uint64_t ActiveOrigin; //!< The origin that caused this action's current state
                         // clang-format off
  float    UpdateTime;   //!< Time relative to now when this event happened. Will be negative to indicate a past time
  bool     IsActive;     //!< whether or not this action is currently available to be bound in the active action set
  bool     IsPressed;    //!< Aspect_InputActionType_Digital state - The current state of this action; will be true if currently pressed
  bool     IsChanged;    //!< Aspect_InputActionType_Digital state - this is true if the state has changed since the last frame
                         // clang-format on

  //! Empty constructor.
  Aspect_XRDigitalActionData()
      : ActiveOrigin(0),
        UpdateTime(0.0f),
        IsActive(false),
        IsPressed(false),
        IsChanged(false)
  {
  }
};

// Copyright (c) 2020 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

//! Generic XR action.
enum Aspect_XRGenericAction
{
  Aspect_XRGenericAction_IsHeadsetOn,           //!< headset is on/off head
  Aspect_XRGenericAction_InputAppMenu,          //!< application menu button pressed/released
  Aspect_XRGenericAction_InputSysMenu,          //!< system menu button pressed/released
  Aspect_XRGenericAction_InputTriggerPull,      //!< trigger squeezing [0..1], 1 to click
  Aspect_XRGenericAction_InputTriggerClick,     //!< trigger clicked/released
  Aspect_XRGenericAction_InputGripClick,        //!< grip state on/off
  Aspect_XRGenericAction_InputTrackPadPosition, //!< trackpad 2D position [-1,+1] with X and Y axes
  Aspect_XRGenericAction_InputTrackPadTouch,    //!< trackpad touched/untouched
  Aspect_XRGenericAction_InputTrackPadClick,    //!< trackpad clicked/released
  Aspect_XRGenericAction_InputThumbstickPosition, //!< thumbstick 2D position [-1,+1] with X and Y
                                                  //!< axes
  Aspect_XRGenericAction_InputThumbstickTouch,    //!< thumbstick touched/untouched
  Aspect_XRGenericAction_InputThumbstickClick,    //!< thumbstick clicked/released
  Aspect_XRGenericAction_InputPoseBase,           //!< base position of hand
  Aspect_XRGenericAction_InputPoseFront,          //!< front position of hand
  Aspect_XRGenericAction_InputPoseHandGrip,       //!< position of main handgrip
  Aspect_XRGenericAction_InputPoseFingerTip,      //!< position of main fingertip
  Aspect_XRGenericAction_OutputHaptic             //!< haptic output (vibration)
};

enum
{
  Aspect_XRGenericAction_NB = Aspect_XRGenericAction_OutputHaptic + 1
};

#include <Aspect_XRHapticActionData.hpp>
// Copyright (c) 2020 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

// Copyright (c) 2020 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <gp_Trsf.hpp>
#include <NCollection_Array1.hpp>

//! Describes a single pose for a tracked object (for XR).
struct Aspect_TrackedDevicePose
{
  gp_Trsf Orientation;       //!< device to absolute transformation
  gp_Vec  Velocity;          //!< velocity in tracker space in m/s
  gp_Vec  AngularVelocity;   //!< angular velocity in radians/s
  bool    IsValidPose;       //!< indicates valid pose
  bool    IsConnectedDevice; //!< indicates connected state

  //! Empty constructor.
  Aspect_TrackedDevicePose()
      : IsValidPose(false),
        IsConnectedDevice(false)
  {
  }
};

//! Array of tracked poses.

#include <Standard_TypeDef.hpp>

//! Pose input XR action data.
struct Aspect_XRPoseActionData
{
  Aspect_TrackedDevicePose Pose;         //!< pose state
  uint64_t                 ActiveOrigin; //!< The origin that caused this action's current state
                                         // clang-format off
  bool                     IsActive;     //!< whether or not this action is currently available to be bound in the active action set
                                         // clang-format on

  //! Empty constructor.
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

//! Extended Reality (XR) Session interface.
class Aspect_XRSession : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Aspect_XRSession, Standard_Transient)
public:
  //! Identifies which style of tracking origin the application wants to use for the poses it is
  //! requesting.
  enum TrackingUniverseOrigin
  {
    TrackingUniverseOrigin_Seated,   //! poses are provided relative to the seated zero pose
    TrackingUniverseOrigin_Standing, //! poses are provided relative to the safe bounds configured
                                     //! by the user
  };

public:
  //! Return TRUE if session is opened.
  virtual bool IsOpen() const = 0;

  //! Initialize session.
  virtual bool Open() = 0;

  //! Release session.
  virtual void Close() = 0;

  //! Fetch actual poses of tracked devices.
  virtual bool WaitPoses() = 0;

  //! Return recommended viewport Width x Height for rendering into VR.
  virtual NCollection_Vec2<int> RecommendedViewport() const = 0;

  //! Return transformation from eye to head.
  virtual NCollection_Mat4<double> EyeToHeadTransform(Aspect_Eye theEye) const = 0;

  //! Return transformation from head to eye.
  NCollection_Mat4<double> HeadToEyeTransform(Aspect_Eye theEye) const
  {
    NCollection_Mat4<double> aMat;
    EyeToHeadTransform(theEye).Inverted(aMat);
    return aMat;
  }

  //! Return projection matrix.
  virtual NCollection_Mat4<double> ProjectionMatrix(Aspect_Eye theEye,
                                                    double     theZNear,
                                                    double     theZFar) const = 0;

  //! Return FALSE if projection frustums are unsupported and general 4x4 projection matrix should
  //! be fetched instead
  virtual bool HasProjectionFrustums() const = 0;

  //! Receive XR events.
  virtual void ProcessEvents() = 0;

  //! Submit texture eye to XR Composer.
  //! @param[in] theTexture      texture handle
  //! @param[in] theGraphicsLib  graphics library in which texture handle is defined
  //! @param[in] theColorSpace   texture color space;
  //!                            sRGB means no color conversion by composer;
  //!                            Linear means to sRGB color conversion by composer
  //! @param[in] theEye  eye to display
  //! @return FALSE on error
  virtual bool SubmitEye(void*                  theTexture,
                         Aspect_GraphicsLibrary theGraphicsLib,
                         Aspect_ColorSpace      theColorSpace,
                         Aspect_Eye             theEye) = 0;

  //! Return unit scale factor defined as scale factor for m (meters); 1.0 by default.
  double UnitFactor() const { return myUnitFactor; }

  //! Set unit scale factor.
  void SetUnitFactor(double theFactor) { myUnitFactor = theFactor; }

  //! Return aspect ratio.
  double Aspect() const { return myAspect; }

  //! Return field of view.
  double FieldOfView() const { return myFieldOfView; }

  //! Return Intra-ocular Distance (IOD); also known as Interpupillary Distance (IPD).
  //! Defined in meters by default (@sa UnitFactor()).
  double IOD() const { return myIod; }

  //! Return display frequency or 0 if unknown.
  float DisplayFrequency() const { return myDispFreq; }

  //! Return projection frustum.
  //! @sa HasProjectionFrustums().
  const Aspect_FrustumLRBT<double>& ProjectionFrustum(Aspect_Eye theEye) const
  {
    return theEye == Aspect_Eye_Right ? myFrustumR : myFrustumL;
  }

  //! Return head orientation in right-handed system:
  //! +y is up
  //! +x is to the right
  //! -z is forward
  //! Distance unit is meters by default (@sa UnitFactor()).
  const gp_Trsf& HeadPose() const { return myHeadPose; }

  //! Return left hand orientation.
  gp_Trsf LeftHandPose() const
  {
    const int aDevice = NamedTrackedDevice(Aspect_XRTrackedDeviceRole_LeftHand);
    return aDevice != -1 ? myTrackedPoses[aDevice].Orientation : gp_Trsf();
  }

  //! Return right hand orientation.
  gp_Trsf RightHandPose() const
  {
    const int aDevice = NamedTrackedDevice(Aspect_XRTrackedDeviceRole_RightHand);
    return aDevice != -1 ? myTrackedPoses[aDevice].Orientation : gp_Trsf();
  }

  //! Return number of tracked poses array.
  const NCollection_Array1<Aspect_TrackedDevicePose>& TrackedPoses() const
  {
    return myTrackedPoses;
  }

  //! Return TRUE if device orientation is defined.
  bool HasTrackedPose(int theDevice) const { return myTrackedPoses[theDevice].IsValidPose; }

  //! Return index of tracked device of known role, or -1 if undefined.
  virtual int NamedTrackedDevice(Aspect_XRTrackedDeviceRole theDevice) const = 0;

  //! Load model for displaying device.
  //! @param[in] theDevice   device index
  //! @param[out] theTexture  texture source
  //! @return model triangulation or NULL if not found
  occ::handle<Graphic3d_ArrayOfTriangles> LoadRenderModel(int                         theDevice,
                                                          occ::handle<Image_Texture>& theTexture)
  {
    return loadRenderModel(theDevice, true, theTexture);
  }

  //! Load model for displaying device.
  //! @param[in] theDevice   device index
  //! @param[in] theToApplyUnitFactor  flag to apply unit scale factor
  //! @param[out] theTexture  texture source
  //! @return model triangulation or NULL if not found
  occ::handle<Graphic3d_ArrayOfTriangles> LoadRenderModel(int  theDevice,
                                                          bool theToApplyUnitFactor,
                                                          occ::handle<Image_Texture>& theTexture)
  {
    return loadRenderModel(theDevice, theToApplyUnitFactor, theTexture);
  }

  //! Fetch data for digital input action (like button).
  //! @param[in] theAction  action of Aspect_XRActionType_InputDigital type
  virtual Aspect_XRDigitalActionData GetDigitalActionData(
    const occ::handle<Aspect_XRAction>& theAction) const = 0;

  //! Fetch data for digital input action (like axis).
  //! @param[in] theAction  action of Aspect_XRActionType_InputAnalog type
  virtual Aspect_XRAnalogActionData GetAnalogActionData(
    const occ::handle<Aspect_XRAction>& theAction) const = 0;

  //! Fetch data for pose input action (like fingertip position).
  //! The returned values will match the values returned by the last call to WaitPoses().
  //! @param[in] theAction  action of Aspect_XRActionType_InputPose type
  virtual Aspect_XRPoseActionData GetPoseActionDataForNextFrame(
    const occ::handle<Aspect_XRAction>& theAction) const = 0;

  //! Trigger vibration.
  Standard_EXPORT void TriggerHapticVibrationAction(const occ::handle<Aspect_XRAction>& theAction,
                                                    const Aspect_XRHapticActionData&    theParams);

  //! Abort vibration.
  Standard_EXPORT void AbortHapticVibrationAction(const occ::handle<Aspect_XRAction>& theAction);

  //! Return tracking origin.
  TrackingUniverseOrigin TrackingOrigin() const { return myTrackOrigin; }

  //! Set tracking origin.
  virtual void SetTrackingOrigin(TrackingUniverseOrigin theOrigin) { myTrackOrigin = theOrigin; }

  //! Return generic action for specific hand or NULL if undefined.
  const occ::handle<Aspect_XRAction>& GenericAction(Aspect_XRTrackedDeviceRole theDevice,
                                                    Aspect_XRGenericAction     theAction) const
  {
    const NCollection_Array1<occ::handle<Aspect_XRAction>>& anActions = myRoleActions[theDevice];
    return anActions[theAction];
  }

public:
  //! Info string enumeration.
  enum InfoString
  {
    InfoString_Vendor,
    InfoString_Device,
    InfoString_Tracker,
    InfoString_SerialNumber,
  };

  //! Query information.
  virtual TCollection_AsciiString GetString(InfoString theInfo) const = 0;

protected:
  //! Empty constructor.
  Standard_EXPORT Aspect_XRSession();

  //! Load model for displaying device.
  //! @param[in] theDevice   device index
  //! @param[in] theToApplyUnitFactor  flag to apply unit scale factor
  //! @param[out] theTexture  texture source
  //! @return model triangulation or NULL if not found
  virtual occ::handle<Graphic3d_ArrayOfTriangles> loadRenderModel(
    int                         theDevice,
    bool                        theToApplyUnitFactor,
    occ::handle<Image_Texture>& theTexture) = 0;

  //! Trigger vibration.
  virtual void triggerHapticVibrationAction(const occ::handle<Aspect_XRAction>& theAction,
                                            const Aspect_XRHapticActionData&    theParams) = 0;

protected:
  NCollection_Array1<occ::handle<Aspect_XRAction>>
    // clang-format off
                                  myRoleActions[Aspect_XRTrackedDeviceRole_NB]; //!< generic actions
  NCollection_IndexedDataMap<TCollection_AsciiString, occ::handle<Aspect_XRActionSet>>           myActionSets;   //!< actions sets
  TrackingUniverseOrigin          myTrackOrigin;  //!< tracking origin
  NCollection_Array1<Aspect_TrackedDevicePose>   myTrackedPoses; //!< array of tracked poses
  gp_Trsf                         myHeadPose;     //!< head orientation
  NCollection_Vec2<int>           myRendSize;     //!< viewport Width x Height for rendering into VR
  Aspect_FrustumLRBT<double>      myFrustumL;     //!< left  eye projection frustum
  Aspect_FrustumLRBT<double>      myFrustumR;     //!< right eye projection frustum
  double                   myUnitFactor;   //!< unit scale factor defined as scale factor for m (meters)
  // clang-format on
  double myAspect;      //!< aspect ratio
  double myFieldOfView; //!< field of view
  double myIod;         //!< intra-ocular distance in meters
  float  myDispFreq;    //!< display frequency
};
