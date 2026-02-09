#pragma once

#include <OpenGl_GlCore20.hpp>

struct OpenGl_GlCore21 : public OpenGl_GlCore20
{
private:
  typedef OpenGl_GlCore20 theBaseClass_t;

public:
#if !defined(GL_ES_VERSION_2_0)

  using theBaseClass_t::glUniformMatrix2x3fv;
  using theBaseClass_t::glUniformMatrix2x4fv;
  using theBaseClass_t::glUniformMatrix3x2fv;
  using theBaseClass_t::glUniformMatrix3x4fv;
  using theBaseClass_t::glUniformMatrix4x2fv;
  using theBaseClass_t::glUniformMatrix4x3fv;

#endif
};

struct OpenGl_GlCore30 : public OpenGl_GlCore21
{
private:
  typedef OpenGl_GlCore21 theBaseClass_t;

public:
  using theBaseClass_t::glBindFramebuffer;
  using theBaseClass_t::glBindRenderbuffer;
  using theBaseClass_t::glBlitFramebuffer;
  using theBaseClass_t::glCheckFramebufferStatus;
  using theBaseClass_t::glDeleteFramebuffers;
  using theBaseClass_t::glDeleteRenderbuffers;
  using theBaseClass_t::glFramebufferRenderbuffer;
  using theBaseClass_t::glFramebufferTexture2D;
  using theBaseClass_t::glFramebufferTextureLayer;
  using theBaseClass_t::glGenerateMipmap;
  using theBaseClass_t::glGenFramebuffers;
  using theBaseClass_t::glGenRenderbuffers;
  using theBaseClass_t::glGetFramebufferAttachmentParameteriv;
  using theBaseClass_t::glGetRenderbufferParameteriv;
  using theBaseClass_t::glIsFramebuffer;
  using theBaseClass_t::glIsRenderbuffer;
  using theBaseClass_t::glRenderbufferStorage;
  using theBaseClass_t::glRenderbufferStorageMultisample;
#if !defined(GL_ES_VERSION_2_0)
  using theBaseClass_t::glFramebufferTexture1D;
  using theBaseClass_t::glFramebufferTexture3D;
#endif

public:
  using theBaseClass_t::glBindVertexArray;
  using theBaseClass_t::glDeleteVertexArrays;
  using theBaseClass_t::glGenVertexArrays;
  using theBaseClass_t::glIsVertexArray;

public:
#ifndef __EMSCRIPTEN__
  using theBaseClass_t::glFlushMappedBufferRange;
  using theBaseClass_t::glMapBufferRange;
#endif

public:
  using theBaseClass_t::glBeginTransformFeedback;
  using theBaseClass_t::glBindBufferBase;
  using theBaseClass_t::glBindBufferRange;
  using theBaseClass_t::glClearBufferfi;
  using theBaseClass_t::glClearBufferfv;
  using theBaseClass_t::glClearBufferiv;
  using theBaseClass_t::glClearBufferuiv;
  using theBaseClass_t::glEndTransformFeedback;
  using theBaseClass_t::glGetBooleani_v;
  using theBaseClass_t::glGetFragDataLocation;
  using theBaseClass_t::glGetIntegeri_v;
  using theBaseClass_t::glGetStringi;
  using theBaseClass_t::glGetTransformFeedbackVarying;
  using theBaseClass_t::glGetUniformuiv;
  using theBaseClass_t::glGetVertexAttribIiv;
  using theBaseClass_t::glGetVertexAttribIuiv;
  using theBaseClass_t::glTransformFeedbackVaryings;
  using theBaseClass_t::glUniform1ui;
  using theBaseClass_t::glUniform1uiv;
  using theBaseClass_t::glUniform2ui;
  using theBaseClass_t::glUniform2uiv;
  using theBaseClass_t::glUniform3ui;
  using theBaseClass_t::glUniform3uiv;
  using theBaseClass_t::glUniform4ui;
  using theBaseClass_t::glUniform4uiv;
  using theBaseClass_t::glVertexAttribI4i;
  using theBaseClass_t::glVertexAttribI4iv;
  using theBaseClass_t::glVertexAttribI4ui;
  using theBaseClass_t::glVertexAttribI4uiv;
  using theBaseClass_t::glVertexAttribIPointer;

#if !defined(GL_ES_VERSION_2_0)

  using theBaseClass_t::glColorMaski;
  using theBaseClass_t::glDisablei;
  using theBaseClass_t::glEnablei;
  using theBaseClass_t::glIsEnabledi;

  using theBaseClass_t::glGetTexParameterIiv;
  using theBaseClass_t::glGetTexParameterIuiv;
  using theBaseClass_t::glTexParameterIiv;
  using theBaseClass_t::glTexParameterIuiv;
#endif

#if !defined(GL_ES_VERSION_2_0)

  using theBaseClass_t::glBeginConditionalRender;
  using theBaseClass_t::glBindFragDataLocation;
  using theBaseClass_t::glClampColor;
  using theBaseClass_t::glEndConditionalRender;
  using theBaseClass_t::glVertexAttribI1i;
  using theBaseClass_t::glVertexAttribI1iv;
  using theBaseClass_t::glVertexAttribI1ui;
  using theBaseClass_t::glVertexAttribI1uiv;
  using theBaseClass_t::glVertexAttribI2i;
  using theBaseClass_t::glVertexAttribI2iv;
  using theBaseClass_t::glVertexAttribI2ui;
  using theBaseClass_t::glVertexAttribI2uiv;
  using theBaseClass_t::glVertexAttribI3i;
  using theBaseClass_t::glVertexAttribI3iv;
  using theBaseClass_t::glVertexAttribI3ui;
  using theBaseClass_t::glVertexAttribI3uiv;
  using theBaseClass_t::glVertexAttribI4bv;
  using theBaseClass_t::glVertexAttribI4sv;
  using theBaseClass_t::glVertexAttribI4ubv;
  using theBaseClass_t::glVertexAttribI4usv;
#endif

#if defined(GL_ES_VERSION_2_0)

  using theBaseClass_t::glBeginQuery;
  using theBaseClass_t::glDeleteQueries;
  using theBaseClass_t::glEndQuery;
  using theBaseClass_t::glGenQueries;
  using theBaseClass_t::glGetQueryiv;
  using theBaseClass_t::glGetQueryObjectuiv;
  using theBaseClass_t::glIsQuery;
  #ifndef __EMSCRIPTEN__
  using theBaseClass_t::glUnmapBuffer;
  #endif
#endif
};
