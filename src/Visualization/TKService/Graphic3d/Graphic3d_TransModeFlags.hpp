#pragma once

enum Graphic3d_TransModeFlags
{
  Graphic3d_TMF_None         = 0x0000,
  Graphic3d_TMF_ZoomPers     = 0x0002,
  Graphic3d_TMF_RotatePers   = 0x0008,
  Graphic3d_TMF_TriedronPers = 0x0020,

  Graphic3d_TMF_2d = 0x0040,

  Graphic3d_TMF_CameraPers     = 0x0080,
  Graphic3d_TMF_OrthoPers      = 0x0100,
  Graphic3d_TMF_AxialScalePers = 0x0200,
  Graphic3d_TMF_ZoomRotatePers = Graphic3d_TMF_ZoomPers | Graphic3d_TMF_RotatePers,
  Graphic3d_TMF_AxialZoomPers  = Graphic3d_TMF_ZoomPers | Graphic3d_TMF_AxialScalePers
};

inline Graphic3d_TransModeFlags operator|(Graphic3d_TransModeFlags a, Graphic3d_TransModeFlags b)
{
  return static_cast<Graphic3d_TransModeFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
