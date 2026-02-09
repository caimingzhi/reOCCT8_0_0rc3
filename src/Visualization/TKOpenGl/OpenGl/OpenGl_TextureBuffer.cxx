#include <OpenGl_TextureBuffer.hpp>

#include <OpenGl_ArbTBO.hpp>
#include <OpenGl_GlCore20.hpp>
#include <OpenGl_Context.hpp>
#include <Standard_Assert.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_TextureBuffer, OpenGl_Buffer)

OpenGl_TextureBuffer::OpenGl_TextureBuffer()
    : myTextureId(NO_TEXTURE),
      myTexFormat(GL_RGBA32F)
{
}

OpenGl_TextureBuffer::~OpenGl_TextureBuffer()
{
  Release(nullptr);
}

unsigned int OpenGl_TextureBuffer::GetTarget() const
{
  return GL_TEXTURE_BUFFER;
}

void OpenGl_TextureBuffer::Release(OpenGl_Context* theGlCtx)
{
  if (myTextureId != NO_TEXTURE)
  {

    Standard_ASSERT_RETURN(
      theGlCtx != nullptr,
      "OpenGl_TextureBuffer destroyed without GL context! Possible GPU memory leakage...",
      Standard_VOID_RETURN);

    if (theGlCtx->IsValid())
    {
      theGlCtx->core20fwd->glDeleteTextures(1, &myTextureId);
    }
    myTextureId = NO_TEXTURE;
  }
  base_type::Release(theGlCtx);
}

bool OpenGl_TextureBuffer::Create(const occ::handle<OpenGl_Context>& theGlCtx)
{
  if (!base_type::Create(theGlCtx))
  {
    return false;
  }

  if (myTextureId == NO_TEXTURE)
  {
    theGlCtx->core20fwd->glGenTextures(1, &myTextureId);
  }
  return myTextureId != NO_TEXTURE;
}

bool OpenGl_TextureBuffer::Init(const occ::handle<OpenGl_Context>& theGlCtx,
                                const unsigned int                 theComponentsNb,
                                const int                          theElemsNb,
                                const float*                       theData)
{
  if (theGlCtx->arbTBO == nullptr)
  {
    return false;
  }
  else if (theComponentsNb < 1 || theComponentsNb > 4)
  {

    return false;
  }
  else if (theComponentsNb == 3 && !theGlCtx->arbTboRGB32)
  {
    return false;
  }
  else if (!Create(theGlCtx) || !base_type::Init(theGlCtx, theComponentsNb, theElemsNb, theData))
  {
    return false;
  }

  switch (theComponentsNb)
  {
    case 1:
      myTexFormat = GL_R32F;
      break;
    case 2:
      myTexFormat = GL_RG32F;
      break;
    case 3:
      myTexFormat = GL_RGB32F;
      break;
    case 4:
      myTexFormat = GL_RGBA32F;
      break;
  }

  Bind(theGlCtx);
  BindTexture(theGlCtx, Graphic3d_TextureUnit_0);
  theGlCtx->arbTBO->glTexBuffer(GetTarget(), myTexFormat, myBufferId);
  UnbindTexture(theGlCtx, Graphic3d_TextureUnit_0);
  Unbind(theGlCtx);
  return true;
}

bool OpenGl_TextureBuffer::Init(const occ::handle<OpenGl_Context>& theGlCtx,
                                const unsigned int                 theComponentsNb,
                                const int                          theElemsNb,
                                const unsigned int*                theData)
{
  if (theGlCtx->arbTBO == nullptr)
  {
    return false;
  }
  else if (theComponentsNb < 1 || theComponentsNb > 4)
  {

    return false;
  }
  else if (theComponentsNb == 3 && !theGlCtx->arbTboRGB32)
  {
    return false;
  }
  else if (!Create(theGlCtx) || !base_type::Init(theGlCtx, theComponentsNb, theElemsNb, theData))
  {
    return false;
  }

  switch (theComponentsNb)
  {
    case 1:
      myTexFormat = GL_R32I;
      break;
    case 2:
      myTexFormat = GL_RG32I;
      break;
    case 3:
      myTexFormat = GL_RGB32I;
      break;
    case 4:
      myTexFormat = GL_RGBA32I;
      break;
  }

  Bind(theGlCtx);
  BindTexture(theGlCtx, Graphic3d_TextureUnit_0);
  theGlCtx->arbTBO->glTexBuffer(GetTarget(), myTexFormat, myBufferId);
  UnbindTexture(theGlCtx, Graphic3d_TextureUnit_0);
  Unbind(theGlCtx);
  return true;
}

