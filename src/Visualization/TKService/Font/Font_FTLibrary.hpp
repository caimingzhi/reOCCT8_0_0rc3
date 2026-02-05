#pragma once

#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

// forward declarations to avoid including of FreeType headers
typedef struct FT_LibraryRec_* FT_Library;

//! Wrapper over FT_Library. Provides access to FreeType library.
class Font_FTLibrary : public Standard_Transient
{

public:
  //! Initialize new FT_Library instance.
  Standard_EXPORT Font_FTLibrary();

  //! Release FT_Library instance.
  Standard_EXPORT ~Font_FTLibrary() override;

  //! This method should always return true.
  //! @return true if FT_Library instance is valid.
  bool IsValid() const { return myFTLib != nullptr; }

  //! Access FT_Library instance.
  FT_Library Instance() const { return myFTLib; }

private:
  FT_Library myFTLib;

private:
  Font_FTLibrary(const Font_FTLibrary&)            = delete;
  Font_FTLibrary& operator=(const Font_FTLibrary&) = delete;

public:
  DEFINE_STANDARD_RTTIEXT(Font_FTLibrary, Standard_Transient) // Type definition
};
