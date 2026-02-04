#pragma once


#include <IMeshData_Wire.hpp>
#include <IMeshData_Types.hpp>

//! Default implementation of wire data model entity.
class BRepMeshData_Wire : public IMeshData_Wire
{
public:
  DEFINE_INC_ALLOC

  //! Constructor.
  Standard_EXPORT BRepMeshData_Wire(const TopoDS_Wire&                           theWire,
                                    const int                                    theEdgeNb,
                                    const occ::handle<NCollection_IncAllocator>& theAllocator);

  //! Destructor.
  Standard_EXPORT ~BRepMeshData_Wire() override;

  //! Gets number of children.
  Standard_EXPORT int EdgesNb() const override;

  //! Adds new discrete edge with specified orientation to wire chain.
  //! @return index of added edge in wire chain.
  Standard_EXPORT int AddEdge(const IMeshData::IEdgePtr& theDEdge,
                              const TopAbs_Orientation   theOrientation) override;

  //! Gets edge with the given index.
  Standard_EXPORT const IMeshData::IEdgePtr& GetEdge(const int theIndex) const override;

  //! Returns True if orientation of discrete edge with the given index is forward.
  Standard_EXPORT TopAbs_Orientation GetEdgeOrientation(const int theIndex) const override;

  DEFINE_STANDARD_RTTIEXT(BRepMeshData_Wire, IMeshData_Wire)

private:
  IMeshData::VectorOfIEdgePtrs   myDEdges;
  IMeshData::VectorOfOrientation myDEdgesOri;
};

