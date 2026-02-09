#pragma once

#include <OpenGl_GlFunctions.hpp>

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
