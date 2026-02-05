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

// extern Standard_IMPORT bool Draw_Interprete(char* command); //for C21
Standard_IMPORT bool Draw_Interprete(const char* command); // for C30
// true if complete command

// necessary for WNT in C21 only
static FDraw_InitAppli theDraw_InitAppli; // pointer to the Draw_InitAppli
#endif

#ifdef _WIN32

//=======================================================================
// NOTE: OCC11
//     On Windows NT, both console (UNIX-like) and windowed (classical on
//     WNT, with three separated windows - input, output and graphic)
//     modes are supported.
//     Depending on compilation mode of executable (CONSOLE or WINDOWS),
//     either Draw_Main or Draw_WinMain becomes entry point;
//     the further different behaviour of DRAW is determined by variable
//     Draw_IsConsoleSubsystem which is set by Draw_Main only
//=======================================================================

extern bool Draw_IsConsoleSubsystem;

//=================================================================================================

int Draw_Main(int /*argc*/, char* argv[], const FDraw_InitAppli fDraw_InitAppli)
{
  Draw_IsConsoleSubsystem = true;
  theDraw_InitAppli       = fDraw_InitAppli;

  // Set console code page to UTF-8 so that input from cin and output to cout
  // pass Unicode symbols as expected
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);

  // MKV 01.02.05
  #if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4)))
  Tcl_FindExecutable(argv[0]);
  #endif

  int       aNbArgs  = 0;
  wchar_t** anArgVec = CommandLineToArgvW(GetCommandLineW(), &aNbArgs);
  Draw_Appli(::GetModuleHandleW(NULL), NULL, SW_SHOW, aNbArgs, anArgVec, fDraw_InitAppli);
  LocalFree(anArgVec);
  return 0;
}

//=================================================================================================

int Draw_WinMain(HINSTANCE hInstance,
                 HINSTANCE hPrevinstance,
                 LPSTR /*lpCmdLine*/,
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

//=================================================================================================

int Draw_Main(int argc, char* argv[], const FDraw_InitAppli fDraw_InitAppli)
{
  // MKV 01.02.05
  #if ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4)))
  Tcl_FindExecutable(argv[0]);
  #endif
  Draw_Appli(argc, argv, fDraw_InitAppli);
  return 0;
}

#endif
