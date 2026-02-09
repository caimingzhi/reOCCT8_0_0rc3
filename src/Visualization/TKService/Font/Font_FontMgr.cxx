#include <Font_FontMgr.hpp>

#include <Font_NameOfFont.hpp>
#include <Font_FTLibrary.hpp>
#include <Font_SystemFont.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <NCollection_Buffer.hpp>
#include <NCollection_Map.hpp>
#include <OSD_Environment.hpp>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

#ifdef HAVE_FREETYPE
  #include "Font_DejavuSans_Latin_woff.hpp"

  #include <ft2build.h>
  #include FT_FREETYPE_H
#endif
IMPLEMENT_STANDARD_RTTIEXT(Font_FontMgr, Standard_Transient)

#if defined(_WIN32)

  #include <windows.h>
  #include <stdlib.h>

namespace
{

  static const char* Font_FontMgr_Extensions[] = {"ttf", "otf", "ttc", NULL};
}

#else

  #include <OSD_DirectoryIterator.hpp>
  #include <OSD_FileIterator.hpp>
  #include <OSD_Path.hpp>
  #include <OSD_File.hpp>
  #include <OSD_OpenMode.hpp>
  #include <OSD_Protection.hpp>

namespace
{

  static const char* Font_FontMgr_Extensions[] = {"ttf",
                                                  "otf",
                                                  "ttc",
                                                  "pfa",
                                                  "pfb",
  #ifdef __APPLE__

  #endif
                                                  nullptr};

  #if defined(HAVE_FREETYPE) && !defined(__ANDROID__) && !defined(__APPLE__)                       \
    && !defined(__EMSCRIPTEN__)

  static const char* myFontServiceConf[] = {"/etc/X11/fs/config",
                                            "/usr/X11R6/lib/X11/fs/config",
                                            "/usr/X11/lib/X11/fs/config",
                                            nullptr};

    #include <fontconfig/fontconfig.h>
  #endif

  #ifdef __APPLE__

  static const char* myDefaultFontsDirs[] = {"/System/Library/Fonts", "/Library/Fonts", nullptr};
  #else

  static const char* myDefaultFontsDirs[] = {"/system/fonts",
                                             "/usr/share/fonts",
                                             "/usr/local/share/fonts",
                                             nullptr};
  #endif

  static void addDirsRecursively(const OSD_Path&                           thePath,
                                 NCollection_Map<TCollection_AsciiString>& theDirsMap)
  {
    TCollection_AsciiString aDirName;
    thePath.SystemName(aDirName);
    if (!theDirsMap.Add(aDirName))
    {
      return;
    }

    for (OSD_DirectoryIterator aDirIterator(thePath, "*"); aDirIterator.More(); aDirIterator.Next())
    {
      OSD_Path aChildDirPath;
      aDirIterator.Values().Path(aChildDirPath);

      TCollection_AsciiString aChildDirName;
      aChildDirPath.SystemName(aChildDirName);
      if (!aChildDirName.IsEqual(".") && !aChildDirName.IsEqual(".."))
      {
        aChildDirName = aDirName + "/" + aChildDirName;
        OSD_Path aPath(aChildDirName);
        addDirsRecursively(aPath, theDirsMap);
      }
    }
  }

} // namespace

#endif

