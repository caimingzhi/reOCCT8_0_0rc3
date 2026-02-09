#pragma once

#include <OpenGl_GlFunctions.hpp>

struct OpenGl_ArbIns : protected OpenGl_GlFunctions
{
  using OpenGl_GlFunctions::glDrawArraysInstanced;
  using OpenGl_GlFunctions::glDrawElementsInstanced;
};
