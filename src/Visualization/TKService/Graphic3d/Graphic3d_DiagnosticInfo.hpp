#pragma once

//! Diagnostic info categories bit flags.
enum Graphic3d_DiagnosticInfo
{
  Graphic3d_DiagnosticInfo_Device      = 0x001, //!< device / vendor / version information
  Graphic3d_DiagnosticInfo_FrameBuffer = 0x002, //!< framebuffer information
  Graphic3d_DiagnosticInfo_Limits      = 0x004, //!< hardware limits
  Graphic3d_DiagnosticInfo_Memory      = 0x008, //!< memory counters
  Graphic3d_DiagnosticInfo_NativePlatform =
    0x010, //!< native platform API information (e.g. WGL / GLX / EGL)
  Graphic3d_DiagnosticInfo_Extensions = 0x020, //!< vendor extension list (usually very long)
  // groups
  Graphic3d_DiagnosticInfo_Short = Graphic3d_DiagnosticInfo_Device
                                   | Graphic3d_DiagnosticInfo_FrameBuffer
                                   | Graphic3d_DiagnosticInfo_Limits, //!< minimal information
  Graphic3d_DiagnosticInfo_Basic =
    Graphic3d_DiagnosticInfo_Short | Graphic3d_DiagnosticInfo_NativePlatform
    | Graphic3d_DiagnosticInfo_Memory, //!< basic information, without extension list
  Graphic3d_DiagnosticInfo_Complete =
    Graphic3d_DiagnosticInfo_Basic
    | Graphic3d_DiagnosticInfo_Extensions //!< complete information, including extension list
};
