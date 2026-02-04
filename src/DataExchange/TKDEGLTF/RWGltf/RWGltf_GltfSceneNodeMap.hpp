#pragma once


#include <NCollection_IndexedMap.hpp>
#include <XCAFPrs_DocumentExplorer.hpp>

//! Indexed map of scene nodes with custom search algorithm.
class RWGltf_GltfSceneNodeMap : public NCollection_IndexedMap<XCAFPrs_DocumentNode>
{
public:
  //! Empty constructor.
  RWGltf_GltfSceneNodeMap() = default;

  //! Find index from document node string identifier.
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

