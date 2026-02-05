#pragma once

#include <Quantity_Color.hpp>
#include <TCollection_AsciiString.hpp>

//! Material definition for OBJ file format.
struct RWObj_Material
{
  TCollection_AsciiString Name;        //!< material name (identifier) as defined in MTL file
                                       // clang-format off
  TCollection_AsciiString DiffuseTexture;  //!< path to the texture image file defining diffuse color
  TCollection_AsciiString SpecularTexture; //!< path to the texture image file defining specular color
                                       // clang-format on
  TCollection_AsciiString BumpTexture; //!< path to the texture image file defining normal map
  Quantity_Color          AmbientColor;
  Quantity_Color          DiffuseColor;
  Quantity_Color          SpecularColor;
  float                   Shininess;
  float                   Transparency;

  RWObj_Material()
      : AmbientColor(0.1, 0.1, 0.1, Quantity_TOC_sRGB),
        DiffuseColor(0.8, 0.8, 0.8, Quantity_TOC_sRGB),
        SpecularColor(0.2, 0.2, 0.2, Quantity_TOC_sRGB),
        Shininess(1.0f),
        Transparency(0.0f)
  {
  }
};
