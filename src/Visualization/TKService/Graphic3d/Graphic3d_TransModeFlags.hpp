#pragma once


//! Transform Persistence Mode defining whether to lock in object position, rotation and / or
//! zooming relative to camera position.
enum Graphic3d_TransModeFlags
{
  Graphic3d_TMF_None         = 0x0000, //!< no persistence attributes (normal 3D object)
  Graphic3d_TMF_ZoomPers     = 0x0002, //!< object does not resize
  Graphic3d_TMF_RotatePers   = 0x0008, //!< object does not rotate;
  Graphic3d_TMF_TriedronPers = 0x0020, //!< object behaves like trihedron - it is fixed at the
                                       //!< corner of view and does not resizing (but rotating)
  Graphic3d_TMF_2d = 0x0040, //!< object is defined in 2D screen coordinates (pixels) and does not
                             //!< resize, pan and rotate
  Graphic3d_TMF_CameraPers = 0x0080, //!< object is in front of the camera
  Graphic3d_TMF_OrthoPers =
    0x0100, //!< object is forced to be rendered with orthographic projection.
  Graphic3d_TMF_AxialScalePers = 0x0200, //!< object does not resize with axial scale
  Graphic3d_TMF_ZoomRotatePers =
    Graphic3d_TMF_ZoomPers | Graphic3d_TMF_RotatePers, //!< object doesn't resize and rotate
  Graphic3d_TMF_AxialZoomPers =
    Graphic3d_TMF_ZoomPers | Graphic3d_TMF_AxialScalePers //!< object does not visually resize with
                                                          //!< either object or axial scale
};

//! Bitwise OR operator for transform persistence mode flags. Be aware that some flags combinations
//! are not valid.
inline Graphic3d_TransModeFlags operator|(Graphic3d_TransModeFlags a, Graphic3d_TransModeFlags b)
{
  return static_cast<Graphic3d_TransModeFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

