#pragma once


#include <OpenGl_GlCore11.hpp>

//! OpenGL 1.2 core based on 1.1 version.
struct OpenGl_GlCore12 : public OpenGl_GlCore11Fwd
{
private:
  typedef OpenGl_GlCore11Fwd theBaseClass_t;

public: //! @name OpenGL 1.2 additives to 1.1
  using theBaseClass_t::glBlendColor;
  using theBaseClass_t::glBlendEquation;

#if !defined(GL_ES_VERSION_2_0)
  using theBaseClass_t::glCopyTexSubImage3D;
  using theBaseClass_t::glDrawRangeElements;
  using theBaseClass_t::glTexImage3D;
  using theBaseClass_t::glTexSubImage3D;
#endif
};

