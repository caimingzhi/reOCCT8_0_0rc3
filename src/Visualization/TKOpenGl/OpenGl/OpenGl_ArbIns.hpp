#pragma once


#include <OpenGl_GlFunctions.hpp>

//! Instancing is available on OpenGL 3.0+ hardware
//! (in core since OpenGL 3.1 or GL_ARB_draw_instanced extension).
//!
//! Note that this structure does not include glVertexAttribDivisor(),
//! which has been introduced in later OpenGL versions (OpenGL 3.3 or OpenGL ES 3.0).
struct OpenGl_ArbIns : protected OpenGl_GlFunctions
{
  using OpenGl_GlFunctions::glDrawArraysInstanced;
  using OpenGl_GlFunctions::glDrawElementsInstanced;
};

