#pragma once

// Created on: 2014-03-17
// Created by: Kirill GAVRILOV
// Copyright (c) 2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

// Created on: 2014-03-17
// Created by: Kirill GAVRILOV
// Copyright (c) 2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

// Created on: 2014-03-17
// Created by: Kirill GAVRILOV
// Copyright (c) 2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

// Created on: 2014-03-17
// Created by: Kirill GAVRILOV
// Copyright (c) 2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

// Created on: 2014-03-17
// Created by: Kirill GAVRILOV
// Copyright (c) 2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.


#include <OpenGl_GlCore32.hpp>

//! OpenGL 3.3 definition.
struct OpenGl_GlCore33 : public OpenGl_GlCore32
{
private:
  typedef OpenGl_GlCore32 theBaseClass_t;

public: //! @name GL_ARB_blend_func_extended (added to OpenGL 3.3 core)
  using theBaseClass_t::glBindFragDataLocationIndexed;
  using theBaseClass_t::glGetFragDataIndex;

public: //! @name GL_ARB_sampler_objects (added to OpenGL 3.3 core)
  using theBaseClass_t::glBindSampler;
  using theBaseClass_t::glDeleteSamplers;
  using theBaseClass_t::glGenSamplers;
  using theBaseClass_t::glGetSamplerParameterfv;
  using theBaseClass_t::glGetSamplerParameterIiv;
  using theBaseClass_t::glGetSamplerParameterIuiv;
  using theBaseClass_t::glGetSamplerParameteriv;
  using theBaseClass_t::glIsSampler;
  using theBaseClass_t::glSamplerParameterf;
  using theBaseClass_t::glSamplerParameterfv;
  using theBaseClass_t::glSamplerParameteri;
  using theBaseClass_t::glSamplerParameterIiv;
  using theBaseClass_t::glSamplerParameterIuiv;
  using theBaseClass_t::glSamplerParameteriv;

public: //! @name GL_ARB_timer_query (added to OpenGL 3.3 core)
  using theBaseClass_t::glGetQueryObjecti64v;
  using theBaseClass_t::glGetQueryObjectui64v;
  using theBaseClass_t::glQueryCounter;

public: //! @name GL_ARB_vertex_type_2_10_10_10_rev (added to OpenGL 3.3 core)
  using theBaseClass_t::glVertexAttribP1ui;
  using theBaseClass_t::glVertexAttribP1uiv;
  using theBaseClass_t::glVertexAttribP2ui;
  using theBaseClass_t::glVertexAttribP2uiv;
  using theBaseClass_t::glVertexAttribP3ui;
  using theBaseClass_t::glVertexAttribP3uiv;
  using theBaseClass_t::glVertexAttribP4ui;
  using theBaseClass_t::glVertexAttribP4uiv;

public: //! @name OpenGL 3.3 additives to 3.2
  using theBaseClass_t::glVertexAttribDivisor;
};



