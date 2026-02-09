

#include <WNT_HIDSpaceMouse.hpp>

namespace
{

  enum SpacePid
  {

    SpacePid_SpaceMouse            = 0xC603,
    SpacePid_CADMan                = 0xC605,
    SpacePid_SpaceMouseClassic     = 0xC606,
    SpacePid_SpaceBall5000         = 0xC621,
    SpacePid_SpaceTraveler         = 0xC623,
    SpacePid_SpacePilot            = 0xC625,
    SpacePid_SpaceNavigator        = 0xC626,
    SpacePid_SpaceExplorer         = 0xC627,
    SpacePid_NavigatorForNotebooks = 0xC628,
    SpacePid_SpacePilotPro         = 0xC629,
    SpacePid_SpaceMousePro         = 0xC62B,

    SpacePid_SpaceMouseWireless1    = 0xC62E,
    SpacePid_SpaceMouseWireless2    = 0xC62F,
    SpacePid_SpaceMouseProWireless1 = 0xC631,
    SpacePid_SpaceMouseProWireless2 = 0xC632,
    SpacePid_SpaceMouseEnterprise   = 0xC633,
    SpacePid_SpaceMouseCompact      = 0xC635
  };

  enum SpaceVKey
  {
    SpaceVKey_INVALID = 0,
    SpaceVKey_Menu    = 1,
    SpaceVKey_Fit,
    SpaceVKey_Top,
    SpaceVKey_Left,
    SpaceVKey_Right,
    SpaceVKey_Front,
    SpaceVKey_Bottom,
    SpaceVKey_Back,
    SpaceVKey_RollCW,
    SpaceVKey_RollCCW,
    SpaceVKey_ISO1,
    SpaceVKey_ISO2,
    SpaceVKey_1,
    SpaceVKey_2,
    SpaceVKey_3,
    SpaceVKey_4,
    SpaceVKey_5,
    SpaceVKey_6,
    SpaceVKey_7,
    SpaceVKey_8,
    SpaceVKey_9,
    SpaceVKey_10,
    SpaceVKey_Esc,
    SpaceVKey_Alt,
    SpaceVKey_Shift,
    SpaceVKey_Ctrl,
    SpaceVKey_Rotate,
    SpaceVKey_PanZoom,
    SpaceVKey_Dominant,
    SpaceVKey_Plus,
    SpaceVKey_Minus,
  };

  enum
  {
    THE_RAW_RANGE_350 = 350
  };

