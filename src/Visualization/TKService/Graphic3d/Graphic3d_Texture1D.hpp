#pragma once

#include <Standard.hpp>

#include <Graphic3d_NameOfTexture1D.hpp>
#include <Graphic3d_TextureMap.hpp>
#include <Graphic3d_TypeOfTexture.hpp>
#include <Image_PixMap.hpp>
#include <Standard_Integer.hpp>
class TCollection_AsciiString;

class Graphic3d_Texture1D : public Graphic3d_TextureMap
{

public:
  Standard_EXPORT Graphic3d_NameOfTexture1D Name() const;

  Standard_EXPORT static int NumberOfTextures();

  Standard_EXPORT static TCollection_AsciiString TextureName(const int aRank);

  DEFINE_STANDARD_RTTIEXT(Graphic3d_Texture1D, Graphic3d_TextureMap)

protected:
  Standard_EXPORT Graphic3d_Texture1D(const TCollection_AsciiString& theFileName,
                                      const Graphic3d_TypeOfTexture  theType);

  Standard_EXPORT Graphic3d_Texture1D(const Graphic3d_NameOfTexture1D theName,
                                      const Graphic3d_TypeOfTexture   theType);

  Standard_EXPORT Graphic3d_Texture1D(const occ::handle<Image_PixMap>& thePixMap,
                                      const Graphic3d_TypeOfTexture    theType);

private:
  Graphic3d_NameOfTexture1D myName;
};