//! OpenGL 4.0 definition.
struct OpenGl_GlCore40 : public OpenGl_GlCore33
{
private:
  typedef OpenGl_GlCore33 theBaseClass_t;

public: //! @name GL_ARB_draw_indirect (added to OpenGL 4.0 core)
  using theBaseClass_t::glDrawArraysIndirect;
  using theBaseClass_t::glDrawElementsIndirect;

public: //! @name GL_ARB_gpu_shader_fp64 (added to OpenGL 4.0 core)
  using theBaseClass_t::glGetUniformdv;
  using theBaseClass_t::glUniform1d;
  using theBaseClass_t::glUniform1dv;
  using theBaseClass_t::glUniform2d;
  using theBaseClass_t::glUniform2dv;
  using theBaseClass_t::glUniform3d;
  using theBaseClass_t::glUniform3dv;
  using theBaseClass_t::glUniform4d;
  using theBaseClass_t::glUniform4dv;
  using theBaseClass_t::glUniformMatrix2dv;
  using theBaseClass_t::glUniformMatrix2x3dv;
  using theBaseClass_t::glUniformMatrix2x4dv;
  using theBaseClass_t::glUniformMatrix3dv;
  using theBaseClass_t::glUniformMatrix3x2dv;
  using theBaseClass_t::glUniformMatrix3x4dv;
  using theBaseClass_t::glUniformMatrix4dv;
  using theBaseClass_t::glUniformMatrix4x2dv;
  using theBaseClass_t::glUniformMatrix4x3dv;

public: //! @name GL_ARB_shader_subroutine (added to OpenGL 4.0 core)
  using theBaseClass_t::glGetActiveSubroutineName;
  using theBaseClass_t::glGetActiveSubroutineUniformiv;
  using theBaseClass_t::glGetActiveSubroutineUniformName;
  using theBaseClass_t::glGetProgramStageiv;
  using theBaseClass_t::glGetSubroutineIndex;
  using theBaseClass_t::glGetSubroutineUniformLocation;
  using theBaseClass_t::glGetUniformSubroutineuiv;
  using theBaseClass_t::glUniformSubroutinesuiv;

public: //! @name GL_ARB_tessellation_shader (added to OpenGL 4.0 core)
  using theBaseClass_t::glPatchParameterfv;
  using theBaseClass_t::glPatchParameteri;

public: //! @name GL_ARB_transform_feedback2 (added to OpenGL 4.0 core)
  using theBaseClass_t::glBindTransformFeedback;
  using theBaseClass_t::glDeleteTransformFeedbacks;
  using theBaseClass_t::glDrawTransformFeedback;
  using theBaseClass_t::glGenTransformFeedbacks;
  using theBaseClass_t::glIsTransformFeedback;
  using theBaseClass_t::glPauseTransformFeedback;
  using theBaseClass_t::glResumeTransformFeedback;

public: //! @name GL_ARB_transform_feedback3 (added to OpenGL 4.0 core)
  using theBaseClass_t::glBeginQueryIndexed;
  using theBaseClass_t::glDrawTransformFeedbackStream;
  using theBaseClass_t::glEndQueryIndexed;
  using theBaseClass_t::glGetQueryIndexediv;

public: //! @name OpenGL 4.0 additives to 3.3
  using theBaseClass_t::glBlendEquationi;
  using theBaseClass_t::glBlendEquationSeparatei;
  using theBaseClass_t::glBlendFunci;
  using theBaseClass_t::glBlendFuncSeparatei;
  using theBaseClass_t::glMinSampleShading;
};



