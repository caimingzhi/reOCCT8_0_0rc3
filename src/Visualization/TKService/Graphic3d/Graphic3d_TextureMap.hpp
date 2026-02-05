#pragma once

#include <Graphic3d_TextureRoot.hpp>
#include <Graphic3d_TypeOfTexture.hpp>
#include <Graphic3d_LevelOfTextureAnisotropy.hpp>
class TCollection_AsciiString;

//! This is an abstract class for managing texture applicable on polygons.
class Graphic3d_TextureMap : public Graphic3d_TextureRoot
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_TextureMap, Graphic3d_TextureRoot)
public:
  //! enable texture smoothing
  Standard_EXPORT void EnableSmooth();

  //! Returns TRUE if the texture is smoothed.
  Standard_EXPORT bool IsSmoothed() const;

  //! disable texture smoothing
  Standard_EXPORT void DisableSmooth();

  //! enable texture modulate mode.
  //! the image is modulate with the shading of the surface.
  Standard_EXPORT void EnableModulate();

  //! disable texture modulate mode.
  //! the image is directly decal on the surface.
  Standard_EXPORT void DisableModulate();

  //! Returns TRUE if the texture is modulate.
  Standard_EXPORT bool IsModulate() const;

  //! use this methods if you want to enable
  //! texture repetition on your objects.
  Standard_EXPORT void EnableRepeat();

  //! use this methods if you want to disable
  //! texture repetition on your objects.
  Standard_EXPORT void DisableRepeat();

  //! Returns TRUE if the texture repeat is enable.
  Standard_EXPORT bool IsRepeat() const;

  //! @return level of anisotropy texture filter.
  //! Default value is Graphic3d_LOTA_OFF.
  Standard_EXPORT Graphic3d_LevelOfTextureAnisotropy AnisoFilter() const;

  //! @param theLevel level of anisotropy texture filter.
  Standard_EXPORT void SetAnisoFilter(const Graphic3d_LevelOfTextureAnisotropy theLevel);

protected:
  Standard_EXPORT Graphic3d_TextureMap(const TCollection_AsciiString& theFileName,
                                       const Graphic3d_TypeOfTexture  theType);

  Standard_EXPORT Graphic3d_TextureMap(const occ::handle<Image_PixMap>& thePixMap,
                                       const Graphic3d_TypeOfTexture    theType);
};
