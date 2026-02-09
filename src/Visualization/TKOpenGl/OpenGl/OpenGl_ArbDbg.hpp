#pragma once

#include <OpenGl_GlFunctions.hpp>

struct OpenGl_ArbDbg : protected OpenGl_GlFunctions
{
  using OpenGl_GlFunctions::glDebugMessageCallback;
  using OpenGl_GlFunctions::glDebugMessageControl;
  using OpenGl_GlFunctions::glDebugMessageInsert;
  using OpenGl_GlFunctions::glGetDebugMessageLog;
};