static bool checkFont(NCollection_Sequence<occ::handle<Font_SystemFont>>& theFonts,
                      const occ::handle<Font_FTLibrary>&                  theFTLib,
                      const TCollection_AsciiString&                      theFontPath,
                      signed long                                         theFaceId = -1)
{
#ifdef HAVE_FREETYPE
  const FT_Long aFaceId = theFaceId != -1 ? theFaceId : 0;
  FT_Face       aFontFace;
  FT_Error      aFaceError =
    FT_New_Face(theFTLib->Instance(), theFontPath.ToCString(), aFaceId, &aFontFace);
  if (aFaceError != FT_Err_Ok)
  {
    return false;
  }
  if (aFontFace->family_name == nullptr || FT_Select_Charmap(aFontFace, ft_encoding_unicode) != 0)
  {
    FT_Done_Face(aFontFace);
    return false;
  }

  TCollection_AsciiString aFamily(aFontFace->family_name);
  TCollection_AsciiString aStyle(aFontFace->style_name != nullptr ? aFontFace->style_name : "");
  Font_FontAspect         anAspect = Font_FA_Regular;
  if (aFontFace->style_flags == (FT_STYLE_FLAG_ITALIC | FT_STYLE_FLAG_BOLD))
  {
    anAspect                = Font_FA_BoldItalic;
    const int aRemoveItalic = aStyle.Search("Italic");
    if (aRemoveItalic != -1)
    {
      aStyle.Remove(aRemoveItalic, 6);
    }
    else
    {

      const int aRemoveOblique = aStyle.Search("Oblique");
      if (aRemoveOblique != -1)
      {
        aStyle.Remove(aRemoveOblique, 7);
      }
    }

    const int aRemoveBold = aStyle.Search("Bold");
    if (aRemoveBold != -1)
    {
      aStyle.Remove(aRemoveBold, 4);
    }
  }
  else if (aFontFace->style_flags == FT_STYLE_FLAG_ITALIC)
  {
    anAspect                = Font_FA_Italic;
    const int aRemoveItalic = aStyle.Search("Italic");
    if (aRemoveItalic != -1)
    {
      aStyle.Remove(aRemoveItalic, 6);
    }
    else
    {

      const int aRemoveOblique = aStyle.Search("Oblique");
      if (aRemoveOblique != -1)
      {
        aStyle.Remove(aRemoveOblique, 7);
      }
    }
  }
  else if (aFontFace->style_flags == FT_STYLE_FLAG_BOLD)
  {
    anAspect              = Font_FA_Bold;
    const int aRemoveBold = aStyle.Search("Bold");
    if (aRemoveBold != -1)
    {
      aStyle.Remove(aRemoveBold, 4);
    }
  }

  const int aRemoveReg = aStyle.Search("Regular");
  if (aRemoveReg != -1)
  {
    aStyle.Remove(aRemoveReg, 7);
  }
  else
  {

    const int aRemoveBook = aStyle.Search("Book");
    if (aRemoveBook != -1)
    {
      aStyle.Remove(aRemoveBook, 4);
    }
  }

  aStyle.LeftAdjust();
  aStyle.RightAdjust();
  for (;;)
  {

    const int aRemoveSpace = aStyle.Search("  ");
    if (aRemoveSpace == -1)
    {
      break;
    }

    aStyle.Remove(aRemoveSpace, 1);
  }

  if (!aStyle.IsEmpty())
  {
    aFamily = aFamily + " " + aStyle;
  }

  occ::handle<Font_SystemFont> aResult = new Font_SystemFont(aFamily);
  aResult->SetFontPath(anAspect, theFontPath, (int)aFaceId);

  aResult->SetSingleStrokeFont(aResult->FontKey().StartsWith("olf "));
  theFonts.Append(aResult);

  if (theFaceId < aFontFace->num_faces)
  {
    const FT_Long aNbInstances = aFontFace->style_flags >> 16;
    for (FT_Long anInstIter = 1; anInstIter < aNbInstances; ++anInstIter)
    {
      const FT_Long aSubFaceId = aFaceId + (anInstIter << 16);
      checkFont(theFonts, theFTLib, theFontPath, aSubFaceId);
    }
  }
  if (theFaceId == -1)
  {
    for (FT_Long aFaceIter = 1; aFaceIter < aFontFace->num_faces; ++aFaceIter)
    {
      checkFont(theFonts, theFTLib, theFontPath, aFaceIter);
    }
  }

  FT_Done_Face(aFontFace);
  return true;
#else
  (void)theFonts;
  (void)theFTLib;
  (void)theFontPath;
  (void)theFaceId;
  return false;
#endif
}

occ::handle<Font_FontMgr> Font_FontMgr::GetInstance()
{
  static occ::handle<Font_FontMgr> _mgr;
  if (_mgr.IsNull())
  {
    _mgr = new Font_FontMgr();
  }

  return _mgr;
}

bool& Font_FontMgr::ToUseUnicodeSubsetFallback()
{
  static bool TheToUseUnicodeSubsetFallback = true;
  return TheToUseUnicodeSubsetFallback;
}

bool Font_FontMgr::AddFontAlias(const TCollection_AsciiString& theAliasName,
                                const TCollection_AsciiString& theFontName)
{
  TCollection_AsciiString anAliasName(theAliasName);
  anAliasName.LowerCase();
  occ::handle<Font_FontAliasSequence> anAliases;
  if (!myFontAliases.Find(anAliasName, anAliases))
  {
    anAliases = new Font_FontAliasSequence();
    myFontAliases.Bind(anAliasName, anAliases);
  }

  for (Font_FontAliasSequence::Iterator anAliasIter(*anAliases); anAliasIter.More();
       anAliasIter.Next())
  {
    if (anAliasIter.Value().FontName.IsEqual(anAliasName))
    {
      return false;
    }
  }

  anAliases->Append(Font_FontAlias(theFontName));
  return true;
}

