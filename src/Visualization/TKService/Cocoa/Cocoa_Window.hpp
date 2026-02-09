#pragma once

#if defined(__APPLE__)
  #import <TargetConditionals.h>
#endif

#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
  #ifdef __OBJC__
@class UIView;
@class UIWindow;
  #else
struct UIView;
struct UIWindow;
  #endif
#else
  #ifdef __OBJC__
@class NSView;
@class NSWindow;
  #else
struct NSView;
struct NSWindow;
  #endif
#endif

#include <Aspect_Window.hpp>

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Aspect_FillMethod.hpp>
#include <Aspect_GradientFillMethod.hpp>
#include <Aspect_Handle.hpp>
#include <Aspect_TypeOfResize.hpp>
#include <Aspect_VKey.hpp>
#include <Quantity_NameOfColor.hpp>

class Aspect_WindowDefinitionError;
class Aspect_WindowError;
class Aspect_Background;
class Quantity_Color;
class Aspect_GradientBackground;

class Cocoa_Window : public Aspect_Window
{
public:
  Standard_EXPORT static Aspect_VKey VirtualKeyFromNative(int theKey);

public:
  Standard_EXPORT Cocoa_Window(const char* theTitle,
                               const int   thePxLeft,
                               const int   thePxTop,
                               const int   thePxWidth,
                               const int   thePxHeight);

#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE

  Standard_EXPORT Cocoa_Window(UIView* theViewUI);
#else

  Standard_EXPORT Cocoa_Window(NSView* theViewNS);
#endif

  Standard_EXPORT ~Cocoa_Window();

  Standard_EXPORT virtual void Map() const override;

  Standard_EXPORT virtual void Unmap() const override;

  Standard_EXPORT virtual Aspect_TypeOfResize DoResize() override;

  Standard_EXPORT virtual bool DoMapping() const override;

  Standard_EXPORT virtual bool IsMapped() const override;

  Standard_EXPORT virtual double Ratio() const override;

  Standard_EXPORT virtual void Position(int& X1, int& Y1, int& X2, int& Y2) const override;

  Standard_EXPORT virtual void Size(int& theWidth, int& theHeight) const override;

#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE

  UIView* HView() const { return myHView; }

  Standard_EXPORT void SetHView(UIView* theView);
#else

  NSView* HView() const { return myHView; }

  Standard_EXPORT void SetHView(NSView* theView);
#endif

  virtual Aspect_Drawable NativeHandle() const override { return (Aspect_Drawable)HView(); }

  virtual Aspect_Drawable NativeParentHandle() const override { return 0; }

  virtual Aspect_FBConfig NativeFBConfig() const override { return NULL; }

  Standard_EXPORT virtual void SetTitle(const TCollection_AsciiString& theTitle) override;

  Standard_EXPORT virtual void InvalidateContent(
    const occ::handle<Aspect_DisplayConnection>& theDisp = NULL) override;

protected:
#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
  UIView* myHView;
#else
  NSWindow* myHWindow;
  NSView*   myHView;
#endif
  int myXLeft;
  int myYTop;
  int myXRight;
  int myYBottom;

public:
  DEFINE_STANDARD_RTTIEXT(Cocoa_Window, Aspect_Window)
};
