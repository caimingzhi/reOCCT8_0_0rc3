#pragma once

#include <Standard_Transient.hpp>
#include <BRepMesh_DataStructureOfDelaun.hpp>
#include <BRepMesh_Triangle.hpp>
#include <IMeshData_Types.hpp>

class BRepMesh_Vertex;
class BRepMesh_Edge;

class BRepMesh_SelectorOfDataStructureOfDelaun : public Standard_Transient
{
public:
  Standard_EXPORT BRepMesh_SelectorOfDataStructureOfDelaun();

  Standard_EXPORT BRepMesh_SelectorOfDataStructureOfDelaun(
    const occ::handle<BRepMesh_DataStructureOfDelaun>& theMesh);

  Standard_EXPORT void Initialize(const occ::handle<BRepMesh_DataStructureOfDelaun>& theMesh);

  Standard_EXPORT void NeighboursOf(const BRepMesh_Vertex& theNode);

  Standard_EXPORT void NeighboursOfNode(const int theNodeIndex);

  Standard_EXPORT void NeighboursOf(const BRepMesh_Edge& theLink);

  Standard_EXPORT void NeighboursOfLink(const int theLinkIndex);

  Standard_EXPORT void NeighboursOf(const BRepMesh_Triangle& theElement);

  Standard_EXPORT void NeighboursOfElement(const int theElementIndex);

  Standard_EXPORT void NeighboursByEdgeOf(const BRepMesh_Triangle& theElement);

  void NeighboursOf(const BRepMesh_SelectorOfDataStructureOfDelaun&) {}

  void AddNeighbours() {}

  const IMeshData::MapOfInteger& Nodes() const { return myNodes; }

  const IMeshData::MapOfInteger& Links() const { return myLinks; }

  const IMeshData::MapOfInteger& Elements() const { return myElements; }

  const IMeshData::MapOfInteger& FrontierLinks() const { return myFrontier; }

  DEFINE_STANDARD_RTTIEXT(BRepMesh_SelectorOfDataStructureOfDelaun, Standard_Transient)

private:
  void elementsOfLink(const int theIndex);

private:
  occ::handle<BRepMesh_DataStructureOfDelaun> myMesh;
  IMeshData::MapOfInteger                     myNodes;
  IMeshData::MapOfInteger                     myLinks;
  IMeshData::MapOfInteger                     myElements;
  IMeshData::MapOfInteger                     myFrontier;
};
