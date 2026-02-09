#pragma once

#include <VrmlData_Geometry.hpp>
#include <gp_XYZ.hpp>

class VrmlData_Box : public VrmlData_Geometry
{
public:
  inline VrmlData_Box()
      : mySize(2., 2., 2.)
  {
  }

  inline VrmlData_Box(const VrmlData_Scene& theScene,
                      const char*           theName,
                      const double          sizeX = 2.,
                      const double          sizeY = 2.,
                      const double          sizeZ = 2.)
      : VrmlData_Geometry(theScene, theName),
        mySize(sizeX, sizeY, sizeZ)
  {
  }

  inline const gp_XYZ& Size() const { return mySize; }

  inline void SetSize(const gp_XYZ& theSize)
  {
    mySize = theSize;
    SetModified();
  }

  Standard_EXPORT const occ::handle<TopoDS_TShape>& TShape() override;

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

private:
  gp_XYZ mySize;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Box, VrmlData_Geometry)
};
