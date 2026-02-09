#pragma once

#include <Graphic3d_Aspects.hpp>
#include <Graphic3d_TextureMap.hpp>

class OpenGl_Context;
class OpenGl_TextureSet;
class OpenGl_PointSprite;

class OpenGl_AspectsTextureSet
{
public:
  DEFINE_STANDARD_ALLOC
public:
  OpenGl_AspectsTextureSet()
      : myIsTextureReady(false)
  {
  }

  bool IsReady() const { return myIsTextureReady; }

  void Invalidate() { myIsTextureReady = false; }

  const occ::handle<OpenGl_TextureSet>& TextureSet(
    const occ::handle<OpenGl_Context>&     theCtx,
    const occ::handle<Graphic3d_Aspects>&  theAspect,
    const occ::handle<OpenGl_PointSprite>& theSprite,
    const occ::handle<OpenGl_PointSprite>& theSpriteA,
    bool                                   theToHighlight)
  {
    if (!myIsTextureReady)
    {
      build(theCtx, theAspect, theSprite, theSpriteA);
      myIsTextureReady = true;
    }
    return theToHighlight && !myTextures[1].IsNull() ? myTextures[1] : myTextures[0];
  }

  Standard_EXPORT void UpdateRediness(const occ::handle<Graphic3d_Aspects>& theAspect);

  Standard_EXPORT void Release(OpenGl_Context* theCtx);

private:
  Standard_EXPORT void build(const occ::handle<OpenGl_Context>&     theCtx,
                             const occ::handle<Graphic3d_Aspects>&  theAspect,
                             const occ::handle<OpenGl_PointSprite>& theSprite,
                             const occ::handle<OpenGl_PointSprite>& theSpriteA);

private:
  occ::handle<OpenGl_TextureSet> myTextures[2];
  bool                           myIsTextureReady;
};
