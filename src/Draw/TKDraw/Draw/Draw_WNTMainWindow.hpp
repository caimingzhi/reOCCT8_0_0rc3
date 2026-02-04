#ifdef _WIN32

  #define CLIENTWND 0

  /*
  ** PROCEDURES DE MAIN WINDOW
  */
  #include <windows.h>

LRESULT APIENTRY WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL             CreateProc(HWND);
VOID             DestroyProc(HWND);
LRESULT APIENTRY CmdProc(HWND, UINT, WPARAM, LPARAM);

#endif