  static SpaceVKey hidToSpaceKey(unsigned long theProductId, unsigned short theKeyBit)
  {
    static const SpaceVKey THE_PILOT_KEYS[] = {
      SpaceVKey_1,    SpaceVKey_2,    SpaceVKey_3,     SpaceVKey_4,        SpaceVKey_5,
      SpaceVKey_6,    SpaceVKey_Top,  SpaceVKey_Left,  SpaceVKey_Right,    SpaceVKey_Front,
      SpaceVKey_Esc,  SpaceVKey_Alt,  SpaceVKey_Shift, SpaceVKey_Ctrl,     SpaceVKey_Fit,
      SpaceVKey_Menu, SpaceVKey_Plus, SpaceVKey_Minus, SpaceVKey_Dominant, SpaceVKey_Rotate};
    const int THE_NB_PILOT_KEYS = sizeof(THE_PILOT_KEYS) / sizeof(SpaceVKey);

    static const SpaceVKey THE_EXPLORER_KEYS[]  = {SpaceVKey_1,
                                                   SpaceVKey_2,
                                                   SpaceVKey_Top,
                                                   SpaceVKey_Left,
                                                   SpaceVKey_Right,
                                                   SpaceVKey_Front,
                                                   SpaceVKey_Esc,
                                                   SpaceVKey_Alt,
                                                   SpaceVKey_Shift,
                                                   SpaceVKey_Ctrl,
                                                   SpaceVKey_Fit,
                                                   SpaceVKey_Menu,
                                                   SpaceVKey_Plus,
                                                   SpaceVKey_Minus,
                                                   SpaceVKey_Rotate};
    const int              THE_NB_EXPLORER_KEYS = sizeof(THE_EXPLORER_KEYS) / sizeof(SpaceVKey);

    static const SpaceVKey THE_SPACEMOUSEPRO_KEYS[] = {
      SpaceVKey_Menu,  SpaceVKey_Fit,    SpaceVKey_Top,     SpaceVKey_Left,     SpaceVKey_Right,
      SpaceVKey_Front, SpaceVKey_Bottom, SpaceVKey_Back,    SpaceVKey_RollCW,   SpaceVKey_RollCCW,
      SpaceVKey_ISO1,  SpaceVKey_ISO2,   SpaceVKey_1,       SpaceVKey_2,        SpaceVKey_3,
      SpaceVKey_4,     SpaceVKey_5,      SpaceVKey_6,       SpaceVKey_7,        SpaceVKey_8,
      SpaceVKey_9,     SpaceVKey_10,     SpaceVKey_Esc,     SpaceVKey_Alt,      SpaceVKey_Shift,
      SpaceVKey_Ctrl,  SpaceVKey_Rotate, SpaceVKey_PanZoom, SpaceVKey_Dominant, SpaceVKey_Plus,
      SpaceVKey_Minus};
    const int THE_NB_SPACEMOUSEPRO_KEYS = sizeof(THE_SPACEMOUSEPRO_KEYS) / sizeof(SpaceVKey);

    switch (theProductId)
    {
      case SpacePid_SpacePilot:
        return theKeyBit < THE_NB_PILOT_KEYS ? THE_PILOT_KEYS[theKeyBit] : SpaceVKey_INVALID;
      case SpacePid_SpaceExplorer:
        return theKeyBit < THE_NB_EXPLORER_KEYS ? THE_EXPLORER_KEYS[theKeyBit] : SpaceVKey_INVALID;
      case SpacePid_SpaceNavigator:
      case SpacePid_NavigatorForNotebooks:
      case SpacePid_SpacePilotPro:
      case SpacePid_SpaceMousePro:
      case SpacePid_SpaceMouseWireless1:
      case SpacePid_SpaceMouseWireless2:
      case SpacePid_SpaceMouseProWireless1:
      case SpacePid_SpaceMouseProWireless2:
      case SpacePid_SpaceMouseEnterprise:
      case SpacePid_SpaceMouseCompact:
        return theKeyBit < THE_NB_SPACEMOUSEPRO_KEYS ? THE_SPACEMOUSEPRO_KEYS[theKeyBit]
                                                     : SpaceVKey_INVALID;
    }
    return SpaceVKey_INVALID;
  }

} // namespace

WNT_HIDSpaceMouse::WNT_HIDSpaceMouse(unsigned long  theProductId,
                                     const uint8_t* theData,
                                     size_t         theSize)
    : myData(theData),
      mySize(theSize),
      myProductId(theProductId),
      myValueRange(THE_RAW_RANGE_350)
{
}

bool WNT_HIDSpaceMouse::IsKnownProduct(unsigned long theProductId)
{
  switch (theProductId)
  {
    case SpacePid_SpacePilot:
    case SpacePid_SpaceExplorer:
    case SpacePid_SpaceNavigator:
    case SpacePid_NavigatorForNotebooks:
    case SpacePid_SpacePilotPro:
    case SpacePid_SpaceMousePro:
    case SpacePid_SpaceMouseWireless1:
    case SpacePid_SpaceMouseWireless2:
    case SpacePid_SpaceMouseProWireless1:
    case SpacePid_SpaceMouseProWireless2:
    case SpacePid_SpaceMouseEnterprise:
    case SpacePid_SpaceMouseCompact:
      return true;
  }
  return false;
}

NCollection_Vec3<double> WNT_HIDSpaceMouse::Translation(bool& theIsIdle, bool theIsQuadric) const
{
  theIsIdle = true;
  return myData[0] == SpaceRawInput_Translation && (mySize == 7 || mySize == 13)
           ? fromRawVec3(theIsIdle, myData + 1, true, theIsQuadric)
           : NCollection_Vec3<double>();
}

NCollection_Vec3<double> WNT_HIDSpaceMouse::Rotation(bool& theIsIdle, bool theIsQuadric) const
{
  theIsIdle = true;
  if (myData[0] == SpaceRawInput_Rotation && mySize == 7)
  {
    return fromRawVec3(theIsIdle, myData + 1, false, theIsQuadric);
  }
  else if (myData[0] == SpaceRawInput_Translation && mySize == 13)
  {
    return fromRawVec3(theIsIdle, myData + 7, false, theIsQuadric);
  }
  return NCollection_Vec3<double>();
}

