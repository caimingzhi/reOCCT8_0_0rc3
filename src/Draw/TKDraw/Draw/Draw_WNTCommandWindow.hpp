#ifdef _WIN32

  #define COMMANDCLASS L"COMMANDWINDOW"
  #define COMMANDTITLE L"Command Window"

HWND             CreateCommandWindow(HWND, int);
LRESULT APIENTRY CommandProc(HWND, UINT, WPARAM, LPARAM);
BOOL             CommandCreateProc(HWND);
VOID             CommandDestroyProc(HWND);
BOOL             CommandHandler(HWND, WPARAM, LPARAM);

  #include <sys/stat.h>
  #include <tcl.h>
  #include <Standard_Macro.hpp>
  #include <iostream>
  #include <iomanip>
  #include <fstream>
  #include <stdio.h>
  #include <fcntl.h>

#endif
