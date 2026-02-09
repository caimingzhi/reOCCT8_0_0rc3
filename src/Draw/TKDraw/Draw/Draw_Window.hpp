#pragma once

#if defined(_WIN32)
  #include <windows.h>
#endif

#include <Aspect_Drawable.hpp>
#include <NCollection_Vec2.hpp>
#include <TCollection_AsciiString.hpp>

#include <memory>

const int MAXCOLOR = 15;

struct Draw_XSegment
{
  NCollection_Vec2<short> Points[2];

  NCollection_Vec2<short>& operator[](int theIndex) { return Points[theIndex]; }

  const NCollection_Vec2<short>& operator[](int theIndex) const { return Points[theIndex]; }

  void Init(int theXStart, int theYStart, int theXEnd, int theYEnd)
  {
    Points[0].SetValues((short)theXStart, (short)theYStart);
    Points[1].SetValues((short)theXEnd, (short)theYEnd);
  }
};

#if defined(_WIN32)

  #define DRAWCLASS L"DRAWWINDOW"
  #define DRAWTITLE L"Draw View"

enum console_semaphore_value
{
  STOP_CONSOLE,
  WAIT_CONSOLE_COMMAND,
  HAS_CONSOLE_COMMAND
};

extern console_semaphore_value volatile console_semaphore;

  #define DRAW_COMMAND_SIZE 1000
extern wchar_t console_command[DRAW_COMMAND_SIZE + 1];

Standard_EXPORT bool Init_Appli(HINSTANCE, HINSTANCE, int, HWND&);
Standard_EXPORT void Run_Appli(HWND);
Standard_EXPORT void Destroy_Appli(HINSTANCE);

#else

void Run_Appli(bool (*inteprete)(const char*));

bool Init_Appli();

void Destroy_Appli();

  #if defined(HAVE_XLIB)

typedef unsigned long Window;
typedef unsigned long Pixmap;
typedef unsigned long Drawable;

  #elif defined(__APPLE__)
    #ifdef __OBJC__
@class NSView;
@class NSWindow;
@class NSImage;
@class Draw_CocoaView;
    #else
struct NSView;
struct NSWindow;
struct NSImage;
struct Draw_CocoaView;
    #endif
  #endif

#endif

class Draw_Window
{
public:
  typedef void (*FCallbackBeforeTerminate)();

  Standard_EXPORT static void AddCallbackBeforeTerminate(FCallbackBeforeTerminate theCB);

  Standard_EXPORT static void RemoveCallbackBeforeTerminate(FCallbackBeforeTerminate theCB);

  Standard_EXPORT static bool DefineColor(const int theIndex, const char* theColorName);

  Standard_EXPORT static void Flush();

public:
  Standard_EXPORT virtual ~Draw_Window();

  Standard_EXPORT void GetPosition(int& thePosX, int& thePosY);

  Standard_EXPORT void SetPosition(int theNewXpos, int theNewYpos);

  Standard_EXPORT int HeightWin() const;

  Standard_EXPORT int WidthWin() const;

  Standard_EXPORT void SetDimension(int theNewDx, int theNewDy);

  Standard_EXPORT TCollection_AsciiString GetTitle() const;

  Standard_EXPORT void SetTitle(const TCollection_AsciiString& theTitle);

  Standard_EXPORT bool IsMapped() const;

  Standard_EXPORT void DisplayWindow();

  Standard_EXPORT void Hide();

  Standard_EXPORT void Destroy();

  Standard_EXPORT void Clear();

  bool GetUseBuffer() const { return myUseBuffer; }

  Standard_EXPORT void SetUseBuffer(bool theToUse);

  Standard_EXPORT void SetColor(int theColor);

  Standard_EXPORT void SetMode(int theMode);

  Standard_EXPORT void DrawString(int theX, int theY, const char* theText);

  Standard_EXPORT void DrawSegments(const Draw_XSegment* theSegments, int theNumberOfElements);

  Standard_EXPORT void Redraw();

  Standard_EXPORT bool Save(const char* theFileName) const;

  virtual void WExpose() = 0;

  Standard_EXPORT void InitBuffer();

protected:
  Standard_EXPORT Draw_Window(const char*                  theTitle,
                              const NCollection_Vec2<int>& theXY,
                              const NCollection_Vec2<int>& theSize,
                              Aspect_Drawable              theParent,
                              Aspect_Drawable              theWin);

  Standard_EXPORT void init(const NCollection_Vec2<int>& theXY,
                            const NCollection_Vec2<int>& theSize);

public:
#if defined(_WIN32)
  bool IsEqualWindows(HANDLE theWindow) { return myWindow == theWindow; }

  Standard_EXPORT static void SelectWait(HANDLE& theWindow, int& theX, int& theY, int& theButton);
  Standard_EXPORT static void SelectNoWait(HANDLE& theWindow, int& theX, int& theY, int& theButton);

  Standard_EXPORT static LRESULT APIENTRY DrawProc(HWND, UINT, WPARAM, LPARAM);
  static HWND                             hWndClientMDI;
#elif defined(HAVE_XLIB)
  bool IsEqualWindows(Window theWindow) { return myWindow == theWindow; }

  struct Draw_XEvent
  {
    int    type;
    Window window;
    int    button;
    int    x;
    int    y;
  };

  static void GetNextEvent(Draw_XEvent& theEvent);

  void Wait(bool theToWait = true);
#elif defined(__APPLE__)
  bool IsEqualWindows(const long theWindowNumber);

  static void GetNextEvent(bool  theWait,
                           long& theWindowNumber,
                           int&  theX,
                           int&  theY,
                           int&  theButton);
#endif

private:
#if defined(_WIN32)
  Standard_EXPORT static HWND createDrawWindow(HWND, int);
  Standard_EXPORT HDC         getMemDC(HDC theWinDC);
  Standard_EXPORT void        releaseMemDC(HDC theMemDC);
#elif defined(HAVE_XLIB)
  Drawable GetDrawable() const { return myUseBuffer ? myImageBuffer : myWindow; }
  struct Base_Window;
#endif

private:
#if defined(_WIN32)
  HWND    myWindow;
  HBITMAP myMemHbm;
  HBITMAP myOldHbm;
  int     myCurrPen;
  int     myCurrMode;
#elif defined(HAVE_XLIB)
  Window                       myWindow;
  Window                       myMother;
  Pixmap                       myImageBuffer;
  std::unique_ptr<Base_Window> myBase;
#elif defined(__APPLE__)
  NSWindow*       myWindow;
  Draw_CocoaView* myView;
  NSImage*        myImageBuffer;
#else
  Aspect_Drawable myWindow;
#endif
  int  myCurrentColor;
  bool myUseBuffer;
};
