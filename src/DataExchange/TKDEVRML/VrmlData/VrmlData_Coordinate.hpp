#pragma once

#include <VrmlData_ArrayVec3d.hpp>

class VrmlData_Coordinate : public VrmlData_ArrayVec3d
{
public:
  inline VrmlData_Coordinate() = default;

  inline VrmlData_Coordinate(const VrmlData_Scene& theScene,
                             const char*           theName,
                             const size_t          nPoints   = 0,
                             const gp_XYZ*         arrPoints = nullptr)
      : VrmlData_ArrayVec3d(theScene, theName, nPoints, arrPoints)
  {
  }

  inline const gp_XYZ& Coordinate(const int i) const { return Value(i); }

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Coordinate, VrmlData_ArrayVec3d)
};
