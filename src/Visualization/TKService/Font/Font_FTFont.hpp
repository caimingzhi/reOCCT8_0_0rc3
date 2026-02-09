#pragma once

#include <Font_FontAspect.hpp>
#include <Font_Hinting.hpp>
#include <Font_Rect.hpp>
#include <Font_StrictLevel.hpp>
#include <Font_UnicodeSubset.hpp>
#include <Graphic3d_HorizontalTextAlignment.hpp>
#include <Graphic3d_VerticalTextAlignment.hpp>
#include <Image_PixMap.hpp>
#include <NCollection_String.hpp>
#include <TCollection_AsciiString.hpp>

typedef struct FT_FaceRec_* FT_Face;
typedef struct FT_Vector_   FT_Vector;
typedef struct FT_Outline_  FT_Outline;
class Font_FTLibrary;

struct Font_FTFontParams
{
  unsigned int PointSize;

  unsigned int Resolution;
  Font_Hinting FontHinting;

  bool ToSynthesizeItalic;

  bool IsSingleStrokeFont;

  Font_FTFontParams()
      : PointSize(0),
        Resolution(72u),
        FontHinting(Font_Hinting_Off),
        ToSynthesizeItalic(false),
        IsSingleStrokeFont(false)
  {
  }

  Font_FTFontParams(unsigned int thePointSize, unsigned int theResolution)
      : PointSize(thePointSize),
        Resolution(theResolution),
        FontHinting(Font_Hinting_Off),
        ToSynthesizeItalic(false),
        IsSingleStrokeFont(false)
  {
  }
};

class Font_FTFont : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Font_FTFont, Standard_Transient)
public:
  Standard_EXPORT static occ::handle<Font_FTFont> FindAndCreate(
    const TCollection_AsciiString& theFontName,
    const Font_FontAspect          theFontAspect,
    const Font_FTFontParams&       theParams,
    const Font_StrictLevel         theStrictLevel = Font_StrictLevel_Any);

  static bool IsCharFromCJK(char32_t theUChar)
  {
    return (theUChar >= 0x03400 && theUChar <= 0x04DFF)
           || (theUChar >= 0x04E00 && theUChar <= 0x09FFF)
           || (theUChar >= 0x0F900 && theUChar <= 0x0FAFF)
           || (theUChar >= 0x20000 && theUChar <= 0x2A6DF)
           || (theUChar >= 0x2F800 && theUChar <= 0x2FA1F)

           || IsCharFromHiragana(theUChar) || IsCharFromKatakana(theUChar);
  }

  static bool IsCharFromHiragana(char32_t theUChar)
  {
    return (theUChar >= 0x03040 && theUChar <= 0x0309F);
  }

  static bool IsCharFromKatakana(char32_t theUChar)
  {
    return (theUChar >= 0x030A0 && theUChar <= 0x030FF);
  }

  static bool IsCharFromKorean(char32_t theUChar)
  {
    return (theUChar >= 0x01100 && theUChar <= 0x011FF)
           || (theUChar >= 0x03130 && theUChar <= 0x0318F)
           || (theUChar >= 0x0AC00 && theUChar <= 0x0D7A3);
  }

  static bool IsCharFromArabic(char32_t theUChar)
  {
    return (theUChar >= 0x00600 && theUChar <= 0x006FF);
  }

  static bool IsCharRightToLeft(char32_t theUChar) { return IsCharFromArabic(theUChar); }

  static Font_UnicodeSubset CharSubset(char32_t theUChar)
  {
    if (IsCharFromCJK(theUChar))
    {
      return Font_UnicodeSubset_CJK;
    }
    else if (IsCharFromKorean(theUChar))
    {
      return Font_UnicodeSubset_Korean;
    }
    else if (IsCharFromArabic(theUChar))
    {
      return Font_UnicodeSubset_Arabic;
    }
    return Font_UnicodeSubset_Western;
  }