bool Font_FontMgr::RemoveFontAlias(const TCollection_AsciiString& theAliasName,
                                   const TCollection_AsciiString& theFontName)
{
  if (theAliasName.IsEmpty())
  {
    if (myFontAliases.IsEmpty())
    {
      return false;
    }
    myFontAliases.Clear();
    return true;
  }

  TCollection_AsciiString anAliasName(theAliasName);
  anAliasName.LowerCase();
  occ::handle<Font_FontAliasSequence> anAliases;
  if (!myFontAliases.Find(anAliasName, anAliases))
  {
    return false;
  }

  if (theFontName.IsEmpty())
  {
    myFontAliases.UnBind(anAliasName);
    return true;
  }

  for (Font_FontAliasSequence::Iterator aFontIter(*anAliases); aFontIter.More(); aFontIter.Next())
  {
    if (aFontIter.Value().FontName.IsEqual(theFontName))
    {
      anAliases->Remove(aFontIter);
      if (anAliases->IsEmpty())
      {
        myFontAliases.UnBind(anAliasName);
      }
      return true;
    }
  }
  return false;
}

void Font_FontMgr::GetAllAliases(
  NCollection_Sequence<occ::handle<TCollection_HAsciiString>>& theAliases) const
{
  for (NCollection_DataMap<TCollection_AsciiString, occ::handle<Font_FontAliasSequence>>::Iterator
         anAliasIter(myFontAliases);
       anAliasIter.More();
       anAliasIter.Next())
  {
    theAliases.Append(new TCollection_HAsciiString(anAliasIter.Key()));
  }
}

void Font_FontMgr::GetFontAliases(
  NCollection_Sequence<occ::handle<TCollection_HAsciiString>>& theFontNames,
  const TCollection_AsciiString&                               theAliasName) const
{
  TCollection_AsciiString anAliasName(theAliasName);
  anAliasName.LowerCase();
  occ::handle<Font_FontAliasSequence> anAliases;
  if (!myFontAliases.Find(anAliasName, anAliases))
  {
    return;
  }

  for (Font_FontAliasSequence::Iterator aFontIter(*anAliases); aFontIter.More(); aFontIter.Next())
  {
    theFontNames.Append(new TCollection_HAsciiString(aFontIter.Value().FontName));
  }
}

void Font_FontMgr::addFontAlias(const TCollection_AsciiString&             theAliasName,
                                const occ::handle<Font_FontAliasSequence>& theAliases,
                                Font_FontAspect                            theAspect)
{
  if (theAliases.IsNull() || theAliases->IsEmpty())
  {
    return;
  }

  occ::handle<Font_FontAliasSequence> anAliases = theAliases;
  if (theAspect != Font_FA_Undefined)
  {
    anAliases = new Font_FontAliasSequence();
    for (Font_FontAliasSequence::Iterator anAliasIter(*theAliases); anAliasIter.More();
         anAliasIter.Next())
    {
      const TCollection_AsciiString& aName = anAliasIter.Value().FontName;
      anAliases->Append(Font_FontAlias(aName, theAspect));
    }
  }

  TCollection_AsciiString anAliasName(theAliasName);
  anAliasName.LowerCase();
  myFontAliases.Bind(anAliasName, anAliases);
}

