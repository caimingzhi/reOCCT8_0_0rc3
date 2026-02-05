#pragma once

#include <Standard_Macro.hpp>

#if defined(__APPLE__) && !defined(HAVE_XLIB)
  #import <TargetConditionals.h>
  #if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
    #ifdef __OBJC__
@class EAGLContext;
    #else
struct EAGLContext;
    #endif
typedef EAGLContext* Aspect_RenderingContext;
  #else
    #ifdef __OBJC__
@class NSOpenGLContext;
    #else
struct NSOpenGLContext;
    #endif
Standard_DISABLE_DEPRECATION_WARNINGS typedef NSOpenGLContext* Aspect_RenderingContext;
Standard_ENABLE_DEPRECATION_WARNINGS
  #endif
#else
typedef void* Aspect_RenderingContext; // GLXContext under UNIX
#endif
