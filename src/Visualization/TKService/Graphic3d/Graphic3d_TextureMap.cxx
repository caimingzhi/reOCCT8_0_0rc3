#include <Graphic3d_TextureMap.hpp>
#include <Graphic3d_TextureParams.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_TextureMap, Graphic3d_TextureRoot)

Graphic3d_TextureMap::Graphic3d_TextureMap(const TCollection_AsciiString& theFileName,
                                           const Graphic3d_TypeOfTexture  theType)
    : Graphic3d_TextureRoot(theFileName, theType)
{
}

Graphic3d_TextureMap::Graphic3d_TextureMap(const occ::handle<Image_PixMap>& thePixMap,
                                           const Graphic3d_TypeOfTexture    theType)
    : Graphic3d_TextureRoot(thePixMap, theType)
{
}

void Graphic3d_TextureMap::EnableSmooth()
{
  myParams->SetFilter(Graphic3d_TOTF_TRILINEAR);
}

void Graphic3d_TextureMap::DisableSmooth()
{
  myParams->SetFilter(Graphic3d_TOTF_NEAREST);
}

bool Graphic3d_TextureMap::IsSmoothed() const
{
  return myParams->Filter() != Graphic3d_TOTF_NEAREST;
}

void Graphic3d_TextureMap::EnableModulate()
{
  myParams->SetModulate(true);
}

void Graphic3d_TextureMap::DisableModulate()
{
  myParams->SetModulate(false);
}

bool Graphic3d_TextureMap::IsModulate() const
{
  return myParams->IsModulate();
}

void Graphic3d_TextureMap::EnableRepeat()
{
  myParams->SetRepeat(true);
}

void Graphic3d_TextureMap::DisableRepeat()
{
  myParams->SetRepeat(false);
}

bool Graphic3d_TextureMap::IsRepeat() const
{
  return myParams->IsRepeat();
}

Graphic3d_LevelOfTextureAnisotropy Graphic3d_TextureMap::AnisoFilter() const
{
  return myParams->AnisoFilter();
}

void Graphic3d_TextureMap::SetAnisoFilter(const Graphic3d_LevelOfTextureAnisotropy theLevel)
{
  myParams->SetAnisoFilter(theLevel);
}
