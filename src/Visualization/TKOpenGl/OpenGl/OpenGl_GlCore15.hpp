// Created on: 2012-03-06
// Created by: Kirill GAVRILOV
// Copyright (c) 2012-2014 OPEN CASCADE SAS
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

#ifndef OpenGl_GlCore15_HeaderFile
#define OpenGl_GlCore15_HeaderFile
// Created on: 2012-03-06
// Created by: Kirill GAVRILOV
// Copyright (c) 2012-2014 OPEN CASCADE SAS
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

#ifndef OpenGl_GlCore14_HeaderFile
#define OpenGl_GlCore14_HeaderFile

#include <OpenGl_GlCore13.hpp>

//! OpenGL 1.4 core based on 1.3 version.
struct OpenGl_GlCore14 : public OpenGl_GlCore13
{
private:
  typedef OpenGl_GlCore13 theBaseClass_t;

public: //! @name OpenGL 1.4 additives to 1.3
  using theBaseClass_t::glBlendFuncSeparate;
  using theBaseClass_t::glMultiDrawElements;

#if !defined(GL_ES_VERSION_2_0)
  using theBaseClass_t::glMultiDrawArrays;
  using theBaseClass_t::glPointParameterf;
  using theBaseClass_t::glPointParameterfv;
  using theBaseClass_t::glPointParameteri;
  using theBaseClass_t::glPointParameteriv;
#endif
};

#endif // _OpenGl_GlCore14_Header


//! OpenGL 1.5 core based on 1.4 version.
struct OpenGl_GlCore15 : public OpenGl_GlCore14
{
private:
  typedef OpenGl_GlCore14 theBaseClass_t;

public: //! @name OpenGL 1.5 additives to 1.4
#if !defined(GL_ES_VERSION_2_0)
  using theBaseClass_t::glBeginQuery;
  using theBaseClass_t::glDeleteQueries;
  using theBaseClass_t::glEndQuery;
  using theBaseClass_t::glGenQueries;
  using theBaseClass_t::glGetQueryiv;
  using theBaseClass_t::glGetQueryObjectiv;
  using theBaseClass_t::glGetQueryObjectuiv;
  using theBaseClass_t::glIsQuery;

  using theBaseClass_t::glGetBufferPointerv;
  using theBaseClass_t::glGetBufferSubData;
  using theBaseClass_t::glMapBuffer;
  using theBaseClass_t::glUnmapBuffer;
#endif

  using theBaseClass_t::glBindBuffer;
  using theBaseClass_t::glBufferData;
  using theBaseClass_t::glBufferSubData;
  using theBaseClass_t::glDeleteBuffers;
  using theBaseClass_t::glGenBuffers;
  using theBaseClass_t::glGetBufferParameteriv;
  using theBaseClass_t::glIsBuffer;
};

#endif // _OpenGl_GlCore15_Header
