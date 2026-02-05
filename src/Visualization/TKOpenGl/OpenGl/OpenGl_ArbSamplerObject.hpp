#pragma once

#include <OpenGl_GlFunctions.hpp>

//! Provide Sampler Object functionality (texture parameters stored independently from texture
//! itself). Available since OpenGL 3.3+ (GL_ARB_sampler_objects extension) and OpenGL ES 3.0+.
struct OpenGl_ArbSamplerObject : protected OpenGl_GlFunctions
{
  using OpenGl_GlFunctions::glBindSampler;
  using OpenGl_GlFunctions::glDeleteSamplers;
  using OpenGl_GlFunctions::glGenSamplers;
  using OpenGl_GlFunctions::glGetSamplerParameterfv;
  using OpenGl_GlFunctions::glGetSamplerParameteriv;
  using OpenGl_GlFunctions::glIsSampler;
  using OpenGl_GlFunctions::glSamplerParameterf;
  using OpenGl_GlFunctions::glSamplerParameterfv;
  using OpenGl_GlFunctions::glSamplerParameteri;
  using OpenGl_GlFunctions::glSamplerParameteriv;

#if !defined(GL_ES_VERSION_2_0)
  using OpenGl_GlFunctions::glGetSamplerParameterIiv;
  using OpenGl_GlFunctions::glGetSamplerParameterIuiv;
  using OpenGl_GlFunctions::glSamplerParameterIiv;
  using OpenGl_GlFunctions::glSamplerParameterIuiv;
#endif
};
