#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_HashUtils.hpp>
#include <Standard_ShortReal.hpp>

#include <Quantity_NameOfColor.hpp>
#include <Quantity_TypeOfColor.hpp>
#include <NCollection_Vec4.hpp>

class Quantity_Color
{
public:
  DEFINE_STANDARD_ALLOC

  Quantity_Color()
      : myRgb(valuesOf(Quantity_NOC_YELLOW, Quantity_TOC_RGB))
  {
  }

  Quantity_Color(const Quantity_NameOfColor theName)
      : myRgb(valuesOf(theName, Quantity_TOC_RGB))
  {
  }

  Standard_EXPORT Quantity_Color(const double               theC1,
                                 const double               theC2,
                                 const double               theC3,
                                 const Quantity_TypeOfColor theType);

  Standard_EXPORT explicit Quantity_Color(const NCollection_Vec3<float>& theRgb);

  Standard_EXPORT Quantity_NameOfColor Name() const;

  void SetValues(const Quantity_NameOfColor theName) noexcept
  {
    myRgb = valuesOf(theName, Quantity_TOC_RGB);
  }

  constexpr const NCollection_Vec3<float>& Rgb() const noexcept { return myRgb; }

  constexpr operator const NCollection_Vec3<float>&() const noexcept { return myRgb; }

  Standard_EXPORT void Values(double&                    theC1,
                              double&                    theC2,
                              double&                    theC3,
                              const Quantity_TypeOfColor theType) const;

  Standard_EXPORT void SetValues(const double               theC1,
                                 const double               theC2,
                                 const double               theC3,
                                 const Quantity_TypeOfColor theType);

  constexpr double Red() const noexcept { return myRgb.r(); }

  constexpr double Green() const noexcept { return myRgb.g(); }

  constexpr double Blue() const noexcept { return myRgb.b(); }

  double Hue() const noexcept { return Convert_LinearRGB_To_HLS(myRgb)[0]; }

  double Light() const noexcept { return Convert_LinearRGB_To_HLS(myRgb)[1]; }

  Standard_EXPORT void ChangeIntensity(const double theDelta);

  double Saturation() const noexcept { return Convert_LinearRGB_To_HLS(myRgb)[2]; }

  Standard_EXPORT void ChangeContrast(const double theDelta);

  bool IsDifferent(const Quantity_Color& theOther) const noexcept
  {
    return (SquareDistance(theOther) > Epsilon() * Epsilon());
  }

  bool operator!=(const Quantity_Color& theOther) const noexcept { return IsDifferent(theOther); }

  bool IsEqual(const Quantity_Color& theOther) const noexcept
  {
    return (SquareDistance(theOther) <= Epsilon() * Epsilon());
  }

  bool operator==(const Quantity_Color& theOther) const noexcept { return IsEqual(theOther); }

  double Distance(const Quantity_Color& theColor) const noexcept
  {
    return (NCollection_Vec3<double>(myRgb) - NCollection_Vec3<double>(theColor.myRgb)).Modulus();
  }

  double SquareDistance(const Quantity_Color& theColor) const noexcept
  {
    return (NCollection_Vec3<double>(myRgb) - NCollection_Vec3<double>(theColor.myRgb))
      .SquareModulus();
  }

  Standard_EXPORT void Delta(const Quantity_Color& theColor, double& DC, double& DI) const;

  Standard_EXPORT double DeltaE2000(const Quantity_Color& theOther) const;

public:
  static Quantity_NameOfColor Name(const double theR, const double theG, const double theB)
  {
    const Quantity_Color aColor(theR, theG, theB, Quantity_TOC_RGB);
    return aColor.Name();
  }

  Standard_EXPORT static const char* StringName(const Quantity_NameOfColor theColor) noexcept;

  Standard_EXPORT static bool ColorFromName(const char*           theName,
                                            Quantity_NameOfColor& theColor) noexcept;

  static bool ColorFromName(const char* theColorNameString, Quantity_Color& theColor) noexcept
  {
    Quantity_NameOfColor aColorName = Quantity_NOC_BLACK;
    if (!ColorFromName(theColorNameString, aColorName))
    {
      return false;
    }
    theColor = aColorName;
    return true;
  }

public:
  Standard_EXPORT static bool ColorFromHex(const char* theHexColorString, Quantity_Color& theColor);

