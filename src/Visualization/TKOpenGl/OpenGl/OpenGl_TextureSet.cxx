#include <OpenGl_TextureSet.hpp>

#include <OpenGl_Texture.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_TextureSet, Standard_Transient)

OpenGl_TextureSet::OpenGl_TextureSet(const occ::handle<OpenGl_Texture>& theTexture)
    : myTextures(0, 0),
      myTextureSetBits(Graphic3d_TextureSetBits_NONE)
{
  if (!theTexture.IsNull())
  {
    myTextures.ChangeFirst().Texture = theTexture;
    myTextures.ChangeFirst().Unit    = theTexture->Sampler()->Parameters()->TextureUnit();
  }
}

bool OpenGl_TextureSet::IsModulate() const
{
  return myTextures.IsEmpty() || myTextures.First().Texture.IsNull()
         || myTextures.First().Texture->Sampler()->Parameters()->IsModulate();
}

bool OpenGl_TextureSet::HasNonPointSprite() const
{
  if (myTextures.IsEmpty())
  {
    return false;
  }
  else if (myTextures.Size() == 1)
  {
    return !myTextures.First().Texture.IsNull() && !myTextures.First().Texture->IsPointSprite();
  }
  return !myTextures.First().Texture.IsNull();
}

bool OpenGl_TextureSet::HasPointSprite() const
{
  return !myTextures.IsEmpty() && !myTextures.Last().Texture.IsNull()
         && myTextures.Last().Texture->IsPointSprite();
}