//! OpenGL 4.1 definition.
struct OpenGl_GlCore41 : public OpenGl_GlCore40
{
private:
  typedef OpenGl_GlCore40 theBaseClass_t;

public: //! @name GL_ARB_ES2_compatibility (added to OpenGL 4.1 core)
  using theBaseClass_t::glClearDepthf;
  using theBaseClass_t::glDepthRangef;
  using theBaseClass_t::glGetShaderPrecisionFormat;
  using theBaseClass_t::glReleaseShaderCompiler;
  using theBaseClass_t::glShaderBinary;

public: //! @name GL_ARB_get_program_binary (added to OpenGL 4.1 core)
  using theBaseClass_t::glGetProgramBinary;
  using theBaseClass_t::glProgramBinary;
  using theBaseClass_t::glProgramParameteri;

public: //! @name GL_ARB_separate_shader_objects (added to OpenGL 4.1 core)
  using theBaseClass_t::glActiveShaderProgram;
  using theBaseClass_t::glBindProgramPipeline;
  using theBaseClass_t::glCreateShaderProgramv;
  using theBaseClass_t::glDeleteProgramPipelines;
  using theBaseClass_t::glGenProgramPipelines;
  using theBaseClass_t::glGetProgramPipelineInfoLog;
  using theBaseClass_t::glGetProgramPipelineiv;
  using theBaseClass_t::glIsProgramPipeline;
  using theBaseClass_t::glProgramUniform1d;
  using theBaseClass_t::glProgramUniform1dv;
  using theBaseClass_t::glProgramUniform1f;
  using theBaseClass_t::glProgramUniform1fv;
  using theBaseClass_t::glProgramUniform1i;
  using theBaseClass_t::glProgramUniform1iv;
  using theBaseClass_t::glProgramUniform1ui;
  using theBaseClass_t::glProgramUniform1uiv;
  using theBaseClass_t::glProgramUniform2d;
  using theBaseClass_t::glProgramUniform2dv;
  using theBaseClass_t::glProgramUniform2f;
  using theBaseClass_t::glProgramUniform2fv;
  using theBaseClass_t::glProgramUniform2i;
  using theBaseClass_t::glProgramUniform2iv;
  using theBaseClass_t::glProgramUniform2ui;
  using theBaseClass_t::glProgramUniform2uiv;
  using theBaseClass_t::glProgramUniform3d;
  using theBaseClass_t::glProgramUniform3dv;
  using theBaseClass_t::glProgramUniform3f;
  using theBaseClass_t::glProgramUniform3fv;
  using theBaseClass_t::glProgramUniform3i;
  using theBaseClass_t::glProgramUniform3iv;
  using theBaseClass_t::glProgramUniform3ui;
  using theBaseClass_t::glProgramUniform3uiv;
  using theBaseClass_t::glProgramUniform4d;
  using theBaseClass_t::glProgramUniform4dv;
  using theBaseClass_t::glProgramUniform4f;
  using theBaseClass_t::glProgramUniform4fv;
  using theBaseClass_t::glProgramUniform4i;
  using theBaseClass_t::glProgramUniform4iv;
  using theBaseClass_t::glProgramUniform4ui;
  using theBaseClass_t::glProgramUniform4uiv;
  using theBaseClass_t::glProgramUniformMatrix2dv;
  using theBaseClass_t::glProgramUniformMatrix2fv;
  using theBaseClass_t::glProgramUniformMatrix2x3dv;
  using theBaseClass_t::glProgramUniformMatrix2x3fv;
  using theBaseClass_t::glProgramUniformMatrix2x4dv;
  using theBaseClass_t::glProgramUniformMatrix2x4fv;
  using theBaseClass_t::glProgramUniformMatrix3dv;
  using theBaseClass_t::glProgramUniformMatrix3fv;
  using theBaseClass_t::glProgramUniformMatrix3x2dv;
  using theBaseClass_t::glProgramUniformMatrix3x2fv;
  using theBaseClass_t::glProgramUniformMatrix3x4dv;
  using theBaseClass_t::glProgramUniformMatrix3x4fv;
  using theBaseClass_t::glProgramUniformMatrix4dv;
  using theBaseClass_t::glProgramUniformMatrix4fv;
  using theBaseClass_t::glProgramUniformMatrix4x2dv;
  using theBaseClass_t::glProgramUniformMatrix4x2fv;
  using theBaseClass_t::glProgramUniformMatrix4x3dv;
  using theBaseClass_t::glProgramUniformMatrix4x3fv;
  using theBaseClass_t::glUseProgramStages;
  using theBaseClass_t::glValidateProgramPipeline;

public: //! @name GL_ARB_vertex_attrib_64bit (added to OpenGL 4.1 core)
  using theBaseClass_t::glGetVertexAttribLdv;
  using theBaseClass_t::glVertexAttribL1d;
  using theBaseClass_t::glVertexAttribL1dv;
  using theBaseClass_t::glVertexAttribL2d;
  using theBaseClass_t::glVertexAttribL2dv;
  using theBaseClass_t::glVertexAttribL3d;
  using theBaseClass_t::glVertexAttribL3dv;
  using theBaseClass_t::glVertexAttribL4d;
  using theBaseClass_t::glVertexAttribL4dv;
  using theBaseClass_t::glVertexAttribLPointer;

public: //! @name GL_ARB_viewport_array (added to OpenGL 4.1 core)
  using theBaseClass_t::glDepthRangeArrayv;
  using theBaseClass_t::glDepthRangeIndexed;
  using theBaseClass_t::glGetDoublei_v;
  using theBaseClass_t::glGetFloati_v;
  using theBaseClass_t::glScissorArrayv;
  using theBaseClass_t::glScissorIndexed;
  using theBaseClass_t::glScissorIndexedv;
  using theBaseClass_t::glViewportArrayv;
  using theBaseClass_t::glViewportIndexedf;
  using theBaseClass_t::glViewportIndexedfv;
};