  static TCollection_AsciiString ColorToHex(const Quantity_Color& theColor,
                                            const bool            theToPrefixHash = true) noexcept
  {
    NCollection_Vec3<float> anSRgb = Convert_LinearRGB_To_sRGB((NCollection_Vec3<float>)theColor);
    NCollection_Vec3<int>   anSRgbInt(anSRgb * 255.0f + NCollection_Vec3<float>(0.5f));
    char                    aBuff[10];
    Sprintf(aBuff,
            theToPrefixHash ? "#%02X%02X%02X" : "%02X%02X%02X",
            anSRgbInt.r(),
            anSRgbInt.g(),
            anSRgbInt.b());
    return aBuff;
  }

  Standard_EXPORT static NCollection_Vec3<float> Convert_sRGB_To_HLS(
    const NCollection_Vec3<float>& theRgb) noexcept;

  Standard_EXPORT static NCollection_Vec3<float> Convert_HLS_To_sRGB(
    const NCollection_Vec3<float>& theHls);

  static NCollection_Vec3<float> Convert_LinearRGB_To_HLS(
    const NCollection_Vec3<float>& theRgb) noexcept
  {
    return Convert_sRGB_To_HLS(Convert_LinearRGB_To_sRGB(theRgb));
  }

  static NCollection_Vec3<float> Convert_HLS_To_LinearRGB(
    const NCollection_Vec3<float>& theHls) noexcept
  {
    return Convert_sRGB_To_LinearRGB(Convert_HLS_To_sRGB(theHls));
  }

  Standard_EXPORT static NCollection_Vec3<float> Convert_LinearRGB_To_Lab(
    const NCollection_Vec3<float>& theRgb) noexcept;

  Standard_EXPORT static NCollection_Vec3<float> Convert_Lab_To_Lch(
    const NCollection_Vec3<float>& theLab) noexcept;

  Standard_EXPORT static NCollection_Vec3<float> Convert_Lab_To_LinearRGB(
    const NCollection_Vec3<float>& theLab) noexcept;

  Standard_EXPORT static NCollection_Vec3<float> Convert_Lch_To_Lab(
    const NCollection_Vec3<float>& theLch) noexcept;

  static constexpr void Color2argb(const Quantity_Color& theColor, int& theARGB) noexcept
  {
    const NCollection_Vec3<int> aColor(static_cast<int>(255.0f * theColor.myRgb.r() + 0.5f),
                                       static_cast<int>(255.0f * theColor.myRgb.g() + 0.5f),
                                       static_cast<int>(255.0f * theColor.myRgb.b() + 0.5f));
    theARGB = (((aColor.r() & 0xff) << 16) | ((aColor.g() & 0xff) << 8) | (aColor.b() & 0xff));
  }

  static void Argb2color(const int theARGB, Quantity_Color& theColor) noexcept
  {
    const NCollection_Vec3<double> aColor(static_cast<double>((theARGB & 0xff0000) >> 16),
                                          static_cast<double>((theARGB & 0x00ff00) >> 8),
                                          static_cast<double>((theARGB & 0x0000ff)));
    theColor.SetValues(aColor.r() / 255.0,
                       aColor.g() / 255.0,
                       aColor.b() / 255.0,
                       Quantity_TOC_sRGB);
  }

  static double Convert_LinearRGB_To_sRGB(double theLinearValue) noexcept
  {
    return theLinearValue <= 0.0031308 ? theLinearValue * 12.92
                                       : std::pow(theLinearValue, 1.0 / 2.4) * 1.055 - 0.055;
  }

  static float Convert_LinearRGB_To_sRGB(float theLinearValue) noexcept
  {
    return theLinearValue <= 0.0031308f ? theLinearValue * 12.92f
                                        : powf(theLinearValue, 1.0f / 2.4f) * 1.055f - 0.055f;
  }

  static double Convert_sRGB_To_LinearRGB(double thesRGBValue) noexcept
  {
    return thesRGBValue <= 0.04045 ? thesRGBValue / 12.92
                                   : std::pow((thesRGBValue + 0.055) / 1.055, 2.4);
  }

