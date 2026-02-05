#pragma once

#include <Graphic3d_NameOfTexture2D.hpp>
#include <Graphic3d_TextureMap.hpp>

//! This abstract class for managing 2D textures
class Graphic3d_Texture2D : public Graphic3d_TextureMap
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Texture2D, Graphic3d_TextureMap)
public:
  //! Returns the number of predefined textures.
  Standard_EXPORT static int NumberOfTextures();

  //! Returns the name of the predefined texture of rank <aRank>
  Standard_EXPORT static TCollection_AsciiString TextureName(const int theRank);

public:
  //! Creates a texture from a file.
  //! MipMaps levels will be automatically generated if needed.
  Standard_EXPORT Graphic3d_Texture2D(const TCollection_AsciiString& theFileName);

  //! Creates a texture from a predefined texture name set.
  //! MipMaps levels will be automatically generated if needed.
  Standard_EXPORT Graphic3d_Texture2D(const Graphic3d_NameOfTexture2D theNOT);

  //! Creates a texture from the pixmap.
  //! MipMaps levels will be automatically generated if needed.
  Standard_EXPORT Graphic3d_Texture2D(const occ::handle<Image_PixMap>& thePixMap);

  //! Returns the name of the predefined textures or NOT_2D_UNKNOWN
  //! when the name is given as a filename.
  Standard_EXPORT Graphic3d_NameOfTexture2D Name() const;

  //! Assign new image to the texture.
  //! Note that this method does not invalidate already uploaded resources - consider calling
  //! ::UpdateRevision() if needed.
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
