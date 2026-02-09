#pragma once

#include <Aspect_RenderingContext.hpp>
#include <Aspect_Window.hpp>
#include <OpenGl_GlCore11.hpp>
#include <OpenGl_Caps.hpp>
#include <Standard_Transient.hpp>

#if defined(__APPLE__)
  #import <TargetConditionals.h>
#endif

#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
  #ifdef __OBJC__
@class UIView;
  #else
struct UIView;
  #endif
#endif

class OpenGl_Context;
class OpenGl_GraphicDriver;

class OpenGl_Window : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_Window, Standard_Transient)
public:
  Standard_EXPORT OpenGl_Window();

  Standard_EXPORT void Init(const occ::handle<OpenGl_GraphicDriver>& theDriver,
                            const occ::handle<Aspect_Window>&        thePlatformWindow,
                            const occ::handle<Aspect_Window>&        theSizeWindow,
                            Aspect_RenderingContext                  theGContext,
                            const occ::handle<OpenGl_Caps>&          theCaps,
                            const occ::handle<OpenGl_Context>&       theShareCtx);

  Standard_EXPORT ~OpenGl_Window() override;

  Standard_EXPORT virtual void Resize();

  const occ::handle<Aspect_Window>& PlatformWindow() { return myPlatformWindow; }

  const occ::handle<Aspect_Window>& SizeWindow() { return mySizeWindow; }

  int Width() const { return mySize.x(); }

  int Height() const { return mySize.y(); }

  const occ::handle<OpenGl_Context>& GetGlContext() const { return myGlContext; }

  Standard_EXPORT virtual bool Activate();

  Standard_EXPORT void SetSwapInterval(bool theToForceNoSync);

protected:
  Standard_EXPORT void init();

protected:
  occ::handle<OpenGl_Context> myGlContext;

  bool myOwnGContext;

  occ::handle<Aspect_Window> myPlatformWindow;
  occ::handle<Aspect_Window> mySizeWindow;
#if defined(__APPLE__)
  #if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
  UIView* myUIView;
  #endif
  NCollection_Vec2<int> mySizePt;
#endif
  NCollection_Vec2<int> mySize;

  int mySwapInterval;
};
