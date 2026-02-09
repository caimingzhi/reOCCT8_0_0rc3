#pragma once

#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

typedef struct FT_LibraryRec_* FT_Library;

class Font_FTLibrary : public Standard_Transient
{

public:
  Standard_EXPORT Font_FTLibrary();

  Standard_EXPORT ~Font_FTLibrary() override;

  bool IsValid() const { return myFTLib != nullptr; }

  FT_Library Instance() const { return myFTLib; }

private:
  FT_Library myFTLib;

private:
  Font_FTLibrary(const Font_FTLibrary&)            = delete;
  Font_FTLibrary& operator=(const Font_FTLibrary&) = delete;

public:
  DEFINE_STANDARD_RTTIEXT(Font_FTLibrary, Standard_Transient)
};
