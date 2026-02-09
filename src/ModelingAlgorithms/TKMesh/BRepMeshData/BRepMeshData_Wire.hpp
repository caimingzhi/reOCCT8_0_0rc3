#pragma once

#include <IMeshData_Wire.hpp>
#include <IMeshData_Types.hpp>

class BRepMeshData_Wire : public IMeshData_Wire
{
public:
  DEFINE_INC_ALLOC

  Standard_EXPORT BRepMeshData_Wire(const TopoDS_Wire&                           theWire,
                                    const int                                    theEdgeNb,
                                    const occ::handle<NCollection_IncAllocator>& theAllocator);

  Standard_EXPORT ~BRepMeshData_Wire() override;

  Standard_EXPORT int EdgesNb() const override;

  Standard_EXPORT int AddEdge(const IMeshData::IEdgePtr& theDEdge,
                              const TopAbs_Orientation   theOrientation) override;

  Standard_EXPORT const IMeshData::IEdgePtr& GetEdge(const int theIndex) const override;

  Standard_EXPORT TopAbs_Orientation GetEdgeOrientation(const int theIndex) const override;

  DEFINE_STANDARD_RTTIEXT(BRepMeshData_Wire, IMeshData_Wire)

private:
  IMeshData::VectorOfIEdgePtrs   myDEdges;
  IMeshData::VectorOfOrientation myDEdgesOri;
};
