#ifdef _WIN32
  #include <windows.h>
#endif

#include <Draw_Window.hpp>

#include <Aspect_DisplayConnection.hpp>
#include <Draw_Appli.hpp>
#include <Draw_Interpretor.hpp>
#include <Image_AlienPixMap.hpp>
#include <Message.hpp>
#include <NCollection_List.hpp>
#include <OSD.hpp>
#include <OSD_Timer.hpp>
#include <Standard_ErrorHandler.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>

#include <tcl.h>

#if !defined(_WIN32)
  #include <unistd.h>
#endif

#if defined(__EMSCRIPTEN__)
  #include <emscripten/emscripten.h>

EM_JS(bool, occJSModuleNoExitRuntime, (), { return Module.noExitRuntime == = true; });
#endif

#ifdef HAVE_TK
  #if defined(__APPLE__) && !defined(HAVE_XLIB)

    #define _TK
typedef struct Tk_Window_* Tk_Window;
typedef const char*        Tk_Uid;

extern "C" int         Tk_Init(Tcl_Interp* interp);
extern "C" void        Tk_MainLoop();
extern "C" Tk_Window   Tk_MainWindow(Tcl_Interp* interp);
extern "C" Tk_Uid      Tk_GetUid(const char* str);
extern "C" const char* Tk_SetAppName(Tk_Window tkwin, const char* name);
extern "C" void        Tk_GeometryRequest(Tk_Window tkwin, int reqWidth, int reqHeight);

  #else
    #include <tk.h>
  #endif
#endif

#if defined(HAVE_XLIB)
  #include <X11/Xutil.h>
#endif

#if defined(_WIN32)

  #include "Draw_WNTRessource.hpp"
  #include "Draw_WNTInit.hpp"

  #define PENWIDTH 1
  #define CLIENTWND 0

static HPEN Draw_colorPenTab[MAXCOLOR] = {CreatePen(PS_SOLID, PENWIDTH, RGB(255, 255, 255)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(255, 0, 0)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(0, 255, 0)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(0, 0, 255)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(0, 255, 255)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(255, 215, 0)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(255, 0, 255)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(255, 52, 179)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(255, 165, 0)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(255, 228, 225)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(255, 160, 122)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(199, 21, 133)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(255, 255, 0)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(240, 230, 140)),
                                          CreatePen(PS_SOLID, PENWIDTH, RGB(255, 127, 80))};

static const int Draw_modeTab[16] = {R2_BLACK,
                                     R2_MASKPEN,
                                     R2_MASKPENNOT,
                                     R2_COPYPEN,
                                     R2_MASKNOTPEN,
                                     R2_NOP,
                                     R2_XORPEN,
                                     R2_MERGEPEN,
                                     R2_NOTMASKPEN,
                                     R2_NOTXORPEN,
                                     R2_NOT,
                                     R2_MERGEPENNOT,
                                     R2_NOTCOPYPEN,
                                     R2_MERGENOTPEN,
                                     R2_NOTMERGEPEN,
                                     R2_WHITE};
#endif

extern bool Draw_Batch;
extern bool Draw_VirtualWindows;
bool        Draw_BlackBackGround = true;
#if defined(_WIN32)

Standard_EXPORT bool Draw_IsConsoleSubsystem    = false;
HWND                 Draw_Window::hWndClientMDI = 0;
#endif

static NCollection_List<Draw_Window::FCallbackBeforeTerminate>& TermCallbacks()
{
  static NCollection_List<Draw_Window::FCallbackBeforeTerminate> MyCallbacks;
  return MyCallbacks;
}

void Draw_Window::AddCallbackBeforeTerminate(FCallbackBeforeTerminate theCB)
{
  TermCallbacks().Append(theCB);
}

void Draw_Window::RemoveCallbackBeforeTerminate(FCallbackBeforeTerminate theCB)
{
  for (NCollection_List<Draw_Window::FCallbackBeforeTerminate>::Iterator anIter(TermCallbacks());
       anIter.More();
       anIter.Next())
  {
    if (anIter.Value() == theCB)
    {
      TermCallbacks().Remove(anIter);
      break;
    }
  }
}

static void Prompt(Tcl_Interp* theInterp, int thePartial)
{
  Tcl_Channel errChannel;
  Tcl_Channel outChannel = Tcl_GetStdChannel(TCL_STDOUT);
  const char* promptCmd =
    Tcl_GetVar(theInterp, thePartial ? "tcl_prompt2" : "tcl_prompt1", TCL_GLOBAL_ONLY);
  if (promptCmd == nullptr)
  {
  defaultPrompt:
    if (!thePartial && outChannel)
    {
      Tcl_Write(outChannel, "% ", 2);
    }
  }
  else
  {
    int code   = Tcl_Eval(theInterp, promptCmd);
    outChannel = Tcl_GetStdChannel(TCL_STDOUT);
    errChannel = Tcl_GetStdChannel(TCL_STDERR);
    if (code != TCL_OK)
    {
      if (errChannel)
      {
#if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 5)))
        Tcl_Write(errChannel, Tcl_GetStringResult(theInterp), -1);
#else
        Tcl_Write(errChannel, theInterp->result, -1);
#endif
        Tcl_Write(errChannel, "\n", 1);
      }
      Tcl_AddErrorInfo(theInterp, "\n    (script that generates prompt)");
      goto defaultPrompt;
    }
  }
  if (outChannel)
  {
    Tcl_Flush(outChannel);
  }
}

#if !defined(_WIN32)

static Tcl_DString Draw_TclCommand;

static Tcl_DString Draw_TclLine;

static void StdinProc(ClientData theClientData, int theMask);
static void Prompt(Tcl_Interp* theInterp, int thePartial);

static bool tty;

  #if defined(HAVE_XLIB)
static unsigned long thePixels[MAXCOLOR];

Display*                                     Draw_WindowDisplay = nullptr;
Colormap                                     Draw_WindowColorMap;
static int                                   Draw_WindowScreen = 0;
static occ::handle<Aspect_DisplayConnection> Draw_DisplayConnection;

static NCollection_List<Draw_Window*>& getDrawWindowList()
{
  static NCollection_List<Draw_Window*> MyWindows;
  return MyWindows;
}

struct Draw_Window::Base_Window
{
  GC                   gc;
  XSetWindowAttributes xswa;
};
  #endif
#endif

#if !defined(__APPLE__) || defined(HAVE_XLIB)

Draw_Window::Draw_Window(const char*                  theTitle,
                         const NCollection_Vec2<int>& theXY,
                         const NCollection_Vec2<int>& theSize,
                         Aspect_Drawable              theParent,
                         Aspect_Drawable              theWin)
    : myWindow(0),
  #if defined(_WIN32)
      myMemHbm(NULL),
      myCurrPen(0),
      myCurrMode(0),
  #elif defined(HAVE_XLIB)
      myMother((Window)theParent),
      myImageBuffer(0),
      myBase(new Base_Window()),
  #endif
      myCurrentColor(0),
      myUseBuffer(false)
{
  NCollection_Vec2<int> anXY = theXY, aSize = theSize;
  #if defined(_WIN32)
  myWindow = (HWND)theWin;
  (void)theParent;
  #elif defined(HAVE_XLIB)
  myWindow = (Window)theWin;
  if (theParent == 0)
  {
    myMother = RootWindow(Draw_WindowDisplay, Draw_WindowScreen);
  }
  if (theWin != 0)
  {
    GetPosition(anXY.x(), anXY.y());
    aSize.x() = HeightWin();
    aSize.y() = WidthWin();
  }

  getDrawWindowList().Append(this);
  #else
  (void)theParent;
  (void)theWin;
  #endif

  init(anXY, aSize);
  SetTitle(theTitle);
}

