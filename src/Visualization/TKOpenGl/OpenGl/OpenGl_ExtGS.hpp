#pragma once

#include <OpenGl_GlFunctions.hpp>

//! Geometry shader as extension is available on OpenGL 2.0+
struct OpenGl_ExtGS : protected OpenGl_GlFunctions
{
#if !defined(GL_ES_VERSION_2_0)
  using OpenGl_GlFunctions::glProgramParameteriEXT;
#endif
};
