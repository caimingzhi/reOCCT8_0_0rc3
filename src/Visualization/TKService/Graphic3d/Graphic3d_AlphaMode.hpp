#pragma once

enum Graphic3d_AlphaMode
{
  Graphic3d_AlphaMode_Opaque = 0,
  Graphic3d_AlphaMode_Mask,

  Graphic3d_AlphaMode_Blend,
  Graphic3d_AlphaMode_MaskBlend,

  Graphic3d_AlphaMode_BlendAuto = -1,
};
