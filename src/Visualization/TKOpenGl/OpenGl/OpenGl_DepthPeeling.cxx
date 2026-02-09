#include <OpenGl_DepthPeeling.hpp>

#include <OpenGl_ArbFBO.hpp>
#include <OpenGl_Context.hpp>
#include <OpenGl_Texture.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_DepthPeeling, OpenGl_NamedResource)

OpenGl_DepthPeeling::OpenGl_DepthPeeling()
    : OpenGl_NamedResource("depth_peeling")
{
  myDepthPeelFbosOit[0]      = new OpenGl_FrameBuffer(myResourceId + ":fbo0");
  myDepthPeelFbosOit[1]      = new OpenGl_FrameBuffer(myResourceId + ":fbo1");
  myFrontBackColorFbosOit[0] = new OpenGl_FrameBuffer(myResourceId + ":fbo0_color");
  myFrontBackColorFbosOit[1] = new OpenGl_FrameBuffer(myResourceId + ":fbo1_color");
  myBlendBackFboOit          = new OpenGl_FrameBuffer(myResourceId + ":fbo_blend");
}

OpenGl_DepthPeeling::~OpenGl_DepthPeeling()
{
  Release(nullptr);
}

void OpenGl_DepthPeeling::Release(OpenGl_Context* theCtx)
{
  myDepthPeelFbosOit[0]->Release(theCtx);
  myDepthPeelFbosOit[1]->Release(theCtx);
  myFrontBackColorFbosOit[0]->Release(theCtx);
  myFrontBackColorFbosOit[1]->Release(theCtx);
  myBlendBackFboOit->Release(theCtx);
}

size_t OpenGl_DepthPeeling::EstimatedDataSize() const
{
  return myDepthPeelFbosOit[0]->EstimatedDataSize() + myDepthPeelFbosOit[1]->EstimatedDataSize()
         + myFrontBackColorFbosOit[0]->EstimatedDataSize()
         + myFrontBackColorFbosOit[1]->EstimatedDataSize() + myBlendBackFboOit->EstimatedDataSize();
}

void OpenGl_DepthPeeling::AttachDepthTexture(
  const occ::handle<OpenGl_Context>& theCtx,
  const occ::handle<OpenGl_Texture>& theDepthStencilTexture)
{
  if (!theDepthStencilTexture.IsNull() && theDepthStencilTexture->IsValid())
  {
    for (int aPairIter = 0; aPairIter < 2; ++aPairIter)
    {
      myDepthPeelFbosOit[aPairIter]->BindBuffer(theCtx);
      theCtx->arbFBO->glFramebufferTexture2D(GL_FRAMEBUFFER,
                                             GL_DEPTH_STENCIL_ATTACHMENT,
                                             theDepthStencilTexture->GetTarget(),
                                             theDepthStencilTexture->TextureId(),
                                             0);
      myDepthPeelFbosOit[aPairIter]->UnbindBuffer(theCtx);
    }
  }
}

void OpenGl_DepthPeeling::DetachDepthTexture(const occ::handle<OpenGl_Context>& theCtx)
{
  if (!myDepthPeelFbosOit[0]->DepthStencilTexture().IsNull())
  {
    for (int aPairIter = 0; aPairIter < 2; ++aPairIter)
    {
      myDepthPeelFbosOit[aPairIter]->BindBuffer(theCtx);
      theCtx->arbFBO->glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        myDepthPeelFbosOit[aPairIter]->DepthStencilTexture()->GetTarget(),
        0,
        0);
      myDepthPeelFbosOit[aPairIter]->UnbindBuffer(theCtx);
    }
  }
}
