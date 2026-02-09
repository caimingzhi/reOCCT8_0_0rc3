#pragma once

#include <TopoDS_Shape.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Draw_Interpretor.hpp>

class MeshTest_CheckTopology
{
public:
  MeshTest_CheckTopology(const TopoDS_Shape& theShape)
      : myShape(theShape)
  {
  }

  Standard_EXPORT void Perform(Draw_Interpretor& di);

  int NbFacesWithFL() const { return myMapFaceLinks.Extent(); }

  int GetFaceNumWithFL(const int theIndex) const { return myMapFaceLinks.FindKey(theIndex); }

  int NbFreeLinks(const int theIndex) const { return myMapFaceLinks(theIndex)->Length() / 2; }

  Standard_EXPORT void GetFreeLink(const int theFaceIndex,
                                   const int theLinkIndex,
                                   int&      theNode1,
                                   int&      theNode2) const;

  int NbCrossFaceErrors() const { return myErrorsVal.Length(); }

  Standard_EXPORT void GetCrossFaceError(const int theIndex,
                                         int&      theFace1,
                                         int&      theNode1,
                                         int&      theFace2,
                                         int&      theNode2,
                                         double&   theValue) const;

  int NbAsyncEdges() const { return myAsyncEdges.Length(); }

  int GetAsyncEdgeNum(const int theIndex) const { return myAsyncEdges(theIndex); }

  int NbFreeNodes() const { return myFreeNodeFaces.Length(); }

  void GetFreeNodeNum(const int theIndex, int& theFaceNum, int& theNodeNum) const
  {
    theFaceNum = myFreeNodeFaces(theIndex);
    theNodeNum = myFreeNodeNums(theIndex);
  }

  int NbSmallTriangles() const { return mySmallTrianglesFaces.Length(); }

  void GetSmallTriangle(const int theIndex, int& theFaceNum, int& theNodeNum) const
  {
    theFaceNum = mySmallTrianglesFaces(theIndex);
    theNodeNum = mySmallTrianglesTriangles(theIndex);
  }

private:
  TopoDS_Shape                                                             myShape;
  NCollection_IndexedDataMap<int, occ::handle<NCollection_HSequence<int>>> myMapFaceLinks;

  NCollection_Sequence<int>    myErrors;
  NCollection_Sequence<double> myErrorsVal;

  NCollection_Sequence<int> myAsyncEdges;
  NCollection_Sequence<int> myFreeNodeFaces;
  NCollection_Sequence<int> myFreeNodeNums;
  NCollection_Sequence<int> mySmallTrianglesFaces;
  NCollection_Sequence<int> mySmallTrianglesTriangles;
};
