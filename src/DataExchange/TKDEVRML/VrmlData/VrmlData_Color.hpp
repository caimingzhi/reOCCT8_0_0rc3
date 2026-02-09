#pragma once

#include <VrmlData_ArrayVec3d.hpp>
#include <Quantity_Color.hpp>
#include <gp_XYZ.hpp>

class VrmlData_Color : public VrmlData_ArrayVec3d
{
public:
  inline VrmlData_Color() = default;

  inline VrmlData_Color(const VrmlData_Scene& theScene,
                        const char*           theName,
                        const size_t          nColors   = 0,
                        const gp_XYZ*         arrColors = nullptr)
      : VrmlData_ArrayVec3d(theScene, theName, nColors, arrColors)
  {
  }

  inline const Quantity_Color Color(const int i) const
  {
    return Quantity_Color(Value(i).X(), Value(i).Y(), Value(i).Z(), Quantity_TOC_sRGB);
  }

  inline void SetColors(const size_t nColors, const gp_XYZ* arrColors)
  {
    myLength = nColors;
    myArray  = arrColors;
  }

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Color, VrmlData_ArrayVec3d)
};