bool OpenGl_TextureBuffer::Init(const occ::handle<OpenGl_Context>& theGlCtx,
                                const unsigned int                 theComponentsNb,
                                const int                          theElemsNb,
                                const unsigned short*              theData)
{
  if (theGlCtx->arbTBO == nullptr)
  {
    return false;
  }
  else if (theComponentsNb < 1 || theComponentsNb > 4)
  {

    return false;
  }
  else if (!Create(theGlCtx) || !base_type::Init(theGlCtx, theComponentsNb, theElemsNb, theData))
  {
    return false;
  }

  switch (theComponentsNb)
  {
    case 1:
      myTexFormat = GL_R16I;
      break;
    case 2:
      myTexFormat = GL_RG16I;
      break;
    case 3:
      myTexFormat = GL_RGB16I;
      break;
    case 4:
      myTexFormat = GL_RGBA16I;
      break;
  }

  Bind(theGlCtx);
  BindTexture(theGlCtx, Graphic3d_TextureUnit_0);
  theGlCtx->arbTBO->glTexBuffer(GetTarget(), myTexFormat, myBufferId);
  UnbindTexture(theGlCtx, Graphic3d_TextureUnit_0);
  Unbind(theGlCtx);
  return true;
}

bool OpenGl_TextureBuffer::Init(const occ::handle<OpenGl_Context>& theGlCtx,
                                const unsigned int                 theComponentsNb,
                                const int                          theElemsNb,
                                const uint8_t*                     theData)
{
  if (theGlCtx->arbTBO == nullptr)
  {
    return false;
  }
  else if (theComponentsNb < 1 || theComponentsNb > 4)
  {

    return false;
  }
  else if (!Create(theGlCtx) || !base_type::Init(theGlCtx, theComponentsNb, theElemsNb, theData))
  {
    return false;
  }

  switch (theComponentsNb)
  {
    case 1:
      myTexFormat = GL_R8;
      break;
    case 2:
      myTexFormat = GL_RG8;
      break;
    case 3:
      myTexFormat = GL_RGB8;
      break;
    case 4:
      myTexFormat = GL_RGBA8;
      break;
  }

  Bind(theGlCtx);
  BindTexture(theGlCtx, Graphic3d_TextureUnit_0);
  theGlCtx->arbTBO->glTexBuffer(GetTarget(), myTexFormat, myBufferId);
  UnbindTexture(theGlCtx, Graphic3d_TextureUnit_0);
  Unbind(theGlCtx);
  return true;
}

void OpenGl_TextureBuffer::BindTexture(const occ::handle<OpenGl_Context>& theGlCtx,
                                       const Graphic3d_TextureUnit        theTextureUnit) const
{
  theGlCtx->core20fwd->glActiveTexture(GL_TEXTURE0 + theTextureUnit);
  theGlCtx->core20fwd->glBindTexture(GetTarget(), myTextureId);
}

void OpenGl_TextureBuffer::UnbindTexture(const occ::handle<OpenGl_Context>& theGlCtx,
                                         const Graphic3d_TextureUnit        theTextureUnit) const
{
  theGlCtx->core20fwd->glActiveTexture(GL_TEXTURE0 + theTextureUnit);
  theGlCtx->core20fwd->glBindTexture(GetTarget(), NO_TEXTURE);
}
