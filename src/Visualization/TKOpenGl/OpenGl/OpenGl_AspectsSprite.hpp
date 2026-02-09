#pragma once

#include <Graphic3d_Aspects.hpp>
#include <Graphic3d_TextureMap.hpp>

class OpenGl_Context;
class OpenGl_PointSprite;

class OpenGl_AspectsSprite
{
public:
  DEFINE_STANDARD_ALLOC
public:
  OpenGl_AspectsSprite()
      : myMarkerSize(1.0f),
        myIsSpriteReady(false)
  {
  }

  float MarkerSize() const { return myMarkerSize; }

  bool IsReady() const { return myIsSpriteReady; }

  void Invalidate() { myIsSpriteReady = false; }

  Standard_EXPORT bool HasPointSprite(const occ::handle<OpenGl_Context>&    theCtx,
                                      const occ::handle<Graphic3d_Aspects>& theAspects);

  Standard_EXPORT bool IsDisplayListSprite(const occ::handle<OpenGl_Context>&    theCtx,
                                           const occ::handle<Graphic3d_Aspects>& theAspects);

  Standard_EXPORT const occ::handle<OpenGl_PointSprite>& Sprite(
    const occ::handle<OpenGl_Context>&    theCtx,
    const occ::handle<Graphic3d_Aspects>& theAspects,
    bool                                  theIsAlphaSprite);

  Standard_EXPORT void UpdateRediness(const occ::handle<Graphic3d_Aspects>& theAspect);

  Standard_EXPORT void Release(OpenGl_Context* theCtx);

private:
  Standard_EXPORT void build(const occ::handle<OpenGl_Context>&        theCtx,
                             const occ::handle<Graphic3d_MarkerImage>& theMarkerImage,
                             Aspect_TypeOfMarker                       theType,
                             float                                     theScale,
                             const NCollection_Vec4<float>&            theColor,
                             float&                                    theMarkerSize);

  static void spriteKeys(const occ::handle<Graphic3d_MarkerImage>& theMarkerImage,
                         Aspect_TypeOfMarker                       theType,
                         float                                     theScale,
                         const NCollection_Vec4<float>&            theColor,
                         TCollection_AsciiString&                  theKey,
                         TCollection_AsciiString&                  theKeyA);

private:
  occ::handle<OpenGl_PointSprite> mySprite;
  occ::handle<OpenGl_PointSprite> mySpriteA;
  float                           myMarkerSize;
  bool                            myIsSpriteReady;
};
