#pragma once


#include <OpenGl_GlFunctions.hpp>

//! TBO is available on OpenGL 3.0+ and OpenGL ES 3.2+ hardware
struct OpenGl_ArbTBO : protected OpenGl_GlFunctions
{
  using OpenGl_GlFunctions::glTexBuffer;
};

