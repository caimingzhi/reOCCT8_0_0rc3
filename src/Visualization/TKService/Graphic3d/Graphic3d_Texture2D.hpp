#pragma once

#include <Graphic3d_NameOfTexture2D.hpp>
#include <Graphic3d_TextureMap.hpp>

class Graphic3d_Texture2D : public Graphic3d_TextureMap
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Texture2D, Graphic3d_TextureMap)
public:
  Standard_EXPORT static int NumberOfTextures();

  Standard_EXPORT static TCollection_AsciiString TextureName(const int theRank);

public:
  Standard_EXPORT Graphic3d_Texture2D(const TCollection_AsciiString& theFileName);

  Standard_EXPORT Graphic3d_Texture2D(const Graphic3d_NameOfTexture2D theNOT);

  Standard_EXPORT Graphic3d_Texture2D(const occ::handle<Image_PixMap>& thePixMap);

  Standard_EXPORT Graphic3d_NameOfTexture2D Name() const;

  Standard_EXPORT void SetImage(const occ::handle<Image_PixMap>& thePixMap);

protected:
  Standard_EXPORT Graphic3d_Texture2D(const TCollection_AsciiString& theFileName,
                                      const Graphic3d_TypeOfTexture  theType);

  Standard_EXPORT Graphic3d_Texture2D(const Graphic3d_NameOfTexture2D theName,
                                      const Graphic3d_TypeOfTexture   theType);

  Standard_EXPORT Graphic3d_Texture2D(const occ::handle<Image_PixMap>& thePixMap,
                                      const Graphic3d_TypeOfTexture    theType);

protected:
  Graphic3d_NameOfTexture2D myName;
};
