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

//! This class represents low-level wrapper over window with GL context.
//! The window itself should be provided to constructor.
class OpenGl_Window : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_Window, Standard_Transient)
public:
  //! Empty constructor.
  Standard_EXPORT OpenGl_Window();

  //! Initialize the new window - prepare GL context for specified window.
  //! Throws exception in case of failure.
  Standard_EXPORT void Init(const occ::handle<OpenGl_GraphicDriver>& theDriver,
                            const occ::handle<Aspect_Window>&        thePlatformWindow,
                            const occ::handle<Aspect_Window>&        theSizeWindow,
                            Aspect_RenderingContext                  theGContext,
                            const occ::handle<OpenGl_Caps>&          theCaps,
                            const occ::handle<OpenGl_Context>&       theShareCtx);

  //! Destructor
  Standard_EXPORT ~OpenGl_Window() override;

  //! Resizes the window.
  Standard_EXPORT virtual void Resize();

  //! Return platform window.
  const occ::handle<Aspect_Window>& PlatformWindow() { return myPlatformWindow; }

  //! Return window object defining dimensions.
  const occ::handle<Aspect_Window>& SizeWindow() { return mySizeWindow; }

  int Width() const { return mySize.x(); }

  int Height() const { return mySize.y(); }

  //! Return OpenGL context.
  const occ::handle<OpenGl_Context>& GetGlContext() const { return myGlContext; }

  //! Makes GL context for this window active in current thread
  Standard_EXPORT virtual bool Activate();

  //! Sets swap interval for this window according to the context's settings.
  Standard_EXPORT void SetSwapInterval(bool theToForceNoSync);

protected:
  //! Activates GL context and setup viewport.
  Standard_EXPORT void init();

protected:
  occ::handle<OpenGl_Context> myGlContext;
  // clang-format off
  bool       myOwnGContext;    //!< set to TRUE if GL context was not created by this class
  // clang-format on
  occ::handle<Aspect_Window> myPlatformWindow; //!< software platform window wrapper
  occ::handle<Aspect_Window> mySizeWindow;     //!< window object defining dimensions
#if defined(__APPLE__)
  #if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
  UIView* myUIView;
  #endif
  NCollection_Vec2<int> mySizePt; //!< window width x height in logical units
#endif
  NCollection_Vec2<int> mySize; //!< window width x height in pixels

  int mySwapInterval; //!< last assigned swap interval (VSync) for this window
};
