#pragma once

#include <Quantity_Color.hpp>
#include <TCollection_AsciiString.hpp>

struct RWObj_Material
{
  TCollection_AsciiString Name;

  TCollection_AsciiString DiffuseTexture;
  TCollection_AsciiString SpecularTexture;

  TCollection_AsciiString BumpTexture;
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
