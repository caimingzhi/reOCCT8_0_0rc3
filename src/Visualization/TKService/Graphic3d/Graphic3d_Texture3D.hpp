#pragma once

#include <Graphic3d_TextureMap.hpp>
#include <NCollection_Array1.hpp>

//! This abstract class for managing 3D textures.
class Graphic3d_Texture3D : public Graphic3d_TextureMap
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Texture3D, Graphic3d_TextureMap)
public:
  //! Creates a texture from a file.
  Standard_EXPORT Graphic3d_Texture3D(const TCollection_AsciiString& theFileName);

  //! Creates a texture from the pixmap.
  Standard_EXPORT Graphic3d_Texture3D(const occ::handle<Image_PixMap>& thePixMap);

  //! Creates a texture from a file.
  Standard_EXPORT Graphic3d_Texture3D(const NCollection_Array1<TCollection_AsciiString>& theFiles);

  //! Destructor.
  Standard_EXPORT ~Graphic3d_Texture3D() override;

  //! Assign new image to the texture.
  //! Note that this method does not invalidate already uploaded resources - consider calling
  //! ::UpdateRevision() if needed.
  Standard_EXPORT void SetImage(const occ::handle<Image_PixMap>& thePixMap);

  //! Load and return image.
  Standard_EXPORT occ::handle<Image_PixMap> GetImage(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

protected:
  NCollection_Array1<TCollection_AsciiString> myPaths;
};
