#pragma once

#include <OpenGl_Texture.hpp>

class OpenGl_PointSprite : public OpenGl_Texture
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_PointSprite, OpenGl_Texture)
public:
  Standard_EXPORT OpenGl_PointSprite(const TCollection_AsciiString& theResourceId);

  Standard_EXPORT ~OpenGl_PointSprite() override;

  Standard_EXPORT void Release(OpenGl_Context* theCtx) override;

  bool IsPointSprite() const override { return true; }

  bool IsValid() const override { return myBitmapList != 0 || myTextureId != NO_TEXTURE; }

  inline bool IsDisplayList() const { return myBitmapList != 0; }

  Standard_EXPORT void DrawBitmap(const occ::handle<OpenGl_Context>& theCtx) const;

  Standard_EXPORT void SetDisplayList(const occ::handle<OpenGl_Context>& theCtx,
                                      const GLuint                       theBitmapList);

protected:
  GLuint myBitmapList;
};
