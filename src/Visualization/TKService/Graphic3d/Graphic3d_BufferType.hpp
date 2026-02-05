#pragma once

//! Define buffers available for dump
enum Graphic3d_BufferType
{
  Graphic3d_BT_RGB,                 //!< color buffer without alpha component
  Graphic3d_BT_RGBA,                //!< color buffer
  Graphic3d_BT_Depth,               //!< depth buffer
  Graphic3d_BT_RGB_RayTraceHdrLeft, //!< left view HDR color buffer for Ray-Tracing
  Graphic3d_BT_Red,                 //!< color buffer, red channel
  Graphic3d_BT_ShadowMap,           //!< buffer with shadow map
};
