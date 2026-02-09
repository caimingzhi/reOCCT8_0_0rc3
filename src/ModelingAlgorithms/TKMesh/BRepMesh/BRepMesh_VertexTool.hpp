#pragma once

#include <Standard_Transient.hpp>

#include <Precision.hpp>
#include <gp_XY.hpp>
#include <IMeshData_Types.hpp>
#include <NCollection_CellFilter.hpp>
#include <BRepMesh_Vertex.hpp>

class BRepMesh_VertexInspector : public NCollection_CellFilter_InspectorXY
{
public:
  typedef int Target;

  BRepMesh_VertexInspector(const occ::handle<NCollection_IncAllocator>& theAllocator)
      : myIndex(0),
        myMinSqDist(RealLast()),
        myVertices(new IMeshData::VectorOfVertex),
        myDelNodes(theAllocator)
  {
    SetTolerance(Precision::Confusion());
  }

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

  void SetTolerance(const double theTolerance)
  {
    myTolerance[0] = theTolerance * theTolerance;
    myTolerance[1] = 0.;
  }

  void SetTolerance(const double theToleranceX, const double theToleranceY)
  {
    myTolerance[0] = theToleranceX * theToleranceX;
    myTolerance[1] = theToleranceY * theToleranceY;
  }

  void Clear()
  {
    myVertices->Clear();
    myDelNodes.Clear();
  }

  void Delete(const int theIndex)
  {
    myVertices->ChangeValue(theIndex - 1).SetMovability(BRepMesh_Deleted);
    myDelNodes.Append(theIndex);
  }

  int NbVertices() const { return myVertices->Length(); }

  BRepMesh_Vertex& GetVertex(int theIndex) { return myVertices->ChangeValue(theIndex - 1); }

  void SetPoint(const gp_XY& thePoint)
  {
    myIndex     = 0;
    myMinSqDist = RealLast();
    myPoint     = thePoint;
  }

  int GetCoincidentPoint() const { return myIndex; }

  const IMeshData::ListOfInteger& GetListOfDelPoints() const { return myDelNodes; }

  const Handle(IMeshData::VectorOfVertex)& Vertices() const { return myVertices; }

  Handle(IMeshData::VectorOfVertex)& ChangeVertices() { return myVertices; }

  Standard_EXPORT NCollection_CellFilter_Action Inspect(const int theTargetIndex);

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

class BRepMesh_VertexTool : public Standard_Transient
{
public:
  Standard_EXPORT BRepMesh_VertexTool(const occ::handle<NCollection_IncAllocator>& theAllocator);

  void SetCellSize(const double theSize)
  {
    myCellFilter.Reset(theSize, myAllocator);
    mySelector.Clear();
  }

  void SetCellSize(const double theSizeX, const double theSizeY)
  {
    double                     aCellSizeC[2] = {theSizeX, theSizeY};
    NCollection_Array1<double> aCellSize(aCellSizeC[0], 1, 2);
    myCellFilter.Reset(aCellSize, myAllocator);
    mySelector.Clear();
  }

  void SetTolerance(const double theTolerance)
  {
    mySelector.SetTolerance(theTolerance);
    myTolerance[0] = theTolerance;
    myTolerance[1] = theTolerance;
  }

  void SetTolerance(const double theToleranceX, const double theToleranceY)
  {
    mySelector.SetTolerance(theToleranceX, theToleranceY);
    myTolerance[0] = theToleranceX;
    myTolerance[1] = theToleranceY;
  }

  void GetTolerance(double& theToleranceX, double& theToleranceY)
  {
    theToleranceX = myTolerance[0];
    theToleranceY = myTolerance[1];
  }

  Standard_EXPORT int Add(const BRepMesh_Vertex& theVertex, const bool isForceAdd);

  Standard_EXPORT void DeleteVertex(const int theIndex);

  const Handle(IMeshData::VectorOfVertex)& Vertices() const { return mySelector.Vertices(); }

  Handle(IMeshData::VectorOfVertex)& ChangeVertices() { return mySelector.ChangeVertices(); }

  const BRepMesh_Vertex& FindKey(const int theIndex) { return mySelector.GetVertex(theIndex); }

  int FindIndex(const BRepMesh_Vertex& theVertex)
  {
    mySelector.SetPoint(theVertex.Coord());
    myCellFilter.Inspect(theVertex.Coord(), mySelector);
    return mySelector.GetCoincidentPoint();
  }

  int Extent() const { return mySelector.NbVertices(); }

  bool IsEmpty() const { return (Extent() == 0); }

  Standard_EXPORT void Substitute(const int theIndex, const BRepMesh_Vertex& theVertex);

  void RemoveLast() { DeleteVertex(Extent()); }

  const IMeshData::ListOfInteger& GetListOfDelNodes() const
  {
    return mySelector.GetListOfDelPoints();
  }

  Standard_EXPORT void Statistics(Standard_OStream& theStream) const;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_VertexTool, Standard_Transient)

private:
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
