#ifdef _WIN32

  #include <windows.h>

  #include "Draw_Window.hpp"
  #include "Draw_WNTRessource.hpp"
  #include "Draw_WNTInit.hpp"
  #include "Draw_WNTMainWindow.hpp"
  #include "Draw_WNTCommandWindow.hpp"

  #define USEDEFAULT 200

BOOL RegisterAppClass(HINSTANCE theInstance)
{
  WNDCLASSW wndClass;

  wndClass.style      = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC;
  wndClass.cbClsExtra = 0;
  wndClass.hCursor    = LoadCursor(NULL, IDC_ARROW);
  wndClass.hInstance  = theInstance;

  wndClass.cbWndExtra    = sizeof(void*);
  wndClass.lpfnWndProc   = (WNDPROC)WndProc;
  wndClass.hIcon         = LoadIconW(theInstance, MAKEINTRESOURCEW(IDI_ICON1));
  wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wndClass.lpszMenuName  = MAKEINTRESOURCEW(APPMENU);
  wndClass.lpszClassName = APPCLASS;
  if (!RegisterClassW(&wndClass))
  {
    return FALSE;
  }

  wndClass.cbWndExtra    = sizeof(void*);
  wndClass.lpfnWndProc   = (WNDPROC)Draw_Window::DrawProc;
  wndClass.hIcon         = 0;
  wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wndClass.lpszMenuName  = NULL;
  wndClass.lpszClassName = DRAWCLASS;
  if (!RegisterClassW(&wndClass))
  {
    UnregisterClassW(APPCLASS, theInstance);
    return FALSE;
  }

  wndClass.lpfnWndProc   = (WNDPROC)CommandProc;
  wndClass.hIcon         = 0;
  wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wndClass.lpszMenuName  = NULL;
  wndClass.lpszClassName = COMMANDCLASS;
  if (!RegisterClassW(&wndClass))
  {
    UnregisterClassW(APPCLASS, theInstance);
    UnregisterClassW(DRAWCLASS, theInstance);
    return FALSE;
  }

  return TRUE;
}

VOID UnregisterAppClass(HINSTANCE theInstance)
{
  UnregisterClassW(APPCLASS, theInstance);
  UnregisterClassW(DRAWCLASS, theInstance);
}

HWND CreateAppWindow(HINSTANCE theInstance)
{
  return CreateWindowW(APPCLASS,
                       APPTITLE,
                       WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                       400,
                       0,
                       623,
                       767,
                       NULL,
                       NULL,
                       theInstance,
                       NULL);
}

HWND CreateMDIClientWindow(HWND theWndFrame)
{
  CLIENTCREATESTRUCT ccs;
  ccs.hWindowMenu  = NULL;
  ccs.idFirstChild = 0;

  HINSTANCE hInstance  = (HINSTANCE)GetWindowLongPtrW(theWndFrame, GWLP_HINSTANCE);
  HWND      hWndClient = CreateWindowW(L"MDICLIENT",
                                  NULL,
                                  WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | MDIS_ALLCHILDSTYLES,
                                  0,
                                  0,
                                  1,
                                  1,
                                  theWndFrame,
                                  NULL,
                                  hInstance,
                                  (LPVOID)&ccs);
  return hWndClient;
}
#endif
