#include <BRepMeshData_Wire.hpp>
#include <IMeshData_Edge.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMeshData_Wire, IMeshData_Wire)

//=================================================================================================

BRepMeshData_Wire::BRepMeshData_Wire(const TopoDS_Wire&                           theWire,
                                     const int                                    theEdgeNb,
                                     const occ::handle<NCollection_IncAllocator>& theAllocator)
    : IMeshData_Wire(theWire),
      myDEdges(theEdgeNb > 0 ? theEdgeNb : 256, theAllocator),
      myDEdgesOri(theEdgeNb > 0 ? theEdgeNb : 256, theAllocator)
{
}

//=================================================================================================

BRepMeshData_Wire::~BRepMeshData_Wire() = default;

//=================================================================================================

int BRepMeshData_Wire::EdgesNb() const
{
  return myDEdges.Size();
}

//=================================================================================================

int BRepMeshData_Wire::AddEdge(const IMeshData::IEdgePtr& theDEdge,
                               const TopAbs_Orientation   theOrientation)
{
  const int aIndex = EdgesNb();

  myDEdges.Append(theDEdge);
  myDEdgesOri.Append(theOrientation);

  return aIndex;
}

//=================================================================================================

const IMeshData::IEdgePtr& BRepMeshData_Wire::GetEdge(const int theIndex) const
{
  return myDEdges(theIndex);
}

//=================================================================================================

TopAbs_Orientation BRepMeshData_Wire::GetEdgeOrientation(const int theIndex) const
{
  return myDEdgesOri(theIndex);
}