Draw_Window::~Draw_Window()
{
  #ifdef _WIN32

  if (myMemHbm)
  {
    DeleteObject(myMemHbm);
    myMemHbm = NULL;
  }
  #elif defined(HAVE_XLIB)
  getDrawWindowList().Remove(this);
  if (myImageBuffer != 0)
  {
    XFreePixmap(Draw_WindowDisplay, myImageBuffer);
    myImageBuffer = 0;
  }
  #endif
}

void Draw_Window::init(const NCollection_Vec2<int>& theXY, const NCollection_Vec2<int>& theSize)
{
  #ifdef _WIN32
  if (myWindow == NULL)
  {
    myWindow = createDrawWindow(hWndClientMDI, 0);
  }

  DWORD aWinStyle   = GetWindowLongW(myWindow, GWL_STYLE);
  DWORD aWinStyleEx = GetWindowLongW(myWindow, GWL_EXSTYLE);
  HMENU aMenu       = GetMenu(myWindow);

  RECT aRect;
  aRect.top    = theXY.y();
  aRect.bottom = theXY.y() + theSize.y();
  aRect.left   = theXY.x();
  aRect.right  = theXY.x() + theSize.x();
  AdjustWindowRectEx(&aRect, aWinStyle, aMenu != NULL ? TRUE : FALSE, aWinStyleEx);

  SetPosition(aRect.left, aRect.top);
  SetDimension(aRect.right - aRect.left, aRect.bottom - aRect.top);

  SetWindowLongPtrW(myWindow, CLIENTWND, (LONG_PTR)this);
  HDC hDC = GetDC(myWindow);
  SetBkColor(hDC, RGB(0, 0, 0));
  myCurrPen  = 3;
  myCurrMode = 3;
  SelectObject(hDC, Draw_colorPenTab[myCurrPen]);
  SelectObject(hDC, GetStockObject(BLACK_BRUSH));
  SetTextColor(hDC, RGB(0, 0, 255));
  ReleaseDC(myWindow, hDC);

  if (Draw_VirtualWindows)
  {

    SetUseBuffer(true);
  }
  #elif defined(HAVE_XLIB)
  if (Draw_BlackBackGround)
  {
    myBase->xswa.background_pixel = BlackPixel(Draw_WindowDisplay, Draw_WindowScreen);
    myBase->xswa.border_pixel     = WhitePixel(Draw_WindowDisplay, Draw_WindowScreen);
  }
  else
  {
    myBase->xswa.background_pixel = WhitePixel(Draw_WindowDisplay, Draw_WindowScreen);
    myBase->xswa.border_pixel     = BlackPixel(Draw_WindowDisplay, Draw_WindowScreen);
  }
  myBase->xswa.colormap  = Draw_WindowColorMap;
  unsigned long aSetMask = CWBackPixel | CWBorderPixel;

  XSizeHints aWinHints;
  aWinHints.flags = USPosition;
  aWinHints.x     = theXY.x();
  aWinHints.y     = theXY.y();
  if (myWindow == 0)
  {
    myWindow = XCreateWindow(Draw_WindowDisplay,
                             myMother,
                             theXY.x(),
                             theXY.y(),
                             (unsigned int)theSize.x(),
                             (unsigned int)theSize.y(),
                             5,
                             DefaultDepth(Draw_WindowDisplay, Draw_WindowScreen),
                             InputOutput,
                             DefaultVisual(Draw_WindowDisplay, Draw_WindowScreen),
                             aSetMask,
                             &myBase->xswa);
    XSelectInput(Draw_WindowDisplay,
                 myWindow,
                 ButtonPressMask | ExposureMask | StructureNotifyMask);

    XSetWMNormalHints(Draw_WindowDisplay, myWindow, &aWinHints);

    Atom aDeleteWindowAtom = Draw_DisplayConnection->GetAtom(Aspect_XA_DELETE_WINDOW);
    XSetWMProtocols(Draw_WindowDisplay, myWindow, &aDeleteWindowAtom, 1);

    if (Draw_VirtualWindows)
    {
      myUseBuffer = true;
      InitBuffer();
    }
  }

  myBase->gc = XCreateGC(Draw_WindowDisplay, myWindow, 0, nullptr);

  XSetPlaneMask(Draw_WindowDisplay, myBase->gc, AllPlanes);
  XSetForeground(Draw_WindowDisplay, myBase->gc, WhitePixel(Draw_WindowDisplay, Draw_WindowScreen));
  XSetBackground(Draw_WindowDisplay, myBase->gc, BlackPixel(Draw_WindowDisplay, Draw_WindowScreen));

  myBase->xswa.backing_store = Always;
  XChangeWindowAttributes(Draw_WindowDisplay, myWindow, CWBackingStore, &myBase->xswa);

  XSetLineAttributes(Draw_WindowDisplay, myBase->gc, 0, LineSolid, CapButt, JoinMiter);
  #else
  (void)theXY;
  (void)theSize;
  #endif
}

void Draw_Window::SetUseBuffer(bool theToUse)
{
  myUseBuffer = theToUse;
  InitBuffer();
}

  #ifdef _WIN32

HDC Draw_Window::getMemDC(HDC theWinDC)
{
  if (!myUseBuffer)
  {
    return NULL;
  }

  HDC aWorkDC = CreateCompatibleDC(theWinDC);
  myOldHbm    = (HBITMAP)SelectObject(aWorkDC, myMemHbm);
  SetROP2(aWorkDC, Draw_modeTab[myCurrMode]);
  SelectObject(aWorkDC, Draw_colorPenTab[myCurrPen]);
  SetBkColor(aWorkDC, RGB(0, 0, 0));
  SelectObject(aWorkDC, GetStockObject(BLACK_BRUSH));
  SetTextColor(aWorkDC, RGB(0, 0, 255));
  return aWorkDC;
}

void Draw_Window::releaseMemDC(HDC theMemDC)
{
  if (!myUseBuffer || !theMemDC)
  {
    return;
  }

  if (myOldHbm)
  {
    SelectObject(theMemDC, myOldHbm);
  }
  DeleteDC(theMemDC);
}
  #endif

