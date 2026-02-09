#ifdef _WIN32
  #include <windows.h>
#endif

#include <Draw_Main.hpp>
#include <cstdlib>
#include <Draw_Appli.hpp>
#include <TCollection_AsciiString.hpp>

#include <tcl.h>

#ifdef _WIN32
  #include <sys/stat.h>

extern Draw_Viewer dout;

Standard_IMPORT bool Draw_Interprete(const char* command);

static FDraw_InitAppli theDraw_InitAppli;
#endif

#ifdef _WIN32

extern bool Draw_IsConsoleSubsystem;

int Draw_Main(int, char* argv[], const FDraw_InitAppli fDraw_InitAppli)
{
  Draw_IsConsoleSubsystem = true;
  theDraw_InitAppli       = fDraw_InitAppli;

  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);

  #if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4)))
  Tcl_FindExecutable(argv[0]);
  #endif

  int       aNbArgs  = 0;
  wchar_t** anArgVec = CommandLineToArgvW(GetCommandLineW(), &aNbArgs);
  Draw_Appli(::GetModuleHandleW(NULL), NULL, SW_SHOW, aNbArgs, anArgVec, fDraw_InitAppli);
  LocalFree(anArgVec);
  return 0;
}

int Draw_WinMain(HINSTANCE hInstance,
                 HINSTANCE hPrevinstance,
                 LPSTR,
                 int                   nCmdShow,
                 const FDraw_InitAppli fDraw_InitAppli)
{
  theDraw_InitAppli  = fDraw_InitAppli;
  int       aNbArgs  = 0;
  wchar_t** anArgVec = CommandLineToArgvW(GetCommandLineW(), &aNbArgs);
  Draw_Appli(hInstance, hPrevinstance, nCmdShow, aNbArgs, anArgVec, fDraw_InitAppli);
  LocalFree(anArgVec);
  return 0;
}

#else

int Draw_Main(int argc, char* argv[], const FDraw_InitAppli fDraw_InitAppli)
{

  #if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4)))
  Tcl_FindExecutable(argv[0]);
  #endif
  Draw_Appli(argc, argv, fDraw_InitAppli);
  return 0;
}

#endif
