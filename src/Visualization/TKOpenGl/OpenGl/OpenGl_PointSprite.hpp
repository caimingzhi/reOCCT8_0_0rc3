#pragma once


#include <OpenGl_Texture.hpp>

//! Point sprite resource. On modern hardware it will be texture with extra parameters.
//! On ancient hardware sprites will be drawn using bitmaps.
class OpenGl_PointSprite : public OpenGl_Texture
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_PointSprite, OpenGl_Texture)
public:
  //! Create uninitialized resource.
  Standard_EXPORT OpenGl_PointSprite(const TCollection_AsciiString& theResourceId);

  //! Destroy object.
  Standard_EXPORT ~OpenGl_PointSprite() override;

  //! Destroy object - will release GPU memory if any.
  Standard_EXPORT void Release(OpenGl_Context* theCtx) override;

  //! Returns TRUE for point sprite texture.
  bool IsPointSprite() const override { return true; }

  //! @return true if current object was initialized
  bool IsValid() const override { return myBitmapList != 0 || myTextureId != NO_TEXTURE; }

  //! @return true if this is display list bitmap
  inline bool IsDisplayList() const { return myBitmapList != 0; }

  //! Draw sprite using glBitmap.
  //! Please call glRasterPos3fv() before to setup sprite position.
  Standard_EXPORT void DrawBitmap(const occ::handle<OpenGl_Context>& theCtx) const;

  //! Initialize point sprite as display list
  Standard_EXPORT void SetDisplayList(const occ::handle<OpenGl_Context>& theCtx,
                                      const GLuint                       theBitmapList);

protected:
  // clang-format off
  GLuint myBitmapList; //!< if of display list to draw sprite using glBitmap (for backward compatibility)
  // clang-format on
};