void Draw_Window::InitBuffer()
{
  #ifdef _WIN32
  if (myUseBuffer)
  {
    RECT aRect;
    HDC  hDC = GetDC(myWindow);
    GetClientRect(myWindow, &aRect);
    if (myMemHbm)
    {
      BITMAP aBmp;
      GetObjectW(myMemHbm, sizeof(BITMAP), &aBmp);
      if ((aRect.right - aRect.left) == aBmp.bmWidth && (aRect.bottom - aRect.top) == aBmp.bmHeight)
      {
        return;
      }
      DeleteObject(myMemHbm);
    }
    myMemHbm =
      (HBITMAP)CreateCompatibleBitmap(hDC, aRect.right - aRect.left, aRect.bottom - aRect.top);
    HDC aMemDC = getMemDC(hDC);
    FillRect(aMemDC, &aRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
    releaseMemDC(aMemDC);
    ReleaseDC(myWindow, hDC);
  }
  else
  {
    if (myMemHbm)
    {
      DeleteObject(myMemHbm);
      myMemHbm = NULL;
    }
  }
  #elif defined(HAVE_XLIB)
  if (myUseBuffer)
  {
    if (myImageBuffer != 0)
    {
      XFreePixmap(Draw_WindowDisplay, myImageBuffer);
    }
    XWindowAttributes aWinAttr;
    XGetWindowAttributes(Draw_WindowDisplay, myWindow, &aWinAttr);
    myImageBuffer =
      XCreatePixmap(Draw_WindowDisplay, myWindow, aWinAttr.width, aWinAttr.height, aWinAttr.depth);
  }
  else if (myImageBuffer != 0)
  {
    XFreePixmap(Draw_WindowDisplay, myImageBuffer);
    myImageBuffer = 0;
  }
  #endif
}

void Draw_Window::SetPosition(int theNewXpos, int theNewYpos)
{
  #ifdef _WIN32
  UINT aFlags = SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER;
  if (Draw_VirtualWindows)
  {
    aFlags |= SWP_NOSENDCHANGING;
  }
  SetWindowPos(myWindow, 0, theNewXpos, theNewYpos, 0, 0, aFlags);
  #elif defined(HAVE_XLIB)
  int aPosX = 0, aPosY = 0;
  GetPosition(aPosX, aPosY);
  if (aPosX != theNewXpos || aPosY != theNewYpos)
  {
    XMoveWindow(Draw_WindowDisplay, myWindow, theNewXpos, theNewYpos);
  }
  #else
  (void)theNewXpos;
  (void)theNewYpos;
  #endif
}

void Draw_Window::SetDimension(int theNewDx, int theNewDy)
{
  #ifdef _WIN32
  UINT aFlags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER;
  if (Draw_VirtualWindows)
  {
    aFlags |= SWP_NOSENDCHANGING;
  }
  SetWindowPos(myWindow, 0, 0, 0, theNewDx, theNewDy, aFlags);
  #elif defined(HAVE_XLIB)
  if (theNewDx != WidthWin() || theNewDy != HeightWin())
  {
    XResizeWindow(Draw_WindowDisplay, myWindow, theNewDx, theNewDy);
  }
  #else
  (void)theNewDx;
  (void)theNewDy;
  #endif
}

void Draw_Window::GetPosition(int& thePosX, int& thePosY)
{
  thePosX = thePosY = 0;
  #ifdef _WIN32
  RECT aRect;
  GetWindowRect(myWindow, &aRect);

  POINT aPoint;
  aPoint.x = aRect.left;
  aPoint.y = aRect.top;

  ScreenToClient(hWndClientMDI, &aPoint);
  thePosX = aPoint.x;
  thePosY = aPoint.y;
  #elif defined(HAVE_XLIB)
  XWindowAttributes aWinAttr;
  XGetWindowAttributes(Draw_WindowDisplay, myWindow, &aWinAttr);
  thePosX = aWinAttr.x;
  thePosY = aWinAttr.y;
  #endif
}

int Draw_Window::HeightWin() const
{
  #ifdef _WIN32
  RECT aRect;
  GetClientRect(myWindow, &aRect);
  return aRect.bottom - aRect.top;
  #elif defined(HAVE_XLIB)
  XWindowAttributes aWinAttr;
  XGetWindowAttributes(Draw_WindowDisplay, myWindow, &aWinAttr);
  return aWinAttr.height;
  #else
  return 1;
  #endif
}

int Draw_Window::WidthWin() const
{
  #ifdef _WIN32
  RECT aRect;
  GetClientRect(myWindow, &aRect);
  return aRect.right - aRect.left;
  #elif defined(HAVE_XLIB)
  XWindowAttributes aWinAttr;
  XGetWindowAttributes(Draw_WindowDisplay, myWindow, &aWinAttr);
  return aWinAttr.width;
  #else
  return 1;
  #endif
}

void Draw_Window::SetTitle(const TCollection_AsciiString& theTitle)
{
  #ifdef _WIN32
  const TCollection_ExtendedString aTitleW(theTitle);
  SetWindowTextW(myWindow, aTitleW.ToWideString());
  #elif defined(HAVE_XLIB)
  XStoreName(Draw_WindowDisplay, myWindow, theTitle.ToCString());
  #else
  (void)theTitle;
  #endif
}

TCollection_AsciiString Draw_Window::GetTitle() const
{
  #ifdef _WIN32
  wchar_t aTitleW[32];
  GetWindowTextW(myWindow, aTitleW, 30);
  return TCollection_AsciiString(aTitleW);
  #elif defined(HAVE_XLIB)
  char* aTitle = nullptr;
  XFetchName(Draw_WindowDisplay, myWindow, &aTitle);
  return TCollection_AsciiString(aTitle);
  #else
  return TCollection_AsciiString();
  #endif
}

bool Draw_Window::DefineColor(const int theIndex, const char* theColorName)
{
  #if defined(HAVE_XLIB)
  XColor aColor;
  if (!XParseColor(Draw_WindowDisplay, Draw_WindowColorMap, theColorName, &aColor))
  {
    return false;
  }
  if (!XAllocColor(Draw_WindowDisplay, Draw_WindowColorMap, &aColor))
  {
    return false;
  }
  thePixels[theIndex % MAXCOLOR] = aColor.pixel;
  return true;
  #else
  (void)theIndex;
  (void)theColorName;
  return true;
  #endif
}

bool Draw_Window::IsMapped() const
{
  if (Draw_VirtualWindows || myWindow == 0)
  {
    return false;
  }

  #ifdef _WIN32
  LONG aWinStyle = GetWindowLongW(myWindow, GWL_STYLE);
  return (aWinStyle & WS_VISIBLE) != 0 && (aWinStyle & WS_MINIMIZE) == 0;
  #elif defined(HAVE_XLIB)
  XFlush(Draw_WindowDisplay);
  XWindowAttributes aWinAttr;
  XGetWindowAttributes(Draw_WindowDisplay, myWindow, &aWinAttr);
  return aWinAttr.map_state == IsUnviewable || aWinAttr.map_state == IsViewable;
  #else
  return false;
  #endif
}

void Draw_Window::DisplayWindow()
{
  if (Draw_VirtualWindows)
  {
    return;
  }

  #ifdef _WIN32
  ShowWindow(myWindow, SW_SHOW);
  UpdateWindow(myWindow);
  #elif defined(HAVE_XLIB)
  XMapRaised(Draw_WindowDisplay, myWindow);
  XFlush(Draw_WindowDisplay);
  #endif
}

void Draw_Window::Hide()
{
  #ifdef _WIN32
  ShowWindow(myWindow, SW_HIDE);
  #elif defined(HAVE_XLIB)
  XUnmapWindow(Draw_WindowDisplay, myWindow);
  #endif
}

void Draw_Window::Destroy()
{
  #ifdef _WIN32
  DestroyWindow(myWindow);
  #elif defined(HAVE_XLIB)
  XFreeGC(Draw_WindowDisplay, myBase->gc);
  XDestroyWindow(Draw_WindowDisplay, myWindow);
  myWindow = 0;
  if (myImageBuffer != 0)
  {
    XFreePixmap(Draw_WindowDisplay, myImageBuffer);
    myImageBuffer = 0;
  }
  #endif
}

void Draw_Window::Clear()
{
  #ifdef _WIN32
  HDC hDC     = GetDC(myWindow);
  HDC aWorkDC = myUseBuffer ? getMemDC(hDC) : hDC;

  SaveDC(aWorkDC);
  SelectObject(aWorkDC, GetStockObject(BLACK_PEN));
  Rectangle(aWorkDC, 0, 0, WidthWin(), HeightWin());
  RestoreDC(aWorkDC, -1);

  if (myUseBuffer)
  {
    releaseMemDC(aWorkDC);
  }
  ReleaseDC(myWindow, hDC);
  #elif defined(HAVE_XLIB)
  if (myUseBuffer)
  {

    XGCValues aCurrValues;
    XGetGCValues(Draw_WindowDisplay, myBase->gc, GCBackground | GCForeground, &aCurrValues);
    XSetForeground(Draw_WindowDisplay, myBase->gc, aCurrValues.background);
    XFillRectangle(Draw_WindowDisplay, myImageBuffer, myBase->gc, 0, 0, WidthWin(), HeightWin());
    XSetForeground(Draw_WindowDisplay, myBase->gc, aCurrValues.foreground);
  }
  else
  {
    XClearArea(Draw_WindowDisplay, myWindow, 0, 0, 0, 0, False);
  }
  #endif
}

void Draw_Window::Flush()
{
  #if defined(HAVE_XLIB)
  XFlush(Draw_WindowDisplay);
  #endif
}

void Draw_Window::DrawString(int theX, int theY, const char* theText)
{
  #ifdef _WIN32
  HDC hDC     = GetDC(myWindow);
  HDC aWorkDC = myUseBuffer ? getMemDC(hDC) : hDC;

  const TCollection_ExtendedString aTextW(theText);
  TextOutW(aWorkDC, theX, theY, aTextW.ToWideString(), aTextW.Length());

  if (myUseBuffer)
  {
    releaseMemDC(aWorkDC);
  }
  ReleaseDC(myWindow, hDC);
  #elif defined(HAVE_XLIB)
  XDrawString(Draw_WindowDisplay,
              GetDrawable(),
              myBase->gc,
              theX,
              theY,
              (char*)theText,
              (int)strlen(theText));
  #else
  (void)theX;
  (void)theY;
  (void)theText;
  #endif
}

void Draw_Window::DrawSegments(const Draw_XSegment* theSegments, int theNbElems)
{
  #ifdef _WIN32
  HDC hDC     = GetDC(myWindow);
  HDC aWorkDC = myUseBuffer ? getMemDC(hDC) : hDC;
  for (int aSegIter = 0; aSegIter < theNbElems; ++aSegIter)
  {
    const Draw_XSegment& aSeg = theSegments[aSegIter];
    MoveToEx(aWorkDC, aSeg[0].x(), aSeg[0].y(), NULL);
    LineTo(aWorkDC, aSeg[1].x(), aSeg[1].y());
  }
  if (myUseBuffer)
  {
    releaseMemDC(aWorkDC);
  }
  ReleaseDC(myWindow, hDC);
  #elif defined(HAVE_XLIB)
  Standard_STATIC_ASSERT(sizeof(Draw_XSegment) == sizeof(XSegment));
  XDrawSegments(Draw_WindowDisplay, GetDrawable(), myBase->gc, (XSegment*)theSegments, theNbElems);
  #else
  (void)theSegments;
  (void)theNbElems;
  #endif
}

void Draw_Window::Redraw()
{
  #ifdef _WIN32
  if (myUseBuffer)
  {
    HDC  hDC = GetDC(myWindow);
    RECT aRect;
    GetClientRect(myWindow, &aRect);
    HDC aMemDC = getMemDC(hDC);
    BitBlt(hDC,
           aRect.left,
           aRect.top,
           aRect.right - aRect.left,
           aRect.bottom - aRect.top,
           aMemDC,
           0,
           0,
           SRCCOPY);
    releaseMemDC(aMemDC);
    ReleaseDC(myWindow, hDC);
  }
  #elif defined(HAVE_XLIB)
  if (myUseBuffer)
  {
    XCopyArea(Draw_WindowDisplay,
              myImageBuffer,
              myWindow,
              myBase->gc,
              0,
              0,
              WidthWin(),
              HeightWin(),
              0,
              0);
  }
  #endif
}

void Draw_Window::SetColor(int theColor)
{
  #ifdef _WIN32
  HDC hDC   = GetDC(myWindow);
  myCurrPen = theColor;
  SelectObject(hDC, Draw_colorPenTab[theColor]);
  ReleaseDC(myWindow, hDC);
  #elif defined(HAVE_XLIB)
  XSetForeground(Draw_WindowDisplay, myBase->gc, thePixels[theColor]);
  #endif
  myCurrentColor = theColor;
}

void Draw_Window::SetMode(int theMode)
{
  #ifdef _WIN32
  HDC hDC    = GetDC(myWindow);
  myCurrMode = theMode;
  SetROP2(hDC, Draw_modeTab[theMode]);
  ReleaseDC(myWindow, hDC);
  #elif defined(HAVE_XLIB)
  XSetFunction(Draw_WindowDisplay, myBase->gc, theMode);
  #else
  (void)theMode;
  #endif
}

  #ifdef _WIN32

static bool SaveBitmap(HBITMAP theHBitmap, const char* theFileName)
{

  BITMAP aBitmap;
  if (GetObjectW(theHBitmap, sizeof(BITMAP), &aBitmap) == 0)
  {
    return false;
  }

  Image_AlienPixMap anImage;
  const size_t      aSizeRowBytes = ((size_t(aBitmap.bmWidth) * 24 + 31) / 32) * 4;
  if (!anImage.InitTrash(Image_Format_BGR,
                         size_t(aBitmap.bmWidth),
                         size_t(aBitmap.bmHeight),
                         aSizeRowBytes))
  {
    return false;
  }
  anImage.SetTopDown(false);

  BITMAPINFOHEADER aBitmapInfo;
  memset(&aBitmapInfo, 0, sizeof(BITMAPINFOHEADER));
  aBitmapInfo.biSize        = sizeof(BITMAPINFOHEADER);
  aBitmapInfo.biWidth       = aBitmap.bmWidth;
  aBitmapInfo.biHeight      = aBitmap.bmHeight;
  aBitmapInfo.biPlanes      = 1;
  aBitmapInfo.biBitCount    = 24;
  aBitmapInfo.biCompression = BI_RGB;

  HDC  aDC       = GetDC(NULL);
  bool isSuccess = GetDIBits(aDC,
                             theHBitmap,
                             0,
                             aBitmap.bmHeight,
                             anImage.ChangeData(),
                             (LPBITMAPINFO)&aBitmapInfo,
                             DIB_RGB_COLORS)
                   != 0;
  ReleaseDC(NULL, aDC);
  return isSuccess && anImage.Save(theFileName);
}
  #endif

bool Draw_Window::Save(const char* theFileName) const
{
  #ifdef _WIN32
  if (myUseBuffer)
  {
    return SaveBitmap(myMemHbm, theFileName);
  }

  RECT aRect;
  GetClientRect(myWindow, &aRect);
  int aWidth  = aRect.right - aRect.left;
  int aHeight = aRect.bottom - aRect.top;

  HDC aDstDC = GetDC(NULL);
  HDC aSrcDC = GetDC(myWindow);
  HDC aMemDC = CreateCompatibleDC(aDstDC);

  HBITMAP anHBitmapDump = CreateCompatibleBitmap(aDstDC, aWidth, aHeight);
  HBITMAP anHBitmapOld  = (HBITMAP)SelectObject(aMemDC, anHBitmapDump);
  BitBlt(aMemDC, 0, 0, aWidth, aHeight, aSrcDC, 0, 0, SRCCOPY);

  bool isSuccess = SaveBitmap(anHBitmapDump, theFileName);

  DeleteObject(SelectObject(aMemDC, anHBitmapOld));
  DeleteDC(aMemDC);

  return isSuccess;
  #elif defined(HAVE_XLIB)

  XSync(Draw_WindowDisplay, True);

  XWindowAttributes aWinAttr;
  XGetWindowAttributes(Draw_WindowDisplay, myWindow, &aWinAttr);

  if (!myUseBuffer)
  {

    XWindowAttributes aWinAttrRoot;
    XGetWindowAttributes(Draw_WindowDisplay, XRootWindowOfScreen(aWinAttr.screen), &aWinAttrRoot);

    Window aWinChildDummy;
    int    aWinLeft = 0, aWinTop = 0;
    XTranslateCoordinates(Draw_WindowDisplay,
                          myWindow,
                          XRootWindowOfScreen(aWinAttr.screen),
                          0,
                          0,
                          &aWinLeft,
                          &aWinTop,
                          &aWinChildDummy);

    if (((aWinLeft + aWinAttr.width) > aWinAttrRoot.width) || aWinLeft < aWinAttrRoot.x
        || ((aWinTop + aWinAttr.height) > aWinAttrRoot.height) || aWinTop < aWinAttrRoot.y)
    {
      std::cerr << "The window not fully visible! Can't create the snapshot.\n";
      return false;
    }
  }

  XVisualInfo aVInfo;
  if (XMatchVisualInfo(Draw_WindowDisplay, Draw_WindowScreen, 32, TrueColor, &aVInfo) == 0
      && XMatchVisualInfo(Draw_WindowDisplay, Draw_WindowScreen, 24, TrueColor, &aVInfo) == 0)
  {
    std::cerr << "24-bit TrueColor visual is not supported by server!\n";
    return false;
  }

  Image_AlienPixMap anImage;
  bool              isBigEndian   = Image_PixMap::IsBigEndianHost();
  const size_t      aSizeRowBytes = size_t(aWinAttr.width) * 4;
  if (!anImage.InitTrash(isBigEndian ? Image_Format_RGB32 : Image_Format_BGR32,
                         size_t(aWinAttr.width),
                         size_t(aWinAttr.height),
                         aSizeRowBytes))
  {
    return false;
  }
  anImage.SetTopDown(true);

  XImage* anXImage           = XCreateImage(Draw_WindowDisplay,
                                  aVInfo.visual,
                                  32,
                                  ZPixmap,
                                  0,
                                  (char*)anImage.ChangeData(),
                                  aWinAttr.width,
                                  aWinAttr.height,
                                  32,
                                  int(aSizeRowBytes));
  anXImage->bitmap_bit_order = anXImage->byte_order = (isBigEndian ? MSBFirst : LSBFirst);
  if (XGetSubImage(Draw_WindowDisplay,
                   GetDrawable(),
                   0,
                   0,
                   aWinAttr.width,
                   aWinAttr.height,
                   AllPlanes,
                   ZPixmap,
                   anXImage,
                   0,
                   0)
      == nullptr)
  {
    anXImage->data = nullptr;
    XDestroyImage(anXImage);
    return false;
  }

  anXImage->data = nullptr;
  XDestroyImage(anXImage);

  return anImage.Save(theFileName);
  #else
  (void)theFileName;
  return false;
  #endif
}

#endif

#if defined(HAVE_XLIB)

void Draw_Window::Wait(bool theToWait)
{
  Flush();
  long aMask = ButtonPressMask | ExposureMask | StructureNotifyMask;
  if (!theToWait)
  {
    aMask |= PointerMotionMask;
  }
  XSelectInput(Draw_WindowDisplay, myWindow, aMask);
}

static void processXEvents(ClientData, int)
{

  while (XPending(Draw_WindowDisplay))
  {
    XEvent anEvent;
    XNextEvent(Draw_WindowDisplay, &anEvent);

    bool isFound = false;

    for (NCollection_List<Draw_Window*>::Iterator aWinIter(getDrawWindowList()); aWinIter.More();
         aWinIter.Next())
    {
      Draw_Window* aDrawWin = aWinIter.Value();
      if (aDrawWin->IsEqualWindows(anEvent.xany.window))
      {
        switch (anEvent.type)
        {
          case ClientMessage:
          {
            if (anEvent.xclient.data.l[0]
                == (int)Draw_DisplayConnection->GetAtom(Aspect_XA_DELETE_WINDOW))
            {
              aDrawWin->Hide();
            }
            break;
          }
          case Expose:
          {
            aDrawWin->WExpose();
            break;
          }
        }

        isFound = true;
        break;
      }
    }
    if (!isFound)
    {
  #ifdef _TK
      Tk_HandleEvent(&anEvent);
  #endif
    }
  }
}

void Draw_Window::GetNextEvent(Draw_Window::Draw_XEvent& theEvent)
{
  XEvent anXEvent;
  XNextEvent(Draw_WindowDisplay, &anXEvent);
  switch (anXEvent.type)
  {
    case ButtonPress:
    {
      theEvent.type   = 4;
      theEvent.window = anXEvent.xbutton.window;
      theEvent.button = anXEvent.xbutton.button;
      theEvent.x      = anXEvent.xbutton.x;
      theEvent.y      = anXEvent.xbutton.y;
      break;
    }
    case MotionNotify:
    {
      theEvent.type   = 6;
      theEvent.window = anXEvent.xmotion.window;
      theEvent.button = 0;
      theEvent.x      = anXEvent.xmotion.x;
      theEvent.y      = anXEvent.xmotion.y;
      break;
    }
  }
}
#endif

#ifndef _WIN32

static bool (*Interprete)(const char*);

void Run_Appli(bool (*interprete)(const char*))
{
  Interprete = interprete;

  bool toWaitInput = true;
  #ifdef __EMSCRIPTEN__
  toWaitInput = !occJSModuleNoExitRuntime();
  #endif

  Tcl_Channel anInChannel = Tcl_GetStdChannel(TCL_STDIN);
  if (anInChannel && toWaitInput)
  {
    Tcl_CreateChannelHandler(anInChannel, TCL_READABLE, StdinProc, (ClientData)anInChannel);
  }

  #if defined(HAVE_XLIB)
  Tcl_CreateFileHandler(ConnectionNumber(Draw_WindowDisplay),
                        TCL_READABLE,
                        processXEvents,
                        (ClientData) nullptr);
  #endif

  Draw_Interpretor& aCommands = Draw::GetInterpretor();

  if (tty)
  {
    Prompt(aCommands.Interp(), 0);
  }
  Prompt(aCommands.Interp(), 0);

  Tcl_Channel anOutChannel = Tcl_GetStdChannel(TCL_STDOUT);
  if (anOutChannel)
  {
    Tcl_Flush(anOutChannel);
  }
  Tcl_DStringInit(&Draw_TclCommand);

  #ifdef _TK
  if (Draw_VirtualWindows)
  {

    Tcl_Eval(aCommands.Interp(), "wm withdraw .");
  }

  Tk_MainLoop();
  #else
  if (!toWaitInput)
  {
    return;
  }

  for (;;)
  {
    Tcl_DoOneEvent(0);
  }
  #endif

  for (NCollection_List<Draw_Window::FCallbackBeforeTerminate>::Iterator anIter(TermCallbacks());
       anIter.More();
       anIter.Next())
  {
    (*anIter.Value())();
  }
}

bool Init_Appli()
{
  Draw_Interpretor& aCommands = Draw::GetInterpretor();
  aCommands.Init();
  Tcl_Interp* interp = aCommands.Interp();
  Tcl_Init(interp);

  #ifdef _TK
  try
  {
    OCC_CATCH_SIGNALS
    Tk_Init(interp);
  }
  catch (Standard_Failure const& theFail)
  {
    Message::SendFail() << "TK_Init() failed with " << theFail;
  }

  Tcl_StaticPackage(interp, "Tk", Tk_Init, (Tcl_PackageInitProc*)nullptr);

  Tk_Window aMainWindow = Tk_MainWindow(interp);
  if (aMainWindow == nullptr)
  {
    #if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 5)))
    fprintf(stderr, "%s\n", Tcl_GetStringResult(interp));
    #else
    fprintf(stderr, "%s\n", interp->result);
    #endif
    exit(1);
  }
    #if defined(__APPLE__) && !defined(HAVE_XLIB)
  Tk_SetAppName(aMainWindow, "Draw");
    #else
  Tk_Name(aMainWindow) = Tk_GetUid(Tk_SetAppName(aMainWindow, "Draw"));
    #endif

  Tk_GeometryRequest(aMainWindow, 200, 200);
  #endif

  #if defined(HAVE_XLIB)
  if (Draw_DisplayConnection.IsNull())
  {
    try
    {
      Draw_DisplayConnection = new Aspect_DisplayConnection();
    }
    catch (Standard_Failure const& theFail)
    {
      std::cout << "Cannot open display (" << theFail << "). Interpret commands in batch mode."
                << std::endl;
      return false;
    }
  }
  if (Draw_WindowDisplay == nullptr)
  {
    Draw_WindowDisplay = (Display*)Draw_DisplayConnection->GetDisplayAspect();
  }

  XSynchronize(Draw_WindowDisplay, True);
  XSetInputFocus(Draw_WindowDisplay, PointerRoot, RevertToPointerRoot, CurrentTime);

  Draw_WindowScreen   = DefaultScreen(Draw_WindowDisplay);
  Draw_WindowColorMap = DefaultColormap(Draw_WindowDisplay, Draw_WindowScreen);
  #endif

  tty = isatty(0);
  Tcl_SetVar(interp, "tcl_interactive", (char*)(tty ? "1" : "0"), TCL_GLOBAL_ONLY);

  return true;
}

void Destroy_Appli() {}

static void StdinProc(ClientData clientData, int theMask)
{
  (void)theMask;
  static int gotPartial = 0;

  Tcl_Channel chan = (Tcl_Channel)clientData;

  Tcl_DStringFree(&Draw_TclLine);
  int count = Tcl_Gets(chan, &Draw_TclLine);

  #if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4)))
  Tcl_DString aLineTmp;
  Tcl_DStringInit(&aLineTmp);
  Tcl_UniChar* aUniCharString =
    Tcl_UtfToUniCharDString(Tcl_DStringValue(&Draw_TclLine), -1, &aLineTmp);
  int                     l = Tcl_UniCharLen(aUniCharString);
  TCollection_AsciiString anAsciiString;
  for (int i = 0; i < l; ++i)
  {
    char aCharacter = aUniCharString[i];
    anAsciiString.AssignCat(aCharacter);
  }
  Tcl_DStringInit(&Draw_TclLine);
  Tcl_DStringAppend(&Draw_TclLine, anAsciiString.ToCString(), -1);
  #endif
  if (count < 0)
  {
    if (!gotPartial)
    {
      if (tty)
      {
        Tcl_Exit(0);
      }
      else
      {
        Tcl_DeleteChannelHandler(chan, StdinProc, (ClientData)chan);
      }
      return;
    }
    else
    {
      count = 0;
    }
  }

  (void)Tcl_DStringAppend(&Draw_TclCommand, Tcl_DStringValue(&Draw_TclLine), -1);
  char* cmd = Tcl_DStringAppend(&Draw_TclCommand, "\n", -1);
  Tcl_DStringFree(&Draw_TclLine);
  try
  {
    OCC_CATCH_SIGNALS
    if (!Tcl_CommandComplete(cmd))
    {
      gotPartial = 1;
      goto prompt;
    }
    gotPartial = 0;

    Tcl_CreateChannelHandler(chan, 0, StdinProc, (ClientData)chan);

  #ifdef _TK

  #endif

    Interprete(cmd);

    Tcl_CreateChannelHandler(chan, TCL_READABLE, StdinProc, (ClientData)chan);
    Tcl_DStringFree(&Draw_TclCommand);

  prompt:
    if (tty)
    {
      Prompt(Draw::GetInterpretor().Interp(), gotPartial);
    }
  }
  catch (Standard_Failure const&)
  {
  }
}

#else

HWND Draw_Window::createDrawWindow(HWND hWndClient, int nitem)
{
  if (Draw_IsConsoleSubsystem)
  {
    HWND aWin = CreateWindowW(DRAWCLASS,
                              DRAWTITLE,
                              WS_OVERLAPPEDWINDOW,
                              1,
                              1,
                              1,
                              1,
                              NULL,
                              NULL,
                              ::GetModuleHandle(NULL),
                              NULL);
    if (!Draw_VirtualWindows)
    {
      SetWindowPos(aWin, HWND_TOPMOST, 1, 1, 1, 1, SWP_NOMOVE);
      SetWindowPos(aWin, HWND_NOTOPMOST, 1, 1, 1, 1, SWP_NOMOVE);
    }
    return aWin;
  }
  else
  {
    HANDLE hInstance = (HANDLE)GetWindowLongPtrW(hWndClient, GWLP_HINSTANCE);
    return CreateMDIWindowW(DRAWCLASS,
                            DRAWTITLE,
                            WS_CAPTION | WS_CHILD | WS_THICKFRAME,
                            1,
                            1,
                            0,
                            0,
                            hWndClient,
                            (HINSTANCE)hInstance,
                            nitem);
  }
}

LRESULT APIENTRY Draw_Window::DrawProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
  Draw_Window* aLocWin = (Draw_Window*)GetWindowLongPtrW(hWnd, CLIENTWND);
  if (aLocWin == NULL)
  {
    return Draw_IsConsoleSubsystem ? DefWindowProcW(hWnd, wMsg, wParam, lParam)
                                   : DefMDIChildProcW(hWnd, wMsg, wParam, lParam);
  }

  switch (wMsg)
  {
    case WM_CLOSE:
    {
      aLocWin->Hide();
      return 0;
    }
    case WM_PAINT:
    {
      PAINTSTRUCT ps;
      BeginPaint(hWnd, &ps);
      if (aLocWin->GetUseBuffer())
      {
        aLocWin->Redraw();
      }
      else
      {
        aLocWin->WExpose();
      }
      EndPaint(hWnd, &ps);
      return 0;
    }
    case WM_SIZE:
    {
      if (aLocWin->GetUseBuffer())
      {
        aLocWin->InitBuffer();
        aLocWin->WExpose();
        aLocWin->Redraw();
        return 0;
      }
      break;
    }
  }
  return Draw_IsConsoleSubsystem ? DefWindowProcW(hWnd, wMsg, wParam, lParam)
                                 : DefMDIChildProcW(hWnd, wMsg, wParam, lParam);
}