Font_FontMgr::Font_FontMgr()
    : myToTraceAliases(false),
      myToPrintErrors(true)
{
  occ::handle<Font_FontAliasSequence> aMono   = new Font_FontAliasSequence();
  occ::handle<Font_FontAliasSequence> aSerif  = new Font_FontAliasSequence();
  occ::handle<Font_FontAliasSequence> aSans   = new Font_FontAliasSequence();
  occ::handle<Font_FontAliasSequence> aSymbol = new Font_FontAliasSequence();
  occ::handle<Font_FontAliasSequence> aScript = new Font_FontAliasSequence();
  occ::handle<Font_FontAliasSequence> aWinDin = new Font_FontAliasSequence();
  occ::handle<Font_FontAliasSequence> anIris  = new Font_FontAliasSequence();
  occ::handle<Font_FontAliasSequence> aCJK    = new Font_FontAliasSequence();
  occ::handle<Font_FontAliasSequence> aKorean = new Font_FontAliasSequence();
  occ::handle<Font_FontAliasSequence> anArab  = new Font_FontAliasSequence();

  aMono->Append(Font_FontAlias("courier new"));
  aSerif->Append(Font_FontAlias("times new roman"));
  aSans->Append(Font_FontAlias("arial"));
  aSymbol->Append(Font_FontAlias("symbol"));
  aScript->Append(Font_FontAlias("script"));
  aWinDin->Append(Font_FontAlias("wingdings"));
  anIris->Append(Font_FontAlias("lucida console"));

#if defined(__ANDROID__)

  aMono->Append(Font_FontAlias("noto mono"));
  aSerif->Append(Font_FontAlias("noto serif"));

  aMono->Append(Font_FontAlias("droid sans mono"));
  aSerif->Append(Font_FontAlias("droid serif"));
  aSans->Append(Font_FontAlias("roboto"));
#elif !defined(_WIN32) && !defined(__APPLE__)
  aSerif->Append(Font_FontAlias("times"));
  aSans->Append(Font_FontAlias("helvetica"));

  aMono->Append(Font_FontAlias("freemono"));
  aSerif->Append(Font_FontAlias("freeserif"));
  aSans->Append(Font_FontAlias("freesans"));

  aMono->Append(Font_FontAlias("dejavu sans mono"));
  aSerif->Append(Font_FontAlias("dejavu serif"));
  aSans->Append(Font_FontAlias("dejavu sans"));
#endif

  aCJK->Append(Font_FontAlias("simsun"));
  aCJK->Append(Font_FontAlias("droid sans fallback"));
  aCJK->Append(Font_FontAlias("noto sans sc"));
  aCJK->Append(Font_FontAlias("noto sans cjk jp"));

#if defined(_WIN32)
  aKorean->Append(Font_FontAlias("malgun gothic"));
  aKorean->Append(Font_FontAlias("gulim"));
#elif defined(__APPLE__)
  aKorean->Append(Font_FontAlias("applegothic"));
  aKorean->Append(Font_FontAlias("stfangsong"));
#endif
  aKorean->Append(Font_FontAlias("nanumgothic"));
  aKorean->Append(Font_FontAlias("noto sans kr"));
  aKorean->Append(Font_FontAlias("nanummyeongjo"));
  aKorean->Append(Font_FontAlias("noto serif cjk jp"));
  aKorean->Append(Font_FontAlias("noto sans cjk jp"));
  aKorean->Append(Font_FontAlias("droid sans fallback"));

#if defined(_WIN32)
  anArab->Append(Font_FontAlias("times new roman"));
#elif defined(__APPLE__)
  anArab->Append(Font_FontAlias("decotype naskh"));
#elif defined(__ANDROID__)
  anArab->Append(Font_FontAlias("droid arabic naskh"));
  anArab->Append(Font_FontAlias("noto naskh arabic"));
#endif

  addFontAlias("mono", aMono);
  addFontAlias("courier", aMono);
  addFontAlias("monospace", aMono);
  addFontAlias("rock", aSans);
  addFontAlias("sansserif", aSans);
  addFontAlias("sans-serif", aSans);
  addFontAlias("sans", aSans);
  addFontAlias("arial", aSans);
  addFontAlias("times", aSerif);
  addFontAlias("serif", aSerif);
  addFontAlias("times-roman", aSerif);
  addFontAlias("times-bold", aSerif, Font_FA_Bold);
  addFontAlias("times-italic", aSerif, Font_FA_Italic);
  addFontAlias("times-bolditalic", aSerif, Font_FA_BoldItalic);
  addFontAlias("symbol", aSymbol);
  addFontAlias("iris", anIris);
  addFontAlias("korean", aKorean);
  addFontAlias("cjk", aCJK);
  addFontAlias("nsimsun", aCJK);
  addFontAlias("arabic", anArab);
  addFontAlias(Font_NOF_SYMBOL_MONO, aWinDin);
  addFontAlias(Font_NOF_ASCII_SCRIPT_SIMPLEX, aScript);

  myFallbackAlias = aSans;

  InitFontDataBase();
}

bool Font_FontMgr::CheckFont(NCollection_Sequence<occ::handle<Font_SystemFont>>& theFonts,
                             const TCollection_AsciiString&                      theFontPath) const
{
  occ::handle<Font_FTLibrary> aFtLibrary = new Font_FTLibrary();
  return checkFont(theFonts, aFtLibrary, theFontPath, 0);
}

occ::handle<Font_SystemFont> Font_FontMgr::CheckFont(const char* theFontPath) const
{
  occ::handle<Font_FTLibrary>                        aFtLibrary = new Font_FTLibrary();
  NCollection_Sequence<occ::handle<Font_SystemFont>> aFonts;
  return checkFont(aFonts, aFtLibrary, theFontPath, 0) ? aFonts.First()
                                                       : occ::handle<Font_SystemFont>();
}

bool Font_FontMgr::RegisterFont(const occ::handle<Font_SystemFont>& theFont,
                                const bool                          theToOverride)
{
  if (theFont.IsNull())
  {
    return false;
  }

  const int anOldIndex = myFontMap.FindIndex(theFont);
  if (anOldIndex == 0)
  {
    myFontMap.Add(theFont);
    return true;
  }

  occ::handle<Font_SystemFont> anOldFont = myFontMap.FindKey(anOldIndex);
  for (int anAspectIter = 0; anAspectIter < Font_FontAspect_NB; ++anAspectIter)
  {
    if (anOldFont->FontPath((Font_FontAspect)anAspectIter)
          .IsEqual(theFont->FontPath((Font_FontAspect)anAspectIter))
        && anOldFont->FontFaceId((Font_FontAspect)anAspectIter)
             == theFont->FontFaceId((Font_FontAspect)anAspectIter))
    {
      continue;
    }
    else if (theToOverride || !anOldFont->HasFontAspect((Font_FontAspect)anAspectIter))
    {
      anOldFont->SetFontPath((Font_FontAspect)anAspectIter,
                             theFont->FontPath((Font_FontAspect)anAspectIter),
                             theFont->FontFaceId((Font_FontAspect)anAspectIter));
    }
    else if (theFont->HasFontAspect((Font_FontAspect)anAspectIter))
    {
      return false;
    }
  }
  return true;
}

