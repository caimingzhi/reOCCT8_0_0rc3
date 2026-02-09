#include <Font_FTLibrary.hpp>

#ifdef HAVE_FREETYPE
  #include <ft2build.h>
  #include FT_FREETYPE_H
#endif

IMPLEMENT_STANDARD_RTTIEXT(Font_FTLibrary, Standard_Transient)

Font_FTLibrary::Font_FTLibrary()
    : myFTLib(nullptr)
{
#ifdef HAVE_FREETYPE
  if (FT_Init_FreeType(&myFTLib) != 0)
  {
    myFTLib = nullptr;
  }
#endif
}

Font_FTLibrary::~Font_FTLibrary()
{
  if (IsValid())
  {
#ifdef HAVE_FREETYPE
    FT_Done_FreeType(myFTLib);
#endif
  }
}
