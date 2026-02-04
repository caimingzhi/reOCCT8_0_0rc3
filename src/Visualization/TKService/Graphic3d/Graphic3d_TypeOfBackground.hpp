#pragma once


//! Describes type of view background.
enum Graphic3d_TypeOfBackground
{
  Graphic3d_TOB_NONE = -1,
  Graphic3d_TOB_GRADIENT,
  Graphic3d_TOB_TEXTURE,
  Graphic3d_TOB_CUBEMAP
};

enum
{
  Graphic3d_TypeOfBackground_NB = Graphic3d_TOB_CUBEMAP + 1
};

