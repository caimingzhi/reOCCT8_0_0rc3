#pragma once

#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_CString.hpp>

#include <Standard_Type.hpp>

struct Standard_UUID
{
  uint32_t Data1;
  uint16_t Data2;
  uint16_t Data3;
  uint8_t  Data4[8];
};

#include <Standard_PCharacter.hpp>
#include <Standard_PExtCharacter.hpp>
#include <Standard_OStream.hpp>

#define Standard_GUID_SIZE 36
#define Standard_GUID_SIZE_ALLOC Standard_GUID_SIZE + 1

class Standard_GUID
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr Standard_GUID() noexcept
      : my32b(0),
        my16b1(0),
        my16b2(0),
        my16b3(0),
        my8b1(0),
        my8b2(0),
        my8b3(0),
        my8b4(0),
        my8b5(0),
        my8b6(0)
  {
  }

  Standard_EXPORT Standard_GUID(const char* aGuid);

  Standard_EXPORT Standard_GUID(const char16_t* aGuid);

  constexpr Standard_GUID(const int      a32b,
                          const char16_t a16b1,
                          const char16_t a16b2,
                          const char16_t a16b3,
                          const uint8_t  a8b1,
                          const uint8_t  a8b2,
                          const uint8_t  a8b3,
                          const uint8_t  a8b4,
                          const uint8_t  a8b5,
                          const uint8_t  a8b6) noexcept
      : my32b(a32b),
        my16b1(a16b1),
        my16b2(a16b2),
        my16b3(a16b3),
        my8b1(a8b1),
        my8b2(a8b2),
        my8b3(a8b3),
        my8b4(a8b4),
        my8b5(a8b5),
        my8b6(a8b6)
  {
  }

  constexpr Standard_GUID(const Standard_UUID& theUUID) noexcept
      : my32b(theUUID.Data1),
        my16b1(theUUID.Data2),
        my16b2(theUUID.Data3),
        my16b3(static_cast<char16_t>((theUUID.Data4[0] << 8) | theUUID.Data4[1])),
        my8b1(theUUID.Data4[2]),
        my8b2(theUUID.Data4[3]),
        my8b3(theUUID.Data4[4]),
        my8b4(theUUID.Data4[5]),
        my8b5(theUUID.Data4[6]),
        my8b6(theUUID.Data4[7])
  {
  }

  constexpr Standard_GUID(const Standard_GUID& theGuid) noexcept = default;

  Standard_EXPORT void ToCString(const Standard_PCharacter aStrGuid) const;

  Standard_EXPORT void ToExtString(const Standard_PExtCharacter aStrGuid) const;

  constexpr Standard_UUID ToUUID() const noexcept
  {
    return Standard_UUID{static_cast<uint32_t>(my32b),
                         static_cast<uint16_t>(my16b1),
                         static_cast<uint16_t>(my16b2),
                         {static_cast<uint8_t>((my16b3 >> 8) & 0xFF),
                          static_cast<uint8_t>(my16b3 & 0xFF),
                          my8b1,
                          my8b2,
                          my8b3,
                          my8b4,
                          my8b5,
                          my8b6}};
  }

  constexpr bool IsSame(const Standard_GUID& uid) const noexcept
  {
    return my32b == uid.my32b && my16b1 == uid.my16b1 && my16b2 == uid.my16b2
           && my16b3 == uid.my16b3 && my8b1 == uid.my8b1 && my8b2 == uid.my8b2 && my8b3 == uid.my8b3
           && my8b4 == uid.my8b4 && my8b5 == uid.my8b5 && my8b6 == uid.my8b6;
  }

  constexpr bool operator==(const Standard_GUID& uid) const noexcept { return IsSame(uid); }

  constexpr bool IsNotSame(const Standard_GUID& uid) const noexcept { return !IsSame(uid); }

  constexpr bool operator!=(const Standard_GUID& uid) const noexcept { return IsNotSame(uid); }

  constexpr void Assign(const Standard_GUID& uid) noexcept
  {
    my32b  = uid.my32b;
    my16b1 = uid.my16b1;
    my16b2 = uid.my16b2;
    my16b3 = uid.my16b3;
    my8b1  = uid.my8b1;
    my8b2  = uid.my8b2;
    my8b3  = uid.my8b3;
    my8b4  = uid.my8b4;
    my8b5  = uid.my8b5;
    my8b6  = uid.my8b6;
  }

  constexpr Standard_GUID& operator=(const Standard_GUID& uid) noexcept
  {
    Assign(uid);
    return *this;
  }

  constexpr void Assign(const Standard_UUID& uid) noexcept
  {
    my32b  = uid.Data1;
    my16b1 = uid.Data2;
    my16b2 = uid.Data3;
    my16b3 = static_cast<char16_t>((uid.Data4[0] << 8) | uid.Data4[1]);
    my8b1  = uid.Data4[2];
    my8b2  = uid.Data4[3];
    my8b3  = uid.Data4[4];
    my8b4  = uid.Data4[5];
    my8b5  = uid.Data4[6];
    my8b6  = uid.Data4[7];
  }

  constexpr Standard_GUID& operator=(const Standard_UUID& uid) noexcept
  {
    Assign(uid);
    return *this;
  }

  Standard_EXPORT void ShallowDump(Standard_OStream& aStream) const;

  Standard_EXPORT static bool CheckGUIDFormat(const char* aGuid);

  template <class T>
  friend struct std::hash;

private:
  int      my32b;
  char16_t my16b1;
  char16_t my16b2;
  char16_t my16b3;
  uint8_t  my8b1;
  uint8_t  my8b2;
  uint8_t  my8b3;
  uint8_t  my8b4;
  uint8_t  my8b5;
  uint8_t  my8b6;
};

namespace std
{
  template <>
  struct hash<Standard_GUID>
  {
    size_t operator()(const Standard_GUID& theGUID) const noexcept
    {
      struct GUID
      {
        int      my32b;
        char16_t my16b1;
        char16_t my16b2;
        char16_t my16b3;
        uint8_t  my8b1;
        uint8_t  my8b2;
        uint8_t  my8b3;
        uint8_t  my8b4;
        uint8_t  my8b5;
        uint8_t  my8b6;
      };

      GUID aGUID{theGUID.my32b,
                 theGUID.my16b1,
                 theGUID.my16b2,
                 theGUID.my16b3,
                 theGUID.my8b1,
                 theGUID.my8b2,
                 theGUID.my8b3,
                 theGUID.my8b4,
                 theGUID.my8b5,
                 theGUID.my8b6};
      return opencascade::hashBytes(&aGUID, sizeof(GUID));
    }
  };
} // namespace std
