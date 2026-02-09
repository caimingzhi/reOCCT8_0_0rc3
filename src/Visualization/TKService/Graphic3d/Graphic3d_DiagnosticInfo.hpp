#pragma once

enum Graphic3d_DiagnosticInfo
{
  Graphic3d_DiagnosticInfo_Device         = 0x001,
  Graphic3d_DiagnosticInfo_FrameBuffer    = 0x002,
  Graphic3d_DiagnosticInfo_Limits         = 0x004,
  Graphic3d_DiagnosticInfo_Memory         = 0x008,
  Graphic3d_DiagnosticInfo_NativePlatform = 0x010,
  Graphic3d_DiagnosticInfo_Extensions     = 0x020,

  Graphic3d_DiagnosticInfo_Short = Graphic3d_DiagnosticInfo_Device
                                   | Graphic3d_DiagnosticInfo_FrameBuffer
                                   | Graphic3d_DiagnosticInfo_Limits,
  Graphic3d_DiagnosticInfo_Basic = Graphic3d_DiagnosticInfo_Short
                                   | Graphic3d_DiagnosticInfo_NativePlatform
                                   | Graphic3d_DiagnosticInfo_Memory,
  Graphic3d_DiagnosticInfo_Complete =
    Graphic3d_DiagnosticInfo_Basic | Graphic3d_DiagnosticInfo_Extensions
};
