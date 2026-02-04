#pragma once


#include <OpenGl_GlFunctions.hpp>

//! Provides bindless textures.
//! This extension allows OpenGL applications to access texture objects in
//! shaders without first binding each texture to one of a limited number of
//! texture image units.
struct OpenGl_ArbTexBindless : protected OpenGl_GlFunctions
{
#if !defined(GL_ES_VERSION_2_0)
  using OpenGl_GlFunctions::glGetImageHandleARB;
  using OpenGl_GlFunctions::glGetTextureHandleARB;
  using OpenGl_GlFunctions::glGetTextureSamplerHandleARB;
  using OpenGl_GlFunctions::glGetVertexAttribLui64vARB;
  using OpenGl_GlFunctions::glIsImageHandleResidentARB;
  using OpenGl_GlFunctions::glIsTextureHandleResidentARB;
  using OpenGl_GlFunctions::glMakeImageHandleNonResidentARB;
  using OpenGl_GlFunctions::glMakeImageHandleResidentARB;
  using OpenGl_GlFunctions::glMakeTextureHandleNonResidentARB;
  using OpenGl_GlFunctions::glMakeTextureHandleResidentARB;
  using OpenGl_GlFunctions::glProgramUniformHandleui64ARB;
  using OpenGl_GlFunctions::glProgramUniformHandleui64vARB;
  using OpenGl_GlFunctions::glUniformHandleui64ARB;
  using OpenGl_GlFunctions::glUniformHandleui64vARB;
  using OpenGl_GlFunctions::glVertexAttribL1ui64ARB;
  using OpenGl_GlFunctions::glVertexAttribL1ui64vARB;
#endif
};

