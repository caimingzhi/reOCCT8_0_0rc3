#pragma once

#include <VrmlData_Geometry.hpp>

class VrmlData_Sphere : public VrmlData_Geometry
{
public:
  inline VrmlData_Sphere()
      : myRadius(1.)
  {
  }

  inline VrmlData_Sphere(const VrmlData_Scene& theScene,
                         const char*           theName,
                         const double          theRadius = 1.)
      : VrmlData_Geometry(theScene, theName),
        myRadius(theRadius)
  {
  }

  inline double Radius() const { return myRadius; }

  inline void SetRadius(const double theRadius)
  {
    myRadius = theRadius;
    SetModified();
  }

  Standard_EXPORT const occ::handle<TopoDS_TShape>& TShape() override;

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

private:
  double myRadius;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Sphere, VrmlData_Geometry)
};
