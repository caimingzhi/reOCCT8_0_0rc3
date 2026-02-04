#pragma once


#include <Standard_Transient.hpp>
// Created on: 2011-06-01
// Created by: Oleg AGASHIN
// Copyright (c) 2011-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.


#include <Precision.hpp>
#include <gp_XY.hpp>
#include <IMeshData_Types.hpp>
#include <NCollection_CellFilter.hpp>
#include <BRepMesh_Vertex.hpp>

//! Class intended for fast searching of the coincidence points.
class BRepMesh_VertexInspector : public NCollection_CellFilter_InspectorXY
{
public:
  typedef int Target;

  //! Constructor.
  //! @param theAllocator memory allocator to be used by internal collections.
  BRepMesh_VertexInspector(const occ::handle<NCollection_IncAllocator>& theAllocator)
      : myIndex(0),
        myMinSqDist(RealLast()),
        myVertices(new IMeshData::VectorOfVertex),
        myDelNodes(theAllocator)
  {
    SetTolerance(Precision::Confusion());
  }

  //! Registers the given vertex.
  //! @param theVertex vertex to be registered.
  int Add(const BRepMesh_Vertex& theVertex)
  {
    if (myDelNodes.IsEmpty())
    {
      myVertices->Append(theVertex);
      return myVertices->Length();
    }

    int aNodeIndex                          = myDelNodes.First();
    myVertices->ChangeValue(aNodeIndex - 1) = theVertex;
    myDelNodes.RemoveFirst();
    return aNodeIndex;
  }

  //! Sets the tolerance to be used for identification of
  //! coincident vertices equal for both dimensions.
  void SetTolerance(const double theTolerance)
  {
    myTolerance[0] = theTolerance * theTolerance;
    myTolerance[1] = 0.;
  }

  //! Sets the tolerance to be used for identification of
  //! coincident vertices.
  //! @param theToleranceX tolerance for X dimension.
  //! @param theToleranceY tolerance for Y dimension.
  void SetTolerance(const double theToleranceX, const double theToleranceY)
  {
    myTolerance[0] = theToleranceX * theToleranceX;
    myTolerance[1] = theToleranceY * theToleranceY;
  }

  //! Clear inspector's internal data structures.
  void Clear()
  {
    myVertices->Clear();
    myDelNodes.Clear();
  }

  //! Deletes vertex with the given index.
  //! @param theIndex index of vertex to be removed.
  void Delete(const int theIndex)
  {
    myVertices->ChangeValue(theIndex - 1).SetMovability(BRepMesh_Deleted);
    myDelNodes.Append(theIndex);
  }

  //! Returns number of registered vertices.
  int NbVertices() const { return myVertices->Length(); }

  //! Returns vertex with the given index.
  BRepMesh_Vertex& GetVertex(int theIndex) { return myVertices->ChangeValue(theIndex - 1); }

  //! Set reference point to be checked.
  void SetPoint(const gp_XY& thePoint)
  {
    myIndex     = 0;
    myMinSqDist = RealLast();
    myPoint     = thePoint;
  }

  //! Returns index of point coinciding with regerence one.
  int GetCoincidentPoint() const { return myIndex; }

  //! Returns list with indexes of vertices that have movability attribute
  //! equal to BRepMesh_Deleted and can be replaced with another node.
  const IMeshData::ListOfInteger& GetListOfDelPoints() const { return myDelNodes; }

  //! Returns set of mesh vertices.
  const Handle(IMeshData::VectorOfVertex)& Vertices() const { return myVertices; }

  //! Returns set of mesh vertices for modification.
  Handle(IMeshData::VectorOfVertex)& ChangeVertices() { return myVertices; }

  //! Performs inspection of a point with the given index.
  //! @param theTargetIndex index of a circle to be checked.
  //! @return status of the check.
  Standard_EXPORT NCollection_CellFilter_Action Inspect(const int theTargetIndex);

  //! Checks indices for equality.
  static bool IsEqual(const int theIndex, const int theTargetIndex)
  {
    return (theIndex == theTargetIndex);
  }

private:
  int                               myIndex;
  double                            myMinSqDist;
  double                            myTolerance[2];
  Handle(IMeshData::VectorOfVertex) myVertices;
  IMeshData::ListOfInteger          myDelNodes;
  gp_XY                             myPoint;
};


#include <Standard_OStream.hpp>
#include <gp_XY.hpp>
#include <IMeshData_Types.hpp>

//! Describes data structure intended to keep mesh nodes
//! defined in UV space and implements functionality
//! providing their uniqueness regarding their position.
class BRepMesh_VertexTool : public Standard_Transient
{
public:
  //! Constructor.
  //! @param theAllocator memory allocator to be used by internal collections.
  Standard_EXPORT BRepMesh_VertexTool(const occ::handle<NCollection_IncAllocator>& theAllocator);

