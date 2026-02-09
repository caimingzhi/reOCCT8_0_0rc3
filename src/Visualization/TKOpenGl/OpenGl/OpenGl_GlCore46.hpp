#pragma once

#include <OpenGl_GlCore45.hpp>

struct OpenGl_GlCore46 : public OpenGl_GlCore45
{
private:
  typedef OpenGl_GlCore45 theBaseClass_t;

public:
  using theBaseClass_t::glMultiDrawArraysIndirectCount;
  using theBaseClass_t::glMultiDrawElementsIndirectCount;
  using theBaseClass_t::glPolygonOffsetClamp;
  using theBaseClass_t::glSpecializeShader;
};
