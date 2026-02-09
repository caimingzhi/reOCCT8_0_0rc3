#pragma once

#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#endif

#ifndef APIENTRY
  #define APIENTRY
#endif
#ifndef APIENTRYP
  #define APIENTRYP APIENTRY*
#endif
#ifndef GLAPI
  #define GLAPI extern
#endif

#ifndef GL_APICALL
  #define GL_APICALL GLAPI
#endif

#ifndef GL_GLEXT_LEGACY
  #define GL_GLEXT_LEGACY
#endif
#ifndef GLX_GLXEXT_LEGACY
  #define GLX_GLXEXT_LEGACY
#endif

#if defined(__APPLE__)
  #import <TargetConditionals.h>

  #define GL_SILENCE_DEPRECATION
  #if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
    #include <OpenGLES/ES3/gl.h>
  #else
    #include <OpenGL/gl.h>
  #endif
  #define __X_GL_H
#elif defined(HAVE_GLES2) || defined(OCCT_UWP) || defined(__ANDROID__) || defined(__QNX__)         \
  || defined(__EMSCRIPTEN__)
  #if defined(_WIN32)

    #define GL_GLEXT_PROTOTYPES
  #endif
  #include <GLES3/gl3.h>
#else
  #include <GL/gl.h>
#endif
