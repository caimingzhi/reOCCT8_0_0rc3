#pragma once


#include <Draw_Appli.hpp>
#include <Standard_PCharacter.hpp>

typedef void (*FDraw_InitAppli)(Draw_Interpretor&);

Standard_EXPORT int Draw_Main(int                   argc,
                              Standard_PCharacter   argv[],
                              const FDraw_InitAppli Draw_InitAppli);

// Declarations of macros DRAW_MAIN to be used in executables instead of explicit main/WinMain
#ifdef _WIN32

  #include <windows.h>

Standard_EXPORT int Draw_WinMain(HINSTANCE             hInstance,
                                 HINSTANCE             hPrevinstance,
                                 LPSTR                 lpCmdLine,
                                 int                   nCmdShow,
                                 const FDraw_InitAppli Draw_InitAppli);

  // WinMain() and main()
  #define DRAW_MAIN                                                                                \
    int PASCAL WinMain(HINSTANCE hInstance,                                                        \
                       HINSTANCE hPrevinstance,                                                    \
                       LPSTR     lpCmdLine,                                                        \
                       int       nCmdShow)                                                         \
    {                                                                                              \
      return Draw_WinMain(hInstance, hPrevinstance, lpCmdLine, nCmdShow, Draw_InitAppli);          \
    }                                                                                              \
                                                                                                   \
    int main(int argc, char* argv[])                                                               \
    {                                                                                              \
      return Draw_Main(argc, argv, Draw_InitAppli);                                                \
    }

#else

  // main()
  #define DRAW_MAIN                                                                                \
    int main(int argc, char* argv[])                                                               \
    {                                                                                              \
      return Draw_Main(argc, argv, Draw_InitAppli);                                                \
    }

#endif

