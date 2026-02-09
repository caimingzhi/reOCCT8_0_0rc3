#ifdef _WIN32

  #include <windows.h>

  #include <Draw_Window.hpp>

  #include "Draw_WNTCommandWindow.hpp"
  #include "Draw_WNTInit.hpp"
  #include "Draw_WNTMainWindow.hpp"
  #include "Draw_WNTRessource.hpp"

bool        Draw_Interprete(const char* command);
extern bool Draw_IsConsoleSubsystem;

LRESULT APIENTRY WndProc(HWND hWndFrame, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
  switch (wMsg)
  {
    case WM_CREATE:
    {
      CreateProc(hWndFrame);
      HWND hWndClient            = (HWND)GetWindowLongPtrW(hWndFrame, CLIENTWND);
      Draw_Window::hWndClientMDI = hWndClient;
      if (!Draw_IsConsoleSubsystem)
      {
        CreateCommandWindow(hWndFrame, 0);
      }
      return 0;
    }
    case WM_COMMAND:
    {
      CmdProc(hWndFrame, LOWORD(wParam), wParam, lParam);
      return 0;
    }
    case WM_DESTROY:
    {
      Draw_Interprete("exit");
      DestroyProc(hWndFrame);
      return 0;
    }
  }
  HWND hWndClient = (HWND)GetWindowLongPtrW(hWndFrame, CLIENTWND);
  return DefFrameProcW(hWndFrame, hWndClient, wMsg, wParam, lParam);
}

BOOL CreateProc(HWND hWndFrame)
{
  HWND hWnd = CreateMDIClientWindow(hWndFrame);
  if (hWnd != NULL)
  {

    SetWindowLongPtrW(hWndFrame, CLIENTWND, (LONG_PTR)hWnd);
  }
  return (TRUE);
}

LRESULT APIENTRY CmdProc(HWND hWndFrame, UINT wMsg, WPARAM, LPARAM)
{

  HWND hWndClient = (HWND)GetWindowLongPtrW(hWndFrame, CLIENTWND);
  switch (wMsg)
  {
    case IDM_WINDOW_NEXT:
    {
      if (hWndClient != NULL)
      {
        HWND hWndActive = (HWND)SendMessageW(hWndClient, WM_MDIGETACTIVE, 0, 0l);
        SendMessageW(hWndClient, WM_MDINEXT, (WPARAM)hWndActive, 0l);
      }
      break;
    }
    case IDM_WINDOW_CASCADE:
    {
      if (hWndClient != NULL)
      {
        SendMessageW(hWndClient, WM_MDICASCADE, 0, 0l);
      }
      break;
    }
    case IDM_WINDOW_TILEHOR:
    {
      if (hWndClient != NULL)
      {
        SendMessageW(hWndClient, WM_MDITILE, MDITILE_HORIZONTAL, 0l);
      }
      break;
    }
    case IDM_WINDOW_TILEVERT:
    {
      if (hWndClient != NULL)
      {
        SendMessageW(hWndClient, WM_MDITILE, MDITILE_VERTICAL, 0l);
      }
      break;
    }
    case IDM_FILE_EXIT:
    {
      Draw_Interprete("exit");
      DestroyProc(hWndFrame);
      break;
    }
  }
  return 0;
}

VOID DestroyProc(HWND hWnd)
{
  HINSTANCE hInst = (HINSTANCE)GetWindowLongPtrW(hWnd, GWLP_HINSTANCE);

  Destroy_Appli(hInst);
  PostQuitMessage(0);
}
#endif
