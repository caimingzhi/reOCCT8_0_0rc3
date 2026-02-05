#pragma once

//! Nature of the reflection of a material.
enum Graphic3d_TypeOfReflection
{
  Graphic3d_TOR_AMBIENT = 0,
  Graphic3d_TOR_DIFFUSE,
  Graphic3d_TOR_SPECULAR,
  Graphic3d_TOR_EMISSION
};

enum
{
  Graphic3d_TypeOfReflection_NB = 4
};
