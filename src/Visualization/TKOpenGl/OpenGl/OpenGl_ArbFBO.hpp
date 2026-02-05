#pragma once

#include <OpenGl_GlFunctions.hpp>

//! FBO is available on OpenGL 2.0+ hardware
struct OpenGl_ArbFBO : protected OpenGl_GlFunctions
{

  using OpenGl_GlFunctions::glBindFramebuffer;
  using OpenGl_GlFunctions::glBindRenderbuffer;
  using OpenGl_GlFunctions::glCheckFramebufferStatus;
  using OpenGl_GlFunctions::glDeleteFramebuffers;
  using OpenGl_GlFunctions::glDeleteRenderbuffers;
  using OpenGl_GlFunctions::glFramebufferRenderbuffer;
  using OpenGl_GlFunctions::glFramebufferTexture2D;
  using OpenGl_GlFunctions::glGenerateMipmap;
  using OpenGl_GlFunctions::glGenFramebuffers;
  using OpenGl_GlFunctions::glGenRenderbuffers;
  using OpenGl_GlFunctions::glGetFramebufferAttachmentParameteriv;
  using OpenGl_GlFunctions::glGetRenderbufferParameteriv;
  using OpenGl_GlFunctions::glIsFramebuffer;
  using OpenGl_GlFunctions::glIsRenderbuffer;
  using OpenGl_GlFunctions::glRenderbufferStorage;

#if !defined(GL_ES_VERSION_2_0)
  using OpenGl_GlFunctions::glBlitFramebuffer;
  using OpenGl_GlFunctions::glFramebufferTexture1D;
  using OpenGl_GlFunctions::glFramebufferTexture3D;
  using OpenGl_GlFunctions::glFramebufferTextureLayer;
  using OpenGl_GlFunctions::glRenderbufferStorageMultisample;
#endif
};

//! FBO blit is available in OpenGL 3.0+.
//! Moved out from OpenGl_ArbFBO since it is unavailable in OpenGL ES 2.0.
struct OpenGl_ArbFBOBlit : protected OpenGl_GlFunctions
{

  using OpenGl_GlFunctions::glBlitFramebuffer;
};
