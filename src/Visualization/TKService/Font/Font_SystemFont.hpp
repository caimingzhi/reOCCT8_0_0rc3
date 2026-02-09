#pragma once

#include <Font_FontAspect.hpp>
#include <Standard.hpp>
#include <NCollection_DefineAlloc.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>

class Font_SystemFont : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Font_SystemFont, Standard_Transient)
public:
  Standard_EXPORT Font_SystemFont(const TCollection_AsciiString& theFontName);

  const TCollection_AsciiString& FontKey() const { return myFontKey; }

  const TCollection_AsciiString& FontName() const { return myFontName; }

  const TCollection_AsciiString& FontPath(Font_FontAspect theAspect) const
  {
    return myFilePaths[theAspect != Font_FontAspect_UNDEFINED ? theAspect
                                                              : Font_FontAspect_Regular];
  }

  int FontFaceId(Font_FontAspect theAspect) const
  {
    return myFaceIds[theAspect != Font_FontAspect_UNDEFINED ? theAspect : Font_FontAspect_Regular];
  }

  Standard_EXPORT void SetFontPath(Font_FontAspect                theAspect,
                                   const TCollection_AsciiString& thePath,
                                   const int                      theFaceId = 0);

  bool HasFontAspect(Font_FontAspect theAspect) const
  {
    return !myFilePaths[theAspect != Font_FontAspect_UNDEFINED ? theAspect
                                                               : Font_FontAspect_Regular]
              .IsEmpty();
  }

  const TCollection_AsciiString& FontPathAny(Font_FontAspect theAspect,
                                             bool&           theToSynthesizeItalic,
                                             int&            theFaceId) const
  {
    const Font_FontAspect anAspect =
      theAspect != Font_FontAspect_UNDEFINED ? theAspect : Font_FontAspect_Regular;
    const TCollection_AsciiString& aPath = myFilePaths[anAspect];
    theFaceId                            = myFaceIds[anAspect];
    if (!aPath.IsEmpty())
    {
      return aPath;
    }

    if (theAspect == Font_FontAspect_Italic || theAspect == Font_FontAspect_BoldItalic)
    {
      if (theAspect == Font_FontAspect_BoldItalic && !myFilePaths[Font_FontAspect_Bold].IsEmpty())
      {
        theToSynthesizeItalic = true;
        theFaceId             = myFaceIds[Font_FontAspect_Bold];
        return myFilePaths[Font_FontAspect_Bold];
      }
      else if (!myFilePaths[Font_FontAspect_Regular].IsEmpty())
      {
        theToSynthesizeItalic = true;
        theFaceId             = myFaceIds[Font_FontAspect_Regular];
        return myFilePaths[Font_FontAspect_Regular];
      }
    }

    if (!myFilePaths[Font_FontAspect_Regular].IsEmpty())
    {
      theFaceId = myFaceIds[Font_FontAspect_Regular];
      return myFilePaths[Font_FontAspect_Regular];
    }

    for (int anAspectIter = 0; anAspectIter < Font_FontAspect_NB; ++anAspectIter)
    {
      if (!myFilePaths[anAspectIter].IsEmpty())
      {
        theFaceId = myFaceIds[anAspectIter];
        return myFilePaths[anAspectIter];
      }
    }
    theFaceId = myFaceIds[Font_FontAspect_Regular];
    return myFilePaths[Font_FontAspect_Regular];
  }

  Standard_EXPORT bool IsEqual(const occ::handle<Font_SystemFont>& theOtherFont) const;

  bool IsSingleStrokeFont() const { return myIsSingleLine; }

  void SetSingleStrokeFont(bool theIsSingleLine) { myIsSingleLine = theIsSingleLine; }

  Standard_EXPORT TCollection_AsciiString ToString() const;

public:
  bool operator==(const Font_SystemFont& theFont) const
  {
    return myFontKey.IsEqual(theFont.FontKey());
  }

private:
  TCollection_AsciiString myFilePaths[Font_FontAspect_NB];
  int                     myFaceIds[Font_FontAspect_NB];
  TCollection_AsciiString myFontKey;
  TCollection_AsciiString myFontName;
  bool                    myIsSingleLine;
};

namespace std
{
  template <>
  struct hash<occ::handle<Font_SystemFont>>
  {
    size_t operator()(const occ::handle<Font_SystemFont>& theLink) const noexcept
    {
      if (theLink.IsNull())
        return 0;
      return std::hash<TCollection_AsciiString>{}(theLink->FontKey());
    }
  };
}; // namespace std