  //! Sets new size of cell for cellfilter equal in both directions.
  void SetCellSize(const double theSize)
  {
    myCellFilter.Reset(theSize, myAllocator);
    mySelector.Clear();
  }

  //! Sets new size of cell for cellfilter.
  //! @param theSizeX size for X dimension.
  //! @param theSizeY size for Y dimension.
  void SetCellSize(const double theSizeX, const double theSizeY)
  {
    double                     aCellSizeC[2] = {theSizeX, theSizeY};
    NCollection_Array1<double> aCellSize(aCellSizeC[0], 1, 2);
    myCellFilter.Reset(aCellSize, myAllocator);
    mySelector.Clear();
  }

  //! Sets the tolerance to be used for identification of
  //! coincident vertices equal for both dimensions.
  void SetTolerance(const double theTolerance)
  {
    mySelector.SetTolerance(theTolerance);
    myTolerance[0] = theTolerance;
    myTolerance[1] = theTolerance;
  }

  //! Sets the tolerance to be used for identification of
  //! coincident vertices.
  //! @param theToleranceX tolerance for X dimension.
  //! @param theToleranceY tolerance for Y dimension.
  void SetTolerance(const double theToleranceX, const double theToleranceY)
  {
    mySelector.SetTolerance(theToleranceX, theToleranceY);
    myTolerance[0] = theToleranceX;
    myTolerance[1] = theToleranceY;
  }

  //! Gets the tolerance to be used for identification of
  //! coincident vertices.
  //! @param theToleranceX tolerance for X dimension.
  //! @param theToleranceY tolerance for Y dimension.
  void GetTolerance(double& theToleranceX, double& theToleranceY)
  {
    theToleranceX = myTolerance[0];
    theToleranceY = myTolerance[1];
  }

  //! Adds vertex with empty data to the tool.
  //! @param theVertex node to be added to the mesh.
  //! @param isForceAdd adds the given node to structure without
  //! checking on coincidence with other nodes.
  //! @return index of the node in the structure.
  Standard_EXPORT int Add(const BRepMesh_Vertex& theVertex, const bool isForceAdd);

  //! Deletes vertex with the given index from the tool.
  Standard_EXPORT void DeleteVertex(const int theIndex);

  //! Returns set of mesh vertices.
  const Handle(IMeshData::VectorOfVertex)& Vertices() const { return mySelector.Vertices(); }

  //! Returns set of mesh vertices.
  Handle(IMeshData::VectorOfVertex)& ChangeVertices() { return mySelector.ChangeVertices(); }

  //! Returns vertex by the given index.
  const BRepMesh_Vertex& FindKey(const int theIndex) { return mySelector.GetVertex(theIndex); }

  //! Returns index of the given vertex.
  int FindIndex(const BRepMesh_Vertex& theVertex)
  {
    mySelector.SetPoint(theVertex.Coord());
    myCellFilter.Inspect(theVertex.Coord(), mySelector);
    return mySelector.GetCoincidentPoint();
  }

  //! Returns a number of vertices.
  int Extent() const { return mySelector.NbVertices(); }

  //! Returns True when the map contains no keys.
  bool IsEmpty() const { return (Extent() == 0); }

  //! Substitutes vertex with the given by the given vertex with attributes.
  //! @param theIndex index of vertex to be substituted.
  //! @param theVertex replacement vertex.
  Standard_EXPORT void Substitute(const int theIndex, const BRepMesh_Vertex& theVertex);

  //! Remove last node from the structure.
  void RemoveLast() { DeleteVertex(Extent()); }

  //! Returns the list with indexes of vertices that have movability attribute
  //! equal to BRepMesh_Deleted and can be replaced with another node.
  const IMeshData::ListOfInteger& GetListOfDelNodes() const
  {
    return mySelector.GetListOfDelPoints();
  }

  //! Prints statistics.
  Standard_EXPORT void Statistics(Standard_OStream& theStream) const;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_VertexTool, Standard_Transient)

private:
  //! Expands the given point according to specified tolerance.
  //! @param thePoint point to be expanded.
  //! @param[out] theMinPoint bottom left corner of area defined by expanded point.
  //! @param[out] theMaxPoint top right corner of area defined by expanded point.
  void expandPoint(const gp_XY& thePoint, gp_XY& theMinPoint, gp_XY& theMaxPoint)
  {
    theMinPoint.SetX(thePoint.X() - myTolerance[0]);
    theMinPoint.SetY(thePoint.Y() - myTolerance[1]);
    theMaxPoint.SetX(thePoint.X() + myTolerance[0]);
    theMaxPoint.SetY(thePoint.Y() + myTolerance[1]);
  }

private:
  occ::handle<NCollection_IncAllocator> myAllocator;
  IMeshData::VertexCellFilter           myCellFilter;
  BRepMesh_VertexInspector              mySelector;
  double                                myTolerance[2];
};

