#ifdef _WIN32

  // include windows.h first to have all definitions available
  #include <windows.h>

  #include "Draw_Window.hpp"
  #include "Draw_WNTRessource.hpp"
  #include "Draw_WNTInit.hpp"
  #include "Draw_WNTMainWindow.hpp"
  #include "Draw_WNTCommandWindow.hpp"

  #define USEDEFAULT 200

/*--------------------------------------------------------*\
|  REGISTER APPLICATION CLASS
|  Enregistrement des classes de fenetres de l'application
|
\*--------------------------------------------------------*/
BOOL RegisterAppClass(HINSTANCE theInstance)
{
  WNDCLASSW wndClass;

  // Parametres communs aux classes
  //-----
  wndClass.style      = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC;
  wndClass.cbClsExtra = 0;
  wndClass.hCursor    = LoadCursor(NULL, IDC_ARROW);
  wndClass.hInstance  = theInstance;

  // Enregistrement de la fenetre principale
  //-----
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

  // Enregistrement de la fenetre DrawWindow
  //------
  wndClass.cbWndExtra    = sizeof(void*); // Extra Memory
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

  // Enregistrement de la fenetre CommandWindow
  //------
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

/*--------------------------------------------------------*\
|  UNREGISTER APPLICATION CLASS
|    Suppression des classes de fenetres de l'application
|
\*--------------------------------------------------------*/
VOID UnregisterAppClass(HINSTANCE theInstance)
{
  UnregisterClassW(APPCLASS, theInstance);
  UnregisterClassW(DRAWCLASS, theInstance);
}

/*--------------------------------------------------------*\
|  CREATE APPLICATION WINDOW
|    Creation de la fenetre Top-Level
|
\*--------------------------------------------------------*/
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

/*--------------------------------------------------------*\
|  CREATE MDI CLIENT WINDOW
|    Creation de la fenetre qui contient des fenetres MDI
|
\*--------------------------------------------------------*/
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
