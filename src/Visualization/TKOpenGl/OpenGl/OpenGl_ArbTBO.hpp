#pragma once

#include <OpenGl_GlFunctions.hpp>

struct OpenGl_ArbTBO : protected OpenGl_GlFunctions
{
  using OpenGl_GlFunctions::glTexBuffer;
};
