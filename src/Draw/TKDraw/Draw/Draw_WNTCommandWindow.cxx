#ifdef _WIN32

  #include <windows.h>

  #include <Draw_Window.hpp>
  #include <Draw_Appli.hpp>
  #include <TCollection_AsciiString.hpp>

  #include "Draw_WNTMainWindow.hpp"
  #include "Draw_WNTCommandWindow.hpp"

  #define CLIENTWND 0

  #define THE_PROMPT L"Command >> "
  #define COMMANDSIZE 1000

bool Draw_Interprete(const char* command);

namespace
{

  static WNDPROC OldEditProc;
}

HWND CreateCommandWindow(HWND hWnd, int)
{
  HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtrW(hWnd, GWLP_HINSTANCE);

  HWND hWndCommand = CreateWindowW(COMMANDCLASS,
                                   COMMANDTITLE,
                                   WS_CLIPCHILDREN | WS_OVERLAPPED | WS_THICKFRAME | WS_CAPTION,
                                   0,
                                   0,
                                   400,
                                   100,
                                   hWnd,
                                   NULL,
                                   hInstance,
                                   NULL);

  ShowWindow(hWndCommand, SW_SHOW);
  return hWndCommand;
}

LRESULT APIENTRY CommandProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
  switch (wMsg)
  {
    case WM_CREATE:
    {
      CommandCreateProc(hWnd);
      HWND hWndEdit = (HWND)GetWindowLongPtrW(hWnd, CLIENTWND);
      SendMessageW(hWndEdit, EM_REPLACESEL, 0, (LPARAM)THE_PROMPT);
      return 0;
    }
    case WM_GETMINMAXINFO:
    {
      MINMAXINFO* lpmmi       = (MINMAXINFO*)lParam;
      lpmmi->ptMinTrackSize.x = 200;
      lpmmi->ptMinTrackSize.y = 50;
      return 0;
    }
    case WM_SIZE:
    {
      HWND hWndEdit = (HWND)GetWindowLongPtrW(hWnd, CLIENTWND);
      MoveWindow(hWndEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);

      LRESULT index = SendMessageW(hWnd, WM_GETTEXTLENGTH, 0l, 0l);
      SendMessageW(hWnd, EM_SETSEL, index, index);
      return 0;
    }
    case WM_SETFOCUS:
    {
      HWND hWndEdit = (HWND)GetWindowLongPtrW(hWnd, CLIENTWND);
      SetFocus(hWndEdit);
      return 0;
    }
  }
  return DefWindowProcW(hWnd, wMsg, wParam, lParam);
}

LRESULT APIENTRY EditProc(HWND, UINT, WPARAM, LPARAM);

BOOL CommandCreateProc(HWND hWnd)
{
  HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtrW(hWnd, GWLP_HINSTANCE);
  HWND      hWndEdit =
    CreateWindowW(L"EDIT",
                  NULL,
                  WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
                  0,
                  0,
                  0,
                  0,
                  hWnd,
                  0,
                  hInstance,
                  NULL);

  if (hWndEdit != NULL)
  {
    SetWindowLongPtrW(hWnd, CLIENTWND, (LONG_PTR)hWndEdit);
  }

  OldEditProc = (WNDPROC)GetWindowLongPtrW(hWndEdit, GWLP_WNDPROC);

  SetWindowLongPtrW(hWndEdit, GWLP_WNDPROC, (LONG_PTR)EditProc);
  return TRUE;
}

int GetCommand(HWND hWnd, wchar_t* theBuffer)
{
  bool    isAgain                = true;
  wchar_t aTempBuff[COMMANDSIZE] = L"";

  int aNbLine  = (int)SendMessageW(hWnd, EM_GETLINECOUNT, 0l, 0l);
  int aNbChar  = 0;
  theBuffer[0] = L'\0';
  while (isAgain && aNbLine > -1 && aNbChar < COMMANDSIZE - 1)
  {
    wcscat(theBuffer, _wcsrev(aTempBuff));

    WORD* aNbMaxChar = (WORD*)aTempBuff;
    *aNbMaxChar      = COMMANDSIZE - 1;

    const int aNbCharRead = (int)SendMessageW(hWnd, EM_GETLINE, aNbLine - 1, (LPARAM)aTempBuff);
    aNbChar += aNbCharRead;
    const bool isPromp     = wcsncmp(aTempBuff, THE_PROMPT, 10) == 0;
    aTempBuff[aNbCharRead] = '\0';
    if (isPromp)
    {
      wcscat(theBuffer, _wcsrev(aTempBuff));
      isAgain = false;
    }
    aNbLine -= 1;
  }
  _wcsrev(theBuffer);
  return aNbChar;
}

LRESULT APIENTRY EditProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
  static LRESULT nbline;
  switch (wMsg)
  {
    case WM_CHAR:
    {
      if (console_semaphore != WAIT_CONSOLE_COMMAND)
      {
        return 0;
      }
      switch (LOWORD(wParam))
      {

        case 0x0d:
        {
          wchar_t aCmdBuffer[COMMANDSIZE];
          GetCommand(hWnd, aCmdBuffer);

          CallWindowProcW(OldEditProc, hWnd, wMsg, wParam, lParam);

          POINT pos;
          GetCaretPos(&pos);
          SendMessageW(hWnd, EM_REPLACESEL, 0, (LPARAM)THE_PROMPT);

          TCollection_AsciiString aCmdUtf8(aCmdBuffer + sizeof(THE_PROMPT) / sizeof(wchar_t) - 1);
          std::cout << aCmdUtf8.ToCString() << std::endl;

          wcscpy_s(console_command, aCmdBuffer + sizeof(THE_PROMPT) / sizeof(wchar_t) - 1);
          console_semaphore = HAS_CONSOLE_COMMAND;

          nbline = SendMessageW(hWnd, EM_GETLINECOUNT, 0l, 0l);
          if (nbline > 200)
          {
            nbline = 0;
            GetCommand(hWnd, aCmdBuffer);
            LRESULT index = SendMessageW(hWnd, EM_LINEINDEX, 100, 0);
            SendMessageW(hWnd, EM_SETSEL, 0, index);
            SendMessageW(hWnd, WM_CUT, 0, 0);

            index = SendMessageW(hWnd, WM_GETTEXTLENGTH, 0l, 0l);
            SendMessageW(hWnd, EM_SETSEL, index, index);
          }
          return 0;
        }
        default:
        {
          if (IsAlphanumeric((char)LOWORD(wParam)))
          {

            LRESULT index = SendMessageW(hWnd, WM_GETTEXTLENGTH, 0l, 0l);
            SendMessageW(hWnd, EM_SETSEL, index, index);
            CallWindowProcW(OldEditProc, hWnd, wMsg, wParam, lParam);
            return 0;
          }
          break;
        }
      }
      break;
    }
    case WM_KEYDOWN:
    {
      if (console_semaphore != WAIT_CONSOLE_COMMAND)
      {
        return 0;
      }
      break;
    }
  }
  return CallWindowProcW(OldEditProc, hWnd, wMsg, wParam, lParam);
}
#endif
