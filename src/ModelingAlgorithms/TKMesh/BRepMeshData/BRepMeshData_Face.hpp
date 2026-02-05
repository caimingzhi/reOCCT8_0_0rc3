#pragma once

#include <IMeshData_Types.hpp>
#include <IMeshData_Face.hpp>
#include <IMeshData_Wire.hpp>

//! Default implementation of face data model entity.
class BRepMeshData_Face : public IMeshData_Face
{
public:
  DEFINE_INC_ALLOC

  //! Constructor.
  Standard_EXPORT BRepMeshData_Face(const TopoDS_Face&                           theFace,
                                    const occ::handle<NCollection_IncAllocator>& theAllocator);

  //! Destructor.
  Standard_EXPORT ~BRepMeshData_Face() override;

  //! Gets number of children.
  Standard_EXPORT int WiresNb() const override;

  //! Gets wire with the given index.
  Standard_EXPORT const IMeshData::IWireHandle& GetWire(const int theIndex) const override;

  //! Adds wire to discrete model of face.
  Standard_EXPORT const IMeshData::IWireHandle& AddWire(const TopoDS_Wire& theWire,
                                                        const int          theEdgeNb = 0) override;

  DEFINE_STANDARD_RTTIEXT(BRepMeshData_Face, IMeshData_Face)

private:
  occ::handle<NCollection_IncAllocator> myAllocator;
  IMeshData::VectorOfIWireHandles       myDWires;
};