void Draw_Window::SelectWait(HANDLE& theWindow, int& theX, int& theY, int& theButton)
{
  MSG aMsg;
  aMsg.wParam = 1;
  GetMessageW(&aMsg, NULL, 0, 0);
  while ((aMsg.message != WM_RBUTTONDOWN && aMsg.message != WM_LBUTTONDOWN)
         || !(Draw_IsConsoleSubsystem || IsChild(Draw_Window::hWndClientMDI, aMsg.hwnd)))
  {
    GetMessageW(&aMsg, NULL, 0, 0);
  }

  theWindow = aMsg.hwnd;
  theX      = LOWORD(aMsg.lParam);
  theY      = HIWORD(aMsg.lParam);
  if (aMsg.message == WM_LBUTTONDOWN)
  {
    theButton = 1;
  }
  else
  {
    theButton = 3;
  }
}

void Draw_Window::SelectNoWait(HANDLE& theWindow, int& theX, int& theY, int& theButton)
{
  MSG aMsg;
  aMsg.wParam = 1;
  GetMessageW(&aMsg, NULL, 0, 0);
  while ((aMsg.message != WM_RBUTTONDOWN && aMsg.message != WM_LBUTTONDOWN
          && aMsg.message != WM_MOUSEMOVE)
         || !(Draw_IsConsoleSubsystem || IsChild(Draw_Window::hWndClientMDI, aMsg.hwnd)))
  {
    GetMessageW(&aMsg, NULL, 0, 0);
  }

  theWindow = aMsg.hwnd;
  theX      = LOWORD(aMsg.lParam);
  theY      = HIWORD(aMsg.lParam);
  switch (aMsg.message)
  {
    case WM_LBUTTONDOWN:
      theButton = 1;
      break;
    case WM_RBUTTONDOWN:
      theButton = 3;
      break;
    case WM_MOUSEMOVE:
      theButton = 0;
      break;
  }
}

