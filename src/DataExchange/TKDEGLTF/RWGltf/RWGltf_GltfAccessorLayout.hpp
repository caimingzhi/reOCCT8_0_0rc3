#pragma once

#include <Standard_CString.hpp>

//! Low-level glTF enumeration defining Accessor layout.
//! Similar to Graphic3d_TypeOfData but does not define actual type and includes matrices.
enum RWGltf_GltfAccessorLayout
{
  RWGltf_GltfAccessorLayout_UNKNOWN, //!< unknown or invalid type
  RWGltf_GltfAccessorLayout_Scalar,  //!< "SCALAR"
  RWGltf_GltfAccessorLayout_Vec2,    //!< "VEC2"
  RWGltf_GltfAccessorLayout_Vec3,    //!< "VEC3"
  RWGltf_GltfAccessorLayout_Vec4,    //!< "VEC4"
  RWGltf_GltfAccessorLayout_Mat2,    //!< "MAT2"
  RWGltf_GltfAccessorLayout_Mat3,    //!< "MAT3"
  RWGltf_GltfAccessorLayout_Mat4,    //!< "MAT4"
};

//! Parse GltfAccessorLayout from string.
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
