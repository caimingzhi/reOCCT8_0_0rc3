#pragma once


#include <TopoDS_Shape.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Draw_Interpretor.hpp>

//! This class checks topology of the mesh presented by
//! triangulations of faces.
//!
//! The following error are reported:
//! - free links. A link is considered free if it has only one
//!   neighboring triangle and at least one of its nodes belongs to
//!   interior of the face rather than to its boundary.
//! - cross face errors. It is a situation when a point on a common
//!   boundary between two faces has different 3d coordinates on each
//!   triangulation. The error is reported if the distance is greater
//!   than a deflection written in triangulations.
//! - asynchronous edges. It is an edge having polygons on two neighboring
//!   triangulations with different number of points in the polygons.
//! - free nodes -- nodes not shared by any triangle.

class MeshTest_CheckTopology
{
public:
  //! constructor
  MeshTest_CheckTopology(const TopoDS_Shape& theShape)
      : myShape(theShape)
  {
  }

  //! performs checking
  Standard_EXPORT void Perform(Draw_Interpretor& di);

  //! returns the number of faces with free links
  int NbFacesWithFL() const { return myMapFaceLinks.Extent(); }

  //! returns the number (in the shape) of a face with free links
  //! with the given index
  int GetFaceNumWithFL(const int theIndex) const { return myMapFaceLinks.FindKey(theIndex); }

  //! returns the number free links on a face with the given index
  int NbFreeLinks(const int theIndex) const { return myMapFaceLinks(theIndex)->Length() / 2; }

  //! gets the numbers of nodes of a free link with the given index
  //! in the face with the given index
  Standard_EXPORT void GetFreeLink(const int theFaceIndex,
                                   const int theLinkIndex,
                                   int&      theNode1,
                                   int&      theNode2) const;

  //! returns the number of cross face errors
  int NbCrossFaceErrors() const { return myErrorsVal.Length(); }

  //! gets the attributes of a cross face error with the given index
  Standard_EXPORT void GetCrossFaceError(const int theIndex,
                                         int&      theFace1,
                                         int&      theNode1,
                                         int&      theFace2,
                                         int&      theNode2,
                                         double&   theValue) const;

  //! returns the number of async edges
  int NbAsyncEdges() const { return myAsyncEdges.Length(); }

  //! returns the number (in the shape) of an async edge with the given index
  int GetAsyncEdgeNum(const int theIndex) const { return myAsyncEdges(theIndex); }

  //! returns the number of free nodes
  int NbFreeNodes() const { return myFreeNodeFaces.Length(); }

  //! returns the number of face containing the Index-th detected free node,
  //! and number of this node in the triangulation of that face
  void GetFreeNodeNum(const int theIndex, int& theFaceNum, int& theNodeNum) const
  {
    theFaceNum = myFreeNodeFaces(theIndex);
    theNodeNum = myFreeNodeNums(theIndex);
  }

  //! Returns number of triangles with null area
  int NbSmallTriangles() const { return mySmallTrianglesFaces.Length(); }

  //! returns the number of face containing the Index-th detected
  //! small triangle and number of the problematic triangle in
  //! this face.
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

