#pragma once


//! Predefined tracked devices.
enum Aspect_XRTrackedDeviceRole
{
  Aspect_XRTrackedDeviceRole_Head,      //!< head
  Aspect_XRTrackedDeviceRole_LeftHand,  //!< left hand
  Aspect_XRTrackedDeviceRole_RightHand, //!< right hand
  Aspect_XRTrackedDeviceRole_Other,     //!< other devices
};

enum
{
  Aspect_XRTrackedDeviceRole_NB = Aspect_XRTrackedDeviceRole_Other + 1
};

