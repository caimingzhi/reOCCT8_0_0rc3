#pragma once

#include <Standard_CString.hpp>

enum RWGltf_GltfAccessorLayout
{
  RWGltf_GltfAccessorLayout_UNKNOWN,
  RWGltf_GltfAccessorLayout_Scalar,
  RWGltf_GltfAccessorLayout_Vec2,
  RWGltf_GltfAccessorLayout_Vec3,
  RWGltf_GltfAccessorLayout_Vec4,
  RWGltf_GltfAccessorLayout_Mat2,
  RWGltf_GltfAccessorLayout_Mat3,
  RWGltf_GltfAccessorLayout_Mat4,
};

inline RWGltf_GltfAccessorLayout RWGltf_GltfParseAccessorType(const char* theType)
{
  if (IsEqual("SCALAR", theType))
  {
    return RWGltf_GltfAccessorLayout_Scalar;
  }
  else if (IsEqual("VEC2", theType))
  {
    return RWGltf_GltfAccessorLayout_Vec2;
  }
  else if (IsEqual("VEC3", theType))
  {
    return RWGltf_GltfAccessorLayout_Vec3;
  }
  else if (IsEqual("VEC4", theType))
  {
    return RWGltf_GltfAccessorLayout_Vec4;
  }
  else if (IsEqual("MAT2", theType))
  {
    return RWGltf_GltfAccessorLayout_Mat2;
  }
  else if (IsEqual("MAT3", theType))
  {
    return RWGltf_GltfAccessorLayout_Mat3;
  }
  else if (IsEqual("MAT4", theType))
  {
    return RWGltf_GltfAccessorLayout_Mat4;
  }
  return RWGltf_GltfAccessorLayout_UNKNOWN;
}
