#pragma once


//! Type of the texture file format.
enum Graphic3d_TypeOfTexture
{
  //! 1D texture (array).
  //! Note that this texture type might be unsupported by graphics API (emulated by 2D texture with
  //! 1 pixel height).
  Graphic3d_TypeOfTexture_1D,

  //! 2D texture (image plane).
  Graphic3d_TypeOfTexture_2D,

  //! 3D texture (a set of image planes).
  Graphic3d_TypeOfTexture_3D,

  //! Cubemap texture (6 image planes defining cube sides).
  Graphic3d_TypeOfTexture_CUBEMAP,

  //! Obsolete type - Graphic3d_TextureRoot::SetMipmapsGeneration() should be used instead.
  Graphic3d_TOT_2D_MIPMAP,

  // old aliases
  Graphic3d_TOT_1D      = Graphic3d_TypeOfTexture_1D,
  Graphic3d_TOT_2D      = Graphic3d_TypeOfTexture_2D,
  Graphic3d_TOT_CUBEMAP = Graphic3d_TypeOfTexture_CUBEMAP
};