void Font_FontMgr::ClearFontDataBase()
{
  myFontMap.Clear();
}

void Font_FontMgr::InitFontDataBase()
{
  myFontMap.Clear();
  occ::handle<Font_FTLibrary>                        aFtLibrary = new Font_FTLibrary();
  NCollection_Sequence<occ::handle<Font_SystemFont>> aFonts;

#if defined(OCCT_UWP)

  (void)aFtLibrary;
#elif defined(_WIN32)

  UINT aStrLength = GetSystemWindowsDirectoryA(NULL, 0);
  if (aStrLength == 0)
  {
    return;
  }

  char* aWinDir = new char[aStrLength];
  GetSystemWindowsDirectoryA(aWinDir, aStrLength);
  TCollection_AsciiString aFontsDir(aWinDir);
  aFontsDir.AssignCat("\\Fonts\\");
  delete[] aWinDir;

  HKEY aFontsKey;
  if (RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                    "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts",
                    0,
                    KEY_READ,
                    &aFontsKey)
      != ERROR_SUCCESS)
  {
    return;
  }

  NCollection_Map<TCollection_AsciiString> aSupportedExtensions;
  for (int anIter = 0; Font_FontMgr_Extensions[anIter] != NULL; ++anIter)
  {
    const char* anExt = Font_FontMgr_Extensions[anIter];
    aSupportedExtensions.Add(TCollection_AsciiString(anExt));
  }

  static const DWORD aBufferSize = 256;
  char               aNameBuff[aBufferSize];
  char               aPathBuff[aBufferSize];
  DWORD              aNameSize = aBufferSize;
  DWORD              aPathSize = aBufferSize;
  for (DWORD anIter = 0; RegEnumValueA(aFontsKey,
                                       anIter,
                                       aNameBuff,
                                       &aNameSize,
                                       NULL,
                                       NULL,
                                       (LPBYTE)aPathBuff,
                                       &aPathSize)
                         != ERROR_NO_MORE_ITEMS;
       ++anIter, aNameSize = aBufferSize, aPathSize = aBufferSize)
  {

    aPathBuff[(aPathSize < aBufferSize) ? aPathSize : (aBufferSize - 1)] = '\0';

    TCollection_AsciiString aFontName(aNameBuff), aFontPath(aPathBuff);
    if (aFontPath.Search("\\") == -1)
    {
      aFontPath.Insert(1, aFontsDir);
    }

    const int anExtensionPosition = aFontPath.SearchFromEnd(".") + 1;
    if (anExtensionPosition > 0 && anExtensionPosition < aFontPath.Length())
    {
      TCollection_AsciiString aFontExtension =
        aFontPath.SubString(anExtensionPosition, aFontPath.Length());
      aFontExtension.LowerCase();
      if (aSupportedExtensions.Contains(aFontExtension))
      {
        aFonts.Clear();
        checkFont(aFonts, aFtLibrary, aFontPath.ToCString());
        RegisterFonts(aFonts, false);
      }
    }
  }

  RegCloseKey(aFontsKey);

