#pragma once

#include <OpenGl_GlCore12.hpp>

struct OpenGl_GlCore13 : public OpenGl_GlCore12
{

public:
#if !defined(GL_ES_VERSION_2_0)
  using OpenGl_GlFunctions::glCompressedTexImage1D;
  using OpenGl_GlFunctions::glCompressedTexImage3D;
  using OpenGl_GlFunctions::glCompressedTexSubImage1D;
  using OpenGl_GlFunctions::glCompressedTexSubImage3D;
  using OpenGl_GlFunctions::glGetCompressedTexImage;
#endif

  using OpenGl_GlFunctions::glActiveTexture;
  using OpenGl_GlFunctions::glCompressedTexImage2D;
  using OpenGl_GlFunctions::glCompressedTexSubImage2D;
  using OpenGl_GlFunctions::glSampleCoverage;
};
