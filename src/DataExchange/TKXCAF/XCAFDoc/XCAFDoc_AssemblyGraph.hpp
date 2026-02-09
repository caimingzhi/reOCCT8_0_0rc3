#pragma once

#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TColStd_PackedMapOfInteger.hpp>

class TDF_Label;
class TDocStd_Document;
class XCAFDoc_ShapeTool;

class XCAFDoc_AssemblyGraph : public Standard_Transient
{
public:
  enum NodeType
  {
    NodeType_UNDEFINED = 0,
    NodeType_AssemblyRoot,
    NodeType_Subassembly,
    NodeType_Occurrence,
    NodeType_Part,
    NodeType_Subshape
  };

  typedef NCollection_DataMap<int, TColStd_PackedMapOfInteger> AdjacencyMap;

public:
  class Iterator
  {
  public:
    Standard_EXPORT Iterator(const occ::handle<XCAFDoc_AssemblyGraph>& theGraph,
                             const int                                 theNode = 1);

    bool More() const { return myCurrentIndex <= myGraph->NbNodes(); }

    int Current() const { return myCurrentIndex; }

    void Next() { ++myCurrentIndex; }

  private:
    occ::handle<XCAFDoc_AssemblyGraph> myGraph;
    int                                myCurrentIndex;
  };

public:
  Standard_EXPORT XCAFDoc_AssemblyGraph(const occ::handle<TDocStd_Document>& theDoc);

  Standard_EXPORT XCAFDoc_AssemblyGraph(const TDF_Label& theLabel);

  const occ::handle<XCAFDoc_ShapeTool>& GetShapeTool() const { return myShapeTool; }

  const TColStd_PackedMapOfInteger& GetRoots() const { return myRoots; }

  Standard_EXPORT bool IsDirectLink(const int theNode1, const int theNode2) const;

  bool HasChildren(const int theNode) const { return myAdjacencyMap.IsBound(theNode); }

  const TColStd_PackedMapOfInteger& GetChildren(const int theNode) const
  {
    return myAdjacencyMap(theNode);
  }

  Standard_EXPORT NodeType GetNodeType(const int theNode) const;

  const TDF_Label& GetNode(const int theNode) const { return myNodes(theNode); }

  const NCollection_IndexedMap<TDF_Label>& GetNodes() const { return myNodes; }

  int NbNodes() const { return myNodes.Extent(); }

  const AdjacencyMap& GetLinks() const { return myAdjacencyMap; }

  Standard_EXPORT int NbLinks() const;

  Standard_EXPORT int NbOccurrences(const int theNode) const;

private:
  Standard_EXPORT void buildGraph(const TDF_Label& theLabel);

  Standard_EXPORT void addComponents(const TDF_Label& theParent, const int theParentId);

  Standard_EXPORT int addNode(const TDF_Label& theLabel, const int theParentId);

private:
  occ::handle<XCAFDoc_ShapeTool> myShapeTool;
  TColStd_PackedMapOfInteger     myRoots;

  NCollection_IndexedMap<TDF_Label> myNodes;

  AdjacencyMap                       myAdjacencyMap;
  NCollection_DataMap<int, NodeType> myNodeTypes;
  NCollection_DataMap<int, int>      myUsages;
};
