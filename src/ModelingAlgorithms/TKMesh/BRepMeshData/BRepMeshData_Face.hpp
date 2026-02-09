#pragma once

#include <IMeshData_Types.hpp>
#include <IMeshData_Face.hpp>
#include <IMeshData_Wire.hpp>

class BRepMeshData_Face : public IMeshData_Face
{
public:
  DEFINE_INC_ALLOC

  Standard_EXPORT BRepMeshData_Face(const TopoDS_Face&                           theFace,
                                    const occ::handle<NCollection_IncAllocator>& theAllocator);

  Standard_EXPORT ~BRepMeshData_Face() override;

  Standard_EXPORT int WiresNb() const override;

  Standard_EXPORT const IMeshData::IWireHandle& GetWire(const int theIndex) const override;

  Standard_EXPORT const IMeshData::IWireHandle& AddWire(const TopoDS_Wire& theWire,
                                                        const int          theEdgeNb = 0) override;

  DEFINE_STANDARD_RTTIEXT(BRepMeshData_Face, IMeshData_Face)

private:
  occ::handle<NCollection_IncAllocator> myAllocator;
  IMeshData::VectorOfIWireHandles       myDWires;
};
