#pragma once

#include <OpenGl_FrameBuffer.hpp>
#include <OpenGl_NamedResource.hpp>

class OpenGl_DepthPeeling : public OpenGl_NamedResource
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_DepthPeeling, OpenGl_NamedResource)
public:
  Standard_EXPORT OpenGl_DepthPeeling();

  Standard_EXPORT ~OpenGl_DepthPeeling() override;

  Standard_EXPORT void Release(OpenGl_Context* theGlCtx) override;

  Standard_EXPORT size_t EstimatedDataSize() const override;

  Standard_EXPORT void AttachDepthTexture(
    const occ::handle<OpenGl_Context>& theCtx,
    const occ::handle<OpenGl_Texture>& theDepthStencilTexture);

  Standard_EXPORT void DetachDepthTexture(const occ::handle<OpenGl_Context>& theCtx);

  const occ::handle<OpenGl_FrameBuffer>* DepthPeelFbosOit() const { return myDepthPeelFbosOit; }

  const occ::handle<OpenGl_FrameBuffer>* FrontBackColorFbosOit() const
  {
    return myFrontBackColorFbosOit;
  }

  const occ::handle<OpenGl_FrameBuffer>& BlendBackFboOit() const { return myBlendBackFboOit; }

private:
  occ::handle<OpenGl_FrameBuffer> myDepthPeelFbosOit[2];
  occ::handle<OpenGl_FrameBuffer> myFrontBackColorFbosOit[2];
  occ::handle<OpenGl_FrameBuffer> myBlendBackFboOit;
};