static DWORD WINAPI tkLoop(LPVOID theThreadParameter);
  #ifdef _TK
static Tk_Window mainWindow;
  #endif

static DWORD dwMainThreadId;
console_semaphore_value volatile console_semaphore = WAIT_CONSOLE_COMMAND;
wchar_t console_command[DRAW_COMMAND_SIZE + 1];
bool volatile isTkLoopStarted = false;

bool Init_Appli(HINSTANCE hInst, HINSTANCE hPrevInst, int nShow, HWND& hWndFrame)
{
  DWORD  IDThread;
  HANDLE hThread;
  console_semaphore = STOP_CONSOLE;

  dwMainThreadId = GetCurrentThreadId();

  hThread = CreateThread(NULL, 0, tkLoop, NULL, 0, &IDThread);
  if (!hThread)
  {
    std::cout << "Failed to create Tcl/Tk main loop thread. Switching to batch mode..."
              << std::endl;
    Draw_Batch                  = true;
    Draw_Interpretor& aCommands = Draw::GetInterpretor();
    aCommands.Init();
    Tcl_Interp* interp = aCommands.Interp();
    Tcl_Init(interp);
  #ifdef _TK
    try
    {
      OCC_CATCH_SIGNALS
      Tk_Init(interp);
    }
    catch (Standard_Failure& anExcept)
    {
      std::cout << "Failed to initialize Tk: " << anExcept.what() << std::endl;
    }

    Tcl_StaticPackage(interp, "Tk", Tk_Init, (Tcl_PackageInitProc*)NULL);
  #endif

    return false;
  }

  while (!isTkLoopStarted)
  {
    Sleep(10);
  }

  if (!hPrevInst)
  {
    if (!RegisterAppClass(hInst))
    {
      return false;
    }
  }

  hWndFrame = !Draw_IsConsoleSubsystem ? CreateAppWindow(hInst) : NULL;
  if (hWndFrame != NULL)
  {
    ShowWindow(hWndFrame, nShow);
    UpdateWindow(hWndFrame);
  }

  return true;
}

