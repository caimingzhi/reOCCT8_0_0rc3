#pragma once

#include <Aspect_Window.hpp>

#if defined(_WIN32) && !defined(OCCT_UWP)

  #include <Aspect_Drawable.hpp>
  #include <Aspect_VKey.hpp>
  #include <Aspect_Handle.hpp>

  #ifndef __WINDOWS_H_INCLUDED
    #define __WINDOWS_H_INCLUDED
    #ifndef STRICT
      #define STRICT
    #endif
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>

    #ifdef DrawText
      #undef DrawText
    #endif

    #ifdef THIS
      #undef THIS
    #endif
  #endif

typedef DWORD WNT_Dword;

class Aspect_WindowInputListener;
class WNT_WClass;
typedef struct tagMSG MSG;

class WNT_Window : public Aspect_Window
{
  DEFINE_STANDARD_RTTIEXT(WNT_Window, Aspect_Window)
public:
  Standard_EXPORT static Aspect_VKey VirtualKeyFromNative(int theKey);

  Standard_EXPORT static Aspect_VKeyFlags MouseKeyFlagsFromEvent(WPARAM theKeys);

  Standard_EXPORT static Aspect_VKeyMouse MouseButtonsFromEvent(WPARAM theKeys);

  Standard_EXPORT static Aspect_VKeyFlags MouseKeyFlagsAsync();

  Standard_EXPORT static Aspect_VKeyMouse MouseButtonsAsync();

public:
  Standard_EXPORT WNT_Window(const char*                    theTitle,
                             const occ::handle<WNT_WClass>& theClass,
                             const WNT_Dword&               theStyle,
                             const int                      thePxLeft,
                             const int                      thePxTop,
                             const int                      thePxWidth,
                             const int                      thePxHeight,
                             const Quantity_NameOfColor     theBackColor = Quantity_NOC_MATRAGRAY,
                             const Aspect_Handle            theParent    = 0,
                             const Aspect_Handle            theMenu      = 0,
                             void* const                    theClientStruct = 0);

  Standard_EXPORT WNT_Window(const Aspect_Handle        theHandle,
                             const Quantity_NameOfColor theBackColor = Quantity_NOC_MATRAGRAY);

  Standard_EXPORT virtual ~WNT_Window();

  Standard_EXPORT void SetCursor(const Aspect_Handle theCursor) const;

  Standard_EXPORT virtual void Map() const override;

  Standard_EXPORT void Map(const int theMapMode) const;

  Standard_EXPORT virtual void Unmap() const override;

  Standard_EXPORT virtual Aspect_TypeOfResize DoResize() override;

  virtual bool DoMapping() const override { return true; }

  Standard_EXPORT void SetPos(const int X, const int Y, const int X1, const int Y1);

  Standard_EXPORT virtual bool IsMapped() const override;

  Standard_EXPORT virtual double Ratio() const override;

  Standard_EXPORT virtual void Position(int& X1, int& Y1, int& X2, int& Y2) const override;

  Standard_EXPORT virtual void Size(int& Width, int& Height) const override;

  virtual Aspect_Drawable NativeHandle() const override { return (Aspect_Drawable)myHWindow; }

  virtual Aspect_Drawable NativeParentHandle() const override
  {
    return (Aspect_Drawable)myHParentWindow;
  }

  virtual Aspect_FBConfig NativeFBConfig() const override { return NULL; }

  Standard_EXPORT virtual void SetTitle(const TCollection_AsciiString& theTitle) override;

  Standard_EXPORT virtual void InvalidateContent(
    const occ::handle<Aspect_DisplayConnection>& theDisp =
      occ::handle<Aspect_DisplayConnection>()) override;

public:
  Aspect_Handle HWindow() const { return myHWindow; }

  Aspect_Handle HParentWindow() const { return myHParentWindow; }

  enum RawInputMask
  {
    RawInputMask_Mouse      = 0x01,
    RawInputMask_SpaceMouse = 0x02,
  };

  Standard_EXPORT int RegisterRawInputDevices(unsigned int theRawDeviceMask);

  Standard_EXPORT virtual bool ProcessMessage(Aspect_WindowInputListener& theListener, MSG& theMsg);

private:
  class TouchInputHelper;

protected:
  occ::handle<WNT_WClass>       myWClass;
  occ::handle<TouchInputHelper> myTouchInputHelper;
  Aspect_Handle                 myHWindow;
  Aspect_Handle                 myHParentWindow;
  int                           myXLeft;
  int                           myYTop;
  int                           myXRight;
  int                           myYBottom;
  bool                          myIsForeign;
};

#endif
