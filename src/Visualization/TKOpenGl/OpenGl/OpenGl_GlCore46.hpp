#pragma once

#include <OpenGl_GlCore45.hpp>

//! OpenGL 4.6 definition.
struct OpenGl_GlCore46 : public OpenGl_GlCore45
{
private:
  typedef OpenGl_GlCore45 theBaseClass_t;

public: //! @name OpenGL 4.6 additives to 4.5
  using theBaseClass_t::glMultiDrawArraysIndirectCount;
  using theBaseClass_t::glMultiDrawElementsIndirectCount;
  using theBaseClass_t::glPolygonOffsetClamp;
  using theBaseClass_t::glSpecializeShader;
};