bool Draw_Interprete(const char*);

static DWORD WINAPI readStdinThreadFunc(const LPVOID theThreadParameter)
{
  (void)theThreadParameter;
  if (!Draw_IsConsoleSubsystem)
  {
    return 1;
  }

  bool isConsoleInput = true;
  for (;;)
  {
    while (console_semaphore != WAIT_CONSOLE_COMMAND)
    {
      Sleep(100);
    }

    const HANDLE anStdIn = ::GetStdHandle(STD_INPUT_HANDLE);
    if (anStdIn != NULL && anStdIn != INVALID_HANDLE_VALUE && isConsoleInput)
    {
      DWORD aNbRead = 0;
      if (ReadConsoleW(anStdIn, console_command, DRAW_COMMAND_SIZE, &aNbRead, NULL))
      {
        console_command[aNbRead] = L'\0';
        console_semaphore        = HAS_CONSOLE_COMMAND;
        continue;
      }
      else
      {
        const DWORD anErr = GetLastError();
        if (anErr != ERROR_SUCCESS)
        {

          isConsoleInput = false;
          continue;
        }
      }
    }

    if (fgetws(console_command, DRAW_COMMAND_SIZE, stdin))
    {
      console_semaphore = HAS_CONSOLE_COMMAND;
    }
  }
}

