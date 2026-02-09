#pragma once

#include <OpenGl_GlFunctions.hpp>

struct OpenGl_ExtGS : protected OpenGl_GlFunctions
{
#if !defined(GL_ES_VERSION_2_0)
  using OpenGl_GlFunctions::glProgramParameteriEXT;
#endif
};
