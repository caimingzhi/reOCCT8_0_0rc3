#include <OpenGl_PointSprite.hpp>

#include <Graphic3d_TextureParams.hpp>
#include <OpenGl_Context.hpp>
#include <OpenGl_Sampler.hpp>
#include <Standard_Assert.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_PointSprite, OpenGl_Texture)

OpenGl_PointSprite::OpenGl_PointSprite(const TCollection_AsciiString& theResourceId)
    : OpenGl_Texture(theResourceId, occ::handle<Graphic3d_TextureParams>()),
      myBitmapList(0)
{

  mySampler->Parameters()->SetModulate(false);
  mySampler->Parameters()->SetGenMode(Graphic3d_TOTM_SPRITE,
                                      NCollection_Vec4<float>(0.0f, 0.0f, 0.0f, 0.0f),
                                      NCollection_Vec4<float>(0.0f, 0.0f, 0.0f, 0.0f));
}

OpenGl_PointSprite::~OpenGl_PointSprite()
{
  Release(nullptr);
}

void OpenGl_PointSprite::Release(OpenGl_Context* theGlCtx)
{
  if (myBitmapList != 0)
  {
    Standard_ASSERT_RETURN(
      theGlCtx != nullptr,
      "OpenGl_PointSprite destroyed without GL context! Possible GPU memory leakage...",
      Standard_VOID_RETURN);

    if (theGlCtx->IsValid())
    {
      theGlCtx->core11ffp->glDeleteLists(myBitmapList, 1);
    }
    myBitmapList = 0;
  }

  OpenGl_Texture::Release(theGlCtx);
}

void OpenGl_PointSprite::SetDisplayList(const occ::handle<OpenGl_Context>& theCtx,
                                        const GLuint                       theBitmapList)
{
  Release(theCtx.operator->());
  myBitmapList = theBitmapList;
}

void OpenGl_PointSprite::DrawBitmap(const occ::handle<OpenGl_Context>& theCtx) const
{
  if (myBitmapList != 0)
  {
    theCtx->core11ffp->glCallList(myBitmapList);
  }
}