void exitProc(ClientData)
{
  for (NCollection_List<Draw_Window::FCallbackBeforeTerminate>::Iterator anIter(TermCallbacks());
       anIter.More();
       anIter.Next())
  {
    (*anIter.Value())();
  }
  HANDLE proc = GetCurrentProcess();
  TerminateProcess(proc, 0);
}

static Tcl_Channel TclpGetDefaultStdChannel(int type)
{
  Tcl_Channel channel;
  HANDLE      handle;
  int         mode     = -1;
  const char* bufMode  = NULL;
  DWORD       handleId = (DWORD)-1;

  switch (type)
  {
    case TCL_STDIN:
      handleId = STD_INPUT_HANDLE;
      mode     = TCL_READABLE;
      bufMode  = "line";
      break;
    case TCL_STDOUT:
      handleId = STD_OUTPUT_HANDLE;
      mode     = TCL_WRITABLE;
      bufMode  = "line";
      break;
    case TCL_STDERR:
      handleId = STD_ERROR_HANDLE;
      mode     = TCL_WRITABLE;
      bufMode  = "none";
      break;
    default:
      Tcl_Panic("TclGetDefaultStdChannel: Unexpected channel type");
      break;
  }

  handle = GetStdHandle(handleId);

  if ((handle == INVALID_HANDLE_VALUE) || (handle == 0))
  {
    return (Tcl_Channel)NULL;
  }

  if (!DuplicateHandle(GetCurrentProcess(),
                       handle,
                       GetCurrentProcess(),
                       &handle,
                       0,
                       FALSE,
                       DUPLICATE_SAME_ACCESS))
  {
    return (Tcl_Channel)NULL;
  }

  channel = Tcl_MakeFileChannel(handle, mode);

  if (channel == NULL)
  {
    return (Tcl_Channel)NULL;
  }

  if (Tcl_SetChannelOption(NULL, channel, "-translation", "auto") != TCL_OK
      || Tcl_SetChannelOption(NULL, channel, "-eofchar", "\032 {}") != TCL_OK
      || Tcl_SetChannelOption(NULL, channel, "-buffering", bufMode) != TCL_OK)
  {
    Tcl_Close(NULL, channel);
    return (Tcl_Channel)NULL;
  }
  return channel;
}

