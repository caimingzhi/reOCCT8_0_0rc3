#pragma once

#include <Standard_Transient.hpp>
#include <BRepMesh_VertexTool.hpp>

class BRepMesh_Edge;

class BRepMesh_DataStructureOfDelaun : public Standard_Transient
{
public:
  Standard_EXPORT BRepMesh_DataStructureOfDelaun(
    const occ::handle<NCollection_IncAllocator>& theAllocator,
    const int                                    theReservedNodeSize = 100);

public:
  int NbNodes() const { return myNodes->Extent(); }

  Standard_EXPORT int AddNode(const BRepMesh_Vertex& theNode, const bool isForceAdd = false);

  int IndexOf(const BRepMesh_Vertex& theNode) { return myNodes->FindIndex(theNode); }

  const BRepMesh_Vertex& GetNode(const int theIndex) { return myNodes->FindKey(theIndex); }

  const BRepMesh_Vertex& operator()(const int theIndex) { return GetNode(theIndex); }

  Standard_EXPORT bool SubstituteNode(const int theIndex, const BRepMesh_Vertex& theNewNode);

  void RemoveNode(const int theIndex, const bool isForce = false)
  {
    if (isForce || myNodes->FindKey(theIndex).Movability() == BRepMesh_Free)
    {
      if (LinksConnectedTo(theIndex).Extent() == 0)
        myNodes->DeleteVertex(theIndex);
    }
  }

  const IMeshData::ListOfInteger& LinksConnectedTo(const int theIndex) const
  {
    return linksConnectedTo(theIndex);
  }

public:
  int NbLinks() const { return myLinks.Extent(); }

  Standard_EXPORT int AddLink(const BRepMesh_Edge& theLink);

  int IndexOf(const BRepMesh_Edge& theLink) const { return myLinks.FindIndex(theLink); }

  const BRepMesh_Edge& GetLink(const int theIndex) { return myLinks.FindKey(theIndex); }

  const IMeshData::MapOfInteger& LinksOfDomain() const { return myLinksOfDomain; }

  Standard_EXPORT bool SubstituteLink(const int theIndex, const BRepMesh_Edge& theNewLink);

  Standard_EXPORT void RemoveLink(const int theIndex, const bool isForce = false);

  const BRepMesh_PairOfIndex& ElementsConnectedTo(const int theLinkIndex) const
  {
    return myLinks.FindFromIndex(theLinkIndex);
  }

public:
  int NbElements() const { return myElements.Size(); }

  Standard_EXPORT int AddElement(const BRepMesh_Triangle& theElement);

  const BRepMesh_Triangle& GetElement(const int theIndex)
  {
    return myElements.ChangeValue(theIndex - 1);
  }

  const IMeshData::MapOfInteger& ElementsOfDomain() const { return myElementsOfDomain; }

  Standard_EXPORT bool SubstituteElement(const int                theIndex,
                                         const BRepMesh_Triangle& theNewElement);

  Standard_EXPORT void RemoveElement(const int theIndex);

  Standard_EXPORT void ElementNodes(const BRepMesh_Triangle& theElement, int (&theNodes)[3]);

  Standard_EXPORT void Dump(const char* theFileNameStr);

public:
  Standard_EXPORT void Statistics(Standard_OStream& theStream) const;

  const occ::handle<NCollection_IncAllocator>& Allocator() const { return myAllocator; }

  const occ::handle<BRepMesh_VertexTool>& Data() { return myNodes; }

  Standard_EXPORT void ClearDomain();

  void ClearDeleted()
  {
    clearDeletedLinks();
    clearDeletedNodes();
  }

  DEFINE_STANDARD_RTTIEXT(BRepMesh_DataStructureOfDelaun, Standard_Transient)

private:
  IMeshData::ListOfInteger& linksConnectedTo(const int theIndex) const
  {
    return (IMeshData::ListOfInteger&)myNodeLinks.Find(theIndex);
  }

  Standard_EXPORT void clearDeletedLinks();

  Standard_EXPORT void clearDeletedNodes();

  void cleanLink(const int theIndex, const BRepMesh_Edge& theLink);

  void cleanElement(const int theIndex, const BRepMesh_Triangle& theElement);

  void removeElementIndex(const int theIndex, BRepMesh_PairOfIndex& thePair);

private:
  occ::handle<NCollection_IncAllocator> myAllocator;
  occ::handle<BRepMesh_VertexTool>      myNodes;
  IMeshData::DMapOfIntegerListOfInteger myNodeLinks;
  IMeshData::IDMapOfLink                myLinks;
  IMeshData::ListOfInteger              myDelLinks;
  IMeshData::VectorOfElements           myElements;
  IMeshData::MapOfInteger               myElementsOfDomain;
  IMeshData::MapOfInteger               myLinksOfDomain;
};
