#pragma once

#include <Standard.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_List.hpp>
#include <Font_SystemFont.hpp>
#include <Font_StrictLevel.hpp>
#include <Font_UnicodeSubset.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Shared.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>

class TCollection_HAsciiString;
class NCollection_Buffer;

class Font_FontMgr : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Font_FontMgr, Standard_Transient)
public:
  Standard_EXPORT static occ::handle<Font_FontMgr> GetInstance();

  static const char* FontAspectToString(Font_FontAspect theAspect)
  {
    switch (theAspect)
    {
      case Font_FontAspect_UNDEFINED:
        return "undefined";
      case Font_FontAspect_Regular:
        return "regular";
      case Font_FontAspect_Bold:
        return "bold";
      case Font_FontAspect_Italic:
        return "italic";
      case Font_FontAspect_BoldItalic:
        return "bold-italic";
    }
    return "invalid";
  }

  Standard_EXPORT static bool& ToUseUnicodeSubsetFallback();

public:
  void AvailableFonts(NCollection_List<occ::handle<Font_SystemFont>>& theList) const
  {
    for (Font_FontMap::Iterator aFontIter(myFontMap); aFontIter.More(); aFontIter.Next())
    {
      theList.Append(aFontIter.Value());
    }
  }

  NCollection_List<occ::handle<Font_SystemFont>> GetAvailableFonts() const
  {
    NCollection_List<occ::handle<Font_SystemFont>> aList;
    AvailableFonts(aList);
    return aList;
  }

  Standard_EXPORT void GetAvailableFontsNames(
    NCollection_Sequence<occ::handle<TCollection_HAsciiString>>& theFontsNames) const;

  Standard_EXPORT occ::handle<Font_SystemFont> GetFont(
    const occ::handle<TCollection_HAsciiString>& theFontName,
    const Font_FontAspect                        theFontAspect,
    const int                                    theFontSize) const;

  Standard_EXPORT occ::handle<Font_SystemFont> GetFont(
    const TCollection_AsciiString& theFontName) const;

  Standard_EXPORT occ::handle<Font_SystemFont> FindFont(const TCollection_AsciiString& theFontName,
                                                        Font_StrictLevel theStrictLevel,
                                                        Font_FontAspect& theFontAspect,
                                                        bool             theDoFailMsg = true) const;

  occ::handle<Font_SystemFont> FindFont(const TCollection_AsciiString& theFontName,
                                        Font_FontAspect&               theFontAspect) const
  {
    return FindFont(theFontName, Font_StrictLevel_Any, theFontAspect);
  }

  Standard_EXPORT occ::handle<Font_SystemFont> FindFallbackFont(
    Font_UnicodeSubset theSubset,
    Font_FontAspect    theFontAspect) const;

  Standard_EXPORT bool CheckFont(NCollection_Sequence<occ::handle<Font_SystemFont>>& theFonts,
                                 const TCollection_AsciiString& theFontPath) const;

  Standard_EXPORT occ::handle<Font_SystemFont> CheckFont(const char* theFontPath) const;

  Standard_EXPORT bool RegisterFont(const occ::handle<Font_SystemFont>& theFont,
                                    const bool                          theToOverride);

  bool RegisterFonts(const NCollection_Sequence<occ::handle<Font_SystemFont>>& theFonts,
                     const bool                                                theToOverride)
  {
    bool isRegistered = false;
    for (NCollection_Sequence<occ::handle<Font_SystemFont>>::Iterator aFontIter(theFonts);
         aFontIter.More();
         aFontIter.Next())
    {
      isRegistered = RegisterFont(aFontIter.Value(), theToOverride) || isRegistered;
    }
    return isRegistered;
  }

public:
  bool ToTraceAliases() const { return myToTraceAliases; }

  void SetTraceAliases(bool theToTrace) { myToTraceAliases = theToTrace; }

  bool ToPrintErrors() const { return myToPrintErrors; }

  void SetPrintErrors(bool theToPrintErrors) { myToPrintErrors = theToPrintErrors; }

  Standard_EXPORT void GetAllAliases(
    NCollection_Sequence<occ::handle<TCollection_HAsciiString>>& theAliases) const;

  Standard_EXPORT void GetFontAliases(
    NCollection_Sequence<occ::handle<TCollection_HAsciiString>>& theFontNames,
    const TCollection_AsciiString&                               theAliasName) const;

  Standard_EXPORT bool AddFontAlias(const TCollection_AsciiString& theAliasName,
                                    const TCollection_AsciiString& theFontName);

  Standard_EXPORT bool RemoveFontAlias(const TCollection_AsciiString& theAliasName,
                                       const TCollection_AsciiString& theFontName);

public:
  Standard_EXPORT void InitFontDataBase();

  Standard_EXPORT void ClearFontDataBase();

  Standard_EXPORT static occ::handle<NCollection_Buffer> EmbedFallbackFont();

private:
  Standard_EXPORT Font_FontMgr();

private:
  struct FontHasher
  {
    size_t operator()(const occ::handle<Font_SystemFont>& theFont) const noexcept
    {
      return std::hash<TCollection_AsciiString>{}(theFont->FontKey());
    }

    bool operator()(const occ::handle<Font_SystemFont>& theFont1,
                    const occ::handle<Font_SystemFont>& theFont2) const
    {
      return theFont1->IsEqual(theFont2);
    }
  };

  class Font_FontMap : public NCollection_IndexedMap<occ::handle<Font_SystemFont>, FontHasher>
  {
  public:
    Font_FontMap() = default;

    occ::handle<Font_SystemFont> Find(const TCollection_AsciiString& theFontName) const;
  };

  struct Font_FontAlias
  {
    TCollection_AsciiString FontName;
    Font_FontAspect         FontAspect;

    Font_FontAlias(const TCollection_AsciiString& theFontName,
                   Font_FontAspect                theFontAspect = Font_FontAspect_UNDEFINED)
        : FontName(theFontName),
          FontAspect(theFontAspect)
    {
    }

    Font_FontAlias()
        : FontAspect(Font_FontAspect_UNDEFINED)
    {
    }
  };

  typedef NCollection_Shared<NCollection_Sequence<Font_FontAlias>> Font_FontAliasSequence;

  void addFontAlias(const TCollection_AsciiString&             theAliasName,
                    const occ::handle<Font_FontAliasSequence>& theAliases,
                    Font_FontAspect theAspect = Font_FontAspect_UNDEFINED);

private:
  Font_FontMap                                                                      myFontMap;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Font_FontAliasSequence>> myFontAliases;
  occ::handle<Font_FontAliasSequence>                                               myFallbackAlias;
  bool myToTraceAliases;
  bool myToPrintErrors;
};
