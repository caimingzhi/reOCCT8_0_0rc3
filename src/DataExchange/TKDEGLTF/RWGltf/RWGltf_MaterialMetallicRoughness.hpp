#pragma once

#include <NCollection_Vec2.hpp>

#include <Standard_TypeDef.hpp>

#include <NCollection_Vec3.hpp>

#include <NCollection_Vec4.hpp>

#include <NCollection_Mat4.hpp>
#include <Quantity_ColorRGBA.hpp>

#include <Standard_CString.hpp>

enum RWGltf_GltfAlphaMode
{
  RWGltf_GltfAlphaMode_Opaque,
  RWGltf_GltfAlphaMode_Mask,

  RWGltf_GltfAlphaMode_Blend,
};

inline RWGltf_GltfAlphaMode RWGltf_GltfParseAlphaMode(const char* theType)
{
  if (IsEqual("OPAQUE", theType))
  {
    return RWGltf_GltfAlphaMode_Opaque;
  }
  else if (IsEqual("MASK", theType))
  {
    return RWGltf_GltfAlphaMode_Mask;
  }
  else if (IsEqual("BLEND", theType))
  {
    return RWGltf_GltfAlphaMode_Blend;
  }
  return RWGltf_GltfAlphaMode_Opaque;
}

#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>

class Image_Texture;

class RWGltf_MaterialMetallicRoughness : public Standard_Transient
{
public:
  occ::handle<Image_Texture> BaseColorTexture;

  occ::handle<Image_Texture> MetallicRoughnessTexture;
  occ::handle<Image_Texture> EmissiveTexture;
  occ::handle<Image_Texture> OcclusionTexture;
  occ::handle<Image_Texture> NormalTexture;
  TCollection_AsciiString    Id;
  TCollection_AsciiString    Name;
  Quantity_ColorRGBA         BaseColor;
  NCollection_Vec3<float>    EmissiveFactor;
  float                      Metallic;
  float                      Roughness;
  float                      AlphaCutOff;
  RWGltf_GltfAlphaMode       AlphaMode;
  bool                       IsDoubleSided;

  RWGltf_MaterialMetallicRoughness()
      : BaseColor(1.0f, 1.0f, 1.0f, 1.0f),
        EmissiveFactor(0.0f, 0.0f, 0.0f),
        Metallic(1.0f),
        Roughness(1.0f),
        AlphaCutOff(0.5f),
        AlphaMode(RWGltf_GltfAlphaMode_Opaque),
        IsDoubleSided(false)
  {
  }
};
