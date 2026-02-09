#pragma once

#include <Graphic3d_TextureUnit.hpp>
#include <OpenGl_Buffer.hpp>

class OpenGl_TextureBuffer : public OpenGl_Buffer
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_TextureBuffer, OpenGl_Buffer)
public:
  static const unsigned int NO_TEXTURE = 0;

public:
  Standard_EXPORT OpenGl_TextureBuffer();

  Standard_EXPORT ~OpenGl_TextureBuffer() override;

  Standard_EXPORT unsigned int GetTarget() const override;

  bool IsValid() const { return OpenGl_Buffer::IsValid() && myTextureId != NO_TEXTURE; }

  Standard_EXPORT void Release(OpenGl_Context* theGlCtx) override;

  Standard_EXPORT bool Create(const occ::handle<OpenGl_Context>& theGlCtx) override;

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
                            const unsigned int                 theComponentsNb,
                            const int                          theElemsNb,
                            const float*                       theData);

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
                            const unsigned int                 theComponentsNb,
                            const int                          theElemsNb,
                            const unsigned int*                theData);

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
                            const unsigned int                 theComponentsNb,
                            const int                          theElemsNb,
                            const unsigned short*              theData);

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
                            const unsigned int                 theComponentsNb,
                            const int                          theElemsNb,
                            const uint8_t*                     theData);

  Standard_EXPORT void BindTexture(const occ::handle<OpenGl_Context>& theGlCtx,
                                   const Graphic3d_TextureUnit        theTextureUnit) const;

  Standard_EXPORT void UnbindTexture(const occ::handle<OpenGl_Context>& theGlCtx,
                                     const Graphic3d_TextureUnit        theTextureUnit) const;

  unsigned int TextureId() const { return myTextureId; }

  unsigned int TextureFormat() const { return myTexFormat; }

protected:
  unsigned int myTextureId;
  unsigned int myTexFormat;
};
