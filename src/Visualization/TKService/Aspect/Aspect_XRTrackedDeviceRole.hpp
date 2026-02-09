#pragma once

enum Aspect_XRTrackedDeviceRole
{
  Aspect_XRTrackedDeviceRole_Head,
  Aspect_XRTrackedDeviceRole_LeftHand,
  Aspect_XRTrackedDeviceRole_RightHand,
  Aspect_XRTrackedDeviceRole_Other,
};

enum
{
  Aspect_XRTrackedDeviceRole_NB = Aspect_XRTrackedDeviceRole_Other + 1
};