static void ResetStdChannel(int type)
{
  Tcl_Channel aChannel = TclpGetDefaultStdChannel(type);
  Tcl_SetStdChannel(aChannel, type);
  if (aChannel)
  {
    Tcl_RegisterChannel(NULL, aChannel);
  }
}

static DWORD WINAPI tkLoop(const LPVOID theThreadParameter)
{
  (void)theThreadParameter;
  Tcl_CreateExitHandler(exitProc, 0);

  Draw_Interpretor& aCommands = Draw::GetInterpretor();
  aCommands.Init();
  Tcl_Interp* interp = aCommands.Interp();
  Tcl_Init(interp);

  ResetStdChannel(TCL_STDOUT);
  ResetStdChannel(TCL_STDERR);

  #if (TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 5))

  {
    Tcl_Channel aChannelIn  = Tcl_GetStdChannel(TCL_STDIN);
    Tcl_Channel aChannelOut = Tcl_GetStdChannel(TCL_STDOUT);
    Tcl_Channel aChannelErr = Tcl_GetStdChannel(TCL_STDERR);
    if (aChannelIn != NULL)
    {
      Tcl_RegisterChannel(aCommands.Interp(), aChannelIn);
    }
    if (aChannelOut != NULL)
    {
      Tcl_RegisterChannel(aCommands.Interp(), aChannelOut);
    }
    if (aChannelErr != NULL)
    {
      Tcl_RegisterChannel(aCommands.Interp(), aChannelErr);
    }
  }
  #endif

  #ifdef _TK

  if (!Draw_VirtualWindows)
  {
    try
    {
      OCC_CATCH_SIGNALS
      int res = Tk_Init(interp);
      if (res != TCL_OK)
      {
    #if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 5)))
        std::cout << "tkLoop: error in Tk initialization. Tcl reported: "
                  << Tcl_GetStringResult(interp) << std::endl;
    #else
        std::cout << "tkLoop: error in Tk initialization. Tcl reported: " << interp->result
                  << std::endl;
    #endif
      }
    }
    catch (const Standard_Failure&)
    {
      std::cout << "tkLoop: exception in TK_Init\n";
    }
    Tcl_StaticPackage(interp, "Tk", Tk_Init, (Tcl_PackageInitProc*)NULL);
    mainWindow = Tk_MainWindow(interp);
    if (mainWindow == NULL)
    {
    #if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 5)))
      fprintf(stderr, "%s\n", Tcl_GetStringResult(interp));
    #else
      fprintf(stderr, "%s\n", interp->result);
    #endif
      std::cout << "tkLoop: Tk_MainWindow() returned NULL. Exiting...\n";
      Tcl_Exit(0);
    }
    Tk_Name(mainWindow) = Tk_GetUid(Tk_SetAppName(mainWindow, "Draw"));
  }
  #endif

  OSD::SetSignal(false);

  isTkLoopStarted = true;

  while (console_semaphore == STOP_CONSOLE)
  {
    Tcl_DoOneEvent(TCL_ALL_EVENTS | TCL_DONT_WAIT);
  }

  if (Draw_IsConsoleSubsystem && console_semaphore == WAIT_CONSOLE_COMMAND)
  {
    Prompt(interp, 0);
  }

  bool toLoop = true;
  while (toLoop)
  {

    const bool isTclEventQueueEmpty = Tcl_DoOneEvent(TCL_ALL_EVENTS | TCL_DONT_WAIT) == 0;
    if (console_semaphore == HAS_CONSOLE_COMMAND)
    {
      const TCollection_AsciiString aCmdUtf8(console_command);
      const bool                    wasInterpreted = Draw_Interprete(aCmdUtf8.ToCString());
      if (Draw_IsConsoleSubsystem)
      {
        Prompt(interp, wasInterpreted ? 0 : 1);
      }
      console_semaphore = WAIT_CONSOLE_COMMAND;
    }
    else if (isTclEventQueueEmpty)
    {

      Sleep(1);
    }
  #ifdef _TK

    toLoop = (Draw_VirtualWindows || Tk_GetNumMainWindows() > 0);
  #endif
  }
  Tcl_Exit(0);
  #if (!((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION == 6) && (TCL_RELEASE_SERIAL >= 15)))
  return 0;
  #endif
}

void Run_Appli(HWND hWnd)
{
  MSG    msg;
  HACCEL hAccel = NULL;
  msg.wParam    = 1;

  DWORD  IDThread;
  HANDLE hThread;
  if (Draw_IsConsoleSubsystem)
  {
    hThread = CreateThread(NULL, 0, readStdinThreadFunc, NULL, 0, &IDThread);
    if (!hThread)
    {
      std::cout << "pb in creation of the thread reading stdin" << std::endl;
      Draw_IsConsoleSubsystem = false;
      Init_Appli(GetModuleHandleW(NULL), GetModuleHandleW(NULL), 1, hWnd);
    }
  }

  if (console_semaphore == STOP_CONSOLE)
  {
    console_semaphore = WAIT_CONSOLE_COMMAND;
  }

  while (GetMessageW(&msg, NULL, 0, 0) > 0)
  {
    if (!TranslateAcceleratorW(hWnd, hAccel, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessageW(&msg);
    }
  }
  ExitProcess(0);
}

void Destroy_Appli(HINSTANCE hInst)
{
  UnregisterAppClass(hInst);
  for (int i = 0; i < MAXCOLOR; ++i)
  {
    DeleteObject(Draw_colorPenTab[i]);
  }
}

#endif
