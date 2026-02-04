#pragma once


#include <Image_Texture.hpp>
#include <Quantity_ColorRGBA.hpp>

//! glTF 1.0 format common (obsolete) material definition.
class RWGltf_MaterialCommon : public Standard_Transient
{
public:
  occ::handle<Image_Texture> AmbientTexture;  //!< image defining ambient color
  occ::handle<Image_Texture> DiffuseTexture;  //!< image defining diffuse color
  occ::handle<Image_Texture> SpecularTexture; //!< image defining specular color
  TCollection_AsciiString    Id;              //!< material identifier
  TCollection_AsciiString    Name;            //!< material name
  Quantity_Color             AmbientColor;
  Quantity_Color             DiffuseColor;
  Quantity_Color             SpecularColor;
  Quantity_Color             EmissiveColor;
  float                      Shininess;
  float                      Transparency;

  RWGltf_MaterialCommon()
      : AmbientColor(0.1, 0.1, 0.1, Quantity_TOC_sRGB),
        DiffuseColor(0.8, 0.8, 0.8, Quantity_TOC_sRGB),
        SpecularColor(0.2, 0.2, 0.2, Quantity_TOC_sRGB),
        EmissiveColor(Quantity_NOC_BLACK),
        Shininess(1.0f),
        Transparency(0.0f)
  {
  }
};