#else

  NCollection_Map<TCollection_AsciiString> aMapOfFontsDirs;
  #if defined(HAVE_FREETYPE) && !defined(__ANDROID__) && !defined(__APPLE__)                       \
    && !defined(__EMSCRIPTEN__)
  if (FcConfig* aFcCfg = FcInitLoadConfig())
  {
    if (FcStrList* aFcFontDir = FcConfigGetFontDirs(aFcCfg))
    {
      for (;;)
      {
        FcChar8* aFcFolder = FcStrListNext(aFcFontDir);
        if (aFcFolder == nullptr)
        {
          break;
        }

        TCollection_AsciiString aPathStr((const char*)aFcFolder);
        OSD_Path                aPath(aPathStr);
        addDirsRecursively(aPath, aMapOfFontsDirs);
      }
      FcStrListDone(aFcFontDir);
    }
    FcConfigDestroy(aFcCfg);
  }

  const OSD_Protection aProtectRead(OSD_R, OSD_R, OSD_R, OSD_R);
  if (aMapOfFontsDirs.IsEmpty())
  {
    Message::SendAlarm("Font_FontMgr, fontconfig library returns an empty folder list");

    for (int anIter = 0; myFontServiceConf[anIter] != nullptr; ++anIter)
    {
      const TCollection_AsciiString aFileOfFontsPath(myFontServiceConf[anIter]);
      OSD_File                      aFile(aFileOfFontsPath);
      if (!aFile.Exists())
      {
        continue;
      }

      aFile.Open(OSD_ReadOnly, aProtectRead);
      if (!aFile.IsOpen())
      {
        continue;
      }

      int                     aNByte = 256;
      int                     aNbyteRead;
      TCollection_AsciiString aStr;
      while (!aFile.IsAtEnd())
      {
        int aLocation     = -1;
        int aPathLocation = -1;

        aFile.ReadLine(aStr, aNByte, aNbyteRead);
        aLocation = aStr.Search("catalogue=");
        if (aLocation < 0)
        {
          aLocation = aStr.Search("catalogue =");
        }

        aPathLocation = aStr.Search("/");
        if (aLocation > 0 && aPathLocation > 0)
        {
          aStr = aStr.Split(aPathLocation - 1);
          TCollection_AsciiString aFontPath;
          int                     aPathNumber = 1;
          do
          {

            aFontPath = aStr.Token(":,", aPathNumber);
            aFontPath.RightAdjust();
            if (!aFontPath.IsEmpty())
            {
              OSD_Path aPath(aFontPath);
              addDirsRecursively(aPath, aMapOfFontsDirs);
            }
            aPathNumber++;
          } while (!aFontPath.IsEmpty());
        }
      }
      aFile.Close();
    }
  }
  #endif

  for (int anIter = 0; myDefaultFontsDirs[anIter] != nullptr; ++anIter)
  {
    const char*             anItem = myDefaultFontsDirs[anIter];
    TCollection_AsciiString aPathStr(anItem);
    OSD_Path                aPath(aPathStr);
    addDirsRecursively(aPath, aMapOfFontsDirs);
  }

  NCollection_Map<TCollection_AsciiString> aSupportedExtensions;
  for (int anIter = 0; Font_FontMgr_Extensions[anIter] != nullptr; ++anIter)
  {
    const char* anExt = Font_FontMgr_Extensions[anIter];
    aSupportedExtensions.Add(TCollection_AsciiString(anExt));
  }

  for (NCollection_Map<TCollection_AsciiString>::Iterator anIter(aMapOfFontsDirs); anIter.More();
       anIter.Next())
  {
  #if defined(HAVE_FREETYPE) && !defined(__ANDROID__) && !defined(__APPLE__)                       \
    && !defined(__EMSCRIPTEN__)
    OSD_File aReadFile(anIter.Value() + "/fonts.dir");
    if (!aReadFile.Exists())
    {
  #endif
      OSD_Path aFolderPath(anIter.Value());
      for (OSD_FileIterator aFileIter(aFolderPath, "*"); aFileIter.More(); aFileIter.Next())
      {
        OSD_Path aFontFilePath;
        aFileIter.Values().Path(aFontFilePath);

        TCollection_AsciiString aFontFileName;
        aFontFilePath.SystemName(aFontFileName);
        aFontFileName = anIter.Value() + "/" + aFontFileName;

        aFonts.Clear();
        checkFont(aFonts, aFtLibrary, aFontFileName);
        RegisterFonts(aFonts, false);
      }

  #if defined(HAVE_FREETYPE) && !defined(__ANDROID__) && !defined(__APPLE__)                       \
    && !defined(__EMSCRIPTEN__)
      continue;
    }

    aReadFile.Open(OSD_ReadOnly, aProtectRead);
    if (!aReadFile.IsOpen())
    {
      continue;
    }

    int                           aNbyteRead, aNByte = 256;
    TCollection_AsciiString       aLine(aNByte);
    bool                          isFirstLine = true;
    const TCollection_AsciiString anEncoding("iso8859-1\n");
    while (!aReadFile.IsAtEnd())
    {
      aReadFile.ReadLine(aLine, aNByte, aNbyteRead);
      if (isFirstLine)
      {

        isFirstLine = false;
        continue;
      }

      int anExtensionPosition = aLine.Search(".") + 1;
      if (anExtensionPosition == 0)
      {
        continue;
      }

      int anEndOfFileName = aLine.Location(" ", anExtensionPosition, aLine.Length()) - 1;
      if (anEndOfFileName < 0 || anEndOfFileName < anExtensionPosition)
      {
        continue;
      }

      TCollection_AsciiString aFontExtension =
        aLine.SubString(anExtensionPosition, anEndOfFileName);
      aFontExtension.LowerCase();
      if (aSupportedExtensions.Contains(aFontExtension) && (aLine.Search(anEncoding) > 0))
      {

        TCollection_AsciiString aXLFD(aLine.SubString(anEndOfFileName + 2, aLine.Length()));
        TCollection_AsciiString aFontPath(anIter.Value().ToCString());
        if (aFontPath.SearchFromEnd("/") != aFontPath.Length())
        {
          aFontPath.AssignCat("/");
        }
        TCollection_AsciiString aFontFileName(aLine.SubString(1, anEndOfFileName));
        aFontPath.AssignCat(aFontFileName);

        aFonts.Clear();
        if (checkFont(aFonts, aFtLibrary, aFontPath))
        {
          RegisterFonts(aFonts, false);
          const occ::handle<Font_SystemFont>& aNewFont = aFonts.First();
          if (!aXLFD.IsEmpty() && aXLFD.Search("-0-0-0-0-") != -1)
          {
            const TCollection_AsciiString anXName   = aXLFD.Token("-", 2);
            Font_FontAspect               anXAspect = Font_FA_Regular;
            if (aXLFD.Token("-", 3).IsEqual("bold")
                && (aXLFD.Token("-", 4).IsEqual("i") || aXLFD.Token("-", 4).IsEqual("o")))
            {
              anXAspect = Font_FA_BoldItalic;
            }
            else if (aXLFD.Token("-", 3).IsEqual("bold"))
            {
              anXAspect = Font_FA_Bold;
            }
            else if (aXLFD.Token("-", 4).IsEqual("i") || aXLFD.Token("-", 4).IsEqual("o"))
            {
              anXAspect = Font_FA_Italic;
            }

            occ::handle<Font_SystemFont> aNewFontFromXLFD = new Font_SystemFont(anXName);
            aNewFontFromXLFD->SetFontPath(anXAspect, aFontPath, 0);
            if (!aNewFont->IsEqual(aNewFontFromXLFD))
            {
              RegisterFont(aNewFontFromXLFD, false);
            }
          }
        }
      }
    }
    aReadFile.Close();
  #endif
  }
