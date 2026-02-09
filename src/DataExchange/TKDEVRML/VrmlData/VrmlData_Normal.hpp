#pragma once

#include <VrmlData_ArrayVec3d.hpp>

class VrmlData_Normal : public VrmlData_ArrayVec3d
{
public:
  inline VrmlData_Normal() = default;

  inline VrmlData_Normal(const VrmlData_Scene& theScene,
                         const char*           theName,
                         const size_t          nVec   = 0,
                         const gp_XYZ*         arrVec = nullptr)
      : VrmlData_ArrayVec3d(theScene, theName, nVec, arrVec)
  {
  }

  inline const gp_XYZ& Normal(const int i) const { return Value(i); }

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Normal, VrmlData_ArrayVec3d)
};