  static float Convert_sRGB_To_LinearRGB(float thesRGBValue) noexcept
  {
    return thesRGBValue <= 0.04045f ? thesRGBValue / 12.92f
                                    : powf((thesRGBValue + 0.055f) / 1.055f, 2.4f);
  }

  template <typename T>
  static NCollection_Vec3<T> Convert_LinearRGB_To_sRGB(const NCollection_Vec3<T>& theRGB) noexcept
  {
    return NCollection_Vec3<T>(Convert_LinearRGB_To_sRGB(theRGB.r()),
                               Convert_LinearRGB_To_sRGB(theRGB.g()),
                               Convert_LinearRGB_To_sRGB(theRGB.b()));
  }

  template <typename T>
  static NCollection_Vec3<T> Convert_sRGB_To_LinearRGB(const NCollection_Vec3<T>& theRGB) noexcept
  {
    return NCollection_Vec3<T>(Convert_sRGB_To_LinearRGB(theRGB.r()),
                               Convert_sRGB_To_LinearRGB(theRGB.g()),
                               Convert_sRGB_To_LinearRGB(theRGB.b()));
  }

  static float Convert_LinearRGB_To_sRGB_approx22(float theLinearValue) noexcept
  {
    return powf(theLinearValue, 2.2f);
  }

  static float Convert_sRGB_To_LinearRGB_approx22(float thesRGBValue) noexcept
  {
    return powf(thesRGBValue, 1.0f / 2.2f);
  }

  static NCollection_Vec3<float> Convert_LinearRGB_To_sRGB_approx22(
    const NCollection_Vec3<float>& theRGB) noexcept
  {
    return NCollection_Vec3<float>(Convert_LinearRGB_To_sRGB_approx22(theRGB.r()),
                                   Convert_LinearRGB_To_sRGB_approx22(theRGB.g()),
                                   Convert_LinearRGB_To_sRGB_approx22(theRGB.b()));
  }

  static NCollection_Vec3<float> Convert_sRGB_To_LinearRGB_approx22(
    const NCollection_Vec3<float>& theRGB) noexcept
  {
    return NCollection_Vec3<float>(Convert_sRGB_To_LinearRGB_approx22(theRGB.r()),
                                   Convert_sRGB_To_LinearRGB_approx22(theRGB.g()),
                                   Convert_sRGB_To_LinearRGB_approx22(theRGB.b()));
  }

  static void HlsRgb(const double theH,
                     const double theL,
                     const double theS,
                     double&      theR,
                     double&      theG,
                     double&      theB) noexcept
  {
    const NCollection_Vec3<float> anRgb =
      Convert_HLS_To_sRGB(NCollection_Vec3<float>((float)theH, (float)theL, (float)theS));
    theR = anRgb[0];
    theG = anRgb[1];
    theB = anRgb[2];
  }

  static void RgbHls(const double theR,
                     const double theG,
                     const double theB,
                     double&      theH,
                     double&      theL,
                     double&      theS) noexcept
  {
    const NCollection_Vec3<float> aHls =
      Convert_sRGB_To_HLS(NCollection_Vec3<float>((float)theR, (float)theG, (float)theB));
    theH = aHls[0];
    theL = aHls[1];
    theS = aHls[2];
  }

public:
  Standard_EXPORT static double Epsilon() noexcept;

  Standard_EXPORT static void SetEpsilon(const double theEpsilon) noexcept;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT bool InitFromJson(const Standard_SStream& theSStream, int& theStreamPos);

private:
  Standard_EXPORT static NCollection_Vec3<float> valuesOf(const Quantity_NameOfColor theName,
                                                          const Quantity_TypeOfColor theType);

private:
  NCollection_Vec3<float> myRgb;
};

namespace std
{
  template <>
  struct hash<Quantity_Color>
  {
    std::size_t operator()(const Quantity_Color& theColor) const noexcept
    {
      unsigned char aByteArr[3] = {static_cast<unsigned char>(255 * theColor.Red()),
                                   static_cast<unsigned char>(255 * theColor.Green()),
                                   static_cast<unsigned char>(255 * theColor.Blue())};
      return opencascade::hashBytes(aByteArr, sizeof(aByteArr));
    }
  };
} // namespace std
