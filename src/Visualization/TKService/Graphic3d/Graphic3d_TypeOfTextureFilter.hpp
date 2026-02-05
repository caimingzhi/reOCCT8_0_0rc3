#pragma once

//! Type of the texture filter.
//! Notice that for textures without mipmaps linear interpolation will be used instead of
//! TOTF_BILINEAR and TOTF_TRILINEAR.
enum Graphic3d_TypeOfTextureFilter
{
  Graphic3d_TOTF_NEAREST,
  Graphic3d_TOTF_BILINEAR,
  Graphic3d_TOTF_TRILINEAR
};
