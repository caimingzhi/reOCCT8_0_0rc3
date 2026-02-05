#pragma once

#include <OpenGl_FrameBuffer.hpp>
#include <OpenGl_NamedResource.hpp>

//! Class provides FBOs for dual depth peeling.
class OpenGl_DepthPeeling : public OpenGl_NamedResource
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_DepthPeeling, OpenGl_NamedResource)
public:
  //! Constructor.
  Standard_EXPORT OpenGl_DepthPeeling();

  //! Destructor.
  Standard_EXPORT ~OpenGl_DepthPeeling() override;

  //! Release OpenGL resources
  Standard_EXPORT void Release(OpenGl_Context* theGlCtx) override;

  //! Returns estimated GPU memory usage for holding data without considering overheads and
  //! allocation alignment rules.
  Standard_EXPORT size_t EstimatedDataSize() const override;

  //! Attach a texture image.
  //! Resets the active FBO to 0.
  Standard_EXPORT void AttachDepthTexture(
    const occ::handle<OpenGl_Context>& theCtx,
    const occ::handle<OpenGl_Texture>& theDepthStencilTexture);

  //! Detach a texture image.
  //! Resets the active FBO to 0.
  Standard_EXPORT void DetachDepthTexture(const occ::handle<OpenGl_Context>& theCtx);

  //! Returns additional buffers for ping-pong
  const occ::handle<OpenGl_FrameBuffer>* DepthPeelFbosOit() const { return myDepthPeelFbosOit; }

  //! Returns additional buffers for ping-pong
  const occ::handle<OpenGl_FrameBuffer>* FrontBackColorFbosOit() const
  {
    return myFrontBackColorFbosOit;
  }

  //! Returns additional FBO for depth peeling
  const occ::handle<OpenGl_FrameBuffer>& BlendBackFboOit() const { return myBlendBackFboOit; }

private:
  occ::handle<OpenGl_FrameBuffer> myDepthPeelFbosOit[2];      //!< depth + front color + back color
  occ::handle<OpenGl_FrameBuffer> myFrontBackColorFbosOit[2]; //!< front color + back color
  occ::handle<OpenGl_FrameBuffer> myBlendBackFboOit;
};