NCollection_Vec3<double> WNT_HIDSpaceMouse::fromRawVec3(bool&          theIsIdle,
                                                        const uint8_t* theData,
                                                        bool           theIsTrans,
                                                        bool           theIsQuadric) const
{
  theIsIdle = true;
  const NCollection_Vec3<int16_t>& aRaw16 =
    *reinterpret_cast<const NCollection_Vec3<int16_t>*>(theData);
  NCollection_Vec3<double> aVec(aRaw16.x(), aRaw16.y(), aRaw16.z());
  if (theIsTrans)
  {
    static const int16_t THE_MIN_RAW_TRANS   = 4;
    static const int16_t THE_MIN_RAW_TRANS_Z = 8;
    for (int aCompIter = 0; aCompIter < 3; ++aCompIter)
    {
      if (aRaw16[aCompIter] > -THE_MIN_RAW_TRANS && aRaw16[aCompIter] < THE_MIN_RAW_TRANS)
      {
        aVec[aCompIter] = 0.0;
      }
      else
      {
        theIsIdle = false;
      }
    }
    if (aRaw16.z() > -THE_MIN_RAW_TRANS_Z && aRaw16.z() < THE_MIN_RAW_TRANS_Z)
    {
      aVec.z() = 0.0;
    }
  }
  else
  {
    for (int aCompIter = 0; aCompIter < 3; ++aCompIter)
    {
      if (aRaw16[aCompIter] != 0)
      {
        theIsIdle = false;
        break;
      }
    }
  }

  for (int aCompIter = 0; aCompIter < 3; ++aCompIter)
  {
    if (aRaw16[aCompIter] > myValueRange || -aRaw16[aCompIter] > myValueRange)
    {
      myValueRange = 32767;
      break;
    }
  }

  if (!theIsQuadric)
  {
    return aVec / double(myValueRange);
  }

  for (int aCompIter = 0; aCompIter < 3; ++aCompIter)
  {
    aVec[aCompIter] = aRaw16[aCompIter] > 0 ? aVec[aCompIter] * aVec[aCompIter]
                                            : -aVec[aCompIter] * aVec[aCompIter];
  }
  return aVec / (double(myValueRange) * double(myValueRange));
}

Aspect_VKey WNT_HIDSpaceMouse::HidToSpaceKey(unsigned short theKeyBit) const
{
  const SpaceVKey aKey = hidToSpaceKey(myProductId, theKeyBit);
  switch (aKey)
  {
    case SpaceVKey_1:
    case SpaceVKey_2:
    case SpaceVKey_3:
    case SpaceVKey_4:
    case SpaceVKey_5:
    case SpaceVKey_6:
    case SpaceVKey_7:
    case SpaceVKey_8:
    case SpaceVKey_9:
    case SpaceVKey_10:
      return (int(aKey) - int(SpaceVKey_1)) + Aspect_VKey_1;
    case SpaceVKey_Esc:
      return Aspect_VKey_Escape;
    case SpaceVKey_Shift:
      return Aspect_VKey_Shift;
    case SpaceVKey_Alt:
      return Aspect_VKey_Alt;
    case SpaceVKey_Ctrl:
      return Aspect_VKey_Control;
    case SpaceVKey_Top:
      return Aspect_VKey_ViewTop;
    case SpaceVKey_Bottom:
      return Aspect_VKey_ViewBottom;
    case SpaceVKey_Left:
      return Aspect_VKey_ViewLeft;
    case SpaceVKey_Right:
      return Aspect_VKey_ViewRight;
    case SpaceVKey_Front:
      return Aspect_VKey_ViewFront;
    case SpaceVKey_Back:
      return Aspect_VKey_ViewBack;
    case SpaceVKey_ISO1:
      return Aspect_VKey_ViewAxoLeftProj;
    case SpaceVKey_ISO2:
      return Aspect_VKey_ViewAxoRightProj;
    case SpaceVKey_Fit:
      return Aspect_VKey_ViewFitAll;
    case SpaceVKey_RollCW:
      return Aspect_VKey_ViewRoll90CW;
    case SpaceVKey_RollCCW:
      return Aspect_VKey_ViewRoll90CCW;
    case SpaceVKey_Rotate:
      return Aspect_VKey_ViewSwitchRotate;
    default:
      break;
  }
  return Aspect_VKey_UNKNOWN;
}
