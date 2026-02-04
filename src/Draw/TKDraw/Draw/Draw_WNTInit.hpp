#ifdef _WIN32

  #define APPCLASS L"TDRAW"
  #define APPTITLE L"Windows NT TDRAW"
  #include <windows.h>

BOOL RegisterAppClass(HINSTANCE);
VOID UnregisterAppClass(HINSTANCE);
HWND CreateAppWindow(HINSTANCE);
HWND CreateMDIClientWindow(HWND);

#endif