//! OpenGL 4.2 definition.
struct OpenGl_GlCore42 : public OpenGl_GlCore41
{
private:
  typedef OpenGl_GlCore41 theBaseClass_t;

public: //! @name GL_ARB_base_instance (added to OpenGL 4.2 core)
  using theBaseClass_t::glDrawArraysInstancedBaseInstance;
  using theBaseClass_t::glDrawElementsInstancedBaseInstance;
  using theBaseClass_t::glDrawElementsInstancedBaseVertexBaseInstance;

public: //! @name GL_ARB_transform_feedback_instanced (added to OpenGL 4.2 core)
  using theBaseClass_t::glDrawTransformFeedbackInstanced;
  using theBaseClass_t::glDrawTransformFeedbackStreamInstanced;

public: //! @name GL_ARB_internalformat_query (added to OpenGL 4.2 core)
  using theBaseClass_t::glGetInternalformativ;

public: //! @name GL_ARB_shader_atomic_counters (added to OpenGL 4.2 core)
  using theBaseClass_t::glGetActiveAtomicCounterBufferiv;

public: //! @name GL_ARB_shader_image_load_store (added to OpenGL 4.2 core)
  using theBaseClass_t::glBindImageTexture;
  using theBaseClass_t::glMemoryBarrier;

public: //! @name GL_ARB_texture_storage (added to OpenGL 4.2 core)
  using theBaseClass_t::glTexStorage1D;
  using theBaseClass_t::glTexStorage2D;
  using theBaseClass_t::glTexStorage3D;
};



//! OpenGL 4.3 definition.
struct OpenGl_GlCore43 : public OpenGl_GlCore42
{
private:
  typedef OpenGl_GlCore42 theBaseClass_t;

public: //! @name OpenGL 4.3 additives to 4.2
  using theBaseClass_t::glBindVertexBuffer;
  using theBaseClass_t::glClearBufferData;
  using theBaseClass_t::glClearBufferSubData;
  using theBaseClass_t::glCopyImageSubData;
  using theBaseClass_t::glDebugMessageCallback;
  using theBaseClass_t::glDebugMessageControl;
  using theBaseClass_t::glDebugMessageInsert;
  using theBaseClass_t::glDispatchCompute;
  using theBaseClass_t::glDispatchComputeIndirect;
  using theBaseClass_t::glFramebufferParameteri;
  using theBaseClass_t::glGetDebugMessageLog;
  using theBaseClass_t::glGetFramebufferParameteriv;
  using theBaseClass_t::glGetInternalformati64v;
  using theBaseClass_t::glGetObjectLabel;
  using theBaseClass_t::glGetObjectPtrLabel;
  using theBaseClass_t::glGetProgramInterfaceiv;
  using theBaseClass_t::glGetProgramResourceIndex;
  using theBaseClass_t::glGetProgramResourceiv;
  using theBaseClass_t::glGetProgramResourceLocation;
  using theBaseClass_t::glGetProgramResourceLocationIndex;
  using theBaseClass_t::glGetProgramResourceName;
  using theBaseClass_t::glInvalidateBufferData;
  using theBaseClass_t::glInvalidateBufferSubData;
  using theBaseClass_t::glInvalidateFramebuffer;
  using theBaseClass_t::glInvalidateSubFramebuffer;
  using theBaseClass_t::glInvalidateTexImage;
  using theBaseClass_t::glInvalidateTexSubImage;
  using theBaseClass_t::glMultiDrawArraysIndirect;
  using theBaseClass_t::glMultiDrawElementsIndirect;
  using theBaseClass_t::glObjectLabel;
  using theBaseClass_t::glObjectPtrLabel;
  using theBaseClass_t::glPopDebugGroup;
  using theBaseClass_t::glPushDebugGroup;
  using theBaseClass_t::glShaderStorageBlockBinding;
  using theBaseClass_t::glTexBufferRange;
  using theBaseClass_t::glTexStorage2DMultisample;
  using theBaseClass_t::glTexStorage3DMultisample;
  using theBaseClass_t::glTextureView;
  using theBaseClass_t::glVertexAttribBinding;
  using theBaseClass_t::glVertexAttribFormat;
  using theBaseClass_t::glVertexAttribIFormat;
  using theBaseClass_t::glVertexAttribLFormat;
  using theBaseClass_t::glVertexBindingDivisor;
};



//! OpenGL 4.4 definition.
struct OpenGl_GlCore44 : public OpenGl_GlCore43
{
private:
  typedef OpenGl_GlCore43 theBaseClass_t;

public: //! @name OpenGL 4.4 additives to 4.3
  using theBaseClass_t::glBindBuffersBase;
  using theBaseClass_t::glBindBuffersRange;
  using theBaseClass_t::glBindImageTextures;
  using theBaseClass_t::glBindSamplers;
  using theBaseClass_t::glBindTextures;
  using theBaseClass_t::glBindVertexBuffers;
  using theBaseClass_t::glBufferStorage;
  using theBaseClass_t::glClearTexImage;
  using theBaseClass_t::glClearTexSubImage;
};

