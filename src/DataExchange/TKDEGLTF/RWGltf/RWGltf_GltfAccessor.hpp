#pragma once

#include <Graphic3d_BndBox3d.hpp>

enum RWGltf_GltfAccessorCompType
{
  RWGltf_GltfAccessorCompType_UNKNOWN,
  RWGltf_GltfAccessorCompType_Int8    = 5120,
  RWGltf_GltfAccessorCompType_UInt8   = 5121,
  RWGltf_GltfAccessorCompType_Int16   = 5122,
  RWGltf_GltfAccessorCompType_UInt16  = 5123,
  RWGltf_GltfAccessorCompType_UInt32  = 5125,
  RWGltf_GltfAccessorCompType_Float32 = 5126,
};

#include <RWGltf_GltfAccessorLayout.hpp>
#include <Standard_TypeDef.hpp>

struct RWGltf_GltfAccessor
{
  static const int INVALID_ID = -1;

public:
  int                         Id;
  int64_t                     ByteOffset;
  int64_t                     Count;
  int32_t                     ByteStride;
  RWGltf_GltfAccessorLayout   Type;
  RWGltf_GltfAccessorCompType ComponentType;
  Graphic3d_BndBox3d          BndBox;
  bool                        IsCompressed;

  RWGltf_GltfAccessor()
      : Id(INVALID_ID),
        ByteOffset(0),
        Count(0),
        ByteStride(0),
        Type(RWGltf_GltfAccessorLayout_UNKNOWN),
        ComponentType(RWGltf_GltfAccessorCompType_UNKNOWN),
        IsCompressed(false)
  {
  }
};
