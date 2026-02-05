#pragma once

#include <Graphic3d_Aspects.hpp>
#include <Graphic3d_TextureMap.hpp>

class OpenGl_Context;
class OpenGl_PointSprite;

//! OpenGl resources for custom point sprites.
class OpenGl_AspectsSprite
{
public:
  DEFINE_STANDARD_ALLOC
public:
  //! Empty constructor.
  OpenGl_AspectsSprite()
      : myMarkerSize(1.0f),
        myIsSpriteReady(false)
  {
  }

  float MarkerSize() const { return myMarkerSize; }

  //! Return TRUE if resource is up-to-date.
  bool IsReady() const { return myIsSpriteReady; }

  //! Invalidate resource state.
  void Invalidate() { myIsSpriteReady = false; }

  //! Return TRUE if OpenGl point sprite resource defines texture.
  Standard_EXPORT bool HasPointSprite(const occ::handle<OpenGl_Context>&    theCtx,
                                      const occ::handle<Graphic3d_Aspects>& theAspects);

  //! Return TRUE if OpenGl point sprite resource defined by obsolete Display List (bitmap).
  Standard_EXPORT bool IsDisplayListSprite(const occ::handle<OpenGl_Context>&    theCtx,
                                           const occ::handle<Graphic3d_Aspects>& theAspects);

  //! Return sprite.
  Standard_EXPORT const occ::handle<OpenGl_PointSprite>& Sprite(
    const occ::handle<OpenGl_Context>&    theCtx,
    const occ::handle<Graphic3d_Aspects>& theAspects,
    bool                                  theIsAlphaSprite);

  //! Update texture resource up-to-date state.
  Standard_EXPORT void UpdateRediness(const occ::handle<Graphic3d_Aspects>& theAspect);

  //! Release texture resource.
  Standard_EXPORT void Release(OpenGl_Context* theCtx);

private:
  //! Build texture resources.
  Standard_EXPORT void build(const occ::handle<OpenGl_Context>&        theCtx,
                             const occ::handle<Graphic3d_MarkerImage>& theMarkerImage,
                             Aspect_TypeOfMarker                       theType,
                             float                                     theScale,
                             const NCollection_Vec4<float>&            theColor,
                             float&                                    theMarkerSize);

  //! Generate resource keys for a sprite.
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
