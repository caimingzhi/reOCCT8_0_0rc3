#include <BRepMeshData_Model.hpp>

#include <BRepMeshData_Face.hpp>
#include <BRepMeshData_Edge.hpp>
#include <NCollection_IncAllocator.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMeshData_Model, IMeshData_Model)

BRepMeshData_Model::BRepMeshData_Model(const TopoDS_Shape& theShape)
    : IMeshData_Model(theShape),
      myMaxSize(0.),
      myAllocator(new NCollection_IncAllocator(IMeshData::MEMORY_BLOCK_SIZE_HUGE)),
      myDFaces(256, myAllocator),
      myDEdges(256, myAllocator)
{
  myAllocator->SetThreadSafe(true);
}

BRepMeshData_Model::~BRepMeshData_Model() = default;

int BRepMeshData_Model::FacesNb() const
{
  return myDFaces.Size();
}

const IMeshData::IFaceHandle& BRepMeshData_Model::AddFace(const TopoDS_Face& theFace)
{
  IMeshData::IFaceHandle aFace(new (myAllocator) BRepMeshData_Face(theFace, myAllocator));
  return myDFaces.Append(aFace);
}

const IMeshData::IFaceHandle& BRepMeshData_Model::GetFace(const int theIndex) const
{
  return myDFaces(theIndex);
}

int BRepMeshData_Model::EdgesNb() const
{
  return myDEdges.Size();
}

const IMeshData::IEdgeHandle& BRepMeshData_Model::AddEdge(const TopoDS_Edge& theEdge)
{
  IMeshData::IEdgeHandle aEdge(new (myAllocator) BRepMeshData_Edge(theEdge, myAllocator));
  return myDEdges.Append(aEdge);
}

const IMeshData::IEdgeHandle& BRepMeshData_Model::GetEdge(const int theIndex) const
{
  return myDEdges(theIndex);
}