#endif
}

void Font_FontMgr::GetAvailableFontsNames(
  NCollection_Sequence<occ::handle<TCollection_HAsciiString>>& theFontsNames) const
{
  theFontsNames.Clear();
  for (Font_FontMap::Iterator aFontIter(myFontMap); aFontIter.More(); aFontIter.Next())
  {
    const occ::handle<Font_SystemFont>& aFont = aFontIter.Value();
    theFontsNames.Append(new TCollection_HAsciiString(aFont->FontName()));
  }
}

occ::handle<Font_SystemFont> Font_FontMgr::GetFont(
  const occ::handle<TCollection_HAsciiString>& theFontName,
  const Font_FontAspect                        theFontAspect,
  const int                                    theFontSize) const
{
  if ((theFontSize < 2 && theFontSize != -1) || theFontName.IsNull())
  {
    return occ::handle<Font_SystemFont>();
  }

  occ::handle<Font_SystemFont> aFont = myFontMap.Find(theFontName->String());
  return (aFont.IsNull() || theFontAspect == Font_FontAspect_UNDEFINED
          || aFont->HasFontAspect(theFontAspect))
           ? aFont
           : occ::handle<Font_SystemFont>();
}

occ::handle<Font_SystemFont> Font_FontMgr::GetFont(const TCollection_AsciiString& theFontName) const
{
  return myFontMap.Find(theFontName);
}

occ::handle<Font_SystemFont> Font_FontMgr::FindFallbackFont(Font_UnicodeSubset theSubset,
                                                            Font_FontAspect    theFontAspect) const
{
  Font_FontAspect              aFontAspect = theFontAspect;
  occ::handle<Font_SystemFont> aFont;
  switch (theSubset)
  {
    case Font_UnicodeSubset_Western:
      aFont = FindFont(Font_NOF_SANS_SERIF, Font_StrictLevel_Aliases, aFontAspect, false);
      break;
    case Font_UnicodeSubset_Korean:
      aFont = FindFont(Font_NOF_KOREAN, Font_StrictLevel_Aliases, aFontAspect, false);
      break;
    case Font_UnicodeSubset_CJK:
      aFont = FindFont(Font_NOF_CJK, Font_StrictLevel_Aliases, aFontAspect, false);
      break;
    case Font_UnicodeSubset_Arabic:
      aFont = FindFont(Font_NOF_ARABIC, Font_StrictLevel_Aliases, aFontAspect, false);
      break;
  }
  if (aFont.IsNull())
  {
    const char* aRange = "";
    switch (theSubset)
    {
      case Font_UnicodeSubset_Western:
        aRange = "Western";
        break;
      case Font_UnicodeSubset_Korean:
        aRange = "Korean";
        break;
      case Font_UnicodeSubset_CJK:
        aRange = "CJK";
        break;
      case Font_UnicodeSubset_Arabic:
        aRange = "Arabic";
        break;
    }
    Message::SendFail(TCollection_AsciiString("Font_FontMgr, error: unable to find ") + aRange
                      + " fallback font!");
  }
  return aFont;
}

