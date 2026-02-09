#pragma once

#include <Standard_CString.hpp>

enum RWGltf_GltfArrayType
{
  RWGltf_GltfArrayType_UNKNOWN,
  RWGltf_GltfArrayType_Indices,
  RWGltf_GltfArrayType_Position,
  RWGltf_GltfArrayType_Normal,
  RWGltf_GltfArrayType_Color,
  RWGltf_GltfArrayType_TCoord0,
  RWGltf_GltfArrayType_TCoord1,
  RWGltf_GltfArrayType_Joint,
  RWGltf_GltfArrayType_Weight,
};

inline RWGltf_GltfArrayType RWGltf_GltfParseAttribType(const char* theType)
{
  if (IsEqual("POSITION", theType))
  {
    return RWGltf_GltfArrayType_Position;
  }
  else if (IsEqual("NORMAL", theType))
  {
    return RWGltf_GltfArrayType_Normal;
  }
  else if (IsEqual("COLOR", theType))
  {
    return RWGltf_GltfArrayType_Color;
  }
  else if (IsEqual("TEXCOORD_0", theType))
  {
    return RWGltf_GltfArrayType_TCoord0;
  }
  else if (IsEqual("TEXCOORD_1", theType))
  {
    return RWGltf_GltfArrayType_TCoord1;
  }
  else if (IsEqual("JOINT", theType))
  {
    return RWGltf_GltfArrayType_Joint;
  }
  else if (IsEqual("WEIGHT", theType))
  {
    return RWGltf_GltfArrayType_Weight;
  }
  return RWGltf_GltfArrayType_UNKNOWN;
}
