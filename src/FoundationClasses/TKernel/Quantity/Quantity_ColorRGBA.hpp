#pragma once

#include <Quantity_Color.hpp>
#include <Standard_Assert.hpp>

class Quantity_ColorRGBA
{
public:
  Quantity_ColorRGBA()
      : myAlpha(1.0f)
  {
  }

  constexpr explicit Quantity_ColorRGBA(const Quantity_Color& theRgb)
      : myRgb(theRgb),
        myAlpha(1.0f)
  {
  }

  constexpr Quantity_ColorRGBA(const Quantity_Color& theRgb, float theAlpha)
      : myRgb(theRgb),
        myAlpha(theAlpha)
  {
  }

  explicit Quantity_ColorRGBA(const NCollection_Vec4<float>& theRgba)
      : myRgb(theRgba.rgb()),
        myAlpha(theRgba.a())
  {
  }

  Quantity_ColorRGBA(float theRed, float theGreen, float theBlue, float theAlpha)
      : myRgb(theRed, theGreen, theBlue, Quantity_TOC_RGB),
        myAlpha(theAlpha)
  {
  }

  void SetValues(float theRed, float theGreen, float theBlue, float theAlpha) noexcept
  {
    myRgb.SetValues(theRed, theGreen, theBlue, Quantity_TOC_RGB);
    myAlpha = theAlpha;
  }

  constexpr const Quantity_Color& GetRGB() const noexcept { return myRgb; }

  constexpr Quantity_Color& ChangeRGB() noexcept { return myRgb; }

  constexpr void SetRGB(const Quantity_Color& theRgb) noexcept { myRgb = theRgb; }

  constexpr float Alpha() const noexcept { return myAlpha; }

  constexpr void SetAlpha(const float theAlpha) noexcept { myAlpha = theAlpha; }

  operator const NCollection_Vec4<float>&() const noexcept
  {
    return *reinterpret_cast<const NCollection_Vec4<float>*>(this);
  }

  bool IsDifferent(const Quantity_ColorRGBA& theOther) const noexcept
  {
    return myRgb.IsDifferent(theOther.GetRGB())
           || std::abs(myAlpha - theOther.myAlpha) > (float)Quantity_Color::Epsilon();
  }

  bool operator!=(const Quantity_ColorRGBA& theOther) const noexcept
  {
    return IsDifferent(theOther);
  }

  bool IsEqual(const Quantity_ColorRGBA& theOther) const noexcept
  {
    return myRgb.IsEqual(theOther.GetRGB())
           && std::abs(myAlpha - theOther.myAlpha) <= (float)Quantity_Color::Epsilon();
  }

  bool operator==(const Quantity_ColorRGBA& theOther) const noexcept { return IsEqual(theOther); }

public:
  static bool ColorFromName(const char* theColorNameString, Quantity_ColorRGBA& theColor) noexcept
  {
    Quantity_ColorRGBA aColor;
    if (!Quantity_Color::ColorFromName(theColorNameString, aColor.ChangeRGB()))
    {
      return false;
    }
    theColor = aColor;
    return true;
  }

  Standard_EXPORT static bool ColorFromHex(const char* const   theHexColorString,
                                           Quantity_ColorRGBA& theColor,
                                           const bool          theAlphaComponentIsOff = false);

  static TCollection_AsciiString ColorToHex(const Quantity_ColorRGBA& theColor,
                                            const bool theToPrefixHash = true) noexcept
  {
    NCollection_Vec4<float> anSRgb = Convert_LinearRGB_To_sRGB((NCollection_Vec4<float>)theColor);
    NCollection_Vec4<int>   anSRgbInt(anSRgb * 255.0f + NCollection_Vec4<float>(0.5f));
    char                    aBuff[12];
    Sprintf(aBuff,
            theToPrefixHash ? "#%02X%02X%02X%02X" : "%02X%02X%02X%02X",
            anSRgbInt.r(),
            anSRgbInt.g(),
            anSRgbInt.b(),
            anSRgbInt.a());
    return aBuff;
  }

public:
  static NCollection_Vec4<float> Convert_LinearRGB_To_sRGB(
    const NCollection_Vec4<float>& theRGB) noexcept
  {
    return NCollection_Vec4<float>(Quantity_Color::Convert_LinearRGB_To_sRGB(theRGB.r()),
                                   Quantity_Color::Convert_LinearRGB_To_sRGB(theRGB.g()),
                                   Quantity_Color::Convert_LinearRGB_To_sRGB(theRGB.b()),
                                   theRGB.a());
  }

  static NCollection_Vec4<float> Convert_sRGB_To_LinearRGB(
    const NCollection_Vec4<float>& theRGB) noexcept
  {
    return NCollection_Vec4<float>(Quantity_Color::Convert_sRGB_To_LinearRGB(theRGB.r()),
                                   Quantity_Color::Convert_sRGB_To_LinearRGB(theRGB.g()),
                                   Quantity_Color::Convert_sRGB_To_LinearRGB(theRGB.b()),
                                   theRGB.a());
  }

public:
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT bool InitFromJson(const Standard_SStream& theSStream, int& theStreamPos);

private:
  static void myTestSize3() { Standard_STATIC_ASSERT(sizeof(float) * 3 == sizeof(Quantity_Color)); }

  static void myTestSize4()
  {
    Standard_STATIC_ASSERT(sizeof(float) * 4 == sizeof(Quantity_ColorRGBA));
  }

private:
  Quantity_Color myRgb;
  float          myAlpha;
};

namespace std
{
  template <>
  struct hash<Quantity_ColorRGBA>
  {
    std::size_t operator()(const Quantity_ColorRGBA& theColor) const noexcept
    {
      const Quantity_Color& anRGB       = theColor.GetRGB();
      unsigned char         aByteArr[4] = {static_cast<unsigned char>(100 * theColor.Alpha()),
                                           static_cast<unsigned char>(255 * anRGB.Red()),
                                           static_cast<unsigned char>(255 * anRGB.Green()),
                                           static_cast<unsigned char>(255 * anRGB.Blue())};
      return opencascade::hashBytes(aByteArr, sizeof(aByteArr));
    }
  };
} // namespace std
