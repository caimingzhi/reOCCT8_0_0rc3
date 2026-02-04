#pragma once


#include <NCollection_Buffer.hpp>
#include <RWGltf_GltfAccessor.hpp>
#include <RWGltf_GltfArrayType.hpp>
#include <TCollection_AsciiString.hpp>

//! An element within primitive array - vertex attribute or element indexes.
class RWGltf_GltfPrimArrayData
{
public:
  occ::handle<NCollection_Buffer> StreamData;
  TCollection_AsciiString         StreamUri;
  int64_t                         StreamOffset;
  int64_t                         StreamLength;

  RWGltf_GltfAccessor  Accessor;
  RWGltf_GltfArrayType Type;

  RWGltf_GltfPrimArrayData()
      : StreamOffset(0),
        StreamLength(0),
        Type(RWGltf_GltfArrayType_UNKNOWN)
  {
  }

  RWGltf_GltfPrimArrayData(RWGltf_GltfArrayType theType)
      : StreamOffset(0),
        StreamLength(0),
        Type(theType)
  {
  }
};