occ::handle<Font_SystemFont> Font_FontMgr::FindFont(const TCollection_AsciiString& theFontName,
                                                    Font_StrictLevel               theStrictLevel,
                                                    Font_FontAspect&               theFontAspect,
                                                    bool theDoFailMsg) const
{
  TCollection_AsciiString aFontName(theFontName);
  aFontName.LowerCase();
  occ::handle<Font_SystemFont> aFont = myFontMap.Find(aFontName);
  if (!aFont.IsNull() || theStrictLevel == Font_StrictLevel_Strict)
  {
    return aFont;
  }

  for (int aPass = 0; aPass < 2; ++aPass)
  {
    occ::handle<Font_FontAliasSequence> anAliases;
    if (aPass == 0)
    {
      myFontAliases.Find(aFontName, anAliases);
    }
    else if (theStrictLevel == Font_StrictLevel_Any)
    {
      anAliases = myFallbackAlias;
    }

    if (anAliases.IsNull() || anAliases->IsEmpty())
    {
      continue;
    }

    bool isAliasUsed = false, isBestAlias = false;
    for (Font_FontAliasSequence::Iterator anAliasIter(*anAliases); anAliasIter.More();
         anAliasIter.Next())
    {
      const Font_FontAlias& anAlias = anAliasIter.Value();
      if (occ::handle<Font_SystemFont> aFont2 = myFontMap.Find(anAlias.FontName))
      {
        if (aFont.IsNull())
        {
          aFont       = aFont2;
          isAliasUsed = true;
        }

        if ((anAlias.FontAspect != Font_FontAspect_UNDEFINED
             && aFont2->HasFontAspect(anAlias.FontAspect)))
        {

          isBestAlias   = true;
          theFontAspect = anAlias.FontAspect;
          break;
        }
        else if (anAlias.FontAspect == Font_FontAspect_UNDEFINED
                 && (theFontAspect == Font_FontAspect_UNDEFINED
                     || aFont2->HasFontAspect(theFontAspect)))
        {
          isBestAlias = true;
          break;
        }
      }
    }

    if (aPass == 0)
    {
      if (isAliasUsed && myToTraceAliases)
      {
        Message::SendTrace(TCollection_AsciiString("Font_FontMgr, using font alias '")
                           + aFont->FontName()
                           + "'"
                             " instead of requested '"
                           + theFontName + "'");
      }
      if (isBestAlias)
      {
        return aFont;
      }
      else if (!aFont.IsNull())
      {
        break;
      }
    }
  }

  if (aFont.IsNull() && theStrictLevel == Font_StrictLevel_Any)
  {

    aFont = myFontMap.Find(TCollection_AsciiString::EmptyString());
  }
  if (aFont.IsNull())
  {
    if (theDoFailMsg && myToPrintErrors)
    {
      Message::SendFail("Font_FontMgr, error: unable to find any font!");
    }
    return occ::handle<Font_SystemFont>();
  }

  if ((theFontAspect != Font_FA_Undefined && !aFont->HasFontAspect(theFontAspect))
      || (!aFontName.IsEmpty() && !aFontName.IsEqual(aFont->FontKey())))
  {
    TCollection_AsciiString aDesc = TCollection_AsciiString() + "'" + theFontName + "'"
                                    + TCollection_AsciiString() + " ["
                                    + Font_FontMgr::FontAspectToString(theFontAspect) + "]";
    Message::SendWarning(TCollection_AsciiString("Font_FontMgr, warning: unable to find font ")
                         + aDesc + "; " + aFont->ToString() + " is used instead");
  }
  return aFont;
}

occ::handle<Font_SystemFont> Font_FontMgr::Font_FontMap::Find(
  const TCollection_AsciiString& theFontName) const
{
  if (IsEmpty())
  {
    return occ::handle<Font_SystemFont>();
  }
  else if (theFontName.IsEmpty())
  {
    return FindKey(1);
  }
  occ::handle<Font_SystemFont> aTmpFont = new Font_SystemFont(theFontName);
  const int                    anInd    = FindIndex(aTmpFont);
  if (anInd > 0)
  {
    return FindKey(anInd);
  }
  return occ::handle<Font_SystemFont>();
}

occ::handle<NCollection_Buffer> Font_FontMgr::EmbedFallbackFont()
{
#ifdef HAVE_FREETYPE
  return new NCollection_Buffer(occ::handle<NCollection_BaseAllocator>(),
                                Font_DejavuSans_Latin_woff_size,
                                const_cast<uint8_t*>(Font_DejavuSans_Latin_woff));
#else
  return occ::handle<NCollection_Buffer>();
#endif
}
