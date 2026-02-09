#pragma once

#include <OpenGl_GlCore30.hpp>

struct OpenGl_GlCore31 : public OpenGl_GlCore30
{
private:
  typedef OpenGl_GlCore30 theBaseClass_t;

public:
  using theBaseClass_t::glGetActiveUniformBlockiv;
  using theBaseClass_t::glGetActiveUniformBlockName;
  using theBaseClass_t::glGetActiveUniformsiv;
  using theBaseClass_t::glGetUniformBlockIndex;
  using theBaseClass_t::glGetUniformIndices;
  using theBaseClass_t::glUniformBlockBinding;
#if !defined(GL_ES_VERSION_2_0)
  using theBaseClass_t::glGetActiveUniformName;
#endif

public:
  using theBaseClass_t::glCopyBufferSubData;

public:
  using theBaseClass_t::glDrawArraysInstanced;
  using theBaseClass_t::glDrawElementsInstanced;
#if !defined(GL_ES_VERSION_2_0)
  using theBaseClass_t::glPrimitiveRestartIndex;
  using theBaseClass_t::glTexBuffer;
#endif
};

struct OpenGl_GlCore32 : public OpenGl_GlCore31
{
private:
  typedef OpenGl_GlCore31 theBaseClass_t;

public:
  using theBaseClass_t::glDrawElementsBaseVertex;
  using theBaseClass_t::glDrawElementsInstancedBaseVertex;
  using theBaseClass_t::glDrawRangeElementsBaseVertex;
  using theBaseClass_t::glMultiDrawElementsBaseVertex;

public:
  using theBaseClass_t::glProvokingVertex;

public:
  using theBaseClass_t::glClientWaitSync;
  using theBaseClass_t::glDeleteSync;
  using theBaseClass_t::glFenceSync;
  using theBaseClass_t::glGetInteger64v;
  using theBaseClass_t::glGetSynciv;
  using theBaseClass_t::glIsSync;
  using theBaseClass_t::glWaitSync;

public:
  using theBaseClass_t::glGetMultisamplefv;
  using theBaseClass_t::glSampleMaski;
  using theBaseClass_t::glTexImage2DMultisample;
  using theBaseClass_t::glTexImage3DMultisample;

public:
  using theBaseClass_t::glFramebufferTexture;
  using theBaseClass_t::glGetBufferParameteri64v;
  using theBaseClass_t::glGetInteger64i_v;
};
