#pragma once


#include <Graphic3d_TextureUnit.hpp>

//! Standard texture units combination bits.
enum Graphic3d_TextureSetBits
{
  Graphic3d_TextureSetBits_NONE      = 0,
  Graphic3d_TextureSetBits_BaseColor = (unsigned int)(1 << int(Graphic3d_TextureUnit_BaseColor)),
  Graphic3d_TextureSetBits_Emissive  = (unsigned int)(1 << int(Graphic3d_TextureUnit_Emissive)),
  Graphic3d_TextureSetBits_Occlusion = (unsigned int)(1 << int(Graphic3d_TextureUnit_Occlusion)),
  Graphic3d_TextureSetBits_Normal    = (unsigned int)(1 << int(Graphic3d_TextureUnit_Normal)),
  Graphic3d_TextureSetBits_MetallicRoughness =
    (unsigned int)(1 << int(Graphic3d_TextureUnit_MetallicRoughness)),
};

