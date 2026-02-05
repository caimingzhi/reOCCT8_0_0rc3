#pragma once

#include <Standard.hpp>

#include <Graphic3d_NameOfTextureEnv.hpp>
#include <Graphic3d_TextureRoot.hpp>
#include <Standard_Integer.hpp>
class TCollection_AsciiString;

//! This class provides environment texture.
class Graphic3d_TextureEnv : public Graphic3d_TextureRoot
{

public:
  //! Creates an environment texture from a file.
  Standard_EXPORT Graphic3d_TextureEnv(const TCollection_AsciiString& theFileName);

  //! Creates an environment texture from a predefined texture name set.
  Standard_EXPORT Graphic3d_TextureEnv(const Graphic3d_NameOfTextureEnv theName);

  //! Creates an environment texture from the pixmap.
  Standard_EXPORT Graphic3d_TextureEnv(const occ::handle<Image_PixMap>& thePixMap);

  //! Returns the name of the predefined textures or NOT_ENV_UNKNOWN
  //! when the name is given as a filename.
  Standard_EXPORT Graphic3d_NameOfTextureEnv Name() const;

  //! Returns the number of predefined textures.
  Standard_EXPORT static int NumberOfTextures();

  //! Returns the name of the predefined texture of rank <aRank>
  Standard_EXPORT static TCollection_AsciiString TextureName(const int theRank);

  DEFINE_STANDARD_RTTIEXT(Graphic3d_TextureEnv, Graphic3d_TextureRoot)

private:
  Graphic3d_NameOfTextureEnv myName;
};
