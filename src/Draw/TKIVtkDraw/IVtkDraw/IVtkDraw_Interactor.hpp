#pragma once

#include <Standard.hpp>
#include <Standard_Macro.hpp>
#include <Standard_Transient.hpp>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <X11/X.h>
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
  #include <tcl.h>
#endif

// prevent disabling some MSVC warning messages by VTK headers
#include <Standard_WarningsDisable.hpp>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <Standard_WarningsRestore.hpp>

#include <IVtkTools_ShapePicker.hpp>
#include <IVtkDraw_HighlightAndSelectionPipeline.hpp>
#include <Aspect_Window.hpp>

class vtkWin32RenderWindowInteractor;
typedef vtkSmartPointer<IVtkTools_ShapePicker> PSelector;

class IVtkDraw_Interactor : public vtkRenderWindowInteractor
{
public:
  static IVtkDraw_Interactor* New();

  vtkTypeMacro(IVtkDraw_Interactor, vtkRenderWindowInteractor)

    void Initialize() override;
  void Enable() override;

  void Start() override {}

  const PSelector& Selector() const { return mySelector; }

  void                              SetShapePicker(const PSelector& theSelector);
  void                              SetPipelines(const occ::handle<ShapePipelineMap>& thePipelines);
  void                              SetOCCWindow(const occ::handle<Aspect_Window>& theWindow);
  const occ::handle<Aspect_Window>& GetOCCWindow() const;

  //! Process highlighting
  void MoveTo(int theX, int theY);

  //! Process selection
  void OnSelection();

  bool IsEnabled() const;

#ifndef _WIN32
  Display* GetDisplayId() const;
  int      ViewerMainLoop(int theArgNum, const char** theArgs);
#endif

protected:
  IVtkDraw_Interactor();
  ~IVtkDraw_Interactor() override;

#ifdef _WIN32
  friend LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
  friend LRESULT CALLBACK ViewerWindowProc(HWND                 hwnd,
                                           UINT                 Msg,
                                           WPARAM               wParam,
                                           LPARAM               lParam,
                                           IVtkDraw_Interactor* theInteractor);

  void OnMouseMove(HWND wnd, UINT nFlags, int X, int Y);
  void OnRButtonDown(HWND wnd, UINT nFlags, int X, int Y, int repeat = 0);
  void OnRButtonUp(HWND wnd, UINT nFlags, int X, int Y);
  void OnMButtonDown(HWND wnd, UINT nFlags, int X, int Y, int repeat = 0);
  void OnMButtonUp(HWND wnd, UINT nFlags, int X, int Y);
  void OnLButtonDown(HWND wnd, UINT nFlags, int X, int Y, int repeat = 0);
  void OnLButtonUp(HWND wnd, UINT nFlags, int X, int Y);
  void OnSize(HWND wnd, UINT nType, int X, int Y);
  void OnTimer(HWND wnd, UINT nIDEvent);
  void OnMouseWheelForward(HWND wnd, UINT nFlags, int X, int Y);
  void OnMouseWheelBackward(HWND wnd, UINT nFlags, int X, int Y);
#else
  static void ProcessEvents(ClientData theData, int);
  void        GetMousePosition(int* theX, int* theY) override;
#endif

private:
  // copying is prohibited
  IVtkDraw_Interactor(const IVtkDraw_Interactor&) = delete;
  void operator=(const IVtkDraw_Interactor&)      = delete;

private:
#ifdef _WIN32
  HWND myWindowId;
  int  myMouseInWindow;
#else
  Window   myWindowId;
  Display* myDisplayId;
  bool     myIsLeftButtonPressed;
#endif

  PSelector                     mySelector;
  occ::handle<ShapePipelineMap> myPipelines;
  occ::handle<Aspect_Window>    myWindow;
};
