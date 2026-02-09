#pragma once

#include <Standard.hpp>

#include <Graphic3d_NameOfTextureEnv.hpp>
#include <Graphic3d_TextureRoot.hpp>
#include <Standard_Integer.hpp>
class TCollection_AsciiString;

class Graphic3d_TextureEnv : public Graphic3d_TextureRoot
{

public:
  Standard_EXPORT Graphic3d_TextureEnv(const TCollection_AsciiString& theFileName);

  Standard_EXPORT Graphic3d_TextureEnv(const Graphic3d_NameOfTextureEnv theName);

  Standard_EXPORT Graphic3d_TextureEnv(const occ::handle<Image_PixMap>& thePixMap);

  Standard_EXPORT Graphic3d_NameOfTextureEnv Name() const;

  Standard_EXPORT static int NumberOfTextures();

  Standard_EXPORT static TCollection_AsciiString TextureName(const int theRank);

  DEFINE_STANDARD_RTTIEXT(Graphic3d_TextureEnv, Graphic3d_TextureRoot)

private:
  Graphic3d_NameOfTextureEnv myName;
};
