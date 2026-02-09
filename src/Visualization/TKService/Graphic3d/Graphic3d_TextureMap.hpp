#pragma once

#include <Graphic3d_TextureRoot.hpp>
#include <Graphic3d_TypeOfTexture.hpp>
#include <Graphic3d_LevelOfTextureAnisotropy.hpp>
class TCollection_AsciiString;

class Graphic3d_TextureMap : public Graphic3d_TextureRoot
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_TextureMap, Graphic3d_TextureRoot)
public:
  Standard_EXPORT void EnableSmooth();

  Standard_EXPORT bool IsSmoothed() const;

  Standard_EXPORT void DisableSmooth();

  Standard_EXPORT void EnableModulate();

  Standard_EXPORT void DisableModulate();

  Standard_EXPORT bool IsModulate() const;

  Standard_EXPORT void EnableRepeat();

  Standard_EXPORT void DisableRepeat();

  Standard_EXPORT bool IsRepeat() const;

  Standard_EXPORT Graphic3d_LevelOfTextureAnisotropy AnisoFilter() const;

  Standard_EXPORT void SetAnisoFilter(const Graphic3d_LevelOfTextureAnisotropy theLevel);

protected:
  Standard_EXPORT Graphic3d_TextureMap(const TCollection_AsciiString& theFileName,
                                       const Graphic3d_TypeOfTexture  theType);

  Standard_EXPORT Graphic3d_TextureMap(const occ::handle<Image_PixMap>& thePixMap,
                                       const Graphic3d_TypeOfTexture    theType);
};
