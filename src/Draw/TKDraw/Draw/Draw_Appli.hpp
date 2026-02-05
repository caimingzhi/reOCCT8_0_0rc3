#pragma once

#include <Draw_Viewer.hpp>
#include <Draw.hpp>

typedef void (*FDraw_InitAppli)(Draw_Interpretor&);

#ifdef _WIN32
  #include <windows.h>
Standard_EXPORT void Draw_Appli(HINSTANCE,
                                HINSTANCE,
                                int,
                                int                   argc,
                                wchar_t**             argv,
                                const FDraw_InitAppli Draw_InitAppli);
#else
extern void Draw_Appli(int argc, char** argv, const FDraw_InitAppli Draw_InitAppli);
#endif

#ifndef _WIN32
extern Draw_Viewer dout;
extern bool        Draw_Batch;
#endif
