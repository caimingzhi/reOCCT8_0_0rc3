#pragma once

enum Graphic3d_StereoMode
{
  Graphic3d_StereoMode_QuadBuffer,
  Graphic3d_StereoMode_Anaglyph,
  Graphic3d_StereoMode_RowInterlaced,
  Graphic3d_StereoMode_ColumnInterlaced,
  Graphic3d_StereoMode_ChessBoard,
  Graphic3d_StereoMode_SideBySide,
  Graphic3d_StereoMode_OverUnder,
  Graphic3d_StereoMode_SoftPageFlip,
  Graphic3d_StereoMode_OpenVR,
};

enum
{
  Graphic3d_StereoMode_NB = Graphic3d_StereoMode_OpenVR + 1
};
