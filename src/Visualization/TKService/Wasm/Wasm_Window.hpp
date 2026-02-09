#pragma once

#include <Aspect_Window.hpp>

#include <Aspect_VKey.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>

class Aspect_WindowInputListener;

struct EmscriptenMouseEvent;
struct EmscriptenWheelEvent;
struct EmscriptenTouchEvent;
struct EmscriptenKeyboardEvent;
struct EmscriptenUiEvent;
struct EmscriptenFocusEvent;

class Wasm_Window : public Aspect_Window
{
  DEFINE_STANDARD_RTTIEXT(Wasm_Window, Aspect_Window)
public:
  Standard_EXPORT static Aspect_VKeyMouse MouseButtonsFromNative(unsigned short theButtons);

  Standard_EXPORT static Aspect_VKey VirtualKeyFromNative(int theKey);

public:
  Standard_EXPORT Wasm_Window(const TCollection_AsciiString& theCanvasId,
                              const bool                     theToScaleBacking = true);

  Standard_EXPORT ~Wasm_Window() override;

  bool IsMapped() const override { return myIsMapped; }

  void Map() const override { myIsMapped = true; }

  void Unmap() const override { myIsMapped = false; }

  Standard_EXPORT Aspect_TypeOfResize DoResize() override;

  bool DoMapping() const override { return true; }

  Standard_EXPORT double Ratio() const override;

  Standard_EXPORT void Position(int& theX1, int& theY1, int& theX2, int& theY2) const override;

  Standard_EXPORT void Size(int& theWidth, int& theHeight) const override;

  Standard_EXPORT void SetSizeLogical(const NCollection_Vec2<double>& theSize);

  Standard_EXPORT void SetSizeBacking(const NCollection_Vec2<int>& theSize);

  const TCollection_AsciiString& CanvasId() const { return myCanvasId; }

  Aspect_Drawable NativeHandle() const override { return 0; }

  Aspect_Drawable NativeParentHandle() const override { return 0; }

  Aspect_FBConfig NativeFBConfig() const override { return nullptr; }

  double DevicePixelRatio() const override { return myDevicePixelRatio; }

  void SetDevicePixelRatio(double theDevicePixelRatio) { myDevicePixelRatio = theDevicePixelRatio; }

  Standard_EXPORT void InvalidateContent(
    const occ::handle<Aspect_DisplayConnection>& theDisp) override;

public:
  Standard_EXPORT virtual bool ProcessMessage(Aspect_WindowInputListener& theListener,
                                              int                         theEventType,
                                              const void*                 theEvent);

  Standard_EXPORT virtual bool ProcessMouseEvent(Aspect_WindowInputListener& theListener,
                                                 int                         theEventType,
                                                 const EmscriptenMouseEvent* theEvent);

  Standard_EXPORT virtual bool ProcessWheelEvent(Aspect_WindowInputListener& theListener,
                                                 int                         theEventType,
                                                 const EmscriptenWheelEvent* theEvent);

  Standard_EXPORT virtual bool ProcessTouchEvent(Aspect_WindowInputListener& theListener,
                                                 int                         theEventType,
                                                 const EmscriptenTouchEvent* theEvent);

  Standard_EXPORT virtual bool ProcessKeyEvent(Aspect_WindowInputListener&    theListener,
                                               int                            theEventType,
                                               const EmscriptenKeyboardEvent* theEvent);

  Standard_EXPORT virtual bool ProcessUiEvent(Aspect_WindowInputListener& theListener,
                                              int                         theEventType,
                                              const EmscriptenUiEvent*    theEvent);

  Standard_EXPORT virtual bool ProcessFocusEvent(Aspect_WindowInputListener& theListener,
                                                 int                         theEventType,
                                                 const EmscriptenFocusEvent* theEvent);

protected:
  TCollection_AsciiString myCanvasId;
  NCollection_Vec2<int>   mySize;
  double                  myDevicePixelRatio;
  bool                    myToScaleBacking;
  mutable bool            myIsMapped;
};
