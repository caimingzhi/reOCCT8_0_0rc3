#pragma once

#include <Aspect_Window.hpp>

#include <Aspect_VKey.hpp>

class Aspect_DisplayConnection;
class Aspect_WindowInputListener;

typedef union _XEvent XEvent;

class Xw_Window : public Aspect_Window
{
  DEFINE_STANDARD_RTTIEXT(Xw_Window, Aspect_Window)
public:
  Standard_EXPORT static Aspect_VKey VirtualKeyFromNative(unsigned long theKey);

public:
  Standard_EXPORT Xw_Window(const occ::handle<Aspect_DisplayConnection>& theXDisplay,
                            const char*                                  theTitle,
                            const int                                    thePxLeft,
                            const int                                    thePxTop,
                            const int                                    thePxWidth,
                            const int                                    thePxHeight);

  Standard_EXPORT Xw_Window(const occ::handle<Aspect_DisplayConnection>& theXDisplay,
                            const Aspect_Drawable                        theXWin,
                            const Aspect_FBConfig                        theFBConfig = nullptr);

  Standard_EXPORT ~Xw_Window() override;

  Standard_EXPORT void Map() const override;

  Standard_EXPORT void Unmap() const override;

  Standard_EXPORT Aspect_TypeOfResize DoResize() override;

  bool DoMapping() const override { return true; }

  Standard_EXPORT bool IsMapped() const override;

  Standard_EXPORT double Ratio() const override;

  Standard_EXPORT void Position(int& X1, int& Y1, int& X2, int& Y2) const override;

  Standard_EXPORT void Size(int& theWidth, int& theHeight) const override;

  Aspect_Drawable XWindow() const { return myXWindow; }

  Aspect_Drawable NativeHandle() const override { return myXWindow; }

  Aspect_Drawable NativeParentHandle() const override { return 0; }

  Aspect_FBConfig NativeFBConfig() const override { return myFBConfig; }

  Standard_EXPORT void SetTitle(const TCollection_AsciiString& theTitle) override;

  Standard_EXPORT void InvalidateContent(
    const occ::handle<Aspect_DisplayConnection>& theDisp) override;

  Standard_EXPORT virtual bool ProcessMessage(Aspect_WindowInputListener& theListener,
                                              XEvent&                     theMsg);

protected:
  Aspect_Drawable myXWindow;
  Aspect_FBConfig myFBConfig;
  int             myXLeft;
  int             myYTop;
  int             myXRight;
  int             myYBottom;

  bool myIsOwnWin;
};
