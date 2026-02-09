#pragma once

enum Graphic3d_ShaderFlags
{
  Graphic3d_ShaderFlags_VertColor  = 0x0001,
  Graphic3d_ShaderFlags_TextureRGB = 0x0002,
  Graphic3d_ShaderFlags_TextureEnv = 0x0004,
  Graphic3d_ShaderFlags_TextureNormal =
    Graphic3d_ShaderFlags_TextureRGB | Graphic3d_ShaderFlags_TextureEnv,
  Graphic3d_ShaderFlags_PointSimple = 0x0008,
  Graphic3d_ShaderFlags_PointSprite = 0x0010,
  Graphic3d_ShaderFlags_PointSpriteA =
    Graphic3d_ShaderFlags_PointSimple | Graphic3d_ShaderFlags_PointSprite,
  Graphic3d_ShaderFlags_StippleLine = 0x0020,
  Graphic3d_ShaderFlags_ClipPlanes1 = 0x0040,
  Graphic3d_ShaderFlags_ClipPlanes2 = 0x0080,
  Graphic3d_ShaderFlags_ClipPlanesN =
    Graphic3d_ShaderFlags_ClipPlanes1 | Graphic3d_ShaderFlags_ClipPlanes2,
  Graphic3d_ShaderFlags_ClipChains      = 0x0100,
  Graphic3d_ShaderFlags_MeshEdges       = 0x0200,
  Graphic3d_ShaderFlags_AlphaTest       = 0x0400,
  Graphic3d_ShaderFlags_WriteOit        = 0x0800,
  Graphic3d_ShaderFlags_OitDepthPeeling = 0x1000,

  Graphic3d_ShaderFlags_NB      = 0x2000,
  Graphic3d_ShaderFlags_IsPoint = Graphic3d_ShaderFlags_PointSimple
                                  | Graphic3d_ShaderFlags_PointSprite
                                  | Graphic3d_ShaderFlags_PointSpriteA,
  Graphic3d_ShaderFlags_HasTextures =
    Graphic3d_ShaderFlags_TextureRGB | Graphic3d_ShaderFlags_TextureEnv,
  Graphic3d_ShaderFlags_NeedsGeomShader = Graphic3d_ShaderFlags_MeshEdges,
};
