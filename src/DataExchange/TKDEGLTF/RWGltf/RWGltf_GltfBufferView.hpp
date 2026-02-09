#pragma once

enum RWGltf_GltfBufferViewTarget
{
  RWGltf_GltfBufferViewTarget_UNKNOWN,
  RWGltf_GltfBufferViewTarget_ARRAY_BUFFER         = 34962,
  RWGltf_GltfBufferViewTarget_ELEMENT_ARRAY_BUFFER = 34963,
};

#include <Standard_TypeDef.hpp>

struct RWGltf_GltfBufferView
{
  static const int INVALID_ID = -1;

public:
  int                         Id;
  int64_t                     ByteOffset;
  int64_t                     ByteLength;
  int32_t                     ByteStride;
  RWGltf_GltfBufferViewTarget Target;

  RWGltf_GltfBufferView()
      : Id(INVALID_ID),
        ByteOffset(0),
        ByteLength(0),
        ByteStride(0),
        Target(RWGltf_GltfBufferViewTarget_UNKNOWN)
  {
  }
};
