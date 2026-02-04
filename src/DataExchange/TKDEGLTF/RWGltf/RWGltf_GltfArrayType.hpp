#pragma once


#include <Standard_CString.hpp>

//! Low-level glTF enumeration defining Array type.
enum RWGltf_GltfArrayType
{
  RWGltf_GltfArrayType_UNKNOWN,  //!< unknown or invalid type
  RWGltf_GltfArrayType_Indices,  //!< "indices"    within "primitive"  element
  RWGltf_GltfArrayType_Position, //!< "POSITION"   within "attributes" element
  RWGltf_GltfArrayType_Normal,   //!< "NORMAL"     within "attributes" element
  RWGltf_GltfArrayType_Color,    //!< "COLOR"      within "attributes" element
  RWGltf_GltfArrayType_TCoord0,  //!< "TEXCOORD_0" within "attributes" element
  RWGltf_GltfArrayType_TCoord1,  //!< "TEXCOORD_1" within "attributes" element
  RWGltf_GltfArrayType_Joint,    //!< "JOINT"      within "attributes" element
  RWGltf_GltfArrayType_Weight,   //!< "WEIGHT"     within "attributes" element
};

//! Parse GltfArrayType from string.
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

