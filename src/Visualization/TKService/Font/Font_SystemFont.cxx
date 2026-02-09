#include <Font_SystemFont.hpp>

#include <Font_FontMgr.hpp>
#include <OSD_Path.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Font_SystemFont, Standard_Transient)

Font_SystemFont::Font_SystemFont(const TCollection_AsciiString& theFontName)
    : myFontKey(theFontName),
      myFontName(theFontName),
      myIsSingleLine(false)
{
  memset(myFaceIds, 0, sizeof(myFaceIds));
  if (theFontName.IsEmpty())
  {
    throw Standard_ProgramError("Font_SystemFont constructor called with empty font name");
  }
  myFontKey.LowerCase();
}

void Font_SystemFont::SetFontPath(Font_FontAspect                theAspect,
                                  const TCollection_AsciiString& thePath,
                                  const int                      theFaceId)
{
  if (theAspect == Font_FontAspect_UNDEFINED)
  {
    throw Standard_ProgramError("Font_SystemFont::SetFontPath() called with UNDEFINED aspect");
  }
  myFilePaths[theAspect] = thePath;
  myFaceIds[theAspect]   = theFaceId;
}

bool Font_SystemFont::IsEqual(const occ::handle<Font_SystemFont>& theOtherFont) const
{
  return theOtherFont.get() == this || myFontKey.IsEqual(theOtherFont->myFontKey);
}

TCollection_AsciiString Font_SystemFont::ToString() const
{
  TCollection_AsciiString aDesc;
  aDesc += TCollection_AsciiString() + "'" + myFontName + "'";

  bool isFirstAspect = true;
  aDesc += " [aspects: ";
  for (int anAspectIter = 0; anAspectIter < Font_FontAspect_NB; ++anAspectIter)
  {
    if (!HasFontAspect((Font_FontAspect)anAspectIter))
    {
      continue;
    }

    if (!isFirstAspect)
    {
      aDesc += ",";
    }
    else
    {
      isFirstAspect = false;
    }
    aDesc += Font_FontMgr::FontAspectToString((Font_FontAspect)anAspectIter);
  }
  aDesc += "]";

  isFirstAspect = true;
  aDesc += " [paths: ";
  for (int anAspectIter = 0; anAspectIter < Font_FontAspect_NB; ++anAspectIter)
  {
    if (!HasFontAspect((Font_FontAspect)anAspectIter))
    {
      continue;
    }

    if (!isFirstAspect)
    {
      aDesc += ";";
    }
    else
    {
      isFirstAspect = false;
    }
    aDesc += FontPath((Font_FontAspect)anAspectIter);
    if (FontFaceId((Font_FontAspect)anAspectIter) != 0)
    {
      aDesc = aDesc + "," + FontFaceId((Font_FontAspect)anAspectIter);
    }
  }
  aDesc += "]";
  return aDesc;
}
