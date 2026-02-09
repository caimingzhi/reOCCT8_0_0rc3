#pragma once

#include <NCollection_IndexedMap.hpp>
#include <XCAFPrs_DocumentExplorer.hpp>

class RWGltf_GltfSceneNodeMap : public NCollection_IndexedMap<XCAFPrs_DocumentNode>
{
public:
  RWGltf_GltfSceneNodeMap() = default;

  int FindIndex(const TCollection_AsciiString& theNodeId) const
  {
    if (IsEmpty())
    {
      return 0;
    }
    XCAFPrs_DocumentNode aDocNode;
    aDocNode.Id = theNodeId;
    return NCollection_IndexedMap<XCAFPrs_DocumentNode>::FindIndex(aDocNode);
  }
};
