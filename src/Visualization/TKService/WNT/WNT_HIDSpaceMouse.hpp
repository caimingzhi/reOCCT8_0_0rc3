#pragma once

#include <Aspect_VKey.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Vec3.hpp>
#include <NCollection_Vec4.hpp>
#include <NCollection_Mat4.hpp>

class WNT_HIDSpaceMouse
{
public:
  enum
  {
    VENDOR_ID_LOGITECH    = 0x46D,
    VENDOR_ID_3DCONNEXION = 0x256F
  };

  Standard_EXPORT static bool IsKnownProduct(unsigned long theProductId);

public:
  Standard_EXPORT WNT_HIDSpaceMouse(unsigned long  theProductId,
                                    const uint8_t* theData,
                                    size_t         theSize);

  int16_t RawValueRange() const { return myValueRange; }

  void SetRawValueRange(int16_t theRange)
  {
    myValueRange = theRange > myValueRange ? theRange : myValueRange;
  }

  bool IsTranslation() const
  {
    return myData[0] == SpaceRawInput_Translation && (mySize == 7 || mySize == 13);
  }

  Standard_EXPORT NCollection_Vec3<double> Translation(bool& theIsIdle, bool theIsQuadric) const;

  bool IsRotation() const
  {
    return (myData[0] == SpaceRawInput_Rotation && mySize == 7)
           || (myData[0] == SpaceRawInput_Translation && mySize == 13);
  }

  Standard_EXPORT NCollection_Vec3<double> Rotation(bool& theIsIdle, bool theIsQuadric) const;

  bool IsKeyState() const { return myData[0] == SpaceRawInput_KeyState; }

  uint32_t KeyState() const { return *reinterpret_cast<const uint32_t*>(myData + 1); }

  Standard_EXPORT Aspect_VKey HidToSpaceKey(unsigned short theKeyBit) const;

private:
  NCollection_Vec3<double> fromRawVec3(bool&          theIsIdle,
                                       const uint8_t* theData,
                                       bool           theIsTrans,
                                       bool           theIsQuadric) const;

  enum
  {
    SpaceRawInput_Translation = 0x01,
    SpaceRawInput_Rotation    = 0x02,
    SpaceRawInput_KeyState    = 0x03,
  };

private:
  const uint8_t*  myData;
  size_t          mySize;
  unsigned long   myProductId;
  mutable int16_t myValueRange;
};