public:
  Standard_EXPORT Font_FTFont(
    const occ::handle<Font_FTLibrary>& theFTLib = occ::handle<Font_FTLibrary>());

  Standard_EXPORT ~Font_FTFont() override;

  inline bool IsValid() const { return myFTFace != nullptr; }

  inline const Image_PixMap& GlyphImage() const { return myGlyphImg; }

  bool Init(const TCollection_AsciiString& theFontPath,
            const Font_FTFontParams&       theParams,
            const int                      theFaceId = 0)
  {
    return Init(occ::handle<NCollection_Buffer>(), theFontPath, theParams, theFaceId);
  }

  Standard_EXPORT bool Init(const occ::handle<NCollection_Buffer>& theData,
                            const TCollection_AsciiString&         theFileName,
                            const Font_FTFontParams&               theParams,
                            const int                              theFaceId = 0);

  Standard_EXPORT bool FindAndInit(const TCollection_AsciiString& theFontName,
                                   Font_FontAspect                theFontAspect,
                                   const Font_FTFontParams&       theParams,
                                   Font_StrictLevel theStrictLevel = Font_StrictLevel_Any);

  bool ToUseUnicodeSubsetFallback() const { return myToUseUnicodeSubsetFallback; }

  void SetUseUnicodeSubsetFallback(bool theToFallback)
  {
    myToUseUnicodeSubsetFallback = theToFallback;
  }

  bool IsSingleStrokeFont() const { return myFontParams.IsSingleStrokeFont; }

  void SetSingleStrokeFont(bool theIsSingleLine)
  {
    myFontParams.IsSingleStrokeFont = theIsSingleLine;
  }

  bool ToSynthesizeItalic() const { return myFontParams.ToSynthesizeItalic; }

  Standard_EXPORT virtual void Release();

  Standard_EXPORT bool RenderGlyph(const char32_t theChar);

  Standard_EXPORT unsigned int GlyphMaxSizeX(bool theToIncludeFallback = false) const;

  Standard_EXPORT unsigned int GlyphMaxSizeY(bool theToIncludeFallback = false) const;

  Standard_EXPORT float Ascender() const;

  Standard_EXPORT float Descender() const;

  Standard_EXPORT float LineSpacing() const;

  unsigned int PointSize() const { return myFontParams.PointSize; }

  float WidthScaling() const { return myWidthScaling; }

  void SetWidthScaling(const float theScaleFactor) { myWidthScaling = theScaleFactor; }

  Standard_EXPORT bool HasSymbol(char32_t theUChar) const;

  Standard_EXPORT float AdvanceX(char32_t theUCharNext) const;

  Standard_EXPORT float AdvanceX(char32_t theUChar, char32_t theUCharNext);

  Standard_EXPORT float AdvanceY(char32_t theUCharNext) const;

  Standard_EXPORT float AdvanceY(char32_t theUChar, char32_t theUCharNext);

  Standard_EXPORT int GlyphsNumber(bool theToIncludeFallback = false) const;

  Standard_EXPORT void GlyphRect(Font_Rect& theRect) const;

  Standard_EXPORT Font_Rect BoundingBox(const NCollection_String&               theString,
                                        const Graphic3d_HorizontalTextAlignment theAlignX,
                                        const Graphic3d_VerticalTextAlignment   theAlignY);

public:
  Standard_EXPORT const FT_Outline* renderGlyphOutline(const char32_t theChar);

public:
  Standard_DEPRECATED("Deprecated method, Font_FTFontParams should be used for passing "
                      "parameters")

  bool Init(const NCollection_String& theFontPath,
            unsigned int              thePointSize,
            unsigned int              theResolution)
  {
    Font_FTFontParams aParams;
    aParams.PointSize  = thePointSize;
    aParams.Resolution = theResolution;
    return Init(theFontPath.ToCString(), aParams, 0);
  }

  Standard_DEPRECATED("Deprecated method, Font_FTFontParams should be used for passing "
                      "parameters")

  bool Init(const NCollection_String& theFontName,
            Font_FontAspect           theFontAspect,
            unsigned int              thePointSize,
            unsigned int              theResolution)
  {
    Font_FTFontParams aParams;
    aParams.PointSize  = thePointSize;
    aParams.Resolution = theResolution;
    return FindAndInit(theFontName.ToCString(), theFontAspect, aParams);
  }

protected:
  template <typename theInput_t>
  int32_t toFTPoints(const theInput_t thePointSize) const
  {
    return (int32_t)thePointSize * 64;
  }

  template <typename theReturn_t, typename theFTUnits_t>
  inline theReturn_t fromFTPoints(const theFTUnits_t theFTUnits) const
  {
    return (theReturn_t)theFTUnits / 64.0f;
  }

protected:
  Standard_EXPORT bool loadGlyph(const char32_t theUChar);

  Standard_EXPORT bool getKerning(FT_Vector& theKern,
                                  char32_t   theUCharCurr,
                                  char32_t   theUCharNext) const;

  Standard_EXPORT bool findAndInitFallback(Font_UnicodeSubset theSubset);

  void setLoadFlag(int32_t theFlag, bool theToEnable)
  {
    if (theToEnable)
    {
      myLoadFlags |= theFlag;
    }
    else
    {
      myLoadFlags &= ~theFlag;
    }
  }

protected:
  occ::handle<Font_FTLibrary>     myFTLib;
  occ::handle<NCollection_Buffer> myBuffer;
  occ::handle<Font_FTFont>        myFallbackFaces[Font_UnicodeSubset_NB];
  FT_Face                         myFTFace;
  FT_Face                         myActiveFTFace;
  TCollection_AsciiString         myFontPath;
  Font_FTFontParams               myFontParams;
  Font_FontAspect                 myFontAspect;
  float                           myWidthScaling;
  int32_t                         myLoadFlags;

  Image_PixMap myGlyphImg;
  char32_t     myUChar;

  bool myToUseUnicodeSubsetFallback;
};
