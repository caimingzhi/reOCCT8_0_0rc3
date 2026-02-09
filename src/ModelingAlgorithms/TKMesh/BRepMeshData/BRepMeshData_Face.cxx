#include <BRepMeshData_Face.hpp>
#include <BRepMeshData_Wire.hpp>
#include <BRepMesh_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMeshData_Face, IMeshData_Face)

BRepMeshData_Face::BRepMeshData_Face(const TopoDS_Face&                           theFace,
                                     const occ::handle<NCollection_IncAllocator>& theAllocator)
    : IMeshData_Face(theFace),
      myAllocator(theAllocator),
      myDWires(256, myAllocator)
{
}

BRepMeshData_Face::~BRepMeshData_Face() = default;

int BRepMeshData_Face::WiresNb() const
{
  return myDWires.Size();
}

const IMeshData::IWireHandle& BRepMeshData_Face::AddWire(const TopoDS_Wire& theWire,
                                                         const int          theEdgeNb)
{
  IMeshData::IWireHandle aWire(new (myAllocator)
                                 BRepMeshData_Wire(theWire, theEdgeNb, myAllocator));
  myDWires.Append(aWire);
  return GetWire(WiresNb() - 1);
}

const IMeshData::IWireHandle& BRepMeshData_Face::GetWire(const int theIndex) const
{
  return myDWires(theIndex);
}
